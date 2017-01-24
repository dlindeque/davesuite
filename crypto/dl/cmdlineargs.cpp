#include "stdafx.h"
#include "cmdlineargs.h"

#include <locale>
#include <codecvt>
#include <iostream>

#ifdef _UNICODE
#define _ADD_ARG_MAP(key, value) args.emplace(key, converter.to_bytes(std::wstring(value)))
#else
#define _ADD_ARG_MAP(key, value) args.emplace(key, std::string(value))
#endif

namespace dave
{
    auto load_args(int argc, _TCHAR* argv[], const std::wstring &argname, cmdargmap &args) -> void
    {
#ifdef _UNICODE
        typedef std::codecvt_utf8<wchar_t> convert_type;
        std::wstring_convert<convert_type, wchar_t> converter;
#endif
        for (int i = 1; i < argc; i++) {
            if (_tcsnicmp(argv[i], (L"/" + argname + L":").c_str(), argname.size() + 2) == 0) {
                _ADD_ARG_MAP(std::string(argname.begin(), argname.end()), argv[i] + argname.size() + 2);
            }
        }
    }

    auto get_single_mandatory_arg(const cmdargmap &args, const std::string &name, bool &ok)->std::string
    {
        std::string value;
        bool found = false;
        auto f = args.equal_range(name);
        for (auto i = f.first; i != f.second; i++) {
            if (found) {
                std::cout << "The argument '" << name << "' was given more than once." << std::endl;
                ok = false;
                return "";
            }
            else {
                found = true;
                value = i->second;
            }
        }

        if (!found) {
            std::cout << "The argument '" << name << "' was not specified." << std::endl;
            ok = false;
        }
        return value;
    }

    auto get_multi_args(const cmdargmap &args, const std::string &name, std::vector<std::string> &results) -> void
    {
        auto f = args.equal_range(name);
        for (auto i = f.first; i != f.second; i++) {
            results.push_back(i->second);
        }
    }
}