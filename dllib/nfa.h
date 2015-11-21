﻿#pragma once

#include <string>
#include <memory>
#include <ostream>
#include <istream>
#include <map>
#include <set>
#include <sstream>
#include "re_parser.h"
#include "model.h"

using namespace davecommon;

namespace davelexer
{
    struct token_yield {
        size_t yield;
        std::wstring goto_section;
        bool pop;
    };

    class lex_ast_nfa_generator sealed : public lex_ast_visitor{
    private:
        struct section_anchors {
            size_t start;
            size_t recurse;
            size_t end;
        };
        logger *_logger;
        size_t _next_state;
        size_t _next_yield;
        std::map<std::wstring, std::unique_ptr<re_ast>> _bindings;
        std::map<std::wstring, std::vector<std::unique_ptr<lex_ast_section_item>>> _shared_sections;
        std::map<std::wstring, section_anchors> _sections;
    public:
        lex_ast_nfa_generator(logger *logger)
            : _logger(logger), _ok(true), _next_state(0), _next_yield(1)
        {
            // We immediately take states 0, 1, 2 & 3 as default section states
            _sections.emplace(L"default", section_anchors{ 0, 1, 2 });
            _next_state = 4;
            // Setup common default transitions
            // 0 - epsilon -> 1
            _transitions.emplace_back(0, true, false, 0, 0, 1, 0);
            // 2 - epsilon -> 1
            _transitions.emplace_back(2, true, false, 0, 0, 1, 0);
            // 1 - eod -> 3
            _transitions.emplace_back(1, false, true, 0, 0, 3, 0);
        }
        virtual ~lex_ast_nfa_generator() {}

        bool _ok;
        std::vector<fa_transition> _transitions;
        std::map<std::wstring, std::vector<token_yield>> _token_yields;

        virtual auto accept(lex_ast_binding* ast) -> void override {
            _bindings.emplace(std::move(ast->name()), std::move(ast->ast()));
        }
        virtual auto accept(lex_ast_section* ast) -> void override;
    };
}