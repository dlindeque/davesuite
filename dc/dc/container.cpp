//
//  container.cpp
//  dc
//
//  Created by David Lindeque on 19/01/2016.
//  Copyright © 2016 David Lindeque. All rights reserved.
//

#include "container.h"
#include "dc.ds.h"

namespace dc
{
    auto container::add_symbol(const symbolreference &ns, const std::shared_ptr<PatternAst> &symbol) -> void
    {
        find_ns_container(ns).dl_patterns.emplace(symbol->Name.value(), symbol);
    }
    
    auto container::add_symbol(const symbolreference &ns, const std::shared_ptr<SetAst> &symbol) -> void
    {
        find_ns_container(ns).dl_sets.emplace(symbol->Name.value(), symbol);
    }
    
    auto container::add_symbol(const symbolreference &ns, const std::shared_ptr<EnumAst> &symbol) -> void
    {
        find_ns_container(ns).enums.emplace(symbol->Name.value(), symbol);
    }
    
    auto container::add_symbol(const symbolreference &ns, const std::shared_ptr<TypeAst> &symbol) -> void
    {
        find_ns_container(ns).types.emplace(symbol->Name.value(), symbol);
    }

    auto container::add_symbol(const symbolreference &ns, const std::shared_ptr<TypeAliasAst> &symbol) -> void
    {
        find_ns_container(ns).aliases.emplace(symbol->Name.value(), symbol);
    }
    
    auto container::add_symbol(const symbolreference &ns, const std::shared_ptr<AutomataAst> &symbol, size_t start_state) -> void
    {
        find_ns_container(ns).dl_automatas.emplace(symbol->Name.value(), std::pair<std::shared_ptr<AutomataAst>, size_t>(symbol, start_state));
    }
}