//
//  main.cpp
//  dc
//
//  Created by David Lindeque on 11/01/2016.
//  Copyright © 2016 David Lindeque. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sys/stat.h>

#include "dc.dl.h"
#include "dc.dp.h"

#include "astformat.h"
#include "dfa.h"
#include "smcpp.ds.h"
#include "graph_formatter.h"

using namespace dc;

class filecontainer : public container {
private:
    std::string _filename;
public:
    filecontainer(const std::string &filename)
    : _filename(filename)
    {}
    
    virtual auto name() const->std::string { return _filename; }
    virtual auto filename() const->std::string { return _filename; }

    virtual auto map_to_file(const span &spn) const -> span {
        return spn;
    }
};

class virtualcontainer : public container {
private:
    std::string _name;
    std::shared_ptr<container> _parent;
    span _program;
public:
    virtualcontainer(const std::shared_ptr<container> &parent, const span &program)
    : _parent(parent), _program(program)
    {
        _name = "Virt:";
        _name.append(parent->name());
    }

    virtual auto name() const->std::string { return _name; }
    virtual auto filename() const->std::string { return _parent->filename(); }

    virtual auto map_to_file(const span &spn) const -> span {
        return _program;
    }
};

class console_logger : public logger {
protected:
    virtual auto write(severity s, unsigned int errorno, const std::shared_ptr<container> &cntr, const span &spn, const std::wstring &msg) -> void {
        if (cntr == nullptr) {
            std::wcout << msg << std::endl;
        } else {
            auto fspn = cntr->map_to_file(spn);
            auto n = cntr->name();
            switch (s) {
                case severity::info:
                    std::wcout << L"INFO ";
                    break;
                case severity::warning:
                    std::wcout << L"WARNING ";
                    break;
                case severity::error:
                    std::wcout << L"ERROR ";
                    break;
                default:
                    std::wcout << L"UNKNOWN ";
                    break;
            }
            std::wcout << errorno << L" -------------------------------------------------------------------------------" << std::endl;
            std::wcout << std::wstring(n.begin(), n.end()) << std::endl;
            std::wcout << fspn.begin.line << L":" << fspn.begin.column << L'-' << fspn.end.line << L':' << fspn.end  .column << L"  " << msg << std::endl;
        }
    }
};
    
inline auto file_exists(const std::string &fn) -> bool {
    struct stat buffer;
    return stat(fn.c_str(), &buffer) == 0;
}
        
inline auto file_locator(const std::shared_ptr<container> &filerefcntr, const span &filerefspn, const std::string &fn, const std::vector<std::string> &search_directories, std::string &full_path, logger *logger) -> bool {
    std::vector<std::string> matches;
    if (file_exists(fn)) {
        matches.push_back(fn);
    }
    else {
        for(auto &sd : search_directories) {
            std::string mf(sd);
            mf.append(sd);
            if (file_exists(mf)) {
                matches.push_back(std::move(mf));
            }
        }
    }
    switch(matches.size()) {
        case 0:
            log::error::FileNotFound(logger, filerefcntr, filerefspn, fn, search_directories);
            return false;
        case 1:
            full_path = std::move(matches[0]);
            return true;
        default:
            log::error::FileFoundManyTimes(logger, filerefcntr, filerefspn, fn, search_directories, matches);
            return false;
    }
}
            
inline auto find_automata(const symbolreference &name,
                          const std::shared_ptr<container> &name_cntr, 
                          const span &name_spn, 
                          const std::vector<symbolreference> &search_namespaces, 
                          logger  *logger, 
                          bool &ok) -> size_t
{
    std::shared_ptr<container> prev_cntr;
    span prev_spn;
    size_t automata_state = 0;
    container::find<std::pair<std::shared_ptr<AutomataAst>, size_t>>(name_cntr, name, search_namespaces,
            [&name_cntr, &name_spn, &logger, &prev_cntr, &prev_spn, &automata_state, &ok]
            (std::shared_ptr<container> &found_cntr, const std::pair<std::shared_ptr<AutomataAst>, size_t> &p, const symbolreference &name, size_t index)
            {
                // We only process patterns if they matched completely
                if (index == name.size() - 1) {
                    if (automata_state != 0) {
                        // Found previously
                        ok = false;
                        log::error::SymbolFoundMoreThanOnce(logger, L"automata", name_cntr, name_spn, name, found_cntr, p.first->Spn, prev_cntr, prev_spn);
                        return false;
                    } else {
                        prev_cntr = found_cntr;
                        prev_spn = p.first->Spn;
                        automata_state = p.second;
                    }
                }
                return true;
            });
    if (automata_state == 0) {
        log::error::SymbolNotFound(logger, L"automata", name_cntr, name_spn, name);
        ok = false;
    }

    return automata_state;
}

class NamespaceItemAstProcessor : public NamespaceItemAstVisitor {
private:
    const std::shared_ptr<container> &_cntr;
    const symbolreference &_namespace;
    bool &_ok;
    logger *_logger;
    symbolreference &_start_symbol;
    
    std::vector<symbolreference> _search_namespaces;

    nfa &_nfa;
public:
    NamespaceItemAstProcessor(const std::shared_ptr<container> &cntr, const symbolreference &ns, bool &ok, logger *logger, symbolreference &start_symbol, nfa &nfa)
    : _cntr(cntr), _namespace(ns), _ok(ok), _logger(logger), _start_symbol(start_symbol), _nfa(nfa)
    {
        // We add the current namespace to the namespaces to search for symbols (as the first one)
        _search_namespaces.push_back(ns);
    }

    std::shared_ptr<NamespaceItemAst> _ast;

    virtual auto visit(const PatternAst*) -> void {
        _cntr->add_symbol(_namespace, std::dynamic_pointer_cast<PatternAst>(_ast));
    }
    virtual auto visit(const SetAst*) -> void {
        _cntr->add_symbol(_namespace, std::dynamic_pointer_cast<SetAst>(_ast));
    }
    virtual auto visit(const AutomataAst* ast) -> void {
        class SetItemAstProcessor : public SetItemAstVisitor {
        private:
            std::vector<std::shared_ptr<container>> _cntr_stack;
            bool &_ok;
            logger *_logger;
            const std::vector<symbolreference> &_search_namespaces;
            nfa &_nfa;
            size_t _start_state;
        public:
            SetItemAstProcessor(const std::shared_ptr<container> &cntr, bool &ok, logger *logger, const std::vector<symbolreference> &search_namespaces, 
                nfa &nfa, size_t nfa_start_state)
            : _ok(ok), _logger(logger), _search_namespaces(search_namespaces), _nfa(nfa), _start_state(nfa_start_state)
            {
                _cntr_stack.push_back(cntr);
            }
            virtual auto visit(const MatchDefinitionAst* ast) -> void override {
                // Discover the transitions
                size_t end_state = _nfa.next_state++;
                bool start_is_final = false;
                BuildNfaReAst builder(_cntr_stack.back(), _nfa, _start_state, end_state, _search_namespaces, _logger, _ok, start_is_final);
                ast->Value->accept(&builder);    
                if (start_is_final) {
                    log::error::InvalidEmptyTokenProduction(_logger, _cntr_stack.back(), ast->Spn);
                    _ok = false;
                } 
                // Add the 'terminate' transition (so we don't loose last state in DFA building)
                size_t final_state = _nfa.next_state++;
                _nfa.transitions.emplace_back(end_state, false, L'\x0', L'\x0', final_state);

                if (ast->IsGoto) {
                    // Locate the referenced automata
                    size_t goto_state = find_automata(ast->GotoLabel,
                                                _cntr_stack.back(), 
                                                ast->Spn,
                                                _search_namespaces,
                                                _logger,
                                                _ok);
                    auto f = _nfa.actions.emplace(end_state, std::set<NfaAction, NfaActionLess>());
                    f.first->second.emplace(NfaAction { _nfa.next_precedence++, ast->FunctionName, ast->TokenName, ast->IsReturn, true, goto_state, containerspan(_cntr_stack.back(), ast->Spn) });
                }
                else {
                    auto f = _nfa.actions.emplace(end_state, std::set<NfaAction, NfaActionLess>());
                    f.first->second.emplace(NfaAction { _nfa.next_precedence++, ast->FunctionName, ast->TokenName, ast->IsReturn, false, 0, containerspan(_cntr_stack.back(), ast->Spn) });
                }
                
            }
            virtual auto visit(const IncludeSetAst* ast) -> void override {
                // Find the set mentioned
                bool found = false;
                std::shared_ptr<container> prev_cntr;
                span prev_spn;
                auto _this = this;
                auto &cntr_stack = _cntr_stack;
                auto logger = _logger;

                // Search container
                container::find<std::shared_ptr<SetAst>>(_cntr_stack.back(), ast->Name, _search_namespaces,
                [&found, &prev_cntr, &prev_spn, &_this, &cntr_stack, &logger, &ast](const std::shared_ptr<container> &cntr, const std::shared_ptr<SetAst> &p, const symbolreference &name, size_t index)
                {
                    if (index == name.size() - 1) {
                        if (found) {
                            log::error::SymbolFoundMoreThanOnce(logger, L"match set", cntr_stack.back(), ast->Spn, ast->Name, prev_cntr, prev_spn, cntr, p->Spn);
                            return false;
                        }
                        // Set the found status
                        found = true;
                        prev_cntr = cntr;
                        prev_spn = p->Spn;

                        // Process the set
                        cntr_stack.push_back(cntr);
                        for(auto &item : p->Items) {
                            item->accept(_this);
                        }
                        cntr_stack.pop_back();
                    }
                    // Search further (to find duplicate names)
                    return true;
                });

                if (!found) {
                    log::error::SymbolNotFound(_logger, L"match set", _cntr_stack.back(), ast->Spn, ast->Name);
                    _ok = false;
                }
            }
        };

        // Create a new start state
        size_t start_state = _nfa.next_state++;
        _nfa.automataspns.emplace(start_state, containerspan(_cntr, ast->Name.spn()));
        
        // Add the symbol
        _cntr->add_symbol(_namespace, std::dynamic_pointer_cast<AutomataAst>(_ast), start_state);
        
        // Add the nfa transitions for this automata
        SetItemAstProcessor item_processor(_cntr, _ok, _logger, _search_namespaces, _nfa, start_state);
        for(auto &item : ast->Items) {
            item->accept(&item_processor);
        }
    }
    virtual auto visit(const EnumAst*) -> void {
        _cntr->add_symbol(_namespace, std::dynamic_pointer_cast<EnumAst>(_ast));
    }
    virtual auto visit(const UsingNamespaceAst* ast) -> void {
        _search_namespaces.push_back(ast->Name);
    }
};

class DocumentAstProcessor : public DocumentAstVisitor {
private:
    bool &_ok;
    const std::vector<std::string> &_search_directories;
    std::vector<std::string> _seen_imports;
    logger *_logger;
    
    std::vector<std::shared_ptr<container>> _cntr_stack;

    symbolreference _start_symbol;
    std::shared_ptr<container> _start_symbol_def_cntr;
    span _start_symbol_def_spn;
    nfa _nfa;
public:
    DocumentAstProcessor(const std::string &fn, const std::shared_ptr<container> &cntr, logger *logger, bool &ok, const std::vector<std::string> &search_directories)
    : _logger(logger), _ok(ok), _search_directories(search_directories)
    {
        _seen_imports.push_back(fn);
        _cntr_stack.push_back(cntr);
    }
    
    inline auto nfa() -> nfa& { return _nfa; }
    inline auto nfa() const -> const class nfa& { return _nfa; }
    inline auto start_symbol() const -> const symbolreference& { return _start_symbol; }
    inline auto start_symbol_cntr() const -> const std::shared_ptr<container>& { return _start_symbol_def_cntr; }
    inline auto start_symbol_spn() const -> span { return _start_symbol_def_spn; }

    virtual auto visit(const StartItemAst* ast) -> void {
        if (_start_symbol_def_cntr != nullptr) {
            log::error::StartSymbolRedefined(_logger, _cntr_stack.back(), ast->Spn, _start_symbol_def_cntr, _start_symbol_def_spn);
            _ok = false;
        } else {
            _start_symbol_def_cntr = _cntr_stack.back();
            _start_symbol_def_spn = ast->Spn;
            _start_symbol = ast->Document;
        }
    }
    virtual auto visit(const NamespaceAst* ast) -> void {
        NamespaceItemAstProcessor processor(_cntr_stack.back(), ast->Name, _ok, _logger, _start_symbol, _nfa);
        for(auto &item : ast->Items) {
            processor._ast = item;
            item->accept(&processor);
        }
    }
    virtual auto visit(const ImportAst* ast) -> void {
        // Find and open the referenced file
        std::string full_path;
        if (!file_locator(_cntr_stack.back(), ast->Spn, std::string(ast->Document.value().begin(), ast->Document.value().end()), _search_directories, full_path, _logger)) {
            _ok = false;
            return;
        }
        
        bool seen = false;
        for(auto &fn : _seen_imports) {
            if (full_path == fn) {
                seen = true;
                break;
            }
        }
        
        if (seen) {
            // We don't process the file again
            log::error::RecursiveFileReferenceFound(_logger, _cntr_stack.back(), ast->Spn, full_path, _seen_imports);
            _ok = false;
            return;
        }
        
        std::shared_ptr<container> cntr(new filecontainer(full_path));
        std::wifstream stm(full_path);
        if (!stm) {
            log::error::FailureOpeningFile(_logger, _cntr_stack.back(), ast->Spn, full_path);
            _ok = false;
            return;
        }

        // Process the referenced file
        _cntr_stack.push_back(cntr);
        _seen_imports.push_back(full_path);
        _ok &= parse(stm, cntr, _logger, this, _ok);
        _seen_imports.pop_back();
        _cntr_stack.pop_back();
        _cntr_stack.back()->add_reference(cntr);
    }
    virtual auto visit(const MixinAst *ast) -> void {
        // We have to 'evaluate' the expression, producing a text value, which must now be processed
        std::wstringstream text;
        text << L"// This is the text resulting from the evaluation of the expression mentioned in the Mixin ast";

        std::shared_ptr<container> cntr(new virtualcontainer(_cntr_stack.back(), ast->Spn));

        _cntr_stack.push_back(cntr);
        _ok &= parse(text, cntr, _logger, this, _ok);
        _cntr_stack.pop_back();
        _cntr_stack.back()->add_reference(cntr);
    }
};
        
int main(int argc, const char * argv[]) {
    std::wcout << L"Dave Compiler 0.1" << std::endl;
    
    console_logger logger;
    std::vector<std::string> search_directories;
    bool ok = true;

    // Find and open the file
    std::string full_path;
    if (!file_locator(std::shared_ptr<container>(), span(), "/Users/davidlindeque/davesuite/dl/dl/dl.dl", search_directories, full_path, &logger)) {
        return 1;
    }

    std::shared_ptr<container> cntr(new filecontainer(full_path));
    std::wifstream stm(full_path);
    if (!stm) {
        log::error::FailureOpeningFile(&logger, nullptr, span(), full_path);
        return 1;
    }

    // Create the processor and parse
    DocumentAstProcessor processor(full_path, cntr, &logger, ok, search_directories);
    ok &= parse(stm, cntr, &logger, &processor, ok);
    
    if (!ok) {
        return 1;
    }
    
    if (processor.start_symbol_cntr() == nullptr) {
        log::error::StartSymbolNotDefined(&logger);
        return 1;
    }
    
    // Find the start automata
    size_t start_automata_state = find_automata(processor.start_symbol(), 
                                                processor.start_symbol_cntr(), 
                                                processor.start_symbol_spn(),
                                                std::vector<symbolreference>(),
                                                &logger,
                                                ok);

    if (!ok) {
        return 1;
    }
    
    // We need to add an epsilon transition from 0 to the start start
    processor.nfa().transitions.push_back(Transition(0, true, L' ', L' ', start_automata_state));
    processor.nfa().automataspns.emplace(0, processor.nfa().automataspns[start_automata_state]);
    
    nfa test;
    test.transitions.emplace_back(0, false, L'a', L'a', 1);
    test.transitions.emplace_back(1, true, L' ', L' ', 2);
    test.transitions.emplace_back(2, false, L'b', L'b', 2);
    test.transitions.emplace_back(2, false, L'c', L'c', 2);
    test.transitions.emplace_back(2, true, L' ', L' ', 3);
    test.transitions.emplace_back(3, false, L'c', L'c', 4);
    auto f = test.actions.emplace(4, std::set<NfaAction, NfaActionLess>());
    f.first->second.emplace(NfaAction { 0, spantext(), symbolreference(), false, false, 0, containerspan() });
    test.next_state = 5;
    
    std::wofstream nfagv("/Users/davidlindeque/Documents/nfa.gv");
    graph_formatter fmt1(nfagv);
    fmt1(L"NFA", processor.nfa().transitions, processor.nfa().actions);
    //return 0;
    
    // Now we have the fully defined NFA - now we can build the DFA
    auto dfa = build_dfa(&logger, processor.nfa());
    //build_dfa(&logger, test);
    
    std::wofstream dfagv("/Users/davidlindeque/Documents/dfa.gv");
    graph_formatter fmt2(dfagv);
    fmt2(L"DFA", dfa.transitions, dfa.actions);
    
    // Validate the DFA and determine find the Default Actions (error or rewind)
    if (!valid_and_find_default_actions(&logger, dfa)) {
        return 1;
    }

    
    std::unordered_map<std::wstring, std::wstring> settings;
    settings.emplace(L"cppfn", L"/Users/davidlindeque/scratch/dl.cpp");
    settings.emplace(L"hfn", L"/Users/davidlindeque/scratch/dl.h");
    settings.emplace(L"namespace", L"dc");
    settings.emplace(L"functionName", L"read_next_token");
    
    // Write the code
    if (!smcpp_write(&logger, dfa, settings)) {
        return 1;
    }
    
    return 0;
}



