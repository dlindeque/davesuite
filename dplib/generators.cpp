#include "stdafx.h"
#include "generators.h"
#include "log.h"

using namespace davecommon;

namespace daveparser
{
    auto lr<0>::generate(const std::vector<production> &grammar) -> parser_table
    {
        return parser_table{};
    }

    auto lalr<1>::generate(const std::vector<production> &grammar) -> parser_table
    {
        return parser_table{};
    }

    auto ielr<1>::generate(const std::vector<production> &grammar) -> parser_table
    {
        return parser_table{};
    }
}