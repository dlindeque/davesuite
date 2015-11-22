#pragma once

#include <string>
#include <memory>
#include <ostream>
#include <istream>
#include <map>
#include <set>
#include <sstream>
#include <assert.h>
#include "re_parser.h"
#include "model.h"

using namespace davecommon;

namespace davelexer
{
    struct section_anchors {
        size_t start;
        size_t recurse;
        size_t end;
    };

    struct token_yield {
        size_t yield;
        std::wstring goto_section;
        bool pop;
    };

    struct yield_details {
        std::wstring token;
        size_t goto_state;
        bool pop;
    };

    class dfa;

    class nfa_builder sealed : public lex_ast_visitor{
    private:
        logger *_logger;
        size_t _next_state;
        size_t _next_yield;
        std::map<std::wstring, std::unique_ptr<re_ast>> _bindings;
        std::map<std::wstring, std::vector<std::unique_ptr<lex_ast_section_item>>> _shared_sections;

        std::map<std::wstring, section_anchors> _sections;
        std::map<std::wstring, std::vector<token_yield>> _token_yields;
        std::vector<fa_transition> _transitions;
    public:
        nfa_builder(logger *logger)
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
        virtual ~nfa_builder() {}

        bool _ok;

        inline auto compile_yield_details() const->std::map < size_t, yield_details > {
            std::map<size_t, yield_details> m;
            for (auto &ty : _token_yields) {
                for (auto &t : ty.second) {
                    if (!t.goto_section.empty()) {
                        auto f = _sections.find(t.goto_section);
                        assert(f != _sections.end());
                        m.emplace(t.yield, yield_details{ ty.first, f->second.start, t.pop });
                    } else {
                        m.emplace(t.yield, yield_details{ ty.first, 0, t.pop });
                    }
                }
            }
            return m;
        }
        inline auto transitions() const -> const std::vector<fa_transition>& { return  _transitions; }

        virtual auto accept(lex_ast_binding* ast) -> void override {
            if (!_bindings.emplace(std::move(ast->name()), std::move(ast->ast())).second) {
                log::error::binding_already_defined(_logger, ast->ctnr(), ast->spn(), ast->name());
                _ok = false;
            }
        }
        virtual auto accept(lex_ast_section* ast) -> void override;

        friend dfa;
    };
}