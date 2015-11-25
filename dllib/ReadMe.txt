Dave Lexer
----------


-------------------------------------------------------------------------------------------------------------------------------
Lexer File (*.dl)
-------------------------------------------------------------------------------------------------------------------------------
import "ds.dlh"; // We can import patterns, shared sections and script components from other sources

// Numbers
pattern positivedigit           = '[1-9]';
pattern digit                   = '[0-9]';
pattern integer                 = '{positivedigit}{digit}*';
pattern float                   = '{integer}\.{digit}+';

// Strings
pattern cr                      = '(\\r)';
pattern nl                      = '(\\n)';
pattern otherctrl               = '\\[^nr]';
pattern controls                = '{cr}|{nl}|{otherctrl}';
pattern string                  = '"([^\\]|{controls})*"';

// Inline script will be evaluated and the output will form part of the compile like any other text, this means you can output more script!
range "a" "d"
    |> map
        <"
        pattern <# id #> = <# id #>;
        ">;

external function state append(char ch, mstr s, int state);

let escape = transform(tochars)
{
    case 0:
        ch => when ch = '"' then 1
              else failwith "invalid";
    case 1:
        ch => when ch = '\\' then 2
              else 1 |> append ch;
    case 2:
        ch => 1 |>
                when ch = 'n' then append '\n'
                when ch = 'r' then append '\r'
                else append ch;
};

external function int atoi(string s); // Implemented in each language
external function double atof(string s);

enum class brace_side {
    start,
    end
};
enum class brace_type {
    braces,
    parenthesis,
    comment
};
class brace_tag { 
    brace_side side,
    brace_type bt 
};

shared section base_section {
    token number            = {integer} -> atoi $;
    token number            = {float}   -> atof $;
    token string            = {string}  -> escape $;
    token comment goto comment = /\*    -> $ 
                                           |> tag(brace_tag { side = brace_side.start, bt = brace_type.comment }), @);
};

section default {
    include base_section;
    token grammar goto grammar = '';
};

section comment {
    token comment           = .*;
    end comment             = \*/       -> $ |> tag(brace_tag { side = brace_side.end, bt = brace_type.comment }), @);
};

section grammar {
    include base_section;
    end grammar             = '';
};

===============================================================================================================================
The regular expression language
-------------------------------------------------------------------------------------------------------------------------------

Grammar
-------------------------------------------------------------------------------------------------------------------------------
A character matches itself
    'a' matches 'a'
    Characters can be escaped:
    '\\' matches the '\' character
    '\n' matches the newline character
    '\+' matches the '+' character
The following character classes are defined:
    '\a' matches any single lowercase alpha character (a-z)
    '\A' matches any single uppercase alpha character (A-Z)
    '\w' = '\a|\A'
    '\d' matches any single digit (0-9)
    '\s' matches any whitespace (' ', '\t', '\v', '\f')
    '.' matches any single character
Character Ranges are specified in [] brackets. Ranges are inclusive (i.e.; '[a-z]' will match 'a').
    '[abc]' matches a single character any of a, b or c
    '[a-z]' matches a single character in the range a-z
    '[a-zA-Z]' matches a single character in both ranges a-z and A-Z
    '[-a]' matches both the '-' and 'a' character (This is how you include '-' in the range)
    Ranges can be inverted (i.e.: match any character NOT in the range specified). They are also inclusive, i.e.: '[^a-z]' will not match 'a'
    '[^a-z]' matches any character not a-z
    Ranges can also include character classes
    '[\d\a]' matches all digits and alpha characters
    but they come into power with the inverted sets, i.e.:
    '[^\d]' matches all non-digits.
Whitespace
    All whitespace will be matched as characters
Scoping and precedence
    Use '(' and ')' to make precedence explicit. Any regular expression can be surrounded by (). For instance:
    'ab*' will match 'a', then any number of 'b', i.e.: 'abbbbbb'
    '(ab)*' will match any number of 'ab' pairs, i.e.: 'abababab'
Match options
    An option can be specified using the | character. For instance
    'a|b' will match either 'a' or 'b'
Cardinality
    The number of times a match must occur can be specified using one of the cardinality operators
    ?: 0..1
        'ab?' will match one a, then zero or one b. 'a' will be matched, 'ab' will be matched, 'abb' will not be matched.
    *: 0..n
        'ab*' will match one a, then any number (including zero) of b. 'a' will be matched, 'ab' will be matched, 'abb' will also be matched.
    +: 1..n
        'ab+' will match one a, then one or more b. 'a' will not be matched, and both 'ab' and 'abb' will be matched.
    {x}: x..x
        'ab{2}' will match one a, then exactly two b's. Both 'a' and 'ab' will not be matched, and 'abb' will be matched.
    {x,y}: x..y
        'ab{2,6}' will match one a, then a minimum of two and maximum of 6 b's.
Output
    The regular expression will output all matched characters, unless overriden using the output operator.
    To override the output, use the {>...} operator. An empty output '{>}' will remove any output. The
    length of the output can be anything and is unrelated to the length of the matched text.
    For instance:
    matching 'abc' with 'abc' will output 'abc'.
    matching 'abc' with '...' will output 'abc'.
    matching 'abc' with '.*{>}' will output nothing.
    matching 'abc' with '.*{>This is my output}' will output 'This is my output'.
    matching 'abc' with '.{>A}*' will output 'AAA'.

Terminals:
    c: char
    s: char set (\w, \s, \a, \A, etc)
    n: name
    -
    [
    ]
    @: [^
    (
    )
    |
    o: output {abc}
    d: cardinal
    $

1.  R -> c
2.  R -> s
3.  R -> n
4.  R -> -
5.  R -> [S]
6.  R -> @S]
7.  R -> (R)
8.  R -> RR
9.  R -> R|R
10. R -> Ro
11. R -> Rd
12. T -> -
13. T -> c
14. T -> c-c
15. S -> T
16. S -> ST

===============================================================================================================================
-------------------------------------------------------------------------------------------------------------------------------
Parser Tables
-------------------------------------------------------------------------------------------------------------------------------
State 0
-------
0.  S' -> .R$       G1

1.  R -> .c         s1
2.  R -> .s         s2
3.  R -> .n         s3
4.  R -> .-         s4
5.  R -> .[S]       S3
6.  R -> .@S]       S5
7.  R -> .(R)       S7
8.  R -> .RR        G1
9.  R -> .R|R       G1
10. R -> .Ro        G1
11. R -> .Rd        G1

State 1 (0 R)
-------------
0.  S' -> R.$       s0
8.  R -> R.R        G2
9.  R -> R.|R       S9
10. R -> R.o        s10
11. R -> R.d        s11

1.  R -> .c         s1
2.  R -> .s         s2
3.  R -> .n         s3
4.  R -> .-         s4
5.  R -> .[S]       S3
6.  R -> .@S]       S5
7.  R -> .(R)       S7
8.  R -> .RR        G2
9.  R -> .R|R       G2
10. R -> .Ro        G2
11. R -> .Rd        G2

State 2 (1,2 R)
---------------
8.  R -> RR.        R8
8.  R -> R.R        G2
9.  R -> R.|R       S9
10. R -> R.o        s10
11. R -> R.d        s11

1.  R -> .c         s1
2.  R -> .s         s2
3.  R -> .n         s3
4.  R -> .-         s4
5.  R -> .[S]       S3
6.  R -> .@S]       S5
7.  R -> .(R)       S7
8.  R -> .RR        G2
9.  R -> .R|R       G2
10. R -> .Ro        G2
11. R -> .Rd        G2

CONFLICT:
    RR.|    abc|e    = ab(c|e)      Shift
    RR.o    abc{>x}  = ab(c{>x})    Shift
    RR.d    abc{3}   = ab(c{3})     Shift
    RR.c    abce     = (abc)e       Reduce
    RR.s    abc\w    = (abc)\w      Reduce
    RR.n    abc{xyz} = (abc){xyz}   Reduce
    RR.-    abc-     = (abc)-       Reduce
    RR.[    abc[x]   = (abc)[x]     Reduce
    RR.@    abc[^x]  = (abc)[^x]    Reduce
    RR.(    abc(xyz) = (abc)(xyz)   Reduce

State 3 (0 [)
-------------
5.  R -> [.S]       G4

15. S -> .T         r15
16. S -> .ST        G4
12. T -> .-         s12
13. T -> .c         S11
14. T -> .c-c       S11

State 4 (3 S)
-------------
5.  R -> [S.]       s5
16. S -> S.T        r16

12. T -> .-         s12
13. T -> .c         S11
14. T -> .c-c       S11

State 5 (0 @)
-------------
6.  R -> @.S]       G6

15. S -> .T         r15
16. S -> .ST        G6
12. T -> .-         s12
13. T -> .c         S11
14. T -> .c-c       S11

State 6 (5 S)
-------------
6.  R -> @S.]       s6
16. S -> S.T        r16

12. T -> .-         s12
13. T -> .c         S11
14. T -> .c-c       S11

State 7 (0 ()
-------------
7.  R -> (.R)       G8

1.  R -> .c         s1
2.  R -> .s         s2
3.  R -> .n         s3
4.  R -> .-         s4
5.  R -> .[S]       S3
6.  R -> .@S]       S5
7.  R -> .(R)       S7
8.  R -> .RR        G8
9.  R -> .R|R       G8
10. R -> .Ro        G8
11. R -> .Rd        G8

State 8 (7 R)
-------------
7.  R -> (R.)       s7
8.  R -> R.R        G2
9.  R -> R.|R       S9
10. R -> R.o        s10
11. R -> R.d        s11

1.  R -> .c         s1
2.  R -> .s         s2
3.  R -> .n         s3
4.  R -> .-         s4
5.  R -> .[S]       S3
6.  R -> .@S]       S5
7.  R -> .(R)       S7
8.  R -> .RR        G2
9.  R -> .R|R       G2
10. R -> .Ro        G2
11. R -> .Rd        G2

State 9 (1 |)
-------------
9.  R -> R|.R       G10

1.  R -> .c         s1
2.  R -> .s         s2
3.  R -> .n         s3
4.  R -> .-         s4
5.  R -> .[S]       S3
6.  R -> .@S]       S5
7.  R -> .(R)       S7
8.  R -> .RR        G10
9.  R -> .R|R       G10
10. R -> .Ro        G10
11. R -> .Rd        G10

State 10 (9 R)
--------------
9.  R -> R|R.       R9
8.  R -> R.R        G2
9.  R -> R.|R       S9
10. R -> R.o        s10
11. R -> R.d        s11

1.  R -> .c         s1
2.  R -> .s         s2
3.  R -> .n         s3
4.  R -> .-         s4
5.  R -> .[S]       S3
6.  R -> .@S]       S5
7.  R -> .(R)       S7
8.  R -> .RR        G2
9.  R -> .R|R       G2
10. R -> .Ro        G2
11. R -> .Rd        G2

CONFLICT:
    R|R.|    a|c|e    = (a|c)e       Reduce
    R|R.o    a|c{>x}  = a|(c{>x})    Shift
    R|R.d    a|c{3}   = a|(c{3})     Shift
    R|R.c    a|ce     = (a|c)e       Reduce
    R|R.s    a|c\w    = (a|c)\w      Reduce
    R|R.n    a|c{xyz} = (a|c){xyz}   Reduce
    R|R.-    a|c-     = (a|c)-       Reduce
    R|R.[    a|c[x]   = (a|c)[x]     Reduce
    R|R.@    a|c[^x]  = (a|c)[^x]    Reduce
    R|R.(    a|c(xyz) = (a|c)(xyz)   Reduce

State 11 (X c)
--------------
13. T -> c.         R13
14. T -> c.-c       S12

CONFLICT:
    c.]     a]   = (a)]      Reduce
    c.-     a-bc = (a-b)c    Shift

State 12 (11 -)
---------------
14. T -> c-.c       s14

Tables
======

Terminals:
    c: char
    s: char set
    n: name
    -
    [
    ]
    @: [^
    (
    )
    |
    o: output {abc}
    d: cardinal
    $

Non-terminals:
    S', R, T, S

Actions:
    Sx:  Shift x
    sx:  Shift any then Rx
    Rx:  Reduce by rule x
    rx:  Goto any then Rx
    Gx:  Goto x

    c   s   n   -   [   ]   @   (   )   |   o   d   $   S'  R   T   S
------------------------------------------------------------------------
0   s1  s2  s3  s4  S3      S5  S7                          G1
1   s1  s2  s3  s4  S3      S5  S7      S9  s10 s11 s0      G2
2   R8  R8  R8  R8  R8      R8  R8  R8  S9  s10 s11 R8      G2
3   S11         s12                                             r15 G4
4   S11         s12     s5                                      r16
5   S11         s12                                             r15 G6
6   S11         s12     s6                                      r16
7   s1  s2  s3  s4  S3      S5  S7                          G8
8   s1  s2  s3  s4  S3      S5  S7  s7  S9  s10 s11         G2
9   s1  s2  s3  s4  S3      S5  S7                          G10
10  R9  R9  R9  R9  R9      R9  R9  R9  R9  s10 s11 R9      G2
11  R13         S12     R13
12  s14

0.  S' -> R$
1.  R -> c
2.  R -> s
3.  R -> n
4.  R -> -
5.  R -> [S]
6.  R -> @S]
7.  R -> (R)
8.  R -> RR
9.  R -> R|R
10. R -> Ro
11. R -> Rd
12. T -> -
13. T -> c
14. T -> c-c
15. S -> T
16. S -> ST

===============================================================================================================================
Non-lexer regular expressions
In some cases, we want to be able to use a regular expression to match groups (extract parts of a text).
===============================================================================================================================
