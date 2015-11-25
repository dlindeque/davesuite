#include "stdafx.h"

#include <assert.h>

#include "nfa_builder.h"
#include "re_lexer.h"
#include "..\common\offset_logger.h"
#include "log.h"

namespace davelexer
{
    class re_ast_processor sealed : public const_re_ast_visitor{
    private:
        size_t &_next_state;
        std::vector<fa_transition> &_transitions;
        const std::unordered_map<std::wstring, std::unique_ptr<re_ast>> &_patterns;

        size_t _from;
        size_t _to;

        bool &_ok;
        logger *& _logger;
        const container * _cntr;
    public:
        re_ast_processor(size_t &next_state, 
            std::vector<fa_transition> &transitions, 
            const std::unordered_map<std::wstring, std::unique_ptr<re_ast>> &patterns,
            size_t from, 
            size_t to, 
            bool &ok,
            logger *&logger,
            const container *cntr)
            : _next_state(next_state), _transitions(transitions), _patterns(patterns), _from(from), _to(to), _ok(ok), _logger(logger), _cntr(cntr)
        {}

        virtual ~re_ast_processor() {}
        virtual auto accept(const re_ast_char_set_match* ast) -> void override {
            if (ast->exclude()) {
                // Build the include ranges by excluding the ranges from the universe
                std::vector<wchar_range> universe;
                universe.push_back(wchar_range{ 0, WCHAR_MAX });
                for (auto &range : ast->ranges()) {
                    register size_t i = 0;
                    std::vector<wchar_range> new_ranges;
                    while (i < universe.size()) {
                        if (range.from <= universe[i].from) {
                            if (range.to >= universe[i].to) {
                                // delete the whole universe item
                                universe.erase(universe.begin() + i);
                            }
                            else if (range.to >= universe[i].from) {
                                // trim the front
                                universe[i].from = range.to + 1;
                                i++;
                            }
                            else {
                                // the whole range is in front of the universe item
                                i++;
                            }
                        }
                        else if (range.to >= universe[i].to) {
                            // range.from > universe[i].from
                            if (range.from <= universe[i].to) {
                                // trim the end
                                universe[i].to = range.from - 1;
                                i++;
                            }
                            else {
                                // the whole range is beyond the universe item
                                i++;
                            }
                        }
                        else {
                            // range.from > universe[i].from & range.to < universe[i].to
                            // split the universe item
                            new_ranges.push_back(wchar_range{ range.to + 1, universe[i].to });
                            universe[i].to = range.from - 1;
                            i++;
                        }
                    }
                    for (auto &nr : new_ranges) {
                        universe.push_back(std::move(nr));
                    }
                }
                // Include the universe
                for (auto &range : universe) {
                    _transitions.emplace_back(_from, false, range.from, range.to, _to);
                }
            }
            else {
                // Include all the ranges
                for (auto &range : ast->ranges()) {
                    _transitions.emplace_back(_from, false, range.from, range.to, _to);
                }
            }
        }
        virtual auto accept(const re_ast_reference* ast) -> void override {
            auto f = _patterns.find(ast->name());
            if (f == _patterns.end()) {
                log::error::expression_not_found(_logger, _cntr, ast->spn(), ast->name());
                _ok = false;
            }
            else {
                f->second->accept(this);
            }
        }
        virtual auto accept(const re_ast_then* ast) -> void override {
            auto tt = _to;
            auto tf = _from;
            _to = _next_state++;
            ast->re1()->accept(this);
            _from = _to;
            _to = tt;
            ast->re2()->accept(this);
            _from = tf;
        }
        virtual auto accept(const re_ast_or* ast) -> void override {
            ast->re1()->accept(this);
            ast->re2()->accept(this);
        }
        virtual auto accept(const re_ast_cardinality* ast) -> void override {
            // X -E-> X --min*re--> X -E-> X
            //                      X --min+1--> X
            //                      X --min+2--> X
            //                      ...
            //                      X --max-min--> X

            // re{2-4}: FROM -E-> S0 -re-> S1 -re-> S2 -E->           TO
            //                                         -re->          TO
            //                                         -re-> S3 -re-> TO
            auto tt = _to;
            auto tf = _from;
            // Add the 'min' transitions
            for (int i = 0; i < ast->min(); i++) {
                _to = _next_state++;
                ast->re()->accept(this);
                _from = _to;
            }
            
            // If the max is infinate, then we recurse on the current state
            if (ast->min() == ast->max()) {
                // add an epsilon s -E-> to_state
                _to = tt;
                _transitions.emplace_back(_from, true, 0, 0, _to);
                _from = tf;
            }
            else if (ast->max() == -1) {
                auto t1 = _next_state++;
                auto t2 = _next_state++;
                _transitions.emplace_back(_from, true, 0, 0, t1);
                _transitions.emplace_back(_from, true, 0, 0, tt);
                _transitions.emplace_back(t2, true, 0, 0, t1);
                _transitions.emplace_back(t2, true, 0, 0, tt);
                _from = t1;
                _to = t2;
                ast->re()->accept(this);
                _from = tf;
                _to = tt;
            }
            else {
                _transitions.emplace_back(_from, true, 0, 0, tt);
                for (int i = ast->min(); i < ast->max(); i++) {
                    _to = _next_state++;
                    ast->re()->accept(this);
                    _from = _to;
                    _transitions.emplace_back(_from, true, 0, 0, tt);
                }
                _from = tf;
                _to = tt;
            }
        }
    };

    class lex_ast_section_item_processor sealed : public lex_ast_section_item_visitor{
    private:
        bool &_ok;
        const container * _cntr;
        logger *& _logger;
        size_t &_next_state;
        const std::unordered_map<std::wstring, std::unique_ptr<re_ast>> &_patterns;
        const std::unordered_map<std::wstring, std::vector<std::unique_ptr<lex_ast_section_item>>> &_shared_sections;
        std::vector<fa_transition> &_transitions;
        std::unordered_map<size_t, state_yield> &_state_yields;
        std::unordered_map<std::wstring, std::shared_ptr<std::wstring>> &_tokens;
        std::unordered_map<std::wstring, std::shared_ptr<std::wstring>> &_section_names;
        inline auto add_token_transitions(const std::shared_ptr<std::wstring> &token, const std::shared_ptr<std::wstring> &goto_section, bool pop, const std::unique_ptr<re_ast> &ast) -> void {
            // start - ast -> t(yield)
            auto t = _next_state++;
            re_ast_processor rep(_next_state, _transitions, _patterns, start, t, _ok, _logger, _cntr);
            ast->accept(&rep);
            _state_yields.emplace(t, state_yield{ token, goto_section, pop });
        }
        inline auto get_shared_str(std::unordered_map<std::wstring, std::shared_ptr<std::wstring>> &map, const std::wstring &value)->std::shared_ptr < std::wstring > {
            auto f = map.find(value);
            if (f == map.end()) {
                auto x = map.emplace(value, std::make_shared<std::wstring>(value));
                return x.first->second;
            }
            else {
                return f->second;
            }
        }
    public:
        lex_ast_section_item_processor(bool &ok, const container *cntr, logger *& logger, size_t &next_state,
            const std::unordered_map<std::wstring, std::unique_ptr<re_ast>> &patterns,
            const std::unordered_map<std::wstring, std::vector<std::unique_ptr<lex_ast_section_item>>> &shared_sections,
            std::vector<fa_transition> &transitions,
            std::unordered_map<size_t, state_yield> &state_yields,
            std::unordered_map<std::wstring, std::shared_ptr<std::wstring>> &tokens,
            std::unordered_map<std::wstring, std::shared_ptr<std::wstring>> &section_names)
            : _ok(ok), _cntr(cntr), _logger(logger), _next_state(next_state),
            _patterns(patterns), _shared_sections(shared_sections), _transitions(transitions),
            _state_yields(state_yields), _tokens(tokens), _section_names(section_names)
        {}
        virtual ~lex_ast_section_item_processor() {}

        size_t start;

        virtual auto accept(lex_ast_import* ast) -> void override {
            auto f = _shared_sections.find(ast->shared_section_to_import());
            if (f == _shared_sections.end()) {
                davecommon::log::error::imported_section_not_found(_logger, _cntr, ast->spn(), ast->shared_section_to_import());
                _ok = false;
            }
            else {
                for (auto &item : f->second) {
                    item->accept(this);
                }
            }
        }
        virtual auto accept(lex_ast_token* ast) -> void override {
            add_token_transitions(get_shared_str(_tokens, ast->token_name()), nullptr, false, ast->ast());
        }
        virtual auto accept(lex_ast_start* ast) -> void override {
            add_token_transitions(get_shared_str(_tokens, ast->token_name()), get_shared_str(_section_names, ast->section_name()), false, ast->ast());
        }
        virtual auto accept(lex_ast_return* ast) -> void override {
            add_token_transitions(get_shared_str(_tokens, ast->token_name()), nullptr, true, ast->ast());
        }
    };

    auto nfa_builder::accept(lex_ast_section* ast) -> void
    {
        if (ast->is_shared()) {
            _shared_sections.emplace(std::move(ast->name()), std::move(ast->items()));
        }
        else {
            lex_ast_section_item_processor item_processor(_ok, ast->ctnr(), _logger, _next_state, _patterns, _shared_sections, _transitions, _state_yields, _tokens, _section_names);
            auto f = _sections.find(ast->name());
            if (f == _sections.end()) {
                // Create the section
                auto s = _sections.emplace(ast->name(), _next_state++);
                item_processor.start = s.first->second;
            }
            else {
                item_processor.start = f->second;
            }
            for (auto &item : ast->items()) {
                item->accept(&item_processor);
            }
        }
    }
}


