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
        std::shared_ptr<std::wstring> goto_section;
        size_t goto_section_start;
        bool pop;
    };

    class dfa;

    class nfa_builder sealed : public lex_ast_visitor{
    private:
        logger *_logger;
        size_t _next_state;
        std::unordered_map<std::wstring, std::unique_ptr<re_ast>> _patterns;
        std::unordered_map<std::wstring, std::vector<std::unique_ptr<lex_ast_section_item>>> _shared_sections;

        std::unordered_map<std::wstring, size_t> _sections;
        std::vector<fa_transition> _transitions;
        std::unordered_map<size_t, state_yield> _state_yields;
        std::unordered_map<std::wstring, std::shared_ptr<std::wstring>> _tokens;
        std::unordered_map<std::wstring, std::shared_ptr<std::wstring>> _section_names;
        std::unordered_map<std::wstring, std::vector<position>> _precedences;
    public:
        nfa_builder(logger *logger)
            : _logger(logger), _ok(true), _next_state(0)
        {
            // We immediately take states 0 as default section states
            _sections.emplace(L"default", 0);
            _next_state = 1;
        }
        virtual ~nfa_builder() {}

        bool _ok;

        inline auto transitions() const -> const std::vector<fa_transition>& { return  _transitions; }
        inline auto state_yields() const -> const std::unordered_map<size_t, state_yield>& { return _state_yields; }
        inline auto state_yields() -> std::unordered_map<size_t, state_yield>& { return _state_yields; }
        inline auto precedences() const -> const std::unordered_map<std::wstring, std::vector<position>>& { return _precedences; }

        virtual auto accept(lex_ast_pattern* ast) -> void override {
            if (!_patterns.emplace(std::move(ast->name()), std::move(ast->ast())).second) {
                log::error::pattern_already_defined(_logger, ast->ctnr(), ast->spn(), ast->name());
                _ok = false;
            }
        }
        virtual auto accept(lex_ast_section* ast) -> void override;

        friend dfa;
    };
}