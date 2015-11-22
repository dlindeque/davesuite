#pragma once

#include <string>
#include <sstream>
#include <vector>
#include "..\common\logger.h"
#include "re_lexer.h"

using namespace davelexer;

namespace davecommon
{
    inline auto wchar_friendly(wchar_t ch, std::wostream &os) -> std::wostream& {
        switch (ch) {
        case L' ':
            os << L"<space>";
            break;
        case L'\n':
            os << L"\\n";
            break;
        case L'\r':
            os << L"\\r";
            break;
        case L'\t':
            os << L"\\t";
            break;
        case L'\v':
            os << L"\\v";
            break;
        case L'\f':
            os << L"\\f";
            break;
        case L'\b':
            os << L"\\b";
            break;
        case 0:
            os << L"<start>";
            break;
        case WCHAR_MAX:
            os << L"<end>";
        default:
            os << ch;
            break;
        }
        return os;
    }

    struct log {
        struct warning {

        };
        struct error {
            static inline auto tkn_name(re_token_type t) -> std::wstring {
                switch (t) {
                case re_token_type::bracket_left: return L"'['";
                case re_token_type::bracket_right: return L"']'";
                case re_token_type::cardinality: return L"{x,y}";
                case re_token_type::char_: return L"<char>";
                case re_token_type::char_set: return L"<char set>";
                case re_token_type::eod: return L"<eod>";
                case re_token_type::ex_bracket_left: return L"'[^'";
                case re_token_type::hyphen: return L"'-'";
                case re_token_type::name: return L"{name}";
                case re_token_type::output: return L"{>...}";
                case re_token_type::parenthesis_left: return L"'('";
                case re_token_type::parenthesis_right: return L"')'";
                case re_token_type::pipe: return L"'|'";
                default: return L"???";
                }
            }

            static auto syntax_error(logger *logger, const container *container, const span &spn, const std::vector<re_token_type> &expected) -> void {
                std::wstringstream stm;
                stm << L"Syntax error Expected one of ";
                if (expected.size() == 0) {
                    stm << L"UNKNOWN";
                }
                else {
                    stm << tkn_name(expected[0]);
                }
                for (size_t i = 1; i < expected.size();i++) {
                    stm << L',' << tkn_name(expected[i]);
                }
                logger->write(severity::error, container, spn, stm.str());
            }

            static auto invalid_cardinality(logger *logger, const container *container, const span &spn, int min, int max) -> void {
                std::wstringstream stm;
                stm << L"Invalid cardinality (" << min << L'-' << max << L')';
                logger->write(severity::error, container, spn, stm.str());
            }

            static auto invalid_range(logger *logger, const container *container, const span &spn, wchar_t from, wchar_t to) -> void {
                std::wstringstream stm;
                stm << L"Invalid range (";
                wchar_friendly(from, stm) << L'-';
                wchar_friendly(to, stm) << L')';
                logger->write(severity::error, container, spn, stm.str());
            }

            static auto expression_not_found(logger *logger, const container *container, const span &spn, const std::wstring &name) -> void {
                std::wstringstream stm;
                stm << L"Expression '" << name << "' was not found";
                logger->write(severity::error, container, spn, stm.str());
            }

            static auto re_must_process_something(logger *logger, const container *container, const span &spn, const std::wstring &name) -> void {
                std::wstringstream stm;
                stm << L"Expression '" << name << "' cannot be used as a token since it's possible to match zero characters.";
                logger->write(severity::error, container, spn, stm.str());
            }

            static auto imported_section_not_found(logger *logger, const container *container, const span &spn, const std::wstring &name) -> void {
                std::wstringstream stm;
                stm << L"The imported section '" << name << "' could not be found.";
                logger->write(severity::error, container, spn, stm.str());
            }

            static auto binding_already_defined(logger *logger, const container *container, const span &spn, const std::wstring &name) -> void {
                std::wstringstream stm;
                stm << L"The binding '" << name << "' was previously defined.";
                logger->write(severity::error, container, spn, stm.str());
            }
        };
    };
}