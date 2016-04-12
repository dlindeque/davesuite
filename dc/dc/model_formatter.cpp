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
        inline static auto write_type(output_writer &stm, const std::shared_ptr<TypeAst> &t) -> bool {
            if (!t->Arguments.empty()) {
                stm << L"template<";
                bool first = true;
                for(auto &a : t->Arguments) {
                    if (first) {
                        first = false;
                    } else {
                        stm << ',';
                    }
                    stm << L"typename " << a->Name.value();
                }
                stm << L"> ";
            }
            stm << L"class " << t->Name.value() << L";";
            return true;
        }
    };
    struct declaration_writer {
        static auto get_all_properties(const TypeAst *t, std::vector<const std::shared_ptr<TypePropertyAst>> &lst) -> void {
            if (t->Parent != nullptr) {
                auto ptype = dynamic_cast<const TypeAst*>(t->Parent->BoundType.get());
                if (ptype != nullptr) {
                    get_all_properties(ptype, lst);
                }
            }
            for(auto &p : t->Properties) {
                lst.push_back(p);
            }
        }

		inline static auto write_enum(output_writer &stm, const std::shared_ptr<EnumAst> &e) -> bool {
            for(auto &d : e->Documentation) {
                stm << L"// " << trim_docs(d.value()) << endl;
            }
			stm << L"enum class " << e->Name.value() << L" {" << inc;
            int value = 1;
            bool first = true;
			for (auto &item : e->Items) {
                if (first) {
                    first = false;
                } else {
                    stm << L',';
                }
                for(auto &id : item->Documentation) {
                    stm << endl << L"// " << trim_docs(id.value());
                }
				stm << endl << item->Name.value() << L" = " << (value++);
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
			stm << L"}";
            return true;
    	}
        inline static auto write_type(output_writer &stm, const std::shared_ptr<TypeAst> &t) -> bool  {
            const TypeAst *parent_type = nullptr;
            if (t->Parent != nullptr) {
                parent_type = dynamic_cast<const TypeAst*>(t->Parent->BoundType.get());
            }

            for(auto &d : t->Documentation) {
                stm << L"// " << trim_docs(d.value()) << endl;
            }
            if (!t->Arguments.empty()) {
                stm << L"template<";
                bool first = true;
                for(auto &a : t->Arguments) {
                    if (first) {
                        first = false;
                    } else {
                        stm << ',';
                    }
                    stm << L"typename " << a->Name.value();
                }
                stm << L'>' << endl;
            }
            stm << L"class " << t->Name.value();
            if (t->Parent != nullptr) {
                stm << L": public ";
                write_cpp_type(stm, t->Parent, true);
            }
            stm << L" {";
            stm << endl << L"private:" << inc;
            for(auto &p : t->Properties) {
                stm << endl;
                write_cpp_type(stm, p->Type);
                stm << L" " << p->BackingField << L";";
            }
            if (t->IsAbstract) {
                stm << dec << endl << L"protected:" << inc;
            } else {
                stm << dec << endl << L"public:" << inc;
            }
            // constructors
            stm << endl << t->Name.value() << L"()";
            if (parent_type != nullptr) {
                stm << endl << L": " << parent_type->Name.value() << L"()";
            }
            stm << endl << L"{}" << endl;
            // copy
            stm << t->Name.value() << L"(const " << t->Name.value() << L" &c)";
            bool first = true;
            if (parent_type != nullptr) {
                stm << endl << L": " << parent_type->Name.value() << L"(c)";
                first = false;
            }
            for(auto &p : t->Properties) {
                if (first) {
                    first = false;
                    stm << endl << L": ";
                } else {
                    stm << L", ";
                }
                stm << p->BackingField << L"(c." << p->BackingField << L')';
            }
            stm << endl << L"{}" << endl;
            // move
            stm << t->Name.value() << L"(" << t->Name.value() << L" &&c)";
            first = true;
            if (parent_type != nullptr) {
                stm << endl << L": " << parent_type->Name.value() << L"(std::move(c))";
                first = false;
            }
            for(auto &p : t->Properties) {
                if (first) {
                    first = false;
                    stm << endl << L": ";
                } else {
                    stm << L", ";
                }
                stm << p->BackingField << L"(std::move(c." << p->BackingField << L"))";
            }
            stm << endl << L"{}" << endl;
            // custom
            std::vector<const std::shared_ptr<TypePropertyAst>> all_properties;
            get_all_properties(t.get(), all_properties);
            if (!all_properties.empty()) {
                stm << L"template<";
                first = true;
                for(auto &p : all_properties) {
                    if (first) {
                        first = false;
                    } else {
                        stm << L", ";
                    }
                    stm << L"typename _T" << p->Name.value();
                }
                stm << L"> " << t->Name.value() << L'(';
                first = true;
                for(auto &p : all_properties) {
                    if (first) {
                        first = false;
                    } else {
                        stm << L", ";
                    }
                    stm << L"_T" << p->Name.value() << L"&& " << p->Name.value();
                }
                stm << L')';
                first = true;
                if (parent_type != nullptr) {
                    std::vector<const std::shared_ptr<TypePropertyAst>> all_parent_properties;
                    get_all_properties(parent_type, all_parent_properties);
                    stm << endl << L": " << parent_type->Name.value() << L"(";
                    for(auto &p : all_parent_properties) {
                        if (first) {
                            first = false;
                        } else {
                            stm << L", ";
                        }
                        stm << L"std::forward<_T" << p->Name.value() << L">(" << p->Name.value() << L")";
                    }
                    stm << L")";
                    first = false;
                }
                for(auto &p : t->Properties) {
                    if (first) {
                        first = false;
                        stm << endl << L": ";
                    } else {
                        stm << L", ";
                    }
                    stm << p->BackingField << L"(std::forward<_T" << p->Name.value() << L">(" << p->Name.value() << L"))";
                }
                stm << endl << L"{}" << endl;
            }
            if (t->IsAbstract) {
                stm << dec << endl << L"public:" << inc << endl;
            }
            // destructors
            if (t->Parent != nullptr || !t->Children.empty()) {
                stm << endl << L"virtual ~" << t->Name.value() << L"() { }" << endl;
            }

            // properties
            for(auto &p : t->Properties) {
                for(auto &d : p->Documentation) {
                    stm << endl << L"// " << trim_docs(d.value());
                }
                stm << endl << L"inline auto " << p->Name.value() << L"() const -> const ";
                write_cpp_type(stm, p->Type);
                stm << L"&" << L" { return " << p->BackingField << L"; }";
                for(auto &d : p->Documentation) {
                    stm << endl << L"// " << trim_docs(d.value());
                }
                stm << endl << L"template<typename _Value> inline auto set_" << p->Name.value() << L"(_Value&& value) -> void { " << p->BackingField << L" = std::forward<_Value>(value); }";
            }

            // assignment
            stm << endl << endl << L"inline auto operator = (const " << t->Name.value() << L" &c) -> " << t->Name.value() << L"& {" << inc << endl;
            if (t->Parent != nullptr) {
                stm << L"((";
                write_cpp_type(stm, t->Parent, true);
                stm << L")*this) = c;" << endl;
            }
            for(auto &p : t->Properties) {
                stm << p->BackingField << L" = c." << p->BackingField << L';' << endl;
            }
            stm << L"return *this;" << dec << endl << L'}';
            stm << endl << L"inline auto operator = (" << t->Name.value() << L" &&c) -> " << t->Name.value() << L"& {" << inc << endl;
            stm << L"if (this != &c) {" << inc << endl;
            if (t->Parent != nullptr) {
                stm << L"((";
                write_cpp_type(stm, t->Parent, true);
                stm << L")*this) = std::move(c);" << endl;
            }
            for(auto &p : t->Properties) {
                stm << p->BackingField << L" = std::move(c." << p->BackingField << L");" << endl;
            }
            stm << dec << endl << L'}' << endl;
            stm << L"return *this;" << dec << endl << L'}';

            // operators
            stm << endl << L"friend inline auto operator == (const " << t->Name.value() << L" &v1, const " << t->Name.value() << L" &v2) -> bool {" << inc << endl;
            stm << L"return dc::equal(v1, v2);" << dec << endl << L'}';
            stm << endl << L"friend inline auto operator != (const " << t->Name.value() << L" &v1, const " << t->Name.value() << L" &v2) -> bool {" << inc << endl;
            stm << L"return !dc::equal(v1, v2);" << dec << endl << L'}';
            stm << endl << L"friend inline auto operator < (const " << t->Name.value() << L" &v1, const " << t->Name.value() << L" &v2) -> bool {" << inc << endl;
            stm << L"return dc::compare(v1, v2) < 0;" << dec << endl << L'}';
            stm << endl << L"friend inline auto operator > (const " << t->Name.value() << L" &v1, const " << t->Name.value() << L" &v2) -> bool {" << inc << endl;
            stm << L"return dc::compare(v1, v2) > 0;" << dec << endl << L'}';
            stm << endl << L"friend inline auto operator <= (const " << t->Name.value() << L" &v1, const " << t->Name.value() << L" &v2) -> bool {" << inc << endl;
            stm << L"return dc::compare(v1, v2) <= 0;" << dec << endl << L'}';
            stm << endl << L"friend inline auto operator >= (const " << t->Name.value() << L" &v1, const " << t->Name.value() << L" &v2) -> bool {" << inc << endl;
            stm << L"return dc::compare(v1, v2) >= 0;" << dec << endl << L'}';
            stm << endl << L"friend inline auto operator << (std::wostream &os, const " << t->Name.value() << L" &value) -> std::wostream& {" << inc << endl;
            stm << L"return dc::standard_writer(os, value);" << dec << endl << L'}';

            stm << dec << endl << L"};";
            return true;
        }
    };
    struct implementation_writer {
    	inline static auto write_enum(output_writer &stm, const std::shared_ptr<EnumAst> &e) -> bool {
            return true;
    	}
        inline static auto write_type(output_writer &stm, const std::shared_ptr<TypeAst> &t) -> bool  {
            return true;
        }
    };

    struct comparer_writer {
        inline static auto write_enum(output_writer &stm, const std::wstring &ns, const std::shared_ptr<EnumAst> &e) -> bool {
            // We will rely on the standard compare template for enums
            return true;
        }
        inline static auto write_type(output_writer &stm, const std::wstring &ns, const std::shared_ptr<TypeAst> &t) -> bool  {
            // We have to calculate the cost of comparing each field, then compare cheapest first

            // compare
            stm << L"template<";
            if (!t->Arguments.empty()) {
                stm << L"template Arg0";
                for(size_t i = 1; i < t->Arguments.size(); i++) {
                    stm << L",template Arg" << (int)i;
                }
            }
            stm << L"> struct compare<" << ns << t->Name.value();
            if (!t->Arguments.empty()) {
                stm << L"<Arg0";
                for(size_t i = 1; i < t->Arguments.size(); i++) {
                    stm << L",Arg" << (int)i;
                }
                stm << L"> ";
            }
            stm << L"> {" << inc << endl;
            stm << L"inline auto operator()(const " << ns << t->Name.value();
            if (!t->Arguments.empty()) {
                stm << L"<Arg0";
                for(size_t i = 1; i < t->Arguments.size(); i++) {
                    stm << L",Arg" << (int)i;
                }
                stm << L"> ";
            }
            stm << L" &v1, const " << ns << t->Name.value();
            if (!t->Arguments.empty()) {
                stm << L"<Arg0";
                for(size_t i = 1; i < t->Arguments.size(); i++) {
                    stm << L",Arg" << (int)i;
                }
                stm << L"> ";
            }
            stm << L" &v2) const -> int {" << inc << endl;
            if (t->Parent != nullptr) {
                stm << L"int c = compare<";
                write_cpp_type(stm, t->Parent, true);
                stm << L">()(v1, v2); if (c != 0) return c;" << endl;
            } else {
                stm << L"int c = 0;" << endl;
            }
            for(auto &p : t->Properties) {
                stm << L"c = compare<";
                write_cpp_type(stm, p->Type, true);
                stm << L">()(v1." << p->Name.value() << L"(), v2." << p->Name.value() << L"()); if (c != 0) return c;" << endl;
            }
            stm << L"return c;" << dec << endl << L"}";
            stm << dec << endl << L"};" << endl;

            // equal
            stm << L"template<";
            if (!t->Arguments.empty()) {
                stm << L"template Arg0";
                for(size_t i = 1; i < t->Arguments.size(); i++) {
                    stm << L",template Arg" << (int)i;
                }
            }
            stm << L"> struct equal<" << ns << t->Name.value();
            if (!t->Arguments.empty()) {
                stm << L"<Arg0";
                for(size_t i = 1; i < t->Arguments.size(); i++) {
                    stm << L",Arg" << (int)i;
                }
                stm << L"> ";
            }
            stm << L"> {" << inc << endl;
            stm << L"inline auto operator()(const " << ns << t->Name.value();
            if (!t->Arguments.empty()) {
                stm << L"<Arg0";
                for(size_t i = 1; i < t->Arguments.size(); i++) {
                    stm << L",Arg" << (int)i;
                }
                stm << L"> ";
            }
            stm << L" &v1, const " << ns << t->Name.value();
            if (!t->Arguments.empty()) {
                stm << L"<Arg0";
                for(size_t i = 1; i < t->Arguments.size(); i++) {
                    stm << L",Arg" << (int)i;
                }
                stm << L"> ";
            }
            stm << L" &v2) const -> bool {" << inc << endl;
            if (t->Parent != nullptr) {
                stm << L"if (!equal<";
                write_cpp_type(stm, t->Parent, true);
                stm << L">()(v1, v2)) return false;" << endl;
            }
            for(auto &p : t->Properties) {
                stm << L"if (!equal<";
                write_cpp_type(stm, p->Type, true);
                stm << L">()(v1." << p->Name.value() << L"(), v2." << p->Name.value() << L"())) return false;" << endl;
            }
            stm << L"return true;" << dec << endl << L"}";
            stm << dec << endl << L"};" << endl;
            return true;
        }
    };
    struct output_operator_writer {
        inline static auto write_enum(output_writer &stm, const std::wstring &ns, const std::shared_ptr<EnumAst> &e) -> bool {
            // We will rely on the standard output operator for enums
            return true;
        }
        inline static auto write_type(output_writer &stm, const std::wstring &ns, const std::shared_ptr<TypeAst> &t) -> bool  {
            // Summary (in future we will be able to suppress generation of the writers so to provide a custom one)
            // name{..}
            stm << L"template<typename _Os";
            if (!t->Arguments.empty()) {
                for(size_t i = 0; i<t->Arguments.size(); i++) {
                    stm << L",typename _Arg" << (int)i;
                }
            }
            stm << L"> struct summary_writer<_Os, " << ns << t->Name.value();
            if (!t->Arguments.empty()) {
                stm << L"<Arg0";
                for(size_t i = 1; i< t->Arguments.size();i++) {
                    stm << L",_Arg" << (int)i;
                }
                stm << L"> ";
            }
            stm << L"> {" << inc << endl;
            stm << L"inline auto operator()(_Os &os, const " << ns << t->Name.value();
            if (!t->Arguments.empty()) {
                stm << L"<Arg0";
                for(size_t i = 1; i< t->Arguments.size();i++) {
                    stm << L",_Arg" << (int)i;
                }
                stm << L">";
            }
            stm << L" &value) const -> _Os& {" << inc << endl;
            stm << L"return os << \"" << cpp_string(t->Name.value());
            if (!t->Arguments.empty()) {
                stm << L"<..>";
            }
            stm << L"{..}\";";
            stm << dec << endl << L"}";
            stm << dec << endl << L"};" << endl;

            // Standard
            // name{ property1 = <summary>, property2 = <summary> }
            stm << L"template<typename _Os";
            if (!t->Arguments.empty()) {
                for(size_t i = 0; i<t->Arguments.size(); i++) {
                    stm << L",typename _Arg" << (int)i;
                }
            }
            stm << L"> struct standard_writer<_Os, " << ns << t->Name.value();
            if (!t->Arguments.empty()) {
                stm << L"<Arg0";
                for(size_t i = 1; i< t->Arguments.size();i++) {
                    stm << L",_Arg" << (int)i;
                }
                stm << L"> ";
            }
            stm << L"> {" << inc << endl;
            stm << L"inline auto operator()(_Os &os, const " << ns << t->Name.value();
            if (!t->Arguments.empty()) {
                stm << L"<Arg0";
                for(size_t i = 1; i< t->Arguments.size();i++) {
                    stm << L",_Arg" << (int)i;
                }
                stm << L">";
            }
            stm << L" &value) const -> _Os& {" << inc << endl;
            stm << L"return os << \"" << cpp_string(ns + t->Name.value());
            if (!t->Arguments.empty()) {
                stm << L"<..>";
            }
            stm << L"{";
            if (!t->Properties.empty()) {
                stm << L' ' << t->Properties[0]->Name.value() << L" = \" << dc::write_summary(os, " << t->Properties[0]->Name.value() << L"()) << \"";
                for(size_t i = 1; i < t->Properties.size();i++) {
                    stm << L' ' << t->Properties[i]->Name.value() << L" = \" << dc::write_summary(os, " << t->Properties[i]->Name.value() << L"()) << \"";
                }
            }
            stm << L" }\";";
            stm << dec << endl << L"}";
            stm << dec << endl << L"};" << endl;

            // Full
            // name{ property1 = <full>, property2 = <full> }
            stm << L"template<typename _Os";
            if (!t->Arguments.empty()) {
                for(size_t i = 0; i<t->Arguments.size(); i++) {
                    stm << L",typename _Arg" << (int)i;
                }
            }
            stm << L"> struct full_writer<_Os, " << ns << t->Name.value();
            if (!t->Arguments.empty()) {
                stm << L"<Arg0";
                for(size_t i = 1; i< t->Arguments.size();i++) {
                    stm << L",_Arg" << (int)i;
                }
                stm << L"> ";
            }
            stm << L"> {" << inc << endl;
            stm << L"inline auto operator()(_Os &os, const " << ns << t->Name.value();
            if (!t->Arguments.empty()) {
                stm << L"<Arg0";
                for(size_t i = 1; i< t->Arguments.size();i++) {
                    stm << L",_Arg" << (int)i;
                }
                stm << L">";
            }
            stm << L" &value) const -> _Os& {" << inc << endl;
            stm << L"return os << \"" << cpp_string(ns + t->Name.value());
            if (!t->Arguments.empty()) {
                stm << L"<..>";
            }
            stm << L"{";
            if (!t->Properties.empty()) {
                stm << L' ' << t->Properties[0]->Name.value() << L" = \" << dc::write_full(os, " << t->Properties[0]->Name.value() << L"()) << \"";
                for(size_t i = 1; i < t->Properties.size();i++) {
                    stm << L' ' << t->Properties[i]->Name.value() << L" = \" << dc::write_full(os, " << t->Properties[i]->Name.value() << L"()) << \"";
                }
            }
            stm << L" }\";";
            stm << dec << endl << L"}";
            stm << dec << endl << L"};" << endl;

            return true;
        }
    };

    auto collect_all_types(std::map<position, std::pair<std::wstring, std::shared_ptr<TypeAst>>> &types, const std::wstring &ns, const namespace_container &items) -> void
    {
        for(auto &t : items.types) {
            types.emplace(t.second->Spn.begin, std::pair<std::wstring, std::shared_ptr<TypeAst>>(ns, t.second));
        }
        if (ns.empty()) {
            for(auto &item : items.namespaces) {
                collect_all_types(types, item.first, item.second);
            }
        } else {
            for(auto &item : items.namespaces) {
                collect_all_types(types, ns + L"::" + item.first, item.second);
            }
        }
    }
    
    template<class _Writer> auto write_all_enums(output_writer &stm, const namespace_container &items) -> bool
    {
        bool ok = true;
        bool first = true;
        for (auto &e : items.enums) {
            if (first) {
                first = false;
            } else {
                stm << endl;
            }
            ok &= _Writer::write_enum(stm, e.second);
        }
                
        for(auto &ns : items.namespaces) {
            stm << L"namespace " << ns.first << L" {" << inc << endl;
            ok &= write_all_enums<_Writer>(stm, ns.second);
            stm << dec << endl << L'}' << endl;
        }

        return ok;
    }

    template<class _Writer> auto write_flat(output_writer &stm, const namespace_container &items, const std::wstring &parent_ns) -> bool
    {
        bool ok = true;
        for(auto &e : items.enums) {
            ok &= _Writer::write_enum(stm, parent_ns, e.second);
        }
        for(auto &t : items.types) {
            ok &= _Writer::write_type(stm, parent_ns, t.second);
        }
        for(auto &n : items.namespaces) {
            ok &= write_flat<_Writer>(stm, n.second, parent_ns + n.first + L"::");
        }
        return ok;
    }

    template<class _Writer> auto write_all(output_writer &stm, const namespace_container &items) -> bool
    {
        // Write the enums
        bool ok = write_all_enums<_Writer>(stm, items);

        // Order the types in the order they were defined in the source file
        std::map<position, std::pair<std::wstring, std::shared_ptr<TypeAst>>> types;
        collect_all_types(types, L"", items);

        std::wstring cur_ns = L"";

        bool in_ns = false;
        for (auto &t : types) {
            if (t.second.first != cur_ns) {
                if (in_ns) {
                    stm << dec << endl << L'}' << endl;
                }
                if (t.second.first.empty()) {
                    in_ns = false;
                } else {
                    stm << L"namespace " << t.second.first << L" {" << inc << endl;
                    in_ns = true;
                }
                cur_ns = t.second.first;
            }

            ok &= _Writer::write_type(stm, t.second.second);
            stm << endl;
        }

        if (in_ns) {
            stm << dec << endl << L'}' << endl;
        }
        
        return ok;
    }

    inline auto process_enum(std::shared_ptr<EnumAst> &t) -> bool
    {
        return true;
    }

    inline auto process_type(std::shared_ptr<TypeAst> &t, std::unordered_multimap<const TypeAst*, std::shared_ptr<TypeAst>> &hierarchy_map) -> bool
    {
        // Create a backing field for all properties
        std::set<std::wstring> used;
        for(auto &p : t->Properties) {
            used.emplace(p->Name.value());
        }
        for(auto &p : t->Properties) {
            auto fname = L"_" + p->Name.value();
            auto f = used.emplace(fname);
            while(!f.second) {
                fname = L"_" + fname;
                f = used.emplace(fname);
            }
            p->BackingField = fname;
        }
        // Add to the hierarchy map if we've got a parent
        if (t->Parent != nullptr) {
            assert(dynamic_cast<const TypeAst*>(t->Parent->BoundType.get()) != nullptr);
            hierarchy_map.emplace((const TypeAst*)t->Parent->BoundType.get(), t);
        }
        return true;
    }

    auto process_all(namespace_container &items, std::unordered_multimap<const TypeAst*, std::shared_ptr<TypeAst>> &hierarchy_map) -> bool {
        bool ok = true;
        for (auto &e : items.enums) {
            ok &= process_enum(e.second);
        }
        
        for (auto &t : items.types) {
            ok &= process_type(t.second, hierarchy_map);
        }
        
        for(auto &ns : items.namespaces) {
            ok &= process_all(ns.second, hierarchy_map);
        }
        
        return ok;
    }

    auto setup_children_all(namespace_container &items, std::unordered_multimap<const TypeAst*, std::shared_ptr<TypeAst>> &hierarchy_map) -> bool {
        bool ok = true;

        for(auto &t : items.types) {
            auto f = hierarchy_map.equal_range(t.second.get());
            for(auto x = f.first; x != f.second; ++x) {
                t.second->Children.push_back(x->second);
            }
        }

        for(auto &ns : items.namespaces) {
            ok &= setup_children_all(ns.second, hierarchy_map);
        }
        
        return ok;
    }

    auto set_hierarchy_reference(TypeAst *type) -> void {
        type->MustBeReferenceType = true;
        for(auto &child : type->Children) {
            set_hierarchy_reference(child.get());
        }
    }

    auto classify_all(namespace_container &items) -> bool {
        bool ok = true;

        for(auto &t : items.types) {
            if (!t.second->Children.empty()) {
                set_hierarchy_reference(t.second.get());
            } else {
                // If a type 'reference' itself, it must be a reference type
                for(auto &p : t.second->Properties) {
                    auto pbt = dynamic_cast<const TypeAst*>(p->Type->BoundType.get());
                    if (pbt != nullptr && pbt->Name.value() == t.second->Name.value() && pbt->Arguments.size() == t.second->Arguments.size()) {
                        t.second->MustBeReferenceType = true;
                    }
                }
            }
        }

        for(auto &ns : items.namespaces) {
            ok &= classify_all(ns.second);
        }
        
        return ok;
    }

    auto output_model_cpp::process(DocumentAstProcessor &processor) const -> bool {
        // Uncontextual processing
        std::unordered_multimap<const TypeAst*, std::shared_ptr<TypeAst>> hierarchy_map; // parent -> child
        if (!process_all(processor.root_cntr()->root_namespace(), hierarchy_map)) return false;

        // Setup the children
        if (!setup_children_all(processor.root_cntr()->root_namespace(), hierarchy_map)) return false;

        // Classify each type
        if (!classify_all(processor.root_cntr()->root_namespace())) return false;

        return true;
    }

    auto output_model_cpp::write_h(DocumentAstProcessor &processor) const -> bool {
    	//std::vector<std::shared_ptr<container>> cntrs;
    	//find_all_containers(processor.root_cntr(), cntrs);

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
        hstm << L"#include <memory>" << endl;
        hstm << L"#include \"modelhelpers.h\"" << endl << endl;

        // Write all the #include statements
        //for(auto &cntr : cntrs) {
    	//for(auto &r : cntr->references()) {
        for(auto &r : processor.root_cntr()->references()) {
    		if (!r->is_virtual()) {
                auto incfn = get_relative_filename(fn, get_standard_output_filename(r->filename(), _path, ".model.h"));
                hstm << L"#include \"" << std::wstring(incfn.begin(), incfn.end()) << L"\"" << endl;
    		}
    	}
        //}

        bool ok = true;
        //for(auto &cntr : cntrs) {
        //ok &= write_all<forward_writer>(a, cntr->root_namespace());
    	//}
        ok &= write_all<forward_writer>(hstm, processor.root_cntr()->root_namespace());
    	//for(auto &cntr : cntrs) {
        //	ok &= write_all<declaration_writer>(hstm, cntr->root_namespace());
        //}
        ok &= write_all<declaration_writer>(hstm, processor.root_cntr()->root_namespace());
        hstm << L"namespace dc {" << inc << endl;
        ok &= write_flat<comparer_writer>(hstm, processor.root_cntr()->root_namespace(), L"");
        ok &= write_flat<output_operator_writer>(hstm, processor.root_cntr()->root_namespace(), L"");
        hstm << dec << endl << L'}';
        return ok;
    }
    
    auto output_model_cpp::write_cpp(DocumentAstProcessor &processor) const -> bool
    {
    	//std::vector<std::shared_ptr<container>> cntrs;
    	//find_all_containers(processor.root_cntr(), cntrs);
    	
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
        //for(auto &cntr : cntrs) {
        //	ok &= write_all<implementation_writer>(cppstm, cntr->root_namespace());
        //}
        ok &= write_all<implementation_writer>(cppstm, processor.root_cntr()->root_namespace());
        return ok;
    }
}
