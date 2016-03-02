//
//  main.cpp
//  dc
//
//  Created by David Lindeque on 11/01/2016.
//  Copyright © 2016 David Lindeque. All rights reserved.
//

#include <iostream>
#include <dirent.h>
#include "compiler.h"

#include "dfa.h"

#include "lexer_formatter.h"
#include "graph_formatter.h"
#include "model_formatter.h"

using namespace dc;

class console_logger : public logger {
protected:
    virtual auto write(severity s, unsigned int errorno, const std::shared_ptr<container> &cntr, const span &spn, const std::wstring &msg) -> void {
        if (cntr == nullptr) {
            std::wcout << msg << std::endl;
        } else {
            auto fspn = cntr->map_to_file(spn);
            auto n = cntr->name();
            switch (s) {
                case severity::info:
                    std::wcout << L"INFO ";
                    break;
                case severity::warning:
                    std::wcout << L"WARNING ";
                    break;
                case severity::error:
                    std::wcout << L"ERROR ";
                    break;
                default:
                    std::wcout << L"UNKNOWN ";
                    break;
            }
            //std::wcout << errorno << L" -------------------------------------------------------------------------------" << std::endl;
            //std::wcout << std::wstring(n.begin(), n.end()) << std::endl;
            std::wcout << errorno << L' ' << std::wstring(n.begin(), n.end()) << L' ' << fspn.begin.line << L':' << fspn.begin.column << L'-' << fspn.end.line << L':' << fspn.end  .column << L' ' << msg << std::endl;
        }
    }
};
        
typedef std::unordered_multimap<std::wstring, std::wstring> settings_map;

inline auto s2w(const char *s) -> std::wstring
{
    std::string ss(s);
    return std::wstring(ss.begin(), ss.end());
}
            
inline auto parse_options(int argc, const char *argv[], settings_map &settings, std::string &compile_fn) -> bool
{
    // dc.exe /path:/Users/davidlindeque/Documents/ /output:nfa_gv /output:dfa_gv /output:cpp_lexer /Users/davidlindeque/davesuite/dc/dc/lexer.ds
    for(int i = 1;i<argc;i++) {
        //std::cout << i << ": " << argv[i] << std::endl;
        if (strncmp(argv[i], "/path:", 6) == 0) {
            settings.emplace(L"path", s2w(argv[i] + 6));
        } else if (strncmp(argv[i], "/output:", 8) == 0) {
            settings.emplace(L"output", s2w(argv[i] + 8));
        } else if (strncmp(argv[i], "/include:", 9) == 0) {
            settings.emplace(L"include", s2w(argv[i] + 9));
        } else {
            if (compile_fn.empty()) {
                compile_fn = argv[i];
            } else {
                std::wcout << L"Cannot specify more than one input file" << std::endl;
                return false;
            }
        }
    }

    //compile_fn = "/Users/davidlindeque/davesuite/dc/dc/lexer.ds";

    //settings.emplace(L"path", L"/Users/davidlindeque/davesuite/dc/dc/gen/");
    //settings.emplace(L"output", L"nfa_gv");
    //settings.emplace(L"output", L"dfa_gv");
    //settings.emplace(L"output", L"cpp_lexer");
    
    return true;
}

template<typename T, class _Deserializer> inline auto get_unique_option(const settings_map &settings, const std::wstring &name, bool mandatory, const T &defaultValue, T &result, const _Deserializer &deserializer) -> bool {
    auto f = settings.equal_range(name);
    if (f.first == f.second) {
        if (mandatory) {
            std::wcout << L"The command line option '" << name << L"' could not be found" << std::endl;
            return false;
        } else {
            result = defaultValue;
            return true;
        }
    }
    auto i = f.first;
    i++;
    if (i != f.second) {
        std::wcout << L"The command line option '" << name << L"' was found more than once." << std::endl;
        return false;
    }

    return deserializer(f.first->second, result);
}

template<typename T, class _Deserializer>
inline auto get_non_unique_option(const settings_map &settings, const std::wstring &name, std::vector<T> &result, const _Deserializer &deserializer) -> bool {
    auto f = settings.equal_range(name);
    for(auto &i = f.first; i != f.second; i++) {
        result.emplace_back(T());
        if (!deserializer(i->second, result.back())) {
            return false;
        }
    }
    return true;
}

template<typename T, class _Deserializer>
inline auto get_non_unique_option(const settings_map &settings, const std::wstring &name, std::set<T> &result, const _Deserializer &deserializer) -> bool {
    auto f = settings.equal_range(name);
    for(auto &i = f.first; i != f.second; i++) {
        T x;
        deserializer(i->second, x);
        result.emplace(x);
    }
    return true;
}

inline auto get_bool_option(const settings_map &settings, const std::wstring &name, bool mandatory, bool defaultValue, bool &result) -> bool {
    return get_unique_option(settings, name, mandatory, defaultValue, result, [](const std::wstring &value, bool &result) {
        result = (value == L"y" || value == L"Y");
        return true;
    });
}

inline auto get_string_option(const settings_map &settings, const std::wstring &name, bool mandatory, std::wstring defaultValue, std::wstring &result) -> bool {
    return get_unique_option(settings, name, mandatory, defaultValue, result, [](const std::wstring &value, std::wstring &result) {
        result = value;
        return true;
    });
}

inline auto get_string_option(const settings_map &settings, const std::wstring &name, bool mandatory, std::string defaultValue, std::string &result) -> bool {
    return get_unique_option(settings, name, mandatory, defaultValue, result, [](const std::wstring &value, std::string &result) {
        result = std::string(value.begin(), value.end());
        return true;
    });
}

inline auto get_string_options(const settings_map &settings, const std::wstring &name, std::vector<std::wstring> &result) -> bool
{
    return get_non_unique_option(settings, name, result, [](const std::wstring &value, std::wstring &result)
    {
        result = value;
        return true;
    });
}
inline auto get_string_options(const settings_map &settings, const std::wstring &name, std::set<std::wstring> &result) -> bool
{
    return get_non_unique_option(settings, name, result, [](const std::wstring &value, std::wstring &result)
    {
        result = value;
        return true;
    });
}
inline auto get_string_options(const settings_map &settings, const std::wstring &name, std::vector<std::string> &result) -> bool
{
    return get_non_unique_option(settings, name, result, [](const std::wstring &value, std::string &result)
    {
        result = std::string(value.begin(), value.end());
        return true;
    });
}
inline auto get_string_options(const settings_map &settings, const std::wstring &name, std::set<std::string> &result) -> bool
{
    return get_non_unique_option(settings, name, result, [](const std::wstring &value, std::string &result)
    {
        result = std::string(value.begin(), value.end());
        return true;
    });
}

inline auto output_require_lexer(const std::set<std::wstring> &output) -> bool {
    return output.find(L"cpp_lexer") != output.end()
        || output.find(L"cs_lexer") != output.end()
        || output.find(L"js_lexer") != output.end();
}

inline auto output_require_dfa(const std::set<std::wstring> &output) -> bool {
    return output.find(L"dfa_gv") != output.end()
        || output_require_lexer(output);
}

inline auto output_require_nfa(const std::set<std::wstring> &output) -> bool {
    return output.find(L"nfa_gv") != output.end()
        || output_require_dfa(output);
}
            
inline auto output_require_dfa_validation(const std::set<std::wstring> &output) -> bool {
    return output_require_lexer(output);
}

inline auto create_directory(const std::string &path) -> void {
    mkdir(path.c_str(), 0777);
}

int main(int argc, const char * argv[]) 
{
    std::wcout << L"Dave Compiler 0.1" << std::endl;

    settings_map settings;
    std::string compile_fn, path;
    if (!parse_options(argc, argv, settings, compile_fn)) {
        return 1;
    }
    
    std::vector<std::string> search_directories;
    std::set<std::wstring> output;

    if (!get_string_options(settings, L"include", search_directories)) {
        return 1;
    }
    if (!get_string_options(settings, L"output", output)) {
        return 1;
    }
    if (!get_string_option(settings, L"path", true, "", path)) {
        return 1;
    }

    if (output.find(L"cpp_lexer") != output.end()) {
        output.emplace(L"cpp_model");
    }
    if (output.find(L"cs_lexer") != output.end()) {
        output.emplace(L"cs_model");
    }
    if (output.find(L"js_lexer") != output.end()) {
        output.emplace(L"js_model");
    }

    create_directory(path);

    console_logger logger;
    bool ok = true;

    // Process the file
    DocumentAstProcessor processor(&logger, ok, search_directories);
    processor.process_root_container(compile_fn);

    if (!ok) {
        return 1;
    }

    if (output_require_nfa(output)) {
        // We require a start symbol
        if (processor.start_symbol_cntr() == nullptr) {
            log::error::StartSymbolNotDefined(&logger);
            return 1;
        }
        
        // Find the start automata
        size_t start_automata_state = find_automata(processor.start_symbol(), 
                                                    processor.start_symbol_cntr(), 
                                                    processor.start_symbol_spn(),
                                                    std::vector<symbolreference>(),
                                                    &logger,
                                                    ok);

        if (!ok) {
            return 1;
        }
    
        // We need to add an epsilon transition from 0 to the start start
        processor.nfa().transitions.push_back(Transition(0, true, L' ', L' ', start_automata_state));
        processor.nfa().automataspns.emplace(0, processor.nfa().automataspns[start_automata_state]);   
    }

    if (output.find(L"nfa_gv") != output.end()) {
        output_nfa_gv op(&logger, compile_fn, path);
        ok &= op(processor);
    }

    if (output_require_dfa(output)) {
        processor.dfa() = build_dfa(&logger, processor.nfa());
    }

    if (output.find(L"dfa_gv") != output.end()) {
        output_dfa_gv op(&logger, compile_fn, path);
        ok &= op(processor);
    }

    if (output_require_dfa_validation(output)) {
        // Validate the DFA and determine find the Default Actions (error or rewind)
        if (!valid_and_find_default_actions(&logger, processor.dfa())) {
            return 1;
        }

        // We split the transitions that 'contains' the '\n' and '\r' characters since we'll use them during position calculations
        split_position_character_transitions(processor.dfa());

        if (output_require_lexer(output)) {
            // We need to type the automata match statements - all reachable match statements must have same type
            // For now we find the first 'token' type and use that
            if (!processor.match_expressions().empty()) {
                auto &me = processor.match_expressions()[0];
                processor.automata_match_return_type() = find_enum<true>(me.item->TokenName, me.cntr, me.item->Spn, me.search_namespaces, &logger, ok);
                //auto found_enum = find_enum(me.item->TokenName, me.cntr, me.item->Spn, me.search_namespaces, &logger, ok);
                //if (found_enum != nullptr) {
                //    symbolreference enum_fullname(((NamespaceAst*)found_enum->DeclaringAst)->Name);
                //    enum_fullname.push_back(found_enum->Name);
                //    processor.automata_match_return_type() = std::move(enum_fullname);
                //}
            }
        }
    }

    if (output.find(L"cpp_lexer") != output.end()) {
        output_lexer_cpp op(&logger, compile_fn, path);
        ok &= op(processor);
    }

    if (output.find(L"cpp_model") != output.end()) {
        output_model_cpp op(&logger, compile_fn, path);
        ok &= op(processor);
    }

    return ok ? 0 : 1;
}



