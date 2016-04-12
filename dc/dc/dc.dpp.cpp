#include <vector>
#include "dc.dpp.h"
#include "lexer.ds.lexer.h"
#include "lexer.ds.model.h"

namespace dc
{
    struct lexical_type {
        struct CharRange { };
        struct CharRanges { };
        struct Document { };
        struct DocumentItem { };
        struct Documentation { };
        struct EnumItem { };
        struct EnumItems { };
        struct Ident { };
        struct Metadata { };
        struct NamespaceItem { };
        struct NamespaceItems { };
        struct QName { };
        struct Re { };
        struct ReText { };
        struct SetItem { };
        struct SetItems { };
        struct Str { };
        struct TypeArgument { };
        struct TypeArguments { };
        struct TypeProperties { };
        struct TypeProperty { };
        struct TypeReference { };
        struct TypeReferences { };
    };
    struct lexical_value {
        std::wstring desc;
        dc::TokenType tkn_type;
        std::wstring tkn_value;
        span tkn_span;
         std::shared_ptr<CharSetAst> CharRange;
         std::vector<std::shared_ptr<CharSetAst>> CharRanges;
         std::vector<std::shared_ptr<DocumentAst>> Document;
         std::shared_ptr<DocumentAst> DocumentItem;
         std::vector<spantext> Documentation;
         std::shared_ptr<EnumItemAst> EnumItem;
         std::vector<std::shared_ptr<EnumItemAst>> EnumItems;
         spantext Ident;
         std::shared_ptr<AttrAndDoc> Metadata;
         std::shared_ptr<NamespaceItemAst> NamespaceItem;
         std::vector<std::shared_ptr<NamespaceItemAst>> NamespaceItems;
         symbolreference QName;
         std::shared_ptr<ReAst> Re;
         std::shared_ptr<ReAst> ReText;
         std::shared_ptr<SetItemAst> SetItem;
         std::vector<std::shared_ptr<SetItemAst>> SetItems;
         spantext Str;
         std::shared_ptr<TypeArgumentAst> TypeArgument;
         std::vector<std::shared_ptr<TypeArgumentAst>> TypeArguments;
         std::vector<std::shared_ptr<TypePropertyAst>> TypeProperties;
         std::shared_ptr<TypePropertyAst> TypeProperty;
         std::shared_ptr<TypeReferenceAst> TypeReference;
         std::vector<std::shared_ptr<TypeReferenceAst>> TypeReferences;
        lexical_value() { }
        lexical_value(span &&spn, const dc::TokenType _tkn_type, const std::wstring &_tkn_value)
        : desc(text(_tkn_type)), tkn_span(std::move(spn)), tkn_type(_tkn_type), tkn_value(_tkn_value)
        {}
        lexical_value(span &&spn, const dc::TokenType _tkn_type, std::wstring &&_tkn_value)
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
        lexical_value(const lexical_type::Documentation&,  std::vector<spantext>&& value)
        : desc(L"DOCUMENTATION"), Documentation(std::move(value))
        {}
        lexical_value(const lexical_type::EnumItem&,  std::shared_ptr<EnumItemAst>&& value)
        : desc(L"ENUMITEM"), EnumItem(std::move(value))
        {}
        lexical_value(const lexical_type::EnumItems&,  std::vector<std::shared_ptr<EnumItemAst>>&& value)
        : desc(L"ENUMITEMS"), EnumItems(std::move(value))
        {}
        lexical_value(const lexical_type::Ident&,  spantext&& value)
        : desc(L"IDENT"), Ident(std::move(value))
        {}
        lexical_value(const lexical_type::Metadata&,  std::shared_ptr<AttrAndDoc>&& value)
        : desc(L"METADATA"), Metadata(std::move(value))
        {}
        lexical_value(const lexical_type::NamespaceItem&,  std::shared_ptr<NamespaceItemAst>&& value)
        : desc(L"NAMESPACEITEM"), NamespaceItem(std::move(value))
        {}
        lexical_value(const lexical_type::NamespaceItems&,  std::vector<std::shared_ptr<NamespaceItemAst>>&& value)
        : desc(L"NAMESPACEITEMS"), NamespaceItems(std::move(value))
        {}
        lexical_value(const lexical_type::QName&,  symbolreference&& value)
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
        lexical_value(const lexical_type::Str&,  spantext&& value)
        : desc(L"STR"), Str(std::move(value))
        {}
        lexical_value(const lexical_type::TypeArgument&,  std::shared_ptr<TypeArgumentAst>&& value)
        : desc(L"TYPEARGUMENT"), TypeArgument(std::move(value))
        {}
        lexical_value(const lexical_type::TypeArguments&,  std::vector<std::shared_ptr<TypeArgumentAst>>&& value)
        : desc(L"TYPEARGUMENTS"), TypeArguments(std::move(value))
        {}
        lexical_value(const lexical_type::TypeProperties&,  std::vector<std::shared_ptr<TypePropertyAst>>&& value)
        : desc(L"TYPEPROPERTIES"), TypeProperties(std::move(value))
        {}
        lexical_value(const lexical_type::TypeProperty&,  std::shared_ptr<TypePropertyAst>&& value)
        : desc(L"TYPEPROPERTY"), TypeProperty(std::move(value))
        {}
        lexical_value(const lexical_type::TypeReference&,  std::shared_ptr<TypeReferenceAst>&& value)
        : desc(L"TYPEREFERENCE"), TypeReference(std::move(value))
        {}
        lexical_value(const lexical_type::TypeReferences&,  std::vector<std::shared_ptr<TypeReferenceAst>>&& value)
        : desc(L"TYPEREFERENCES"), TypeReferences(std::move(value))
        {}
    };

    auto parse(std::wistream &stm, const std::shared_ptr<container> &cntr, logger *logger, DocumentAstMutatingVisitor *processor, bool &ok) -> bool
    {
        std::vector<size_t> states;
        std::vector<lexical_value> values;
        states.push_back(0);
        bool read_token = true;
        dc::lexer lexer(stm);
        long start_line = 0, start_column = 0, end_line = 0, end_column = 0;
        std::wstring value;
        dc::TokenType token = dc::TokenType::Error;
        while(true) {
            if (read_token) {
                while(true) {
                    if (!lexer.try_read_next_token(start_line, start_column, end_line, end_column, value, token)) {
                        token = dc::TokenType::EOD;
                    }
                    if (token != dc::TokenType::Whitespace && token != dc::TokenType::Comment) break;
                }
            }
            switch(states.back()) {
                case 0:
                    switch(token) {
                        case dc::TokenType::Namespace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Namespace, std::move(value));
                            states.push_back(2);
                            read_token = true;
                            break;
                        case dc::TokenType::Set:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Set, std::move(value));
                            states.push_back(3);
                            read_token = true;
                            break;
                        case dc::TokenType::Import:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Import, std::move(value));
                            states.push_back(4);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Namespace);
                                validTokens.push_back(dc::TokenType::Set);
                                validTokens.push_back(dc::TokenType::Import);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 1:
                    switch(token) {
                        case dc::TokenType::Namespace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Namespace, std::move(value));
                            states.push_back(2);
                            read_token = true;
                            break;
                        case dc::TokenType::Set:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Set, std::move(value));
                            states.push_back(3);
                            read_token = true;
                            break;
                        case dc::TokenType::Import:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Import, std::move(value));
                            states.push_back(4);
                            read_token = true;
                            break;
                        case dc::TokenType::EOD:
                            return true;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Namespace);
                                validTokens.push_back(dc::TokenType::Set);
                                validTokens.push_back(dc::TokenType::Import);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 2:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 3:
                    switch(token) {
                        case dc::TokenType::Start:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Start, std::move(value));
                            states.push_back(9);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Start);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 4:
                    switch(token) {
                        case dc::TokenType::String:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::String, std::move(value));
                            states.push_back(6);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::String);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
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
                         values.emplace_back(); i1.DocumentItem->accept(i1.DocumentItem, processor); if(!ok) return false;
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
                         values.emplace_back(lexical_type::Str(), spantext(i1.tkn_span, get_str(std::move(i1.tkn_value))));
                        read_token = false;
                        switch(states.back()) {
                            case 4: states.push_back(7); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 7:
                    switch(token) {
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(8);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
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
                         values.emplace_back(lexical_type::DocumentItem(), std::shared_ptr<DocumentAst>(new ImportAst(span(i1.tkn_span.begin, i3.tkn_span.end), std::move(i2.Str))));
                        read_token = false;
                        switch(states.back()) {
                            case 0: states.push_back(5); break;
                            case 1: states.push_back(230); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 9:
                    switch(token) {
                        case dc::TokenType::Equals:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Equals, std::move(value));
                            states.push_back(10);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Equals);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 10:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
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
                         values.emplace_back(lexical_type::Ident(), spantext(i1.tkn_span, std::move(i1.tkn_value)));
                        read_token = false;
                        switch(states.back()) {
                            case 2: states.push_back(12); break;
                            case 10: states.push_back(12); break;
                            case 15: states.push_back(16); break;
                            case 22: states.push_back(216); break;
                            case 25: states.push_back(204); break;
                            case 26: states.push_back(194); break;
                            case 27: states.push_back(190); break;
                            case 31: states.push_back(119); break;
                            case 33: states.push_back(34); break;
                            case 36: states.push_back(12); break;
                            case 44: states.push_back(12); break;
                            case 46: states.push_back(47); break;
                            case 47: states.push_back(12); break;
                            case 50: states.push_back(51); break;
                            case 51: states.push_back(12); break;
                            case 55: states.push_back(56); break;
                            case 56: states.push_back(12); break;
                            case 59: states.push_back(12); break;
                            case 71: states.push_back(12); break;
                            case 95: states.push_back(12); break;
                            case 101: states.push_back(114); break;
                            case 102: states.push_back(109); break;
                            case 103: states.push_back(105); break;
                            case 120: states.push_back(124); break;
                            case 123: states.push_back(130); break;
                            case 126: states.push_back(124); break;
                            case 131: states.push_back(173); break;
                            case 133: states.push_back(134); break;
                            case 135: states.push_back(124); break;
                            case 139: states.push_back(12); break;
                            case 148: states.push_back(12); break;
                            case 149: states.push_back(162); break;
                            case 159: states.push_back(12); break;
                            case 165: states.push_back(166); break;
                            case 167: states.push_back(12); break;
                            case 171: states.push_back(12); break;
                            case 174: states.push_back(178); break;
                            case 175: states.push_back(12); break;
                            case 182: states.push_back(178); break;
                            case 184: states.push_back(12); break;
                            case 195: states.push_back(178); break;
                            case 196: states.push_back(12); break;
                            case 201: states.push_back(12); break;
                            case 209: states.push_back(12); break;
                            case 217: states.push_back(12); break;
                            case 218: states.push_back(178); break;
                            case 221: states.push_back(12); break;
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
                            case 36: states.push_back(94); break;
                            case 44: states.push_back(54); break;
                            case 47: states.push_back(48); break;
                            case 51: states.push_back(52); break;
                            case 56: states.push_back(57); break;
                            case 59: states.push_back(74); break;
                            case 71: states.push_back(74); break;
                            case 95: states.push_back(99); break;
                            case 139: states.push_back(141); break;
                            case 148: states.push_back(141); break;
                            case 159: states.push_back(141); break;
                            case 167: states.push_back(141); break;
                            case 171: states.push_back(141); break;
                            case 175: states.push_back(141); break;
                            case 184: states.push_back(141); break;
                            case 196: states.push_back(141); break;
                            case 201: states.push_back(141); break;
                            case 209: states.push_back(141); break;
                            case 217: states.push_back(141); break;
                            case 221: states.push_back(141); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 13:
                    switch(token) {
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(14);
                            read_token = true;
                            break;
                        case dc::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Dot, std::move(value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Semicolon);
                                validTokens.push_back(dc::TokenType::Dot);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
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
                         values.emplace_back(lexical_type::DocumentItem(), std::shared_ptr<DocumentAst>(new StartItemAst(span(i1.tkn_span.begin, i5.tkn_span.end), std::move(i4.QName))));
                        read_token = false;
                        switch(states.back()) {
                            case 0: states.push_back(5); break;
                            case 1: states.push_back(230); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 15:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
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
                            case 36: states.push_back(94); break;
                            case 44: states.push_back(54); break;
                            case 47: states.push_back(48); break;
                            case 51: states.push_back(52); break;
                            case 56: states.push_back(57); break;
                            case 59: states.push_back(74); break;
                            case 71: states.push_back(74); break;
                            case 95: states.push_back(99); break;
                            case 139: states.push_back(141); break;
                            case 148: states.push_back(141); break;
                            case 159: states.push_back(141); break;
                            case 167: states.push_back(141); break;
                            case 171: states.push_back(141); break;
                            case 175: states.push_back(141); break;
                            case 184: states.push_back(141); break;
                            case 196: states.push_back(141); break;
                            case 201: states.push_back(141); break;
                            case 209: states.push_back(141); break;
                            case 217: states.push_back(141); break;
                            case 221: states.push_back(141); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 17:
                    switch(token) {
                        case dc::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenBrace, std::move(value));
                            states.push_back(18);
                            read_token = true;
                            break;
                        case dc::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Dot, std::move(value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::OpenBrace);
                                validTokens.push_back(dc::TokenType::Dot);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 18:
                    switch(token) {
                        case dc::TokenType::Sealed:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Sealed, std::move(value));
                            states.push_back(19);
                            read_token = true;
                            break;
                        case dc::TokenType::Type:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Type, std::move(value));
                            states.push_back(20);
                            read_token = true;
                            break;
                        case dc::TokenType::Abstract:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Abstract, std::move(value));
                            states.push_back(21);
                            read_token = true;
                            break;
                        case dc::TokenType::Documentation:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Documentation, std::move(value));
                            states.push_back(24);
                            read_token = true;
                            break;
                        case dc::TokenType::Automata:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Automata, std::move(value));
                            states.push_back(25);
                            read_token = true;
                            break;
                        case dc::TokenType::Alias:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Alias, std::move(value));
                            states.push_back(26);
                            read_token = true;
                            break;
                        case dc::TokenType::Pattern:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Pattern, std::move(value));
                            states.push_back(27);
                            read_token = true;
                            break;
                        case dc::TokenType::Enum:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Enum, std::move(value));
                            states.push_back(31);
                            read_token = true;
                            break;
                        case dc::TokenType::Set:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Set, std::move(value));
                            states.push_back(33);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Sealed);
                                validTokens.push_back(dc::TokenType::Type);
                                validTokens.push_back(dc::TokenType::Abstract);
                                validTokens.push_back(dc::TokenType::Documentation);
                                validTokens.push_back(dc::TokenType::Automata);
                                validTokens.push_back(dc::TokenType::Alias);
                                validTokens.push_back(dc::TokenType::Pattern);
                                validTokens.push_back(dc::TokenType::Enum);
                                validTokens.push_back(dc::TokenType::Set);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 19:
                    switch(token) {
                        case dc::TokenType::Abstract:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Abstract, std::move(value));
                            states.push_back(227);
                            read_token = true;
                            break;
                        case dc::TokenType::Type:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Type, std::move(value));
                            states.push_back(228);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Abstract);
                                validTokens.push_back(dc::TokenType::Type);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 20:
                    // Reduce TypeProps: TokenType.Type
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::NamespaceItem(), std::shared_ptr<NamespaceItemAst>(new TypeAst(i1.tkn_span, std::vector<spantext>(), spantext(), std::vector<std::shared_ptr<TypeArgumentAst>>(), false, false, std::shared_ptr<TypeReferenceAst>(), std::vector<std::shared_ptr<TypePropertyAst>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(22); break;
                            case 28: states.push_back(22); break;
                            case 30: states.push_back(22); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 21:
                    switch(token) {
                        case dc::TokenType::Sealed:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Sealed, std::move(value));
                            states.push_back(224);
                            read_token = true;
                            break;
                        case dc::TokenType::Type:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Type, std::move(value));
                            states.push_back(225);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Sealed);
                                validTokens.push_back(dc::TokenType::Type);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 22:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 23:
                    switch(token) {
                        case dc::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenBrace, std::move(value));
                            states.push_back(209);
                            read_token = true;
                            break;
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(210);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::OpenBrace);
                                validTokens.push_back(dc::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 24:
                    // Reduce Documentation: TokenType.Documentation
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::Documentation(), as_vector(std::move(spantext(i1.tkn_span, std::move(i1.tkn_value)))));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(32); break;
                            case 28: states.push_back(32); break;
                            case 120: states.push_back(121); break;
                            case 126: states.push_back(121); break;
                            case 135: states.push_back(121); break;
                            case 139: states.push_back(121); break;
                            case 159: states.push_back(121); break;
                            case 209: states.push_back(121); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 25:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 26:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 27:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 28:
                    switch(token) {
                        case dc::TokenType::Type:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Type, std::move(value));
                            states.push_back(20);
                            read_token = true;
                            break;
                        case dc::TokenType::Abstract:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Abstract, std::move(value));
                            states.push_back(21);
                            read_token = true;
                            break;
                        case dc::TokenType::Documentation:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Documentation, std::move(value));
                            states.push_back(24);
                            read_token = true;
                            break;
                        case dc::TokenType::Automata:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Automata, std::move(value));
                            states.push_back(25);
                            read_token = true;
                            break;
                        case dc::TokenType::Set:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Set, std::move(value));
                            states.push_back(33);
                            read_token = true;
                            break;
                        case dc::TokenType::Alias:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Alias, std::move(value));
                            states.push_back(26);
                            read_token = true;
                            break;
                        case dc::TokenType::Pattern:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Pattern, std::move(value));
                            states.push_back(27);
                            read_token = true;
                            break;
                        case dc::TokenType::Enum:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Enum, std::move(value));
                            states.push_back(31);
                            read_token = true;
                            break;
                        case dc::TokenType::Sealed:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Sealed, std::move(value));
                            states.push_back(19);
                            read_token = true;
                            break;
                        case dc::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CloseBrace, std::move(value));
                            states.push_back(188);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Type);
                                validTokens.push_back(dc::TokenType::Abstract);
                                validTokens.push_back(dc::TokenType::Documentation);
                                validTokens.push_back(dc::TokenType::Automata);
                                validTokens.push_back(dc::TokenType::Set);
                                validTokens.push_back(dc::TokenType::Alias);
                                validTokens.push_back(dc::TokenType::Pattern);
                                validTokens.push_back(dc::TokenType::Enum);
                                validTokens.push_back(dc::TokenType::Sealed);
                                validTokens.push_back(dc::TokenType::CloseBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 29:
                    // Reduce NamespaceItems: NamespaceItem
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::NamespaceItems(), as_vector(std::move(i1.NamespaceItem)));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(28); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 30:
                    switch(token) {
                        case dc::TokenType::Sealed:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Sealed, std::move(value));
                            states.push_back(19);
                            read_token = true;
                            break;
                        case dc::TokenType::Type:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Type, std::move(value));
                            states.push_back(20);
                            read_token = true;
                            break;
                        case dc::TokenType::Alias:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Alias, std::move(value));
                            states.push_back(131);
                            read_token = true;
                            break;
                        case dc::TokenType::Abstract:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Abstract, std::move(value));
                            states.push_back(21);
                            read_token = true;
                            break;
                        case dc::TokenType::Enum:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Enum, std::move(value));
                            states.push_back(133);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Sealed);
                                validTokens.push_back(dc::TokenType::Type);
                                validTokens.push_back(dc::TokenType::Alias);
                                validTokens.push_back(dc::TokenType::Abstract);
                                validTokens.push_back(dc::TokenType::Enum);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 31:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 32:
                    switch(token) {
                        case dc::TokenType::Automata:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Automata, std::move(value));
                            states.push_back(101);
                            read_token = true;
                            break;
                        case dc::TokenType::Set:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Set, std::move(value));
                            states.push_back(102);
                            read_token = true;
                            break;
                        case dc::TokenType::Pattern:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Pattern, std::move(value));
                            states.push_back(103);
                            read_token = true;
                            break;
                        case dc::TokenType::Documentation:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Documentation, std::move(value));
                            states.push_back(104);
                            read_token = true;
                            break;
                        default:
                            // Reduce Metadata: Documentation
                            if (true) {
                                auto i1 = std::move(values.back());
                                values.pop_back();
                                states.pop_back();
                                 values.emplace_back(lexical_type::Metadata(), std::shared_ptr<AttrAndDoc>(new AttrAndDoc(span(i1.Documentation[0].spn().begin, i1.Documentation.back().spn().end), std::move(i1.Documentation))));
                                read_token = false;
                                switch(states.back()) {
                                    case 18: states.push_back(30); break;
                                    case 28: states.push_back(30); break;
                                    case 120: states.push_back(123); break;
                                    case 126: states.push_back(123); break;
                                    case 135: states.push_back(123); break;
                                    case 139: states.push_back(148); break;
                                    case 159: states.push_back(148); break;
                                    case 209: states.push_back(148); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 33:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 34:
                    switch(token) {
                        case dc::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenBrace, std::move(value));
                            states.push_back(35);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::OpenBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 35:
                    switch(token) {
                        case dc::TokenType::Include:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Include, std::move(value));
                            states.push_back(36);
                            read_token = true;
                            break;
                        case dc::TokenType::ReStart:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::ReStart, std::move(value));
                            states.push_back(37);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Include);
                                validTokens.push_back(dc::TokenType::ReStart);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 36:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 37:
                    switch(token) {
                        case dc::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenBrace, std::move(value));
                            states.push_back(59);
                            read_token = true;
                            break;
                        case dc::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Dot, std::move(value));
                            states.push_back(60);
                            read_token = true;
                            break;
                        case dc::TokenType::CharClass:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CharClass, std::move(value));
                            states.push_back(61);
                            read_token = true;
                            break;
                        case dc::TokenType::OpenSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenSquare, std::move(value));
                            states.push_back(62);
                            read_token = true;
                            break;
                        case dc::TokenType::Char:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Char, std::move(value));
                            states.push_back(63);
                            read_token = true;
                            break;
                        case dc::TokenType::OpenParenthesis:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenParenthesis, std::move(value));
                            states.push_back(64);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::OpenBrace);
                                validTokens.push_back(dc::TokenType::Dot);
                                validTokens.push_back(dc::TokenType::CharClass);
                                validTokens.push_back(dc::TokenType::OpenSquare);
                                validTokens.push_back(dc::TokenType::Char);
                                validTokens.push_back(dc::TokenType::OpenParenthesis);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 38:
                    // Reduce SetItems: SetItem
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::SetItems(), as_vector(std::move(i1.SetItem)));
                        read_token = false;
                        switch(states.back()) {
                            case 35: states.push_back(40); break;
                            case 110: states.push_back(111); break;
                            case 115: states.push_back(116); break;
                            case 205: states.push_back(206); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 39:
                    switch(token) {
                        case dc::TokenType::Goto:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Goto, std::move(value));
                            states.push_back(44);
                            read_token = true;
                            break;
                        case dc::TokenType::Return:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Return, std::move(value));
                            states.push_back(45);
                            read_token = true;
                            break;
                        case dc::TokenType::ProducedBy:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::ProducedBy, std::move(value));
                            states.push_back(46);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Goto);
                                validTokens.push_back(dc::TokenType::Return);
                                validTokens.push_back(dc::TokenType::ProducedBy);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 40:
                    switch(token) {
                        case dc::TokenType::ReStart:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::ReStart, std::move(value));
                            states.push_back(37);
                            read_token = true;
                            break;
                        case dc::TokenType::Include:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Include, std::move(value));
                            states.push_back(36);
                            read_token = true;
                            break;
                        case dc::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CloseBrace, std::move(value));
                            states.push_back(42);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::ReStart);
                                validTokens.push_back(dc::TokenType::Include);
                                validTokens.push_back(dc::TokenType::CloseBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 41:
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
                            case 35: states.push_back(40); break;
                            case 110: states.push_back(111); break;
                            case 115: states.push_back(116); break;
                            case 205: states.push_back(206); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 42:
                    switch(token) {
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(43);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 43:
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
                         values.emplace_back(lexical_type::NamespaceItem(), std::shared_ptr<NamespaceItemAst>(new SetAst(span(i1.tkn_span.begin, i6.tkn_span.end), std::vector<spantext>(), std::move(i2.Ident), std::move(i4.SetItems))));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(29); break;
                            case 28: states.push_back(187); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 44:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 45:
                    switch(token) {
                        case dc::TokenType::ProducedBy:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::ProducedBy, std::move(value));
                            states.push_back(50);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::ProducedBy);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 46:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 47:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 48:
                    switch(token) {
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(49);
                            read_token = true;
                            break;
                        case dc::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Dot, std::move(value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Semicolon);
                                validTokens.push_back(dc::TokenType::Dot);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 49:
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
                         values.emplace_back(lexical_type::SetItem(), std::shared_ptr<SetItemAst>(new MatchDefinitionAst(span(i1.Re->Spn.begin, i5.tkn_span.end), std::move(i1.Re), false, false, symbolreference(), std::move(i3.Ident), std::move(i4.QName))));
                        read_token = false;
                        switch(states.back()) {
                            case 35: states.push_back(38); break;
                            case 40: states.push_back(41); break;
                            case 110: states.push_back(38); break;
                            case 111: states.push_back(41); break;
                            case 115: states.push_back(38); break;
                            case 116: states.push_back(41); break;
                            case 205: states.push_back(38); break;
                            case 206: states.push_back(41); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 50:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 51:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 52:
                    switch(token) {
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(53);
                            read_token = true;
                            break;
                        case dc::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Dot, std::move(value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Semicolon);
                                validTokens.push_back(dc::TokenType::Dot);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 53:
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
                         values.emplace_back(lexical_type::SetItem(), std::shared_ptr<SetItemAst>(new MatchDefinitionAst(span(i1.Re->Spn.begin, i6.tkn_span.end), std::move(i1.Re), true, false, symbolreference(), std::move(i4.Ident), std::move(i5.QName))));
                        read_token = false;
                        switch(states.back()) {
                            case 35: states.push_back(38); break;
                            case 40: states.push_back(41); break;
                            case 110: states.push_back(38); break;
                            case 111: states.push_back(41); break;
                            case 115: states.push_back(38); break;
                            case 116: states.push_back(41); break;
                            case 205: states.push_back(38); break;
                            case 206: states.push_back(41); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 54:
                    switch(token) {
                        case dc::TokenType::ProducedBy:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::ProducedBy, std::move(value));
                            states.push_back(55);
                            read_token = true;
                            break;
                        case dc::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Dot, std::move(value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::ProducedBy);
                                validTokens.push_back(dc::TokenType::Dot);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 55:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 56:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 57:
                    switch(token) {
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(58);
                            read_token = true;
                            break;
                        case dc::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Dot, std::move(value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Semicolon);
                                validTokens.push_back(dc::TokenType::Dot);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 58:
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
                         values.emplace_back(lexical_type::SetItem(), std::shared_ptr<SetItemAst>(new MatchDefinitionAst(span(i1.Re->Spn.begin, i7.tkn_span.end), std::move(i1.Re), false, true, std::move(i3.QName), std::move(i5.Ident), std::move(i6.QName))));
                        read_token = false;
                        switch(states.back()) {
                            case 35: states.push_back(38); break;
                            case 40: states.push_back(41); break;
                            case 110: states.push_back(38); break;
                            case 111: states.push_back(41); break;
                            case 115: states.push_back(38); break;
                            case 116: states.push_back(41); break;
                            case 205: states.push_back(38); break;
                            case 206: states.push_back(41); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 59:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 60:
                    // Reduce ReText: TokenType.Dot
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new CharClassReAst(i1.tkn_span, spanvalue<CharClass>(i1.tkn_span, CharClass::AnyChar))));
                        read_token = false;
                        switch(states.back()) {
                            case 37: states.push_back(65); break;
                            case 64: states.push_back(81); break;
                            case 65: states.push_back(72); break;
                            case 69: states.push_back(80); break;
                            case 72: states.push_back(72); break;
                            case 80: states.push_back(72); break;
                            case 81: states.push_back(72); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 61:
                    // Reduce ReText: TokenType.CharClass
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new CharClassReAst(i1.tkn_span, spanvalue<CharClass>(i1.tkn_span, as_charclass(i1.tkn_value)))));
                        read_token = false;
                        switch(states.back()) {
                            case 37: states.push_back(65); break;
                            case 64: states.push_back(81); break;
                            case 65: states.push_back(72); break;
                            case 69: states.push_back(80); break;
                            case 72: states.push_back(72); break;
                            case 80: states.push_back(72); break;
                            case 81: states.push_back(72); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 62:
                    switch(token) {
                        case dc::TokenType::Hat:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Hat, std::move(value));
                            states.push_back(83);
                            read_token = true;
                            break;
                        case dc::TokenType::Char:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Char, std::move(value));
                            states.push_back(84);
                            read_token = true;
                            break;
                        case dc::TokenType::CharClass:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CharClass, std::move(value));
                            states.push_back(85);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Hat);
                                validTokens.push_back(dc::TokenType::Char);
                                validTokens.push_back(dc::TokenType::CharClass);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 63:
                    // Reduce ReText: TokenType.Char
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new CharReAst(i1.tkn_span, spanvalue<wchar_t>(i1.tkn_span, as_char(i1.tkn_value)))));
                        read_token = false;
                        switch(states.back()) {
                            case 37: states.push_back(65); break;
                            case 64: states.push_back(81); break;
                            case 65: states.push_back(72); break;
                            case 69: states.push_back(80); break;
                            case 72: states.push_back(72); break;
                            case 80: states.push_back(72); break;
                            case 81: states.push_back(72); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 64:
                    switch(token) {
                        case dc::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenBrace, std::move(value));
                            states.push_back(59);
                            read_token = true;
                            break;
                        case dc::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Dot, std::move(value));
                            states.push_back(60);
                            read_token = true;
                            break;
                        case dc::TokenType::CharClass:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CharClass, std::move(value));
                            states.push_back(61);
                            read_token = true;
                            break;
                        case dc::TokenType::OpenSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenSquare, std::move(value));
                            states.push_back(62);
                            read_token = true;
                            break;
                        case dc::TokenType::Char:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Char, std::move(value));
                            states.push_back(63);
                            read_token = true;
                            break;
                        case dc::TokenType::OpenParenthesis:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenParenthesis, std::move(value));
                            states.push_back(64);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::OpenBrace);
                                validTokens.push_back(dc::TokenType::Dot);
                                validTokens.push_back(dc::TokenType::CharClass);
                                validTokens.push_back(dc::TokenType::OpenSquare);
                                validTokens.push_back(dc::TokenType::Char);
                                validTokens.push_back(dc::TokenType::OpenParenthesis);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 65:
                    switch(token) {
                        case dc::TokenType::CharClass:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CharClass, std::move(value));
                            states.push_back(61);
                            read_token = true;
                            break;
                        case dc::TokenType::ReEnd:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::ReEnd, std::move(value));
                            states.push_back(66);
                            read_token = true;
                            break;
                        case dc::TokenType::Asterisk:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Asterisk, std::move(value));
                            states.push_back(67);
                            read_token = true;
                            break;
                        case dc::TokenType::Question:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Question, std::move(value));
                            states.push_back(68);
                            read_token = true;
                            break;
                        case dc::TokenType::Pipe:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Pipe, std::move(value));
                            states.push_back(69);
                            read_token = true;
                            break;
                        case dc::TokenType::Plus:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Plus, std::move(value));
                            states.push_back(70);
                            read_token = true;
                            break;
                        case dc::TokenType::Char:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Char, std::move(value));
                            states.push_back(63);
                            read_token = true;
                            break;
                        case dc::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenBrace, std::move(value));
                            states.push_back(71);
                            read_token = true;
                            break;
                        case dc::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Dot, std::move(value));
                            states.push_back(60);
                            read_token = true;
                            break;
                        case dc::TokenType::OpenSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenSquare, std::move(value));
                            states.push_back(62);
                            read_token = true;
                            break;
                        case dc::TokenType::OpenParenthesis:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenParenthesis, std::move(value));
                            states.push_back(64);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::CharClass);
                                validTokens.push_back(dc::TokenType::ReEnd);
                                validTokens.push_back(dc::TokenType::Asterisk);
                                validTokens.push_back(dc::TokenType::Question);
                                validTokens.push_back(dc::TokenType::Pipe);
                                validTokens.push_back(dc::TokenType::Plus);
                                validTokens.push_back(dc::TokenType::Char);
                                validTokens.push_back(dc::TokenType::OpenBrace);
                                validTokens.push_back(dc::TokenType::Dot);
                                validTokens.push_back(dc::TokenType::OpenSquare);
                                validTokens.push_back(dc::TokenType::OpenParenthesis);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 66:
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
                            case 35: states.push_back(39); break;
                            case 40: states.push_back(39); break;
                            case 106: states.push_back(107); break;
                            case 110: states.push_back(39); break;
                            case 111: states.push_back(39); break;
                            case 115: states.push_back(39); break;
                            case 116: states.push_back(39); break;
                            case 191: states.push_back(192); break;
                            case 205: states.push_back(39); break;
                            case 206: states.push_back(39); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 67:
                    // Reduce ReText: ReText TokenType.Asterisk
                    if (true) {
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new CardinalReAst(span(i1.ReText->Spn.begin, i2.tkn_span.end), std::move(i1.ReText), 0, -1)));
                        read_token = false;
                        switch(states.back()) {
                            case 37: states.push_back(65); break;
                            case 64: states.push_back(81); break;
                            case 65: states.push_back(72); break;
                            case 69: states.push_back(80); break;
                            case 72: states.push_back(72); break;
                            case 80: states.push_back(72); break;
                            case 81: states.push_back(72); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 68:
                    // Reduce ReText: ReText TokenType.Question
                    if (true) {
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new CardinalReAst(span(i1.ReText->Spn.begin, i2.tkn_span.end), std::move(i1.ReText), 0, 1)));
                        read_token = false;
                        switch(states.back()) {
                            case 37: states.push_back(65); break;
                            case 64: states.push_back(81); break;
                            case 65: states.push_back(72); break;
                            case 69: states.push_back(80); break;
                            case 72: states.push_back(72); break;
                            case 80: states.push_back(72); break;
                            case 81: states.push_back(72); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 69:
                    switch(token) {
                        case dc::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenBrace, std::move(value));
                            states.push_back(59);
                            read_token = true;
                            break;
                        case dc::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Dot, std::move(value));
                            states.push_back(60);
                            read_token = true;
                            break;
                        case dc::TokenType::CharClass:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CharClass, std::move(value));
                            states.push_back(61);
                            read_token = true;
                            break;
                        case dc::TokenType::OpenSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenSquare, std::move(value));
                            states.push_back(62);
                            read_token = true;
                            break;
                        case dc::TokenType::Char:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Char, std::move(value));
                            states.push_back(63);
                            read_token = true;
                            break;
                        case dc::TokenType::OpenParenthesis:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenParenthesis, std::move(value));
                            states.push_back(64);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::OpenBrace);
                                validTokens.push_back(dc::TokenType::Dot);
                                validTokens.push_back(dc::TokenType::CharClass);
                                validTokens.push_back(dc::TokenType::OpenSquare);
                                validTokens.push_back(dc::TokenType::Char);
                                validTokens.push_back(dc::TokenType::OpenParenthesis);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 70:
                    // Reduce ReText: ReText TokenType.Plus
                    if (true) {
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new CardinalReAst(span(i1.ReText->Spn.begin, i2.tkn_span.end), std::move(i1.ReText), 1, -1)));
                        read_token = false;
                        switch(states.back()) {
                            case 37: states.push_back(65); break;
                            case 64: states.push_back(81); break;
                            case 65: states.push_back(72); break;
                            case 69: states.push_back(80); break;
                            case 72: states.push_back(72); break;
                            case 80: states.push_back(72); break;
                            case 81: states.push_back(72); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 71:
                    switch(token) {
                        case dc::TokenType::Number:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Number, std::move(value));
                            states.push_back(73);
                            read_token = true;
                            break;
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Number);
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 72:
                    switch(token) {
                        case dc::TokenType::Asterisk:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Asterisk, std::move(value));
                            states.push_back(67);
                            read_token = true;
                            break;
                        case dc::TokenType::Pipe:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Pipe, std::move(value));
                            states.push_back(69);
                            read_token = true;
                            break;
                        case dc::TokenType::Plus:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Plus, std::move(value));
                            states.push_back(70);
                            read_token = true;
                            break;
                        case dc::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenBrace, std::move(value));
                            states.push_back(71);
                            read_token = true;
                            break;
                        case dc::TokenType::Question:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Question, std::move(value));
                            states.push_back(68);
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
                                 values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new ThenReAst(span(i1.ReText->Spn.begin, i2.ReText->Spn.end), std::move(i1.ReText), std::move(i2.ReText))));
                                read_token = false;
                                switch(states.back()) {
                                    case 37: states.push_back(65); break;
                                    case 64: states.push_back(81); break;
                                    case 65: states.push_back(72); break;
                                    case 69: states.push_back(80); break;
                                    case 72: states.push_back(72); break;
                                    case 80: states.push_back(72); break;
                                    case 81: states.push_back(72); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 73:
                    switch(token) {
                        case dc::TokenType::Comma:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Comma, std::move(value));
                            states.push_back(76);
                            read_token = true;
                            break;
                        case dc::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CloseBrace, std::move(value));
                            states.push_back(77);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Comma);
                                validTokens.push_back(dc::TokenType::CloseBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 74:
                    switch(token) {
                        case dc::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CloseBrace, std::move(value));
                            states.push_back(75);
                            read_token = true;
                            break;
                        case dc::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Dot, std::move(value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::CloseBrace);
                                validTokens.push_back(dc::TokenType::Dot);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 75:
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
                         values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new ReferenceReAst(span(i1.tkn_span.begin, i3.tkn_span.end), std::move(i2.QName))));
                        read_token = false;
                        switch(states.back()) {
                            case 37: states.push_back(65); break;
                            case 64: states.push_back(81); break;
                            case 65: states.push_back(72); break;
                            case 69: states.push_back(80); break;
                            case 72: states.push_back(72); break;
                            case 80: states.push_back(72); break;
                            case 81: states.push_back(72); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 76:
                    switch(token) {
                        case dc::TokenType::Number:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Number, std::move(value));
                            states.push_back(78);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Number);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 77:
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
                         values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new CardinalReAst(span(i1.tkn_span.begin, i4.tkn_span.end), std::move(i1.ReText), std::stoi(i3.tkn_value), std::stoi(i3.tkn_value))));
                        read_token = false;
                        switch(states.back()) {
                            case 37: states.push_back(65); break;
                            case 64: states.push_back(81); break;
                            case 65: states.push_back(72); break;
                            case 69: states.push_back(80); break;
                            case 72: states.push_back(72); break;
                            case 80: states.push_back(72); break;
                            case 81: states.push_back(72); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 78:
                    switch(token) {
                        case dc::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CloseBrace, std::move(value));
                            states.push_back(79);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::CloseBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 79:
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
                         values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new CardinalReAst(span(i1.tkn_span.begin, i6.tkn_span.end), std::move(i1.ReText), std::stoi(i3.tkn_value), std::stoi(i5.tkn_value))));
                        read_token = false;
                        switch(states.back()) {
                            case 37: states.push_back(65); break;
                            case 64: states.push_back(81); break;
                            case 65: states.push_back(72); break;
                            case 69: states.push_back(80); break;
                            case 72: states.push_back(72); break;
                            case 80: states.push_back(72); break;
                            case 81: states.push_back(72); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 80:
                    switch(token) {
                        case dc::TokenType::Asterisk:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Asterisk, std::move(value));
                            states.push_back(67);
                            read_token = true;
                            break;
                        case dc::TokenType::Plus:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Plus, std::move(value));
                            states.push_back(70);
                            read_token = true;
                            break;
                        case dc::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenBrace, std::move(value));
                            states.push_back(71);
                            read_token = true;
                            break;
                        case dc::TokenType::Question:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Question, std::move(value));
                            states.push_back(68);
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
                                 values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new OrReAst(span(i1.ReText->Spn.begin, i3.ReText->Spn.end), std::move(i1.ReText), std::move(i3.ReText))));
                                read_token = false;
                                switch(states.back()) {
                                    case 37: states.push_back(65); break;
                                    case 64: states.push_back(81); break;
                                    case 65: states.push_back(72); break;
                                    case 69: states.push_back(80); break;
                                    case 72: states.push_back(72); break;
                                    case 80: states.push_back(72); break;
                                    case 81: states.push_back(72); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 81:
                    switch(token) {
                        case dc::TokenType::CharClass:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CharClass, std::move(value));
                            states.push_back(61);
                            read_token = true;
                            break;
                        case dc::TokenType::Asterisk:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Asterisk, std::move(value));
                            states.push_back(67);
                            read_token = true;
                            break;
                        case dc::TokenType::Question:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Question, std::move(value));
                            states.push_back(68);
                            read_token = true;
                            break;
                        case dc::TokenType::Pipe:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Pipe, std::move(value));
                            states.push_back(69);
                            read_token = true;
                            break;
                        case dc::TokenType::Plus:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Plus, std::move(value));
                            states.push_back(70);
                            read_token = true;
                            break;
                        case dc::TokenType::Char:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Char, std::move(value));
                            states.push_back(63);
                            read_token = true;
                            break;
                        case dc::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenBrace, std::move(value));
                            states.push_back(71);
                            read_token = true;
                            break;
                        case dc::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Dot, std::move(value));
                            states.push_back(60);
                            read_token = true;
                            break;
                        case dc::TokenType::CloseParenthesis:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CloseParenthesis, std::move(value));
                            states.push_back(82);
                            read_token = true;
                            break;
                        case dc::TokenType::OpenSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenSquare, std::move(value));
                            states.push_back(62);
                            read_token = true;
                            break;
                        case dc::TokenType::OpenParenthesis:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenParenthesis, std::move(value));
                            states.push_back(64);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::CharClass);
                                validTokens.push_back(dc::TokenType::Asterisk);
                                validTokens.push_back(dc::TokenType::Question);
                                validTokens.push_back(dc::TokenType::Pipe);
                                validTokens.push_back(dc::TokenType::Plus);
                                validTokens.push_back(dc::TokenType::Char);
                                validTokens.push_back(dc::TokenType::OpenBrace);
                                validTokens.push_back(dc::TokenType::Dot);
                                validTokens.push_back(dc::TokenType::CloseParenthesis);
                                validTokens.push_back(dc::TokenType::OpenSquare);
                                validTokens.push_back(dc::TokenType::OpenParenthesis);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 82:
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
                            case 37: states.push_back(65); break;
                            case 64: states.push_back(81); break;
                            case 65: states.push_back(72); break;
                            case 69: states.push_back(80); break;
                            case 72: states.push_back(72); break;
                            case 80: states.push_back(72); break;
                            case 81: states.push_back(72); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 83:
                    switch(token) {
                        case dc::TokenType::Char:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Char, std::move(value));
                            states.push_back(84);
                            read_token = true;
                            break;
                        case dc::TokenType::CharClass:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CharClass, std::move(value));
                            states.push_back(85);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Char);
                                validTokens.push_back(dc::TokenType::CharClass);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 84:
                    switch(token) {
                        case dc::TokenType::Hyphen:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Hyphen, std::move(value));
                            states.push_back(90);
                            read_token = true;
                            break;
                        default:
                            // Reduce CharRange: TokenType.Char
                            if (true) {
                                auto i1 = std::move(values.back());
                                values.pop_back();
                                states.pop_back();
                                 values.emplace_back(lexical_type::CharRange(), std::shared_ptr<CharSetAst>(new SingleCharAst(i1.tkn_span, spanvalue<wchar_t>(i1.tkn_span, as_char(i1.tkn_value)))));
                                read_token = false;
                                switch(states.back()) {
                                    case 62: states.push_back(86); break;
                                    case 83: states.push_back(86); break;
                                    case 87: states.push_back(88); break;
                                    case 92: states.push_back(88); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 85:
                    // Reduce CharRange: TokenType.CharClass
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::CharRange(), std::shared_ptr<CharSetAst>(new CharClassRangeAst(i1.tkn_span, as_charclass(i1.tkn_value))));
                        read_token = false;
                        switch(states.back()) {
                            case 62: states.push_back(86); break;
                            case 83: states.push_back(86); break;
                            case 87: states.push_back(88); break;
                            case 92: states.push_back(88); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 86:
                    // Reduce CharRanges: CharRange
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::CharRanges(), as_vector(std::move(i1.CharRange)));
                        read_token = false;
                        switch(states.back()) {
                            case 62: states.push_back(87); break;
                            case 83: states.push_back(92); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 87:
                    switch(token) {
                        case dc::TokenType::Char:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Char, std::move(value));
                            states.push_back(84);
                            read_token = true;
                            break;
                        case dc::TokenType::CharClass:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CharClass, std::move(value));
                            states.push_back(85);
                            read_token = true;
                            break;
                        case dc::TokenType::CloseSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CloseSquare, std::move(value));
                            states.push_back(89);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Char);
                                validTokens.push_back(dc::TokenType::CharClass);
                                validTokens.push_back(dc::TokenType::CloseSquare);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 88:
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
                            case 62: states.push_back(87); break;
                            case 83: states.push_back(92); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 89:
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
                         values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new CharRangesReAst(span(i1.tkn_span.begin, i3.tkn_span.end), false, std::move(i2.CharRanges))));
                        read_token = false;
                        switch(states.back()) {
                            case 37: states.push_back(65); break;
                            case 64: states.push_back(81); break;
                            case 65: states.push_back(72); break;
                            case 69: states.push_back(80); break;
                            case 72: states.push_back(72); break;
                            case 80: states.push_back(72); break;
                            case 81: states.push_back(72); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 90:
                    switch(token) {
                        case dc::TokenType::Char:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Char, std::move(value));
                            states.push_back(91);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Char);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 91:
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
                         values.emplace_back(lexical_type::CharRange(), std::shared_ptr<CharSetAst>(new CharRangeAst(span(i1.tkn_span.begin, i3.tkn_span.end), spanvalue<wchar_t>(i1.tkn_span, as_char(i1.tkn_value)), spanvalue<wchar_t>(i3.tkn_span, as_char(i3.tkn_value)))));
                        read_token = false;
                        switch(states.back()) {
                            case 62: states.push_back(86); break;
                            case 83: states.push_back(86); break;
                            case 87: states.push_back(88); break;
                            case 92: states.push_back(88); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 92:
                    switch(token) {
                        case dc::TokenType::Char:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Char, std::move(value));
                            states.push_back(84);
                            read_token = true;
                            break;
                        case dc::TokenType::CharClass:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CharClass, std::move(value));
                            states.push_back(85);
                            read_token = true;
                            break;
                        case dc::TokenType::CloseSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CloseSquare, std::move(value));
                            states.push_back(93);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Char);
                                validTokens.push_back(dc::TokenType::CharClass);
                                validTokens.push_back(dc::TokenType::CloseSquare);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 93:
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
                         values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new CharRangesReAst(span(i1.tkn_span.begin, i4.tkn_span.end), true, std::move(i3.CharRanges))));
                        read_token = false;
                        switch(states.back()) {
                            case 37: states.push_back(65); break;
                            case 64: states.push_back(81); break;
                            case 65: states.push_back(72); break;
                            case 69: states.push_back(80); break;
                            case 72: states.push_back(72); break;
                            case 80: states.push_back(72); break;
                            case 81: states.push_back(72); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 94:
                    switch(token) {
                        case dc::TokenType::Goto:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Goto, std::move(value));
                            states.push_back(95);
                            read_token = true;
                            break;
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(96);
                            read_token = true;
                            break;
                        case dc::TokenType::Return:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Return, std::move(value));
                            states.push_back(97);
                            read_token = true;
                            break;
                        case dc::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Dot, std::move(value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Goto);
                                validTokens.push_back(dc::TokenType::Semicolon);
                                validTokens.push_back(dc::TokenType::Return);
                                validTokens.push_back(dc::TokenType::Dot);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 95:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 96:
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
                         values.emplace_back(lexical_type::SetItem(), std::shared_ptr<SetItemAst>(new IncludeSetAst(span(i1.tkn_span.begin, i3.tkn_span.end), std::move(i2.QName), false, false, symbolreference())));
                        read_token = false;
                        switch(states.back()) {
                            case 35: states.push_back(38); break;
                            case 40: states.push_back(41); break;
                            case 110: states.push_back(38); break;
                            case 111: states.push_back(41); break;
                            case 115: states.push_back(38); break;
                            case 116: states.push_back(41); break;
                            case 205: states.push_back(38); break;
                            case 206: states.push_back(41); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 97:
                    switch(token) {
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(98);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 98:
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
                         values.emplace_back(lexical_type::SetItem(), std::shared_ptr<SetItemAst>(new IncludeSetAst(span(i1.tkn_span.begin, i4.tkn_span.end), std::move(i2.QName), true, false, symbolreference())));
                        read_token = false;
                        switch(states.back()) {
                            case 35: states.push_back(38); break;
                            case 40: states.push_back(41); break;
                            case 110: states.push_back(38); break;
                            case 111: states.push_back(41); break;
                            case 115: states.push_back(38); break;
                            case 116: states.push_back(41); break;
                            case 205: states.push_back(38); break;
                            case 206: states.push_back(41); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 99:
                    switch(token) {
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(100);
                            read_token = true;
                            break;
                        case dc::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Dot, std::move(value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Semicolon);
                                validTokens.push_back(dc::TokenType::Dot);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 100:
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
                         values.emplace_back(lexical_type::SetItem(), std::shared_ptr<SetItemAst>(new IncludeSetAst(span(i1.tkn_span.begin, i5.tkn_span.end), std::move(i2.QName), false, true, std::move(i4.QName))));
                        read_token = false;
                        switch(states.back()) {
                            case 35: states.push_back(38); break;
                            case 40: states.push_back(41); break;
                            case 110: states.push_back(38); break;
                            case 111: states.push_back(41); break;
                            case 115: states.push_back(38); break;
                            case 116: states.push_back(41); break;
                            case 205: states.push_back(38); break;
                            case 206: states.push_back(41); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 101:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 102:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 103:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 104:
                    // Reduce Documentation: Documentation TokenType.Documentation
                    if (true) {
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::Documentation(), append_vector(std::move(i1.Documentation), std::move(spantext(i2.tkn_span, std::move(i2.tkn_value)))));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(32); break;
                            case 28: states.push_back(32); break;
                            case 120: states.push_back(121); break;
                            case 126: states.push_back(121); break;
                            case 135: states.push_back(121); break;
                            case 139: states.push_back(121); break;
                            case 159: states.push_back(121); break;
                            case 209: states.push_back(121); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 105:
                    switch(token) {
                        case dc::TokenType::Equals:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Equals, std::move(value));
                            states.push_back(106);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Equals);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 106:
                    switch(token) {
                        case dc::TokenType::ReStart:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::ReStart, std::move(value));
                            states.push_back(37);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::ReStart);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 107:
                    switch(token) {
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(108);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 108:
                    // Reduce NamespaceItem: Documentation TokenType.Pattern Ident TokenType.Equals Re TokenType.Semicolon
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
                         values.emplace_back(lexical_type::NamespaceItem(), std::shared_ptr<NamespaceItemAst>(new PatternAst(span(i2.tkn_span.begin, i6.tkn_span.end), std::move(i1.Documentation), std::move(i3.Ident), std::move(i5.Re))));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(29); break;
                            case 28: states.push_back(187); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 109:
                    switch(token) {
                        case dc::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenBrace, std::move(value));
                            states.push_back(110);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::OpenBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 110:
                    switch(token) {
                        case dc::TokenType::Include:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Include, std::move(value));
                            states.push_back(36);
                            read_token = true;
                            break;
                        case dc::TokenType::ReStart:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::ReStart, std::move(value));
                            states.push_back(37);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Include);
                                validTokens.push_back(dc::TokenType::ReStart);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 111:
                    switch(token) {
                        case dc::TokenType::ReStart:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::ReStart, std::move(value));
                            states.push_back(37);
                            read_token = true;
                            break;
                        case dc::TokenType::Include:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Include, std::move(value));
                            states.push_back(36);
                            read_token = true;
                            break;
                        case dc::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CloseBrace, std::move(value));
                            states.push_back(112);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::ReStart);
                                validTokens.push_back(dc::TokenType::Include);
                                validTokens.push_back(dc::TokenType::CloseBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 112:
                    switch(token) {
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(113);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 113:
                    // Reduce NamespaceItem: Documentation TokenType.Set Ident TokenType.OpenBrace SetItems TokenType.CloseBrace TokenType.Semicolon
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
                         values.emplace_back(lexical_type::NamespaceItem(), std::shared_ptr<NamespaceItemAst>(new SetAst(span(i2.tkn_span.begin, i7.tkn_span.end), std::move(i1.Documentation), std::move(i3.Ident), std::move(i5.SetItems))));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(29); break;
                            case 28: states.push_back(187); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 114:
                    switch(token) {
                        case dc::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenBrace, std::move(value));
                            states.push_back(115);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::OpenBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 115:
                    switch(token) {
                        case dc::TokenType::Include:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Include, std::move(value));
                            states.push_back(36);
                            read_token = true;
                            break;
                        case dc::TokenType::ReStart:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::ReStart, std::move(value));
                            states.push_back(37);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Include);
                                validTokens.push_back(dc::TokenType::ReStart);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 116:
                    switch(token) {
                        case dc::TokenType::ReStart:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::ReStart, std::move(value));
                            states.push_back(37);
                            read_token = true;
                            break;
                        case dc::TokenType::Include:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Include, std::move(value));
                            states.push_back(36);
                            read_token = true;
                            break;
                        case dc::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CloseBrace, std::move(value));
                            states.push_back(117);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::ReStart);
                                validTokens.push_back(dc::TokenType::Include);
                                validTokens.push_back(dc::TokenType::CloseBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 117:
                    switch(token) {
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(118);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 118:
                    // Reduce NamespaceItem: Documentation TokenType.Automata Ident TokenType.OpenBrace SetItems TokenType.CloseBrace TokenType.Semicolon
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
                         values.emplace_back(lexical_type::NamespaceItem(), std::shared_ptr<NamespaceItemAst>(new AutomataAst(span(i2.tkn_span.begin, i7.tkn_span.end), std::move(i1.Documentation), std::move(i3.Ident), std::move(i5.SetItems))));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(29); break;
                            case 28: states.push_back(187); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 119:
                    switch(token) {
                        case dc::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenBrace, std::move(value));
                            states.push_back(120);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::OpenBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 120:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case dc::TokenType::Documentation:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Documentation, std::move(value));
                            states.push_back(24);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                validTokens.push_back(dc::TokenType::Documentation);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 121:
                    switch(token) {
                        case dc::TokenType::Documentation:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Documentation, std::move(value));
                            states.push_back(104);
                            read_token = true;
                            break;
                        default:
                            // Reduce Metadata: Documentation
                            if (true) {
                                auto i1 = std::move(values.back());
                                values.pop_back();
                                states.pop_back();
                                 values.emplace_back(lexical_type::Metadata(), std::shared_ptr<AttrAndDoc>(new AttrAndDoc(span(i1.Documentation[0].spn().begin, i1.Documentation.back().spn().end), std::move(i1.Documentation))));
                                read_token = false;
                                switch(states.back()) {
                                    case 18: states.push_back(30); break;
                                    case 28: states.push_back(30); break;
                                    case 120: states.push_back(123); break;
                                    case 126: states.push_back(123); break;
                                    case 135: states.push_back(123); break;
                                    case 139: states.push_back(148); break;
                                    case 159: states.push_back(148); break;
                                    case 209: states.push_back(148); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 122:
                    // Reduce EnumItems: EnumItem
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::EnumItems(), as_vector(std::move(i1.EnumItem)));
                        read_token = false;
                        switch(states.back()) {
                            case 120: states.push_back(125); break;
                            case 135: states.push_back(136); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 123:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 124:
                    // Reduce EnumItem: Ident
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::EnumItem(), std::shared_ptr<EnumItemAst>(new EnumItemAst(i1.Ident.spn(), std::vector<spantext>(), std::move(i1.Ident))));
                        read_token = false;
                        switch(states.back()) {
                            case 120: states.push_back(122); break;
                            case 126: states.push_back(129); break;
                            case 135: states.push_back(122); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 125:
                    switch(token) {
                        case dc::TokenType::Comma:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Comma, std::move(value));
                            states.push_back(126);
                            read_token = true;
                            break;
                        case dc::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CloseBrace, std::move(value));
                            states.push_back(127);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Comma);
                                validTokens.push_back(dc::TokenType::CloseBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 126:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case dc::TokenType::Documentation:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Documentation, std::move(value));
                            states.push_back(24);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                validTokens.push_back(dc::TokenType::Documentation);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 127:
                    switch(token) {
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(128);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 128:
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
                         values.emplace_back(lexical_type::NamespaceItem(), std::shared_ptr<NamespaceItemAst>(new EnumAst(span(i1.tkn_span.begin, i6.tkn_span.end), std::vector<spantext>(), std::move(i2.Ident), std::move(i4.EnumItems))));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(29); break;
                            case 28: states.push_back(187); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 129:
                    // Reduce EnumItems: EnumItems TokenType.Comma EnumItem
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
                         values.emplace_back(lexical_type::EnumItems(), append_vector(std::move(i1.EnumItems), std::move(i3.EnumItem)));
                        read_token = false;
                        switch(states.back()) {
                            case 120: states.push_back(125); break;
                            case 135: states.push_back(136); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 130:
                    // Reduce EnumItem: Metadata Ident
                    if (true) {
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::EnumItem(), std::shared_ptr<EnumItemAst>(new EnumItemAst(i2.Ident.spn(), std::move(i1.Metadata->Documentation), std::move(i2.Ident))));
                        read_token = false;
                        switch(states.back()) {
                            case 120: states.push_back(122); break;
                            case 126: states.push_back(129); break;
                            case 135: states.push_back(122); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 131:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 132:
                    switch(token) {
                        case dc::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenBrace, std::move(value));
                            states.push_back(139);
                            read_token = true;
                            break;
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(140);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::OpenBrace);
                                validTokens.push_back(dc::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 133:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 134:
                    switch(token) {
                        case dc::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenBrace, std::move(value));
                            states.push_back(135);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::OpenBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 135:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case dc::TokenType::Documentation:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Documentation, std::move(value));
                            states.push_back(24);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                validTokens.push_back(dc::TokenType::Documentation);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 136:
                    switch(token) {
                        case dc::TokenType::Comma:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Comma, std::move(value));
                            states.push_back(126);
                            read_token = true;
                            break;
                        case dc::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CloseBrace, std::move(value));
                            states.push_back(137);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Comma);
                                validTokens.push_back(dc::TokenType::CloseBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 137:
                    switch(token) {
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(138);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 138:
                    // Reduce NamespaceItem: Metadata TokenType.Enum Ident TokenType.OpenBrace EnumItems TokenType.CloseBrace TokenType.Semicolon
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
                         values.emplace_back(lexical_type::NamespaceItem(), std::shared_ptr<NamespaceItemAst>(new EnumAst(span(i2.tkn_span.begin, i7.tkn_span.end), std::move(i1.Metadata->Documentation), std::move(i3.Ident), std::move(i5.EnumItems))));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(29); break;
                            case 28: states.push_back(187); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 139:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case dc::TokenType::FloatKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::FloatKeyword, std::move(value));
                            states.push_back(142);
                            read_token = true;
                            break;
                        case dc::TokenType::WString:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::WString, std::move(value));
                            states.push_back(143);
                            read_token = true;
                            break;
                        case dc::TokenType::Int64:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int64, std::move(value));
                            states.push_back(144);
                            read_token = true;
                            break;
                        case dc::TokenType::Int32:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int32, std::move(value));
                            states.push_back(145);
                            read_token = true;
                            break;
                        case dc::TokenType::DFloat:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::DFloat, std::move(value));
                            states.push_back(146);
                            read_token = true;
                            break;
                        case dc::TokenType::Int16:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int16, std::move(value));
                            states.push_back(147);
                            read_token = true;
                            break;
                        case dc::TokenType::Documentation:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Documentation, std::move(value));
                            states.push_back(24);
                            read_token = true;
                            break;
                        case dc::TokenType::StringKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::StringKeyword, std::move(value));
                            states.push_back(151);
                            read_token = true;
                            break;
                        case dc::TokenType::Int8:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int8, std::move(value));
                            states.push_back(152);
                            read_token = true;
                            break;
                        case dc::TokenType::DWord:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::DWord, std::move(value));
                            states.push_back(153);
                            read_token = true;
                            break;
                        case dc::TokenType::Word:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Word, std::move(value));
                            states.push_back(155);
                            read_token = true;
                            break;
                        case dc::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CloseBrace, std::move(value));
                            states.push_back(156);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                validTokens.push_back(dc::TokenType::FloatKeyword);
                                validTokens.push_back(dc::TokenType::WString);
                                validTokens.push_back(dc::TokenType::Int64);
                                validTokens.push_back(dc::TokenType::Int32);
                                validTokens.push_back(dc::TokenType::DFloat);
                                validTokens.push_back(dc::TokenType::Int16);
                                validTokens.push_back(dc::TokenType::Documentation);
                                validTokens.push_back(dc::TokenType::StringKeyword);
                                validTokens.push_back(dc::TokenType::Int8);
                                validTokens.push_back(dc::TokenType::DWord);
                                validTokens.push_back(dc::TokenType::Word);
                                validTokens.push_back(dc::TokenType::CloseBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 140:
                    // Reduce NamespaceItem: Metadata TypeDef TokenType.Semicolon
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
                         values.push_back(std::move(i2)); ((TypeAst*)values.back().NamespaceItem.get())->Documentation = std::move(i1.Metadata->Documentation);
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(29); break;
                            case 28: states.push_back(187); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 141:
                    switch(token) {
                        case dc::TokenType::OpenTriangle:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenTriangle, std::move(value));
                            states.push_back(167);
                            read_token = true;
                            break;
                        case dc::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Dot, std::move(value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Reduce TypeReference: QName
                            if (true) {
                                auto i1 = std::move(values.back());
                                values.pop_back();
                                states.pop_back();
                                 values.emplace_back(lexical_type::TypeReference(), std::shared_ptr<TypeReferenceAst>(new TypeReferenceAst(i1.QName.back().spn(), std::move(i1.QName), std::vector<std::shared_ptr<TypeReferenceAst>>())));
                                read_token = false;
                                switch(states.back()) {
                                    case 139: states.push_back(149); break;
                                    case 148: states.push_back(165); break;
                                    case 159: states.push_back(149); break;
                                    case 167: states.push_back(169); break;
                                    case 171: states.push_back(172); break;
                                    case 175: states.push_back(176); break;
                                    case 184: states.push_back(185); break;
                                    case 196: states.push_back(197); break;
                                    case 201: states.push_back(202); break;
                                    case 209: states.push_back(149); break;
                                    case 217: states.push_back(223); break;
                                    case 221: states.push_back(222); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 142:
                    // Reduce TypeReference: TokenType.FloatKeyword
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeReference(), std::shared_ptr<TypeReferenceAst>(new TypeReferenceAst(i1.tkn_span, get_system_symbolreference(L"Float"), std::vector<std::shared_ptr<TypeReferenceAst>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 139: states.push_back(149); break;
                            case 148: states.push_back(165); break;
                            case 159: states.push_back(149); break;
                            case 167: states.push_back(169); break;
                            case 171: states.push_back(172); break;
                            case 175: states.push_back(176); break;
                            case 184: states.push_back(185); break;
                            case 196: states.push_back(197); break;
                            case 201: states.push_back(202); break;
                            case 209: states.push_back(149); break;
                            case 217: states.push_back(223); break;
                            case 221: states.push_back(222); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 143:
                    // Reduce TypeReference: TokenType.WString
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeReference(), std::shared_ptr<TypeReferenceAst>(new TypeReferenceAst(i1.tkn_span, get_system_symbolreference(L"WString"), std::vector<std::shared_ptr<TypeReferenceAst>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 139: states.push_back(149); break;
                            case 148: states.push_back(165); break;
                            case 159: states.push_back(149); break;
                            case 167: states.push_back(169); break;
                            case 171: states.push_back(172); break;
                            case 175: states.push_back(176); break;
                            case 184: states.push_back(185); break;
                            case 196: states.push_back(197); break;
                            case 201: states.push_back(202); break;
                            case 209: states.push_back(149); break;
                            case 217: states.push_back(223); break;
                            case 221: states.push_back(222); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 144:
                    // Reduce TypeReference: TokenType.Int64
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeReference(), std::shared_ptr<TypeReferenceAst>(new TypeReferenceAst(i1.tkn_span, get_system_symbolreference(L"Int64"), std::vector<std::shared_ptr<TypeReferenceAst>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 139: states.push_back(149); break;
                            case 148: states.push_back(165); break;
                            case 159: states.push_back(149); break;
                            case 167: states.push_back(169); break;
                            case 171: states.push_back(172); break;
                            case 175: states.push_back(176); break;
                            case 184: states.push_back(185); break;
                            case 196: states.push_back(197); break;
                            case 201: states.push_back(202); break;
                            case 209: states.push_back(149); break;
                            case 217: states.push_back(223); break;
                            case 221: states.push_back(222); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 145:
                    // Reduce TypeReference: TokenType.Int32
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeReference(), std::shared_ptr<TypeReferenceAst>(new TypeReferenceAst(i1.tkn_span, get_system_symbolreference(L"Int32"), std::vector<std::shared_ptr<TypeReferenceAst>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 139: states.push_back(149); break;
                            case 148: states.push_back(165); break;
                            case 159: states.push_back(149); break;
                            case 167: states.push_back(169); break;
                            case 171: states.push_back(172); break;
                            case 175: states.push_back(176); break;
                            case 184: states.push_back(185); break;
                            case 196: states.push_back(197); break;
                            case 201: states.push_back(202); break;
                            case 209: states.push_back(149); break;
                            case 217: states.push_back(223); break;
                            case 221: states.push_back(222); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 146:
                    // Reduce TypeReference: TokenType.DFloat
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeReference(), std::shared_ptr<TypeReferenceAst>(new TypeReferenceAst(i1.tkn_span, get_system_symbolreference(L"DoubleFloat"), std::vector<std::shared_ptr<TypeReferenceAst>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 139: states.push_back(149); break;
                            case 148: states.push_back(165); break;
                            case 159: states.push_back(149); break;
                            case 167: states.push_back(169); break;
                            case 171: states.push_back(172); break;
                            case 175: states.push_back(176); break;
                            case 184: states.push_back(185); break;
                            case 196: states.push_back(197); break;
                            case 201: states.push_back(202); break;
                            case 209: states.push_back(149); break;
                            case 217: states.push_back(223); break;
                            case 221: states.push_back(222); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 147:
                    // Reduce TypeReference: TokenType.Int16
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeReference(), std::shared_ptr<TypeReferenceAst>(new TypeReferenceAst(i1.tkn_span, get_system_symbolreference(L"Int16"), std::vector<std::shared_ptr<TypeReferenceAst>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 139: states.push_back(149); break;
                            case 148: states.push_back(165); break;
                            case 159: states.push_back(149); break;
                            case 167: states.push_back(169); break;
                            case 171: states.push_back(172); break;
                            case 175: states.push_back(176); break;
                            case 184: states.push_back(185); break;
                            case 196: states.push_back(197); break;
                            case 201: states.push_back(202); break;
                            case 209: states.push_back(149); break;
                            case 217: states.push_back(223); break;
                            case 221: states.push_back(222); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 148:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case dc::TokenType::Int16:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int16, std::move(value));
                            states.push_back(147);
                            read_token = true;
                            break;
                        case dc::TokenType::DFloat:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::DFloat, std::move(value));
                            states.push_back(146);
                            read_token = true;
                            break;
                        case dc::TokenType::Int8:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int8, std::move(value));
                            states.push_back(152);
                            read_token = true;
                            break;
                        case dc::TokenType::StringKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::StringKeyword, std::move(value));
                            states.push_back(151);
                            read_token = true;
                            break;
                        case dc::TokenType::Int64:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int64, std::move(value));
                            states.push_back(144);
                            read_token = true;
                            break;
                        case dc::TokenType::Int32:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int32, std::move(value));
                            states.push_back(145);
                            read_token = true;
                            break;
                        case dc::TokenType::FloatKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::FloatKeyword, std::move(value));
                            states.push_back(142);
                            read_token = true;
                            break;
                        case dc::TokenType::DWord:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::DWord, std::move(value));
                            states.push_back(153);
                            read_token = true;
                            break;
                        case dc::TokenType::Word:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Word, std::move(value));
                            states.push_back(155);
                            read_token = true;
                            break;
                        case dc::TokenType::WString:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::WString, std::move(value));
                            states.push_back(143);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                validTokens.push_back(dc::TokenType::Int16);
                                validTokens.push_back(dc::TokenType::DFloat);
                                validTokens.push_back(dc::TokenType::Int8);
                                validTokens.push_back(dc::TokenType::StringKeyword);
                                validTokens.push_back(dc::TokenType::Int64);
                                validTokens.push_back(dc::TokenType::Int32);
                                validTokens.push_back(dc::TokenType::FloatKeyword);
                                validTokens.push_back(dc::TokenType::DWord);
                                validTokens.push_back(dc::TokenType::Word);
                                validTokens.push_back(dc::TokenType::WString);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 149:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case dc::TokenType::OpenSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenSquare, std::move(value));
                            states.push_back(163);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                validTokens.push_back(dc::TokenType::OpenSquare);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 150:
                    // Reduce TypeProperties: TypeProperty
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeProperties(), as_vector(std::move(i1.TypeProperty)));
                        read_token = false;
                        switch(states.back()) {
                            case 139: states.push_back(154); break;
                            case 209: states.push_back(211); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 151:
                    // Reduce TypeReference: TokenType.StringKeyword
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeReference(), std::shared_ptr<TypeReferenceAst>(new TypeReferenceAst(i1.tkn_span, get_system_symbolreference(L"String"), std::vector<std::shared_ptr<TypeReferenceAst>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 139: states.push_back(149); break;
                            case 148: states.push_back(165); break;
                            case 159: states.push_back(149); break;
                            case 167: states.push_back(169); break;
                            case 171: states.push_back(172); break;
                            case 175: states.push_back(176); break;
                            case 184: states.push_back(185); break;
                            case 196: states.push_back(197); break;
                            case 201: states.push_back(202); break;
                            case 209: states.push_back(149); break;
                            case 217: states.push_back(223); break;
                            case 221: states.push_back(222); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 152:
                    // Reduce TypeReference: TokenType.Int8
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeReference(), std::shared_ptr<TypeReferenceAst>(new TypeReferenceAst(i1.tkn_span, get_system_symbolreference(L"Int8"), std::vector<std::shared_ptr<TypeReferenceAst>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 139: states.push_back(149); break;
                            case 148: states.push_back(165); break;
                            case 159: states.push_back(149); break;
                            case 167: states.push_back(169); break;
                            case 171: states.push_back(172); break;
                            case 175: states.push_back(176); break;
                            case 184: states.push_back(185); break;
                            case 196: states.push_back(197); break;
                            case 201: states.push_back(202); break;
                            case 209: states.push_back(149); break;
                            case 217: states.push_back(223); break;
                            case 221: states.push_back(222); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 153:
                    // Reduce TypeReference: TokenType.DWord
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeReference(), std::shared_ptr<TypeReferenceAst>(new TypeReferenceAst(i1.tkn_span, get_system_symbolreference(L"DoubleWord"), std::vector<std::shared_ptr<TypeReferenceAst>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 139: states.push_back(149); break;
                            case 148: states.push_back(165); break;
                            case 159: states.push_back(149); break;
                            case 167: states.push_back(169); break;
                            case 171: states.push_back(172); break;
                            case 175: states.push_back(176); break;
                            case 184: states.push_back(185); break;
                            case 196: states.push_back(197); break;
                            case 201: states.push_back(202); break;
                            case 209: states.push_back(149); break;
                            case 217: states.push_back(223); break;
                            case 221: states.push_back(222); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 154:
                    switch(token) {
                        case dc::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CloseBrace, std::move(value));
                            states.push_back(158);
                            read_token = true;
                            break;
                        case dc::TokenType::Comma:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Comma, std::move(value));
                            states.push_back(159);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::CloseBrace);
                                validTokens.push_back(dc::TokenType::Comma);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 155:
                    // Reduce TypeReference: TokenType.Word
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeReference(), std::shared_ptr<TypeReferenceAst>(new TypeReferenceAst(i1.tkn_span, get_system_symbolreference(L"Word"), std::vector<std::shared_ptr<TypeReferenceAst>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 139: states.push_back(149); break;
                            case 148: states.push_back(165); break;
                            case 159: states.push_back(149); break;
                            case 167: states.push_back(169); break;
                            case 171: states.push_back(172); break;
                            case 175: states.push_back(176); break;
                            case 184: states.push_back(185); break;
                            case 196: states.push_back(197); break;
                            case 201: states.push_back(202); break;
                            case 209: states.push_back(149); break;
                            case 217: states.push_back(223); break;
                            case 221: states.push_back(222); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 156:
                    switch(token) {
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(157);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 157:
                    // Reduce NamespaceItem: Metadata TypeDef TokenType.OpenBrace TokenType.CloseBrace TokenType.Semicolon
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
                         values.push_back(std::move(i2)); ((TypeAst*)values.back().NamespaceItem.get())->Documentation = std::move(i1.Metadata->Documentation);
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(29); break;
                            case 28: states.push_back(187); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 158:
                    switch(token) {
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(161);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 159:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case dc::TokenType::FloatKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::FloatKeyword, std::move(value));
                            states.push_back(142);
                            read_token = true;
                            break;
                        case dc::TokenType::WString:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::WString, std::move(value));
                            states.push_back(143);
                            read_token = true;
                            break;
                        case dc::TokenType::Int64:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int64, std::move(value));
                            states.push_back(144);
                            read_token = true;
                            break;
                        case dc::TokenType::Int32:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int32, std::move(value));
                            states.push_back(145);
                            read_token = true;
                            break;
                        case dc::TokenType::DFloat:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::DFloat, std::move(value));
                            states.push_back(146);
                            read_token = true;
                            break;
                        case dc::TokenType::Int16:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int16, std::move(value));
                            states.push_back(147);
                            read_token = true;
                            break;
                        case dc::TokenType::StringKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::StringKeyword, std::move(value));
                            states.push_back(151);
                            read_token = true;
                            break;
                        case dc::TokenType::Int8:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int8, std::move(value));
                            states.push_back(152);
                            read_token = true;
                            break;
                        case dc::TokenType::DWord:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::DWord, std::move(value));
                            states.push_back(153);
                            read_token = true;
                            break;
                        case dc::TokenType::Documentation:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Documentation, std::move(value));
                            states.push_back(24);
                            read_token = true;
                            break;
                        case dc::TokenType::Word:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Word, std::move(value));
                            states.push_back(155);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                validTokens.push_back(dc::TokenType::FloatKeyword);
                                validTokens.push_back(dc::TokenType::WString);
                                validTokens.push_back(dc::TokenType::Int64);
                                validTokens.push_back(dc::TokenType::Int32);
                                validTokens.push_back(dc::TokenType::DFloat);
                                validTokens.push_back(dc::TokenType::Int16);
                                validTokens.push_back(dc::TokenType::StringKeyword);
                                validTokens.push_back(dc::TokenType::Int8);
                                validTokens.push_back(dc::TokenType::DWord);
                                validTokens.push_back(dc::TokenType::Documentation);
                                validTokens.push_back(dc::TokenType::Word);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 160:
                    // Reduce TypeProperties: TypeProperties TokenType.Comma TypeProperty
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
                         values.emplace_back(lexical_type::TypeProperties(), append_vector(std::move(i1.TypeProperties), std::move(i3.TypeProperty)));
                        read_token = false;
                        switch(states.back()) {
                            case 139: states.push_back(154); break;
                            case 209: states.push_back(211); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 161:
                    // Reduce NamespaceItem: Metadata TypeDef TokenType.OpenBrace TypeProperties TokenType.CloseBrace TokenType.Semicolon
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
                         values.push_back(std::move(i2)); ((TypeAst*)values.back().NamespaceItem.get())->Documentation = std::move(i1.Metadata->Documentation); ((TypeAst*)values.back().NamespaceItem.get())->Properties = std::move(i4.TypeProperties);
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(29); break;
                            case 28: states.push_back(187); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 162:
                    // Reduce TypeProperty: TypeReference Ident
                    if (true) {
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeProperty(), std::shared_ptr<TypePropertyAst>(new TypePropertyAst(span(i1.TypeReference->Spn.begin, i2.Ident.spn().end), std::vector<spantext>(), std::move(i1.TypeReference), std::move(i2.Ident))));
                        read_token = false;
                        switch(states.back()) {
                            case 139: states.push_back(150); break;
                            case 159: states.push_back(160); break;
                            case 209: states.push_back(150); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 163:
                    switch(token) {
                        case dc::TokenType::CloseSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CloseSquare, std::move(value));
                            states.push_back(164);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::CloseSquare);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 164:
                    // Reduce TypeReference: TypeReference TokenType.OpenSquare TokenType.CloseSquare
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
                         values.emplace_back(lexical_type::TypeReference(), std::shared_ptr<TypeReferenceAst>(new TypeReferenceAst(span(i1.TypeReference->Spn.begin, i3.tkn_span.end), get_system_symbolreference(L"Collection"), as_vector(std::move(i1.TypeReference)))));
                        read_token = false;
                        switch(states.back()) {
                            case 139: states.push_back(149); break;
                            case 148: states.push_back(165); break;
                            case 159: states.push_back(149); break;
                            case 167: states.push_back(169); break;
                            case 171: states.push_back(172); break;
                            case 175: states.push_back(176); break;
                            case 184: states.push_back(185); break;
                            case 196: states.push_back(197); break;
                            case 201: states.push_back(202); break;
                            case 209: states.push_back(149); break;
                            case 217: states.push_back(223); break;
                            case 221: states.push_back(222); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 165:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case dc::TokenType::OpenSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenSquare, std::move(value));
                            states.push_back(163);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                validTokens.push_back(dc::TokenType::OpenSquare);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 166:
                    // Reduce TypeProperty: Metadata TypeReference Ident
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
                         values.emplace_back(lexical_type::TypeProperty(), std::shared_ptr<TypePropertyAst>(new TypePropertyAst(span(i2.TypeReference->Spn.begin, i3.Ident.spn().end), std::move(i1.Metadata->Documentation), std::move(i2.TypeReference), std::move(i3.Ident))));
                        read_token = false;
                        switch(states.back()) {
                            case 139: states.push_back(150); break;
                            case 159: states.push_back(160); break;
                            case 209: states.push_back(150); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 167:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case dc::TokenType::Int8:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int8, std::move(value));
                            states.push_back(152);
                            read_token = true;
                            break;
                        case dc::TokenType::StringKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::StringKeyword, std::move(value));
                            states.push_back(151);
                            read_token = true;
                            break;
                        case dc::TokenType::Int64:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int64, std::move(value));
                            states.push_back(144);
                            read_token = true;
                            break;
                        case dc::TokenType::Int32:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int32, std::move(value));
                            states.push_back(145);
                            read_token = true;
                            break;
                        case dc::TokenType::FloatKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::FloatKeyword, std::move(value));
                            states.push_back(142);
                            read_token = true;
                            break;
                        case dc::TokenType::DFloat:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::DFloat, std::move(value));
                            states.push_back(146);
                            read_token = true;
                            break;
                        case dc::TokenType::Int16:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int16, std::move(value));
                            states.push_back(147);
                            read_token = true;
                            break;
                        case dc::TokenType::DWord:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::DWord, std::move(value));
                            states.push_back(153);
                            read_token = true;
                            break;
                        case dc::TokenType::Word:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Word, std::move(value));
                            states.push_back(155);
                            read_token = true;
                            break;
                        case dc::TokenType::WString:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::WString, std::move(value));
                            states.push_back(143);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                validTokens.push_back(dc::TokenType::Int8);
                                validTokens.push_back(dc::TokenType::StringKeyword);
                                validTokens.push_back(dc::TokenType::Int64);
                                validTokens.push_back(dc::TokenType::Int32);
                                validTokens.push_back(dc::TokenType::FloatKeyword);
                                validTokens.push_back(dc::TokenType::DFloat);
                                validTokens.push_back(dc::TokenType::Int16);
                                validTokens.push_back(dc::TokenType::DWord);
                                validTokens.push_back(dc::TokenType::Word);
                                validTokens.push_back(dc::TokenType::WString);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 168:
                    switch(token) {
                        case dc::TokenType::CloseTriangle:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CloseTriangle, std::move(value));
                            states.push_back(170);
                            read_token = true;
                            break;
                        case dc::TokenType::Comma:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Comma, std::move(value));
                            states.push_back(171);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::CloseTriangle);
                                validTokens.push_back(dc::TokenType::Comma);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 169:
                    switch(token) {
                        case dc::TokenType::OpenSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenSquare, std::move(value));
                            states.push_back(163);
                            read_token = true;
                            break;
                        default:
                            // Reduce TypeReferences: TypeReference
                            if (true) {
                                auto i1 = std::move(values.back());
                                values.pop_back();
                                states.pop_back();
                                 values.emplace_back(lexical_type::TypeReferences(), as_vector(std::move(i1.TypeReference)));
                                read_token = false;
                                switch(states.back()) {
                                    case 167: states.push_back(168); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 170:
                    // Reduce TypeReference: QName TokenType.OpenTriangle TypeReferences TokenType.CloseTriangle
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
                         values.emplace_back(lexical_type::TypeReference(), std::shared_ptr<TypeReferenceAst>(new TypeReferenceAst(i1.QName.back().spn(), std::move(i1.QName), std::move(i3.TypeReferences))));
                        read_token = false;
                        switch(states.back()) {
                            case 139: states.push_back(149); break;
                            case 148: states.push_back(165); break;
                            case 159: states.push_back(149); break;
                            case 167: states.push_back(169); break;
                            case 171: states.push_back(172); break;
                            case 175: states.push_back(176); break;
                            case 184: states.push_back(185); break;
                            case 196: states.push_back(197); break;
                            case 201: states.push_back(202); break;
                            case 209: states.push_back(149); break;
                            case 217: states.push_back(223); break;
                            case 221: states.push_back(222); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 171:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case dc::TokenType::Int16:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int16, std::move(value));
                            states.push_back(147);
                            read_token = true;
                            break;
                        case dc::TokenType::DFloat:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::DFloat, std::move(value));
                            states.push_back(146);
                            read_token = true;
                            break;
                        case dc::TokenType::Int8:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int8, std::move(value));
                            states.push_back(152);
                            read_token = true;
                            break;
                        case dc::TokenType::StringKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::StringKeyword, std::move(value));
                            states.push_back(151);
                            read_token = true;
                            break;
                        case dc::TokenType::Int64:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int64, std::move(value));
                            states.push_back(144);
                            read_token = true;
                            break;
                        case dc::TokenType::Int32:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int32, std::move(value));
                            states.push_back(145);
                            read_token = true;
                            break;
                        case dc::TokenType::FloatKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::FloatKeyword, std::move(value));
                            states.push_back(142);
                            read_token = true;
                            break;
                        case dc::TokenType::DWord:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::DWord, std::move(value));
                            states.push_back(153);
                            read_token = true;
                            break;
                        case dc::TokenType::Word:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Word, std::move(value));
                            states.push_back(155);
                            read_token = true;
                            break;
                        case dc::TokenType::WString:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::WString, std::move(value));
                            states.push_back(143);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                validTokens.push_back(dc::TokenType::Int16);
                                validTokens.push_back(dc::TokenType::DFloat);
                                validTokens.push_back(dc::TokenType::Int8);
                                validTokens.push_back(dc::TokenType::StringKeyword);
                                validTokens.push_back(dc::TokenType::Int64);
                                validTokens.push_back(dc::TokenType::Int32);
                                validTokens.push_back(dc::TokenType::FloatKeyword);
                                validTokens.push_back(dc::TokenType::DWord);
                                validTokens.push_back(dc::TokenType::Word);
                                validTokens.push_back(dc::TokenType::WString);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 172:
                    switch(token) {
                        case dc::TokenType::OpenSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenSquare, std::move(value));
                            states.push_back(163);
                            read_token = true;
                            break;
                        default:
                            // Reduce TypeReferences: TypeReferences TokenType.Comma TypeReference
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
                                 values.emplace_back(lexical_type::TypeReferences(), append_vector(std::move(i1.TypeReferences), std::move(i3.TypeReference)));
                                read_token = false;
                                switch(states.back()) {
                                    case 167: states.push_back(168); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 173:
                    switch(token) {
                        case dc::TokenType::OpenTriangle:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenTriangle, std::move(value));
                            states.push_back(174);
                            read_token = true;
                            break;
                        case dc::TokenType::Equals:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Equals, std::move(value));
                            states.push_back(175);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::OpenTriangle);
                                validTokens.push_back(dc::TokenType::Equals);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 174:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 175:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case dc::TokenType::Int16:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int16, std::move(value));
                            states.push_back(147);
                            read_token = true;
                            break;
                        case dc::TokenType::DFloat:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::DFloat, std::move(value));
                            states.push_back(146);
                            read_token = true;
                            break;
                        case dc::TokenType::Int8:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int8, std::move(value));
                            states.push_back(152);
                            read_token = true;
                            break;
                        case dc::TokenType::StringKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::StringKeyword, std::move(value));
                            states.push_back(151);
                            read_token = true;
                            break;
                        case dc::TokenType::Int64:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int64, std::move(value));
                            states.push_back(144);
                            read_token = true;
                            break;
                        case dc::TokenType::Int32:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int32, std::move(value));
                            states.push_back(145);
                            read_token = true;
                            break;
                        case dc::TokenType::FloatKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::FloatKeyword, std::move(value));
                            states.push_back(142);
                            read_token = true;
                            break;
                        case dc::TokenType::DWord:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::DWord, std::move(value));
                            states.push_back(153);
                            read_token = true;
                            break;
                        case dc::TokenType::Word:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Word, std::move(value));
                            states.push_back(155);
                            read_token = true;
                            break;
                        case dc::TokenType::WString:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::WString, std::move(value));
                            states.push_back(143);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                validTokens.push_back(dc::TokenType::Int16);
                                validTokens.push_back(dc::TokenType::DFloat);
                                validTokens.push_back(dc::TokenType::Int8);
                                validTokens.push_back(dc::TokenType::StringKeyword);
                                validTokens.push_back(dc::TokenType::Int64);
                                validTokens.push_back(dc::TokenType::Int32);
                                validTokens.push_back(dc::TokenType::FloatKeyword);
                                validTokens.push_back(dc::TokenType::DWord);
                                validTokens.push_back(dc::TokenType::Word);
                                validTokens.push_back(dc::TokenType::WString);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 176:
                    switch(token) {
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(177);
                            read_token = true;
                            break;
                        case dc::TokenType::OpenSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenSquare, std::move(value));
                            states.push_back(163);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Semicolon);
                                validTokens.push_back(dc::TokenType::OpenSquare);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 177:
                    // Reduce NamespaceItem: Metadata TokenType.Alias Ident TokenType.Equals TypeReference TokenType.Semicolon
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
                         values.emplace_back(lexical_type::NamespaceItem(), std::shared_ptr<NamespaceItemAst>(new TypeAliasAst(span(i2.tkn_span.begin, i5.TypeReference->Spn.end), std::move(i1.Metadata->Documentation), std::move(i3.Ident), std::vector<std::shared_ptr<TypeArgumentAst>>(), std::move(i5.TypeReference))));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(29); break;
                            case 28: states.push_back(187); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 178:
                    // Reduce TypeArgument: Ident
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeArgument(), std::shared_ptr<TypeArgumentAst>(new TypeArgumentAst(i1.Ident.spn(), std::move(i1.Ident))));
                        read_token = false;
                        switch(states.back()) {
                            case 174: states.push_back(179); break;
                            case 182: states.push_back(183); break;
                            case 195: states.push_back(179); break;
                            case 218: states.push_back(179); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 179:
                    // Reduce TypeArguments: TypeArgument
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeArguments(), as_vector(std::move(i1.TypeArgument)));
                        read_token = false;
                        switch(states.back()) {
                            case 174: states.push_back(180); break;
                            case 195: states.push_back(199); break;
                            case 218: states.push_back(219); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 180:
                    switch(token) {
                        case dc::TokenType::CloseTriangle:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CloseTriangle, std::move(value));
                            states.push_back(181);
                            read_token = true;
                            break;
                        case dc::TokenType::Comma:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Comma, std::move(value));
                            states.push_back(182);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::CloseTriangle);
                                validTokens.push_back(dc::TokenType::Comma);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 181:
                    switch(token) {
                        case dc::TokenType::Equals:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Equals, std::move(value));
                            states.push_back(184);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Equals);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 182:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 183:
                    // Reduce TypeArguments: TypeArguments TokenType.Comma TypeArgument
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
                         values.emplace_back(lexical_type::TypeArguments(), append_vector(std::move(i1.TypeArguments), std::move(i3.TypeArgument)));
                        read_token = false;
                        switch(states.back()) {
                            case 174: states.push_back(180); break;
                            case 195: states.push_back(199); break;
                            case 218: states.push_back(219); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 184:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case dc::TokenType::Int16:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int16, std::move(value));
                            states.push_back(147);
                            read_token = true;
                            break;
                        case dc::TokenType::DFloat:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::DFloat, std::move(value));
                            states.push_back(146);
                            read_token = true;
                            break;
                        case dc::TokenType::Int8:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int8, std::move(value));
                            states.push_back(152);
                            read_token = true;
                            break;
                        case dc::TokenType::StringKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::StringKeyword, std::move(value));
                            states.push_back(151);
                            read_token = true;
                            break;
                        case dc::TokenType::Int64:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int64, std::move(value));
                            states.push_back(144);
                            read_token = true;
                            break;
                        case dc::TokenType::Int32:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int32, std::move(value));
                            states.push_back(145);
                            read_token = true;
                            break;
                        case dc::TokenType::FloatKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::FloatKeyword, std::move(value));
                            states.push_back(142);
                            read_token = true;
                            break;
                        case dc::TokenType::DWord:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::DWord, std::move(value));
                            states.push_back(153);
                            read_token = true;
                            break;
                        case dc::TokenType::Word:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Word, std::move(value));
                            states.push_back(155);
                            read_token = true;
                            break;
                        case dc::TokenType::WString:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::WString, std::move(value));
                            states.push_back(143);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                validTokens.push_back(dc::TokenType::Int16);
                                validTokens.push_back(dc::TokenType::DFloat);
                                validTokens.push_back(dc::TokenType::Int8);
                                validTokens.push_back(dc::TokenType::StringKeyword);
                                validTokens.push_back(dc::TokenType::Int64);
                                validTokens.push_back(dc::TokenType::Int32);
                                validTokens.push_back(dc::TokenType::FloatKeyword);
                                validTokens.push_back(dc::TokenType::DWord);
                                validTokens.push_back(dc::TokenType::Word);
                                validTokens.push_back(dc::TokenType::WString);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 185:
                    switch(token) {
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(186);
                            read_token = true;
                            break;
                        case dc::TokenType::OpenSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenSquare, std::move(value));
                            states.push_back(163);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Semicolon);
                                validTokens.push_back(dc::TokenType::OpenSquare);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 186:
                    // Reduce NamespaceItem: Metadata TokenType.Alias Ident TokenType.OpenTriangle TypeArguments TokenType.CloseTriangle TokenType.Equals TypeReference TokenType.Semicolon
                    if (true) {
                        auto i9 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i8 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
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
                         values.emplace_back(lexical_type::NamespaceItem(), std::shared_ptr<NamespaceItemAst>(new TypeAliasAst(span(i2.tkn_span.begin, i8.TypeReference->Spn.end), std::move(i1.Metadata->Documentation), std::move(i3.Ident), std::move(i5.TypeArguments), std::move(i8.TypeReference))));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(29); break;
                            case 28: states.push_back(187); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 187:
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
                            case 18: states.push_back(28); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 188:
                    switch(token) {
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(189);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 189:
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
                         values.emplace_back(lexical_type::DocumentItem(), std::shared_ptr<DocumentAst>(new NamespaceAst(span(i1.tkn_span.begin, i6.tkn_span.end), std::move(i2.QName), std::move(i4.NamespaceItems))));
                        read_token = false;
                        switch(states.back()) {
                            case 0: states.push_back(5); break;
                            case 1: states.push_back(230); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 190:
                    switch(token) {
                        case dc::TokenType::Equals:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Equals, std::move(value));
                            states.push_back(191);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Equals);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 191:
                    switch(token) {
                        case dc::TokenType::ReStart:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::ReStart, std::move(value));
                            states.push_back(37);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::ReStart);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 192:
                    switch(token) {
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(193);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 193:
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
                         values.emplace_back(lexical_type::NamespaceItem(), std::shared_ptr<NamespaceItemAst>(new PatternAst(span(i1.tkn_span.begin, i5.tkn_span.end), std::vector<spantext>(), std::move(i2.Ident), std::move(i4.Re))));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(29); break;
                            case 28: states.push_back(187); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 194:
                    switch(token) {
                        case dc::TokenType::OpenTriangle:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenTriangle, std::move(value));
                            states.push_back(195);
                            read_token = true;
                            break;
                        case dc::TokenType::Equals:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Equals, std::move(value));
                            states.push_back(196);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::OpenTriangle);
                                validTokens.push_back(dc::TokenType::Equals);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 195:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 196:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case dc::TokenType::Int16:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int16, std::move(value));
                            states.push_back(147);
                            read_token = true;
                            break;
                        case dc::TokenType::DFloat:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::DFloat, std::move(value));
                            states.push_back(146);
                            read_token = true;
                            break;
                        case dc::TokenType::Int8:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int8, std::move(value));
                            states.push_back(152);
                            read_token = true;
                            break;
                        case dc::TokenType::StringKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::StringKeyword, std::move(value));
                            states.push_back(151);
                            read_token = true;
                            break;
                        case dc::TokenType::Int64:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int64, std::move(value));
                            states.push_back(144);
                            read_token = true;
                            break;
                        case dc::TokenType::Int32:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int32, std::move(value));
                            states.push_back(145);
                            read_token = true;
                            break;
                        case dc::TokenType::FloatKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::FloatKeyword, std::move(value));
                            states.push_back(142);
                            read_token = true;
                            break;
                        case dc::TokenType::DWord:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::DWord, std::move(value));
                            states.push_back(153);
                            read_token = true;
                            break;
                        case dc::TokenType::Word:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Word, std::move(value));
                            states.push_back(155);
                            read_token = true;
                            break;
                        case dc::TokenType::WString:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::WString, std::move(value));
                            states.push_back(143);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                validTokens.push_back(dc::TokenType::Int16);
                                validTokens.push_back(dc::TokenType::DFloat);
                                validTokens.push_back(dc::TokenType::Int8);
                                validTokens.push_back(dc::TokenType::StringKeyword);
                                validTokens.push_back(dc::TokenType::Int64);
                                validTokens.push_back(dc::TokenType::Int32);
                                validTokens.push_back(dc::TokenType::FloatKeyword);
                                validTokens.push_back(dc::TokenType::DWord);
                                validTokens.push_back(dc::TokenType::Word);
                                validTokens.push_back(dc::TokenType::WString);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 197:
                    switch(token) {
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(198);
                            read_token = true;
                            break;
                        case dc::TokenType::OpenSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenSquare, std::move(value));
                            states.push_back(163);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Semicolon);
                                validTokens.push_back(dc::TokenType::OpenSquare);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 198:
                    // Reduce NamespaceItem: TokenType.Alias Ident TokenType.Equals TypeReference TokenType.Semicolon
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
                         values.emplace_back(lexical_type::NamespaceItem(), std::shared_ptr<NamespaceItemAst>(new TypeAliasAst(span(i1.tkn_span.begin, i4.TypeReference->Spn.end), std::vector<spantext>(), std::move(i2.Ident), std::vector<std::shared_ptr<TypeArgumentAst>>(), std::move(i4.TypeReference))));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(29); break;
                            case 28: states.push_back(187); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 199:
                    switch(token) {
                        case dc::TokenType::CloseTriangle:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CloseTriangle, std::move(value));
                            states.push_back(200);
                            read_token = true;
                            break;
                        case dc::TokenType::Comma:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Comma, std::move(value));
                            states.push_back(182);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::CloseTriangle);
                                validTokens.push_back(dc::TokenType::Comma);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 200:
                    switch(token) {
                        case dc::TokenType::Equals:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Equals, std::move(value));
                            states.push_back(201);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Equals);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 201:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case dc::TokenType::Int16:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int16, std::move(value));
                            states.push_back(147);
                            read_token = true;
                            break;
                        case dc::TokenType::DFloat:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::DFloat, std::move(value));
                            states.push_back(146);
                            read_token = true;
                            break;
                        case dc::TokenType::Int8:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int8, std::move(value));
                            states.push_back(152);
                            read_token = true;
                            break;
                        case dc::TokenType::StringKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::StringKeyword, std::move(value));
                            states.push_back(151);
                            read_token = true;
                            break;
                        case dc::TokenType::Int64:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int64, std::move(value));
                            states.push_back(144);
                            read_token = true;
                            break;
                        case dc::TokenType::Int32:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int32, std::move(value));
                            states.push_back(145);
                            read_token = true;
                            break;
                        case dc::TokenType::FloatKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::FloatKeyword, std::move(value));
                            states.push_back(142);
                            read_token = true;
                            break;
                        case dc::TokenType::DWord:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::DWord, std::move(value));
                            states.push_back(153);
                            read_token = true;
                            break;
                        case dc::TokenType::Word:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Word, std::move(value));
                            states.push_back(155);
                            read_token = true;
                            break;
                        case dc::TokenType::WString:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::WString, std::move(value));
                            states.push_back(143);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                validTokens.push_back(dc::TokenType::Int16);
                                validTokens.push_back(dc::TokenType::DFloat);
                                validTokens.push_back(dc::TokenType::Int8);
                                validTokens.push_back(dc::TokenType::StringKeyword);
                                validTokens.push_back(dc::TokenType::Int64);
                                validTokens.push_back(dc::TokenType::Int32);
                                validTokens.push_back(dc::TokenType::FloatKeyword);
                                validTokens.push_back(dc::TokenType::DWord);
                                validTokens.push_back(dc::TokenType::Word);
                                validTokens.push_back(dc::TokenType::WString);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 202:
                    switch(token) {
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(203);
                            read_token = true;
                            break;
                        case dc::TokenType::OpenSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenSquare, std::move(value));
                            states.push_back(163);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Semicolon);
                                validTokens.push_back(dc::TokenType::OpenSquare);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 203:
                    // Reduce NamespaceItem: TokenType.Alias Ident TokenType.OpenTriangle TypeArguments TokenType.CloseTriangle TokenType.Equals TypeReference TokenType.Semicolon
                    if (true) {
                        auto i8 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
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
                         values.emplace_back(lexical_type::NamespaceItem(), std::shared_ptr<NamespaceItemAst>(new TypeAliasAst(span(i1.tkn_span.begin, i7.TypeReference->Spn.end), std::vector<spantext>(), std::move(i2.Ident), std::move(i4.TypeArguments), std::move(i7.TypeReference))));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(29); break;
                            case 28: states.push_back(187); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 204:
                    switch(token) {
                        case dc::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenBrace, std::move(value));
                            states.push_back(205);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::OpenBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 205:
                    switch(token) {
                        case dc::TokenType::Include:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Include, std::move(value));
                            states.push_back(36);
                            read_token = true;
                            break;
                        case dc::TokenType::ReStart:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::ReStart, std::move(value));
                            states.push_back(37);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Include);
                                validTokens.push_back(dc::TokenType::ReStart);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 206:
                    switch(token) {
                        case dc::TokenType::ReStart:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::ReStart, std::move(value));
                            states.push_back(37);
                            read_token = true;
                            break;
                        case dc::TokenType::Include:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Include, std::move(value));
                            states.push_back(36);
                            read_token = true;
                            break;
                        case dc::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CloseBrace, std::move(value));
                            states.push_back(207);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::ReStart);
                                validTokens.push_back(dc::TokenType::Include);
                                validTokens.push_back(dc::TokenType::CloseBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 207:
                    switch(token) {
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(208);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 208:
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
                         values.emplace_back(lexical_type::NamespaceItem(), std::shared_ptr<NamespaceItemAst>(new AutomataAst(span(i1.tkn_span.begin, i6.tkn_span.end), std::vector<spantext>(), std::move(i2.Ident), std::move(i4.SetItems))));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(29); break;
                            case 28: states.push_back(187); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 209:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case dc::TokenType::FloatKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::FloatKeyword, std::move(value));
                            states.push_back(142);
                            read_token = true;
                            break;
                        case dc::TokenType::WString:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::WString, std::move(value));
                            states.push_back(143);
                            read_token = true;
                            break;
                        case dc::TokenType::Int64:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int64, std::move(value));
                            states.push_back(144);
                            read_token = true;
                            break;
                        case dc::TokenType::Int32:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int32, std::move(value));
                            states.push_back(145);
                            read_token = true;
                            break;
                        case dc::TokenType::DFloat:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::DFloat, std::move(value));
                            states.push_back(146);
                            read_token = true;
                            break;
                        case dc::TokenType::Int16:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int16, std::move(value));
                            states.push_back(147);
                            read_token = true;
                            break;
                        case dc::TokenType::Documentation:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Documentation, std::move(value));
                            states.push_back(24);
                            read_token = true;
                            break;
                        case dc::TokenType::StringKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::StringKeyword, std::move(value));
                            states.push_back(151);
                            read_token = true;
                            break;
                        case dc::TokenType::Int8:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int8, std::move(value));
                            states.push_back(152);
                            read_token = true;
                            break;
                        case dc::TokenType::DWord:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::DWord, std::move(value));
                            states.push_back(153);
                            read_token = true;
                            break;
                        case dc::TokenType::Word:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Word, std::move(value));
                            states.push_back(155);
                            read_token = true;
                            break;
                        case dc::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CloseBrace, std::move(value));
                            states.push_back(212);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                validTokens.push_back(dc::TokenType::FloatKeyword);
                                validTokens.push_back(dc::TokenType::WString);
                                validTokens.push_back(dc::TokenType::Int64);
                                validTokens.push_back(dc::TokenType::Int32);
                                validTokens.push_back(dc::TokenType::DFloat);
                                validTokens.push_back(dc::TokenType::Int16);
                                validTokens.push_back(dc::TokenType::Documentation);
                                validTokens.push_back(dc::TokenType::StringKeyword);
                                validTokens.push_back(dc::TokenType::Int8);
                                validTokens.push_back(dc::TokenType::DWord);
                                validTokens.push_back(dc::TokenType::Word);
                                validTokens.push_back(dc::TokenType::CloseBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 210:
                    // Reduce NamespaceItem: TypeDef TokenType.Semicolon
                    if (true) {
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.push_back(std::move(i1));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(29); break;
                            case 28: states.push_back(187); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 211:
                    switch(token) {
                        case dc::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CloseBrace, std::move(value));
                            states.push_back(214);
                            read_token = true;
                            break;
                        case dc::TokenType::Comma:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Comma, std::move(value));
                            states.push_back(159);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::CloseBrace);
                                validTokens.push_back(dc::TokenType::Comma);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 212:
                    switch(token) {
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(213);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 213:
                    // Reduce NamespaceItem: TypeDef TokenType.OpenBrace TokenType.CloseBrace TokenType.Semicolon
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
                         values.push_back(std::move(i1));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(29); break;
                            case 28: states.push_back(187); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 214:
                    switch(token) {
                        case dc::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Semicolon, std::move(value));
                            states.push_back(215);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 215:
                    // Reduce NamespaceItem: TypeDef TokenType.OpenBrace TypeProperties TokenType.CloseBrace TokenType.Semicolon
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
                         values.push_back(std::move(i1)); ((TypeAst*)values.back().NamespaceItem.get())->Properties = std::move(i3.TypeProperties);
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(29); break;
                            case 28: states.push_back(187); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 216:
                    switch(token) {
                        case dc::TokenType::Colon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Colon, std::move(value));
                            states.push_back(217);
                            read_token = true;
                            break;
                        case dc::TokenType::OpenTriangle:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenTriangle, std::move(value));
                            states.push_back(218);
                            read_token = true;
                            break;
                        default:
                            // Reduce TypeDef: TypeProps Ident
                            if (true) {
                                auto i2 = std::move(values.back());
                                values.pop_back();
                                states.pop_back();
                                auto i1 = std::move(values.back());
                                values.pop_back();
                                states.pop_back();
                                 values.push_back(std::move(i1)); ((TypeAst*)values.back().NamespaceItem.get())->Name = std::move(i2.Ident);
                                read_token = false;
                                switch(states.back()) {
                                    case 18: states.push_back(23); break;
                                    case 28: states.push_back(23); break;
                                    case 30: states.push_back(132); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 217:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case dc::TokenType::Int16:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int16, std::move(value));
                            states.push_back(147);
                            read_token = true;
                            break;
                        case dc::TokenType::DFloat:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::DFloat, std::move(value));
                            states.push_back(146);
                            read_token = true;
                            break;
                        case dc::TokenType::Int8:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int8, std::move(value));
                            states.push_back(152);
                            read_token = true;
                            break;
                        case dc::TokenType::StringKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::StringKeyword, std::move(value));
                            states.push_back(151);
                            read_token = true;
                            break;
                        case dc::TokenType::Int64:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int64, std::move(value));
                            states.push_back(144);
                            read_token = true;
                            break;
                        case dc::TokenType::Int32:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int32, std::move(value));
                            states.push_back(145);
                            read_token = true;
                            break;
                        case dc::TokenType::FloatKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::FloatKeyword, std::move(value));
                            states.push_back(142);
                            read_token = true;
                            break;
                        case dc::TokenType::DWord:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::DWord, std::move(value));
                            states.push_back(153);
                            read_token = true;
                            break;
                        case dc::TokenType::Word:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Word, std::move(value));
                            states.push_back(155);
                            read_token = true;
                            break;
                        case dc::TokenType::WString:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::WString, std::move(value));
                            states.push_back(143);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                validTokens.push_back(dc::TokenType::Int16);
                                validTokens.push_back(dc::TokenType::DFloat);
                                validTokens.push_back(dc::TokenType::Int8);
                                validTokens.push_back(dc::TokenType::StringKeyword);
                                validTokens.push_back(dc::TokenType::Int64);
                                validTokens.push_back(dc::TokenType::Int32);
                                validTokens.push_back(dc::TokenType::FloatKeyword);
                                validTokens.push_back(dc::TokenType::DWord);
                                validTokens.push_back(dc::TokenType::Word);
                                validTokens.push_back(dc::TokenType::WString);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 218:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 219:
                    switch(token) {
                        case dc::TokenType::CloseTriangle:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::CloseTriangle, std::move(value));
                            states.push_back(220);
                            read_token = true;
                            break;
                        case dc::TokenType::Comma:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Comma, std::move(value));
                            states.push_back(182);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::CloseTriangle);
                                validTokens.push_back(dc::TokenType::Comma);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 220:
                    switch(token) {
                        case dc::TokenType::Colon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Colon, std::move(value));
                            states.push_back(221);
                            read_token = true;
                            break;
                        default:
                            // Reduce TypeDef: TypeProps Ident TokenType.OpenTriangle TypeArguments TokenType.CloseTriangle
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
                                 values.push_back(std::move(i1)); ((TypeAst*)values.back().NamespaceItem.get())->Name = std::move(i2.Ident); ((TypeAst*)values.back().NamespaceItem.get())->Arguments = std::move(i4.TypeArguments);
                                read_token = false;
                                switch(states.back()) {
                                    case 18: states.push_back(23); break;
                                    case 28: states.push_back(23); break;
                                    case 30: states.push_back(132); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 221:
                    switch(token) {
                        case dc::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case dc::TokenType::Int16:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int16, std::move(value));
                            states.push_back(147);
                            read_token = true;
                            break;
                        case dc::TokenType::DFloat:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::DFloat, std::move(value));
                            states.push_back(146);
                            read_token = true;
                            break;
                        case dc::TokenType::Int8:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int8, std::move(value));
                            states.push_back(152);
                            read_token = true;
                            break;
                        case dc::TokenType::StringKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::StringKeyword, std::move(value));
                            states.push_back(151);
                            read_token = true;
                            break;
                        case dc::TokenType::Int64:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int64, std::move(value));
                            states.push_back(144);
                            read_token = true;
                            break;
                        case dc::TokenType::Int32:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Int32, std::move(value));
                            states.push_back(145);
                            read_token = true;
                            break;
                        case dc::TokenType::FloatKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::FloatKeyword, std::move(value));
                            states.push_back(142);
                            read_token = true;
                            break;
                        case dc::TokenType::DWord:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::DWord, std::move(value));
                            states.push_back(153);
                            read_token = true;
                            break;
                        case dc::TokenType::Word:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Word, std::move(value));
                            states.push_back(155);
                            read_token = true;
                            break;
                        case dc::TokenType::WString:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::WString, std::move(value));
                            states.push_back(143);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Identifier);
                                validTokens.push_back(dc::TokenType::Int16);
                                validTokens.push_back(dc::TokenType::DFloat);
                                validTokens.push_back(dc::TokenType::Int8);
                                validTokens.push_back(dc::TokenType::StringKeyword);
                                validTokens.push_back(dc::TokenType::Int64);
                                validTokens.push_back(dc::TokenType::Int32);
                                validTokens.push_back(dc::TokenType::FloatKeyword);
                                validTokens.push_back(dc::TokenType::DWord);
                                validTokens.push_back(dc::TokenType::Word);
                                validTokens.push_back(dc::TokenType::WString);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 222:
                    switch(token) {
                        case dc::TokenType::OpenSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenSquare, std::move(value));
                            states.push_back(163);
                            read_token = true;
                            break;
                        default:
                            // Reduce TypeDef: TypeProps Ident TokenType.OpenTriangle TypeArguments TokenType.CloseTriangle TokenType.Colon TypeReference
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
                                 values.push_back(std::move(i1)); ((TypeAst*)values.back().NamespaceItem.get())->Name = std::move(i2.Ident); ((TypeAst*)values.back().NamespaceItem.get())->Arguments = std::move(i4.TypeArguments); ((TypeAst*)values.back().NamespaceItem.get())->Parent = std::move(i6.TypeReference);
                                read_token = false;
                                switch(states.back()) {
                                    case 18: states.push_back(23); break;
                                    case 28: states.push_back(23); break;
                                    case 30: states.push_back(132); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 223:
                    switch(token) {
                        case dc::TokenType::OpenSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::OpenSquare, std::move(value));
                            states.push_back(163);
                            read_token = true;
                            break;
                        default:
                            // Reduce TypeDef: TypeProps Ident TokenType.Colon TypeReference
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
                                 values.push_back(std::move(i1)); ((TypeAst*)values.back().NamespaceItem.get())->Name = std::move(i2.Ident); ((TypeAst*)values.back().NamespaceItem.get())->Parent = std::move(i4.TypeReference);
                                read_token = false;
                                switch(states.back()) {
                                    case 18: states.push_back(23); break;
                                    case 28: states.push_back(23); break;
                                    case 30: states.push_back(132); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 224:
                    switch(token) {
                        case dc::TokenType::Type:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Type, std::move(value));
                            states.push_back(226);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Type);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 225:
                    // Reduce TypeProps: TokenType.Abstract TokenType.Type
                    if (true) {
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::NamespaceItem(), std::shared_ptr<NamespaceItemAst>(new TypeAst(i1.tkn_span, std::vector<spantext>(), spantext(), std::vector<std::shared_ptr<TypeArgumentAst>>(), true, false, std::shared_ptr<TypeReferenceAst>(), std::vector<std::shared_ptr<TypePropertyAst>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(22); break;
                            case 28: states.push_back(22); break;
                            case 30: states.push_back(22); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 226:
                    // Reduce TypeProps: TokenType.Abstract TokenType.Sealed TokenType.Type
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
                         values.emplace_back(lexical_type::NamespaceItem(), std::shared_ptr<NamespaceItemAst>(new TypeAst(i1.tkn_span, std::vector<spantext>(), spantext(), std::vector<std::shared_ptr<TypeArgumentAst>>(), true, true, std::shared_ptr<TypeReferenceAst>(), std::vector<std::shared_ptr<TypePropertyAst>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(22); break;
                            case 28: states.push_back(22); break;
                            case 30: states.push_back(22); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 227:
                    switch(token) {
                        case dc::TokenType::Type:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), dc::TokenType::Type, std::move(value));
                            states.push_back(229);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<dc::TokenType> validTokens;
                                validTokens.push_back(dc::TokenType::Type);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 228:
                    // Reduce TypeProps: TokenType.Sealed TokenType.Type
                    if (true) {
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::NamespaceItem(), std::shared_ptr<NamespaceItemAst>(new TypeAst(i1.tkn_span, std::vector<spantext>(), spantext(), std::vector<std::shared_ptr<TypeArgumentAst>>(), false, true, std::shared_ptr<TypeReferenceAst>(), std::vector<std::shared_ptr<TypePropertyAst>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(22); break;
                            case 28: states.push_back(22); break;
                            case 30: states.push_back(22); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 229:
                    // Reduce TypeProps: TokenType.Sealed TokenType.Abstract TokenType.Type
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
                         values.emplace_back(lexical_type::NamespaceItem(), std::shared_ptr<NamespaceItemAst>(new TypeAst(i1.tkn_span, std::vector<spantext>(), spantext(), std::vector<std::shared_ptr<TypeArgumentAst>>(), true, true, std::shared_ptr<TypeReferenceAst>(), std::vector<std::shared_ptr<TypePropertyAst>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(22); break;
                            case 28: states.push_back(22); break;
                            case 30: states.push_back(22); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 230:
                    // Reduce Document: Document DocumentItem
                    if (true) {
                        auto i2 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(); i2.DocumentItem->accept(i2.DocumentItem, processor); if(!ok) return false;
                        read_token = false;
                        switch(states.back()) {
                            case 0: states.push_back(1); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
            }
        }
    }
}
