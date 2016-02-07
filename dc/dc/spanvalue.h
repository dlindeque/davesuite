//
//  spanvalue.h
//  dc
//
//  Created by David Lindeque on 11/01/2016.
//  Copyright © 2016 David Lindeque. All rights reserved.
//

#pragma once

#include <memory>
#include <string>
#include "span.h"

namespace dc {
    template<typename T> class spanvalue {
    private:
        T _value;
        span _spn;
    public:
        spanvalue()
        : _spn(), _value()
        { }
        spanvalue(const span &spn, const T &value)
        : _spn(spn), _value(value)
        { }
        spanvalue(const span &spn, T &&value)
        : _spn(spn), _value(std::move(value))
        { }
        spanvalue(const spanvalue<T> &c)
        : _spn(c._spn), _value(c._value)
        { }
        spanvalue(spanvalue<T> &&c)
        : _spn(c._spn), _value(std::move(c._value))
        { }
        
        inline auto spn() const -> const span & { return _spn; }
        inline auto value() const -> const T & { return _value; }
        
        inline auto operator =(const spanvalue<T> &c) -> spanvalue<T>& {
            _spn = c._spn;
            _value = c._value;
            return *this;
        }
        inline auto operator =(spanvalue<T> &&c) -> spanvalue& {
            if (this != &c) {
                _spn = c._spn;
                _value = std::move(c._value);
            }
            return *this;
        }
        
        friend inline auto operator <<(std::wostream& os, const spanvalue<T> &v) -> std::wostream& {
            return os << v.value();
        }
    };
    
    typedef spanvalue<std::wstring> spantext;
}

