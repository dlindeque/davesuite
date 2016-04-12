#pragma once

#include "cpp_helpers.h"
#include "helpers.h"
#include "output_writer.h"

namespace dc
{
	inline auto to_cpp_symbol(const symbolreference &name) -> std::wstring
    {
        std::wstring s;
        if (name.empty()) return L"";
        s.append(name[0].value());
        for(size_t i = 1; i < name.size(); i++) {
            s.append(L"::");
            s.append(name[i].value());
        }
        return s;
    }
    
    inline auto is_type(const std::shared_ptr<TypeDefinitionAst> &type, const std::wstring &ns, const std::wstring &name) -> bool {
        if (type->Name.value() != name) return false;
        auto dns = ((const NamespaceAst*)type->DeclaringAst.get())->Name;
        return dns.size() == 1 && dns[0].value() == ns;
    }

    inline auto write_cpp_type(output_writer &os, const std::shared_ptr<TypeReferenceAst> &type, bool structural = false) -> output_writer&
    {
    	if (!structural && type->BoundType != nullptr) {
            auto bt = dynamic_cast<const TypeAst*>(type->BoundType.get());
            if (bt != nullptr && bt->MustBeReferenceType) {
                os << L"std::shared_ptr<";
                write_cpp_type(os, type, true);
                return os << L'>';
            }
    	}
            
        if (type->BoundArgument != nullptr) {
            os << type->BoundArgument->Name.value();
        }
        else if (is_type(type->BoundType, L"System", L"Collection") && type->Arguments.size() == 1) {
    		os << L"std::vector<";
    		write_cpp_type(os, type->Arguments[0]);
    		os << L'>';
    	}
    	else if (is_type(type->BoundType, L"System", L"Word")) {
    		os << L"unsigned int";
    	}
    	else if (is_type(type->BoundType, L"System", L"DoubleWord")) {
    		os << L"unsigned long";
    	}
    	else if (is_type(type->BoundType, L"System", L"Int8")) {
    		os << L"char";
    	}
    	else if (is_type(type->BoundType, L"System", L"Int16")) {
    		os << L"short";
    	}
    	else if (is_type(type->BoundType, L"System", L"Int32")) {
    		os << L"int";
    	}
    	else if (is_type(type->BoundType, L"System", L"Int64")) {
    		os << L"long long";
    	}
    	else if (is_type(type->BoundType, L"System", L"String")) {
    		os << L"std::string";
    	}
    	else if (is_type(type->BoundType, L"System", L"WString")) {
    		os << L"std::wstring";
    	}
    	else if (is_type(type->BoundType, L"System", L"Float")) {
    		os << L"float";
    	}
    	else if (is_type(type->BoundType, L"System", L"DFloat")) {
    		os << L"double";
    	} else {
    		os << to_cpp_symbol(get_nsitem_symbol_reference(type->BoundType));
    		if (!type->Arguments.empty()) {
    			os << L'<';
    			bool first = true;
    			for(auto &a : type->Arguments) {
    				if (first) {
    					first = false;
    				} else {
    					os << L',';
    				}
    				write_cpp_type(os, a);
    			}
    			os << L'>';
    		}
    	}
        return os;
    }

    inline auto extract_filename(const std::string &path) -> std::string
	{
	    // Get abc.xyz from /path1/path2/abc.xyz
	    // or /abc.xyz
	    // or abc.xyz

	    auto f = path.find_last_of("/");
	    if (f != std::string::npos) {
	        return std::string(path.begin() + f + 1, path.end());
	    } 
	    else {
	        return path;
	    }
	}
    
    inline auto extract_file_directory(const std::string &path) -> std::string
    {
        // Get '/path1/path2/' from /path1/path2/abc.xyz
        // Get '' from abc.xyz
        // Get '/' from /abc.xyz
        // Get 'path1/' from path1/abc.xyz
        
        auto f = path.find_last_of("/");
        if (f == std::string::npos) {
            // We have no '/'
            return "";
        }
        else {
            // We've got at least one '/'
            return path.substr(0, f + 1);
        }
    }

	inline auto combine_path_filename(const std::string &path, const std::string &fn) -> std::string
	{
	    if (path.empty()) return fn;
	    auto x = path.end();
	    x--;
	    if (*x == '/') {
	        return path + fn;
	    }
	    else {
	        return path + "/" + fn;
	    }
	}

	inline auto get_standard_output_filename(const std::string &parent_filename, const std::string &output_path, const std::string &new_ext) -> std::string
	{
		return combine_path_filename(output_path, extract_filename(parent_filename) + new_ext);
	}

	inline auto get_relative_filename(const std::string &anchor_fn, const std::string &relative_fn) -> std::string
	{
		// anchor = /a/b/c/d
		// rel    = /a/b/e/f
		// when we've removed the common bits
		// anchor = c/d  = [c,d]
		// rel    = e/f  = [e,f]
		// Now we 'back track' the anchor to the front (i.e.: once: ../) then we add the relative (i.e.: ../e/f)
		const char *a, *r;
		a = anchor_fn.c_str();
		r = relative_fn.c_str();
        bool found_slash = false;
		while(*a != '\x0' && *a == *r) {
            found_slash |= *a == L'/';
			a++;
			r++;
		}
        if (found_slash) {
            // reverse to the last slash
            while(*a != '/') {
                a--;
                r--;
            }
            a++;
            r++;
        } else {
            // No slashes, we don't have a folder
            a = anchor_fn.c_str();
            r = relative_fn.c_str();
        }
		// Now count the number of anchor directories left in the path (number of '/' s)
		std::string result;
		while(*a != '\x0') {
			if (*a == '/') {
				result.append("../");
			}
			a++;
		}
		result.append(r);
		return result;
	}
    
    template<typename T> inline auto cpp_write_symbolreference(T &os, const symbolreference &sr) -> T& {
        if (!sr.empty()) {
            os << sr[0];
            for(size_t i = 1; i < sr.size(); i++) {
                os << L"::" << sr[i];
            }
        }
        return os;
    }

    inline auto cpp_comment(const std::wstring &v) -> std::wstring {
    	std::wstring r;
    	for(auto &c : v) {
    		switch(c) {
    			case L'\\': r.append(L"{backslash}");break;
    			case L'\n': r.append(L"\\n");break;
    			case L'\r': r.append(L"\\r");break;
    			case L'\t': r.append(L"\\t");break;
    			case L'\v': r.append(L"\\v");break;
    			case L'\f': r.append(L"\\f");break;
    			default: r += c;
    		}
    	}
        return r;
    }

    inline auto cpp_string(const std::wstring &v) -> std::wstring {
    	std::wstring r;
    	for(auto &c : v) {
    		switch(c) {
    			case L'\\': r.append(L"\\\\");break;
    			case L'\n': r.append(L"\\n");break;
    			case L'\r': r.append(L"\\r");break;
    			case L'\t': r.append(L"\\t");break;
    			case L'\v': r.append(L"\\v");break;
    			case L'\f': r.append(L"\\f");break;
    			default: r += c;
    		}
    	}
        return r;	
    }
}