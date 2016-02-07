//
//  symbolreference.h
//  dc
//
//  Created by David Lindeque on 11/01/2016.
//  Copyright © 2016 David Lindeque. All rights reserved.
//

#pragma once

#include <vector>
#include <iostream>
#include "spanvalue.h"

namespace dc {
    typedef std::vector<spantext> symbolreference;
    
    inline auto operator <<(std::wostream &os, const symbolreference &v) -> std::wostream& {
        if (!v.empty()) {
            os << v[0];
            for(size_t i = 1; i < v.size(); i++) {
                os << L'.' << v[i];
            }
        }
        return os;
    }

    inline auto spn_of(const symbolreference &s) -> span
    {
        if (s.empty()) {
            return span();
        }
        else {
            return span(s[0].spn().begin, s.back().spn().end);
        }
    }
            
    struct is_same_symbol {
        inline auto operator()(const symbolreference &sym1, const symbolreference &ns2, const std::wstring &name2) -> bool {
            if (sym1.size() != ns2.size() + 1) return false;
            for(size_t i = 0; i < ns2.size(); i++) {
                if (sym1[i].value() != ns2[i].value()) return false;
            }
            return sym1[ns2.size()].value() == name2;
        }

        inline auto operator()(const symbolreference &sym1, const symbolreference &ns2, const spantext &name2) -> bool {
            return (*this)(sym1, ns2, name2.value());
        }   
    };
}

