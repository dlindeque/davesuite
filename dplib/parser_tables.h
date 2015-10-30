#pragma once

#include <vector>
#include <unordered_map>
#include "production.h"

namespace daveparser
{
    
    enum class parser_table_action_type
    {
        shift,
        reduce,
        _goto
    };

    struct parser_table_action {
        parser_table_action_type type;
        union {
            size_t state;
            const production *rule;
        };
    };

    typedef std::vector<parser_table_action> parser_table_cell;

    struct parser_table_row {
        std::vector<parser_table_cell> cells;
        size_t error_state;
    };

    struct parser_table {
        std::vector<const std::wstring*> symbols;
        std::vector<parser_table_row> rows;
    };
}