#pragma once

#include <memory>
#include <assert.h>
#include "symbolreference.h"

namespace dc
{
	template<typename T> inline auto get_nsitem_symbol_reference(const std::shared_ptr<T> &ast) -> symbolreference {
        assert(dynamic_cast<const NamespaceAst*>(ast->DeclaringAst.get()) != nullptr);
        auto nsast = (const NamespaceAst*)ast->DeclaringAst.get();
        symbolreference sr(nsast->Name);
        sr.push_back(ast->Name);
        return std::move(sr);
	}
}