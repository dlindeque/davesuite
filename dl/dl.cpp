// dl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <sstream>
#include <iostream>

#include "..\dllib\nfa.h"
#include "..\dllib\dfa.h"
#include "..\dllib\model.h"
#include "..\dllib\graphviz.h"

class text_container : public davecommon::container {
public:
    virtual auto name() const->std::wstring override { return L"text"; }
};

class console_logger : public davecommon::logger {
protected:
    virtual auto write(severity severity, const container* container, const span &span, const std::wstring &msg) -> void override {
        switch (severity) {
        case davecommon::severity::info:
            std::wcout << L"INFO: ";
            break;
        case davecommon::severity::warning:
            std::wcout << L"WARNING: ";
            break;
        case davecommon::severity::error:
            std::wcout << L"ERROR: ";
            break;
        default:
            std::wcout << L"???: ";
            break;
        }
        std::wcout << span.begin.line << L':' << span.begin.column << L'-' << span.end.line << L':' << span.end.column << L"  " << msg << std::endl;
    }
};

auto compile_re_ast(const container *cntr, logger *logger, const std::wstring &re)->std::unique_ptr < re_ast > {
    std::wstringstream src;
    src << re;
    src.seekg(0);
    return re_try_parse(cntr, src, logger);
}

int _tmain(int argc, _TCHAR* argv[])
{
    text_container tc;
    console_logger cl;

    bool ok = true;
    
    auto re1 = compile_re_ast(&tc, &cl, L"a+");
    if (re1 != nullptr) {
        lex_ast_nfa_generator g(&cl);

        std::vector<std::unique_ptr<lex_ast_section_item>> items;
        items.push_back(std::unique_ptr<lex_ast_section_item>(new lex_ast_token(span(), L"t1", span(), std::move(re1))));
        lex_ast_section d(&tc, span(), false, L"default", std::move(items));
        d.accept(&g);
        if (!g._ok) {
            std::wcout << "ERROR";
        }
        else {
            auto yd = g.compile_yield_details();
            graphviz::write_graph(std::wcout, yd, g._transitions);
        }
    }

	return 0;
}

