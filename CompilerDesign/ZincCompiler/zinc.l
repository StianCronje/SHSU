%{
    #include "y.tab.h"
%}

%option yylineno

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
WHILE               "while"
ENDWHILE            "endwhile"
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

{PROGRAM}           { return T_PROGRAM; }
{BEGIN}             { return T_BEGIN; }
{NUM}               { yylval.num = atoi(yytext); return T_NUM; }
{IDENT}             { strcpy(yylval.str, yytext); return T_IDENT; }
{LP}                { return T_LP; }
{RP}                { return T_RP; }
{ASGN}              { return T_ASGN; }
{SC}                { return T_SC; }
{COLON}             { return T_COLON; }
{POWER}             { return T_POWER; }
{MULT}              { return T_MULT; }
{DIV}               { return T_DIV; }
{MOD}               { return T_MOD; }
{ADD}               { return T_ADD; }
{SUB}               { return T_SUB; }
{EQ}                { return T_EQ; }
{NE}                { return T_NE; }
{LT}                { return T_LT; }
{GT}                { return T_GT; }
{LE}                { return T_LE; }
{GE}                { return T_GE; }
{IF}                { return T_IF; }
{THEN}              { return T_THEN; }
{ELSE}              { return T_ELSE; }
{ENDIF}             { return T_ENDIF; }
{WHILE}             { return T_WHILE; }
{ENDWHILE}          { return T_ENDWHILE; }
{LOOP}              { return T_LOOP; }
{VAR}               { return T_VAR; }
{INT}               { return T_INT; }
{END}               { return T_END; }
{WRITEINT}          { return T_WRITEINT; }
{READINT}           { return T_READINT; }

{COMMENT}           ; //printf("[COMMENT] %s\n", yytext);
{WHITESPACE}        ; //Ignore whitespace.
.                   {printf("INVALID TOKEN: %s\n", yytext);}

%%

int yywrap()
{
    return 1;
}