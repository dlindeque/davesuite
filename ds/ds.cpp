// ds.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include <assert.h>

class type_table {

};

template<typename ast, typename T> struct static_value {};
enum class ast_compare {
    has_same_values,
    has_different_values,
    not_sure
};
template<typename ast> struct compare_equality {};

template<typename ast> class equal_premise {
private:
    ast _ast1;
    ast _ast2;
public:
    equal_premise(const ast &ast1, const ast &ast2)
        : _ast1(ast1), _ast2(ast2)
    {}
    equal_premise(const ast &ast1, ast &&ast2)
        : _ast1(ast1), _ast2(std::move(ast2))
    {}
    equal_premise(ast &&ast1, const ast &ast2)
        : _ast1(std::move(ast1)), _ast2(ast2)
    {}
    equal_premise(ast &&ast1, ast &&ast2)
        : _ast1(std::move(ast1)), _ast2(std::move(ast2))
    {}
};

template<typename ast> struct op_add {
    inline auto operator()(const type_table *tt, const ast &p1, const ast &p2) -> ast {
        if (p1.has_static_value() && p2.has_static_value()) {
            return ast::static_value(static_value<ast, double>::get(p1) + static_value<ast, double>::get(p2));
        }
        else {
            return ast::cannot_optimize;
        }
    }
};
template<typename ast> struct op_and {
    inline auto operator()(const type_table *tt, const ast &b1, const ast &b2) -> ast {
        if (b1.has_static_value()) {
            if (!static_value<ast, bool>::get(b1)) {
                // false & b2
                return ast::static_value(false);
            }
            else {
                // true & b2
                return b2;
            }
        }
        else if (b2.has_static_value()) {
            if (!static_value<ast, bool>::get(b2) == false) {
                // b1 & false
                return ast::static_value(false);
            }
            else {
                // b1 & true
                return b1;
            }
        }
        else {
            // Neither has a static value
            return ast::cannot_optimize;
        }
    };
};
template<typename ast> struct op_or {
    inline auto operator()(const type_table *tt, const ast &b1, const ast &b2) -> ast {
        if (b1.has_static_value()) {
            if (static_value<ast, bool>::get(b1)) {
                // true | b2
                return ast::static_value(true);
            }
            else {
                // false | b2
                return b2;
            }
        }
        else if (b2.has_static_value()) {
            if (static_value<ast, bool>::get(b2) == false) {
                // b1 | true
                return ast::static_value(true);
            }
            else {
                // b1 | false
                return b1;
            }
        }
        else {
            // Neither has a static value
            return ast::cannot_optimize;
        }
    };
};
template<typename ast> struct op_equal {
    inline auto operator()(const type_table *tt, const ast &b1, const ast &b2) -> ast {
        switch (compare_equality<ast>::compare(b1, b2)) {
        case ast_compare::has_same_values:
            return ast::static_value(true);
        case ast_compare::has_different_values:
            return ast::static_value(false);
        case ast_compare::not_sure:
            return ast::get_null_ast();
        default:
            throw std::exception("Not implemented");
        }
    };
};
template<typename ast> struct op_if {
    inline auto operator()(const type_table *tt, const ast &c, const ast &t, const ast &f) -> ast {
        if (c.has_static_value()) {
            bool cv;
            auto cvb = static_value<ast, bool>::try_get(c, cv);
            assert(cvb);
            if (cv == true) {
                // We don't have to assert here since we already know that c is static.
                return t;
            }
            else {
                return f;
            }
        }
        else {
            // c does not have a static value, but we can assert it to be true for the true branch, and false for the false branch!
            auto nt = t.assert_premise(equal_premise(c, ast::static(true)));
            auto nf = f.assert_premise(equal_premise(c, ast::static(false)));
            if (ast::compare_equality(nt, fn) == ast_compare::has_same_values) {
                return nt;
            }
            else {
                // We can continue - if the true branch is 'false' and false branch is 'true', then the function is actually just a 'not'

                // c  tv  fv   result
                // 0  0   ?    ?    fv
                // 0  1   ?    ?    fv
                // 1  0   ?    0    !c
                // 1  1   ?    1    c

                // tv = 1: result = c | fv
                // tv = 0: result = !c | fv

                bool tv;
                auto tvb = static_value<ast, bool>::try_get(t, tv);
                if (tvb) {
                    if (tv) {
                        auto ab = ast_builder.function(functions::op_or);
                        ab.add_parameter(c);
                        ab.add_parameter(f);
                        return ab.get_ast();
                    }
                    else {
                        auto nab = ast_builder.function(functions::op_not);
                        nab.add_parameter(c);
                        auto ab = ast_builder.function(functions::op_or);
                        ab.add_parameter(nab.get_ast());
                        ab.add_parameter(f);
                        return ab.get_ast();
                    }
                }

                // c  tv  fv   result
                // 0  ?   0    0    c
                // 0  ?   1    1    !c
                // 1  ?   0    0    ?
                // 1  ?   1    1    ?

                // fv = 1: result = !c | tv
                // fv = 0: result = c | tv

                bool fv;
                auto fvb = static_value<ast, bool>::try_get(f, fv);
                if (fvb) {
                    if (!fv) {
                        auto ab = ast_builder.function(functions::op_or);
                        ab.add_parameter(c);
                        ab.add_parameter(t);
                        return ab.get_ast();
                    }
                    else {
                        auto nab = ast_builder.function(functions::op_not);
                        nab.add_parameter(c);
                        auto ab = ast_builder.function(functions::op_or);
                        ab.add_parameter(nab.get_ast());
                        ab.add_parameter(t);
                        return ab.get_ast();
                    }
                }

                auto ab = ast_builder.function(functions::op_if);
                ab.add_parameter(c);
                ab.add_parameter(nt);
                ab.add_parameter(nf);

                return ab.get_ast();
            }
        }
    };
};

enum class equinox_value_type {
    number,
    boolean
};

class equinox_value {
private:
    equinox_value_type _type;
    double _number;
    bool _bool;
    bool _is_null;
public:
    equinox_value() = delete;
    equinox_value(const nullptr_t&)
        : _is_null(true)
    {}
    equinox_value(double value)
        : _is_null(false), _type(equinox_value_type::number), _number(value)
    {}
    equinox_value(bool value)
        : _is_null(false), _type(equinox_value_type::boolean), _bool(value)
    {}

    inline auto type() const -> equinox_value_type { return _type; }
    inline auto has_static_value() const -> bool { return true; }

    static inline auto static_value(double value) -> equinox_value {
        return equinox_value(value);
    }
    static inline auto static_value(bool value) -> equinox_value {
        return equinox_value(value);
    }

    inline auto get_double() const -> double { return _number; }
    inline auto get_bool() const -> bool { return _bool; }

    static inline auto get_null_ast() -> equinox_value {
        return equinox_value(nullptr);
    }
};

//equinox_value equinox_value::cannot_optimize;

template<> struct static_value<equinox_value, double> { 
    static inline auto try_get(const equinox_value &ast, double &v) -> double {
        if (ast.type() == equinox_value_type::number) {
            v = ast.get_double();
            return true;
        }
        else {
            return false;
        }
    }
};
template<> struct static_value<equinox_value, bool> {
    static inline auto try_get(const equinox_value &ast, bool &v) -> bool {
        if (ast.type() == equinox_value_type::boolean) {
            v = ast.get_bool();
            return true;
        }
        else {
            return false;
        }
    }
};
template<> struct compare_equality<equinox_value> {
    static inline auto compare(const equinox_value &v1, const equinox_value &v2)->ast_compare {
        switch (v1.type()) {
        case equinox_value_type::number:
            if (v2.type() == equinox_value_type::number && v1.get_double() == v2.get_double()) {
                return ast_compare::has_same_values;
            }
            else {
                return ast_compare::has_different_values;
            }
        case equinox_value_type::boolean:
            if (v2.type() == equinox_value_type::boolean && v1.get_bool() == v2.get_bool()) {
                return ast_compare::has_same_values;
            }
            else {
                return ast_compare::has_different_values;
            }
        default:
            throw std::exception("Not implemented");
        }
    }
};

class expr abstract {
public:
    virtual ~expr() {
    }
    virtual auto has_static_value() const -> bool = 0;
};

template<typename T> class literal_expr sealed : public expr{
private:
    T _value;
public:
    literal_expr(T value)
        : _value(value)
    {}
    virtual ~literal_expr() {}
    virtual auto has_static_value() const -> bool { return true; }
    inline auto value() const -> T { return _value; }
};

class ast {
private:
    std::shared_ptr<expr> _exp;
public:
    ast()
        : _exp(nullptr)
    {}
    ast(const ast &c)
        : _exp(c._exp)
    {}
    ast(ast &&c)
        : _exp(std::move(c._exp))
    {}
    ast(const std::shared_ptr<expr> &e)
        : _exp(e)
    {}
    ast(std::shared_ptr<expr> &&e)
        : _exp(std::move(e))
    {}

    inline auto expr() const -> const std::shared_ptr<expr>& { return _exp; }

    inline auto has_static_value() const -> bool { return _exp->has_static_value(); }

    template<typename T> static inline auto static_value(const T &value) -> ast {
        return ast(std::shared_ptr<::expr>(new literal_expr<T>(value)));
    }

    static inline auto get_null_ast() -> ast {
        return ast();
    }
};

template<typename T> struct static_value<ast, T> {
    static inline auto try_get(const ast &v, T &value) -> bool {
        auto exp = dynamic_cast<const literal_expr<T>*>(v.expr().get());
        if (exp == nullptr) {
            return false;
        }
        else {
            value = exp->value();
            return true;
        }
    }
};
template<> struct compare_equality<ast> {
    template<typename T> static inline auto try_compare_literals(const ast &v1, const ast &v2, ast_compare &ac) -> bool {
        auto lit1 = dynamic_cast<const literal_expr<T>*>(v1.expr().get());
        auto lit2 = dynamic_cast<const literal_expr<T>*>(v2.expr().get());
        if (lit1 != nullptr && lit2 != nullptr) {
            if (lit1->value() == lit2->value()) {
                ac = ast_compare::has_same_values;
            }
            else {
                ac = ast_compare::has_different_values;
            }
            return true;
        }
        else {
            return false;
        }
    }

    static inline auto compare(const ast &v1, const ast &v2)->ast_compare {
        ast_compare ac;
        if (try_compare_literals<double>(v1, v2, ac)) {
            return ac;
        }
        if (try_compare_literals<bool>(v1, v2, ac)) {
            return ac;
        }
        return ast_compare::not_sure;
    }
};

template<typename T, typename ast> inline auto get_static_value(const ast &a) -> T { 
    T v;
    if (static_value<ast, T>::try_get(a, v)) {
        return v;
    }
    else {
        return T();
    }
}

#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
    //op_add<ast> eval;
    //auto res = eval(nullptr, ast(std::shared_ptr<expr>(new literal_expr<double>(3))), ast(std::shared_ptr<expr>(new literal_expr<double>(4))));
    //op_add<equinox_value> eval;
    //auto res = eval(nullptr, equinox_value(3.0), equinox_value(4.0));
    //std::wcout << L"Value = " << get_static_value<double>(res) << std::endl;

    //op_and<ast> eval;
    //auto res = eval(nullptr, ast(std::shared_ptr<expr>(new literal_expr<bool>(true))), ast(std::shared_ptr<expr>(new literal_expr<bool>(false))));
    //op_and<equinox_value> eval;
    //auto res = eval(nullptr, equinox_value(true), equinox_value(false));
    //std::wcout << L"Value = " << get_static_value<bool>(res) << std::endl;

    //op_or<ast> eval;
    //auto res = eval(nullptr, ast(std::shared_ptr<expr>(new literal_expr<bool>(false))), ast(std::shared_ptr<expr>(new literal_expr<bool>(true))));
    //op_or<equinox_value> eval;
    //auto res = eval(nullptr, equinox_value(false), equinox_value(false));
    //std::wcout << L"Value = " << get_static_value<bool>(res) << std::endl;

    //op_equal<ast> eval;
    //auto res = eval(nullptr, ast(std::shared_ptr<expr>(new literal_expr<double>(3))), ast(std::shared_ptr<expr>(new literal_expr<double>(3))));
    op_equal<equinox_value> eval;
    auto res = eval(nullptr, equinox_value(4.0), equinox_value(4.0));
    std::wcout << L"Value = " << get_static_value<bool>(res) << std::endl;

	return 0;
}

