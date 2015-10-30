// dp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <sstream>
#include "..\dplib\parser_tables.h"

auto analyze(const std::wstring &production) -> daveparser::production {
    int state = 0;
    std::wstring name, item;
    std::vector<std::wstring> items;
    for (auto &ch : production) {
        switch (state) {
        case 0:
            switch ((wchar_t)ch) {
            case L':':
                state = 1;
                break;
            default:
                name += (wchar_t)ch;
                break;
            }
            break;
        case 1:
            switch ((wchar_t)ch) {
            case L' ':
                break;
            default:
                item += (wchar_t)ch;
                state = 2;
                break;
            }
            break;
        case 2:
            switch ((wchar_t)ch) {
            case L' ':
                items.push_back(std::move(item));
                item.clear();
                break;
            default:
                item += (wchar_t)ch;
                break;
            }
            break;
        }
    }
    items.push_back(std::move(item));
    return daveparser::production{ std::move(name), std::move(items) };
}

#include <iostream>
#include <set>
#include <string>
#include <fstream>

inline auto get_state_name(size_t state, const std::unordered_multimap<size_t, const daveparser::production*> &reductions) -> std::wstring {
    std::wstringstream stm;
    stm << L"\"" << (int)state;
    auto f = reductions.equal_range(state);
    for (auto i = f.first; i != f.second; i++) {
        stm << L"a" << i->second->name << "b";
        for (auto &item : i->second->items) {
            stm << L" " << item;
        }
    }
    stm << L"\"";
    return stm.str();
}

int _tmain(int argc, _TCHAR* argv[])
{
    std::vector<daveparser::production> productions;
    productions.push_back(analyze(L"DOC: E eod"));
    productions.push_back(analyze(L"C: character"));
    productions.push_back(analyze(L"C: character C"));
    productions.push_back(analyze(L"D: digit"));
    productions.push_back(analyze(L"D: digit D"));
    productions.push_back(analyze(L"E: literal"));
    productions.push_back(analyze(L"E: pl E pr"));
    productions.push_back(analyze(L"E: E E"));
    productions.push_back(analyze(L"E: E or E"));
    productions.push_back(analyze(L"E: E cl C cr"));
    productions.push_back(analyze(L"E: E cl D cr"));
    productions.push_back(analyze(L"E: E cl D comma D cr"));
    productions.push_back(analyze(L"E: E ocl C cr"));
    productions.push_back(analyze(L"R: hyphen"));
    productions.push_back(analyze(L"R: character"));
    productions.push_back(analyze(L"R: character hyphen character"));
    productions.push_back(analyze(L"RS: R"));
    productions.push_back(analyze(L"RS: R RS"));
    productions.push_back(analyze(L"E: bl RS br"));
    productions.push_back(analyze(L"E: nbl RS br"));
    productions.push_back(analyze(L"E: E asterix"));
    productions.push_back(analyze(L"E: E plus"));
    productions.push_back(analyze(L"E: E question"));
    auto tables = daveparser::parser_tables::generate(productions);

    std::set<std::wstring> non_terminals;
    for (auto &nt : tables.non_terminals) {
        non_terminals.emplace(nt);
    }

    // Generate the graphviz dot notation digraph
    //std::wofstream gv("parser.gv");
    auto &gv = std::wcout;
    gv << L"digraph {" << std::endl;
    for (size_t i = 0; i < tables.state_transitions.size(); i++) {
        for (auto &s : tables.state_transitions[i]) {
            gv << L"  " << get_state_name(i, tables.reductions) << L" -> " << get_state_name(s.second, tables.reductions) << L" [label = \"" << s.first << L"\"";
            if (non_terminals.find(s.first) != non_terminals.end()) {
                gv << L", color=red";
            }
            gv << L"];" << std::endl;
        }
    }
    gv << L"}" << std::endl;

    std::wofstream rep("parser.rep");
    rep << L"Parser" << std::endl;
    rep << L"------" << std::endl << std::endl;

    rep << L"Terminals" << std::endl;
    rep << L"---------" << std::endl;
    for (auto &t : tables.terminals) {
        rep << L"  " << t << std::endl;
    }
    rep << std::endl;

    rep << L"Non-terminals" << std::endl;
    rep << L"---------" << std::endl;
    for (auto &t : tables.non_terminals) {
        rep << L"  " << t << std::endl;
    }
    rep << std::endl;

    for (size_t i = 0; i < tables.state_transitions.size(); i++) {
        rep << L"State " << (int)i << std::endl;
        rep << L"------------" << std::endl;
        rep << L"  Shift" << std::endl;
        rep << L"  -----" << std::endl;
        for (auto &s : tables.state_transitions[i]) {
            if (non_terminals.find(s.first) == non_terminals.end()) {
                rep << L"    " << s.first << L": " << (int)s.second << std::endl;
            }
        }
        rep << L"  ----" << std::endl;
        rep << L"  Goto" << std::endl;
        rep << L"  ----" << std::endl;
        for (auto &s : tables.state_transitions[i]) {
            if (non_terminals.find(s.first) != non_terminals.end()) {
                rep << L"    " << s.first << L": " << (int)s.second << std::endl;
            }
        }
        rep << L"  ------" << std::endl;
        rep << L"  Reduce" << std::endl;
        rep << L"  ------" << std::endl;
        if (i == 0) {
            rep << L"    Accept" << std::endl;
        }
        auto f = tables.reductions.equal_range(i);
        for (auto r = f.first; r != f.second; r++) {
            rep << L"    " << r->second->name << ":";
            for (auto &item : r->second->items) {
                rep << L" " << item;
            }
            rep << std::endl;
        }
        rep << std::endl;
    }

	return 0;
}

