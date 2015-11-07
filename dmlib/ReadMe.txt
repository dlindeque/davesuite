--------------------------------------------------------------------------------------------------------------------------------
Creating models made easy
--------------------------------------------------------------------------------------------------------------------------------

Standard code-gen script (ds)


--------------------------------------------------------------------------------------------------------------------------------
Example: Model file (*.dm)
--------------------------------------------------------------------------------------------------------------------------------

// class's are 'model' code, but the 'attribute values' are 'script' code.
[Visitor = true]
abstract class Expression
{
};

// type's are 'script' code
type SomeType
{
};

// root expression are 'script' code
range 1 10
    |> map
        <"
        sealed class PExpression<# id ~> fmt #> : Expression
        {
            <#
                range 1
                    ~> map
                        <"Expression _exp<# id #>;">
            #>
        };
        ">;

// templates are 'model' code
template sealed class LiteralExpression<T>
{
    T Value
};

// template instantiations are 'model' code
class IntExpression = LiteralExpression<int>;
class DoubleExpression = LiteralExpression<double>;
class StringExpression = LiteralExpression<string>;

sealed class FunctionCallExpression : Expression
{
    string FunctionName,
    Expression[] Parameters
};


--------------------------------------------------------------------------------------------------------------------------------
Script (*.ds)
--------------------------------------------------------------------------------------------------------------------------------
let cf : ('a->'b)->('a->bool)->'a->'b = (formatter:'a->'b, predicate:'a->bool, x:'a) => predicate x ? formatter x : null;
let cf = (tf, ff, predicate, x) => predicate x ? tf x : tf x;

let getPrimitiveType type =
    when type.Name = "string" then "std::wstring"
    when type.Name = "int" then "int"
    when type.Name = "double" then "double"
    when type.IsReferenceType then <"std::shared_ptr<<#= getPrimitiveType type.UnderlyingType #>>">
    when type.Name = "vector" then <"std::vector<<#= getPrimitiveType (first type.Arguments) #>>">
    else failwith "Unknown type";

let formatForwards : Type->string =
    <"
    <# 
        HasRootVisitor |> cf 
        <"
        class <# Name ~> cppIdentifier #>_visitor
        class const_<# Name ~> cppIdentifier #>_visitor;
        "> 
    #>
    class <# Name ~> cppIdentifier #>;
    <# Children ~> formatForwards #>
    ">;

let formatHierarchy : Type->string =
    with nonAbstractMembers : Type->Type[] =
        IsAbstract |> cf (Children ~> collect nonAbstractMembers) (o ~> Children ~> collect nonAbstractMembers)
    return 
    <"
    <#
        HasRootVisitor |> cf
        <"
        class const_<# Name ~> cppIdentifier #>_visitor abstract {
        public:
            virtual ~const_<# Name ~> cppIdentifier #>_visitor() {}
            <#
                nonAbstractMembers ~> map
                <"
                virtual auto visit(<#)
                ">
            #>
        }
        ">
    #>
    class <# Name ~> cppIdentifier #><# Parent |> cf <" : <# Parent ~> Name ~> cppIdentifier #>"> #><# IsSealed |> cf <" sealed"> #><# IsAbstract |> cf <" abstract"> #> {
    private:
        <#
            Properties
                ~> map
                    <"
                    <# getPrimitiveType #> _<# Name ~> camelCase #>;    
                    ">
        #>
    public:
        <# IsSealed ~> ! |> cf
            <"
            virtual ~<# Name ~> cppIdentifier #>() {}
            ">
        #>
        <#
            HasRootVisitor |> cf
            <"
            virtual auto accept(const_<# Name ~> cppIdentifier #>_visitor *visitor) const -> void <# IsAbstract |> cf <"= 0;"> <"{ visitor->visit(this); }"> #>
            virtual auto accept(<# Name ~> cppIdentifier #>_visitor *visitor) -> void <# IsAbstract |> cf <"= 0;"> <"{ visitor->visit(this); }"> #>
            "> 
        #>
    };

    <# Children ~> formatHierarchy #>
    ">;

<"
// Generated models

// Forwards
<#
    map formatForwards
#>

// Classes
<#
    map formatHierarchy
#>
">;

--------------------------------------------------------------------------------------------------------------------------------

