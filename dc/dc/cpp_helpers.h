#pragma once

#include "cpp_helpers.h"

namespace dc
{
	inline auto to_cpp_enum(const symbolreference &name) -> std::wstring
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
}