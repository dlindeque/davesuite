--------------------------------------------------------------------------------------------------------------------------------
Creating models made easy
--------------------------------------------------------------------------------------------------------------------------------

Double 'code-gen'. The model file can contain script to generate classes, then the classes are fed to the script to
serialize to an underlying language.


--------------------------------------------------------------------------------------------------------------------------------
Example: Model file (*.dm)
--------------------------------------------------------------------------------------------------------------------------------

// class's are 'model' code, but the 'attribute values' are 'script' code.
abstract class Expression
[Visitor = true]
{
};

// type's are 'script' code
type SomeType
{
};

// root expression are 'script' code - output of the script code would be compiled as 'model' code.
range 1 10
    |> map
        <"
        sealed class PExpression<# fmt #> : Expression
        {
            <#
                range 1
                    ~> map
                        <"Expression _exp<# fmt #>;">
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
class DecimalExpression
[Scale = 28] // Property attributes applied to a class/type will be applied to all properties in the class/type
[Precision = 12]
= LiteralExpression<decimal>;
class StringExpression = LiteralExpression<string>;

sealed class FunctionCallExpression : Expression
{
    string FunctionName,
    Expression[] Parameters
};

namespace TermsAndConditions;

[Mutable = false]
[Observable = true]
sealed class Instrument
{
    [IsPrimaryKey = true]
    [Constraint = "PK_Instrument"]
    [IndexType = IndexType.Clustered]
    int InstrumentId,

    [Length = 31]
    [Unicode = false]
    [VariableLength = true]
    string ShortName,

    [Length = 255]
    string LongName,

    Pricing.Price[] Prices
};

namespace Pricing;

// 'model' code
union class Expression
{
    StringExpression(string value),
    IntExpression(int value),
    BinaryExpression(Expression e1, Expression e2)
};

sealed class Price
{
    int InstrumentId,

    [Constraint = "FK_Price_Instrument"]
    TermsAndConditions.Instrument Instrument -> (p,i) => p.Instrument = i.Instrument,

    [Scale = 28]
    [Precision = 12]
    decimal Close
};

--------------------------------------------------------------------------------------------------------------------------------
Script (*.ds)
--------------------------------------------------------------------------------------------------------------------------------
let cf : ('a->'b)->('a->bool)->'a->'b = (formatter:'a->'b, predicate:'a->bool, x:'a) => predicate x ? formatter x : null;
let cf = (tf, ff, predicate, x) => predicate x ? tf x : tf x;

let isReferenceType t =
	t.MustBeReferenceType | t.Size > 100;

let getPrimitiveType type =
    when type.Name = "string" then "std::wstring"
    when type.Name = "int" then "int"
    when type.Name = "double" then "double"
    when type |> isReferenceType then <"std::shared_ptr<<# Name #>>">
    when type.Name = "vector" then <"std::vector<<#= getPrimitiveType (first type.Arguments) #>>">
    else type.Name;

let formatForwards : Type->string =
    <"
    <# 
        HasRootVisitor |> cf 
        <"
        class <# Name ~> cppIdentifier #>_visitor;
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
The script model has the following model
--------------------------------------------------------------------------------------------------------------------------------

enum class PrimitiveType
{
	na,
	_string,
	_int16,
	_int32,
	_int64,
	_single,
	_double,
	_decimal
};

sealed class TypeReference
{
	PrimitiveType PrimitiveType,
	Type ModelType,
	TypeReference[] Arguments
};

enum class IndexType
{
	None,
	Clustered,
	NonClustered
};

sealed class ReferenceMap
{
	Property Foreign,
	Property Primary
};

sealed class Property
{
	TypeReference Type,
	string Name,
	bool IsMutable,
	bool IsObservable,
	bool IsAbstract,
	bool IsVirtual,
	bool IsSealed,
	int Precision,
	int Scale,
	bool Unicode,
	bool VariableLength,
	bool IsPrimaryKey,
	int Length,
	string ConstraintName,
	IndexType IndexType,
	ReferenceMap[] ReferenceMaps
};

sealed class Type
{
	string Name,
	bool HasRootVisitor,
	string RootVisitorName,
	bool MustBeReferenceType,
	bool IsMutable,
	bool IsObservable,
	bool IsAbstract,
	bool IsSealed,
	Type Parent,
	Type[] Arguments,
	Type[] Children
};

attribute bool IsPrimaryKey on [ Entity.ClassProperty ];
attribute bool Mutable on [ Entity.Class, Entity.ClassProperty ];
attribute bool Observable on [ Entity.Class, Entity.ClassProperty ];
