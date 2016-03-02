//
//  dl.ds.cpp
//  test2
//
//  Created by David Lindeque on 14/12/2015.
//  Copyright © 2015 David Lindeque. All rights reserved.
//

#include "dc.ds.h"
#include "log.h"

namespace dc
{
    auto BuildNfaReAst::visit(const std::shared_ptr<CardinalReAst> &ast) -> void
    {
        // from -r-> t1 -r-> t2 -r-> t3 -r-> t4 -r-> to
        //                              -e-> to
        //                                      -e-> to
        size_t f = _from;
        auto tt = _to;
        if (ast->Min == 0) {
            size_t t = _nfa.next_state++;
            _nfa.transitions.emplace_back(_from, true, L' ', L' ', t);
            f = t;
        }
        else if (ast->Min < 0) {
            log::error::CardinalityInvalidMinimumValue(_logger, _cntr_stack.back(), ast->Spn, ast->Min);
            _ok = false;
            return;
        }
        for(int i = 0; i != ast->Min; i++) {
            size_t t = _nfa.next_state++;
            _from = f;
            _to = t;
            ast->RE->accept(ast->RE, this);
            f = t;
        }
        if (ast->Max == -1) {
            _from = f;
            _to = f;
            ast->RE->accept(ast->RE, this);
            _nfa.transitions.emplace_back(f, true, L' ', L' ', tt);
        }
        else if (ast->Max == ast->Min) {
            _nfa.transitions.emplace_back(f, true, L' ', L' ', tt);
        }
        else if (ast->Max > ast->Min) {
            // -..-> f  -e-> to
            //          -r-> t1  -e-> to
            //                   -r-> t2  -e-> to
            for(int i = ast->Min; i != ast->Max; i++) {
                _nfa.transitions.emplace_back(f, true, L' ', L' ', tt);
                size_t t = _nfa.next_state++;
                _from = f;
                _to = t;
                ast->RE->accept(ast->RE, this);
                f = t;
            }
            _nfa.transitions.emplace_back(f, true, L' ', L' ', tt);
        }
        else {
            log::error::CardinalityMaxLessThanMin(_logger, _cntr_stack.back(), ast->Spn, ast->Min, ast->Max);
            _ok = false;
        }
        
        _start_is_final = ast->Min == 0;
    }
    
    auto BuildNfaReAst::visit(const std::shared_ptr<ReferenceReAst> &ast) -> void
    {
        auto logger = _logger;
        bool found = false;
        auto _this = this;
        std::shared_ptr<container> prev_cntr;
        span prev_spn;
        auto &cntr_stack = _cntr_stack;
        bool &ok = _ok;
        container::find<std::shared_ptr<PatternAst>>(_cntr_stack.back(), ast->Name, _search_namespaces,
            [&logger, &cntr_stack, &ast, &found, &_this, &ok, &prev_cntr, &prev_spn]
            (const std::shared_ptr<container> &found_cntr, const std::shared_ptr<PatternAst> &p, const symbolreference &name, size_t index)
            {
                // We only process patterns if they matched completely
                if (index == name.size() - 1) {
                    if (found) {
                        // Found previously
                        ok = false;
                        log::error::SymbolFoundMoreThanOnce(logger, L"pattern", cntr_stack.back(), ast->Spn, ast->Name, found_cntr, p->Spn, prev_cntr, prev_spn);
                        return false;
                    } else {
                        prev_cntr = found_cntr;
                        prev_spn = p->Spn;
                        found = true;
                        cntr_stack.push_back(found_cntr);
                        p->Value->accept(p->Value, _this);
                        cntr_stack.pop_back();
                    }
                }
                return true;
            });
        if (!found) {
            log::error::SymbolNotFound(_logger, L"pattern", _cntr_stack.back(), ast->Spn, ast->Name);
            _ok = false;
        }
    }

    auto exclude_char_range(wchar_t first, wchar_t last, std::vector<std::pair<wchar_t, wchar_t>> &result) -> void 
    {
        // Remove this range from all the result
        size_t i = 0;
        std::vector<std::pair<wchar_t, wchar_t>> new_ranges;
        while(i < result.size()) {
            if (first <= result[i].first && last >= result[i].second) {
                // remove the whole gap
                result.erase(result.begin() + i);
            }
            else {
                if (first <= result[i].first && last >= result[i].first) {
                    result[i].first = last + 1;
                }
                if (last >= result[i].second && first <= result[i].second) {
                    result[i].second = first - 1;
                }
                if (first > result[i].first && last < result[i].second) {
                    new_ranges.emplace_back(last + 1, result[i].second);
                    result[i].second = first - 1;
                }
                i++;
            }
        }
        if (!new_ranges.empty()) {
            result.push_back(std::move(new_ranges.back()));
        }
    }
}