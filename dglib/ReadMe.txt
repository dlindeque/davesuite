Dave Gherkin
------------



--------------------------------------------------------------------------------------------------------------------------------
Gherkin File
--------------------------------------------------------------------------------------------------------------------------------
Feature: Some text
    Additional descriptive text

# Comments like this

Background:
    Given ...
    And ...
    When ...
    And ...
    Then ...

Scenario: Name
    Given ...
    And ...
    When ...
    And ...
    Then ....
    And ...

Scenario Outline:
    Given ...
    And ...
    When ...
    And ...
    Then ...
    And ...

Examples:
    | Scenario Name                    | var1 | var2 |
    | The name to use for the scenario | ...  | ...  |
    ...
--------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------
Template File.
This file is a standard code-gen script (ds) file. 
The file must have one root expression of type Feature->string
--------------------------------------------------------------------------------------------------------------------------------
// This is a comment
matchset formatStep(string multiline, Table table)
{
    'I have (>\d+) cars'  -> <"_cars = std::stoi(L"<# first #>")">;
    'I have (>\d+) ports' -> <"_ports = std::stoi(L"<# first #>")">;
};
// formatStep: string,string,table->string

let scenarioMethods =
        map
            <"
            inline auto <# ScenarioName #>() -> bool {
                _stm << L"Running <# ScenarioName #>";
                try {
                    <# Steps ~> map (s => formatStep s.StepText, s.Multiline, s.Table) ~> join "\n" #>
                    _stm << L" - Pass" << std::endl;
                    return true;
                }
                catch(std::exception &e) {
                    _stm << L" - FAIL: " << e.what() << std::endl;
                    return false;
                }
            }
            ">
        ~> join "\n";

let rullAll =
        map
            <"
                ok &= <# ScenarioName #>();
            ">
        ~> join "\n";

let featureName : Feature->string = Name ~> cppIdentifier;

set file = header; // Specifies that we're targetting the header file
// The template body must be a function taking Feature as parameter, a partially applied text template will do the trick!
<"
#include <ostream>

class <# featureName #> {
private:
    int _cars;
    int _ports;
    std::wostream &_stm;
public:
    <# featureName #>() = delete;
    <# featureName #>(const <# featureName #> &) = delete;
    <# featureName #>(<# featureName #> &&c)
        : _cars(c._cars), _ports(c._ports), _stm(std::move(c._stm))
    {} 
    <# featureName #>(std::wostream &stm)
        : _cars(0), _ports(0), _stm(stm)
    {}
    
    <# Scenarios ~> scenarioMethods #>

    inline auto operator()() -> bool {
        bool ok = true;
        <# runAll #>
        return ok;
    }
};
">;
--------------------------------------------------------------------------------------------------------------------------------

********************************************************************************************************************************
*                                                   -= Example =-                                                              *   
********************************************************************************************************************************
--------------------------------------------------------------------------------------------------------------------------------
Gherkin File: Simple_Expression_Lexer.dgf
--------------------------------------------------------------------------------------------------------------------------------
Feature: Simple Expression Lexer
    The simple expression lexer will tokenise text to be parsed later

Scenario: Literal number
    Given the expression '45'
    When I analyse the expression
    Then I expect no error
    And I expect the following tokens
    | token type | token value |
    | number     | 45          |

Scenario: Literal text
    Given the expression '"This is some text"'
    When I analyse the expression
    Then I expect no error
    And I expect the following tokens
    | token type | token value       |
    | text       | This is some text |
--------------------------------------------------------------------------------------------------------------------------------
Template file (C++)
--------------------------------------------------------------------------------------------------------------------------------

matchset formatStep(string multiline, Table table)
{
    'the expression ''(>.*)'''      -> <"_expression = L"<# first ~> cppString #>";">;
    'I analyse the expression'      -> <"
                                       std::wstringstream src;
                                       src << _expression;
                                       src.seekg(0);
                                       int end_line = 1, end_column = 1, lex_state = 0;
                                       expression_token tkn;
                                       while(true) {
                                           davelexer::re_lex(src, end_line, end_column, lex_state, tkn);
                                           if (tkn.type == expression_token_type::eod) {
                                               break;
                                           }
                                           else {
                                               _tokens.push_back(token { tkn.type, tkn.value });
                                           }
                                       }
                                       ">;
    'I expect no error'             -> <"if (_error) throw std::exception("Expected no errors");">;
    'I expect the following tokens' -> <"
                                       std::vector<token> expected_tokens;
                                       <#= table.Rows
                                            |> map <"expected_tokens.push_back(token{ expression_token_type::<# GetColumn("token type") #>, L"<# GetColumn("token value") #>" });">
                                       #>
                                       if (expected_tokens.size() != _tokens.size()) throw std::exception("Tokens mismatch");
                                       // compare each row
                                       ">;"
};

let featureName : Feature->string = Name ~> cppIdentifier;

set file = header; // Specifies that we're targetting the header file

<"
#include <ostream>
#include <string>
#include <vector>

class <# featureName #> {
private:
    struct token {
        expression_token_type type;
        std::wstring value;
    };
    std::wstring _expression;
    std::vector<token> _tokens;
    bool _error;
    std::wostream &_stm;
public:
    <# featureName #>() = delete;
    <# featureName #>(const <# featureName #> &) = delete;
    <# featureName #>(<# featureName #> &&c)
        : _cars(c._cars), _ports(c._ports), _stm(std::move(c._stm))
    {} 
    <# featureName #>(std::ostream &stm)
        : _stm(stm)
    {}
    
    <# 
        Scenarios 
            ~> map
                <"
                inline auto <# ScenarioName #>() -> bool {
                    _stm << L"Running <# ScenarioName #>";
                    try {
                        {<# Steps ~> map (s => formatStep s.StepText, s.Multiline, s.Table) ~> join "}\n{" #>}
                        _stm << L" - Pass" << std::endl;
                        return true;
                    } catch(std::exception &e) {
                        _stm << L" - FAIL: " << e.what() << std::endl;
                        return false;
                    }
                }
                ">
            ~> join "\n"
    #>

    inline auto operator()() -> bool {
        bool ok = true;
        <#
            Scenarios
                ~> map
                    <"
                        ok &= <# ScenarioName #>();
                    ">
                ~> join "\n"
        #>
        return ok;
    }
};
">;
--------------------------------------------------------------------------------------------------------------------------------
Template file (C#)
--------------------------------------------------------------------------------------------------------------------------------
matchset formatStep(string multiline, Table table)
{
    'the expression ''(.*)'''       -> <"_expression = "<# first ~> csString #>";">;
    'I analyse the expression'      -> <"
                                       // Run the C# lexer and add tokens to _tokens;
                                       ">;
    'I expect no error'             -> <"if (_error) throw new Exception("Expected no errors");">;
    'I expect the following tokens' -> <"
                                       List<Token> expectedTokens;
                                       <#= table.Rows
                                            |> map <"expectedTokens.Add(new Token { Type = expressionTokenType.<# GetColumn("token type") #>, Value = "<# GetColumn("token value") #>" });">
                                       #>
                                       if (expectedTokens.Count != _tokens.Count) throw new Exception("Tokens mismatch");
                                       // compare each row
                                       ">;"
};

let featureName : Feature->string = Name ~> csIdentifier;

<"
using System;
using System.IO;

namespace Test
{
    public class <# featureName #> 
    {
        private struct Token {
            expression_token_type Type;
            string Value;
        };
        private string _expression;
        private List<Token> _tokens;
        private bool _error;
        private TextWriter _stm;

        public <# featureName #>(TextWriter stm)
        {
            if(stm == null)
            {
                throw new ArgumentNullException()
            }
            _stm = stm;
        }
    
        <# 
            Scenarios 
                ~> map
                    <"
                    public bool <# ScenarioName #>()
                    {
                        _stm.Write("Running <# ScenarioName #>");
                        try 
                        {
                            {<# Steps ~> map (s => formatStep s.StepText, s.Multiline, s.Table) ~> join "}\n{" #>}
                            _stm.WriteLine(" - Pass");
                            return true;
                        }
                        catch(Exception ex) {
                            _stm.WriteLine(" - FAIL: {0}", ex.Message);
                            return false;
                        }
                    }
                    ">
                ~> join "\n"
        #>

        public bool RunAll()
        {
            bool ok = true;
            <#
                Scenarios
                    ~> map
                        <"
                            ok &= <# ScenarioName #>();
                        ">
                    ~> join "\n"
            #>
            return ok;
        }
    }
}
">;
--------------------------------------------------------------------------------------------------------------------------------

Compiling:
dg.exe \dg:test.dg \ds:test.ds