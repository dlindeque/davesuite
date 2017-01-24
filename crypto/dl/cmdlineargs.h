#pragma once

#include <string>
#include <unordered_map>
#include <tchar.h>
#include <vector>

namespace dave
{
    typedef std::unordered_multimap<std::string, std::string> cmdargmap;

    auto load_args(int argc, _TCHAR* argv[], const std::wstring &argname, cmdargmap &args) -> void;
    auto get_single_mandatory_arg(const cmdargmap &args, const std::string &name, bool &ok)->std::string;
    auto get_multi_args(const cmdargmap &args, const std::string &name, std::vector<std::string> &results) -> void;
}