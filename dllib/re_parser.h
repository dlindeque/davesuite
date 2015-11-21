#pragma once

#include <istream>
#include <memory>
#include <vector>
#include <map>
#include "re_lexer.h"

#include "..\common\logger.h"
#include "log.h"
#include "model.h"

using namespace davecommon;

namespace davelexer
{
    auto re_try_parse(
        const container *cntr,
        std::wistream &src,
        logger *logger)->std::unique_ptr<re_ast>;
}
