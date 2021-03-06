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
        if (cls == L"\\a") return CharClass::Alpha;
        else if (cls == L"\\d") return CharClass::Digit;
        else if (cls == L"\\A") return CharClass::AlphaNum;
        else if (cls == L"\\s") return CharClass::Whitespace;
        else if (cls == L".") return CharClass::AnyChar;
        else if (cls == L"\\e") return CharClass::EndOfData;
        else return CharClass::AnyChar;
    }
    
    inline auto as_char(const std::wstring &ch) -> wchar_t {
        assert(ch.size() == 1 || ch.size() == 2);
        if (ch.size() == 2) {
            assert(ch[0] == L'\\');
            switch(ch[1]) {
            case L'n': return L'\n';
            case L'r': return L'\r';
            case L'v': return L'\v';
            case L't': return L'\t';
            case L'f': return L'\f';
            case L'b': return L'\b';
            default: return ch[1];
            }
            return ch[1];
        } else {
            return ch[0];
        }
    }
    
    inline auto get_system_symbolreference(std::wstring &&name) -> symbolreference {
        symbolreference sr;
        sr.push_back(spantext(span(), L"System"));
        sr.push_back(spantext(span(), std::move(name)));
        return std::move(sr);
    }
    
    inline auto get_str(const std::wstring &str) -> std::wstring {
        // str = "\"blablabla\r\n\"" (size = 13)
        //        0 1234567890 1 2 /0
        const wchar_t *s = str.c_str() + 1;
        const wchar_t *e = str.c_str() + str.size() - 1;
        std::wstring res;
        int state = 0;
        while(s != e) {
            switch(state) {
            case 0:
                switch(*s) {
                case L'\\':
                    state = 1;
                    break;
                default:
                    res += *s;
                    break;
                }
                break;
            case 1:
                switch(*s) {
                case L'n':
                    res += L'\n';
                    break;
                case L'r':
                    res += L'\r';
                    break;
                case L'v':
                    res += L'\v';
                    break;
                case L'f':
                    res += L'\f';
                    break;
                case L't':
                    res += L'\t';
                    break;
                default:
                    res += *s;
                    break;
                }
                state = 0;
                break;
            default:
                assert(false);
                break;
            }
            s++;
        }
        return res;
    }
    
    auto parse(std::wistream &stm, const std::shared_ptr<container> &cntr, logger *logger, DocumentAstMutatingVisitor *processor, bool &ok) ->  bool;
}

