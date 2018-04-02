%{
    /*
    Rules of Zinc are as follows:

    Numbers, Literals, and Identifiers:
        num = (+|-)?[1-9][0-9]*|0
        ident = [A-Z][_A-Z0-9]*
    Symbols and Operators:
        LP "("
        RP ")"
        ASGN ":="
        SC ";"
        COLON ":"
        POWER "**"
        MULTIPLICATIVE "*" | "div" | "mod"
        ADDITIVE "+" | "-"
        COMPARE "=" | "<>" | "<" | ">" | "<=" | ">="
    Keywords:
        IF "if"
        THEN "then"
        ELSE "else"
        BEGIN "begin"
        END "end"
        ENDIF "endif"
        ENDWHILE "endwhile"
        WHILE "while"
        LOOP "loop"
        PROGRAM "program"
        VAR "var"
        INT "integer"
    Built-in Procedures:
        WRITEINT "writeInt"
        READINT "readInt"
    */

    #include "y.tab.h"

%}

/* Numbers, Literals, and Identifiers */
NUM                 ("+"|"-")?[1-9][0-9]*|0
IDENT               [A-Z][_A-Z0-9]*
/* Symbols and Operators */
LP                  "("
RP                  ")"
ASGN                ":="
SC                  ";"
COLON               ":"
POWER               "**"
MULT                "*"
DIV                 "div"
MOD                 "mod"
ADD                 "+"
SUB                 "-"
EQ                  "="
NE                  "<>"
LT                  "<"
GT                  ">"
LE                  "<="
GE                  ">="
/* Keywords */
IF                  "if"
THEN                "then"
ELSE                "else"
BEGIN               "begin"
END                 "end"
ENDIF               "endif"
ENDWHILE            "endwhile"
WHILE               "while"
LOOP                "loop"
PROGRAM             "program"
VAR                 "var"
INT                 "integer"
/* Built-in Procedures */
WRITEINT            "writeInt"
READINT             "readInt"
COMMENT             "--".*
WHITESPACE          [ \t\n\r\f]

%%

{PROGRAM}           {/*printf("returning %-10s\n", yytext);*/ return T_PROGRAM;}
{BEGIN}             {/*printf("returning %-10s\n", yytext);*/ return T_BEGIN;}
{NUM}               {/*printf("returning %-10s\n", yytext);*/ return T_NUM;}
{IDENT}             {/*printf("returning %-10s\n", yytext);*/ return T_IDENT;}
{LP}                {/*printf("returning %-10s\n", yytext);*/ return T_LP;}
{RP}                {/*printf("returning %-10s\n", yytext);*/ return T_RP;}
{ASGN}              {/*printf("returning %-10s\n", yytext);*/ return T_ASGN;}
{SC}                {/*printf("returning %-10s\n", yytext);*/ return T_SC;}
{COLON}             {/*printf("returning %-10s\n", yytext);*/ return T_COLON;}
{POWER}             {/*printf("returning %-10s\n", yytext);*/ return T_POWER;}
{MULT}              {/*printf("returning %-10s\n", yytext);*/ return T_MULT;}
{DIV}               {/*printf("returning %-10s\n", yytext);*/ return T_DIV;}
{MOD}               {/*printf("returning %-10s\n", yytext);*/ return T_MOD;}
{ADD}               {/*printf("returning %-10s\n", yytext);*/ return T_ADD;}
{SUB}               {/*printf("returning %-10s\n", yytext);*/ return T_SUB;}
{EQ}                {/*printf("returning %-10s\n", yytext);*/ return T_EQ;}
{NE}                {/*printf("returning %-10s\n", yytext);*/ return T_NE;}
{LT}                {/*printf("returning %-10s\n", yytext);*/ return T_LT;}
{GT}                {/*printf("returning %-10s\n", yytext);*/ return T_GT;}
{LE}                {/*printf("returning %-10s\n", yytext);*/ return T_LE;}
{GE}                {/*printf("returning %-10s\n", yytext);*/ return T_GE;}
{IF}                {/*printf("returning %-10s\n", yytext);*/ return T_IF;}
{THEN}              {/*printf("returning %-10s\n", yytext);*/ return T_THEN;}
{ELSE}              {/*printf("returning %-10s\n", yytext);*/ return T_ELSE;}
{ENDIF}             {/*printf("returning %-10s\n", yytext);*/ return T_ENDIF;}
{WHILE}             {/*printf("returning %-10s\n", yytext);*/ return T_WHILE;}
{ENDWHILE}          {/*printf("returning %-10s\n", yytext);*/ return T_ENDWHILE;}
{LOOP}              {/*printf("returning %-10s\n", yytext);*/ return T_LOOP;}
{VAR}               {/*printf("returning %-10s\n", yytext);*/ return T_VAR;}
{INT}               {/*printf("returning %-10s\n", yytext);*/ return T_INT;}
{END}               {/*printf("returning %-10s\n", yytext);*/ return T_END;}
{WRITEINT}          {/*printf("returning %-10s\n", yytext);*/ return T_WRITEINT;}
{READINT}           {/*printf("returning %-10s\n", yytext);*/ return T_READINT;}

{COMMENT}           ; //printf("[COMMENT] %s\n", yytext);
{WHITESPACE}        ; // Ignore whitespace.
.                   {printf("INVALID TOKEN: %s\n", yytext);}

%%

int yywrap()
{
    return 1;
}