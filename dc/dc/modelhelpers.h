#pragma once

#include <string>
#include <vector>
#include <iostream>

namespace dc
{
	template<typename T> struct compare {
		inline auto operator()(const T &v1, const T &v2) const -> int {
			return v1 == v2 ? 0 : v1 < v2 ? -1 : 1;
		}
	};
	template<typename T> inline auto int compare(const T &v1, const T &v2) -> int { return compare<T>()(v1, v2); }

	template<typename T> struct equal {
		inline auto operator()(const T &v1, const T &v2) const -> bool { return v1 == v2; }
	};
	template<typename T> inline auto int equal(const T &v1, const T &v2) -> int { return equal<T>()(v1, v2); }

	template<typename _Os, typename T> struct summary_writer {
		inline auto operator()(_Os &os, const T &value) const -> _Os& {
			return os << value;
		}
	};
	template<typename _Os, typename T> write_summary(_Os &os, const T &value) const -> _Os& { return summary_writer<_Os, T>()(os, value); }

	template<typename _Os, typename T> struct standard_writer {
		inline auto operator()(_Os &os, const T &value) const -> std::wostream& {
			return os << value;
		}
	};
	template<typename _Os, typename T> write_standard(_Os &os, const T &value) const -> _Os& { return standard_writer<_Os, T>()(os, value); }

	template<typename _Os, typename T> struct full_writer {
		inline auto operator()(_Os &os, const T &value) const -> std::wostream& {
			return os << value;
		}
	};
	template<typename _Os, typename T> write_full(_Os &os, const T &value) const -> _Os& { return full_writer<_Os, T>()(os, value); }

	template<typename _Os> struct writer_formatter {
		static inline auto format(_Os &os, const std::wstring &value) -> _Os& {
			return os << value;
		}
		static inline auto format(_Os &os, const std::string &value) -> _Os& {
			return os << std::wstring(value.begin(), value.begin());
		}
	};
	template<> struct writer_formatter<std::ostream> {
		static inline auto format(_Os &os, const std::wstring &value) -> _Os& {
			return os << std::string(value.begin(), value.end());
		}
		static inline auto format(_Os &os, const std::string &value) -> _Os& {
			return os << value;
		}
	};

	template<typename _Os> struct summary_writer<_Os, std::string> {
		inline auto operator()(_Os &os, const std::string &value) const -> _Os& {
			writer_formatter<_Os>::format(os, L"\"");
			writer_formatter<_Os>::format(os, value);
			writer_formatter<_Os>::format(os, L"\"");
		}
	};
	template<typename _Os> struct summary_writer<_Os, std::wstring> {
		inline auto operator()(_Os &os, const std::wstring &value) const -> _Os& {
			writer_formatter<_Os>::format(os, L"\"");
			writer_formatter<_Os>::format(os, value);
			writer_formatter<_Os>::format(os, L"\"");
		}
	};

	template<class T, class Allocator> struct compare<std::vector<T, Allocator>> {
		inline auto operator()(const std::vector<T, Allocator>& v1, const std::vector<T, Allocator>& v2) const -> int {
			if (v1.size() == v2.size()) {
				compare<T> cmp;
				for(size_t i = 0; i < v1.size(); ++i) {
					auto c = cmp(v1[i], v2[i]);
					if (c != 0) return c;
				}
				return 0;
			} else {
				return v1.size() < v2.size() ? -1 : 1;
			}
		};
	};
	template<class T, class Allocator> struct equal<std::vector<T, Allocator>> {
		inline auto operator()(const std::vector<T, Allocator>& v1, const std::vector<T, Allocator>& v2) const -> bool {
			if (v1.size() == v2.size()) {
				equal<T> eq;
				for(size_t i = 0; i < v1.size(); i++) {
					if (!eq(v1[i], v2[i])) return false;
				}
				return true;
			} else {
				return false;
			}
		}
	};


	template<> struct compare<std::string> {
		inline auto operator()(const std::string &v1, const std::string &v2) const -> int { 
			return strcmp(v1.c_str(), v2.c_str());
		}
	};

	template<> struct compare<std::wstring> {
		inline auto operator()(const std::wstring &v1, const std::wstring &v2) const -> int { 
			return StrWCmp(v1.c_str(), v2.c_str());
		}
	};
}