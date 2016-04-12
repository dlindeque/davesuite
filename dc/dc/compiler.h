#pragma once

#include <sys/stat.h>
#include <fstream>
#include "container.h"
#include "log.h"
#include "dc.dpp.h"
#include "cpp_helpers.h"

namespace dc
{
    class filecontainer : public container {
    private:
        std::string _filename;
    public:
        filecontainer(const std::string &filename)
        : _filename(filename)
        {}
        
        virtual auto name() const->std::string { return _filename; }
        virtual auto filename() const->std::string { return _filename; }
        virtual auto is_virtual() const -> bool { return false; }

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
        virtual auto is_virtual() const -> bool { return true; }

        virtual auto map_to_file(const span &spn) const -> span {
            return _program;
        }
    };

    class systemcontainer : public container {
    private:
        inline auto get_spantext(std::wstring &&text) -> std::vector<spantext> {
            std::vector<spantext> v;
            v.push_back(spantext(span(), std::move(text)));
            return std::move(v);
        }
        inline auto add_primitive_system_type(std::shared_ptr<NamespaceAst> &ns, std::wstring &&name, std::wstring &&documentation) -> void {
            std::shared_ptr<TypeAst> type(new TypeAst(span(), get_spantext(std::move(documentation)), spantext(span(), std::move(name)), std::vector<std::shared_ptr<TypeArgumentAst>>(), true, true, nullptr, std::vector<std::shared_ptr<TypePropertyAst>>()));
            add_symbol(ns->Name, type);
            ns->Items.push_back(type);
            type->DeclaringAst = ns;
        }
        inline auto add_primitive_system_type_1(std::shared_ptr<NamespaceAst> &ns, std::wstring &&name, std::wstring &&documentation, std::wstring &&arg) -> void {
            std::vector<std::shared_ptr<TypeArgumentAst>> args;
            args.emplace_back(new TypeArgumentAst(span(), spantext(span(), std::move(arg))));
            std::shared_ptr<TypeAst> type(new TypeAst(span(), get_spantext(std::move(documentation)), spantext(span(), std::move(name)), std::move(args), true, true, nullptr, std::vector<std::shared_ptr<TypePropertyAst>>()));
            add_symbol(ns->Name, type);
            ns->Items.push_back(type);
            type->DeclaringAst = ns;
        }
    public:
        systemcontainer()
        {
            // Add the system artefacts
            symbolreference systemns;
            systemns.emplace_back(span(), L"System");
            std::shared_ptr<NamespaceAst> systemNamespaceAst(new NamespaceAst(span(), std::move(systemns), std::vector<std::shared_ptr<NamespaceItemAst>>()));
            add_primitive_system_type(systemNamespaceAst, L"Word", L"An unsigned integral type the size of the system word");
            add_primitive_system_type(systemNamespaceAst, L"DoubleWord", L"An unsigned integral double the size of the system word");
            add_primitive_system_type(systemNamespaceAst, L"Int8", L"A signed integral type a to b");
            add_primitive_system_type(systemNamespaceAst, L"Int16", L"A signed integral type a to b");
            add_primitive_system_type(systemNamespaceAst, L"Int32", L"A signed integral type a to b");
            add_primitive_system_type(systemNamespaceAst, L"Int64", L"A signed integral type a to b");
            add_primitive_system_type(systemNamespaceAst, L"String", L"A string of ascii text");
            add_primitive_system_type(systemNamespaceAst, L"WString", L"A string of wide-character text");
            add_primitive_system_type(systemNamespaceAst, L"Float", L"A standard floating point number");
            add_primitive_system_type(systemNamespaceAst, L"DFloat", L"A double sized floating point number");
            add_primitive_system_type_1(systemNamespaceAst, L"Collection", L"A collection of types", L"T");
        }

        virtual auto name() const->std::string { return "System"; }
        virtual auto filename() const->std::string { return "System"; }
        virtual auto is_virtual() const -> bool { return true; }

        virtual auto map_to_file(const span &spn) const -> span {
            return span();
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
                mf.append(fn);
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

    template<bool name_is_member = false> 
    inline auto find_enum(const symbolreference &name,
                          const std::shared_ptr<container> &name_cntr, 
                          const span &name_spn, 
                          const std::vector<symbolreference> &search_namespaces, 
                          logger  *logger, 
                          bool &ok) -> std::shared_ptr<EnumAst>
    {
        std::shared_ptr<container> prev_cntr;
        span prev_spn;
        std::shared_ptr<EnumAst> found_enum;
        bool found = false;
        container::find<std::shared_ptr<EnumAst>>(name_cntr, name, search_namespaces,
            [&found, &logger, &name, &prev_cntr, &prev_spn, &name_cntr, &found_enum, &name_spn](const std::shared_ptr<container> &cntr, const std::shared_ptr<EnumAst> &p, const symbolreference &name, size_t index)
            {
                if (index == name.size() - (name_is_member ? 2 : 1)) {
                    if (found) {
                        log::error::SymbolFoundMoreThanOnce(logger, L"enum", name_cntr, name_spn, name, prev_cntr, prev_spn, cntr, p->Spn);
                        return false;
                    }
                    // Set the found status
                    found = true;
                    prev_cntr = cntr;
                    prev_spn = p->Spn;

                    // Note the find
                    found_enum = p;
                }
                // Search further (to find duplicate names)
                return true;
            });
        if (!found) {
            log::error::SymbolNotFound(logger, L"enum", name_cntr, name_spn, name);
            ok = false;
        }

        return std::move(found_enum);
    }

    template<typename T> struct symbol_detail
    {
        T item;
        std::shared_ptr<container> cntr;
        std::vector<symbolreference> search_namespaces;
    };

    typedef symbol_detail<std::shared_ptr<MatchDefinitionAst>> match_expression;

    class NamespaceItemAstProcessor : public NamespaceItemAstMutatingVisitor {
    private:
        const std::shared_ptr<container> &_cntr;
        std::shared_ptr<NamespaceAst> &_declaringAst;
        const symbolreference &_namespace;
        bool &_ok;
        logger *_logger;
        symbolreference &_start_symbol;
        
        std::vector<symbolreference> _search_namespaces;

        nfa &_nfa;
        std::vector<match_expression> &_match_expressions;

        inline auto find_type(const symbolreference &name, size_t arg_count, bool must_find_type) -> std::pair<std::shared_ptr<container>, std::shared_ptr<TypeDefinitionAst>>
        {
            // Search container
            bool found = false;
            std::shared_ptr<container> prev_cntr;
            span prev_spn;
            std::shared_ptr<TypeDefinitionAst> found_type;
            span name_spn(span(name[0].spn().begin, name.back().spn().end));
            auto &name_cntr = _cntr;
            auto &logger = _logger;
            container::find<std::shared_ptr<TypeAst>>(_cntr, name, _search_namespaces,
                [&found, &logger, &name, &arg_count, &prev_cntr, &prev_spn, &name_cntr, &found_type, &name_spn](const std::shared_ptr<container> &cntr, const std::shared_ptr<TypeAst> &p, const symbolreference &name, size_t index)
                {
                    if (index == name.size() - 1 && p->Arguments.size() == arg_count) {
                        if (found) {
                            log::error::SymbolFoundMoreThanOnce(logger, L"type/enum/alias", name_cntr, name_spn, name, prev_cntr, prev_spn, cntr, p->Spn);
                            return false;
                        }
                        // Set the found status
                        found = true;
                        prev_cntr = cntr;
                        prev_spn = p->Spn;

                        // Note the find
                        found_type = p;
                    }
                    // Search further (to find duplicate names)
                    return true;
                });
            if (arg_count == 0) {
                container::find<std::shared_ptr<EnumAst>>(_cntr, name, _search_namespaces,
                    [&found, &logger, &name, &arg_count, &prev_cntr, &prev_spn, &name_cntr, &found_type, &name_spn](const std::shared_ptr<container> &cntr, const std::shared_ptr<EnumAst> &p, const symbolreference &name, size_t index)
                    {
                        if (index == name.size() - 1) {
                            if (found) {
                                log::error::SymbolFoundMoreThanOnce(logger, L"type/enum/alias", name_cntr, name_spn, name, prev_cntr, prev_spn, cntr, p->Spn);
                                return false;
                            }
                            // Set the found status
                            found = true;
                            prev_cntr = cntr;
                            prev_spn = p->Spn;

                            // Note the find
                            found_type = p;
                        }
                        // Search further (to find duplicate names)
                        return true;
                    });
            }
            container::find<std::shared_ptr<TypeAliasAst>>(_cntr, name, _search_namespaces,
              [&found, &logger, &name, &arg_count, &prev_cntr, &prev_spn, &name_cntr, &found_type, &name_spn](const std::shared_ptr<container> &cntr, const std::shared_ptr<TypeAliasAst> &p, const symbolreference &name, size_t index)
              {
                  if (index == name.size() - 1 && p->Arguments.size() == arg_count) {
                      if (found) {
                          log::error::SymbolFoundMoreThanOnce(logger, L"type/enum/alias", name_cntr, name_spn, name, prev_cntr, prev_spn, cntr, p->Spn);
                          return false;
                      }
                      // Set the found status
                      found = true;
                      prev_cntr = cntr;
                      prev_spn = p->Spn;
                      
                      // Note the find
                      found_type = p;
                  }
                  // Search further (to find duplicate names)
                  return true;
              });

            if (must_find_type && !found) {
                log::error::SymbolNotFound(_logger, L"type/enum/alias", name_cntr, name_spn, name);
                _ok = false;
                return std::pair<std::shared_ptr<container>, std::shared_ptr<TypeDefinitionAst>>();
            } else {
                return std::pair<std::shared_ptr<container>, std::shared_ptr<TypeDefinitionAst>>(std::move(prev_cntr), std::move(found_type));
            }
        }

        inline auto try_lookup_and_bind_type(const std::unordered_map<std::wstring, std::shared_ptr<TypeArgumentAst>> &arguments, TypeReferenceAst *tr) -> bool
        {
            if (tr->Arguments.empty() && tr->Name.size() == 1) {
                auto f = arguments.find(tr->Name[0].value());
                if (f != arguments.end()) {
                    // It's referencing an argument.
                    tr->BoundArgument = f->second;
                    return true;
                }
            }
            auto type = find_type(tr->Name, tr->Arguments.size(), true);
            if (type.second == nullptr) return false;
            tr->BoundType = std::move(type.second);
            bool ok = true;
            for(auto &a : tr->Arguments) {
                ok &= try_lookup_and_bind_type(arguments, a.get());
            }
            return ok;
        }
    public:
        NamespaceItemAstProcessor(const std::shared_ptr<container> &cntr, std::shared_ptr<NamespaceAst> &declaringAst, const symbolreference &ns, bool &ok, logger *logger, symbolreference &start_symbol, nfa &nfa, std::vector<match_expression> &match_expressions)
        : _cntr(cntr), _declaringAst(declaringAst), _namespace(ns), _ok(ok), _logger(logger), _start_symbol(start_symbol), _nfa(nfa), _match_expressions(match_expressions)
        {
            // We add the current namespace to the namespaces to search for symbols (as the first one)
            _search_namespaces.push_back(ns);
        }

        virtual auto visit(std::shared_ptr<PatternAst> &ast) -> void {
            ast->DeclaringAst = _declaringAst;
            _cntr->add_symbol(_namespace, ast);
        }
        virtual auto visit(std::shared_ptr<SetAst> &ast) -> void {
            ast->DeclaringAst = _declaringAst;
            _cntr->add_symbol(_namespace, ast);
        }
        virtual auto visit(std::shared_ptr<AutomataAst> &ast) -> void {
            class SetItemAstProcessor : public SetItemAstMutatingVisitor {
            private:
                std::vector<std::shared_ptr<container>> _cntr_stack;
                std::shared_ptr<AutomataAst> &_declaringAst;
                bool &_ok;
                logger *_logger;
                const std::vector<symbolreference> &_search_namespaces;
                nfa &_nfa;
                size_t _start_state;
                std::vector<match_expression> &_match_expressions;
            public:
                SetItemAstProcessor(const std::shared_ptr<container> &cntr, std::shared_ptr<AutomataAst> &declaringAst, bool &ok, logger *logger, const std::vector<symbolreference> &search_namespaces,
                    nfa &nfa, size_t nfa_start_state, std::vector<match_expression> &match_expressions)
                : _declaringAst(declaringAst), _ok(ok), _logger(logger), _search_namespaces(search_namespaces), _nfa(nfa), _start_state(nfa_start_state), _match_expressions(match_expressions)
                {
                    _cntr_stack.push_back(cntr);
                }

                virtual auto visit(std::shared_ptr<MatchDefinitionAst> &ast) -> void override {
                    ast->DeclaringAst = _declaringAst;
                    _match_expressions.push_back(match_expression { ast, _cntr_stack.back(), _search_namespaces });

                    // Discover the transitions
                    size_t end_state = _nfa.next_state++;
                    bool start_is_final = false;
                    BuildNfaReAst builder(_cntr_stack.back(), _nfa, _start_state, end_state, _search_namespaces, _logger, _ok, start_is_final);
                    ast->Value->accept(ast->Value, &builder);
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
                virtual auto visit(std::shared_ptr<IncludeSetAst> &ast) -> void override {
                    ast->DeclaringAst = _declaringAst;
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
                                item->accept(item, _this);
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

            ast->DeclaringAst = _declaringAst;
            // Create a new start state
            size_t start_state = _nfa.next_state++;
            _nfa.automataspns.emplace(start_state, containerspan(_cntr, ast->Name.spn()));
            
            // Add the symbol
            _cntr->add_symbol(_namespace, ast, start_state);
            
            // Add the nfa transitions for this automata
            SetItemAstProcessor item_processor(_cntr, ast, _ok, _logger, _search_namespaces, _nfa, start_state, _match_expressions);
            for(auto &item : ast->Items) {
                item->accept(item, &item_processor);
            }
        }
        virtual auto visit(std::shared_ptr<EnumAst> &ast) -> void {
            ast->DeclaringAst = _declaringAst;
            _cntr->add_symbol(_namespace, ast);
        }
        virtual auto visit(std::shared_ptr<TypeAst> &ast) -> void {
            ast->DeclaringAst = _declaringAst;
            // Check unique - make sure the type doesn't already exist
            symbolreference this_ref(_namespace);
            this_ref.push_back(ast->Name);
            auto t = find_type(this_ref, ast->Arguments.size(), false);
            if (t.second != nullptr) {
                log::error::TypeNameAlreadyDefined(_logger, _cntr, ast->Name.spn(), ast->Name.value(), t.first, t.second->Spn);
                _ok = false;
                return;
            }

            // Validate
            // a. Type argument names must be unique
            std::unordered_map<std::wstring, std::shared_ptr<TypeArgumentAst>> args;
            for(auto &a : ast->Arguments) {
                if (!args.emplace(a->Name.value(), a).second) {
                    log::error::TypeArgumentsMustBeUnique(_logger, _cntr, a->Name.spn(), a->Name.value());
                    _ok = false;
                }
            }
            // Add to the symbol table
            _cntr->add_symbol(_namespace, ast);
            // Bind all types
            if (ast->Parent != nullptr) {
                try_lookup_and_bind_type(args, ast->Parent.get());
            }
            for(auto &p : ast->Properties) {
                try_lookup_and_bind_type(args, p->Type.get());
            }
            // Validate
            std::shared_ptr<TypeAst> parent;
            if (ast->Parent != nullptr) {
                if (ast->Parent->BoundType != nullptr) {
                    auto alias = std::dynamic_pointer_cast<TypeAliasAst>(ast->Parent->BoundType);
                    if (alias != nullptr) {
                        while(alias != nullptr) {
                            alias = std::dynamic_pointer_cast<TypeAliasAst>(alias->Value);
                        }
                        parent = std::dynamic_pointer_cast<TypeAst>(alias->Value);
                    } else {
                        parent = std::dynamic_pointer_cast<TypeAst>(ast->Parent->BoundType);
                    }
                    if (parent == nullptr) {
                        log::error::TypeParentCannotBeEnum(_logger, _cntr, ast->Parent->Spn, ast->Parent);
                        _ok = false;
                    }
                }
                else if (ast->Parent->BoundArgument != nullptr) {
                    log::error::TypeParentCannotBeArgument(_logger, _cntr, ast->Parent->Spn, ast->Parent);
                    _ok = false;
                }
            }
            // a. Property names must be unique, even up the hierarchy
            // b. Parent hierarchy may not be recursive (Cannot allow structural recursion - infinately sized types)
            // c. Variance usage must be valid
            // d. Parent may not be sealed
            if (parent != nullptr) {
                if (parent->IsSealed) {
                    log::error::TypeParentSealed(_logger, _cntr, ast->Parent->Spn, ast->Parent);
                    _ok = false;
                }
            }
        }
        virtual auto visit(std::shared_ptr<TypeAliasAst> &ast) -> void {
            ast->DeclaringAst = _declaringAst;
            // Check unique - make sure the type doesn't already exist
            symbolreference this_ref(_namespace);
            this_ref.push_back(ast->Name);
            auto t = find_type(this_ref, ast->Arguments.size(), false);
            if (t.second != nullptr) {
                log::error::TypeNameAlreadyDefined(_logger, _cntr, ast->Name.spn(), ast->Name.value(), t.first, t.second->Spn);
                _ok = false;
                return;
            }
            // Validate
            // a. Type argument names must be unique
            std::unordered_map<std::wstring, std::shared_ptr<TypeArgumentAst>> args;
            for(auto &a : ast->Arguments) {
                if (!args.emplace(a->Name.value(), a).second) {
                    log::error::TypeArgumentsMustBeUnique(_logger, _cntr, a->Name.spn(), a->Name.value());
                    _ok = false;
                }
            }
            // Add to the symbol table
            _cntr->add_symbol(_namespace, ast);
            // Bind all types
            try_lookup_and_bind_type(args, ast->Value.get());
        }
        virtual auto visit(std::shared_ptr<UsingNamespaceAst> &ast) -> void {
            ast->DeclaringAst = _declaringAst;
            _search_namespaces.push_back(ast->Name);
        }
    };

    class DocumentAstProcessor : public DocumentAstMutatingVisitor {
    private:
        bool &_ok;
        std::vector<std::string> _search_directories;
        std::vector<std::string> _seen_imports;
        logger *_logger;
        
        std::vector<std::shared_ptr<container>> _cntr_stack;

        symbolreference _start_symbol;
        std::shared_ptr<container> _start_symbol_def_cntr;
        span _start_symbol_def_spn;
        nfa _nfa;
        dfa _dfa;
        std::shared_ptr<TypeDefinitionAst> _automata_match_return_type;

        std::shared_ptr<container> _system_container;
        std::shared_ptr<container> _root_cntr;
        std::vector<match_expression> _match_expressions;
    public:
        DocumentAstProcessor(logger *logger, bool &ok, const std::vector<std::string> &search_directories)
        : _logger(logger), _ok(ok), _search_directories(search_directories), _system_container(new systemcontainer())
        {}

        inline auto process_file(const std::shared_ptr<container> &refcntr, const span &refspn, const std::string &fn) -> std::shared_ptr<container> {
            // Find and open the referenced file
            std::string full_path;
            if (!file_locator(refcntr, refspn, fn, _search_directories, full_path, _logger)) {
                _ok = false;
                return std::shared_ptr<container>();
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
                log::error::RecursiveFileReferenceFound(_logger, refcntr, refspn, full_path, _seen_imports);
                _ok = false;
                return std::shared_ptr<container>();
            }
            
            auto cntr = std::shared_ptr<container>(new filecontainer(full_path));
            // All containers reference the system container
            cntr->add_reference(_system_container);

            std::wifstream stm(full_path);
            if (!stm) {
                log::error::FailureOpeningFile(_logger, refcntr, refspn, full_path);
                _ok = false;
                return std::shared_ptr<container>();
            }

            // Process the referenced file
            auto fd = extract_file_directory(full_path);
            if (!fd.empty()) {
                _search_directories.push_back(fd);
            }
            _cntr_stack.push_back(cntr);
            _seen_imports.push_back(full_path);
            _ok &= parse(stm, cntr, _logger, this, _ok);
            _seen_imports.pop_back();
            _cntr_stack.pop_back();
            if (!_cntr_stack.empty()) {
                _cntr_stack.back()->add_reference(cntr);
            }
            if (!fd.empty()) {
                _search_directories.pop_back();
            }

            return cntr;
        }

        inline auto process_root_container(const std::string &fn) -> void {
            _root_cntr = process_file(std::shared_ptr<container>(), span(), fn);
        }
        
        inline auto nfa() -> nfa& { return _nfa; }
        inline auto nfa() const -> const class nfa& { return _nfa; }
        inline auto dfa() -> dfa& { return _dfa; }
        inline auto dfa() const -> const class dfa& { return _dfa; }
        inline auto automata_match_return_type() const -> const std::shared_ptr<TypeDefinitionAst>& { return _automata_match_return_type; }
        inline auto automata_match_return_type() -> std::shared_ptr<TypeDefinitionAst>& { return _automata_match_return_type; }
        inline auto root_cntr() const -> const std::shared_ptr<container> { return _root_cntr; }
        inline auto start_symbol() const -> const symbolreference& { return _start_symbol; }
        inline auto start_symbol_cntr() const -> const std::shared_ptr<container>& { return _start_symbol_def_cntr; }
        inline auto start_symbol_spn() const -> span { return _start_symbol_def_spn; }
        inline auto match_expressions() const -> const std::vector<match_expression>& { return _match_expressions; }
        inline auto match_expressions() -> std::vector<match_expression>& { return _match_expressions; }

        virtual auto visit(std::shared_ptr<StartItemAst> &ast) -> void {
            if (_start_symbol_def_cntr != nullptr) {
                log::error::StartSymbolRedefined(_logger, _cntr_stack.back(), ast->Spn, _start_symbol_def_cntr, _start_symbol_def_spn);
                _ok = false;
            } else {
                _start_symbol_def_cntr = _cntr_stack.back();
                _start_symbol_def_spn = ast->Spn;
                _start_symbol = ast->Document;
            }
        }
        virtual auto visit(std::shared_ptr<NamespaceAst> &ast) -> void {
            NamespaceItemAstProcessor processor(_cntr_stack.back(), ast, ast->Name, _ok, _logger, _start_symbol, _nfa, _match_expressions);
            for(auto &item : ast->Items) {
                item->accept(item, &processor);
            }
        }
        virtual auto visit(std::shared_ptr<ImportAst> &ast) -> void {
            auto fn = ast->Document.value();
            process_file(_cntr_stack.back(), ast->Spn, std::string(fn.begin(), fn.end()));
        }
        virtual auto visit(std::shared_ptr<MixinAst> &ast) -> void {
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
}