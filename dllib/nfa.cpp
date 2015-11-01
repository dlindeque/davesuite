#include "stdafx.h"
#include "nfa.h"
#include "re_lexer.h"

#define START_STATE 0x00000000;
#define FINAL_STATE 0x0FFFFFFF;

namespace davelexer
{    
    auto nfa::try_add(const std::wstring &section, const std::wstring &token_name, nfa_action action, container *container, const token &re, logger *logger)->bool
    {
        //auto t = get_next_token(re);
        //while (t.type != re_token_type::eod) {
        //
        //    t = get_next_token(re, t.state);
        //}
        log::error::invalid_cardinality(logger, container, span(), 0, 1);
        return false;
    }

    auto nfa::try_compile(bool &ok, std::wostream &errors) -> dfa {
        throw std::exception("not implemneted");
    }
}