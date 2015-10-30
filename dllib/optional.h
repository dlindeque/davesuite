#pragma once

namespace davelexer
{
    template<typename T> class optional {
    private:
        bool _has_value;
        T _value;
    public:
        optional()
            : _has_value(false)
        {}
        optional(const T &value)
            : _has_value(true), _value(value)
        {}
        optional(T &&value)
            : _has_value(true), _value(std::move(value))
        {}
        optional(const optional<T> &c)
            : _has_value(c._has_value), _value(c._value)
        {}
        optional(optional<T> &&c)
            : _has_value(c._has_value), _value(std::move(c._value))
        {}

        inline auto has_value() const -> bool { return _has_value; }
        inline auto value() const -> const T& { return _value; }
        inline auto value() -> T { return _value; }

        inline auto operator =(const optional<T> &c) -> optional<T>& {
            _has_value = c._has_value;
            _value = c._value;
            return *this;
        }
        inline auto operator =(optional<T> &&c) -> optional<T>& {
            if (this != &c) {
                _has_value = c._has_value;
                _value = std::move(c._value);
            }
            return *this;
        }
        inline auto operator ==(const optional<T> &other) const -> bool {
            return _has_value == other._has_value && _value == other._value;
        }
        inline auto operator !=(const optional<T> &other) const -> bool {
            return !(*this == other);
        }
        inline auto operator ==(const T &other) const -> bool {
            return _has_value && _value == other;
        }
        inline auto operator !=(const T &other) const -> bool {
            return !(*this == other);
        }
    };
}