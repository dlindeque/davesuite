

[IsDeterminstic = true]
[Name = "op_add"]
[Implementation =
<#
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
#>]
external function number add(number n1, number n2);

[IsDeterminstic = true]
[Name = "op_and"]
[Implementation =
<#
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
#>
]
external function bool and(bool b1, bool b2);

[IsDeterminstic = true]
[Name = "op_or"]
[Implementation =
<#
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
#>
]
external function bool or(bool b1, bool b2);
    
[IsDeterminstic = true]
[Name = "op_equal"]
[Implementation =
<#
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
#>
]
external function bool equal<T>(T b1, T b2);

[IsDeterminstic = true]
[Name = "op_if"]
[Implementation =
<#
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
#>
]
external function bool if<T>(bool c, T t, T f);
