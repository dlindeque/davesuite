// dl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <locale>
#include <codecvt>

#include "..\dllib\nfa_builder.h"
#include "..\dllib\dfa.h"
#include "..\dllib\model.h"
#include "..\dllib\graphviz.h"
#include "..\dllib\cpp_formatter.h"
#include "..\dllib\linker.h"

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

inline auto spn(long line)->span {
    span s;
    s.begin.line = line;
    return s;
}

auto build_dl_lexer_ast(const container *cntr, logger *logger, bool &ok) -> std::vector<std::unique_ptr<lex_ast>> {
    std::vector<std::unique_ptr<lex_ast>> declarations;

    declarations.emplace_back(new lex_ast_pattern(cntr, spn(1), L"identifier", compile_re_ast(cntr, logger, L"[a-zA-Z_][a-zA-Z_0-9]*", ok)));
    declarations.emplace_back(new lex_ast_pattern(cntr, spn(1), L"string", compile_re_ast(cntr, logger, L"\"([^\"]||(\\\\.)*\"", ok)));
    declarations.emplace_back(new lex_ast_pattern(cntr, spn(1), L"documentation", compile_re_ast(cntr, logger, L"///(\\n)|([^/][^\\n]*\\n)", ok)));
    declarations.emplace_back(new lex_ast_pattern(cntr, spn(1), L"integer", compile_re_ast(cntr, logger, L"(+|-)?0|([1-9]\\d+)", ok)));
    declarations.emplace_back(new lex_ast_pattern(cntr, spn(1), L"singleLineComment", compile_re_ast(cntr, logger, L"//[^\\n]*\\n", ok)));
    declarations.emplace_back(new lex_ast_pattern(cntr, spn(1), L"multiLineCommentStart", compile_re_ast(cntr, logger, L"/\\*", ok)));
    declarations.emplace_back(new lex_ast_pattern(cntr, spn(1), L"multiLineCommentContent", compile_re_ast(cntr, logger, L"([^\\*]+)|(\\*[^/])", ok)));
    declarations.emplace_back(new lex_ast_pattern(cntr, spn(1), L"multiLineCommentReturn", compile_re_ast(cntr, logger, L"\\*/", ok)));

    std::vector<std::unique_ptr<lex_ast_section_item>> items;
    items.emplace_back(new lex_ast_return(spn(1), L"comment", span(), compile_re_ast(cntr, logger, L"{multiLineCommentReturn}", ok)));
    items.emplace_back(new lex_ast_token(spn(2), L"comment", span(), compile_re_ast(cntr, logger, L"{multiLineCommentContent}", ok)));
    declarations.emplace_back(new lex_ast_section(cntr, spn(100), L"multiLineComment", std::move(items)));

    items.clear();
    items.emplace_back(new lex_ast_token(spn(4), L"whitespace", span(), compile_re_ast(cntr, logger, L"\\s+", ok)));
    items.emplace_back(new lex_ast_token(spn(4), L"documentation", span(), compile_re_ast(cntr, logger, L"{documentation}", ok)));
    items.emplace_back(new lex_ast_token(spn(5), L"comment", span(), compile_re_ast(cntr, logger, L"{singleLineComment}", ok)));
    items.emplace_back(new lex_ast_start(spn(6), L"comment", span(), compile_re_ast(cntr, logger, L"{multiLineCommentStart}", ok), L"comment", span()));
    items.emplace_back(new lex_ast_token(spn(7), L"pattern", span(), compile_re_ast(cntr, logger, L"pattern", ok)));
    items.emplace_back(new lex_ast_token(spn(9), L"equal", span(), compile_re_ast(cntr, logger, L"=", ok)));
    items.emplace_back(new lex_ast_start(spn(10), L"re-start", span(), compile_re_ast(cntr, logger, L"'", ok), L"re", span()));
    items.emplace_back(new lex_ast_token(spn(11), L"semi-colon", span(), compile_re_ast(cntr, logger, L";", ok)));
    items.emplace_back(new lex_ast_token(spn(12), L"shared", span(), compile_re_ast(cntr, logger, L"shared", ok)));
    items.emplace_back(new lex_ast_token(spn(13), L"section", span(), compile_re_ast(cntr, logger, L"section", ok)));
    items.emplace_back(new lex_ast_token(spn(14), L"open-curly", span(), compile_re_ast(cntr, logger, L"\\{", ok)));
    items.emplace_back(new lex_ast_token(spn(15), L"close-curly", span(), compile_re_ast(cntr, logger, L"\\}", ok)));
    items.emplace_back(new lex_ast_token(spn(16), L"include", span(), compile_re_ast(cntr, logger, L"include", ok)));
    items.emplace_back(new lex_ast_token(spn(17), L"token", span(), compile_re_ast(cntr, logger, L"token", ok)));
    items.emplace_back(new lex_ast_token(spn(18), L"goto", span(), compile_re_ast(cntr, logger, L"goto", ok)));
    items.emplace_back(new lex_ast_token(spn(19), L"return", span(), compile_re_ast(cntr, logger, L"return", ok)));
    items.emplace_back(new lex_ast_token(spn(21), L"import", span(), compile_re_ast(cntr, logger, L"import", ok)));
    items.emplace_back(new lex_ast_token(spn(22), L"string", span(), compile_re_ast(cntr, logger, L"{string}", ok)));
    items.emplace_back(new lex_ast_token(spn(23), L"identifier", span(), compile_re_ast(cntr, logger, L"@?{identifier}", ok)));
    declarations.emplace_back(new lex_ast_section(cntr, spn(23), false, L"default", std::move(items)));

    items.clear();
    items.emplace_back(new lex_ast_return(spn(24), L"comment-return", span(), compile_re_ast(cntr, logger, L"\\*/", ok)));
    items.emplace_back(new lex_ast_token(spn(25), L"comment-content", span(), compile_re_ast(cntr, logger, L"([^\\*]+)|(\\*[^/])", ok)));
    declarations.emplace_back(new lex_ast_section(cntr, spn(26), false, L"comment", std::move(items)));

    items.clear();
    items.emplace_back(new lex_ast_return(spn(27), L"re-return", span(), compile_re_ast(cntr, logger, L"'", ok)));
    items.emplace_back(new lex_ast_token(spn(28), L"re-asterisk", span(), compile_re_ast(cntr, logger, L"\\*", ok)));
    items.emplace_back(new lex_ast_token(spn(29), L"re-plus", span(), compile_re_ast(cntr, logger, L"\\+", ok)));
    items.emplace_back(new lex_ast_token(spn(30), L"re-question", span(), compile_re_ast(cntr, logger, L"\\?", ok)));
    items.emplace_back(new lex_ast_token(spn(31), L"re-open-parenthesis", span(), compile_re_ast(cntr, logger, L"\\(", ok)));
    items.emplace_back(new lex_ast_token(spn(32), L"re-close-parenthesis", span(), compile_re_ast(cntr, logger, L"\\)", ok)));
    items.emplace_back(new lex_ast_token(spn(33), L"re-pipe", span(), compile_re_ast(cntr, logger, L"\\|", ok)));
    items.emplace_back(new lex_ast_token(spn(34), L"re-exclude-set", span(), compile_re_ast(cntr, logger, L"\\[\\^", ok)));
    items.emplace_back(new lex_ast_token(spn(35), L"re-open-bracket", span(), compile_re_ast(cntr, logger, L"\\[", ok)));
    items.emplace_back(new lex_ast_token(spn(36), L"re-close_bracket", span(), compile_re_ast(cntr, logger, L"\\]", ok)));
    items.emplace_back(new lex_ast_token(spn(37), L"re-hyphen", span(), compile_re_ast(cntr, logger, L"-", ok)));
    items.emplace_back(new lex_ast_token(spn(38), L"re-dot", span(), compile_re_ast(cntr, logger, L"\\.", ok)));
    items.emplace_back(new lex_ast_token(spn(39), L"re-reference", span(), compile_re_ast(cntr, logger, L"\\{{identifier}\\}", ok)));
    items.emplace_back(new lex_ast_token(spn(40), L"re-open-curly", span(), compile_re_ast(cntr, logger, L"\\{", ok)));
    items.emplace_back(new lex_ast_token(spn(41), L"re-close-curly", span(), compile_re_ast(cntr, logger, L"\\}", ok)));
    items.emplace_back(new lex_ast_token(spn(42), L"re-escaped", span(), compile_re_ast(cntr, logger, L"\\\\.", ok)));
    items.emplace_back(new lex_ast_token(spn(43), L"re-char", span(), compile_re_ast(cntr, logger, L".", ok)));
    declarations.emplace_back(new lex_ast_section(cntr, spn(44), false, L"re", std::move(items)));

    return declarations;
}

auto html_encode(const std::wstring &value, std::wostream &stm) -> void {
    for (auto &c : value) {
        switch (c) {
        case L'\n': stm << L"<br />"; break;
        case L' ': stm << L"&nbsp;"; break;
        default: stm << c; break;
        }
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    text_container tc;
    console_logger cl;

    bool ok = true;
    
    auto declarations = build_dl_lexer_ast(&tc, &cl, ok);
    if (!ok) {
        std::wcout << "ERROR" << std::endl;
        return 1;
    }

    time_t t1;
    std::time(&t1);

    linker linker(ok);
    for (auto &d : declarations) {
        d->accept(&linker);
    }

    if (!ok) {
        std::wcout << "ERROR" << std::endl;
        return 1;
    }

    section_dependency_walker walker(&cl, ok);
    for (auto &d : declarations) {
        d->accept(&walker);
    }

    if (!ok) {
        std::wcout << "ERROR" << std::endl;
        return 1;
    }

    nfa_builder g(ok, &cl, walker);

    for (auto &d : declarations) {
        d->accept(&g);
    }

    time_t t2;
    std::time(&t2);

    if (!ok) {
        std::wcout << "ERROR" << std::endl;
        return 1;
    }

    auto dfa = dfa::try_compile(std::move(g));
    time_t t3;
    std::time(&t3);
    std::wcout << L"t2 - t1 = " << t2 - t1 << std::endl;
    std::wcout << L"t3 - t2 = " << t3 - t2 << std::endl;
    //graphviz::write_graph(std::wcout, g.transitions(), g.state_yields());
    //graphviz::write_graph(std::wcout, dfa.tmap(), dfa.state_yields());

    {
        std::wofstream stm("c:\\davecode\\davesuite\\dl\\lexertest.cpp");
        stm << L"#include \"stdafx.h\"" << std::endl;
        stm << L"#include \"lexertest.h\"" << std::endl;
        stm << L"#include <assert.h>" << std::endl;
        stm << std::endl;
        stm << L"namespace testns" << std::endl;
        stm << L"{" << std::endl;
        stm << L"    auto testcls::operator()(std::vector<size_t> &statestack, std::wistream &stm, testcls_token &token, std::wstring &value, bool &is_eod, davecommon::span &spn) -> bool {" << std::endl;
        cpp_formatter::write_lexer_body(L"testcls_token", dfa, stm);
        stm << L"    }" << std::endl;
        stm << L"}" << std::endl;
    }

    {
        std::wofstream stm("c:\\davecode\\davesuite\\dl\\lexertest.h");
        stm << L"#pragma once" << std::endl;
        stm << std::endl;
        stm << L"#include <vector>" << std::endl;
        stm << L"#include <memory>" << std::endl;
        stm << L"#include <string>" << std::endl;
        stm << L"#include \"..\\common\\span.h\"" << std::endl;
        stm << std::endl;
        stm << L"namespace testns" << std::endl;
        stm << L"{" << std::endl;
        stm << L"    enum class testcls_token {" << std::endl;
        std::set<std::wstring> tokens;
        for (auto &sy : dfa.state_yields()) {
            tokens.emplace(*sy.second.token);
        }
        for (auto &tk : tokens) {
            stm << L"        " << cpp_formatter::cpp_identifier(tk) << L"," << std::endl;
        }
        stm << L"    };" << std::endl;
        stm << L"    inline auto test_cls_token_name(testcls_token tkn) -> std::wstring {" << std::endl;
        stm << L"        switch(tkn) {" << std::endl;
        for (auto &tk : tokens) {
            stm << L"        case testcls_token::" << cpp_formatter::cpp_identifier(tk) << L": return L\"" << tk << "\";" << std::endl;
        }
        stm << L"        default: return L\"unknown\";" << std::endl;
        stm << L"        }" << std::endl;
        stm << L"    }" << std::endl;
        stm << std::endl;
        stm << L"    class testcls {" << std::endl;
        stm << L"    public:" << std::endl;
        stm << L"        auto operator()(std::vector<size_t> &statestack, std::wistream &stm, testcls_token &token, std::wstring &value, bool &is_eod, davecommon::span &spn) -> bool;" << std::endl;
        stm << L"    };" << std::endl;
        stm << L"}" << std::endl;
    }

    ////lexer l(std::move(dfa));
    //testns::testcls l;
    //std::vector<size_t> statestack;
    //statestack.push_back(0);
    ////std::wstringstream stm;
    ////stm << "0return\n3.4 /* hello world */abc";
    ////stm << "0/* hello 0 /* world *//****/ 2.3";
    ////stm.seekg(0);
    //std::wifstream stm(L"c:\\test\\test.dl", std::ios::in);
    //stm.imbue(std::locale(stm.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::consume_header>));
    ////wchar_t ch;
    ////if (stm.get(ch)) {
    ////    if (ch != 255) {
    ////        stm.unget();
    ////    }
    ////    else if (stm.get(ch)) {
    ////        if (ch != 254) {
    ////            stm.unget();
    ////            stm.unget();
    ////        }
    ////    }
    ////}
    //testns::testcls_token token;
    //std::wstring value;
    //bool is_eod;
    //span spn;
    //spn.end.line = 1;
    //spn.end.column = 1;
    //std::wofstream dest(L"c:\\test\\dl.html");
    //dest << L"<html>" << std::endl << L"<body>" << std::endl;
    //while (l(statestack, stm, token, value, is_eod, spn)) {
    //    dest << L"<span title=\"";
    //    std::wstring style;
    //    switch (token) {
    //    case testns::testcls_token::identifier: dest << L"identifier"; style = L"color:gray"; break;
    //    case testns::testcls_token::whitespace: dest << L"whitespace"; style = L""; break;
    //    case testns::testcls_token::return_: dest << L"return"; style = L"color:blue"; break;
    //    case testns::testcls_token::comment_start: dest << L"comment_start"; style = L"color:green"; break;
    //    case testns::testcls_token::comment_content: dest << L"comment_content"; style = L"color:green"; break;
    //    case testns::testcls_token::comment_return: dest << L"comment_return"; style = L"color:green"; break;
    //    case testns::testcls_token::line_comment: dest << L"line_comment"; style = L"color:green"; break;
    //    case testns::testcls_token::equal: dest << L"equal"; style = L"color:black"; break;
    //    case testns::testcls_token::re_start: dest << L"re_start"; style = L"color:cyan"; break;
    //    case testns::testcls_token::re_return: dest << L"re_return"; style = L"color:cyan"; break;
    //    case testns::testcls_token::semi_colon: dest << L"semi_colon"; style = L"color:black"; break;
    //    case testns::testcls_token::open_curly: dest << L"open_curly"; style = L"color:black"; break;
    //    case testns::testcls_token::close_curly: dest << L"close_curly"; style = L"color:black"; break;
    //    case testns::testcls_token::string: dest << L"string"; style = L"color:purple"; break;
    //    case testns::testcls_token::re_exclude_set: dest << L"re_exclude_set"; style = L"color:black"; break;
    //    case testns::testcls_token::re_reference: dest << L"re_reference"; style = L"color:orange"; break;
    //    case testns::testcls_token::re_char: dest << L"re_char"; style = L"color:cyan"; break;
    //    case testns::testcls_token::token: dest << L"token"; style = L"color:blue"; break;
    //    case testns::testcls_token::shared: dest << L"shared"; style = L"color:blue"; break;
    //    case testns::testcls_token::section: dest << L"section"; style = L"color:blue"; break;
    //    case testns::testcls_token::include: dest << L"include"; style = L"color:blue"; break;
    //    case testns::testcls_token::import: dest << L"import"; style = L"color:blue"; break;
    //    case testns::testcls_token::goto_: dest << L"goto"; style = L"color:blue"; break;
    //    case testns::testcls_token::re_open_parenthesis: dest << L"re_open_parenthesis"; style = L"color:black"; break;
    //    case testns::testcls_token::re_close_parenthesis: dest << L"re_close_parenthesis"; style = L"color:blue"; break;
    //    case testns::testcls_token::re_asterisk: dest << L"re_asterisk"; style = L"color:black"; break;
    //    case testns::testcls_token::re_plus: dest << L"re_plus"; style = L"color:black"; break;
    //    case testns::testcls_token::re_hyphen: dest << L"re_hyphen"; style = L"color:black"; break;
    //    case testns::testcls_token::re_dot: dest << L"re_dot"; style = L"color:black"; break;
    //    case testns::testcls_token::re_question: dest << L"re_question"; style = L"color:black"; break;
    //    case testns::testcls_token::re_open_bracket: dest << L"re_open_bracket"; style = L"color:black"; break;
    //    case testns::testcls_token::re_close_bracket: dest << L"re_close_bracket"; style = L"color:black"; break;
    //    case testns::testcls_token::re_open_curly: dest << L"re_open_curly"; style = L"color:black"; break;
    //    case testns::testcls_token::re_pipe: dest << L"re_pipe"; style = L"color:black"; break;
    //    case testns::testcls_token::re_close_curly: dest << L"re_close_curly"; style = L"color:black"; break;
    //    case testns::testcls_token::pattern: dest << L"pattern"; style = L"color:black"; break;
    //    case testns::testcls_token::re_escaped: dest << L"re_escaped"; style = L"color:green"; break;
    //    default:
    //        style = L"color:red";
    //        dest << "???";
    //        break;
    //    }
    //    dest << L" " << spn.begin.line << L':' << spn.begin.column << L'-' << spn.end.line << L':' << spn.end.column;
    //    dest << L"\" style=\"" << style << L"\">";
    //    html_encode(value, dest);
    //    dest << L"</span>" << std::endl;
    //}
    //if (!is_eod) {
    //    std::wcout << "Unexpected characters" << std::endl;
    //}

	return 0;
}

