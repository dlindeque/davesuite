#pragma once

#include <string>
#include <vector>
#include <memory>

#include "token.h"

namespace daveparser
{
    struct production
    {
        std::unique_ptr<token> name;
        std::vector<std::unique_ptr<token>> items;
    };
}