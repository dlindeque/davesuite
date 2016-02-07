//
//  main.cpp
//  dl
//
//  Created by David Lindeque on 19/12/2015.
//  Copyright © 2015 David Lindeque. All rights reserved.
//

#include <iostream>
#include <fstream>

#include "dl.dl.hpp"
#include "dl.dp.hpp"

#include "astformat.hpp"

using namespace davelexer;

class filecontainer : public davecommon::container {
private:
    std::wstring _filename;
public:
    filecontainer(const std::wstring filename)
    : _filename(filename)
    {}
    
    virtual auto name() const->std::wstring { return _filename; }
};

class console_logger : public davecommon::logger {
protected:
    virtual auto write(davecommon::severity s, const std::shared_ptr<davecommon::container> &cntr, const davecommon::span &spn, const std::wstring &msg) -> void {
        std::wcout << cntr->name() << std::endl << L"  " << spn.begin.line << L":" << spn.begin.column << L'-' << spn.end.line << L':' << spn.end  .column << L"  " << msg;
    }
};

int main(int argc, const char * argv[]) {
    std::shared_ptr<davecommon::container> cntr(new filecontainer(L"/Users/davidlindeque/davesuite/dl/dl/dl.dl"));
    std::wifstream stm("/Users/davidlindeque/davesuite/dl/dl/dl.d");
    
    console_logger logger;
    bool ok = true;
    auto ast = parse(stm, cntr, &logger, ok);
    DocumentAstFormatter fmt(std::wcout);
    for(auto &di : ast) {
        std::wcout << "// Document item" << std::endl;
        di->accept(&fmt);
    }
    return 0;
}
