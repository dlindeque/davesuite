//
//  dl.dp.hpp
//  dl
//
//  Created by David Lindeque on 05/01/2016.
//  Copyright © 2016 David Lindeque. All rights reserved.
//

#pragma once

#include <vector>
#include <algorithm>
#include "dc.dl.h"
#include "logger.h"
#include "container.h"
#include "log.h"
#include <assert.h>

namespace dc {
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
        else if (cls == L"e") return CharClass::EndOfData;
        else return CharClass::AnyChar;
    }
    
    typedef std::function<bool (std::shared_ptr<DocumentAst> &&)> ast_processor;
    
    auto parse(std::wistream &stm, const std::shared_ptr<container> &cntr, logger *logger, DocumentAstVisitor *processor, bool &ok) ->  bool;
}

