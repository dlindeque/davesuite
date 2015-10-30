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
The steps file are a template style file. The file contains a double 'mode' sections, it starts out with 'Template' mode.
The mode is switched to 'Code' mode using '<#' and back to template mode using '#>'
--------------------------------------------------------------------------------------------------------------------------------
// This is a comment in template mode
File: Header // Specifies that we're targetting the header file
<#
// This is code mode - this code will be output directly
#include "anything.h"
// Any C++ code is valid

struct scenario_details
{
    std::string name;
    int start_line;
};

class myfeature {
private:
    std::ostream &_stm;
    std::string _scenarioName;
    std::vector<scenario_details> _scenario_details;
    inline auto assert(bool value, const std::string &expectation, const std::string &stepText) -> void {
        if (!value) {
            _stm << _scenarioName + << " failed. Expectation: '" << expectation << "'. See '" << stepText << "'" << std::endl;
            throw std::exception("Assert Failed");
        }
    }
public:
    myfeature(std::ostream &stm)
        : _stm(stm)
    {
        <#= scenarioDefinitions #>;
    }
    
    <#= scenarios #> // We can access the generated scenario code like this.
};

#>

Scenario: scenarios // This is where we define the structure of a scenario. The name 'scenarios' is the name to be used for this template section (See Feature section)
<#
// Back in code mode. We can access scenario parameters like so: <#= scenarioName #>
inline auto <#= scenarioName #>() -> bool {
    _scenarioName = "<#= scenarioName #>";
    _stm << "Running <#= scenarioName #>" << std::endl;
    <# = steps #>
}
#>

Scenario: scenarioDefinitions // We can format scenarios in multiple ways
<#
_scenario_details.push_back(scenario_details { std::string("<#= scenarioName #>"), <#= scenarioStartLine #> });
#>

// Back in template mode. I can create a function for a step using this syntax:
Step: steps matching Given text // The text must be a regex that will match the text in the given step above.
<#
// Back in code mode. We can reference the literal parameters like so: <#= parameterName #>
std::string somevar("<#= parameterName #>");
#>

Step: steps matching When text // The text must be a regex that will match the text in the given step above.
<#
// Back in code mode.
auto somevarlen = somevar.size();
#>

Step: steps matching Then text // The text must be a regex that will match the text in the given step above.
<#
// Back in code mode. We can access scenario and step details like this;
assert(somevarlen == 6, "<#= scenarioName #>", "<#= stepText #>");
#>

--------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------
Sample output cpp file
--------------------------------------------------------------------------------------------------------------------------------
// This is code mode - this code will be output directly
#include "anything.h"
// Any C++ code is valid

struct scenario_details
{
    std::string name;
    int start_line;
};

class myfeature {
private:
    std::ostream &_stm;
    std::string _scenarioName;
    std::vector<scenario_details> _scenario_details;
    inline auto assert(bool value, const std::string &expectation, const std::string &stepText) -> void {
        if (!value) {
            _stm << _scenarioName + << " failed. Expectation: '" << expectation << "'. See '" << stepText << "'" << std::endl;
            throw std::exception("Assert Failed");
        }
    }
public:
    myfeature(std::ostream &stm)
        : _stm(stm)
    {
        _scenario_details.push_back(scenario_details { std::string("Scenario1"), 15 });
        _scenario_details.push_back(scenario_details { std::string("Scenario2"), 28 });
    }

    // Back in code mode. We can access scenario parameters like so: Scenario1
    inline auto Scenario1() -> bool {
        _scenarioName = "Scenario1";
        _stm << "Running Scenario1" << std::endl;
        // Back in code mode. We can reference the literal parameters like so: <#= parameterName #>
        std::string somevar("Hello world");
        // Back in code mode.
        auto somevarlen = somevar.size();
        // Back in code mode. We can access scenario and step details like this;
        assert(somevarlen == 6, "Scenario1", "Then I expect the length to be 6");
    }

    // Back in code mode. We can access scenario parameters like so: Scenario2
    inline auto Scenario1() -> bool {
        _scenarioName = "Scenario2";
        _stm << "Running Scenario2" << std::endl;
        // Etc..
    }
};

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

--------------------------------------------------------------------------------------------------------------------------------
Template File: Simple_Expression_Lexer.dgt
--------------------------------------------------------------------------------------------------------------------------------
File: Header
<#
#include <ostream>
#include <string>
#include <vector>
#include "..\lexer.h"
#include <utils> // vector equivalence

class <#= identifier(featureName) #> {
private:
    std::wostream &_stm;
public:
    <#= identifier(featureName) #>(std::wostream &stm)
        : _stm(stm)
    {
    }

    <#= scenarios #>

    inline auto run_all() -> bool {
        bool ok = true;
        <#= runscenarios #>
        return ok;
    }
};
#>

Scenario: runscenarios
<#
ok &= <#= identifier(scenarioName) #>();
#>

Scenario: scenarios
<#
inline auto <#= identifier(scenarioName) #>() -> bool {
    _stm << L"<#= scenarioName #>";
    bool ok = true;
    <#= steps #>
    if (ok) {
        _stm << L" Pass" << std::endl;
    } else {
        _stm << L" Pass (Suspect)" << std::endl;
    }
    return true;
}
#>

Step: steps matching Given the expression '(.*)'
<#
std::wstring expression(L"<#= cpp_text(match[1]) #>");
#>

Step: steps matching When I analyse the expression
<#
std::vector<token> actual_tokens;
ok &= lexer::try_analyse(expression, &actual_tokens);
#>

Step: steps matching Then I expect no error
<#
if (!ok) {
    _stm << L" FAILED: Lexer error";
    return false;
}
#>

Step: steps matching Then I expect the following tokens
<#
std::vector<token> expected_tokens;
<#= tokenList #>
if (!utils::is_equivalent(actual_tokens, expected_tokens)) {
    _stm << L" FAILED: different tokens";
    return false;
}
#>

Table: tokenList
<#
tokenList.push_back(token { token_type::<# row["token type"] #>, "<# row["token value"] #>" });
#>
--------------------------------------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------------------------------------
When processed using: dg.exe /dgf:Simple_Expression_Lexer.dgf /dgt:Simple_Expression_Lexer.dgf /ouput:Header=Simple_Expression_Lexer.h
Output: Simple_Expression_Lexer.h
--------------------------------------------------------------------------------------------------------------------------------
#include <ostream>
#include <string>
#include <vector>
#include "..\lexer.h"
#include <utils> // vector equivalence

class Simple_Expression_Lexer {
private:
    std::wostream &_stm;
public:
    Simple_Expression_Lexer(std::wostream &stm)
        : _stm(stm)
    {
    }

    inline auto Literal_number() -> bool {
        _stm << L"Literal number";
        bool ok = true;
        std::wstring expression(L"45");
        std::vector<token> actual_tokens;
        ok &= lexer::try_analyse(expression, &actual_tokens);
        if (!ok) {
            _stm << L" FAILED: Lexer error";
            return false;
        }
        std::vector<token> expected_tokens;
        tokenList.push_back(token { token_type::number, "45" });
        if (!utils::is_equivalent(actual_tokens, expected_tokens)) {
            _stm << L" FAILED: different tokens";
            return false;
        }
        if (ok) {
            _stm << L" Pass" << std::endl;
        } else {
            _stm << L" Pass (Suspect)" << std::endl;
        }
        return true;
    }
    inline auto Literal_text() -> bool {
        _stm << L"Literal text";
        bool ok = true;
        std::wstring expression(L"\"This is some text\"");
        std::vector<token> actual_tokens;
        ok &= lexer::try_analyse(expression, &actual_tokens);
        if (!ok) {
            _stm << L" FAILED: Lexer error";
            return false;
        }
        std::vector<token> expected_tokens;
        tokenList.push_back(token { token_type::text, "This is some text" });
        if (!utils::is_equivalent(actual_tokens, expected_tokens)) {
            _stm << L" FAILED: different tokens";
            return false;
        }
        if (ok) {
            _stm << L" Pass" << std::endl;
        } else {
            _stm << L" Pass (Suspect)" << std::endl;
        }
        return true;
    }

    inline auto run_all() -> bool {
        bool ok = true;
        ok &= Literal_number();
        ok &= Literal_text();
        return ok;
    }
};
--------------------------------------------------------------------------------------------------------------------------------