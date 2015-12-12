#pragma once

#include <string>
#include <memory>
#include <ostream>
#include <istream>
#include <unordered_map>
#include <set>
#include <sstream>
#include <assert.h>
#include "re_parser.h"
#include "model.h"

using namespace davecommon;

namespace davelexer
{
    struct state_yield {
        std::shared_ptr<std::wstring> token;
        std::shared_ptr<qname> goto_section;
        size_t goto_section_start;
        bool pop;
    };

    class dfa;

    class section_dependency_walker sealed : public const_lex_ast_visitor{
    private:
        logger *_logger;
        bool &_ok;
        qname _current_ns;
        bool _start_discovered = false;
        const container *_start_container;
        span _start_spn;
    public:
        section_dependency_walker(logger *logger, bool &ok)
            : _logger(logger), _ok(ok)
        {}

        qname _start_section;
        std::unordered_multimap<qname, qname> _goto_sections;
        std::unordered_multimap<qname, qname> _import_sections;

        virtual auto accept(const lex_ast_pattern* ast) -> void override {
        }
        virtual auto accept(const lex_ast_section* ast) -> void override {
            class walker sealed : public const_lex_ast_section_item_visitor{
            private:
                const qname &_section;
                std::unordered_multimap<qname, qname> &_goto_sections;
                std::unordered_multimap<qname, qname> &_import_sections;
            public:
                walker(const qname &section,
                    std::unordered_multimap<qname, qname> &goto_sections,
                    std::unordered_multimap<qname, qname> &import_sections)
                    : _section(section), _goto_sections(goto_sections), _import_sections(import_sections)
                { }
                virtual auto accept(const lex_ast_import* ast) -> void override {
                    _import_sections.emplace(_section, ast->section_to_import());
                }
                virtual auto accept(const lex_ast_token*) -> void override {
                }
                virtual auto accept(const lex_ast_start* ast) -> void override {
                    _goto_sections.emplace(_section, ast->section_name());
                }
                virtual auto accept(const lex_ast_return*) -> void override {
                }
            };
            qname n(_current_ns);
            n.parts.push_back(ast->name());
            walker w(n, _goto_sections, _import_sections);
            for (auto &item : ast->items()) {
                item->accept(&w);
            }
        }
        virtual auto accept(const lex_ast_option_start* ast) -> void override {
            if (_start_discovered) {
                log::error::duplicate_start_specification(_logger, ast->ctnr(), ast->spn(), _start_container, _start_spn);
                _ok = false;
            }
            else {
                _start_discovered = true;
                _start_section = ast->section_name();
                _start_container = ast->ctnr();
                _start_spn = ast->spn();
            }
        }
        virtual auto accept(const lex_namespace* ast) -> void override {
            for (auto &n : ast->name().parts){
                _current_ns.parts.push_back(n);
            }
            for (auto &item : ast->items()) {
                item->accept(this);
            }
            for (size_t i = 0; i < ast->name().parts.size(); i++){
                _current_ns.parts.pop_back();
            }
        }
        virtual auto accept(const lex_using_namespace*) -> void override {
        }
    };

    class nfa_builder sealed : public lex_ast_visitor{
    private:
        bool &_ok;
        qname _current_ns;
        logger *_logger; // The logger to write errors to
        size_t _next_state; // The next state to create
        std::unordered_map<qname, std::unique_ptr<re_ast>> _patterns; // The discovered patterns
        std::unordered_map<qname, std::vector<std::unique_ptr<lex_ast_section_item>>> _import_section_items; // The items of the section to be imported into other sections
        std::unordered_map<qname, size_t> _sections_start_states; // The start state numbers for each section
        std::vector<fa_transition> _transitions; // The discovered nfa-transitions
        std::unordered_map<size_t, state_yield> _state_yields; // The discovered token yield per state
        std::unordered_map<std::wstring, std::shared_ptr<std::wstring>> _tokens; // The token map (we're keeping a pointer to each token for performance and space)
        std::unordered_map<qname, std::shared_ptr<qname>> _section_names;
        std::unordered_map<std::wstring, std::vector<position>> _precedences;
    public:
        nfa_builder(bool &ok, logger *logger, const section_dependency_walker &walker)
            : _logger(logger), _ok(ok), _next_state(0)
        {
            // We immediately take state 0 for the start state
            _sections_start_states.emplace(walker._start_section, 0);
            _next_state = 1;
            
            std::vector<qname> unprocessed;
            unprocessed.push_back(walker._start_section);
            while (!unprocessed.empty()) {
                auto gtof = walker._goto_sections.equal_range(unprocessed.back());
                auto impf = walker._import_sections.equal_range(unprocessed.back());
                unprocessed.pop_back();
                // for each goto statement, we need a start state
                for (auto i = gtof.first; i != gtof.second; i++) {
                    if (_sections_start_states.find(i->second) == _sections_start_states.end()) {
                        _sections_start_states.emplace(i->second, _next_state++);
                        unprocessed.push_back(i->second);
                    }
                }
                // For each import statement, we need to note the import requirement (add empty section to be populated later)
                for (auto i = impf.first; i != impf.second; i++) {
                    if (_import_section_items.find(i->second) == _import_section_items.end()) {
                        _import_section_items.emplace(i->second, std::vector<std::unique_ptr<lex_ast_section_item>>());
                        unprocessed.push_back(i->second);
                    }
                }
            }
        }
        virtual ~nfa_builder() {}

        inline auto transitions() const -> const std::vector<fa_transition>& { return  _transitions; }
        inline auto state_yields() const -> const std::unordered_map<size_t, state_yield>& { return _state_yields; }
        inline auto state_yields() -> std::unordered_map<size_t, state_yield>& { return _state_yields; }
        inline auto precedences() const -> const std::unordered_map<std::wstring, std::vector<position>>& { return _precedences; }

        virtual auto accept(lex_ast_pattern* ast) -> void override {
            qname n(_current_ns);
            n.parts.push_back(ast->name());
            if (!_patterns.emplace(std::move(n), std::move(ast->ast())).second) {
                log::error::pattern_already_defined(_logger, ast->ctnr(), ast->spn(), _current_ns, ast->name());
                _ok = false;
            }
        }
        virtual auto accept(lex_ast_section* ast) -> void override;
        virtual auto accept(lex_ast_option_start* ast) -> void override {
        }
        virtual auto accept(lex_namespace* ast) -> void override {
            for (auto &n : ast->name().parts){
                _current_ns.parts.push_back(n);
            }
            for (auto &item : ast->items()) {
                item->accept(this);
            }
            for (size_t i = 0; i < ast->name().parts.size(); i++){
                _current_ns.parts.pop_back();
            }
        }
        virtual auto accept(lex_using_namespace*) -> void override {
        }

        friend dfa;
    };
}