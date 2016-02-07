//
//  dl.ds.cpp
//  test2
//
//  Created by David Lindeque on 14/12/2015.
//  Copyright © 2015 David Lindeque. All rights reserved.
//

#include "dl.ds.hpp"
#include "log.h"

namespace davelexer
{
    auto BuildNfaReAst::visit(const ReferenceReAst* ast) -> void
    {
        auto f = _patterns.find(ast->Name, _search_namespaces);
        if (f.first == f.second) {
            davecommon::log::error::PatternNotFound(_logger, _cntr, ast->Spn, ast->Name);
            _ok = false;
        } else {
            auto i = f.first;
            i++;
            if (i != f.second) {
                // Found many
                davecommon::log::error::PatternFoundMoreThanOnce(_logger, _cntr, ast->Spn, ast->Name, f.first, f.second);
            } else {
                f.first->item()->Value->accept(this);
            }
        }
    }

}