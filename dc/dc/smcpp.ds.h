//
//  smcpp.dc.h
//  dc
//
//  Created by David Lindeque on 30/01/2016.
//  Copyright © 2016 David Lindeque. All rights reserved.
//

#pragma once

#include "dc.ds.h"
#include "logger.h"
#include <string>
#include <unordered_map>

namespace dc
{
    auto smcpp_write(logger *logger, const dfa &dfa, const std::unordered_map<std::wstring, std::wstring> &settings) -> bool;
}

