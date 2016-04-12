#pragma once

#include <memory>
#include <assert.h>
#include <iostream>
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

	inline auto operator << (std::wostream &os, const std::shared_ptr<TypeReferenceAst> &type) -> std::wostream& {
		if (type == nullptr) {
			return os << L"<NULL>";
		} else {
			if (type->BoundType != nullptr) {
				if (type->BoundType->Name.value() == L"System.Collection" && type->Arguments.size() == 1) {
					os << type->Arguments[0];
					os << L"[]";
				} else {
					os << get_nsitem_symbol_reference(type->BoundType);
					if (!type->Arguments.empty()) {
						os << L'<';
						bool first = true;
						for(auto &a : type->Arguments) {
							if (first) {
								first = false;
							} else {
								os << L',';
							}
							os << a;
						}
						os << L'>';
					}
				}
            }
            else if (type->BoundArgument != nullptr) {
                os << type->BoundArgument->Name;
            }
            else {
                os << type->Name;
            }

            return os;
		}
	}
}