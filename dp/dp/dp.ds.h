//
//  dp.ds.hpp
//  dp
//
//  Created by David Lindeque on 19/12/2015.
//  Copyright © 2015 David Lindeque. All rights reserved.
//

#ifndef dp_ds_hpp
#define dp_ds_hpp

#include <stdio.h>

#include <string>
#include <vector>

namespace daveparser
{
    class Production {
    public:
        size_t Id;
        size_t Dot;
        std::wstring Name;
        std::vector<std::wstring> Items;
        std::wstring Action;
    };
    
    class ParserAction {
    public:
        std::wstring Token;
        size_t ToState;
        const Production *Reduce;
        bool IsConflictResolutionVictim;
    };
    
    enum class ConflictResolution {
        Shift,
        Reduce,
        DontKnow
    };
}


#endif /* dp_ds_hpp */
