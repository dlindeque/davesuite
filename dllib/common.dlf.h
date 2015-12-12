#pragma once

#include <string>
#include <vector>

#include "..\common\dsf.h"

namespace davelexer
{
    using namespace davecommon;

    struct DfaEdge{
        _char first;
        _char last;
        _int ToStateNo;
    };

    struct DfaState {
        _int StateNo;
        _bool IsFinal;
        _bool IsGoto;
        _bool IsPop;
        _string Token;
        _int GotoState;
        collection<DfaEdge> Edges;
        // DsExpression ValueExpression
    };

    struct LexerData {
        multimap<_string, _string> ContextItems;
        collection<DfaState> States;
    };

    struct context {
        // lookupFirst(name, data.ContextItems)
        inline auto operator()(const _string &name, const LexerData &data) -> option<_string> {
            // parameter 1 = name
            auto pexp1 = [&name, &data](){ return name; };

            // parameter 2 = data.ContextItems
            auto pexp2 = [&name, &data](){
                return data.ContextItems;
            };
            
            auto map = pexp2();
            auto f = map.find(pexp1());
            if (f == map.end()) {
                option<_string> { 
            }
            else {

            }
        }
    };
}