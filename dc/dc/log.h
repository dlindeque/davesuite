//
//  log.h
//  dl
//
//  Created by David Lindeque on 06/01/2016.
//  Copyright © 2016 David Lindeque. All rights reserved.
//

#pragma once

#include <vector>
#include <sstream>
#include "dc.dl.h"
#include "logger.h"
#include "container.h"
#include "span.h"

namespace dc {

    struct log {
    public:
        static inline auto printable(wchar_t ch) -> std::wstring {
            std::wstring s;
            if (ch >= L'a' && ch <= L'z') {
                s += ch;
            } 
            else if (ch >= L'A' && ch <= L'Z') {
                s += ch;
            }
            else if (ch >= L'0' && ch <= L'9') {
                s += ch;
            }
            else if (ch == L'!' || ch == L'@' || ch == L'€' || ch == L'#' || ch == L'£' || ch == L'$' || ch == L'%'
                || ch == L'^' || ch == L'&' || ch == L'*' || ch == L'(' || ch == L')' || ch == L'-' || ch == L'_'
                || ch == L'=' || ch == L'+' || ch == L'{' || ch == L'}' || ch == L'[' || ch == L']' || ch == L':'
                || ch == L';' || ch == L'"' || ch == L'\'' || ch == L'|' || ch == L'\\' || ch == L'<'
                || ch == L',' || ch == L'>' || ch == L'.' || ch == L'?' || ch == L'/' || ch == L'`' || ch == L'~') {
                s += ch;
            }
            else if (ch == (wchar_t)0) {
                s.append(L"<start>");
            }
            else if (ch == (wchar_t)(WCHAR_MAX - 1)) {
                s.append(L"<end>");
            }
            else if (ch == (wchar_t)WCHAR_MAX) {
                s.append(L"<eod>");
            }
            else if (ch == L'\n') {
                s.append(L"\\n");
            }
            else if (ch == L' ') {
                s.append(L" ");
            }
            else if (ch == L'\t') {
                s.append(L"\\t");
            }
            else if (ch == L'\v') {
                s.append(L"\\v");
            }
            else if (ch == L'\f') {
                s.append(L"\\f");
            }
            else if (ch == L'\r') {
                s.append(L"\\r");
            }
            else if (ch == L'\b') {
                s.append(L"\\b");
            }
            else {
                s.append(L"\\x");
                s.append(std::to_wstring((int)ch));
            }
            return s;
        }
        static inline auto printable(const std::pair<wchar_t, wchar_t> &range) -> std::wstring {
            if (range.first == WCHAR_MAX && range.second == WCHAR_MAX) {
                return L"<eod>";
            }
            
            std::wstring s;
            if (range.first == range.second) {
                if (range.first != (wchar_t)0) {
                    //s += L'(';
                    //s.append(printable(range.first - 1));
                    //s += L')';
                    s += L'\'';
                    s.append(printable(range.first));
                    s += L'\'';
                    //if (range.first != WCHAR_MAX - 1) {
                    //    s += L'(';
                    //    s.append(printable(range.first + 1));
                    //    s += L')';
                    //}
                    return s;
                }
                else {
                    s += L'\'';
                    s.append(printable(range.first));
                    s += L'\'';
                    return s;    
                }
            }
            else {
                //if (range.first != (wchar_t)0) {
                //    s += L'(';
                //    s.append(printable(range.first - 1));
                //    s += L')';
                //}

                s += L'\'';
                s.append(printable(range.first));
                s.append(L"'-'");
                s.append(printable(range.second));
                s += L'\'';

                //if (range.second != WCHAR_MAX && range.second != WCHAR_MAX - 1) {
                //    s += L'(';
                //    s.append(printable(range.second + 1));
                //    s += L')';
                //}

                return s;
            }
        }
    public:
        struct info {
            static inline auto ProcessingFile(logger *logger, const std::string &fn) -> void {
                std::wstringstream stm;
                stm << L"Processing " << std::wstring(fn.begin(), fn.end());
                logger->write(severity::info, 0x01, std::shared_ptr<container>(), span(), stm.str());
            }
        };
        struct warning {
            static inline auto TokenLost(logger *logger, const NfaAction &action, const std::vector<NfaAction> &preceding) -> void {
                std::wstringstream stm;
                stm << L"The token " << action.TokenName << " cannot be produced. The token is preceded by:";
                for(auto &p : preceding) {
                    auto fn = p.cspn.cntr->filename();
                    stm << std::endl << L"  " << p.TokenName << L" defined in " << std::wstring(fn.begin(), fn.end()) << L' ' << p.cspn.spn.begin.line << L':' << p.cspn.spn.begin.column << L'-' << p.cspn.spn.end.line << L':' << p.cspn.spn.end.column;
                }
                logger->write(severity::warning, 0x101, action.cspn.cntr, action.cspn.spn, stm.str());
            }
            static inline auto Rewinding(logger *logger, const NfaAction &rewindaction, const std::wstring &sample, const int steps, const NfaAction &unreached) -> void {
                std::wstringstream stm;
                stm << L"The sequence '" << sample << "' can result in a rewind of " << steps << L" steps to reach " << rewindaction.TokenName << L". The unreached token is " << unreached.TokenName;
                logger->write(severity::warning, 0x102, rewindaction.cspn.cntr, rewindaction.cspn.spn, stm.str());
            }
        };
        struct error {
            static inline auto UnexpectedEndOfFile(logger *logger, const std::shared_ptr<container> &cntr) -> void {
                logger->write(severity::error, 0x11, cntr, span(), L"Unexpected end-of-file");
            }
            static inline auto UnexpectedToken(logger *logger, const std::shared_ptr<container> &cntr, const position &begin, const position &end, const TokenType &given_tkn, const std::wstring &given_value, const std::vector<TokenType> &valid_tkns) -> void {
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
                logger->write(severity::error, 0x12, cntr, span(begin, end), stm.str());
            }
            static inline auto SymbolNotFound(logger *logger, const std::wstring &symbol_type, const std::shared_ptr<container> &cntr, const span &spn, const symbolreference &name) -> void {
                std::wstringstream stm;
                stm << L"The " << symbol_type << " '" << name << L"' could not be found";
                logger->write(severity::error, 0x101, cntr, spn, stm.str());
            }
            static inline auto SymbolFoundMoreThanOnce(logger *logger, const std::wstring &symbol_type, const std::shared_ptr<container> &cntr, const span &spn, const symbolreference &name, const std::shared_ptr<container> &othercntr1, const span &otherspn1, const std::shared_ptr<container> &othercntr2, const span &otherspn2) -> void {
                std::wstringstream stm;
                stm << L"The " << symbol_type << " '" << name << L"' was matched more than once. See:" << std::endl;
                auto os1 = othercntr1->map_to_file(otherspn1);
                auto os2 = othercntr2->map_to_file(otherspn2);
                stm << L"  " << os1.begin.line << L':' << os1.begin.column << L'-' << os1.end.line << L':' << os1.end.column << L" in " << std::wstring(othercntr1->filename().begin(), othercntr1->filename().end());
                stm << L"  " << os2.begin.line << L':' << os2.begin.column << L'-' << os2.end.line << L':' << os2.end.column << L" in " << std::wstring(othercntr2->filename().begin(), othercntr2->filename().end());
                logger->write(severity::error, 0x102, cntr, spn, stm.str());
            }
            static inline auto CardinalityInvalidMinimumValue(logger *logger, const std::shared_ptr<container> &cntr, const span &spn, int min) -> void {
                std::wstringstream stm;
                stm << L"Invalid minimum (" << min << L") occurrences specified";
                logger->write(severity::error, 0x107, cntr, spn, stm.str());
            }
            static inline auto CardinalityMaxLessThanMin(logger *logger, const std::shared_ptr<container> &cntr, const span &spn, int min, int max) -> void {
                std::wstringstream stm;
                stm << L"The maximum occurrences (" << max << L") of an expression must be less than, or equal to the minimum (" << min << L") occurrences";
                logger->write(severity::error, 0x108, cntr, spn, stm.str());
            }
            static inline auto InvalidEmptyTokenProduction(logger *logger, const std::shared_ptr<container> &cntr, const span &spn) -> void {
                std::wstringstream stm;
                stm << L"Empty value tokens not allowed.";
                logger->write(severity::error, 0x109, cntr, spn, stm.str());
            }
            static inline auto TrapState(logger *logger, const std::shared_ptr<container> &cntr, const span &spn, const std::wstring &sample) -> void {
                std::wstringstream stm;
                stm << L"Trapped state machine. Once '" << sample << L"' was matched it is impossible to reach a token.";
                logger->write(severity::error, 0x10A, cntr, spn, stm.str());
            }
            static inline auto FailureOpeningFile(logger *logger, const std::shared_ptr<container> &cntr, const span &spn, const std::string &fn) -> void {
                std::wstringstream stm;
                stm << L"Failure opening the file '" << std::wstring(fn.begin(), fn.end()) << L"'";
                logger->write(severity::error, 0x201, cntr, spn, stm.str());
            }
            static inline auto FileNotFound(logger *logger, const std::shared_ptr<container> &cntr, const span &spn, const std::string &fn, const std::vector<std::string> &search_directories) -> void {
                std::wstringstream stm;
                if (!search_directories.empty()) {
                    stm << L"Could not find the file '" << std::wstring(fn.begin(), fn.end()) << L"' in any of the following search directories";
                    for(auto &sd : search_directories) {
                        stm << std::endl << L"  " << std::wstring(sd.begin(), sd.end());
                    }
                } else {
                    stm << L"Could not find the file '" << std::wstring(fn.begin(), fn.end()) << L"'";
                }
                logger->write(severity::error, 0x202, cntr, spn, stm.str());
            }
            static inline auto FileFoundManyTimes(logger *logger, const std::shared_ptr<container> &cntr, const span &spn, const std::string &fn, const std::vector<std::string> &search_directories, const std::vector<std::string> &matches) -> void {
                std::wstringstream stm;
                stm << L"The file '" << std::wstring(fn.begin(), fn.end()) << L"' was matches more than once. See";
                for(auto &sd : matches) {
                    stm << std::endl << L"  " << std::wstring(sd.begin(), sd.end());
                }
                logger->write(severity::error, 0x203, cntr, spn, stm.str());
            }
            static inline auto RecursiveFileReferenceFound(logger *logger, const std::shared_ptr<container> &cntr, const span &spn, const std::string &fn, const std::vector<std::string> &chain) -> void {
                std::wstringstream stm;
                stm << L"The file '" << std::wstring(fn.begin(), fn.end()) << L"' cannot be processed since it will cause a recursion. See:" << std::endl;
                for(auto &sd : chain) {
                    stm << L"  " << std::wstring(sd.begin(), sd.end()) << L" includes";
                }
                stm << L"  " << std::wstring(fn.begin(), fn.end());
                logger->write(severity::error, 0x204, cntr, spn, stm.str());
            }
            static inline auto StartSymbolRedefined(logger *logger, const std::shared_ptr<container> &cntr1, const span &spn1, const std::shared_ptr<container> &cntr2, const span &spn2) -> void {
                std::wstringstream stm;
                stm << L"Redefinition of start symbol. See " << std::wstring(cntr2->filename().begin(), cntr2->filename().end()), cntr2->map_to_file(spn2);
                logger->write(severity::error, 0x301, cntr1, spn1, stm.str());
            }
            static inline auto StartSymbolNotDefined(logger *logger) -> void {
                logger->write(severity::error, 0x302, std::shared_ptr<container>(), span(), L"A start symbol was not defined");
            }
            static inline auto MissingSetting(logger *logger, const std::wstring &name) -> void {
                std::wstringstream stm;
                stm << L"The mandatory setting " << name << L" could not be found";
                logger->write(severity::error, 0x401, std::shared_ptr<container>(), span(), stm.str());
            }
            static inline auto AutomataOutboundGaps(logger *logger, const std::shared_ptr<container> &cntr, const span &spn, const std::wstring &pre_matched, const std::vector<std::pair<wchar_t, wchar_t>> &gaps) -> void {
                // After 'aaa6' was matched, the characters 'a'-'z', '0'-'7' or '%' cannot be processed.
                std::wstringstream stm;
                stm << L"After '" << pre_matched << L"' was matched, the characters ";
                switch(gaps.size()) {
                case 0:
                    stm << L"<unknown>";
                    break;
                case 1:
                    stm << printable(gaps[0]);
                    break;
                default:
                    stm << printable(gaps[0]);
                    for(size_t i = 1; i < gaps.size() - 1; i++) {
                        stm << L',' << printable(gaps[i]);
                    }
                    stm << L" or " << printable(gaps[gaps.size() - 1]);
                    break;
                }
                stm << L" cannot be processed";
                logger->write(severity::error, 0x403, cntr, spn, stm.str());
            }
        };
    };
        
}


