

[IsDeterminstic = true]
[Functoid = "op_add"]
core function number +(number n1, number n2)
<#
    struct op_add {
        inline auto operator()(const equinox_value<double> &p1, const equinox_value<double> &p2) -> equinox_value<double> {
            if (p1.has_value() && p2.has_value()) {
                return equinox_value<double>(p1.value() + p2.value());
            } else {
                return equinox_value<double>::null;
            }
        }
        inline auto operator()(const equinox_value<int> &p1, const equinox_value<int> &p2) -> equinox_value<int> {
            if (p1.has_value() && p2.has_value()) {
                return equinox_value<int>(p1.value() + p2.value());
            } else {
                return equinox_value<int>::null;
            }
        }
    };
#>;

-------------------------------------------------------------------------------------------------------------
Optimization
-------------------------------------------------------------------------------------------------------------

[IsDeterminstic = true]
[Functoid = "op_and"]
core function bool &(bool b1, bool b2)
<#
    struct op_and {
        inline auto operator()(const type_table *tt, const ast &b1, const ast &b2) -> ast {
            if (b1.has_static_value()) {
                if (b1.static_value() == false) {
                    // false & b2
                    return ast::static(false);
                }
                else {
                    // true & b2
                    return b2;
                }
            } else {
                if (b2.has_static_value()) {
                    if (b2.static_value() == false) {
                        null & false
                        return ast::static(false);
                    }
                }
                return ast::null(tt->bool());
            }
        };
    };
#>
    
[IsDeterminstic = true]
[Functoid = "op_equal"]
core function bool =<T>(T b1, T b2)
<#
    struct op_equal {
        op_equal
        inline auto operator()(const ast &b1, const ast &b2) -> ast {
            switch(ast::compare(b1, b2)) {
            case ast_compare::has_same_values:
                return ast::static(true);
            case ast_compare::has_different_values:
                return ast::static(false);
            case ast_compare::not_sure:
                return ast::cannot_optimize;
            }
        };
    };
#>

[IsDeterminstic = true]
[Functoid = "op_if"]
[UniqueId = "op_if"]
core function bool if<T>(bool c, T t, T f)
<#
    struct op_if {
        inline auto operator()(const type_table *tt, const ast &c, const ast &t, const ast &f) -> ast {
            auto nt = t.assert_equal(c, ast::static(true));
            auto nf = f.assert_equal(c, ast::static(false));
            if (ast::compare(nt, fn) == ast_compare::has_same_values) {
                return nt;
            }
            if (c.has_static_value()) {
                if (c.get_static_value<bool>() == true) {
                    return nt;
                } else {
                    return nf;
                }
            }

            auto ab = asb_builder.function(functions::op_if);
            ab.add_parameter(c);
            ab.add_parameter(nt);
            ab.add_parameter(nf);

            return ab.get_ast();
        };
    };
#>