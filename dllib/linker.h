#pragma once

#include "model.h"

namespace davelexer
{
    class linker : public lex_ast_visitor {
    private:
        qname _current_ns;
        std::vector<qname> _imported;
        std::vector<qname> _sections;
        std::vector<qname> _patterns;
        bool &_ok;

        inline static auto is_name(const qname &n1, const qname &n2) -> bool {
            if (n1.size() == n2.size()) {
                for (size_t i = 0; i < n1.size(); i++) {
                    if (n1[i] != n2[i]) {
                        return false;
                    }
                }
                return true;
            }
            else {
                return false;
            }
        }

        inline static auto try_resolve_name(const qname &name, const qname &current_ns, const std::vector<qname> &imported, const std::vector<qname> &nametable, qname &result)->bool {
            if (name.size() == 1){
                // We need to search the imported namespaces & the current namespace
                for (auto &nt : nametable) {
                    if (nt.size() == 1 && nt[0] == name[0]) {
                        result = name;
                        return true;
                    }
                }
                qname cn(current_ns);
                cn.push_back(name[0]);
                for (auto &nt : nametable) {
                    if (is_name(cn, nt)) {
                        result = cn;
                        return true;
                    }
                }
                for (auto &in : imported) {
                    qname cn(in);
                    cn.push_back(name[0]);
                    for (auto &nt : nametable) {
                        if (is_name(cn, nt)) {
                            result = cn;
                            return true;
                        }
                    }
                }
                return false;
            }
            else {
                // Try to find the item in the nametable
                for (auto &nt : nametable) {
                    if (is_name(nt, name)) {
                        result = name;
                        return true;
                    }
                }

                return false;
            }
        }

        class re_linker sealed : public re_ast_visitor{
        private:
            bool &_ok;
            const qname &_current_ns;
            const std::vector<qname> &_imported;
            const std::vector<qname> &_patterns;
        public:
            re_linker(bool &ok, const qname &current_ns, const std::vector<qname> &imported, const std::vector<qname> &patterns)
                : _ok(ok), _current_ns(current_ns), _imported(imported), _patterns(patterns)
            {}
            virtual auto accept(re_ast_char_set_match*) -> void override {}
            virtual auto accept(re_ast_reference* ast) -> void override {
                // Find 'name' in patterns and resolve to the fully qualified name
                qname r;
                _ok &= try_resolve_name(ast->name(), _current_ns, _imported, _patterns, r);
                ast->name() = r;
            }
            virtual auto accept(re_ast_then* ast) -> void override {
                ast->re1()->accept(this);
                ast->re2()->accept(this);
            }
            virtual auto accept(re_ast_or* ast) -> void override {
                ast->re1()->accept(this);
                ast->re2()->accept(this);
            }
            virtual auto accept(re_ast_cardinality* ast) -> void override {
                ast->re()->accept(this);
            }
        };
    public:
        linker(bool &ok)
            : _ok(ok)
        {}

        virtual auto accept(lex_ast_pattern* ast) -> void override {
            // Process the re (before we add this pattern, to prevent recursive pattern references)
            re_linker rel(_ok, _current_ns, _imported, _patterns);
            ast->ast()->accept(&rel);

            // Add the pattern to the nametable
            qname n(_current_ns);
            n.push_back(ast->name());
            _patterns.push_back(std::move(n));
        }
        virtual auto accept(lex_ast_section* ast) -> void override {
            // Process the items before we add this section to prevent recursive section references
            class item_linker sealed : public lex_ast_section_item_visitor{
            private:
                const qname &_current_ns;
                const std::vector<qname> &_imported;
                const std::vector<qname> &_sections;
                const std::vector<qname> &_patterns;
                bool &_ok;
            public:
                item_linker(const qname &current_ns, const std::vector<qname> &imported, const std::vector<qname> &sections, const std::vector<qname> &patterns, bool &ok)
                    : _current_ns(current_ns), _imported(imported), _sections(sections), _patterns(patterns), _ok(ok)
                {}
                virtual auto accept(lex_ast_import* ast) -> void override {
                    // Find 'name' in sections and resolve to the fully qualified name
                    qname r;
                    _ok &= try_resolve_name(ast->section_to_import(), _current_ns, _imported, _sections, r);
                    ast->section_to_import() = r;
                }
                virtual auto accept(lex_ast_token* ast) -> void override {
                    re_linker rel(_ok, _current_ns, _imported, _patterns);
                    ast->ast()->accept(&rel);
                }
                virtual auto accept(lex_ast_start* ast) -> void override {
                    re_linker rel(_ok, _current_ns, _imported, _patterns);
                    ast->ast()->accept(&rel);
                }
                virtual auto accept(lex_ast_return* ast) -> void override {
                    re_linker rel(_ok, _current_ns, _imported, _patterns);
                    ast->ast()->accept(&rel);
                }
            };

            item_linker il(_current_ns, _imported, _sections, _patterns, _ok);
            for (auto &item : ast->items()) {
                item->accept(&il);
            }

            // Add the section to the nametable
            qname n(_current_ns);
            n.push_back(ast->name());
            _sections.push_back(std::move(n));
        }
        virtual auto accept(lex_ast_option_start* ast) -> void override {
            // The start section must always be fully qualified
        }
        virtual auto accept(lex_namespace* ast) -> void override {
            auto m = _imported.size();
            for (auto &n : ast->name()) {
                _current_ns.push_back(n);
            }

            for (auto &item : ast->items()) {
                item->accept(this);
            }

            for (size_t i = 0; i < ast->name().size(); i++) {
                _current_ns.pop_back();
            }
            _imported.resize(m);
        }
        virtual auto accept(lex_using_namespace* ast) -> void override {
            _imported.push_back(ast->name());
        }
    };
}