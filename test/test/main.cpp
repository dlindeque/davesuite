//
//  main.cpp
//  test
//
//  Created by David Lindeque on 28/01/2016.
//  Copyright © 2016 David Lindeque. All rights reserved.
//

#include <iostream>
#include <map>
#include <string>

int main(int argc, const char * argv[]) {
    
    std::multimap<std::wstring, int> m;
    m.emplace(L"a", 1);
    m.emplace(L"b", 2);
    m.emplace(L"b", 3);
    m.emplace(L"c", 3);
    
    auto f = m.equal_range(L"b");
    for(auto i = f.first; i != f.second; i++) {
        std::wcout << i->first << L" = " << i->second << std::endl;
    }
    
    return 0;
}
