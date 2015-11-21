// dl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <sstream>
#include <iostream>

#include "..\dllib\nfa.h"
#include "..\dllib\dfa.h"

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

int _tmain(int argc, _TCHAR* argv[])
{
    text_container tc;
    console_logger cl;

    bool ok = true;

    davelexer::nfa n;
    auto builder = n.get_builder(&tc, &cl);
    auto default_section = builder.get_section_builder(L"default");
    //// for + foreach + etc
    //ok &= default_section.try_add_token(L"if", 1, L"if", span());
    //ok &= default_section.try_add_token(L"for", 2, L"for", span());
    //ok &= default_section.try_add_token(L"foreach", 3, L"foreach", span());
    //ok &= default_section.try_add_goto(L"comment", 4, L"/\\*", span(), L"comment");
    //
    //auto comment = builder.get_section_builder(L"comment");
    //ok &= comment.try_add_token(L"comment", 4, L".+", span());
    //ok &= comment.try_add_return(L"comment", 4, L"\\*/+", span());
    
    // t1 + t2
    ok &= default_section.try_add_token(L"t1", 1, L"abc", span());
    ok &= default_section.try_add_token(L"t2", 2, L"def", span());
    ok &= default_section.try_add_token(L"err", 3, L".", span());

    //nfa n;
    //nfa::test(n);
    //std::wcout << n;

    if (!ok) {
        std::wcout << "FAILED";
        return 1;
    }
    else {
        bool ok;
        auto dfa = dfa::try_compile(std::move(n), std::wcout, ok, [](size_t y1, size_t y2) { return y1 < y2 ? y1 : y2; });
        if (!ok) {
            std::wcout << "FAILED";
            return 1;
        }
        std::wcout << dfa;
    }

    //auto n = nfa::test();
    //auto o = n.remove_epsilon_actions();
    //std::wcout << o;

    //std::wstringstream stm(L"(ab)|(cd){>jjj}");
    //std::unique_ptr<davelexer::re_ast> ast;
    //
    //if (!davelexer::re_try_parse(&tc, stm, &cl, ast)) {
    //    std::wcout << "Failure during re parse" << std::endl;
    //}
    //else {
    //    std::wcout << "AST:" << std::endl << ast << std::endl;
    //}

	return 0;
}

