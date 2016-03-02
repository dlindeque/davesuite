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
        davelexer::TokenType tkn_type;
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
        lexical_value(span &&spn, const davelexer::TokenType _tkn_type, const std::wstring &_tkn_value)
        : desc(text(_tkn_type)), tkn_span(std::move(spn)), tkn_type(_tkn_type), tkn_value(_tkn_value)
        {}
        lexical_value(span &&spn, const davelexer::TokenType _tkn_type, std::wstring &&_tkn_value)
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
        davelexer::lexer lexer(stm);
        long start_line = 0, start_column = 0, end_line = 0, end_column = 0;
        std::wstring value;
        davelexer::TokenType token = davelexer::TokenType::Error;
        while(true) {
            if (read_token) {
                while(true) {
                    if (!lexer.try_read_next_token(start_line, start_column, end_line, end_column, value, token)) {
                        token = davelexer::TokenType::EOD;
                    }
                    if (token != davelexer::TokenType::Whitespace && token != davelexer::TokenType::Comment) break;
                }
            }
            switch(states.back()) {
                case 0:
                    switch(token) {
                        case davelexer::TokenType::Namespace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Namespace, std::move(value));
                            states.push_back(2);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Set:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Set, std::move(value));
                            states.push_back(3);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Import:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Import, std::move(value));
                            states.push_back(4);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Namespace);
                                validTokens.push_back(davelexer::TokenType::Set);
                                validTokens.push_back(davelexer::TokenType::Import);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 1:
                    switch(token) {
                        case davelexer::TokenType::Namespace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Namespace, std::move(value));
                            states.push_back(2);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Set:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Set, std::move(value));
                            states.push_back(3);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Import:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Import, std::move(value));
                            states.push_back(4);
                            read_token = true;
                            break;
                        case davelexer::TokenType::EOD:
                            return true;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Namespace);
                                validTokens.push_back(davelexer::TokenType::Set);
                                validTokens.push_back(davelexer::TokenType::Import);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 2:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 3:
                    switch(token) {
                        case davelexer::TokenType::Start:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Start, std::move(value));
                            states.push_back(9);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Start);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 4:
                    switch(token) {
                        case davelexer::TokenType::String:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::String, std::move(value));
                            states.push_back(6);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::String);
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
                         values.emplace_back(lexical_type::Str(), spantext(i1.tkn_span, std::move(i1.tkn_value)));
                        read_token = false;
                        switch(states.back()) {
                            case 4: states.push_back(7); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 7:
                    switch(token) {
                        case davelexer::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Semicolon, std::move(value));
                            states.push_back(8);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Semicolon);
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
                            case 1: states.push_back(208); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 9:
                    switch(token) {
                        case davelexer::TokenType::Equals:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Equals, std::move(value));
                            states.push_back(10);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Equals);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 10:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
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
                            case 23: states.push_back(193); break;
                            case 24: states.push_back(189); break;
                            case 29: states.push_back(130); break;
                            case 30: states.push_back(118); break;
                            case 32: states.push_back(33); break;
                            case 35: states.push_back(12); break;
                            case 43: states.push_back(12); break;
                            case 45: states.push_back(46); break;
                            case 46: states.push_back(12); break;
                            case 49: states.push_back(50); break;
                            case 50: states.push_back(12); break;
                            case 54: states.push_back(55); break;
                            case 55: states.push_back(12); break;
                            case 58: states.push_back(12); break;
                            case 70: states.push_back(12); break;
                            case 94: states.push_back(12); break;
                            case 100: states.push_back(113); break;
                            case 101: states.push_back(108); break;
                            case 102: states.push_back(104); break;
                            case 119: states.push_back(123); break;
                            case 122: states.push_back(129); break;
                            case 125: states.push_back(123); break;
                            case 131: states.push_back(12); break;
                            case 132: states.push_back(133); break;
                            case 137: states.push_back(133); break;
                            case 139: states.push_back(12); break;
                            case 154: states.push_back(12); break;
                            case 158: states.push_back(12); break;
                            case 165: states.push_back(166); break;
                            case 167: states.push_back(123); break;
                            case 171: states.push_back(12); break;
                            case 173: states.push_back(12); break;
                            case 174: states.push_back(183); break;
                            case 180: states.push_back(12); break;
                            case 184: states.push_back(185); break;
                            case 198: states.push_back(12); break;
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
                            case 35: states.push_back(93); break;
                            case 43: states.push_back(53); break;
                            case 46: states.push_back(47); break;
                            case 50: states.push_back(51); break;
                            case 55: states.push_back(56); break;
                            case 58: states.push_back(73); break;
                            case 70: states.push_back(73); break;
                            case 94: states.push_back(98); break;
                            case 131: states.push_back(140); break;
                            case 139: states.push_back(140); break;
                            case 154: states.push_back(140); break;
                            case 158: states.push_back(140); break;
                            case 171: states.push_back(140); break;
                            case 173: states.push_back(140); break;
                            case 180: states.push_back(140); break;
                            case 198: states.push_back(140); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 13:
                    switch(token) {
                        case davelexer::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Semicolon, std::move(value));
                            states.push_back(14);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Dot, std::move(value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Semicolon);
                                validTokens.push_back(davelexer::TokenType::Dot);
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
                            case 1: states.push_back(208); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 15:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
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
                            case 35: states.push_back(93); break;
                            case 43: states.push_back(53); break;
                            case 46: states.push_back(47); break;
                            case 50: states.push_back(51); break;
                            case 55: states.push_back(56); break;
                            case 58: states.push_back(73); break;
                            case 70: states.push_back(73); break;
                            case 94: states.push_back(98); break;
                            case 131: states.push_back(140); break;
                            case 139: states.push_back(140); break;
                            case 154: states.push_back(140); break;
                            case 158: states.push_back(140); break;
                            case 171: states.push_back(140); break;
                            case 173: states.push_back(140); break;
                            case 180: states.push_back(140); break;
                            case 198: states.push_back(140); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 17:
                    switch(token) {
                        case davelexer::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenBrace, std::move(value));
                            states.push_back(18);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Dot, std::move(value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::OpenBrace);
                                validTokens.push_back(davelexer::TokenType::Dot);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 18:
                    switch(token) {
                        case davelexer::TokenType::Sealed:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Sealed, std::move(value));
                            states.push_back(19);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Type:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Type, std::move(value));
                            states.push_back(20);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Documentation:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Documentation, std::move(value));
                            states.push_back(22);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Automata:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Automata, std::move(value));
                            states.push_back(23);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Pattern:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Pattern, std::move(value));
                            states.push_back(24);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Abstract:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Abstract, std::move(value));
                            states.push_back(28);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Enum:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Enum, std::move(value));
                            states.push_back(30);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Set:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Set, std::move(value));
                            states.push_back(32);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Sealed);
                                validTokens.push_back(davelexer::TokenType::Type);
                                validTokens.push_back(davelexer::TokenType::Documentation);
                                validTokens.push_back(davelexer::TokenType::Automata);
                                validTokens.push_back(davelexer::TokenType::Pattern);
                                validTokens.push_back(davelexer::TokenType::Abstract);
                                validTokens.push_back(davelexer::TokenType::Enum);
                                validTokens.push_back(davelexer::TokenType::Set);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 19:
                    switch(token) {
                        case davelexer::TokenType::Abstract:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Abstract, std::move(value));
                            states.push_back(205);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Type:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Type, std::move(value));
                            states.push_back(206);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Abstract);
                                validTokens.push_back(davelexer::TokenType::Type);
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
                            case 18: states.push_back(29); break;
                            case 25: states.push_back(29); break;
                            case 27: states.push_back(29); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 21:
                    switch(token) {
                        case davelexer::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenBrace, std::move(value));
                            states.push_back(198);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Semicolon, std::move(value));
                            states.push_back(199);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::OpenBrace);
                                validTokens.push_back(davelexer::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 22:
                    // Reduce Documentation: TokenType.Documentation
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::Documentation(), as_vector(std::move(spantext(i1.tkn_span, std::move(i1.tkn_value)))));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(31); break;
                            case 25: states.push_back(31); break;
                            case 119: states.push_back(120); break;
                            case 125: states.push_back(120); break;
                            case 167: states.push_back(120); break;
                            case 171: states.push_back(120); break;
                            case 180: states.push_back(120); break;
                            case 198: states.push_back(120); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 23:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 24:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 25:
                    switch(token) {
                        case davelexer::TokenType::Type:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Type, std::move(value));
                            states.push_back(20);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Documentation:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Documentation, std::move(value));
                            states.push_back(22);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Automata:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Automata, std::move(value));
                            states.push_back(23);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Set:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Set, std::move(value));
                            states.push_back(32);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Pattern:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Pattern, std::move(value));
                            states.push_back(24);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Abstract:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Abstract, std::move(value));
                            states.push_back(28);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Enum:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Enum, std::move(value));
                            states.push_back(30);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Sealed:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Sealed, std::move(value));
                            states.push_back(19);
                            read_token = true;
                            break;
                        case davelexer::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CloseBrace, std::move(value));
                            states.push_back(187);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Type);
                                validTokens.push_back(davelexer::TokenType::Documentation);
                                validTokens.push_back(davelexer::TokenType::Automata);
                                validTokens.push_back(davelexer::TokenType::Set);
                                validTokens.push_back(davelexer::TokenType::Pattern);
                                validTokens.push_back(davelexer::TokenType::Abstract);
                                validTokens.push_back(davelexer::TokenType::Enum);
                                validTokens.push_back(davelexer::TokenType::Sealed);
                                validTokens.push_back(davelexer::TokenType::CloseBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 26:
                    // Reduce NamespaceItems: NamespaceItem
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::NamespaceItems(), as_vector(std::move(i1.NamespaceItem)));
                        read_token = false;
                        switch(states.back()) {
                            case 18: states.push_back(25); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 27:
                    switch(token) {
                        case davelexer::TokenType::Sealed:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Sealed, std::move(value));
                            states.push_back(19);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Type:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Type, std::move(value));
                            states.push_back(20);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Abstract:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Abstract, std::move(value));
                            states.push_back(28);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Enum:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Enum, std::move(value));
                            states.push_back(165);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Sealed);
                                validTokens.push_back(davelexer::TokenType::Type);
                                validTokens.push_back(davelexer::TokenType::Abstract);
                                validTokens.push_back(davelexer::TokenType::Enum);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 28:
                    switch(token) {
                        case davelexer::TokenType::Sealed:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Sealed, std::move(value));
                            states.push_back(161);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Type:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Type, std::move(value));
                            states.push_back(162);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Sealed);
                                validTokens.push_back(davelexer::TokenType::Type);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 29:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 30:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 31:
                    switch(token) {
                        case davelexer::TokenType::Automata:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Automata, std::move(value));
                            states.push_back(100);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Set:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Set, std::move(value));
                            states.push_back(101);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Pattern:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Pattern, std::move(value));
                            states.push_back(102);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Documentation:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Documentation, std::move(value));
                            states.push_back(103);
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
                                    case 18: states.push_back(27); break;
                                    case 25: states.push_back(27); break;
                                    case 119: states.push_back(122); break;
                                    case 125: states.push_back(122); break;
                                    case 167: states.push_back(122); break;
                                    case 171: states.push_back(173); break;
                                    case 180: states.push_back(173); break;
                                    case 198: states.push_back(173); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 32:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 33:
                    switch(token) {
                        case davelexer::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenBrace, std::move(value));
                            states.push_back(34);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::OpenBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 34:
                    switch(token) {
                        case davelexer::TokenType::Include:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Include, std::move(value));
                            states.push_back(35);
                            read_token = true;
                            break;
                        case davelexer::TokenType::ReStart:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::ReStart, std::move(value));
                            states.push_back(36);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Include);
                                validTokens.push_back(davelexer::TokenType::ReStart);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 35:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 36:
                    switch(token) {
                        case davelexer::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenBrace, std::move(value));
                            states.push_back(58);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Dot, std::move(value));
                            states.push_back(59);
                            read_token = true;
                            break;
                        case davelexer::TokenType::CharClass:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CharClass, std::move(value));
                            states.push_back(60);
                            read_token = true;
                            break;
                        case davelexer::TokenType::OpenSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenSquare, std::move(value));
                            states.push_back(61);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Char:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Char, std::move(value));
                            states.push_back(62);
                            read_token = true;
                            break;
                        case davelexer::TokenType::OpenParenthesis:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenParenthesis, std::move(value));
                            states.push_back(63);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::OpenBrace);
                                validTokens.push_back(davelexer::TokenType::Dot);
                                validTokens.push_back(davelexer::TokenType::CharClass);
                                validTokens.push_back(davelexer::TokenType::OpenSquare);
                                validTokens.push_back(davelexer::TokenType::Char);
                                validTokens.push_back(davelexer::TokenType::OpenParenthesis);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 37:
                    // Reduce SetItems: SetItem
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::SetItems(), as_vector(std::move(i1.SetItem)));
                        read_token = false;
                        switch(states.back()) {
                            case 34: states.push_back(39); break;
                            case 109: states.push_back(110); break;
                            case 114: states.push_back(115); break;
                            case 194: states.push_back(195); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 38:
                    switch(token) {
                        case davelexer::TokenType::Goto:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Goto, std::move(value));
                            states.push_back(43);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Return:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Return, std::move(value));
                            states.push_back(44);
                            read_token = true;
                            break;
                        case davelexer::TokenType::ProducedBy:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::ProducedBy, std::move(value));
                            states.push_back(45);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Goto);
                                validTokens.push_back(davelexer::TokenType::Return);
                                validTokens.push_back(davelexer::TokenType::ProducedBy);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 39:
                    switch(token) {
                        case davelexer::TokenType::ReStart:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::ReStart, std::move(value));
                            states.push_back(36);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Include:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Include, std::move(value));
                            states.push_back(35);
                            read_token = true;
                            break;
                        case davelexer::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CloseBrace, std::move(value));
                            states.push_back(41);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::ReStart);
                                validTokens.push_back(davelexer::TokenType::Include);
                                validTokens.push_back(davelexer::TokenType::CloseBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 40:
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
                            case 34: states.push_back(39); break;
                            case 109: states.push_back(110); break;
                            case 114: states.push_back(115); break;
                            case 194: states.push_back(195); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 41:
                    switch(token) {
                        case davelexer::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Semicolon, std::move(value));
                            states.push_back(42);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 42:
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
                            case 18: states.push_back(26); break;
                            case 25: states.push_back(186); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 43:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 44:
                    switch(token) {
                        case davelexer::TokenType::ProducedBy:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::ProducedBy, std::move(value));
                            states.push_back(49);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::ProducedBy);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 45:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 46:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 47:
                    switch(token) {
                        case davelexer::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Semicolon, std::move(value));
                            states.push_back(48);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Dot, std::move(value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Semicolon);
                                validTokens.push_back(davelexer::TokenType::Dot);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 48:
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
                            case 34: states.push_back(37); break;
                            case 39: states.push_back(40); break;
                            case 109: states.push_back(37); break;
                            case 110: states.push_back(40); break;
                            case 114: states.push_back(37); break;
                            case 115: states.push_back(40); break;
                            case 194: states.push_back(37); break;
                            case 195: states.push_back(40); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 49:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 50:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 51:
                    switch(token) {
                        case davelexer::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Semicolon, std::move(value));
                            states.push_back(52);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Dot, std::move(value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Semicolon);
                                validTokens.push_back(davelexer::TokenType::Dot);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 52:
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
                            case 34: states.push_back(37); break;
                            case 39: states.push_back(40); break;
                            case 109: states.push_back(37); break;
                            case 110: states.push_back(40); break;
                            case 114: states.push_back(37); break;
                            case 115: states.push_back(40); break;
                            case 194: states.push_back(37); break;
                            case 195: states.push_back(40); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 53:
                    switch(token) {
                        case davelexer::TokenType::ProducedBy:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::ProducedBy, std::move(value));
                            states.push_back(54);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Dot, std::move(value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::ProducedBy);
                                validTokens.push_back(davelexer::TokenType::Dot);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 54:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 55:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 56:
                    switch(token) {
                        case davelexer::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Semicolon, std::move(value));
                            states.push_back(57);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Dot, std::move(value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Semicolon);
                                validTokens.push_back(davelexer::TokenType::Dot);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 57:
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
                            case 34: states.push_back(37); break;
                            case 39: states.push_back(40); break;
                            case 109: states.push_back(37); break;
                            case 110: states.push_back(40); break;
                            case 114: states.push_back(37); break;
                            case 115: states.push_back(40); break;
                            case 194: states.push_back(37); break;
                            case 195: states.push_back(40); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 58:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 59:
                    // Reduce ReText: TokenType.Dot
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new CharClassReAst(i1.tkn_span, spanvalue<CharClass>(i1.tkn_span, CharClass::AnyChar))));
                        read_token = false;
                        switch(states.back()) {
                            case 36: states.push_back(64); break;
                            case 63: states.push_back(80); break;
                            case 64: states.push_back(71); break;
                            case 68: states.push_back(79); break;
                            case 71: states.push_back(71); break;
                            case 79: states.push_back(71); break;
                            case 80: states.push_back(71); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 60:
                    // Reduce ReText: TokenType.CharClass
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new CharClassReAst(i1.tkn_span, spanvalue<CharClass>(i1.tkn_span, as_charclass(i1.tkn_value)))));
                        read_token = false;
                        switch(states.back()) {
                            case 36: states.push_back(64); break;
                            case 63: states.push_back(80); break;
                            case 64: states.push_back(71); break;
                            case 68: states.push_back(79); break;
                            case 71: states.push_back(71); break;
                            case 79: states.push_back(71); break;
                            case 80: states.push_back(71); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 61:
                    switch(token) {
                        case davelexer::TokenType::Hat:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Hat, std::move(value));
                            states.push_back(82);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Char:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Char, std::move(value));
                            states.push_back(83);
                            read_token = true;
                            break;
                        case davelexer::TokenType::CharClass:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CharClass, std::move(value));
                            states.push_back(84);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Hat);
                                validTokens.push_back(davelexer::TokenType::Char);
                                validTokens.push_back(davelexer::TokenType::CharClass);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 62:
                    // Reduce ReText: TokenType.Char
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::ReText(), std::shared_ptr<ReAst>(new CharReAst(i1.tkn_span, spanvalue<wchar_t>(i1.tkn_span, as_char(i1.tkn_value)))));
                        read_token = false;
                        switch(states.back()) {
                            case 36: states.push_back(64); break;
                            case 63: states.push_back(80); break;
                            case 64: states.push_back(71); break;
                            case 68: states.push_back(79); break;
                            case 71: states.push_back(71); break;
                            case 79: states.push_back(71); break;
                            case 80: states.push_back(71); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 63:
                    switch(token) {
                        case davelexer::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenBrace, std::move(value));
                            states.push_back(58);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Dot, std::move(value));
                            states.push_back(59);
                            read_token = true;
                            break;
                        case davelexer::TokenType::CharClass:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CharClass, std::move(value));
                            states.push_back(60);
                            read_token = true;
                            break;
                        case davelexer::TokenType::OpenSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenSquare, std::move(value));
                            states.push_back(61);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Char:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Char, std::move(value));
                            states.push_back(62);
                            read_token = true;
                            break;
                        case davelexer::TokenType::OpenParenthesis:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenParenthesis, std::move(value));
                            states.push_back(63);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::OpenBrace);
                                validTokens.push_back(davelexer::TokenType::Dot);
                                validTokens.push_back(davelexer::TokenType::CharClass);
                                validTokens.push_back(davelexer::TokenType::OpenSquare);
                                validTokens.push_back(davelexer::TokenType::Char);
                                validTokens.push_back(davelexer::TokenType::OpenParenthesis);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 64:
                    switch(token) {
                        case davelexer::TokenType::CharClass:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CharClass, std::move(value));
                            states.push_back(60);
                            read_token = true;
                            break;
                        case davelexer::TokenType::ReEnd:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::ReEnd, std::move(value));
                            states.push_back(65);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Asterisk:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Asterisk, std::move(value));
                            states.push_back(66);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Question:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Question, std::move(value));
                            states.push_back(67);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Pipe:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Pipe, std::move(value));
                            states.push_back(68);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Plus:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Plus, std::move(value));
                            states.push_back(69);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Char:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Char, std::move(value));
                            states.push_back(62);
                            read_token = true;
                            break;
                        case davelexer::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenBrace, std::move(value));
                            states.push_back(70);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Dot, std::move(value));
                            states.push_back(59);
                            read_token = true;
                            break;
                        case davelexer::TokenType::OpenSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenSquare, std::move(value));
                            states.push_back(61);
                            read_token = true;
                            break;
                        case davelexer::TokenType::OpenParenthesis:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenParenthesis, std::move(value));
                            states.push_back(63);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::CharClass);
                                validTokens.push_back(davelexer::TokenType::ReEnd);
                                validTokens.push_back(davelexer::TokenType::Asterisk);
                                validTokens.push_back(davelexer::TokenType::Question);
                                validTokens.push_back(davelexer::TokenType::Pipe);
                                validTokens.push_back(davelexer::TokenType::Plus);
                                validTokens.push_back(davelexer::TokenType::Char);
                                validTokens.push_back(davelexer::TokenType::OpenBrace);
                                validTokens.push_back(davelexer::TokenType::Dot);
                                validTokens.push_back(davelexer::TokenType::OpenSquare);
                                validTokens.push_back(davelexer::TokenType::OpenParenthesis);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 65:
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
                            case 34: states.push_back(38); break;
                            case 39: states.push_back(38); break;
                            case 105: states.push_back(106); break;
                            case 109: states.push_back(38); break;
                            case 110: states.push_back(38); break;
                            case 114: states.push_back(38); break;
                            case 115: states.push_back(38); break;
                            case 190: states.push_back(191); break;
                            case 194: states.push_back(38); break;
                            case 195: states.push_back(38); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 66:
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
                            case 36: states.push_back(64); break;
                            case 63: states.push_back(80); break;
                            case 64: states.push_back(71); break;
                            case 68: states.push_back(79); break;
                            case 71: states.push_back(71); break;
                            case 79: states.push_back(71); break;
                            case 80: states.push_back(71); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 67:
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
                            case 36: states.push_back(64); break;
                            case 63: states.push_back(80); break;
                            case 64: states.push_back(71); break;
                            case 68: states.push_back(79); break;
                            case 71: states.push_back(71); break;
                            case 79: states.push_back(71); break;
                            case 80: states.push_back(71); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 68:
                    switch(token) {
                        case davelexer::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenBrace, std::move(value));
                            states.push_back(58);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Dot, std::move(value));
                            states.push_back(59);
                            read_token = true;
                            break;
                        case davelexer::TokenType::CharClass:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CharClass, std::move(value));
                            states.push_back(60);
                            read_token = true;
                            break;
                        case davelexer::TokenType::OpenSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenSquare, std::move(value));
                            states.push_back(61);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Char:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Char, std::move(value));
                            states.push_back(62);
                            read_token = true;
                            break;
                        case davelexer::TokenType::OpenParenthesis:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenParenthesis, std::move(value));
                            states.push_back(63);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::OpenBrace);
                                validTokens.push_back(davelexer::TokenType::Dot);
                                validTokens.push_back(davelexer::TokenType::CharClass);
                                validTokens.push_back(davelexer::TokenType::OpenSquare);
                                validTokens.push_back(davelexer::TokenType::Char);
                                validTokens.push_back(davelexer::TokenType::OpenParenthesis);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 69:
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
                            case 36: states.push_back(64); break;
                            case 63: states.push_back(80); break;
                            case 64: states.push_back(71); break;
                            case 68: states.push_back(79); break;
                            case 71: states.push_back(71); break;
                            case 79: states.push_back(71); break;
                            case 80: states.push_back(71); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 70:
                    switch(token) {
                        case davelexer::TokenType::Number:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Number, std::move(value));
                            states.push_back(72);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Number);
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 71:
                    switch(token) {
                        case davelexer::TokenType::Asterisk:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Asterisk, std::move(value));
                            states.push_back(66);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Pipe:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Pipe, std::move(value));
                            states.push_back(68);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Plus:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Plus, std::move(value));
                            states.push_back(69);
                            read_token = true;
                            break;
                        case davelexer::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenBrace, std::move(value));
                            states.push_back(70);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Question:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Question, std::move(value));
                            states.push_back(67);
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
                                    case 36: states.push_back(64); break;
                                    case 63: states.push_back(80); break;
                                    case 64: states.push_back(71); break;
                                    case 68: states.push_back(79); break;
                                    case 71: states.push_back(71); break;
                                    case 79: states.push_back(71); break;
                                    case 80: states.push_back(71); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 72:
                    switch(token) {
                        case davelexer::TokenType::Comma:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Comma, std::move(value));
                            states.push_back(75);
                            read_token = true;
                            break;
                        case davelexer::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CloseBrace, std::move(value));
                            states.push_back(76);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Comma);
                                validTokens.push_back(davelexer::TokenType::CloseBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 73:
                    switch(token) {
                        case davelexer::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CloseBrace, std::move(value));
                            states.push_back(74);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Dot, std::move(value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::CloseBrace);
                                validTokens.push_back(davelexer::TokenType::Dot);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 74:
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
                            case 36: states.push_back(64); break;
                            case 63: states.push_back(80); break;
                            case 64: states.push_back(71); break;
                            case 68: states.push_back(79); break;
                            case 71: states.push_back(71); break;
                            case 79: states.push_back(71); break;
                            case 80: states.push_back(71); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 75:
                    switch(token) {
                        case davelexer::TokenType::Number:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Number, std::move(value));
                            states.push_back(77);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Number);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 76:
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
                            case 36: states.push_back(64); break;
                            case 63: states.push_back(80); break;
                            case 64: states.push_back(71); break;
                            case 68: states.push_back(79); break;
                            case 71: states.push_back(71); break;
                            case 79: states.push_back(71); break;
                            case 80: states.push_back(71); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 77:
                    switch(token) {
                        case davelexer::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CloseBrace, std::move(value));
                            states.push_back(78);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::CloseBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 78:
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
                            case 36: states.push_back(64); break;
                            case 63: states.push_back(80); break;
                            case 64: states.push_back(71); break;
                            case 68: states.push_back(79); break;
                            case 71: states.push_back(71); break;
                            case 79: states.push_back(71); break;
                            case 80: states.push_back(71); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 79:
                    switch(token) {
                        case davelexer::TokenType::Asterisk:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Asterisk, std::move(value));
                            states.push_back(66);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Plus:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Plus, std::move(value));
                            states.push_back(69);
                            read_token = true;
                            break;
                        case davelexer::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenBrace, std::move(value));
                            states.push_back(70);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Question:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Question, std::move(value));
                            states.push_back(67);
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
                                    case 36: states.push_back(64); break;
                                    case 63: states.push_back(80); break;
                                    case 64: states.push_back(71); break;
                                    case 68: states.push_back(79); break;
                                    case 71: states.push_back(71); break;
                                    case 79: states.push_back(71); break;
                                    case 80: states.push_back(71); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 80:
                    switch(token) {
                        case davelexer::TokenType::CharClass:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CharClass, std::move(value));
                            states.push_back(60);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Asterisk:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Asterisk, std::move(value));
                            states.push_back(66);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Question:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Question, std::move(value));
                            states.push_back(67);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Pipe:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Pipe, std::move(value));
                            states.push_back(68);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Plus:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Plus, std::move(value));
                            states.push_back(69);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Char:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Char, std::move(value));
                            states.push_back(62);
                            read_token = true;
                            break;
                        case davelexer::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenBrace, std::move(value));
                            states.push_back(70);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Dot, std::move(value));
                            states.push_back(59);
                            read_token = true;
                            break;
                        case davelexer::TokenType::CloseParenthesis:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CloseParenthesis, std::move(value));
                            states.push_back(81);
                            read_token = true;
                            break;
                        case davelexer::TokenType::OpenSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenSquare, std::move(value));
                            states.push_back(61);
                            read_token = true;
                            break;
                        case davelexer::TokenType::OpenParenthesis:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenParenthesis, std::move(value));
                            states.push_back(63);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::CharClass);
                                validTokens.push_back(davelexer::TokenType::Asterisk);
                                validTokens.push_back(davelexer::TokenType::Question);
                                validTokens.push_back(davelexer::TokenType::Pipe);
                                validTokens.push_back(davelexer::TokenType::Plus);
                                validTokens.push_back(davelexer::TokenType::Char);
                                validTokens.push_back(davelexer::TokenType::OpenBrace);
                                validTokens.push_back(davelexer::TokenType::Dot);
                                validTokens.push_back(davelexer::TokenType::CloseParenthesis);
                                validTokens.push_back(davelexer::TokenType::OpenSquare);
                                validTokens.push_back(davelexer::TokenType::OpenParenthesis);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 81:
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
                            case 36: states.push_back(64); break;
                            case 63: states.push_back(80); break;
                            case 64: states.push_back(71); break;
                            case 68: states.push_back(79); break;
                            case 71: states.push_back(71); break;
                            case 79: states.push_back(71); break;
                            case 80: states.push_back(71); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 82:
                    switch(token) {
                        case davelexer::TokenType::Char:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Char, std::move(value));
                            states.push_back(83);
                            read_token = true;
                            break;
                        case davelexer::TokenType::CharClass:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CharClass, std::move(value));
                            states.push_back(84);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Char);
                                validTokens.push_back(davelexer::TokenType::CharClass);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 83:
                    switch(token) {
                        case davelexer::TokenType::Hyphen:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Hyphen, std::move(value));
                            states.push_back(89);
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
                                    case 61: states.push_back(85); break;
                                    case 82: states.push_back(85); break;
                                    case 86: states.push_back(87); break;
                                    case 91: states.push_back(87); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 84:
                    // Reduce CharRange: TokenType.CharClass
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::CharRange(), std::shared_ptr<CharSetAst>(new CharClassRangeAst(i1.tkn_span, as_charclass(i1.tkn_value))));
                        read_token = false;
                        switch(states.back()) {
                            case 61: states.push_back(85); break;
                            case 82: states.push_back(85); break;
                            case 86: states.push_back(87); break;
                            case 91: states.push_back(87); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 85:
                    // Reduce CharRanges: CharRange
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::CharRanges(), as_vector(std::move(i1.CharRange)));
                        read_token = false;
                        switch(states.back()) {
                            case 61: states.push_back(86); break;
                            case 82: states.push_back(91); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 86:
                    switch(token) {
                        case davelexer::TokenType::Char:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Char, std::move(value));
                            states.push_back(83);
                            read_token = true;
                            break;
                        case davelexer::TokenType::CharClass:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CharClass, std::move(value));
                            states.push_back(84);
                            read_token = true;
                            break;
                        case davelexer::TokenType::CloseSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CloseSquare, std::move(value));
                            states.push_back(88);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Char);
                                validTokens.push_back(davelexer::TokenType::CharClass);
                                validTokens.push_back(davelexer::TokenType::CloseSquare);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 87:
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
                            case 61: states.push_back(86); break;
                            case 82: states.push_back(91); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 88:
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
                            case 36: states.push_back(64); break;
                            case 63: states.push_back(80); break;
                            case 64: states.push_back(71); break;
                            case 68: states.push_back(79); break;
                            case 71: states.push_back(71); break;
                            case 79: states.push_back(71); break;
                            case 80: states.push_back(71); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 89:
                    switch(token) {
                        case davelexer::TokenType::Char:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Char, std::move(value));
                            states.push_back(90);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Char);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 90:
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
                            case 61: states.push_back(85); break;
                            case 82: states.push_back(85); break;
                            case 86: states.push_back(87); break;
                            case 91: states.push_back(87); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 91:
                    switch(token) {
                        case davelexer::TokenType::Char:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Char, std::move(value));
                            states.push_back(83);
                            read_token = true;
                            break;
                        case davelexer::TokenType::CharClass:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CharClass, std::move(value));
                            states.push_back(84);
                            read_token = true;
                            break;
                        case davelexer::TokenType::CloseSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CloseSquare, std::move(value));
                            states.push_back(92);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Char);
                                validTokens.push_back(davelexer::TokenType::CharClass);
                                validTokens.push_back(davelexer::TokenType::CloseSquare);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 92:
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
                            case 36: states.push_back(64); break;
                            case 63: states.push_back(80); break;
                            case 64: states.push_back(71); break;
                            case 68: states.push_back(79); break;
                            case 71: states.push_back(71); break;
                            case 79: states.push_back(71); break;
                            case 80: states.push_back(71); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 93:
                    switch(token) {
                        case davelexer::TokenType::Goto:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Goto, std::move(value));
                            states.push_back(94);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Semicolon, std::move(value));
                            states.push_back(95);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Return:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Return, std::move(value));
                            states.push_back(96);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Dot, std::move(value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Goto);
                                validTokens.push_back(davelexer::TokenType::Semicolon);
                                validTokens.push_back(davelexer::TokenType::Return);
                                validTokens.push_back(davelexer::TokenType::Dot);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 94:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 95:
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
                            case 34: states.push_back(37); break;
                            case 39: states.push_back(40); break;
                            case 109: states.push_back(37); break;
                            case 110: states.push_back(40); break;
                            case 114: states.push_back(37); break;
                            case 115: states.push_back(40); break;
                            case 194: states.push_back(37); break;
                            case 195: states.push_back(40); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 96:
                    switch(token) {
                        case davelexer::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Semicolon, std::move(value));
                            states.push_back(97);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 97:
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
                            case 34: states.push_back(37); break;
                            case 39: states.push_back(40); break;
                            case 109: states.push_back(37); break;
                            case 110: states.push_back(40); break;
                            case 114: states.push_back(37); break;
                            case 115: states.push_back(40); break;
                            case 194: states.push_back(37); break;
                            case 195: states.push_back(40); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 98:
                    switch(token) {
                        case davelexer::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Semicolon, std::move(value));
                            states.push_back(99);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Dot, std::move(value));
                            states.push_back(15);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Semicolon);
                                validTokens.push_back(davelexer::TokenType::Dot);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 99:
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
                            case 34: states.push_back(37); break;
                            case 39: states.push_back(40); break;
                            case 109: states.push_back(37); break;
                            case 110: states.push_back(40); break;
                            case 114: states.push_back(37); break;
                            case 115: states.push_back(40); break;
                            case 194: states.push_back(37); break;
                            case 195: states.push_back(40); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 100:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 101:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 102:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 103:
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
                            case 18: states.push_back(31); break;
                            case 25: states.push_back(31); break;
                            case 119: states.push_back(120); break;
                            case 125: states.push_back(120); break;
                            case 167: states.push_back(120); break;
                            case 171: states.push_back(120); break;
                            case 180: states.push_back(120); break;
                            case 198: states.push_back(120); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 104:
                    switch(token) {
                        case davelexer::TokenType::Equals:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Equals, std::move(value));
                            states.push_back(105);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Equals);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 105:
                    switch(token) {
                        case davelexer::TokenType::ReStart:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::ReStart, std::move(value));
                            states.push_back(36);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::ReStart);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 106:
                    switch(token) {
                        case davelexer::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Semicolon, std::move(value));
                            states.push_back(107);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 107:
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
                            case 18: states.push_back(26); break;
                            case 25: states.push_back(186); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 108:
                    switch(token) {
                        case davelexer::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenBrace, std::move(value));
                            states.push_back(109);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::OpenBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 109:
                    switch(token) {
                        case davelexer::TokenType::Include:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Include, std::move(value));
                            states.push_back(35);
                            read_token = true;
                            break;
                        case davelexer::TokenType::ReStart:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::ReStart, std::move(value));
                            states.push_back(36);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Include);
                                validTokens.push_back(davelexer::TokenType::ReStart);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 110:
                    switch(token) {
                        case davelexer::TokenType::ReStart:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::ReStart, std::move(value));
                            states.push_back(36);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Include:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Include, std::move(value));
                            states.push_back(35);
                            read_token = true;
                            break;
                        case davelexer::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CloseBrace, std::move(value));
                            states.push_back(111);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::ReStart);
                                validTokens.push_back(davelexer::TokenType::Include);
                                validTokens.push_back(davelexer::TokenType::CloseBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 111:
                    switch(token) {
                        case davelexer::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Semicolon, std::move(value));
                            states.push_back(112);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 112:
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
                            case 18: states.push_back(26); break;
                            case 25: states.push_back(186); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 113:
                    switch(token) {
                        case davelexer::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenBrace, std::move(value));
                            states.push_back(114);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::OpenBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 114:
                    switch(token) {
                        case davelexer::TokenType::Include:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Include, std::move(value));
                            states.push_back(35);
                            read_token = true;
                            break;
                        case davelexer::TokenType::ReStart:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::ReStart, std::move(value));
                            states.push_back(36);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Include);
                                validTokens.push_back(davelexer::TokenType::ReStart);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 115:
                    switch(token) {
                        case davelexer::TokenType::ReStart:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::ReStart, std::move(value));
                            states.push_back(36);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Include:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Include, std::move(value));
                            states.push_back(35);
                            read_token = true;
                            break;
                        case davelexer::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CloseBrace, std::move(value));
                            states.push_back(116);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::ReStart);
                                validTokens.push_back(davelexer::TokenType::Include);
                                validTokens.push_back(davelexer::TokenType::CloseBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 116:
                    switch(token) {
                        case davelexer::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Semicolon, std::move(value));
                            states.push_back(117);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 117:
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
                            case 18: states.push_back(26); break;
                            case 25: states.push_back(186); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 118:
                    switch(token) {
                        case davelexer::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenBrace, std::move(value));
                            states.push_back(119);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::OpenBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 119:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Documentation:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Documentation, std::move(value));
                            states.push_back(22);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                validTokens.push_back(davelexer::TokenType::Documentation);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 120:
                    switch(token) {
                        case davelexer::TokenType::Documentation:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Documentation, std::move(value));
                            states.push_back(103);
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
                                    case 18: states.push_back(27); break;
                                    case 25: states.push_back(27); break;
                                    case 119: states.push_back(122); break;
                                    case 125: states.push_back(122); break;
                                    case 167: states.push_back(122); break;
                                    case 171: states.push_back(173); break;
                                    case 180: states.push_back(173); break;
                                    case 198: states.push_back(173); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 121:
                    // Reduce EnumItems: EnumItem
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::EnumItems(), as_vector(std::move(i1.EnumItem)));
                        read_token = false;
                        switch(states.back()) {
                            case 119: states.push_back(124); break;
                            case 167: states.push_back(168); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 122:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 123:
                    // Reduce EnumItem: Ident
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::EnumItem(), std::shared_ptr<EnumItemAst>(new EnumItemAst(i1.Ident.spn(), std::vector<spantext>(), std::move(i1.Ident))));
                        read_token = false;
                        switch(states.back()) {
                            case 119: states.push_back(121); break;
                            case 125: states.push_back(128); break;
                            case 167: states.push_back(121); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 124:
                    switch(token) {
                        case davelexer::TokenType::Comma:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Comma, std::move(value));
                            states.push_back(125);
                            read_token = true;
                            break;
                        case davelexer::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CloseBrace, std::move(value));
                            states.push_back(126);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Comma);
                                validTokens.push_back(davelexer::TokenType::CloseBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 125:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Documentation:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Documentation, std::move(value));
                            states.push_back(22);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                validTokens.push_back(davelexer::TokenType::Documentation);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 126:
                    switch(token) {
                        case davelexer::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Semicolon, std::move(value));
                            states.push_back(127);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 127:
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
                            case 18: states.push_back(26); break;
                            case 25: states.push_back(186); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 128:
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
                            case 119: states.push_back(124); break;
                            case 167: states.push_back(168); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 129:
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
                            case 119: states.push_back(121); break;
                            case 125: states.push_back(128); break;
                            case 167: states.push_back(121); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 130:
                    switch(token) {
                        case davelexer::TokenType::Colon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Colon, std::move(value));
                            states.push_back(131);
                            read_token = true;
                            break;
                        case davelexer::TokenType::OpenTriangle:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenTriangle, std::move(value));
                            states.push_back(132);
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
                                    case 18: states.push_back(21); break;
                                    case 25: states.push_back(21); break;
                                    case 27: states.push_back(164); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 131:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int16:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int16, std::move(value));
                            states.push_back(141);
                            read_token = true;
                            break;
                        case davelexer::TokenType::DFloat:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::DFloat, std::move(value));
                            states.push_back(142);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int8:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int8, std::move(value));
                            states.push_back(143);
                            read_token = true;
                            break;
                        case davelexer::TokenType::StringKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::StringKeyword, std::move(value));
                            states.push_back(144);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int64:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int64, std::move(value));
                            states.push_back(145);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int32:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int32, std::move(value));
                            states.push_back(146);
                            read_token = true;
                            break;
                        case davelexer::TokenType::FloatKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::FloatKeyword, std::move(value));
                            states.push_back(147);
                            read_token = true;
                            break;
                        case davelexer::TokenType::DWord:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::DWord, std::move(value));
                            states.push_back(148);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Word:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Word, std::move(value));
                            states.push_back(149);
                            read_token = true;
                            break;
                        case davelexer::TokenType::WString:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::WString, std::move(value));
                            states.push_back(150);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                validTokens.push_back(davelexer::TokenType::Int16);
                                validTokens.push_back(davelexer::TokenType::DFloat);
                                validTokens.push_back(davelexer::TokenType::Int8);
                                validTokens.push_back(davelexer::TokenType::StringKeyword);
                                validTokens.push_back(davelexer::TokenType::Int64);
                                validTokens.push_back(davelexer::TokenType::Int32);
                                validTokens.push_back(davelexer::TokenType::FloatKeyword);
                                validTokens.push_back(davelexer::TokenType::DWord);
                                validTokens.push_back(davelexer::TokenType::Word);
                                validTokens.push_back(davelexer::TokenType::WString);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 132:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 133:
                    // Reduce TypeArgument: Ident
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeArgument(), std::shared_ptr<TypeArgumentAst>(new TypeArgumentAst(i1.Ident.spn(), std::move(i1.Ident))));
                        read_token = false;
                        switch(states.back()) {
                            case 132: states.push_back(134); break;
                            case 137: states.push_back(138); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 134:
                    // Reduce TypeArguments: TypeArgument
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeArguments(), as_vector(std::move(i1.TypeArgument)));
                        read_token = false;
                        switch(states.back()) {
                            case 132: states.push_back(135); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 135:
                    switch(token) {
                        case davelexer::TokenType::CloseTriangle:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CloseTriangle, std::move(value));
                            states.push_back(136);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Comma:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Comma, std::move(value));
                            states.push_back(137);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::CloseTriangle);
                                validTokens.push_back(davelexer::TokenType::Comma);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 136:
                    switch(token) {
                        case davelexer::TokenType::Colon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Colon, std::move(value));
                            states.push_back(139);
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
                                    case 18: states.push_back(21); break;
                                    case 25: states.push_back(21); break;
                                    case 27: states.push_back(164); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 137:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 138:
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
                            case 132: states.push_back(135); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 139:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int16:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int16, std::move(value));
                            states.push_back(141);
                            read_token = true;
                            break;
                        case davelexer::TokenType::DFloat:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::DFloat, std::move(value));
                            states.push_back(142);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int8:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int8, std::move(value));
                            states.push_back(143);
                            read_token = true;
                            break;
                        case davelexer::TokenType::StringKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::StringKeyword, std::move(value));
                            states.push_back(144);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int64:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int64, std::move(value));
                            states.push_back(145);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int32:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int32, std::move(value));
                            states.push_back(146);
                            read_token = true;
                            break;
                        case davelexer::TokenType::FloatKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::FloatKeyword, std::move(value));
                            states.push_back(147);
                            read_token = true;
                            break;
                        case davelexer::TokenType::DWord:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::DWord, std::move(value));
                            states.push_back(148);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Word:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Word, std::move(value));
                            states.push_back(149);
                            read_token = true;
                            break;
                        case davelexer::TokenType::WString:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::WString, std::move(value));
                            states.push_back(150);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                validTokens.push_back(davelexer::TokenType::Int16);
                                validTokens.push_back(davelexer::TokenType::DFloat);
                                validTokens.push_back(davelexer::TokenType::Int8);
                                validTokens.push_back(davelexer::TokenType::StringKeyword);
                                validTokens.push_back(davelexer::TokenType::Int64);
                                validTokens.push_back(davelexer::TokenType::Int32);
                                validTokens.push_back(davelexer::TokenType::FloatKeyword);
                                validTokens.push_back(davelexer::TokenType::DWord);
                                validTokens.push_back(davelexer::TokenType::Word);
                                validTokens.push_back(davelexer::TokenType::WString);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 140:
                    switch(token) {
                        case davelexer::TokenType::OpenTriangle:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenTriangle, std::move(value));
                            states.push_back(154);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Dot:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Dot, std::move(value));
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
                                    case 131: states.push_back(160); break;
                                    case 139: states.push_back(151); break;
                                    case 154: states.push_back(156); break;
                                    case 158: states.push_back(159); break;
                                    case 171: states.push_back(174); break;
                                    case 173: states.push_back(184); break;
                                    case 180: states.push_back(174); break;
                                    case 198: states.push_back(174); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 141:
                    // Reduce TypeReference: TokenType.Int16
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeReference(), std::shared_ptr<TypeReferenceAst>(new TypeReferenceAst(i1.tkn_span, get_system_symbolreference(L"Int16"), std::vector<std::shared_ptr<TypeReferenceAst>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 131: states.push_back(160); break;
                            case 139: states.push_back(151); break;
                            case 154: states.push_back(156); break;
                            case 158: states.push_back(159); break;
                            case 171: states.push_back(174); break;
                            case 173: states.push_back(184); break;
                            case 180: states.push_back(174); break;
                            case 198: states.push_back(174); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 142:
                    // Reduce TypeReference: TokenType.DFloat
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeReference(), std::shared_ptr<TypeReferenceAst>(new TypeReferenceAst(i1.tkn_span, get_system_symbolreference(L"DoubleFloat"), std::vector<std::shared_ptr<TypeReferenceAst>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 131: states.push_back(160); break;
                            case 139: states.push_back(151); break;
                            case 154: states.push_back(156); break;
                            case 158: states.push_back(159); break;
                            case 171: states.push_back(174); break;
                            case 173: states.push_back(184); break;
                            case 180: states.push_back(174); break;
                            case 198: states.push_back(174); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 143:
                    // Reduce TypeReference: TokenType.Int8
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeReference(), std::shared_ptr<TypeReferenceAst>(new TypeReferenceAst(i1.tkn_span, get_system_symbolreference(L"Int8"), std::vector<std::shared_ptr<TypeReferenceAst>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 131: states.push_back(160); break;
                            case 139: states.push_back(151); break;
                            case 154: states.push_back(156); break;
                            case 158: states.push_back(159); break;
                            case 171: states.push_back(174); break;
                            case 173: states.push_back(184); break;
                            case 180: states.push_back(174); break;
                            case 198: states.push_back(174); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 144:
                    // Reduce TypeReference: TokenType.StringKeyword
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeReference(), std::shared_ptr<TypeReferenceAst>(new TypeReferenceAst(i1.tkn_span, get_system_symbolreference(L"String"), std::vector<std::shared_ptr<TypeReferenceAst>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 131: states.push_back(160); break;
                            case 139: states.push_back(151); break;
                            case 154: states.push_back(156); break;
                            case 158: states.push_back(159); break;
                            case 171: states.push_back(174); break;
                            case 173: states.push_back(184); break;
                            case 180: states.push_back(174); break;
                            case 198: states.push_back(174); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 145:
                    // Reduce TypeReference: TokenType.Int64
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeReference(), std::shared_ptr<TypeReferenceAst>(new TypeReferenceAst(i1.tkn_span, get_system_symbolreference(L"Int64"), std::vector<std::shared_ptr<TypeReferenceAst>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 131: states.push_back(160); break;
                            case 139: states.push_back(151); break;
                            case 154: states.push_back(156); break;
                            case 158: states.push_back(159); break;
                            case 171: states.push_back(174); break;
                            case 173: states.push_back(184); break;
                            case 180: states.push_back(174); break;
                            case 198: states.push_back(174); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 146:
                    // Reduce TypeReference: TokenType.Int32
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeReference(), std::shared_ptr<TypeReferenceAst>(new TypeReferenceAst(i1.tkn_span, get_system_symbolreference(L"Int32"), std::vector<std::shared_ptr<TypeReferenceAst>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 131: states.push_back(160); break;
                            case 139: states.push_back(151); break;
                            case 154: states.push_back(156); break;
                            case 158: states.push_back(159); break;
                            case 171: states.push_back(174); break;
                            case 173: states.push_back(184); break;
                            case 180: states.push_back(174); break;
                            case 198: states.push_back(174); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 147:
                    // Reduce TypeReference: TokenType.FloatKeyword
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeReference(), std::shared_ptr<TypeReferenceAst>(new TypeReferenceAst(i1.tkn_span, get_system_symbolreference(L"Float"), std::vector<std::shared_ptr<TypeReferenceAst>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 131: states.push_back(160); break;
                            case 139: states.push_back(151); break;
                            case 154: states.push_back(156); break;
                            case 158: states.push_back(159); break;
                            case 171: states.push_back(174); break;
                            case 173: states.push_back(184); break;
                            case 180: states.push_back(174); break;
                            case 198: states.push_back(174); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 148:
                    // Reduce TypeReference: TokenType.DWord
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeReference(), std::shared_ptr<TypeReferenceAst>(new TypeReferenceAst(i1.tkn_span, get_system_symbolreference(L"DoubleWord"), std::vector<std::shared_ptr<TypeReferenceAst>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 131: states.push_back(160); break;
                            case 139: states.push_back(151); break;
                            case 154: states.push_back(156); break;
                            case 158: states.push_back(159); break;
                            case 171: states.push_back(174); break;
                            case 173: states.push_back(184); break;
                            case 180: states.push_back(174); break;
                            case 198: states.push_back(174); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 149:
                    // Reduce TypeReference: TokenType.Word
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeReference(), std::shared_ptr<TypeReferenceAst>(new TypeReferenceAst(i1.tkn_span, get_system_symbolreference(L"Word"), std::vector<std::shared_ptr<TypeReferenceAst>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 131: states.push_back(160); break;
                            case 139: states.push_back(151); break;
                            case 154: states.push_back(156); break;
                            case 158: states.push_back(159); break;
                            case 171: states.push_back(174); break;
                            case 173: states.push_back(184); break;
                            case 180: states.push_back(174); break;
                            case 198: states.push_back(174); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 150:
                    // Reduce TypeReference: TokenType.WString
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeReference(), std::shared_ptr<TypeReferenceAst>(new TypeReferenceAst(i1.tkn_span, get_system_symbolreference(L"WString"), std::vector<std::shared_ptr<TypeReferenceAst>>())));
                        read_token = false;
                        switch(states.back()) {
                            case 131: states.push_back(160); break;
                            case 139: states.push_back(151); break;
                            case 154: states.push_back(156); break;
                            case 158: states.push_back(159); break;
                            case 171: states.push_back(174); break;
                            case 173: states.push_back(184); break;
                            case 180: states.push_back(174); break;
                            case 198: states.push_back(174); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 151:
                    switch(token) {
                        case davelexer::TokenType::OpenSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenSquare, std::move(value));
                            states.push_back(152);
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
                                    case 18: states.push_back(21); break;
                                    case 25: states.push_back(21); break;
                                    case 27: states.push_back(164); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 152:
                    switch(token) {
                        case davelexer::TokenType::CloseSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CloseSquare, std::move(value));
                            states.push_back(153);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::CloseSquare);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 153:
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
                            case 131: states.push_back(160); break;
                            case 139: states.push_back(151); break;
                            case 154: states.push_back(156); break;
                            case 158: states.push_back(159); break;
                            case 171: states.push_back(174); break;
                            case 173: states.push_back(184); break;
                            case 180: states.push_back(174); break;
                            case 198: states.push_back(174); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 154:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int8:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int8, std::move(value));
                            states.push_back(143);
                            read_token = true;
                            break;
                        case davelexer::TokenType::StringKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::StringKeyword, std::move(value));
                            states.push_back(144);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int64:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int64, std::move(value));
                            states.push_back(145);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int32:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int32, std::move(value));
                            states.push_back(146);
                            read_token = true;
                            break;
                        case davelexer::TokenType::FloatKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::FloatKeyword, std::move(value));
                            states.push_back(147);
                            read_token = true;
                            break;
                        case davelexer::TokenType::DFloat:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::DFloat, std::move(value));
                            states.push_back(142);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int16:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int16, std::move(value));
                            states.push_back(141);
                            read_token = true;
                            break;
                        case davelexer::TokenType::DWord:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::DWord, std::move(value));
                            states.push_back(148);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Word:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Word, std::move(value));
                            states.push_back(149);
                            read_token = true;
                            break;
                        case davelexer::TokenType::WString:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::WString, std::move(value));
                            states.push_back(150);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                validTokens.push_back(davelexer::TokenType::Int8);
                                validTokens.push_back(davelexer::TokenType::StringKeyword);
                                validTokens.push_back(davelexer::TokenType::Int64);
                                validTokens.push_back(davelexer::TokenType::Int32);
                                validTokens.push_back(davelexer::TokenType::FloatKeyword);
                                validTokens.push_back(davelexer::TokenType::DFloat);
                                validTokens.push_back(davelexer::TokenType::Int16);
                                validTokens.push_back(davelexer::TokenType::DWord);
                                validTokens.push_back(davelexer::TokenType::Word);
                                validTokens.push_back(davelexer::TokenType::WString);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 155:
                    switch(token) {
                        case davelexer::TokenType::CloseTriangle:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CloseTriangle, std::move(value));
                            states.push_back(157);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Comma:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Comma, std::move(value));
                            states.push_back(158);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::CloseTriangle);
                                validTokens.push_back(davelexer::TokenType::Comma);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 156:
                    switch(token) {
                        case davelexer::TokenType::OpenSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenSquare, std::move(value));
                            states.push_back(152);
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
                                    case 154: states.push_back(155); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 157:
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
                            case 131: states.push_back(160); break;
                            case 139: states.push_back(151); break;
                            case 154: states.push_back(156); break;
                            case 158: states.push_back(159); break;
                            case 171: states.push_back(174); break;
                            case 173: states.push_back(184); break;
                            case 180: states.push_back(174); break;
                            case 198: states.push_back(174); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 158:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int16:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int16, std::move(value));
                            states.push_back(141);
                            read_token = true;
                            break;
                        case davelexer::TokenType::DFloat:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::DFloat, std::move(value));
                            states.push_back(142);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int8:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int8, std::move(value));
                            states.push_back(143);
                            read_token = true;
                            break;
                        case davelexer::TokenType::StringKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::StringKeyword, std::move(value));
                            states.push_back(144);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int64:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int64, std::move(value));
                            states.push_back(145);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int32:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int32, std::move(value));
                            states.push_back(146);
                            read_token = true;
                            break;
                        case davelexer::TokenType::FloatKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::FloatKeyword, std::move(value));
                            states.push_back(147);
                            read_token = true;
                            break;
                        case davelexer::TokenType::DWord:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::DWord, std::move(value));
                            states.push_back(148);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Word:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Word, std::move(value));
                            states.push_back(149);
                            read_token = true;
                            break;
                        case davelexer::TokenType::WString:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::WString, std::move(value));
                            states.push_back(150);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                validTokens.push_back(davelexer::TokenType::Int16);
                                validTokens.push_back(davelexer::TokenType::DFloat);
                                validTokens.push_back(davelexer::TokenType::Int8);
                                validTokens.push_back(davelexer::TokenType::StringKeyword);
                                validTokens.push_back(davelexer::TokenType::Int64);
                                validTokens.push_back(davelexer::TokenType::Int32);
                                validTokens.push_back(davelexer::TokenType::FloatKeyword);
                                validTokens.push_back(davelexer::TokenType::DWord);
                                validTokens.push_back(davelexer::TokenType::Word);
                                validTokens.push_back(davelexer::TokenType::WString);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 159:
                    switch(token) {
                        case davelexer::TokenType::OpenSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenSquare, std::move(value));
                            states.push_back(152);
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
                                    case 154: states.push_back(155); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 160:
                    switch(token) {
                        case davelexer::TokenType::OpenSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenSquare, std::move(value));
                            states.push_back(152);
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
                                    case 18: states.push_back(21); break;
                                    case 25: states.push_back(21); break;
                                    case 27: states.push_back(164); break;
                                    default: assert(false); states.push_back(0); break;
                                }
                            }
                            break;
                    }
                    break;
                case 161:
                    switch(token) {
                        case davelexer::TokenType::Type:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Type, std::move(value));
                            states.push_back(163);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Type);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 162:
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
                            case 18: states.push_back(29); break;
                            case 25: states.push_back(29); break;
                            case 27: states.push_back(29); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 163:
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
                            case 18: states.push_back(29); break;
                            case 25: states.push_back(29); break;
                            case 27: states.push_back(29); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 164:
                    switch(token) {
                        case davelexer::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenBrace, std::move(value));
                            states.push_back(171);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Semicolon, std::move(value));
                            states.push_back(172);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::OpenBrace);
                                validTokens.push_back(davelexer::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 165:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 166:
                    switch(token) {
                        case davelexer::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenBrace, std::move(value));
                            states.push_back(167);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::OpenBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 167:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Documentation:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Documentation, std::move(value));
                            states.push_back(22);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                validTokens.push_back(davelexer::TokenType::Documentation);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 168:
                    switch(token) {
                        case davelexer::TokenType::Comma:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Comma, std::move(value));
                            states.push_back(125);
                            read_token = true;
                            break;
                        case davelexer::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CloseBrace, std::move(value));
                            states.push_back(169);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Comma);
                                validTokens.push_back(davelexer::TokenType::CloseBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 169:
                    switch(token) {
                        case davelexer::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Semicolon, std::move(value));
                            states.push_back(170);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 170:
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
                            case 18: states.push_back(26); break;
                            case 25: states.push_back(186); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 171:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case davelexer::TokenType::FloatKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::FloatKeyword, std::move(value));
                            states.push_back(147);
                            read_token = true;
                            break;
                        case davelexer::TokenType::WString:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::WString, std::move(value));
                            states.push_back(150);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int64:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int64, std::move(value));
                            states.push_back(145);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int32:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int32, std::move(value));
                            states.push_back(146);
                            read_token = true;
                            break;
                        case davelexer::TokenType::DFloat:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::DFloat, std::move(value));
                            states.push_back(142);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int16:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int16, std::move(value));
                            states.push_back(141);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Documentation:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Documentation, std::move(value));
                            states.push_back(22);
                            read_token = true;
                            break;
                        case davelexer::TokenType::StringKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::StringKeyword, std::move(value));
                            states.push_back(144);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int8:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int8, std::move(value));
                            states.push_back(143);
                            read_token = true;
                            break;
                        case davelexer::TokenType::DWord:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::DWord, std::move(value));
                            states.push_back(148);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Word:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Word, std::move(value));
                            states.push_back(149);
                            read_token = true;
                            break;
                        case davelexer::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CloseBrace, std::move(value));
                            states.push_back(177);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                validTokens.push_back(davelexer::TokenType::FloatKeyword);
                                validTokens.push_back(davelexer::TokenType::WString);
                                validTokens.push_back(davelexer::TokenType::Int64);
                                validTokens.push_back(davelexer::TokenType::Int32);
                                validTokens.push_back(davelexer::TokenType::DFloat);
                                validTokens.push_back(davelexer::TokenType::Int16);
                                validTokens.push_back(davelexer::TokenType::Documentation);
                                validTokens.push_back(davelexer::TokenType::StringKeyword);
                                validTokens.push_back(davelexer::TokenType::Int8);
                                validTokens.push_back(davelexer::TokenType::DWord);
                                validTokens.push_back(davelexer::TokenType::Word);
                                validTokens.push_back(davelexer::TokenType::CloseBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 172:
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
                            case 18: states.push_back(26); break;
                            case 25: states.push_back(186); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 173:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int16:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int16, std::move(value));
                            states.push_back(141);
                            read_token = true;
                            break;
                        case davelexer::TokenType::DFloat:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::DFloat, std::move(value));
                            states.push_back(142);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int8:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int8, std::move(value));
                            states.push_back(143);
                            read_token = true;
                            break;
                        case davelexer::TokenType::StringKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::StringKeyword, std::move(value));
                            states.push_back(144);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int64:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int64, std::move(value));
                            states.push_back(145);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int32:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int32, std::move(value));
                            states.push_back(146);
                            read_token = true;
                            break;
                        case davelexer::TokenType::FloatKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::FloatKeyword, std::move(value));
                            states.push_back(147);
                            read_token = true;
                            break;
                        case davelexer::TokenType::DWord:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::DWord, std::move(value));
                            states.push_back(148);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Word:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Word, std::move(value));
                            states.push_back(149);
                            read_token = true;
                            break;
                        case davelexer::TokenType::WString:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::WString, std::move(value));
                            states.push_back(150);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                validTokens.push_back(davelexer::TokenType::Int16);
                                validTokens.push_back(davelexer::TokenType::DFloat);
                                validTokens.push_back(davelexer::TokenType::Int8);
                                validTokens.push_back(davelexer::TokenType::StringKeyword);
                                validTokens.push_back(davelexer::TokenType::Int64);
                                validTokens.push_back(davelexer::TokenType::Int32);
                                validTokens.push_back(davelexer::TokenType::FloatKeyword);
                                validTokens.push_back(davelexer::TokenType::DWord);
                                validTokens.push_back(davelexer::TokenType::Word);
                                validTokens.push_back(davelexer::TokenType::WString);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 174:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case davelexer::TokenType::OpenSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenSquare, std::move(value));
                            states.push_back(152);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                validTokens.push_back(davelexer::TokenType::OpenSquare);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 175:
                    // Reduce TypeProperties: TypeProperty
                    if (true) {
                        auto i1 = std::move(values.back());
                        values.pop_back();
                        states.pop_back();
                         values.emplace_back(lexical_type::TypeProperties(), as_vector(std::move(i1.TypeProperty)));
                        read_token = false;
                        switch(states.back()) {
                            case 171: states.push_back(176); break;
                            case 198: states.push_back(200); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 176:
                    switch(token) {
                        case davelexer::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CloseBrace, std::move(value));
                            states.push_back(179);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Comma:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Comma, std::move(value));
                            states.push_back(180);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::CloseBrace);
                                validTokens.push_back(davelexer::TokenType::Comma);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 177:
                    switch(token) {
                        case davelexer::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Semicolon, std::move(value));
                            states.push_back(178);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 178:
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
                            case 18: states.push_back(26); break;
                            case 25: states.push_back(186); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 179:
                    switch(token) {
                        case davelexer::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Semicolon, std::move(value));
                            states.push_back(182);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 180:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case davelexer::TokenType::FloatKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::FloatKeyword, std::move(value));
                            states.push_back(147);
                            read_token = true;
                            break;
                        case davelexer::TokenType::WString:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::WString, std::move(value));
                            states.push_back(150);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int64:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int64, std::move(value));
                            states.push_back(145);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int32:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int32, std::move(value));
                            states.push_back(146);
                            read_token = true;
                            break;
                        case davelexer::TokenType::DFloat:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::DFloat, std::move(value));
                            states.push_back(142);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int16:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int16, std::move(value));
                            states.push_back(141);
                            read_token = true;
                            break;
                        case davelexer::TokenType::StringKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::StringKeyword, std::move(value));
                            states.push_back(144);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int8:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int8, std::move(value));
                            states.push_back(143);
                            read_token = true;
                            break;
                        case davelexer::TokenType::DWord:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::DWord, std::move(value));
                            states.push_back(148);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Documentation:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Documentation, std::move(value));
                            states.push_back(22);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Word:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Word, std::move(value));
                            states.push_back(149);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                validTokens.push_back(davelexer::TokenType::FloatKeyword);
                                validTokens.push_back(davelexer::TokenType::WString);
                                validTokens.push_back(davelexer::TokenType::Int64);
                                validTokens.push_back(davelexer::TokenType::Int32);
                                validTokens.push_back(davelexer::TokenType::DFloat);
                                validTokens.push_back(davelexer::TokenType::Int16);
                                validTokens.push_back(davelexer::TokenType::StringKeyword);
                                validTokens.push_back(davelexer::TokenType::Int8);
                                validTokens.push_back(davelexer::TokenType::DWord);
                                validTokens.push_back(davelexer::TokenType::Documentation);
                                validTokens.push_back(davelexer::TokenType::Word);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 181:
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
                            case 171: states.push_back(176); break;
                            case 198: states.push_back(200); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 182:
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
                            case 18: states.push_back(26); break;
                            case 25: states.push_back(186); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 183:
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
                            case 171: states.push_back(175); break;
                            case 180: states.push_back(181); break;
                            case 198: states.push_back(175); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 184:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case davelexer::TokenType::OpenSquare:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenSquare, std::move(value));
                            states.push_back(152);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                validTokens.push_back(davelexer::TokenType::OpenSquare);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 185:
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
                            case 171: states.push_back(175); break;
                            case 180: states.push_back(181); break;
                            case 198: states.push_back(175); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 186:
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
                            case 18: states.push_back(25); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 187:
                    switch(token) {
                        case davelexer::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Semicolon, std::move(value));
                            states.push_back(188);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 188:
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
                            case 1: states.push_back(208); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 189:
                    switch(token) {
                        case davelexer::TokenType::Equals:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Equals, std::move(value));
                            states.push_back(190);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Equals);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 190:
                    switch(token) {
                        case davelexer::TokenType::ReStart:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::ReStart, std::move(value));
                            states.push_back(36);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::ReStart);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 191:
                    switch(token) {
                        case davelexer::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Semicolon, std::move(value));
                            states.push_back(192);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 192:
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
                            case 18: states.push_back(26); break;
                            case 25: states.push_back(186); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 193:
                    switch(token) {
                        case davelexer::TokenType::OpenBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::OpenBrace, std::move(value));
                            states.push_back(194);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::OpenBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 194:
                    switch(token) {
                        case davelexer::TokenType::Include:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Include, std::move(value));
                            states.push_back(35);
                            read_token = true;
                            break;
                        case davelexer::TokenType::ReStart:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::ReStart, std::move(value));
                            states.push_back(36);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Include);
                                validTokens.push_back(davelexer::TokenType::ReStart);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 195:
                    switch(token) {
                        case davelexer::TokenType::ReStart:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::ReStart, std::move(value));
                            states.push_back(36);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Include:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Include, std::move(value));
                            states.push_back(35);
                            read_token = true;
                            break;
                        case davelexer::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CloseBrace, std::move(value));
                            states.push_back(196);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::ReStart);
                                validTokens.push_back(davelexer::TokenType::Include);
                                validTokens.push_back(davelexer::TokenType::CloseBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 196:
                    switch(token) {
                        case davelexer::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Semicolon, std::move(value));
                            states.push_back(197);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 197:
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
                            case 18: states.push_back(26); break;
                            case 25: states.push_back(186); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 198:
                    switch(token) {
                        case davelexer::TokenType::Identifier:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Identifier, std::move(value));
                            states.push_back(11);
                            read_token = true;
                            break;
                        case davelexer::TokenType::FloatKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::FloatKeyword, std::move(value));
                            states.push_back(147);
                            read_token = true;
                            break;
                        case davelexer::TokenType::WString:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::WString, std::move(value));
                            states.push_back(150);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int64:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int64, std::move(value));
                            states.push_back(145);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int32:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int32, std::move(value));
                            states.push_back(146);
                            read_token = true;
                            break;
                        case davelexer::TokenType::DFloat:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::DFloat, std::move(value));
                            states.push_back(142);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int16:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int16, std::move(value));
                            states.push_back(141);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Documentation:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Documentation, std::move(value));
                            states.push_back(22);
                            read_token = true;
                            break;
                        case davelexer::TokenType::StringKeyword:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::StringKeyword, std::move(value));
                            states.push_back(144);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Int8:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Int8, std::move(value));
                            states.push_back(143);
                            read_token = true;
                            break;
                        case davelexer::TokenType::DWord:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::DWord, std::move(value));
                            states.push_back(148);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Word:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Word, std::move(value));
                            states.push_back(149);
                            read_token = true;
                            break;
                        case davelexer::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CloseBrace, std::move(value));
                            states.push_back(201);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Identifier);
                                validTokens.push_back(davelexer::TokenType::FloatKeyword);
                                validTokens.push_back(davelexer::TokenType::WString);
                                validTokens.push_back(davelexer::TokenType::Int64);
                                validTokens.push_back(davelexer::TokenType::Int32);
                                validTokens.push_back(davelexer::TokenType::DFloat);
                                validTokens.push_back(davelexer::TokenType::Int16);
                                validTokens.push_back(davelexer::TokenType::Documentation);
                                validTokens.push_back(davelexer::TokenType::StringKeyword);
                                validTokens.push_back(davelexer::TokenType::Int8);
                                validTokens.push_back(davelexer::TokenType::DWord);
                                validTokens.push_back(davelexer::TokenType::Word);
                                validTokens.push_back(davelexer::TokenType::CloseBrace);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 199:
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
                            case 18: states.push_back(26); break;
                            case 25: states.push_back(186); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 200:
                    switch(token) {
                        case davelexer::TokenType::CloseBrace:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::CloseBrace, std::move(value));
                            states.push_back(203);
                            read_token = true;
                            break;
                        case davelexer::TokenType::Comma:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Comma, std::move(value));
                            states.push_back(180);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::CloseBrace);
                                validTokens.push_back(davelexer::TokenType::Comma);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 201:
                    switch(token) {
                        case davelexer::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Semicolon, std::move(value));
                            states.push_back(202);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 202:
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
                            case 18: states.push_back(26); break;
                            case 25: states.push_back(186); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 203:
                    switch(token) {
                        case davelexer::TokenType::Semicolon:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Semicolon, std::move(value));
                            states.push_back(204);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Semicolon);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 204:
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
                            case 18: states.push_back(26); break;
                            case 25: states.push_back(186); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 205:
                    switch(token) {
                        case davelexer::TokenType::Type:
                            values.emplace_back(span(position(start_line, start_column), position(end_line, end_column)), davelexer::TokenType::Type, std::move(value));
                            states.push_back(207);
                            read_token = true;
                            break;
                        default:
                            // Error - We did not read an expected token, and we also cannot reduce
                            if(true) {
                                std::vector<davelexer::TokenType> validTokens;
                                validTokens.push_back(davelexer::TokenType::Type);
                                log::error::UnexpectedToken(logger, cntr, start_line, start_column, end_line, end_column, token, value, validTokens);
                                return false;
                            }
                            break;
                    }
                    break;
                case 206:
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
                            case 18: states.push_back(29); break;
                            case 25: states.push_back(29); break;
                            case 27: states.push_back(29); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 207:
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
                            case 18: states.push_back(29); break;
                            case 25: states.push_back(29); break;
                            case 27: states.push_back(29); break;
                            default: assert(false); states.push_back(0); break;
                        }
                    }
                    break;
                case 208:
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
