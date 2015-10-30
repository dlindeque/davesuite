// dl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <sstream>
#include <iostream>

#include "..\dllib\re_parser.h"

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
    std::wstringstream stm(L"(ab)|(cd){>jjj}");
    std::unique_ptr<davelexer::re_ast> ast;
    text_container tc;
    console_logger cl;
    if (!davelexer::re_try_parse(&tc, stm, &cl, ast)) {
        std::wcout << "Failure during re parse" << std::endl;
    }
    else {
        std::wcout << "AST:" << std::endl << ast << std::endl;
    }

	return 0;
}

