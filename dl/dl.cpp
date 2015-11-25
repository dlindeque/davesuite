// dl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <sstream>
#include <iostream>
#include <fstream>

#include "..\dllib\nfa_builder.h"
#include "..\dllib\dfa.h"
#include "..\dllib\model.h"
#include "..\dllib\graphviz.h"
#include "..\dllib\lexer.h"
#include "..\dllib\cpp_formatter.h"

#include "lexertest.h"

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

auto compile_re_ast(const container *cntr, logger *logger, const std::wstring &re, bool &ok)->std::unique_ptr < re_ast > {
    std::wstringstream src;
    src << re;
    src.seekg(0);
    auto ast = re_try_parse(cntr, src, logger);
    ok &= (ast != nullptr);
    return ast;
}

int _tmain(int argc, _TCHAR* argv[])
{
    text_container tc;
    console_logger cl;

    bool ok = true;
    
    auto re1 = compile_re_ast(&tc, &cl, L"[a-zA-Z_][a-zA-Z_0-9]*", ok);
    auto re2 = compile_re_ast(&tc, &cl, L"(0|([1-9]\\d*)(\\.\\d+)?)", ok);
    auto re3 = compile_re_ast(&tc, &cl, L"return", ok);
    auto re4 = compile_re_ast(&tc, &cl, L"\\s+", ok);
    if (ok) {
        nfa_builder g(&cl);

        std::vector<std::unique_ptr<lex_ast_section_item>> items;
        items.emplace_back(new lex_ast_token(span(), L"identifier", span(), std::move(re1)));
        items.emplace_back(new lex_ast_token(span(), L"number", span(), std::move(re2)));
        items.emplace_back(new lex_ast_token(span(), L"return", span(), std::move(re3)));
        items.emplace_back(new lex_ast_token(span(), L"whitespace", span(), std::move(re4)));
        lex_ast_section d(&tc, span(), false, L"default", std::move(items));
        d.accept(&g);
        if (!g._ok) {
            std::wcout << "ERROR";
        }
        else {
            auto dfa = dfa::try_compile(std::move(g), [](state_yield s1, state_yield s2) { return s1; });
            //graphviz::write_graph(std::wcout, g.transitions(), g.state_yields());
            //graphviz::write_graph(std::wcout, dfa.tmap(), dfa.state_yields());

            //std::unordered_map<std::wstring, std::wstring> settings;
            //settings.emplace(L"namespace", L"testns");
            //settings.emplace(L"class", L"testcls");
            //settings.emplace(L"headerfn", L"lexertest.h");
            //settings.emplace(L"tokenenum", L"testcls_token");
            //cpp_formatter()(settings, dfa, std::wofstream("C:\\davecode\\davesuite\\dl\\lexertest.cpp"));


            //lexer l(std::move(dfa));
            testns::testcls l;
            std::vector<size_t> statestack;
            statestack.push_back(0);
            std::wstringstream stm;
            stm << "0return\n3.4 abc";
            stm.seekg(0);
            testns::testcls_token token;
            std::wstring value;
            bool is_eod;
            span spn;
            spn.end.line = 1;
            spn.end.column = 1;
            while (l(statestack, stm, token, value, is_eod, spn)) {
                std::wcout << spn.begin.line << L':' << spn.begin.column << L'-' << spn.end.line << L':' << spn.end.column << L' ';
                switch (token) {
                case testns::testcls_token::identifier:
                    std::wcout << "identifier";
                    break;
                case testns::testcls_token::number:
                    std::wcout << "number";
                    break;
                case testns::testcls_token::return_:
                    std::wcout << "return";
                    break;
                case testns::testcls_token::whitespace:
                    std::wcout << "whitespace";
                    break;
                default:
                    std::wcout << "???";
                    break;
                }
                std::wcout << L" (" << value << L")" << std::endl;
            }
            if (!is_eod) {
                std::wcout << "Unexpected characters" << std::endl;
            }
        }
    }

	return 0;
}

