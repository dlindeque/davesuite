#include "stdafx.h"
#include "nfa.h"
#include "re_lexer.h"

#define START_STATE 0x00000000;
#define FINAL_STATE 0x0FFFFFFF;

namespace davelexer
{    
    auto nfa::try_add(const std::wstring &token, std::wistream &re, std::wostream &errors)->bool
    {
        //auto t = get_next_token(re);
        //while (t.type != re_token_type::eod) {
        //
        //    t = get_next_token(re, t.state);
        //}
        errors << L"Not Implemented";
        return false;
    }

    auto nfa::try_compile(bool &ok, std::wostream &errors) -> dfa {
        throw std::exception("not implemneted");
    }
}