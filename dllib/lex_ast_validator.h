#pragma once

#include <string>
#include <map>
#include <memory>
#include "model.h"
#include "..\common\logger.h"
#include "..\common\container.h"
#include "log.h"

namespace davelexer
{
    class lex_ast_validator sealed : public const_lex_ast_visitor{
    private:
        logger *_logger;
        std::map<std::wstring, std::unique_ptr<re_ast>> _bindings;
    public:
        lex_ast_validator(logger *logger)
            : _logger(logger), _ok(true)
        {}
        virtual ~lex_ast_validator() {}

        bool _ok;

        virtual auto accept(const lex_ast_binding* ast) -> void override {
            _bindings.emplace(std::move(ast->name()), std::move(ast->ast()));
        }
        virtual auto accept(const lex_ast_section* ast) -> void override {
            class section_item_validator sealed : public const_lex_ast_section_item_visitor{
            private:
                class re_validator sealed : public const_re_ast_visitor{
                private:
                    logger *_logger;
                    bool &_ok;
                    const container *_cntr;
                    const std::map<std::wstring, std::unique_ptr<re_ast>> &_bindings;
                public:
                    re_validator(logger *logger, bool &ok, const container *cntr, const std::map<std::wstring, std::unique_ptr<re_ast>> &bindings)
                        : _logger(logger), _ok(ok), _cntr(cntr), _bindings(bindings)
                    {}
                    virtual ~re_validator() {}

                    virtual auto accept(const re_ast_char_set_match* ast) -> void override {
                    }
                    virtual auto accept(const re_ast_reference* ast) -> void override {
                        auto f = _bindings.find(ast->name());
                        if (f == _bindings.end()) {
                            log::error::expression_not_found(_logger, _cntr, ast->spn(), ast->name());
                            _ok = false;
                        }
                        else {
                            f->second->accept(this);
                        }
                    }
                    virtual auto accept(const re_ast_then* ast) -> void override {
                        ast->re1()->accept(this);
                        ast->re2()->accept(this);
                    }
                    virtual auto accept(const re_ast_or* ast) -> void override {
                        ast->re1()->accept(this);
                        ast->re2()->accept(this);
                    }
                    virtual auto accept(const re_ast_cardinality* ast) -> void override {
                        ast->re()->accept(this);
                    }
                };

                class re_can_be_epsilon_only sealed : public const_re_ast_visitor{
                private:
                    const std::map<std::wstring, std::unique_ptr<re_ast>> &_bindings;
                public:
                    re_can_be_epsilon_only(const std::map<std::wstring, std::unique_ptr<re_ast>> &bindings)
                        : _bindings(bindings)
                    {}
                    virtual ~re_can_be_epsilon_only() {}

                    bool _result;

                    virtual auto accept(const re_ast_char_set_match* ast) -> void override {
                        _result = false;
                    }
                    virtual auto accept(const re_ast_reference* ast) -> void override {
                        auto f = _bindings.find(ast->name());
                        if (f == _bindings.end()) {
                            _result = false;
                        }
                        else {
                            f->second->accept(this);
                        }
                    }
                    virtual auto accept(const re_ast_then* ast) -> void override {
                        ast->re1()->accept(this);
                        if (_result) {
                            ast->re2()->accept(this);
                        }
                    }
                    virtual auto accept(const re_ast_or* ast) -> void override {
                        ast->re1()->accept(this);
                        if (!_result) {
                            ast->re2()->accept(this);
                        }
                    }
                    virtual auto accept(const re_ast_cardinality* ast) -> void override {
                        _result = ast->min() == 0;
                        if (!_result) {
                            ast->re()->accept(this);
                        }
                    }
                };
            private:
                const std::wstring &_token_name;
                logger *_logger;
                bool &_ok;
                const container *_cntr;
                const std::map<std::wstring, std::unique_ptr<re_ast>> &_bindings;
            public:
                section_item_validator(const std::wstring &token_name, logger *logger, bool &ok, const container* cntr, const std::map<std::wstring, std::unique_ptr<re_ast>> &bindings)
                    : _token_name(token_name), _logger(logger), _ok(ok), _cntr(cntr), _bindings(bindings)
                {}
                virtual ~section_item_validator() {}
                virtual auto accept(const lex_ast_import* ast) -> void override {
                    // We will validate shared sections seperately
                }
                virtual auto accept(const lex_ast_token* ast) -> void override {
                    re_validator rv(_logger, _ok, _cntr, _bindings);
                    ast->ast()->accept(&rv);
                    re_can_be_epsilon_only v(_bindings);
                    ast->ast()->accept(&v);
                    if (v._result) {
                        log::error::re_must_process_something(_logger, _cntr, ast->spn(), _token_name);
                        _ok = false;
                    }
                }
                virtual auto accept(const lex_ast_start* ast) -> void override {
                    re_validator rv(_logger, _ok, _cntr, _bindings);
                    ast->ast()->accept(&rv);
                    re_can_be_epsilon_only v(_bindings);
                    ast->ast()->accept(&v);
                    if (v._result) {
                        log::error::re_must_process_something(_logger, _cntr, ast->spn(), _token_name);
                        _ok = false;
                    }
                }
                virtual auto accept(const lex_ast_return* ast) -> void override {
                    re_validator rv(_logger, _ok, _cntr, _bindings);
                    ast->ast()->accept(&rv);
                    re_can_be_epsilon_only v(_bindings);
                    ast->ast()->accept(&v);
                    if (v._result) {
                        log::error::re_must_process_something(_logger, _cntr, ast->spn(), _token_name);
                        _ok = false;
                    }
                }
            };

            for (auto &item : ast->items()) {
                section_item_validator validator(ast->name(), _logger, _ok, ast->ctnr(), _bindings);
                item->accept(&validator);
            }
        }
    };
}