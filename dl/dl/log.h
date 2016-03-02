//
//  log.h
//  dl
//
//  Created by David Lindeque on 06/01/2016.
//  Copyright © 2016 David Lindeque. All rights reserved.
//

#ifndef log_h
#define log_h

#include <vector>
#include <sstream>
#include "dl.dl.hpp"
#include "../../common/logger.h"
#include "../../common/container.h"
#include "../../common/span.h"

namespace davecommon {

    struct log {
    private:
        static inline auto format_qname(const std::vector<davelexer::AstToken<std::wstring>> &name) -> std::wstring {
            std::wstring n;
            if (!name.empty()) {
                n = name[0].Value;
                for(size_t i = 1;i<name.size();i++) {
                    n += L'.';
                    n += name[i].Value;
                }
            }
            return n;
        }
    public:
        struct error {
            static inline auto UnexpectedEndOfFile(logger *logger, const std::shared_ptr<container> &cntr) -> void {
                logger->write(davecommon::severity::error, cntr, davecommon::span(), L"Unexpected end-of-file");
            }
            static inline auto UnexpectedToken(logger *logger, const std::shared_ptr<container> &cntr, const position &begin, const position &end, const davelexer::TokenType &given_tkn, const std::wstring &given_value, const std::vector<davelexer::TokenType> &valid_tkns) -> void {
                std::wstringstream stm;
                stm << L"Unexpected token '" << text(given_tkn) << L"' encountered. Expected any of ";
                bool first = true;
                for(auto &tkn : valid_tkns) {
                    if (first) {
                        stm << L',';
                    } else {
                        first = false;
                    }
                    stm << L'\'' << text(tkn) << L'\'';
                }
                logger->write(davecommon::severity::error, cntr, davecommon::span(begin, end), stm.str());
            }
            static inline auto UnexpectedToken(logger *logger, const std::shared_ptr<container> &cntr, const long &start_line, const long &start_column, const long &end_line, const long &end_column, const davelexer::TokenType &given_tkn, const std::wstring &given_value, const std::vector<davelexer::TokenType> &valid_tkns) -> void {
                UnexpectedToken(logger, cntr, position(start_line, start_column), position(end_line, end_column), given_tkn, given_value, valid_tkns);
            }
            static inline auto PatternNotFound(logger *logger, const std::shared_ptr<container> &cntr, const span &spn, const std::vector<davelexer::AstToken<std::wstring>> &pattern) -> void {
                std::wstringstream stm;
                stm << L"The pattern '" << format_qname(pattern) << L"' could not be found";
                logger->write(davecommon::severity::error, cntr, spn, stm.str());
            }
            template<typename _Iterator> static inline auto PatternFoundMoreThanOnce(logger *logger, const std::shared_ptr<container> &cntr, const span &spn, const std::vector<davelexer::AstToken<std::wstring>> &pattern, const _Iterator &begin, const _Iterator &end) -> void {
                std::wstringstream stm;
                stm << L"The pattern '" << format_qname(pattern) << L"' was matched more than once. See";
                for(auto p = begin; p != end; p++) {
                    stm << std::endl << L"  " << p->item()->Spn.begin.line << L':' << p->item()->Spn.begin.column << L'-' << p->item()->Spn.end.line << L':' << p->item()->Spn.end.column << L' ' << p->cntr()->name();
                }
                logger->write(davecommon::severity::error, cntr, spn, stm.str());
            }
        };
    };
        
}


#endif /* log_h */
