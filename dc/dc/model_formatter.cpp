//
//  smcpp.ds.cpp
//  dc
//
//  Created by David Lindeque on 30/01/2016.
//  Copyright © 2016 David Lindeque. All rights reserved.
//

#include "model_formatter.h"
#include "log.h"
#include "logger.h"
#include "container.h"
#include "output_writer.h"
#include "cpp_helpers.h"

#include <map>
#include <fstream>

namespace dc
{
    inline auto trim_docs(const std::wstring &doc) -> std::wstring
    {
        if (doc.empty()) return doc;
        // /// abc abc*
        // 012345678901234
        const wchar_t *s = doc.c_str();
        const wchar_t *e = s + doc.size() - 1;
        while(*s == L'/' || *s == L' ') s++;
        while(*e == L'\n' || *e == L'\r') e--;
        return std::wstring(s, (int)(e-s+1));
    }

    struct forward_writer {
    	inline static auto write_enum(output_writer &stm, const std::shared_ptr<EnumAst> &e) -> bool {
    		stm << L"enum class " << e->Name.value() << L";";
            return true;
    	}
    };
    struct declaration_writer {
		inline static auto write_enum(output_writer &stm, const std::shared_ptr<EnumAst> &e) -> bool {
            for(auto &d : e->Documentation) {
                stm << L"// " << trim_docs(d.value()) << endl;
            }
			stm << L"enum class " << e->Name.value() << L" {" << inc;
			for (auto &item : e->Items) {
                for(auto &id : item->Documentation) {
                    stm << endl << L"// " << trim_docs(id.value());
                }
				stm << endl << item->Name.value() << L",";
			}
			stm << dec << endl << L"};" << endl;
			stm << endl;
			stm << L"inline auto operator <<(std::wostream &os, const " << e->Name.value() << L" &v) -> std::wostream& {" << inc << endl;
			stm << L"switch(v) {";
			for (auto &item : e->Items) {
				stm << endl << L"case " << e->Name.value() << L"::" << item->Name.value() << L": return os << L\"" << item->Name.value() << L"\";";
			}
			stm << endl << L"default: return os << L\"(Program Error)\";" << endl;
			stm << L"}" << dec << endl;
			stm << L"}" << endl;
            return true;
    	}
    };
    struct implementation_writer {
    	inline static auto write_enum(output_writer &stm, const std::shared_ptr<EnumAst> &e) -> bool {
    		return true;
    	}
    };

    template<class _Writer> auto write_all(output_writer &stm, const namespace_container &items) -> bool
    {
    	bool ok = true;
    	for (auto &e : items.enums) {
    		ok &= _Writer::write_enum(stm, e.second);
    	}

    	for(auto &ns : items.namespaces) {
    		stm << L"namespace " << ns.first << L" {" << inc << endl;
    		ok &= write_all<_Writer>(stm, ns.second);
    		stm << dec << endl << L"}" << endl;
    	}
        
        return ok;
    }

    auto find_all_containers(const std::shared_ptr<container> &src, std::vector<std::shared_ptr<container>> &lst) -> void
    {
    	lst.push_back(src);
    	for(auto &r : src->references()) {
    		if (r->is_virtual()) {
    			find_all_containers(r, lst);
    		}
    	}
    }

    auto output_model_cpp::write_h(DocumentAstProcessor &processor) const -> bool {
    	std::vector<std::shared_ptr<container>> cntrs;
    	find_all_containers(processor.root_cntr(), cntrs);

    	std::string fn = get_standard_output_filename(_compile_filename, _path, ".model.h");
    	log::info::WritingOutputFile(_logger, fn);
        std::wofstream stm(fn);
        if (!stm) {
            log::error::FailureOpeningFile(_logger, std::shared_ptr<container>(), span(), fn);
            return false;
        }
        output_adapter a(stm);
    	indenting_writer hstm(a, 4, 0);
        hstm << L"// Generated by Dave Compiler" << endl << endl;
        hstm << L"#pragma once" << endl << endl;
        hstm << L"#include <iostream>" << endl;

        // Write all the #include statements
        for(auto &cntr : cntrs) {
        	for(auto &r : cntr->references()) {
        		if (!r->is_virtual()) {
                    auto incfn = get_relative_filename(fn, get_standard_output_filename(r->filename(), _path, ".model.h"));
                    hstm << L"#include \"" << std::wstring(incfn.begin(), incfn.end()) << L"\"" << endl;
        		}
        	}
        }

        bool ok = true;
        for(auto &cntr : cntrs) {
        	ok &= write_all<forward_writer>(a, cntr->root_namespace());
    	}
    	for(auto &cntr : cntrs) {
        	ok &= write_all<declaration_writer>(hstm, cntr->root_namespace());
        }
        return ok;
    }
    
    auto output_model_cpp::write_cpp(DocumentAstProcessor &processor) const -> bool
    {
    	std::vector<std::shared_ptr<container>> cntrs;
    	find_all_containers(processor.root_cntr(), cntrs);
    	
    	std::string fn = get_standard_output_filename(_compile_filename, _path, ".model.cpp");
    	log::info::WritingOutputFile(_logger, fn);
        std::wofstream stm(fn);
        if (!stm) {
            log::error::FailureOpeningFile(_logger, std::shared_ptr<container>(), span(), fn);
            return false;
        }
        output_adapter a(stm);
        indenting_writer cppstm(a, 4, 0);
        
        cppstm << L"// Generated by Dave Compiler" << endl << endl;
        auto incfn = get_relative_filename(fn, get_standard_output_filename(_compile_filename, _path, ".model.h"));
        cppstm << L"#include \"" << std::wstring(incfn.begin(), incfn.end()) << L"\"" << endl;
        
        bool ok = true;
        for(auto &cntr : cntrs) {
        	ok &= write_all<implementation_writer>(cppstm, cntr->root_namespace());
        }
        return ok;
    }
}
