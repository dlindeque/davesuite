#include "stdafx.h"
#include "re_lexer.h"
#include "log.h"

using namespace davecommon;

namespace davelexer
{
    auto re_lex(
        std::wistream &src,
        register int &end_line, register int &end_column,
        register int &state,
        re_token &token)->void
    {
        int begin_line = end_line, begin_column = end_column;
        while (true) {
            if (!src.get(token.char_)) {
                token.type = re_token_type::eod;
                token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                return;
            }
            end_column++;

            switch (state) {
            case 0:
                switch (token.char_) {
                case L'\n':
                    end_line++;
                case L'\r':
                    end_column = 1;
                    break;
                }
                switch (token.char_) {
                    // Single characters (simple)
                case L'*':
                    token.type = re_token_type::cardinality;
                    token.cardinality_min = 0;
                    token.cardinality_max = -1;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                case L'+':
                    token.type = re_token_type::cardinality;
                    token.cardinality_min = 1;
                    token.cardinality_max = -1;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                case L'?':
                    token.type = re_token_type::cardinality;
                    token.cardinality_min = 0;
                    token.cardinality_max = 1;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                case L'(':
                    token.type = re_token_type::parenthesis_left;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                case L')':
                    token.type = re_token_type::parenthesis_right;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                case L'|':
                    token.type = re_token_type::pipe;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                case L']':
                    token.type = re_token_type::bracket_right;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                case L'-':
                    token.type = re_token_type::hyphen;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                    // Character sets
                case L'.':
                    token.type = re_token_type::char_set;
                    token.cs = re_char_set::any;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                    // Escapes
                case L'\\':
                    state = 1;
                    break;
                    // Names, Outputs, Cardinality
                case L'{':
                    state = 2;
                    break;
                    // Brackets
                case L'[':
                    state = 8;
                    break;
                default:
                    token.type = re_token_type::char_;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                }
                break;
            case 1:
                state = 0;
                switch (token.char_) {
                case L'n':
                    token.char_ = L'\n';
                    token.type = re_token_type::char_;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                case L'r':
                    token.char_ = L'\r';
                    token.type = re_token_type::char_;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                case L't':
                    token.char_ = L'\t';
                    token.type = re_token_type::char_;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                case L'v':
                    token.char_ = L'\v';
                    token.type = re_token_type::char_;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                case L'f':
                    token.char_ = L'\f';
                    token.type = re_token_type::char_;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                case L'b':
                    token.char_ = L'\b';
                    token.type = re_token_type::char_;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                case L'a':
                    token.cs = re_char_set::lalpha;
                    token.type = re_token_type::char_set;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                case L'A':
                    token.cs = re_char_set::ualpha;
                    token.type = re_token_type::char_set;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                case L'w':
                    token.cs = re_char_set::word;
                    token.type = re_token_type::char_set;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                case L'd':
                    token.cs = re_char_set::digit;
                    token.type = re_token_type::char_set;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                case L's':
                    token.cs = re_char_set::space;
                    token.type = re_token_type::char_set;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                default:
                    token.type = re_token_type::char_;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                }
                break;
            case 2:
                switch (token.char_) {
                case L'>':
                    token.name_output_whitespace.clear();
                    state = 4;
                    break;
                case L'0':
                    token.cardinality_min = 0;
                    state = 6;
                    break;
                case L'1':
                    token.cardinality_min = 1;
                    state = 6;
                    break;
                case L'2':
                    token.cardinality_min = 2;
                    state = 6;
                    break;
                case L'3':
                    token.cardinality_min = 3;
                    state = 6;
                    break;
                case L'4':
                    token.cardinality_min = 4;
                    state = 6;
                    break;
                case L'5':
                    token.cardinality_min = 5;
                    state = 6;
                    break;
                case L'6':
                    token.cardinality_min = 6;
                    state = 6;
                    break;
                case L'7':
                    token.cardinality_min = 7;
                    state = 6;
                    break;
                case L'8':
                    token.cardinality_min = 8;
                    state = 6;
                    break;
                case L'9':
                    token.cardinality_min = 9;
                    state = 6;
                    break;
                default:
                    token.name_output_whitespace.clear();
                    token.name_output_whitespace += token.char_;
                    state = 3;
                    break;
                }
                break;
            case 3:
                switch (token.char_) {
                case L'}':
                    state = 0;
                    token.type = re_token_type::name;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                default:
                    token.name_output_whitespace += token.char_;
                    break;
                }
                break;
            case 4:
                switch (token.char_) {
                case L'\\':
                    state = 5;
                    break;
                case L'}':
                    state = 0;
                    token.type = re_token_type::output;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                default:
                    token.name_output_whitespace += token.char_;
                    break;
                }
                break;
            case 5:
                state = 4;
                switch (token.char_) {
                case L'n':
                    token.name_output_whitespace += L'\n';
                    break;
                case L'r':
                    token.name_output_whitespace += L'\r';
                    break;
                case L't':
                    token.name_output_whitespace += L'\t';
                    break;
                case L'v':
                    token.name_output_whitespace += L'\v';
                    break;
                case L'f':
                    token.name_output_whitespace += L'\f';
                    break;
                case L'b':
                    token.name_output_whitespace += L'\b';
                    break;
                default:
                    token.name_output_whitespace += token.char_;
                    break;
                }
                break;
            case 6:
                switch (token.char_) {
                case L'-':
                    state = 7;
                    token.cardinality_max = 0;
                    break;
                case L'}':
                    state = 0;
                    token.cardinality_max = token.cardinality_min;
                    token.type = re_token_type::cardinality;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                default:
                    // We assume it's 0-9
                    token.cardinality_min *= 10;
                    token.cardinality_min += (token.char_ - L'0');
                    break;
                }
                break;
            case 7:
                switch (token.char_) {
                case L'}':
                    state = 0;
                    token.type = re_token_type::cardinality;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                default:
                    // We assume it's 0-9
                    token.cardinality_max *= 10;
                    token.cardinality_max += (token.char_ - L'0');
                    break;
                }
                break;
            case 8:
                state = 0;
                switch (token.char_) {
                case L'^':
                    token.type = re_token_type::ex_bracket_left;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    return;
                default:
                    token.type = re_token_type::bracket_left;
                    token.spn = span{ position{ begin_line, begin_column }, position{ end_line, end_column } };
                    end_column--;
                    src.unget();
                    return;
                }
                break;
            default:
                throw std::exception("Invalid state");
            }
        }
    }
}