#pragma once

#include "production.h"
#include "parser_tables.h"

#include <vector>

namespace daveparser
{
    /*
    A grammar (G) is usually defined as the tuple {T,N,P,S} where
        T: set of terminals
        N: set of non-terminals
        P: set of productions
        S: start non-terminal

        We can infer T & N from P. N is the set of all symbols in the LHS position, while T is the rest.
        We also have the convention that P[0] is S.

        Thus, we have the full grammar spec by just a set of productions.
    */

    template<int lookahead> struct lr { };

    template<> struct lr<0> {
        enum { lookahead = 0 };
        static auto generate(const std::vector<production> &grammar)->parser_table;
    };

    template<int lookahead> struct lalr { };

    template<> struct lalr<1> {
        enum { lookahead = 1 };
        static auto generate(const std::vector<production> &grammar)->parser_table;
    };

    template<int lookahead> struct ielr { };

    template<> struct ielr<1> {
        enum { lookahead = 1 };
        static auto generate(const std::vector<production> &grammar)->parser_table;
    };
}