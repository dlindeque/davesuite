#pragma once

#include <string>
#include <sstream>

namespace dc
{
    class output_writer {
    public:
        virtual ~output_writer() { }
        
        virtual auto append(const wchar_t &c) -> void = 0;
        inline auto append(const wchar_t *txt) -> void {
            const wchar_t *p = txt;
            while (*p) {
                append(*p);
                p++;
            }
        }
    };
    
    inline auto operator << (output_writer &ow, const wchar_t *txt) -> output_writer&
    {
        ow.append(txt);
        return ow;
    }
    
    inline auto operator << (output_writer &ow, const std::wstring &txt) -> output_writer&
    {
        ow.append(txt.c_str());
        return ow;
    }
    
    inline auto operator << (output_writer &ow, const wchar_t &c) -> output_writer&
    {
        ow.append(c);
        return ow;
    }
    
    //inline auto operator << (output_writer &ow, const int &c) -> output_writer&
    //{
    //    char buf[16];
    //    wsprintf_s(buf, "%d", c);
    //    ow.append(buf);
    //    return ow;
    //}
    
    inline auto operator << (output_writer &ow, void(__cdecl *_Pfn)(output_writer&)) -> output_writer&
    {
        _Pfn(ow);
        return ow;
    }

    inline auto endl(output_writer &ow) -> void
    {
        ow.append(L'\n');
    }

    class indenting_writer : public output_writer {
    private:
        int _margin;
        int _indentation;
        int _width;
        output_writer &_inner;
    public:
        indenting_writer(output_writer &inner, int width, int margin)
            : _inner(inner), _indentation(0), _width(width), _margin(margin)
        { }
        indenting_writer(const indenting_writer &c) = delete;
        indenting_writer(indenting_writer &&c) = delete;

        virtual ~indenting_writer() { }

        inline auto increase() -> void { _indentation++; }
        inline auto decrease() -> void { _indentation--; }
        inline auto increase(int amt) -> void { _indentation += amt; }
        inline auto decrease(int amt) -> void { _indentation -= amt; }

        virtual auto append(const wchar_t &c) -> void override {
            if (c == L'\n') {
                // Write the \n
                _inner.append(L'\n');
                // Write the margin, and the indent
                auto w = _margin + _indentation * _width;
                for (int i = 0; i < w; i++) {
                    _inner.append(L' ');
                }
            }
            else {
                _inner.append(c);
            }
        }

        inline auto operator =(const indenting_writer &c)->indenting_writer& = delete;
        inline auto operator =(indenting_writer &&c)->indenting_writer& = delete;
    };

    inline auto inc(output_writer& ow) -> void
    {
        auto ident = dynamic_cast<indenting_writer*>(&ow);
        if (ident != nullptr) {
            ident->increase();
        }
    }

    inline auto dec(output_writer& ow) -> void
    {
        auto ident = dynamic_cast<indenting_writer*>(&ow);
        if (ident != nullptr) {
            ident->decrease();
        }
    }

    class single_line_writer : public output_writer {
    private:
        output_writer &_inner;
    public:
        single_line_writer(output_writer &inner)
            : _inner(inner)
        { }
        single_line_writer(const single_line_writer &c) = delete;
        single_line_writer(single_line_writer &&c) = delete;

        virtual ~single_line_writer() { }

        virtual auto append(const wchar_t &c) -> void override {
            if (c != L'\n') {
                _inner.append(c);
            }
            else {
                _inner.append(L' ');
            }
        }

        inline auto operator =(const single_line_writer &c)->single_line_writer& = delete;
        inline auto operator =(single_line_writer &&c)->single_line_writer& = delete;
    };

    class string_writer : public output_writer {
    private:
        std::wstring _str;
    public:
        string_writer()
            : _str()
        { }
        string_writer(const std::wstring &init)
            : _str(init)
        { }
        string_writer(std::wstring &&init)
            : _str(std::move(init))
        { }
        string_writer(const string_writer &c) = delete;
        string_writer(string_writer &&c) = delete;

        virtual ~string_writer() { }

        inline auto str() const -> const std::wstring& { return _str; }

        virtual auto append(const wchar_t &c) -> void override { _str += c; }

        inline auto operator =(const string_writer &c)->string_writer& = delete;
        inline auto operator =(string_writer &&c)->string_writer& = delete;
    };

    class output_adapter : public output_writer {
    private:
        std::wostream &_stm;
    public:
        output_adapter(std::wostream &stm)
            : _stm(stm)
        { }
        output_adapter(const string_writer &c) = delete;
        output_adapter(string_writer &&c) = delete;

        virtual ~output_adapter() { }

        virtual auto append(const wchar_t &c) -> void override { _stm << c; }

        inline auto operator =(const string_writer &c)->string_writer& = delete;
        inline auto operator =(string_writer &&c)->string_writer& = delete;
    };
}