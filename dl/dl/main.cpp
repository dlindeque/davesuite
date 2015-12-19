//
//  main.cpp
//  dl
//
//  Created by David Lindeque on 19/12/2015.
//  Copyright © 2015 David Lindeque. All rights reserved.
//

#include <iostream>

#include "dl.dl.hpp"

using namespace davelexer;

int main(int argc, const char * argv[]) {
    std::shared_ptr<Container> cntr(new FileContainer());
    dlstate s(std::wcin, cntr);
    s.states.push_back(0);
    
    while(read_next_token(s)) {
        std::wcout << text(s.token) << L": " << s.value << std::endl;
    }
    
    return 0;
}
