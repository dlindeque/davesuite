#include <vector>
#include "dl.dp.hpp"

namespace davelexer
{
    struct lexical_type {
        struct CharRange { };
        struct CharRanges { };
        struct Document { };
        struct DocumentItem { };
        struct EnumItems { };
        struct Ident { };
        struct NamespaceItem { };
        struct NamespaceItems { };
        struct QName { };
        struct Re { };
        struct ReText { };
        struct SetItem { };
        struct SetItems { };
        struct Str { };
    };
    struct lexical_value {
        std::wstring desc;
        TokenType tkn_type;
        std::wstring tkn_value;
        davecommon::span tkn_span;
         std::shared_ptr<CharSetAst> CharRange;
         std::vector<std::shared_ptr<CharSetAst>> CharRanges;
         std::vector<std::shared_ptr<DocumentAst>> Document;
         std::shared_ptr<DocumentAst> DocumentItem;
         std::vector<AstToken<std::wstring>> EnumItems;
         AstToken<std::wstring> Ident;
         std::shared_ptr<NamespaceItemAst> NamespaceItem;
         std::vector<std::shared_ptr<NamespaceItemAst>> NamespaceItems;
         std::vector<AstToken<std::wstring>> QName;
         std::shared_ptr<ReAst> Re;
         std::shared_ptr<ReAst> ReText;
         std::shared_ptr<SetItemAst> SetItem;
         std::vector<std::shared_ptr<SetItemAst>> SetItems;
         AstToken<std::wstring> Str;
        lexical_value(davecommon::span &&spn, const TokenType _tkn_type, const std::wstring &_tkn_value)
        : desc(text(_tkn_type)), tkn_span(std::move(spn)), tkn_type(_tkn_type), tkn_value(_tkn_value)
        {}
        lexical_value(davecommon::span &&spn, const TokenType _tkn_type, std::wstring &&_tkn_value)
        : desc(text(_tkn_type)), tkn_span(std::move(spn)), tkn_type(_tkn_type), tkn_value(std::move(_tkn_value))
        {}
        lexical_value(const lexical_type::CharRange&,  std::shared_ptr<CharSetAst>&& value)
        : desc(L"CHARRANGE"), CharRange(std::move(value))
        {}
        lexical_value(const lexical_type::CharRanges&,  std::vector<std::shared_ptr<CharSetAst>>&& value)
        : desc(L"CHARRANGES"), CharRanges(std::move(value))
        {}
        lexical_value(const lexical_type::Document&,  std::vector<std::shared_ptr<DocumentAst>>&& value)
        : desc(L"DOCUMENT"), Document(std::move(value))
        {}
        lexical_value(const lexical_type::DocumentItem&,  std::shared_ptr<DocumentAst>&& value)
        : desc(L"DOCUMENTITEM"), DocumentItem(std::move(value))
        {}
        lexical_value(const lexical_type::EnumItems&,  std::vector<AstToken<std::wstring>>&& value)
        : desc(L"ENUMITEMS"), EnumItems(std::move(value))
        {}
        lexical_value(const lexical_type::Ident&,  AstToken<std::wstring>&& value)
        : desc(L"IDENT"), Ident(std::move(value))
        {}
        lexical_value(const lexical_type::NamespaceItem&,  std::shared_ptr<NamespaceItemAst>&& value)
        : desc(L"NAMESPACEITEM"), NamespaceItem(std::move(value))
        {}
        lexical_value(const lexical_type::NamespaceItems&,  std::vector<std::shared_ptr<NamespaceItemAst>>&& value)
        : desc(L"NAMESPACEITEMS"), NamespaceItems(std::move(value))
        {}
        lexical_value(const lexical_type::QName&,  std::vector<AstToken<std::wstring>>&& value)
        : desc(L"QNAME"), QName(std::move(value))
        {}
        lexical_value(const lexical_type::Re&,  std::shared_ptr<ReAst>&& value)
        : desc(L"RE"), Re(std::move(value))
        {}
        lexical_value(const lexical_type::ReText&,  std::shared_ptr<ReAst>&& value)
        : desc(L"RETEXT"), ReText(std::move(value))
        {}
        lexical_value(const lexical_type::SetItem&,  std::shared_ptr<SetItemAst>&& value)
        : desc(L"SETITEM"), SetItem(std::move(value))
        {}
        lexical_value(const lexical_type::SetItems&,  std::vector<std::shared_ptr<SetItemAst>>&& value)
        : desc(L"SETITEMS"), SetItems(std::move(value))
        {}
        lexical_value(const lexical_type::Str&,  AstToken<std::wstring>&& value)
        : desc(L"STR"), Str(std::move(value))
        {}
    };

    auto parse(std::wistream &stm, const std::shared_ptr<davecommon::container> &cntr, davecommon::logger *logger, bool &ok) ->  std::vector<std::shared_ptr<DocumentAst>>
    {
        std::vector<size_t> states;
        std::vector<lexical_value> values;
        dlstate s(stm, cntr);
        s.states.push_back(0);
        states.push_back(0);
        bool read_token = true;
        while(ok) {
            if (read_token) {
                while(true) {
                    if (!read_next_token(s)) {
                        s.token = TokenType::Eod;
                        //ok = false;
                        //davecommon::log::error::UnexpectedEndOfFile(logger, cntr);
                        //return  std::vector<std::shared_ptr<DocumentAst>>();
                    }
                    if (s.token != TokenType::Whitespace && s.token != TokenType::Comment) break;
                }
            }
            switch(states.back()) {
                case 0:
                    switch(s.token) {
                        case TokenType::Namespace:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Namespace, std::move(s.value));
                            states.push_back(2);
                            read_token = true;
                            break;
                        case TokenType::Set:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Set, std::move(s.value));
                            states.push_back(3);
                            read_token = true;
                            break;
                        case TokenType::Import:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Import, std::move(s.value));
                            states.push_back(4);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Namespace);
                                validTokens.push_back(TokenType::Set);
                                validTokens.push_back(TokenType::Import);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 1:
                    switch(s.token) {
                        case TokenType::Namespace:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Namespace, std::move(s.value));
                            states.push_back(2);
                            read_token = true;
                            break;
                        case TokenType::Set:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Set, std::move(s.value));
                            states.push_back(3);
                            read_token = true;
                            break;
                        case TokenType::Import:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Import, std::move(s.value));
                            states.push_back(4);
                            read_token = true;
                            break;
                        case TokenType::Eod:
                            return values.back().Document;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Namespace);
                                validTokens.push_back(TokenType::Set);
                                validTokens.push_back(TokenType::Import);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 2:
                    switch(s.token) {
                        case TokenType::Identifier:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Identifier, std::move(s.value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Identifier);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 3:
                    switch(s.token) {
                        case TokenType::Start:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Start, std::move(s.value));
                            states.push_back(9);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Start);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 4:
                    switch(s.token) {
                        case TokenType::String:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::String, std::move(s.value));
                            states.push_back(6);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::String);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 5:
                    // Reduce Document: DocumentItem
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::Document(), as_vector(std::move(i1.DocumentItem)));
                        read_token = false;
                        switch(states.back()) {
                            case 0: states.push_back(1); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 6:
                    // Reduce Str: TokenType.String
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::Str(), AstToken<std::wstring>(i1.tkn_span, std::move(i1.tkn_value)));
                        read_token = false;
                        switch(states.back()) {
                            case 4: states.push_back(7); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 7:
                    switch(s.token) {
                        case TokenType::Semicolon:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Semicolon, std::move(s.value));
                            states.push_back(8);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Semicolon);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 8:
                    // Reduce DocumentItem: TokenType.Import Str TokenType.Semicolon
                    if (true) {
                        auto i3 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::DocumentItem(), std::shared_ptr<DocumentAst>(new ImportAst(davecommon::span(i1.tkn_span.begin, i3.tkn_span.end), std::move(i2.Str))));
                        read_token = false;
                        switch(states.back()) {
                            case 0: states.push_back(5); break;
                            case 1: states.push_back(111); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 9:
                    switch(s.token) {
                        case TokenType::Equals:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Equals, std::move(s.value));
                            states.push_back(10);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Equals);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 10:
                    switch(s.token) {
                        case TokenType::Identifier:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Identifier, std::move(s.value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Identifier);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 11:
                    // Reduce Ident: TokenType.Identifier
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::Ident(), AstToken<std::wstring>(i1.tkn_span, std::move(i1.tkn_value)));
                        read_token = false;
                        switch(states.back()) {
                            case 2: states.push_back(12); break;
                            case 10: states.push_back(12); break;
                            case 15: states.push_back(16); break;
                            case 19: states.push_back(106); break;
                            case 21: states.push_back(72); break;
                            case 22: states.push_back(64); break;
                            case 24: states.push_back(25); break;
                            case 30: states.push_back(12); break;
                            case 42: states.push_back(12); break;
                            case 65: states.push_back(66); break;
                            case 68: states.push_back(71); break;
                            case 74: states.push_back(12); break;
                            case 81: states.push_back(12); break;
                            case 83: states.push_back(84); break;
                            case 84: states.push_back(12); break;
                            case 87: states.push_back(88); break;
                            case 88: states.push_back(12); break;
                            case 92: states.push_back(93); break;
                            case 93: states.push_back(12); break;
                            case 97: states.push_back(12); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 12:
                    // Reduce QName: Ident
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::QName(), as_vector(std::move(i1.Ident)));
                        read_token = false;
                        switch(states.back()) {
                            case 2: states.push_back(17); break;
                            case 10: states.push_back(13); break;
                            case 30: states.push_back(45); break;
                            case 42: states.push_back(45); break;
                            case 74: states.push_back(96); break;
                            case 81: states.push_back(91); break;
                            case 84: states.push_back(85); break;
                            case 88: states.push_back(89); break;
                            case 93: states.push_back(94); break;
                            case 97: states.push_back(101); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 13:
                    switch(s.token) {
                        case TokenType::Semicolon:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Semicolon, std::move(s.value));
                            states.push_back(14);
                            read_token = true;
                            break;
                        case TokenType::Dot:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Dot, std::move(s.value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Semicolon);
                                validTokens.push_back(TokenType::Dot);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 14:
                    // Reduce DocumentItem: TokenType.Set TokenType.Start TokenType.Equals QName TokenType.Semicolon
                    if (true) {
                        auto i5 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i4 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i3 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::DocumentItem(), std::shared_ptr<DocumentAst>(new StartAutomataAst(davecommon::span(i1.tkn_span.begin, i5.tkn_span.end), std::move(i4.QName))));
                        read_token = false;
                        switch(states.back()) {
                            case 0: states.push_back(5); break;
                            case 1: states.push_back(111); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 15:
                    switch(s.token) {
                        case TokenType::Identifier:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Identifier, std::move(s.value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Identifier);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 16:
                    // Reduce QName: QName TokenType.Dot Ident
                    if (true) {
                        auto i3 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::QName(), append_vector(std::move(i1.QName), std::move(i3.Ident)));
                        read_token = false;
                        switch(states.back()) {
                            case 2: states.push_back(17); break;
                            case 10: states.push_back(13); break;
                            case 30: states.push_back(45); break;
                            case 42: states.push_back(45); break;
                            case 74: states.push_back(96); break;
                            case 81: states.push_back(91); break;
                            case 84: states.push_back(85); break;
                            case 88: states.push_back(89); break;
                            case 93: states.push_back(94); break;
                            case 97: states.push_back(101); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 17:
                    switch(s.token) {
                        case TokenType::OpenBrace:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::OpenBrace, std::move(s.value));
                            states.push_back(18);
                            read_token = true;
                            break;
                        case TokenType::Dot:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Dot, std::move(s.value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::OpenBrace);
                                validTokens.push_back(TokenType::Dot);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 18:
                    switch(s.token) {
                        case TokenType::Automata:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Automata, std::move(s.value));
                            states.push_back(19);
                            read_token = true;
                            break;
                        case TokenType::Set:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Set, std::move(s.value));
                            states.push_back(21);
                            read_token = true;
                            break;
                        case TokenType::Enum:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Enum, std::move(s.value));
                            states.push_back(22);
                            read_token = true;
                            break;
                        case TokenType::Pattern:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Pattern, std::move(s.value));
                            states.push_back(24);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Automata);
                                validTokens.push_back(TokenType::Set);
                                validTokens.push_back(TokenType::Enum);
                                validTokens.push_back(TokenType::Pattern);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 19:
                    switch(s.token) {
                        case TokenType::Identifier:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Identifier, std::move(s.value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Identifier);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 20:
                    switch(s.token) {
                        case TokenType::Automata:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Automata, std::move(s.value));
                            states.push_back(19);
                            read_token = true;
                            break;
                        case TokenType::Set:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Set, std::move(s.value));
                            states.push_back(21);
                            read_token = true;
                            break;
                        case TokenType::Enum:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Enum, std::move(s.value));
                            states.push_back(22);
                            read_token = true;
                            break;
                        case TokenType::Pattern:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Pattern, std::move(s.value));
                            states.push_back(24);
                            read_token = true;
                            break;
                        case TokenType::CloseBrace:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::CloseBrace, std::move(s.value));
                            states.push_back(104);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Automata);
                                validTokens.push_back(TokenType::Set);
                                validTokens.push_back(TokenType::Enum);
                                validTokens.push_back(TokenType::Pattern);
                                validTokens.push_back(TokenType::CloseBrace);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 21:
                    switch(s.token) {
                        case TokenType::Identifier:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Identifier, std::move(s.value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Identifier);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 22:
                    switch(s.token) {
                        case TokenType::Identifier:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Identifier, std::move(s.value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Identifier);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 23:
                    // Reduce NamespaceItems: NamespaceItem
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::NamespaceItems(), as_vector(std::move(i1.NamespaceItem)));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(20); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 24:
                    switch(s.token) {
                        case TokenType::Identifier:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Identifier, std::move(s.value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Identifier);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 25:
                    switch(s.token) {
                        case TokenType::Equals:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Equals, std::move(s.value));
                            states.push_back(26);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Equals);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 26:
                    switch(s.token) {
                        case TokenType::ReStart:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::ReStart, std::move(s.value));
                            states.push_back(27);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::ReStart);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 27:
                    switch(s.token) {
                        case TokenType::OpenBrace:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::OpenBrace, std::move(s.value));
                            states.push_back(30);
                            read_token = true;
                            break;
                        case TokenType::Dot:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Dot, std::move(s.value));
                            states.push_back(31);
                            read_token = true;
                            break;
                        case TokenType::CharClass:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::CharClass, std::move(s.value));
                            states.push_back(32);
                            read_token = true;
                            break;
                        case TokenType::OpenSquare:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::OpenSquare, std::move(s.value));
                            states.push_back(33);
                            read_token = true;
                            break;
                        case TokenType::Char:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Char, std::move(s.value));
                            states.push_back(34);
                            read_token = true;
                            break;
                        case TokenType::OpenParenthesis:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::OpenParenthesis, std::move(s.value));
                            states.push_back(35);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::OpenBrace);
                                validTokens.push_back(TokenType::Dot);
                                validTokens.push_back(TokenType::CharClass);
                                validTokens.push_back(TokenType::OpenSquare);
                                validTokens.push_back(TokenType::Char);
                                validTokens.push_back(TokenType::OpenParenthesis);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 28:
                    switch(s.token) {
                        case TokenType::Semicolon:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Semicolon, std::move(s.value));
                            states.push_back(29);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Semicolon);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 29:
                    // Reduce NamespaceItem: TokenType.Pattern Ident TokenType.Equals Re TokenType.Semicolon
                    if (true) {
                        auto i5 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i4 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i3 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::NamespaceItem(), std::shared_ptr<NamespaceItemAst>(new PatternAst(davecommon::span(i1.tkn_span.begin, i5.tkn_span.end), std::move(i2.Ident), std::move(i4.Re))));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(23); break;
                            case 20: states.push_back(103); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 30:
                    switch(s.token) {
                        case TokenType::Identifier:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Identifier, std::move(s.value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Identifier);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 31:
                    // Reduce ReText: TokenType.Dot
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new CharClassReAst(i1.tkn_span, AstToken<CharClass>(i1.tkn_span, CharClass::AnyChar))));
                        read_token = false;
                        switch(states.back()) {
                            case 27: states.push_back(36); break;
                            case 35: states.push_back(52); break;
                            case 36: states.push_back(43); break;
                            case 40: states.push_back(51); break;
                            case 43: states.push_back(43); break;
                            case 51: states.push_back(43); break;
                            case 52: states.push_back(43); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 32:
                    // Reduce ReText: TokenType.CharClass
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new CharClassReAst(i1.tkn_span, AstToken<CharClass>(i1.tkn_span, as_charclass(i1.tkn_value)))));
                        read_token = false;
                        switch(states.back()) {
                            case 27: states.push_back(36); break;
                            case 35: states.push_back(52); break;
                            case 36: states.push_back(43); break;
                            case 40: states.push_back(51); break;
                            case 43: states.push_back(43); break;
                            case 51: states.push_back(43); break;
                            case 52: states.push_back(43); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 33:
                    switch(s.token) {
                        case TokenType::Hat:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Hat, std::move(s.value));
                            states.push_back(54);
                            read_token = true;
                            break;
                        case TokenType::Char:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Char, std::move(s.value));
                            states.push_back(55);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Hat);
                                validTokens.push_back(TokenType::Char);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 34:
                    // Reduce ReText: TokenType.Char
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new CharReAst(i1.tkn_span, AstToken<wchar_t>(i1.tkn_span, i1.tkn_value[0]))));
                        read_token = false;
                        switch(states.back()) {
                            case 27: states.push_back(36); break;
                            case 35: states.push_back(52); break;
                            case 36: states.push_back(43); break;
                            case 40: states.push_back(51); break;
                            case 43: states.push_back(43); break;
                            case 51: states.push_back(43); break;
                            case 52: states.push_back(43); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 35:
                    switch(s.token) {
                        case TokenType::OpenBrace:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::OpenBrace, std::move(s.value));
                            states.push_back(30);
                            read_token = true;
                            break;
                        case TokenType::Dot:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Dot, std::move(s.value));
                            states.push_back(31);
                            read_token = true;
                            break;
                        case TokenType::CharClass:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::CharClass, std::move(s.value));
                            states.push_back(32);
                            read_token = true;
                            break;
                        case TokenType::OpenSquare:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::OpenSquare, std::move(s.value));
                            states.push_back(33);
                            read_token = true;
                            break;
                        case TokenType::Char:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Char, std::move(s.value));
                            states.push_back(34);
                            read_token = true;
                            break;
                        case TokenType::OpenParenthesis:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::OpenParenthesis, std::move(s.value));
                            states.push_back(35);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::OpenBrace);
                                validTokens.push_back(TokenType::Dot);
                                validTokens.push_back(TokenType::CharClass);
                                validTokens.push_back(TokenType::OpenSquare);
                                validTokens.push_back(TokenType::Char);
                                validTokens.push_back(TokenType::OpenParenthesis);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 36:
                    switch(s.token) {
                        case TokenType::CharClass:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::CharClass, std::move(s.value));
                            states.push_back(32);
                            read_token = true;
                            break;
                        case TokenType::ReEnd:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::ReEnd, std::move(s.value));
                            states.push_back(37);
                            read_token = true;
                            break;
                        case TokenType::Asterisk:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Asterisk, std::move(s.value));
                            states.push_back(38);
                            read_token = true;
                            break;
                        case TokenType::Question:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Question, std::move(s.value));
                            states.push_back(39);
                            read_token = true;
                            break;
                        case TokenType::Pipe:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Pipe, std::move(s.value));
                            states.push_back(40);
                            read_token = true;
                            break;
                        case TokenType::Plus:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Plus, std::move(s.value));
                            states.push_back(41);
                            read_token = true;
                            break;
                        case TokenType::Char:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Char, std::move(s.value));
                            states.push_back(34);
                            read_token = true;
                            break;
                        case TokenType::OpenBrace:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::OpenBrace, std::move(s.value));
                            states.push_back(42);
                            read_token = true;
                            break;
                        case TokenType::Dot:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Dot, std::move(s.value));
                            states.push_back(31);
                            read_token = true;
                            break;
                        case TokenType::OpenSquare:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::OpenSquare, std::move(s.value));
                            states.push_back(33);
                            read_token = true;
                            break;
                        case TokenType::OpenParenthesis:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::OpenParenthesis, std::move(s.value));
                            states.push_back(35);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::CharClass);
                                validTokens.push_back(TokenType::ReEnd);
                                validTokens.push_back(TokenType::Asterisk);
                                validTokens.push_back(TokenType::Question);
                                validTokens.push_back(TokenType::Pipe);
                                validTokens.push_back(TokenType::Plus);
                                validTokens.push_back(TokenType::Char);
                                validTokens.push_back(TokenType::OpenBrace);
                                validTokens.push_back(TokenType::Dot);
                                validTokens.push_back(TokenType::OpenSquare);
                                validTokens.push_back(TokenType::OpenParenthesis);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 37:
                    // Reduce Re: TokenType.ReStart ReText TokenType.ReEnd
                    if (true) {
                        auto i3 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::Re(), std::move(i2.ReText));
                        read_token = false;
                        switch(states.back()) {
                            case 26: states.push_back(28); break;
                            case 73: states.push_back(76); break;
                            case 77: states.push_back(76); break;
                            case 107: states.push_back(76); break;
                            case 108: states.push_back(76); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 38:
                    // Reduce ReText: ReText TokenType.Asterisk
                    if (true) {
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new CardinalReAst(davecommon::span(i1.ReText->Spn.begin, i2.tkn_span.end), std::move(i1.ReText), 0, -1)));
                        read_token = false;
                        switch(states.back()) {
                            case 27: states.push_back(36); break;
                            case 35: states.push_back(52); break;
                            case 36: states.push_back(43); break;
                            case 40: states.push_back(51); break;
                            case 43: states.push_back(43); break;
                            case 51: states.push_back(43); break;
                            case 52: states.push_back(43); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 39:
                    // Reduce ReText: ReText TokenType.Question
                    if (true) {
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new CardinalReAst(davecommon::span(i1.ReText->Spn.begin, i2.tkn_span.end), std::move(i1.ReText), 0, 1)));
                        read_token = false;
                        switch(states.back()) {
                            case 27: states.push_back(36); break;
                            case 35: states.push_back(52); break;
                            case 36: states.push_back(43); break;
                            case 40: states.push_back(51); break;
                            case 43: states.push_back(43); break;
                            case 51: states.push_back(43); break;
                            case 52: states.push_back(43); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 40:
                    switch(s.token) {
                        case TokenType::OpenBrace:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::OpenBrace, std::move(s.value));
                            states.push_back(30);
                            read_token = true;
                            break;
                        case TokenType::Dot:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Dot, std::move(s.value));
                            states.push_back(31);
                            read_token = true;
                            break;
                        case TokenType::CharClass:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::CharClass, std::move(s.value));
                            states.push_back(32);
                            read_token = true;
                            break;
                        case TokenType::OpenSquare:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::OpenSquare, std::move(s.value));
                            states.push_back(33);
                            read_token = true;
                            break;
                        case TokenType::Char:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Char, std::move(s.value));
                            states.push_back(34);
                            read_token = true;
                            break;
                        case TokenType::OpenParenthesis:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::OpenParenthesis, std::move(s.value));
                            states.push_back(35);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::OpenBrace);
                                validTokens.push_back(TokenType::Dot);
                                validTokens.push_back(TokenType::CharClass);
                                validTokens.push_back(TokenType::OpenSquare);
                                validTokens.push_back(TokenType::Char);
                                validTokens.push_back(TokenType::OpenParenthesis);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 41:
                    // Reduce ReText: ReText TokenType.Plus
                    if (true) {
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new CardinalReAst(davecommon::span(i1.ReText->Spn.begin, i2.tkn_span.end), std::move(i1.ReText), 1, -1)));
                        read_token = false;
                        switch(states.back()) {
                            case 27: states.push_back(36); break;
                            case 35: states.push_back(52); break;
                            case 36: states.push_back(43); break;
                            case 40: states.push_back(51); break;
                            case 43: states.push_back(43); break;
                            case 51: states.push_back(43); break;
                            case 52: states.push_back(43); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 42:
                    switch(s.token) {
                        case TokenType::Number:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Number, std::move(s.value));
                            states.push_back(44);
                            read_token = true;
                            break;
                        case TokenType::Identifier:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Identifier, std::move(s.value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Number);
                                validTokens.push_back(TokenType::Identifier);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 43:
                    switch(s.token) {
                        case TokenType::Asterisk:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Asterisk, std::move(s.value));
                            states.push_back(38);
                            read_token = true;
                            break;
                        case TokenType::Pipe:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Pipe, std::move(s.value));
                            states.push_back(40);
                            read_token = true;
                            break;
                        case TokenType::Plus:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Plus, std::move(s.value));
                            states.push_back(41);
                            read_token = true;
                            break;
                        case TokenType::OpenBrace:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::OpenBrace, std::move(s.value));
                            states.push_back(42);
                            read_token = true;
                            break;
                        case TokenType::Question:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Question, std::move(s.value));
                            states.push_back(39);
                            read_token = true;
                            break;
                        default:
                            // Reduce ReText: ReText ReText
                            if (true) {
                                auto i2 = std::move(values.back());
                                values.pop_back();
                                states.pop_back();
                                auto i1 = std::move(values.back());
                                values.pop_back();
                                states.pop_back();
                                 values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new ThenReAst(davecommon::span(i1.ReText->Spn.begin, i2.ReText->Spn.end), std::move(i1.ReText), std::move(i2.ReText))));
                                read_token = false;
                                switch(states.back()) {
                                    case 27: states.push_back(36); break;
                                    case 35: states.push_back(52); break;
                                    case 36: states.push_back(43); break;
                                    case 40: states.push_back(51); break;
                                    case 43: states.push_back(43); break;
                                    case 51: states.push_back(43); break;
                                    case 52: states.push_back(43); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 44:
                    switch(s.token) {
                        case TokenType::Comma:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Comma, std::move(s.value));
                            states.push_back(47);
                            read_token = true;
                            break;
                        case TokenType::CloseBrace:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::CloseBrace, std::move(s.value));
                            states.push_back(48);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Comma);
                                validTokens.push_back(TokenType::CloseBrace);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 45:
                    switch(s.token) {
                        case TokenType::CloseBrace:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::CloseBrace, std::move(s.value));
                            states.push_back(46);
                            read_token = true;
                            break;
                        case TokenType::Dot:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Dot, std::move(s.value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::CloseBrace);
                                validTokens.push_back(TokenType::Dot);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 46:
                    // Reduce ReText: TokenType.OpenBrace QName TokenType.CloseBrace
                    if (true) {
                        auto i3 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new ReferenceReAst(davecommon::span(i1.tkn_span.begin, i3.tkn_span.end), std::move(i2.QName))));
                        read_token = false;
                        switch(states.back()) {
                            case 27: states.push_back(36); break;
                            case 35: states.push_back(52); break;
                            case 36: states.push_back(43); break;
                            case 40: states.push_back(51); break;
                            case 43: states.push_back(43); break;
                            case 51: states.push_back(43); break;
                            case 52: states.push_back(43); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 47:
                    switch(s.token) {
                        case TokenType::Number:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Number, std::move(s.value));
                            states.push_back(49);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Number);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 48:
                    // Reduce ReText: ReText TokenType.OpenBrace TokenType.Number TokenType.CloseBrace
                    if (true) {
                        auto i4 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i3 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new CardinalReAst(davecommon::span(i1.tkn_span.begin, i4.tkn_span.end), std::move(i1.ReText), std::stoi(i3.tkn_value), std::stoi(i3.tkn_value))));
                        read_token = false;
                        switch(states.back()) {
                            case 27: states.push_back(36); break;
                            case 35: states.push_back(52); break;
                            case 36: states.push_back(43); break;
                            case 40: states.push_back(51); break;
                            case 43: states.push_back(43); break;
                            case 51: states.push_back(43); break;
                            case 52: states.push_back(43); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 49:
                    switch(s.token) {
                        case TokenType::CloseBrace:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::CloseBrace, std::move(s.value));
                            states.push_back(50);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::CloseBrace);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 50:
                    // Reduce ReText: ReText TokenType.OpenBrace TokenType.Number TokenType.Comma TokenType.Number TokenType.CloseBrace
                    if (true) {
                        auto i6 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i5 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i4 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i3 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new CardinalReAst(davecommon::span(i1.tkn_span.begin, i6.tkn_span.end), std::move(i1.ReText), std::stoi(i3.tkn_value), std::stoi(i5.tkn_value))));
                        read_token = false;
                        switch(states.back()) {
                            case 27: states.push_back(36); break;
                            case 35: states.push_back(52); break;
                            case 36: states.push_back(43); break;
                            case 40: states.push_back(51); break;
                            case 43: states.push_back(43); break;
                            case 51: states.push_back(43); break;
                            case 52: states.push_back(43); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 51:
                    switch(s.token) {
                        case TokenType::Asterisk:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Asterisk, std::move(s.value));
                            states.push_back(38);
                            read_token = true;
                            break;
                        case TokenType::Plus:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Plus, std::move(s.value));
                            states.push_back(41);
                            read_token = true;
                            break;
                        case TokenType::OpenBrace:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::OpenBrace, std::move(s.value));
                            states.push_back(42);
                            read_token = true;
                            break;
                        case TokenType::Question:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Question, std::move(s.value));
                            states.push_back(39);
                            read_token = true;
                            break;
                        default:
                            // Reduce ReText: ReText TokenType.Pipe ReText
                            if (true) {
                                auto i3 = std::move(values.back());
                                values.pop_back();
                                states.pop_back();
                                auto i2 = std::move(values.back());
                                values.pop_back();
                                states.pop_back();
                                auto i1 = std::move(values.back());
                                values.pop_back();
                                states.pop_back();
                                 values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new OrReAst(davecommon::span(i1.ReText->Spn.begin, i3.ReText->Spn.end), std::move(i1.ReText), std::move(i3.ReText))));
                                read_token = false;
                                switch(states.back()) {
                                    case 27: states.push_back(36); break;
                                    case 35: states.push_back(52); break;
                                    case 36: states.push_back(43); break;
                                    case 40: states.push_back(51); break;
                                    case 43: states.push_back(43); break;
                                    case 51: states.push_back(43); break;
                                    case 52: states.push_back(43); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 52:
                    switch(s.token) {
                        case TokenType::CharClass:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::CharClass, std::move(s.value));
                            states.push_back(32);
                            read_token = true;
                            break;
                        case TokenType::Asterisk:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Asterisk, std::move(s.value));
                            states.push_back(38);
                            read_token = true;
                            break;
                        case TokenType::Question:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Question, std::move(s.value));
                            states.push_back(39);
                            read_token = true;
                            break;
                        case TokenType::Pipe:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Pipe, std::move(s.value));
                            states.push_back(40);
                            read_token = true;
                            break;
                        case TokenType::Plus:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Plus, std::move(s.value));
                            states.push_back(41);
                            read_token = true;
                            break;
                        case TokenType::Char:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Char, std::move(s.value));
                            states.push_back(34);
                            read_token = true;
                            break;
                        case TokenType::OpenBrace:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::OpenBrace, std::move(s.value));
                            states.push_back(42);
                            read_token = true;
                            break;
                        case TokenType::Dot:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Dot, std::move(s.value));
                            states.push_back(31);
                            read_token = true;
                            break;
                        case TokenType::CloseParenthesis:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::CloseParenthesis, std::move(s.value));
                            states.push_back(53);
                            read_token = true;
                            break;
                        case TokenType::OpenSquare:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::OpenSquare, std::move(s.value));
                            states.push_back(33);
                            read_token = true;
                            break;
                        case TokenType::OpenParenthesis:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::OpenParenthesis, std::move(s.value));
                            states.push_back(35);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::CharClass);
                                validTokens.push_back(TokenType::Asterisk);
                                validTokens.push_back(TokenType::Question);
                                validTokens.push_back(TokenType::Pipe);
                                validTokens.push_back(TokenType::Plus);
                                validTokens.push_back(TokenType::Char);
                                validTokens.push_back(TokenType::OpenBrace);
                                validTokens.push_back(TokenType::Dot);
                                validTokens.push_back(TokenType::CloseParenthesis);
                                validTokens.push_back(TokenType::OpenSquare);
                                validTokens.push_back(TokenType::OpenParenthesis);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 53:
                    // Reduce ReText: TokenType.OpenParenthesis ReText TokenType.CloseParenthesis
                    if (true) {
                        auto i3 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.push_back(std::move(i2));
                        read_token = false;
                        switch(states.back()) {
                            case 27: states.push_back(36); break;
                            case 35: states.push_back(52); break;
                            case 36: states.push_back(43); break;
                            case 40: states.push_back(51); break;
                            case 43: states.push_back(43); break;
                            case 51: states.push_back(43); break;
                            case 52: states.push_back(43); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 54:
                    switch(s.token) {
                        case TokenType::Char:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Char, std::move(s.value));
                            states.push_back(55);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Char);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 55:
                    switch(s.token) {
                        case TokenType::Hyphen:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Hyphen, std::move(s.value));
                            states.push_back(60);
                            read_token = true;
                            break;
                        default:
                            // Reduce CharRange: TokenType.Char
                            if (true) {
                                auto i1 = std::move(values.back());
                                values.pop_back();
                                states.pop_back();
                                 values.emplace_back(lexical_type::CharRange(), std::shared_ptr<CharSetAst>(new SingleCharAst(i1.tkn_span, AstToken<wchar_t>(i1.tkn_span, i1.tkn_value[0]))));
                                read_token = false;
                                switch(states.back()) {
                                    case 33: states.push_back(56); break;
                                    case 54: states.push_back(56); break;
                                    case 57: states.push_back(58); break;
                                    case 62: states.push_back(58); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 56:
                    // Reduce CharRanges: CharRange
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::CharRanges(), as_vector(std::move(i1.CharRange)));
                        read_token = false;
                        switch(states.back()) {
                            case 33: states.push_back(57); break;
                            case 54: states.push_back(62); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 57:
                    switch(s.token) {
                        case TokenType::Char:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Char, std::move(s.value));
                            states.push_back(55);
                            read_token = true;
                            break;
                        case TokenType::CloseSquare:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::CloseSquare, std::move(s.value));
                            states.push_back(59);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Char);
                                validTokens.push_back(TokenType::CloseSquare);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 58:
                    // Reduce CharRanges: CharRanges CharRange
                    if (true) {
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::CharRanges(), append_vector(std::move(i1.CharRanges), std::move(i2.CharRange)));
                        read_token = false;
                        switch(states.back()) {
                            case 33: states.push_back(57); break;
                            case 54: states.push_back(62); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 59:
                    // Reduce ReText: TokenType.OpenSquare CharRanges TokenType.CloseSquare
                    if (true) {
                        auto i3 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new CharRangesReAst(davecommon::span(i1.tkn_span.begin, i3.tkn_span.end), false, std::move(i2.CharRanges))));
                        read_token = false;
                        switch(states.back()) {
                            case 27: states.push_back(36); break;
                            case 35: states.push_back(52); break;
                            case 36: states.push_back(43); break;
                            case 40: states.push_back(51); break;
                            case 43: states.push_back(43); break;
                            case 51: states.push_back(43); break;
                            case 52: states.push_back(43); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 60:
                    switch(s.token) {
                        case TokenType::Char:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Char, std::move(s.value));
                            states.push_back(61);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Char);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 61:
                    // Reduce CharRange: TokenType.Char TokenType.Hyphen TokenType.Char
                    if (true) {
                        auto i3 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::CharRange(), std::shared_ptr<CharSetAst>(new CharRangeAst(davecommon::span(i1.tkn_span.begin, i3.tkn_span.end), AstToken<wchar_t>(i1.tkn_span, i1.tkn_value[0]), AstToken<wchar_t>(i3.tkn_span, i3.tkn_value[0]))));
                        read_token = false;
                        switch(states.back()) {
                            case 33: states.push_back(56); break;
                            case 54: states.push_back(56); break;
                            case 57: states.push_back(58); break;
                            case 62: states.push_back(58); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 62:
                    switch(s.token) {
                        case TokenType::Char:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Char, std::move(s.value));
                            states.push_back(55);
                            read_token = true;
                            break;
                        case TokenType::CloseSquare:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::CloseSquare, std::move(s.value));
                            states.push_back(63);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Char);
                                validTokens.push_back(TokenType::CloseSquare);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 63:
                    // Reduce ReText: TokenType.OpenSquare TokenType.Hat CharRanges TokenType.CloseSquare
                    if (true) {
                        auto i4 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i3 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new CharRangesReAst(davecommon::span(i1.tkn_span.begin, i4.tkn_span.end), true, std::move(i3.CharRanges))));
                        read_token = false;
                        switch(states.back()) {
                            case 27: states.push_back(36); break;
                            case 35: states.push_back(52); break;
                            case 36: states.push_back(43); break;
                            case 40: states.push_back(51); break;
                            case 43: states.push_back(43); break;
                            case 51: states.push_back(43); break;
                            case 52: states.push_back(43); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 64:
                    switch(s.token) {
                        case TokenType::OpenBrace:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::OpenBrace, std::move(s.value));
                            states.push_back(65);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::OpenBrace);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 65:
                    switch(s.token) {
                        case TokenType::Identifier:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Identifier, std::move(s.value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Identifier);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 66:
                    // Reduce EnumItems: Ident
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::EnumItems(), as_vector(std::move(i1.Ident)));
                        read_token = false;
                        switch(states.back()) {
                            case 65: states.push_back(67); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 67:
                    switch(s.token) {
                        case TokenType::Comma:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Comma, std::move(s.value));
                            states.push_back(68);
                            read_token = true;
                            break;
                        case TokenType::CloseBrace:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::CloseBrace, std::move(s.value));
                            states.push_back(69);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Comma);
                                validTokens.push_back(TokenType::CloseBrace);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 68:
                    switch(s.token) {
                        case TokenType::Identifier:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Identifier, std::move(s.value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Identifier);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 69:
                    switch(s.token) {
                        case TokenType::Semicolon:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Semicolon, std::move(s.value));
                            states.push_back(70);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Semicolon);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 70:
                    // Reduce NamespaceItem: TokenType.Enum Ident TokenType.OpenBrace EnumItems TokenType.CloseBrace TokenType.Semicolon
                    if (true) {
                        auto i6 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i5 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i4 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i3 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::NamespaceItem(), std::shared_ptr<NamespaceItemAst>(new EnumAst(davecommon::span(i1.tkn_span.begin, i6.tkn_span.end), std::move(i2.Ident), std::move(i4.EnumItems))));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(23); break;
                            case 20: states.push_back(103); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 71:
                    // Reduce EnumItems: EnumItems TokenType.Comma Ident
                    if (true) {
                        auto i3 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::EnumItems(), append_vector(std::move(i1.EnumItems), std::move(i3.Ident)));
                        read_token = false;
                        switch(states.back()) {
                            case 65: states.push_back(67); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 72:
                    switch(s.token) {
                        case TokenType::OpenBrace:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::OpenBrace, std::move(s.value));
                            states.push_back(73);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::OpenBrace);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 73:
                    switch(s.token) {
                        case TokenType::Include:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Include, std::move(s.value));
                            states.push_back(74);
                            read_token = true;
                            break;
                        case TokenType::ReStart:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::ReStart, std::move(s.value));
                            states.push_back(27);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Include);
                                validTokens.push_back(TokenType::ReStart);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 74:
                    switch(s.token) {
                        case TokenType::Identifier:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Identifier, std::move(s.value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Identifier);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 75:
                    // Reduce SetItems: SetItem
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::SetItems(), as_vector(std::move(i1.SetItem)));
                        read_token = false;
                        switch(states.back()) {
                            case 73: states.push_back(77); break;
                            case 107: states.push_back(108); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 76:
                    switch(s.token) {
                        case TokenType::Goto:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Goto, std::move(s.value));
                            states.push_back(81);
                            read_token = true;
                            break;
                        case TokenType::Return:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Return, std::move(s.value));
                            states.push_back(82);
                            read_token = true;
                            break;
                        case TokenType::ProducedBy:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::ProducedBy, std::move(s.value));
                            states.push_back(83);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Goto);
                                validTokens.push_back(TokenType::Return);
                                validTokens.push_back(TokenType::ProducedBy);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 77:
                    switch(s.token) {
                        case TokenType::ReStart:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::ReStart, std::move(s.value));
                            states.push_back(27);
                            read_token = true;
                            break;
                        case TokenType::Include:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Include, std::move(s.value));
                            states.push_back(74);
                            read_token = true;
                            break;
                        case TokenType::CloseBrace:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::CloseBrace, std::move(s.value));
                            states.push_back(79);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::ReStart);
                                validTokens.push_back(TokenType::Include);
                                validTokens.push_back(TokenType::CloseBrace);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 78:
                    // Reduce SetItems: SetItems SetItem
                    if (true) {
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::SetItems(), append_vector(std::move(i1.SetItems), std::move(i2.SetItem)));
                        read_token = false;
                        switch(states.back()) {
                            case 73: states.push_back(77); break;
                            case 107: states.push_back(108); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 79:
                    switch(s.token) {
                        case TokenType::Semicolon:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Semicolon, std::move(s.value));
                            states.push_back(80);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Semicolon);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 80:
                    // Reduce NamespaceItem: TokenType.Set Ident TokenType.OpenBrace SetItems TokenType.CloseBrace TokenType.Semicolon
                    if (true) {
                        auto i6 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i5 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i4 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i3 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::NamespaceItem(), std::shared_ptr<NamespaceItemAst>(new SetAst(davecommon::span(i1.tkn_span.begin, i6.tkn_span.end), std::move(i2.Ident), std::move(i4.SetItems))));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(23); break;
                            case 20: states.push_back(103); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 81:
                    switch(s.token) {
                        case TokenType::Identifier:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Identifier, std::move(s.value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Identifier);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 82:
                    switch(s.token) {
                        case TokenType::ProducedBy:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::ProducedBy, std::move(s.value));
                            states.push_back(87);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::ProducedBy);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 83:
                    switch(s.token) {
                        case TokenType::Identifier:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Identifier, std::move(s.value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Identifier);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 84:
                    switch(s.token) {
                        case TokenType::Identifier:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Identifier, std::move(s.value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Identifier);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 85:
                    switch(s.token) {
                        case TokenType::Semicolon:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Semicolon, std::move(s.value));
                            states.push_back(86);
                            read_token = true;
                            break;
                        case TokenType::Dot:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Dot, std::move(s.value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Semicolon);
                                validTokens.push_back(TokenType::Dot);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 86:
                    // Reduce SetItem: Re TokenType.ProducedBy Ident QName TokenType.Semicolon
                    if (true) {
                        auto i5 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i4 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i3 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::SetItem(), std::shared_ptr<SetItemAst>(new MatchDefinitionAst(davecommon::span(i1.Re->Spn.begin, i5.tkn_span.end), std::move(i1.Re), false, false, std::vector<AstToken<std::wstring>>(), std::move(i3.Ident), std::move(i4.QName))));
                        read_token = false;
                        switch(states.back()) {
                            case 73: states.push_back(75); break;
                            case 77: states.push_back(78); break;
                            case 107: states.push_back(75); break;
                            case 108: states.push_back(78); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 87:
                    switch(s.token) {
                        case TokenType::Identifier:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Identifier, std::move(s.value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Identifier);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 88:
                    switch(s.token) {
                        case TokenType::Identifier:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Identifier, std::move(s.value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Identifier);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 89:
                    switch(s.token) {
                        case TokenType::Semicolon:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Semicolon, std::move(s.value));
                            states.push_back(90);
                            read_token = true;
                            break;
                        case TokenType::Dot:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Dot, std::move(s.value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Semicolon);
                                validTokens.push_back(TokenType::Dot);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 90:
                    // Reduce SetItem: Re TokenType.Return TokenType.ProducedBy Ident QName TokenType.Semicolon
                    if (true) {
                        auto i6 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i5 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i4 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i3 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::SetItem(), std::shared_ptr<SetItemAst>(new MatchDefinitionAst(davecommon::span(i1.Re->Spn.begin, i6.tkn_span.end), std::move(i1.Re), true, false, std::vector<AstToken<std::wstring>>(), std::move(i4.Ident), std::move(i5.QName))));
                        read_token = false;
                        switch(states.back()) {
                            case 73: states.push_back(75); break;
                            case 77: states.push_back(78); break;
                            case 107: states.push_back(75); break;
                            case 108: states.push_back(78); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 91:
                    switch(s.token) {
                        case TokenType::ProducedBy:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::ProducedBy, std::move(s.value));
                            states.push_back(92);
                            read_token = true;
                            break;
                        case TokenType::Dot:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Dot, std::move(s.value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::ProducedBy);
                                validTokens.push_back(TokenType::Dot);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 92:
                    switch(s.token) {
                        case TokenType::Identifier:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Identifier, std::move(s.value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Identifier);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 93:
                    switch(s.token) {
                        case TokenType::Identifier:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Identifier, std::move(s.value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Identifier);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 94:
                    switch(s.token) {
                        case TokenType::Semicolon:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Semicolon, std::move(s.value));
                            states.push_back(95);
                            read_token = true;
                            break;
                        case TokenType::Dot:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Dot, std::move(s.value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Semicolon);
                                validTokens.push_back(TokenType::Dot);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 95:
                    // Reduce SetItem: Re TokenType.Goto QName TokenType.ProducedBy Ident QName TokenType.Semicolon
                    if (true) {
                        auto i7 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i6 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i5 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i4 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i3 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::SetItem(), std::shared_ptr<SetItemAst>(new MatchDefinitionAst(davecommon::span(i1.Re->Spn.begin, i7.tkn_span.end), std::move(i1.Re), false, true, std::move(i3.QName), std::move(i5.Ident), std::move(i6.QName))));
                        read_token = false;
                        switch(states.back()) {
                            case 73: states.push_back(75); break;
                            case 77: states.push_back(78); break;
                            case 107: states.push_back(75); break;
                            case 108: states.push_back(78); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 96:
                    switch(s.token) {
                        case TokenType::Goto:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Goto, std::move(s.value));
                            states.push_back(97);
                            read_token = true;
                            break;
                        case TokenType::Semicolon:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Semicolon, std::move(s.value));
                            states.push_back(98);
                            read_token = true;
                            break;
                        case TokenType::Return:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Return, std::move(s.value));
                            states.push_back(99);
                            read_token = true;
                            break;
                        case TokenType::Dot:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Dot, std::move(s.value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Goto);
                                validTokens.push_back(TokenType::Semicolon);
                                validTokens.push_back(TokenType::Return);
                                validTokens.push_back(TokenType::Dot);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 97:
                    switch(s.token) {
                        case TokenType::Identifier:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Identifier, std::move(s.value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Identifier);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 98:
                    // Reduce SetItem: TokenType.Include QName TokenType.Semicolon
                    if (true) {
                        auto i3 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::SetItem(), std::shared_ptr<SetItemAst>(new IncludeSetAst(davecommon::span(i1.tkn_span.begin, i3.tkn_span.end), std::move(i2.QName), false, false, std::vector<AstToken<std::wstring>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 73: states.push_back(75); break;
                            case 77: states.push_back(78); break;
                            case 107: states.push_back(75); break;
                            case 108: states.push_back(78); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 99:
                    switch(s.token) {
                        case TokenType::Semicolon:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Semicolon, std::move(s.value));
                            states.push_back(100);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Semicolon);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 100:
                    // Reduce SetItem: TokenType.Include QName TokenType.Return TokenType.Semicolon
                    if (true) {
                        auto i4 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i3 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::SetItem(), std::shared_ptr<SetItemAst>(new IncludeSetAst(davecommon::span(i1.tkn_span.begin, i4.tkn_span.end), std::move(i2.QName), true, false, std::vector<AstToken<std::wstring>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 73: states.push_back(75); break;
                            case 77: states.push_back(78); break;
                            case 107: states.push_back(75); break;
                            case 108: states.push_back(78); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 101:
                    switch(s.token) {
                        case TokenType::Semicolon:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Semicolon, std::move(s.value));
                            states.push_back(102);
                            read_token = true;
                            break;
                        case TokenType::Dot:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Dot, std::move(s.value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Semicolon);
                                validTokens.push_back(TokenType::Dot);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 102:
                    // Reduce SetItem: TokenType.Include QName TokenType.Goto QName TokenType.Semicolon
                    if (true) {
                        auto i5 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i4 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i3 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::SetItem(), std::shared_ptr<SetItemAst>(new IncludeSetAst(davecommon::span(i1.tkn_span.begin, i5.tkn_span.end), std::move(i2.QName), false, true, std::move(i4.QName))));
                        read_token = false;
                        switch(states.back()) {
                            case 73: states.push_back(75); break;
                            case 77: states.push_back(78); break;
                            case 107: states.push_back(75); break;
                            case 108: states.push_back(78); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 103:
                    // Reduce NamespaceItems: NamespaceItems NamespaceItem
                    if (true) {
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::NamespaceItems(), append_vector(std::move(i1.NamespaceItems), std::move(i2.NamespaceItem)));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(20); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 104:
                    switch(s.token) {
                        case TokenType::Semicolon:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Semicolon, std::move(s.value));
                            states.push_back(105);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Semicolon);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 105:
                    // Reduce DocumentItem: TokenType.Namespace QName TokenType.OpenBrace NamespaceItems TokenType.CloseBrace TokenType.Semicolon
                    if (true) {
                        auto i6 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i5 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i4 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i3 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::DocumentItem(), std::shared_ptr<DocumentAst>(new NamespaceAst(davecommon::span(i1.tkn_span.begin, i6.tkn_span.end), std::move(i2.QName), std::move(i4.NamespaceItems))));
                        read_token = false;
                        switch(states.back()) {
                            case 0: states.push_back(5); break;
                            case 1: states.push_back(111); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 106:
                    switch(s.token) {
                        case TokenType::OpenBrace:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::OpenBrace, std::move(s.value));
                            states.push_back(107);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::OpenBrace);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 107:
                    switch(s.token) {
                        case TokenType::Include:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Include, std::move(s.value));
                            states.push_back(74);
                            read_token = true;
                            break;
                        case TokenType::ReStart:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::ReStart, std::move(s.value));
                            states.push_back(27);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Include);
                                validTokens.push_back(TokenType::ReStart);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 108:
                    switch(s.token) {
                        case TokenType::ReStart:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::ReStart, std::move(s.value));
                            states.push_back(27);
                            read_token = true;
                            break;
                        case TokenType::Include:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Include, std::move(s.value));
                            states.push_back(74);
                            read_token = true;
                            break;
                        case TokenType::CloseBrace:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::CloseBrace, std::move(s.value));
                            states.push_back(109);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::ReStart);
                                validTokens.push_back(TokenType::Include);
                                validTokens.push_back(TokenType::CloseBrace);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 109:
                    switch(s.token) {
                        case TokenType::Semicolon:
                            values.emplace_back(davecommon::span(std::move(s.begin), std::move(s.end)), TokenType::Semicolon, std::move(s.value));
                            states.push_back(110);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<TokenType> validTokens;
                                validTokens.push_back(TokenType::Semicolon);
                                davecommon::log::error::UnexpectedToken(logger, cntr, s.begin, s.end, s.token, s.value, validTokens);
                                ok = false;
                            }
                            break;
                    }
                    break;
                case 110:
                    // Reduce NamespaceItem: TokenType.Automata Ident TokenType.OpenBrace SetItems TokenType.CloseBrace TokenType.Semicolon
                    if (true) {
                        auto i6 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i5 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i4 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i3 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::NamespaceItem(), std::shared_ptr<NamespaceItemAst>(new AutomataAst(davecommon::span(i1.tkn_span.begin, i6.tkn_span.end), std::move(i2.Ident), std::move(i4.SetItems))));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(23); break;
                            case 20: states.push_back(103); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 111:
                    // Reduce Document: Document DocumentItem
                    if (true) {
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::Document(), append_vector(std::move(i1.Document), std::move(i2.DocumentItem)));
                        read_token = false;
                        switch(states.back()) {
                            case 0: states.push_back(1); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
            }
        }
        return std::move(values.back().Document);
    }
}
