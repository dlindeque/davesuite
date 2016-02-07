//
//  dl.dp.hpp
//  dl
//
//  Created by David Lindeque on 05/01/2016.
//  Copyright © 2016 David Lindeque. All rights reserved.
//

#ifndef dl_dp_h
#define dl_dp_h

#include <vector>
#include "dl.dl.hpp"
#include "../../common/logger.h"
#include "../../common/container.h"
#include "log.h"
#include <assert.h>

namespace davelexer {
    template <typename T> inline auto as_vector(T &&item) -> std::vector<T> {
        std::vector<T> v;
        v.push_back(std::move(item));
        return std::move(v);
    }
    
    template< typename T> inline auto append_vector(std::vector<T> &&v, T &&item) -> std::vector<T> {
        v.push_back(std::move(item));
        return std::move(v);
    }
    
    inline auto as_charclass(const std::wstring &cls) -> CharClass {
        if (cls == L"a") return CharClass::Alpha;
        else if (cls == L"d") return CharClass::Digit;
        else if (cls == L"A") return CharClass::AlphaNum;
        else if (cls == L"s") return CharClass::Whitespace;
        else if (cls == L".") return CharClass::AnyChar;
        else return CharClass::AnyChar;
    }
    
    auto parse(std::wistream &stm, const std::shared_ptr<davecommon::container> &cntr, davecommon::logger *logger, bool &ok) ->  std::vector<std::shared_ptr<DocumentAst>>;
}

#endif /* dl_dp_h */
