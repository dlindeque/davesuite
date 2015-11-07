Dave Parser
-----------

Parsers
    LR(k)
    -----
        Left-to-right, Rightmost derivation parser. Bottom-up parse (i.e.: number->Expression->Document)
        
        https://en.wikipedia.org/wiki/LR_parser#Constructing_LR.280.29_parsing_tables

        LR(0)
        -----
            LR parser using zero lookahead.
            This parser can generate a simpler, faster parser, but is not as powerful in language acceptance as LALR(1) with the same amount of states.

            We deduce the LR(0) parser tables as follows. Say we have the following grammar:
            0: S -> E $
            1: E -> n
            2: E -> v

            Create the goto-nonterminal set as the distinct set of all non-terminals behind the .
            For each non-terminal behind the ., create a goto transition ot the next state (might be an existing state)
            Create the shift-terminal set as the distinct set of all terminals behind the ., and all the FIRST(N) of all non-terminals.
            For each shift-terminal, create a shift transition to the next state (might be an existing state)
            For each item with nothing behind the ., create a reduce action.

            State 0
            -------
            S -> .E$    (G1)
                goto-nonterminals {E}
                shift-terminals = {n,v}

            State 1 (0 E)
            -------------
            S -> E.$    (S2)
                goto-nonterminals {}
                shift-terminals = {$}

            State 2 (1 $)
            -------------
            S -> E$.    (ACCEPT)
                goto-nonterminals = {}
                shift-terminals = {}

            State 3 (0 n)
            -------------
            E -> n.     (R1)
                goto-nonterminals = {}
                shift-terminals = {}

            State 4 (0 v)
            -------------
            E -> v.     (R2)
                goto-nonterminals = {}
                shift-terminals = {}

            State   n   v   $   S   E
            -------------------------
            0       S3  S4          G1
            1               S2
            2       ACCEPT
            3       Reduce R1
            4       Reduce R2


        SLR(1)
        ------
            Simple LR parser
            LR(0) parser with simple lookahead sets
            Lookahead sets = FOLLOW(NON-TERMINAL)
            It does not take into account the current state for trimming the lookahead sets.
            Not as powerful as LALR(1) and same number of states.

        LALR(1)
        -------
            Look-Ahead LR parser.
            Same number of states as LR(0), but with lookahead included.

        LR(1)
        -----
            Left to right, Rightmost derivation parser using 1 lookahead.
            It was shown that any LR(k) with k>1 has a LR(1) dual. This means that any LR(k)[k>1] language is also a LR(1) language.
            When developing the states, the lookahead is calculated and included as part of the match criteria when checking for existing states.
            Too many states - inefficient. IELR(1) can parse same language with LALR(1) scale of states.

        IELR(1)
        -------
            Inadequacy Elimination LR(1)

        GLR
        ---
            Generalized LR
            Uses multiple parse stacks to analyze all options in the face of conflicts. Say a conflict is found, like a shift/reduce conflict, then both options are
            analyzed using two stacks until the one stack fails, or the two stacks merge (when a decision needs to be made to pick the preferred parse)

    Compiling Parser Tables
    -----------------------
        Conflicts
        ---------
            Shift/Reduce
                A S/R conflict will always be of the following type:
                    1. E -> E.+E    // shift '+' for rule 1
                    2. E -> E*E.    // reduce by rule 2
                A useful error message will be:
                The grammar is ambigious in rule 1 & 2. When parsing a sentence like '3*3+3' the parser is unable to decide whether to process it as '3*3' and '+3' or '3*' and '3+3'.
            Reduce/Reduce        
                With a grammar like this:
                    1. E -> aA
                    2. E -> aB
                    3. A -> n
                    4. B -> n
                The states will look like this:
                    0
                        S -> .E$
                        E -> .aA
                        E -> .aB
                    1
                        S -> E.$
                    2
                        S -> E$.
                    3
                        E -> a.A
                        E -> a.B
                        A -> .n
                        B -> .n
                    4   // R/R conflict
                        E -> aA.
                        E -> aB.
                    5
                        A -> n.
                        B -> n.
                A useful error message will be:
                The grammar is ambigious in rule 1 & 2. When parsing a sentence like 'an' the parser is unable to decide whether to process it as 'a' and 'n' as production 3 (A->n) or 'a' and 'n' as production 4 (B->n).
    PDA
    ---
    Push-Down Automata. This is the 'machine' that can parse the language specified by the parsing tables given.


    LL(k)
    -----
        Left-to-right, Leftmost derivation parser. Top-down parse
        LL(1) languages are a proper subset of LR(1)

    Recursive Descent
    -----------------



LR(1)
==============================================================================================================
S: Aa
S: bAc
S: Bc
S: bBa
A: d
B: d


State 0
-------
S: .Aa, $
S: .bAc, $
S: .Bc, $
S: .bBa, $
A: .d, a
B: .d, c

State 1 (0 d)
-------------
A: d ., a
B: d ., c

State 2 (0 B)
-------------
S: B.c, $

State 3 (2 c)
-------------
S: Bc ., $

State 4 (0 A)
-------------
S: A.a, $

State 5 (4 a)
-------------
S: Aa ., $

State 6 (0 b)
-------------
S: b.Ac, $
S: b.Ba, $
A: .d, c
B: .d, a

State 7 (6 A)
-------------
S: bA.c, $

State 8 (7 c)
-------------
S: bAc ., $

State 9 (6 d)
-------------
A: d ., c
A: d ., a

State 10 (6 B)
--------------
S: bB.a, $

State 11 (10 a)
---------------
S: bBa ., $

LALR(1) would've merged States 1 and 9

==============================================================================================================
dp files
==============================================================================================================
Say we want to define the grammar for gherkin
--------------------------------------------------------------------------------------------------------------

namespace gherkin;

using namespace core;
using namespace davelexer;

set ignore = [ whitespace, comment ];

enum scenario_term_type
{
    given,
    when,
    then
};

type scenario_term
{
    span location,
    string text,
    scenario_term_type type,
    string multilinetext,
    string[][] table
};

type scenario
{
    bool is_background,
    bool is_outline,
    span name_location,
    string name,
    scenario_term[] terms,
    string[][] examples
};

type feature
{
    span name_location,
    string name,
    scenario[] scenarios
};

set document = FEATURE;

token pipe = "|";
token colon = ":";

production SIMPLETERM
{
    given termtext                    -> scenario_term { location = @$, text = $2, type = scenario_term_type.given };
    when termtext                     -> scenario_term { location = @$, text = $2, type = scenario_term_type.when };
    then termtext                     -> scenario_term { location = @$, text = $2, type = scenario_term_type.then };
    and termtext                      -> scneario_term { location = @$, text = $2, type = scenario_term_type.and };
};

production TABLECOLS
{
    "|" "|"                           -> [ "" ];
    "|" name "|"                      -> [ $2 ];
    TABLECOLS name "|"                -> $1 |> append $2;
    TABLECOLS "|"                     -> $1 |> append "";
    "|" name error                    -> [ $2 ]
                                            |> error $3 "Missing '|'";
    TABLECOLS name error              -> $1 |> append $2
                                            |> error $3 "Missing '|'";
};

production TABLEROWS
{
    TABLECOLS nl                      -> [ $1 ];
    TABLEROWS TABLECOLS nl            -> $1 |> append $2;
};

production SCENARIOTERM
{
    SIMPLETERM                        -> $1;
    SIMPLETERM multilinetext          -> $1 |> mapWith multilinetext $2;
    SIMPLETERM TABLEROWS              -> $1 |> mapWith table $2;
};

production SCENARIOTERMS
{
    SCENARIOTERM                      -> [ $1 ];
    SCENARIOTERMS SCENARIOTERM        -> $1 |> append $2;
};

production SCENARIO
{
    scenario ":" name SCENARIOTERMS   -> scenario { is_background = false, is_outline = false, name_location = @3, name = $3, terms = $4 };
    background ":" SCENARIOTERMS      -> scenario { is_background = true, is_outline = false, terms = $4 };
    scenario outline ":" SCENARIOTERMS examples ":" TABLEROWS
                                      -> scenario { is_background = false, is_outline = true, terms = $4, examples = $5 };
};

production SCENARIOS
{
    SCENARIO                          -> [ $1 ];
    SCENARIOS SCENARIO                -> $1 |> append $1;
};

production FEATURE
{
    feature ":" name SCENARIOS        -> feature { name_location = @3, name = $3, scenarios = $4 };
};

--------------------------------------------------------------------------------------------------------------