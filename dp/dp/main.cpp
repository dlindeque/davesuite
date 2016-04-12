//
//  main.cpp
//  dp
//
//  Created by David Lindeque on 19/12/2015.
//  Copyright © 2015 David Lindeque. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <map>
#include <fstream>
#include <codecvt>
#include <dirent.h>
#include <sys/stat.h>

#include "dp.ds.h"

#define NEW_LEXER

using namespace daveparser;

enum class dpp_token
{
    eod,
    hypens,
    productions,
    colon,
    identifier,
    produced_by,
    text,
    semicolon,
    error,
    equals
};

inline auto char_is_ws(wchar_t ch, int &line) -> bool {
    if (ch == L'\n') { line++; return true; }
    if (ch == L'\r') return true;
    if (ch == L' ') return true;
    if (ch == L'\t') return true;
    if (ch == L'\f') return true;
    if (ch == L'\v') return true;
    return false;
}

inline auto get_non_ws(std::wifstream &stm, int &line) -> std::wifstream::int_type {
    auto ch = stm.get();
    while(true) {
        if (ch == std::char_traits<wchar_t>::eof()) return ch;
        if (!char_is_ws(ch, line)) return ch;
        ch = stm.get();
    }
}

inline auto read_next_dpp_token(std::wifstream &stm, int &state, std::wstring &value, int &line) -> dpp_token {
    value.clear();
    if (state == 1) {
        // We're reading the action text
        bool escaped = false;
        while(true) {
            auto ch = stm.get();
            if (ch == std::char_traits<wchar_t>::eof()) {
                return dpp_token::eod;
            }
            if (ch == L'\n') line++;
            if (escaped) {
                value += (wchar_t)ch;
                escaped = false;
            } else if ((wchar_t)ch == L'\\') {
                escaped = true;
            } else if ((wchar_t)ch == L';') {
                stm.unget();
                state = 0;
                return dpp_token::text;
            } else {
                value += (wchar_t)ch;
            }
        }
    } else {
        // Reading normal productions
        while(true) {
            auto ch = get_non_ws(stm, line);
            switch(ch) {
                case std::char_traits<wchar_t>::eof():
                    return dpp_token::eod;
                case L'-': // either -> or ---..--
                    if (true) {
                        ch = stm.get();
                        if (ch == L'>') {
                            // We need to read the action after this
                            state = 1;
                            return dpp_token::produced_by;
                        }
                        while(ch == L'-') {
                            ch = stm.get();
                        }
                        stm.unget();
                    }
                    return dpp_token::hypens;
                case L':':
                    return dpp_token::colon;
                case L';':
                    return dpp_token::semicolon;
                case L'=':
                    return dpp_token::equals;
                default:
                    if (true) {
                        bool is_id = false;
                        while ((ch >= L'a' && ch <= L'z')
                               || (ch >= L'A' && ch <= L'Z')
                               || (ch >= L'0' && ch <= L'9')
                               || (ch == L'.')
                               || (ch == L'_')) {
                            is_id = true;
                            value += (wchar_t)ch;
                            ch = stm.get();
                            if (ch == L'\n') line++;
                        }
                        if (is_id) {
                            stm.unget();
                            if (value == L"Productions") {
                                return dpp_token::productions;
                            } else {
                                return dpp_token::identifier;
                            }
                        } else {
                            value += (wchar_t)ch;
                            return dpp_token::error;
                        }
                    }
                    break;
            }
        }
    }
}

inline auto resolve_conflict(const std::map<std::pair<const Production*, std::wstring>, ConflictResolution>& resolutions, const Production *reduction, const std::wstring &shift) -> ConflictResolution {
    //std::wcout << reduction->Name << L':';
    //for(auto &item : reduction->Items) {
    //    std::wcout << L' ' << item;
    //}
    //std::wcout << L' ' << shift << L" -> ???;" << std::endl;
    //return ConflictResolution::Reduce;
    auto f = resolutions.find(std::pair<const Production*, std::wstring>(reduction, shift));
    if (f == resolutions.end()) {
        std::wcout << L"Unresolved conflict" << std::endl;
        std::wcout << L"  " << reduction->Name << L':';
        for(auto &item : reduction->Items) {
            std::wcout << L' ' << item;
        }
        std::wcout << L" " << shift << std::endl;
        return ConflictResolution::DontKnow;
    } else {
        std::wcout << L"Resolving conflict" << std::endl;
        std::wcout << L"  " << reduction->Name << L':';
        for(auto &item : reduction->Items) {
            std::wcout << L' ' << item;
        }
        std::wcout << L" " << shift << std::endl;
        std::wcout << L"  As ";
        switch(f->second) {
            case ConflictResolution::Shift:
                std::wcout << L"Shift" << std::endl;
                break;
            case ConflictResolution::Reduce:
                std::wcout << L"Reduce" << std::endl;
                break;
            default:
                std::wcout << L"Don't know!" << std::endl;
                break;
        }
        return f->second;
    }
}
        
inline auto as_cpp_token(const std::wstring &tkn) -> std::wstring {
    std::wstring s;
    for(auto &ch : tkn) {
        if (ch == L'.') {
            s.append(L"::");
        } else {
            s += ch;
        }
    }
    return s;
}
        
inline auto toupper(const std::wstring &value) -> std::wstring {
    std::wstring s;
    for(auto &ch : value) {
        s += std::toupper(ch);
    }
    return s;
}

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

inline auto create_directory(const std::string &path) -> void {
    mkdir(path.c_str(), 0777);
}

inline auto extract_filename(const std::string &path) -> std::string
{
    // Get abc.xyz from /path1/path2/abc.xyz
    // or /abc.xyz
    // or abc.xyz

    auto f = path.find_last_of("/");
    if (f != std::string::npos) {
        return std::string(path.begin() + f + 1, path.end());
    } 
    else {
        return path;
    }
}

inline auto combine_path_filename(const std::string &path, const std::string &fn) -> std::string
{
    if (path.empty()) return fn;
    auto x = path.end();
    x--;
    if (*x == '/') {
        return path + fn;
    }
    else {
        return path + "/" + fn;
    }
}

inline auto get_standard_output_filename(const std::string &parent_filename, const std::string &output_path, const std::string &new_ext) -> std::string
{
    return combine_path_filename(output_path, extract_filename(parent_filename) + new_ext);
}
        
int main(int argc, const char * argv[]) {

    std::wcout << L"Dave Temporary Parser 0.1" << std::endl;

    settings_map settings;
    std::string compile_fn, path;
    if (!parse_options(argc, argv, settings, compile_fn)) {
        return 1;
    }
    
    std::set<std::wstring> output;

    if (!get_string_option(settings, L"path", true, "", path)) {
        return 1;
    }

    create_directory(path);
    std::string output_fn = get_standard_output_filename(compile_fn, path, ".cpp");
    std::string output_h = get_standard_output_filename(compile_fn, path, ".h");

    std::vector<Production> productions;
    std::wstring start;
    std::map<std::wstring, std::wstring> production_type;
    std::map<std::pair<const Production*, std::wstring>, ConflictResolution> resolutions;
    
    // Parse the dpp file
    std::wifstream dpp(compile_fn, std::ios::binary);
    if (!dpp.is_open()) {
        std::wcout << L"Failure opening " << std::wstring(compile_fn.begin(), compile_fn.end()) << std::endl;
        return 1;
    }
    dpp.imbue(std::locale(dpp.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, (std::codecvt_mode)(std::little_endian | std::consume_header)>));
    
    int s2 = 0, line = 0;
    std::wstring value;
    auto tkn = read_next_dpp_token(dpp, s2, value, line);
    if (tkn != dpp_token::hypens) { std::wcout << line << L": " << L"Expecting hyphens" << std::endl; return 1; }
    tkn = read_next_dpp_token(dpp, s2, value, line);
    if (tkn != dpp_token::productions) { std::wcout << line << L": " << L"Expecting Productions" << std::endl; return 1; }
    tkn = read_next_dpp_token(dpp, s2, value, line);
    if (tkn != dpp_token::colon) { std::wcout << line << L": " << L"Expecting :" << std::endl; return 1; }
    tkn = read_next_dpp_token(dpp, s2, value, line);
    if (tkn != dpp_token::identifier) { std::wcout << line << L": " << L"Expecting identifier" << std::endl; return 1; }
    start = std::move(value);
    tkn = read_next_dpp_token(dpp, s2, value, line);
    if (tkn != dpp_token::hypens) { std::wcout << line << L": " << L"Expecting hyphens" << std::endl; return 1; }
    tkn = read_next_dpp_token(dpp, s2, value, line);
    while(tkn != dpp_token::hypens) {
        Production p;
        if (tkn != dpp_token::identifier) { std::wcout << line << L": " << L"Expecting identifier" << std::endl; return 1; }
        p.Name = value;
        tkn = read_next_dpp_token(dpp, s2, value, line);
        if (tkn != dpp_token::colon) { std::wcout << line << L": " << L"Expecting :" << std::endl; return 1; }
        tkn = read_next_dpp_token(dpp, s2, value, line);
        while(tkn == dpp_token::identifier) {
            p.Items.push_back(std::move(value));
            tkn = read_next_dpp_token(dpp, s2, value, line);
        }
        if (tkn != dpp_token::produced_by) { std::wcout << line << L": " << L"Expecting ->" << std::endl; return 1; }
        tkn = read_next_dpp_token(dpp, s2, value, line);
        if (tkn != dpp_token::text) { std::wcout << line << L": " << L"Expecting action text" << std::endl; return 1; }
        p.Action = value;
        tkn = read_next_dpp_token(dpp, s2, value, line);
        if (tkn != dpp_token::semicolon) { std::wcout << line << L": " << L"Expecting ;" << std::endl; return 1; }
        productions.push_back(std::move(p));
        tkn = read_next_dpp_token(dpp, s2, value, line);
    }
    tkn = read_next_dpp_token(dpp, s2, value, line);
    while(tkn != dpp_token::hypens) {
        std::wstring name;
        if (tkn != dpp_token::identifier) { std::wcout << line << L": " << L"Expecting identifier" << std::endl; return 1; }
        name = std::move(value);
        tkn = read_next_dpp_token(dpp, s2, value, line);
        if (tkn != dpp_token::produced_by) { std::wcout << line << L": " << L"Expecting ->" << std::endl; return 1; }
        tkn = read_next_dpp_token(dpp, s2, value, line);
        if (tkn != dpp_token::text) { std::wcout << line << L": " << L"Expecting type text" << std::endl; return 1; }
        production_type.emplace(std::move(name), std::move(value));
        tkn = read_next_dpp_token(dpp, s2, value, line);
        if (tkn != dpp_token::semicolon) { std::wcout << line << L": " << L"Expecting ;" << std::endl; return 1; }
        tkn = read_next_dpp_token(dpp, s2, value, line);
    }
    tkn = read_next_dpp_token(dpp, s2, value, line);
    while(tkn != dpp_token::eod) {
        std::wstring name;
        std::vector<std::wstring> items;
        ConflictResolution action;
        if (tkn != dpp_token::identifier) { std::wcout << line << L": " << L"Expecting identifier" << std::endl; return 1; }
        name = value;
        tkn = read_next_dpp_token(dpp, s2, value, line);
        if (tkn != dpp_token::colon) { std::wcout << line << L": " << L"Expecting :" << std::endl; return 1; }
        tkn = read_next_dpp_token(dpp, s2, value, line);
        while(tkn == dpp_token::identifier) {
            items.push_back(std::move(value));
            tkn = read_next_dpp_token(dpp, s2, value, line);
        }
        if (tkn != dpp_token::equals) { std::wcout << line << L": " << L"Expecting =" << std::endl; return 1; }
        tkn = read_next_dpp_token(dpp, s2, value, line);
        if (tkn != dpp_token::identifier) { std::wcout << line << L": " << L"Expecting Shift/Reduce" << std::endl; return 1; }
        if (value == L"Shift") action = ConflictResolution::Shift;
        else if (value == L"Reduce") action = ConflictResolution::Reduce;
        else {
            std::wcout << line << L": The value '" << value << "' is not a valid action. Please use 'Shift' or 'Reduce'" << std::endl;
            return 1;
        }
        tkn = read_next_dpp_token(dpp, s2, value, line);
        if (tkn != dpp_token::semicolon) { std::wcout << line << L": " << L"Expecting ;" << std::endl; return 1; }
        tkn = read_next_dpp_token(dpp, s2, value, line);
        
        // Find the production
        bool found = false;
        for(size_t p = 0; p < productions.size(); p++) {
            if (productions[p].Name == name && productions[p].Items.size() == items.size() - 1) {
                bool ne = false;
                for(size_t i = 0; i < productions[p].Items.size(); i++) {
                    ne |= productions[p].Items[i] != items[i];
                    if (ne) break;
                }
                if (!ne) {
                    found = true;
                    resolutions.emplace(std::pair<const Production*, std::wstring>(&productions[p], items[productions[p].Items.size()]), action);
                }
            }
            if (found) break;
        }
        if (!found) {
            std::wcout << line << L": Could not find the production" << std::endl;
            return 1;
        }
    }
    
    std::wcout << L"Productions" << std::endl;
    for(auto &p : productions) {
        std::wcout << L' ' << p.Name << L":";
        for(auto &i : p.Items) {
            std::wcout << L' ' << i;
        }
        std::wcout << std::endl;
    }
    
    // We'll implement a LR(0) - hopefully this is good enough
    
    std::set<std::wstring> terminals, allsymbols, nonterminals;
    std::unordered_multimap<std::wstring, size_t> nts;
    
    for(size_t i = 0;i<productions.size();i++) {
        nts.emplace(productions[i].Name, i);
        productions[i].Id = i;
        nonterminals.emplace(productions[i].Name);
        allsymbols.emplace(productions[i].Name);
        for(auto &i : productions[i].Items) {
            allsymbols.emplace(i);
        }
    }
    for(auto &s : allsymbols) {
        auto f = nonterminals.find(s);
        if (f == nonterminals.end()) {
            terminals.emplace(s);
        }
    }
    
    std::wcout << L"Non-terminals" << std::endl;
    for(auto &s : nonterminals) {
        std::wcout << L"  " << s << std::endl;
    }
    
    std::wcout << L"Terminals" << std::endl;
    for(auto &s : terminals) {
        std::wcout << L"  " << s << std::endl;
    }
    
    typedef std::pair<size_t, size_t> item_type;
    
    size_t nextstate = 0;
    std::map<std::set<item_type>, size_t> kernels;
    
    struct state {
        size_t stateno;
        std::set<item_type> items;
    };
    std::vector<state> unprocessed_kernels;
    // add the first state
    {
        state s;
        s.stateno = 0;
        // Add the closure on the non-terminal (terminals will not have closures)
        auto f = nts.equal_range(start);
        for(auto i = f.first; i != f.second; i++) {
            s.items.emplace(item_type(i->second, 0));
        }
        unprocessed_kernels.push_back(s);
        kernels.emplace(std::move(s.items), nextstate++);
    }
    
    std::unordered_multimap<size_t, ParserAction> actions;
    
    while(!unprocessed_kernels.empty()) {
        // Find all the closure of all the symbols transitioning (productions) out of this state
        std::unordered_map<std::wstring, std::set<item_type>> transitions; // terminal/non-terminal -> production index + dot index
        auto stateno = unprocessed_kernels.back().stateno;
        for(auto &p : unprocessed_kernels.back().items) {
            auto &pr = productions[p.first];
            if (pr.Items.size() == p.second) {
                // This is a reduce
                ParserAction a;
                a.Reduce = &pr;
                actions.emplace(stateno, a);
            } else {
                // This is a shift, or goto (terminals = shift, non-terminals = goto). The item after the dot takes us one step onwards.
                auto &item = pr.Items[p.second];
                auto s = transitions.emplace(item, std::set<item_type>()).first;
                s->second.emplace(item_type(p.first, p.second + 1));
                // We can also process the closure of the non-terminal (if it is a non-terminal)
                std::vector<std::wstring> unclosed;
                unclosed.push_back(item);
                while(!unclosed.empty()) {
                    auto f = nts.equal_range(unclosed.back());
                    unclosed.pop_back();
                    for(auto i = f.first; i != f.second; i++) {
                        auto &cpr = productions[i->second];
                        // cpr is the closure production. We can also have processed the first item
                        auto ts = transitions.emplace(cpr.Items[0], std::set<item_type>()).first;
                        if (ts->second.emplace(item_type(i->second, 1)).second) {
                            unclosed.push_back(cpr.Items[0]);
                        }
                    }
                }
            }
        }
        unprocessed_kernels.pop_back();
        // Now, for each unique terminal/non-terminal, we find the target state
        for(auto &t : transitions) {
            ParserAction a;
            a.Token = t.first;
            auto f = kernels.find(t.second);
            if (f == kernels.end()) {
                // The state does not exist yet, create the new state and enqueue as an unprocessed
                state s;
                s.stateno = nextstate;
                s.items = t.second;
                unprocessed_kernels.push_back(std::move(s));
                a.ToState = nextstate;
                kernels.emplace(t.second, nextstate++);
            } else {
                // The state does exist - setup a transition
                a.ToState = f->second;
            }
            
            actions.emplace(stateno, a);
        }
    }
    
    std::unordered_map<size_t, std::vector<const Production*>> reduce_reduce_conflicts;
    std::unordered_map<size_t, std::pair<std::vector<const Production*>, std::vector<std::wstring>>> shift_reduce_conflicts;
    std::map<std::wstring, std::map<size_t, size_t>> goto_table;
    
    for(size_t s = 0; s != nextstate; s++) {
        std::wcout << L"State " << s << std::endl;
        std::wcout << L"  Kernel" << std::endl;
        for(auto &sm : kernels) {
            if (sm.second == s) {
                for(auto &p : sm.first) {
                    auto &pr = productions[p.first];
                    std::wcout << L"    " << pr.Name << L':';
                    for(size_t i = 0;i < pr.Items.size();i++) {
                        if (i == p.second) {
                            std::wcout << L" ." << pr.Items[i];
                        } else {
                            std::wcout << L' ' << pr.Items[i];
                        }
                    }
                    if (p.second == productions[p.first].Items.size()) std::wcout << L" .";
                    std::wcout << std::endl;
                }
            }
        }
        
        std::vector<const Production*> reductions;
        std::vector<std::wstring> shifts;
        
        std::wcout << L"  Actions" << std::endl;
        auto f = actions.equal_range(s);
        for(auto i = f.first; i != f.second; i++) {
            if (i->second.Reduce != nullptr) {
                reductions.push_back(i->second.Reduce);
                std::wcout << L"    Reduce " << i->second.Reduce->Name << L':';
                for(auto &item : i->second.Reduce->Items) {
                    std::wcout << L' ' << item;
                }
                std::wcout << std::endl;
            } else {
                std::wcout << L"    " << i->second.Token;
                for(size_t x = i->second.Token.size(); x < 25; x++) std::wcout << L' ';
                if (terminals.find(i->second.Token) == terminals.end()) {
                    // It's a non-terminal
                    std::wcout << L"\t\tGoto " << i->second.ToState << std::endl;
                    auto gt = goto_table.find(i->second.Token);
                    if (gt == goto_table.end()) {
                        std::map<size_t, size_t> mm;
                        mm.emplace(s, i->second.ToState);
                        goto_table.emplace(i->second.Token, std::move(mm));
                    } else {
                        gt->second.emplace(s, i->second.ToState);
                    }
                } else {
                    // It's a terminal
                    shifts.push_back(i->second.Token);
                    std::wcout << L"\t\tShift " << i->second.ToState << std::endl;
                }
            }
        }
        
        // Perform conflict resolution
        if (reductions.size() == 1) {
            // For each shift, we need to
            size_t i = 0;
            while(i < shifts.size()) {
                switch(resolve_conflict(resolutions, reductions[0], shifts[i])) {
                    case ConflictResolution::Reduce:
                        for(auto fi = f.first; fi != f.second; fi++) {
                            if (fi->second.Token == shifts[i]) {
                                fi->second.IsConflictResolutionVictim = true;
                            }
                        }
                        shifts.erase(shifts.begin()+i);
                        break;
                    case ConflictResolution::Shift:
                        shifts.erase(shifts.begin()+i);
                        break;
                    default:
                        i++;
                        break;
                }
            }
        }
        
        // Find the additional conflicts
        if (reductions.size() > 1) {
            reduce_reduce_conflicts.emplace(s, reductions);
        }
        if (!reductions.empty() && !shifts.empty()) {
            shift_reduce_conflicts.emplace(s, std::pair<std::vector<const Production*>, std::vector<std::wstring>>(reductions, shifts));
        }
        
    }
    
    // Detect the conflicts
    int rr = 0, sr = 0;
    for(size_t s = 0; s != nextstate; s++) {
        auto f1 = reduce_reduce_conflicts.find(s);
        auto f2 = shift_reduce_conflicts.find(s);
        if (f1 != reduce_reduce_conflicts.end() || f2 != shift_reduce_conflicts.end()) {
            std::wcout << L"Conflict in state " << s << std::endl;
        }
        if (f1 != reduce_reduce_conflicts.end()) {
            std::wcout << L"  Reduce/reduce conflict" << std::endl;
            rr++;
            for(auto &p : f1->second) {
                std::wcout << L"    " << p->Name << L':';
                for(auto &pi : p->Items) {
                    std::wcout << L' ' << pi;
                }
                std::wcout << std::endl;
            }
        }
        if (f2 != shift_reduce_conflicts.end()) {
            std::wcout << L"  Shift/reduce conflict" << std::endl;
            sr++;
            for(auto &s : f2->second.second) {
                std::wcout << L"    " << s << std::endl;
            }
        }
    }
    
    std::wcout << L"Found " << rr << L" reduce/reduce conflicts" << std::endl;
    std::wcout << L"Found " << sr << L" shift/reduce conflicts" << std::endl;
    
    // Find the final states
    std::set<size_t> final_states;
    for(auto &a : actions) {
        if (a.second.Token == start) {
            final_states.emplace(a.second.ToState);
        }
    }
    
    std::wcout << L"Final states" << std::endl;
    for(auto &fs : final_states) {
        std::wcout << L' ' << (int)fs << std::endl;
    }
    std::wcout << std::endl;
    
    if(rr != 0 || sr != 0) {
        std::wcout << L"Not generating PDA because of conflicts" << std::endl;
        return 1;
    }
    
    // Build a PDA
    std::wofstream stm(output_fn);
    if(!stm.is_open()) {
        std::wcout << L"Failed to open";
        return 1;
    }
    stm << L"#include <vector>" << std::endl;
    auto inc_fn = extract_filename(output_h);
    stm << L"#include \"" << std::wstring(inc_fn.begin(), inc_fn.end()) << "\"" << std::endl;
#ifdef NEW_LEXER
    stm << L"#include \"lexer.ds.lexer.h\"" << std::endl;
    stm << L"#include \"lexer.ds.model.h\"" << std::endl;
#endif
    stm << std::endl;
    stm << L"namespace dc" << std::endl;
    stm << L"{" << std::endl;
    stm << L"    struct lexical_type {" << std::endl;
    for(auto &pt : production_type) {
        stm << L"        struct " << pt.first << L" { };" << std::endl;
    }
    stm << L"    };" << std::endl;
    stm << L"    struct lexical_value {" << std::endl;
    stm << L"        std::wstring desc;" << std::endl;
#ifdef NEW_LEXER
    stm << L"        dc::TokenType tkn_type;" << std::endl;
#else
    stm << L"        TokenType tkn_type;" << std::endl;
#endif
    stm << L"        std::wstring tkn_value;" << std::endl;
    stm << L"        span tkn_span;" << std::endl;
    for(auto &pt : production_type) {
        stm << L"        " << pt.second << L" " << pt.first << L";" << std::endl;
    }
    stm << L"        lexical_value() { }" << std::endl;
#ifdef NEW_LEXER
    stm << L"        lexical_value(span &&spn, const dc::TokenType _tkn_type, const std::wstring &_tkn_value)" << std::endl;
#else
    stm << L"        lexical_value(span &&spn, const TokenType _tkn_type, const std::wstring &_tkn_value)" << std::endl;
#endif
    stm << L"        : desc(text(_tkn_type)), tkn_span(std::move(spn)), tkn_type(_tkn_type), tkn_value(_tkn_value)" << std::endl;
    stm << L"        {}" << std::endl;
#ifdef NEW_LEXER
    stm << L"        lexical_value(span &&spn, const dc::TokenType _tkn_type, std::wstring &&_tkn_value)" << std::endl;
#else
    stm << L"        lexical_value(span &&spn, const TokenType _tkn_type, std::wstring &&_tkn_value)" << std::endl;
#endif
    stm << L"        : desc(text(_tkn_type)), tkn_span(std::move(spn)), tkn_type(_tkn_type), tkn_value(std::move(_tkn_value))" << std::endl;
    stm << L"        {}" << std::endl;
    for(auto &pt : production_type) {
        stm << L"        lexical_value(const lexical_type::" << pt.first << "&, " << pt.second << L"&& value)" << std::endl;
        stm << L"        : desc(L\"" << toupper(pt.first) << L"\"), " << pt.first << L"(std::move(value))" << std::endl;
        stm << L"        {}" << std::endl;
    }
    stm << L"    };" << std::endl;
    stm << std::endl;
    stm << L"    auto parse(std::wistream &stm, const std::shared_ptr<container> &cntr, logger *logger, DocumentAstMutatingVisitor *processor, bool &ok) -> bool" << std::endl;
    stm << L"    {" << std::endl;
    stm << L"        std::vector<size_t> states;" << std::endl;
    stm << L"        std::vector<lexical_value> values;" << std::endl;
#ifndef NEW_LEXER
    stm << L"        dlstate s(stm, cntr);" << std::endl;
    stm << L"        s.states.push_back(0);" << std::endl;
#endif
    stm << L"        states.push_back(0);" << std::endl;
    stm << L"        bool read_token = true;" << std::endl;
#ifdef NEW_LEXER
    stm << L"        dc::lexer lexer(stm);" << std::endl;
    stm << L"        long start_line = 0, start_column = 0, end_line = 0, end_column = 0;" << std::endl;
    stm << L"        std::wstring value;" << std::endl;
    stm << L"        dc::TokenType token = dc::TokenType::Error;" << std::endl;
#endif
    stm << L"        while(true) {" << std::endl;
    stm << L"            if (read_token) {" << std::endl;
    stm << L"                while(true) {" << std::endl;
#ifdef NEW_LEXER
    stm << L"                    if (!lexer.try_read_next_token(start_line, start_column, end_line, end_column, value, token)) {" << std::endl;
    stm << L"                        token = dc::TokenType::EOD;" << std::endl;
    stm << L"                    }" << std::endl;
    stm << L"                    if (token != dc::TokenType::Whitespace && token != dc::TokenType::Comment) break;" << std::endl;
#else
    stm << L"                    if (!read_next_token(s)) {" << std::endl;
    stm << L"                        s.token = TokenType::Eod;" << std::endl;
    stm << L"                    }" << std::endl;
    stm << L"                    if (s.token != TokenType::Whitespace && s.token != TokenType::Comment) break;" << std::endl;
#endif
    stm << L"                }" << std::endl;
    stm << L"            }" << std::endl;
    stm << L"            switch(states.back()) {" << std::endl;
    
    for(size_t s = 0; s < nextstate; s++) {
        stm << L"                case " << (int)s << L":" << std::endl;
        auto f = actions.equal_range(s);
        const Production *reduce = nullptr;
        bool has_shifts = false;
        for(auto i = f.first; i != f.second; i++) {
            if (i->second.Reduce != nullptr) {
                reduce = i->second.Reduce;
            } else {
                if (!i->second.IsConflictResolutionVictim && terminals.find(i->second.Token) != terminals.end()) {
                    has_shifts = true;
                }
            }
        }
        bool is_final_state = final_states.find(s) != final_states.end();
        if (!has_shifts && !is_final_state) {
            // We reduce on this state
            stm << L"                    // Reduce " << reduce->Name << L':';
            for(auto &item : reduce->Items) {
                stm << L' ' << item;
            }
            stm << std::endl;
            stm << L"                    if (true) {" << std::endl;
            //stm << L"                        for(size_t i = 0;i < values.size() - " << (int)reduce->Items.size() << L"; i++) {" << std::endl;
            //stm << L"                            std::wcout << values[i].desc << L' ';" << std::endl;
            //stm << L"                        }" << std::endl;
            //stm << L"                        std::wcout << L\"  ( \";" << std::endl;
            //stm << L"                        for(size_t i = values.size() - " << (int)reduce->Items.size() << L"; i < values.size(); i++) {" << std::endl;
            //stm << L"                            std::wcout << values[i].desc << L' ';" << std::endl;
            //stm << L"                        }" << std::endl;
            //stm << L"                        std::wcout << L\") = " << toupper(reduce->Name) << L"\" << std::endl;" << std::endl;
            for(size_t i = 0; i < reduce->Items.size(); i++) {
                stm << L"                        auto i" << (int)(reduce->Items.size() - i) << L" = std::move(values.back());" << std::endl;
                stm << L"                        values.pop_back();" << std::endl;
                stm << L"                        states.pop_back();" << std::endl;
            }
            stm << L"                        " << reduce->Action << L";" << std::endl;
            // goto
            stm << L"                        read_token = false;" << std::endl;
            auto gt = goto_table.find(reduce->Name);
            if (gt != goto_table.end()) {
                stm << L"                        switch(states.back()) {" << std::endl;
                for(auto &gti : gt->second) {
                    stm << L"                            case " << gti.first << L": states.push_back(" << gti.second << L"); break;" << std::endl;
                }
                stm << L"                            default: assert(false); states.push_back(0); break;" << std::endl;
                stm << L"                        }" << std::endl;
            }
            stm << L"                    }" << std::endl;
            stm << L"                    break;" << std::endl;

        } else {
#ifdef NEW_LEXER
            stm << L"                    switch(token) {" << std::endl;
#else
            stm << L"                    switch(s.token) {" << std::endl;
#endif
            for(auto i = f.first; i != f.second; i++) {
                if (i->second.Reduce == nullptr && i->second.IsConflictResolutionVictim == false && terminals.find(i->second.Token) != terminals.end()) {
#ifdef NEW_LEXER
                    stm << L"                        case dc::" << as_cpp_token(i->second.Token) << L":" << std::endl;
                    stm << L"                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::" << as_cpp_token(i->second.Token) << L", std::move(value));" << std::endl;
#else
                    stm << L"                        case " << as_cpp_token(i->second.Token) << L":" << std::endl;
                    stm << L"                            values.emplace_back(span(std::move(s.begin), std::move(s.end)), " << as_cpp_token(i->second.Token) << L", std::move(s.value));" << std::endl;
#endif
                    stm << L"                            states.push_back(" << i->second.ToState << L");" << std::endl;
                    stm << L"                            read_token = true;" << std::endl;
                    stm << L"                            break;" << std::endl;
                }
            }
            if (is_final_state) {
#ifdef NEW_LEXER
                stm << L"                        case dc::TokenType::EOD:" << std::endl;
#else
                stm << L"                        case TokenType::Eod:" << std::endl;
#endif
                stm << L"                            return true;" << std::endl;
            }
            stm << L"                        default:" << std::endl;
            if (reduce != nullptr) {
                // We reduce on this state
                stm << L"                            // Reduce " << reduce->Name << L':';
                for(auto &item : reduce->Items) {
                    stm << L' ' << item;
                }
                stm << std::endl;
                stm << L"                            if (true) {" << std::endl;
                //stm << L"                                for(size_t i = 0;i < values.size() - " << (int)reduce->Items.size() << L"; i++) {" << std::endl;
                //stm << L"                                    std::wcout << values[i].desc << L' ';" << std::endl;
                //stm << L"                                }" << std::endl;
                //stm << L"                                std::wcout << L\"  ( \";" << std::endl;
                //stm << L"                                for(size_t i = values.size() - " << (int)reduce->Items.size() << L"; i < values.size(); i++) {" << std::endl;
                //stm << L"                                    std::wcout << values[i].desc << L' ';" << std::endl;
                //stm << L"                                }" << std::endl;
                //stm << L"                                std::wcout << L\") = " << toupper(reduce->Name) << L"\" << std::endl;" << std::endl;
                for(size_t i = 0; i < reduce->Items.size(); i++) {
                    stm << L"                                auto i" << (int)(reduce->Items.size() - i) << L" = std::move(values.back());" << std::endl;
                    stm << L"                                values.pop_back();" << std::endl;
                    stm << L"                                states.pop_back();" << std::endl;
                }
                stm << L"                                " << reduce->Action << L";" << std::endl;
                stm << L"                                read_token = false;" << std::endl;
                // goto
                auto gt = goto_table.find(reduce->Name);
                if (gt != goto_table.end()) {
                    stm << L"                                switch(states.back()) {" << std::endl;
                    for(auto &gti : gt->second) {
                        stm << L"                                    case " << gti.first << L": states.push_back(" << gti.second << L"); break;" << std::endl;
                    }
                    stm << L"                                    default: assert(false); states.push_back(0); break;" << std::endl;
                    stm << L"                                }" << std::endl;
                }
                stm << L"                            }" << std::endl;
                stm << L"                            break;" << std::endl;
            } else {
                // There's no reduce on this state - must be an error then.
                stm << L"                            // Error - We did not read an expected token, and we also cannot reduce" << std::endl;
                stm << L"                            if(true) {" << std::endl;
#ifdef NEW_LEXER
                stm << L"                                std::vector<dc::TokenType> validTokens;" << std::endl;
#else
                stm << L"                                std::vector<TokenType> validTokens;" << std::endl;
#endif
                for(auto i = f.first; i != f.second; i++) {
                    if (!i->second.IsConflictResolutionVictim && terminals.find(i->second.Token) != terminals.end()) {
#ifdef NEW_LEXER
                        stm << L"                                validTokens.push_back(dc::" << as_cpp_token(i->second.Token) << L");" << std::endl;
#else
                        stm << L"                                validTokens.push_back(" << as_cpp_token(i->second.Token) << L");" << std::endl;
#endif
                    }
                }
#ifdef NEW_LEXER
                stm << L"                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);" << std::endl;
#else
                stm << L"                                log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);" << std::endl;
#endif
                stm << L"                                return false;" << std::endl;
                stm << L"                            }" << std::endl;
                stm << L"                            break;" << std::endl;
            }
        
            stm << L"                    }" << std::endl;
            stm << L"                    break;" << std::endl;
        }
    }
    stm << L"            }" << std::endl;
    stm << L"        }" << std::endl;
    stm << L"    }" << std::endl;
    stm << L"}" << std::endl;
    
    stm.close();
    
    return 0;
}
