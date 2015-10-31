

[IsDeterminstic = true]
[Functoid = "op_add"]
[UniqueId = "op_add"]
[Body =
<#
	template<typename ast> struct op_add {
		inline auto operator()(const type_table *tt, const ast &p1, const ast &p2) -> ast {
		    if (p1.has_static_value() && p2.has_static_value()) {
                return ast::static(p1.get_static_value<double>() + p2.get_static_value<double>());
            }
		}
	};
#>]
external function number +(number n1, number n2);

[IsDeterminstic = true]
[Functoid = "op_and"]
[UniqueId = "op_and"]
[Body =
<#
    template<typename ast> struct op_and {
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
            } else if (b2.has_static_value()) {
                if (b2.static_value() == false) {
                    b1 & false
                    return ast::static(false);
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
external function bool &(bool b1, bool b2);

[IsDeterminstic = true]
[Functoid = "op_or"]
[UniqueId = "op_or"]
[Body =
<#
    template<typename ast> struct op_or {
        inline auto operator()(const type_table *tt, const ast &b1, const ast &b2) -> ast {
            if (b1.has_static_value()) {
                if (b1.static_value() == true) {
                    // true | b2
                    return ast::static(true);
                }
                else {
                    // false | b2
                    return b2;
                }
            } else if (b2.has_static_value()) {
                if (b2.static_value() == true) {
                    b1 | true
                    return ast::static(true);
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
external function bool &(bool b1, bool b2);
    
[IsDeterminstic = true]
[Functoid = "op_equal"]
[UniqueId = "op_equal"]
[Body =
<#
    template<typename ast> struct op_equal {
        op_equal
        inline auto operator()(const type_table *tt, const ast &b1, const ast &b2) -> ast {
            switch(ast::compare_equality(b1, b2)) {
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
]
external function bool =<T>(T b1, T b2);

[IsDeterminstic = true]
[Functoid = "op_if"]
[UniqueId = "op_if"]
[Body =
<#
    template<typename ast> struct op_if {
        inline auto operator()(const type_table *tt, const ast &c, const ast &t, const ast &f) -> ast {
            auto nt = t.assert_equal(c, ast::static(true));
            auto nf = f.assert_equal(c, ast::static(false));
            if (ast::compare_equality(nt, fn) == ast_compare::has_same_values) {
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
]
external function bool if<T>(bool c, T t, T f);
