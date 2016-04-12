//
//  container.hpp
//  dc
//
//  Created by David Lindeque on 19/01/2016.
//  Copyright © 2016 David Lindeque. All rights reserved.
//

#pragma once

#include <string>
#include <set>
#include <unordered_map>
#include <algorithm>

#include "symbolreference.h"

/*
 A symbol reference can always terminate with a property path (i.e.: .prop1.prop2), so if we have
 a.b.c.d, we must assume d, c, b can all be part of a property path, so we need to find symbols referenced partly (i.e.: a, a.b, a.b.c or a.b.c.d can be a symbol reference, while the rest is a property path)
 */

namespace dc
{
    class PatternAst;
    class SetAst;
    class EnumAst;
    class TypeAst;
    class TypeAliasAst;
    class AutomataAst;
    
    class logger;
    
    template<typename T> using symbol_table = std::unordered_multimap<std::wstring, T>;
    struct namespace_container {
        symbol_table<std::shared_ptr<PatternAst>> dl_patterns;
        symbol_table<std::shared_ptr<SetAst>> dl_sets;
        symbol_table<std::shared_ptr<EnumAst>> enums;
        symbol_table<std::shared_ptr<TypeAst>> types;
        symbol_table<std::shared_ptr<TypeAliasAst>> aliases;
        symbol_table<std::pair<std::shared_ptr<AutomataAst>, size_t>> dl_automatas;
        std::unordered_map<std::wstring, namespace_container> namespaces;
    };
    
    template<typename T> struct symbols_accessor { };
    
    // Container for code to be compiled, and also serves as symbol container
    class container {
    private:
        std::vector<std::shared_ptr<container>> _references;
        namespace_container _anonymous_namespace;
        inline auto find_ns_container(const symbolreference &ns) -> namespace_container& {
            auto cns = &_anonymous_namespace;
            for(size_t i = 0; i < ns.size(); i++) {
                auto f = cns->namespaces.find(ns[i].value());
                if (f == cns->namespaces.end()) {
                    cns = &(cns->namespaces.emplace(ns[i].value(), namespace_container()).first->second);
                } 
                else {
                    cns = &f->second;
                }
            }
            return *cns;
        }
        
    public:
        // The name of this token source (i.e.: property name)
        virtual auto name() const->std::string = 0;
        
        // The name of the file to open when referencing this container
        virtual auto filename() const -> std::string = 0;

        // A flag indicating whether this container is virtual (i.e.: doesn't have an actual file backing)
        virtual auto is_virtual() const -> bool = 0;
        
        // The span as mapped to the file when referencing this container
        virtual auto map_to_file(const span &spn) const -> span = 0;
        
        inline auto add_reference(const std::shared_ptr<container> &reference) -> void {
            _references.push_back(reference);
        }

        inline auto references() const -> const std::vector<std::shared_ptr<container>>& { return _references; }
        inline auto root_namespace() const -> const namespace_container& { return _anonymous_namespace; }
        inline auto root_namespace() -> namespace_container& { return _anonymous_namespace; }
        
        auto add_symbol(const symbolreference &ns, const std::shared_ptr<PatternAst> &symbol) -> void;
        auto add_symbol(const symbolreference &ns, const std::shared_ptr<SetAst> &symbol) -> void;
        auto add_symbol(const symbolreference &ns, const std::shared_ptr<EnumAst> &symbol) -> void;
        auto add_symbol(const symbolreference &ns, const std::shared_ptr<TypeAst> &symbol) -> void;
        auto add_symbol(const symbolreference &ns, const std::shared_ptr<TypeAliasAst> &symbol) -> void;
        auto add_symbol(const symbolreference &ns, const std::shared_ptr<AutomataAst> &symbol, size_t start_state) -> void;
        
        // Find the symbol by searching the specified namespaces
        template<typename T, typename TAction> inline static auto find(const std::shared_ptr<container> &root_cntr, const symbolreference &symbol_name, const std::vector<symbolreference> &search_namespaces, const TAction &action) -> void {
            // Create a list of fully qualified names
            struct sym_search {
                size_t min_ns_depth; // We must matches this amount as namespace - no symbols returned until this reach zero
                symbolreference name; // This is the symbol we're refering to
            };
            std::vector<sym_search> sym_searches;
            sym_searches.push_back(sym_search { 0, symbol_name });
            for(auto &sn : search_namespaces) {
                sym_searches.push_back(sym_search { sn.size(), sn });
                for(auto &n : symbol_name) {
                    sym_searches.back().name.push_back(n);
                }
            }
            
            // recursively search referenced containers
            std::set<const container*> processed;
            std::vector<std::shared_ptr<container>> unprocessed;
            unprocessed.push_back(root_cntr);
            while(!unprocessed.empty()) {
                if(processed.find(unprocessed.back().get()) == processed.end()) {
                    // process it
                    auto cntr = unprocessed.back();
                    processed.emplace(cntr.get());
                    unprocessed.pop_back();
                    
                    // add the references
                    for(auto &r : cntr->_references) {
                        unprocessed.push_back(r);
                    }
                    
                    // We search namespaces by traveling down the hierarchy, and return 'partial' matches as we get to a dead end
                    
                    struct ns_search {
                        const namespace_container* ns;
                        size_t depth; // This is the depth we've already traversed downwards (and matched)
                        const sym_search* sym;
                    };
                    
                    std::vector<ns_search> unprocessed_namespaces;
                    for(auto &n : sym_searches) {
                        unprocessed_namespaces.emplace_back();
                        unprocessed_namespaces.back().ns = &cntr->_anonymous_namespace;
                        unprocessed_namespaces.back().depth = 0;
                        unprocessed_namespaces.back().sym = &n;
                    }
                    
                    while(!unprocessed_namespaces.empty()) {
                        auto ns = unprocessed_namespaces.back().ns;
                        auto depth = unprocessed_namespaces.back().depth;
                        auto sym = unprocessed_namespaces.back().sym;
                        unprocessed_namespaces.pop_back();
                        
                        if (sym->min_ns_depth <= depth) {
                            auto f = symbols_accessor<T>::get(ns).equal_range(sym->name[depth].value());
                            std::vector<T> found;
                            for(auto i = f.first; i != f.second; i++) {
                                found.push_back(i->second);
                            }
                            for(auto &i : found) {
                                // We found a match
                                if (!action(cntr, i, sym->name, depth)) {
                                    // Do not continue
                                    return;
                                }
                            }
                        }
                        auto nf = ns->namespaces.find(sym->name[depth].value());
                        if (nf != ns->namespaces.end()) {
                            depth++;
                            if (sym->name.size() != depth) {
                                unprocessed_namespaces.emplace_back();
                                unprocessed_namespaces.back().ns = &(nf->second);
                                unprocessed_namespaces.back().depth = depth;
                                unprocessed_namespaces.back().sym = sym;
                            }
                        }
                    }
                } else {
                    // already processed - skip it
                    unprocessed.pop_back();
                }
            }
        }
    };
    
    template<> struct symbols_accessor<std::shared_ptr<PatternAst>> { static inline auto get(const namespace_container *ns) -> const symbol_table<std::shared_ptr<PatternAst>>& { return ns->dl_patterns; } };
    template<> struct symbols_accessor<std::shared_ptr<SetAst>> { static inline auto get(const namespace_container *ns) -> const symbol_table<std::shared_ptr<SetAst>>& { return ns->dl_sets; } };
    template<> struct symbols_accessor<std::shared_ptr<EnumAst>> { static inline auto get(const namespace_container *ns) -> const symbol_table<std::shared_ptr<EnumAst>>& { return ns->enums; } };
    template<> struct symbols_accessor<std::shared_ptr<TypeAst>> { static inline auto get(const namespace_container *ns) -> const symbol_table<std::shared_ptr<TypeAst>>& { return ns->types; } };
    template<> struct symbols_accessor<std::shared_ptr<TypeAliasAst>> { static inline auto get(const namespace_container *ns) -> const symbol_table<std::shared_ptr<TypeAliasAst>>& { return ns->aliases; } };
    template<> struct symbols_accessor<std::pair<std::shared_ptr<AutomataAst>, size_t>> { static inline auto get(const namespace_container *ns) -> const symbol_table<std::pair<std::shared_ptr<AutomataAst>, size_t>>& { return ns->dl_automatas; } };
}

