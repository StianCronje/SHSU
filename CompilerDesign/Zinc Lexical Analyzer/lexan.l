%{
    /*
    Rules of Zinc are as follows:

    Numbers, Literals, and Identifiers:
    •	num = (+|-)?[1-9][0-9]*|0
    •	ident = [A-Z][_A-Z0-9]*
    Symbols and Operators:
    •	LP "("
    •	RP ")"
    •	ASGN ":="
    •	SC ";"
    •	COLON ":"
    •	POWER "**"
    •	MULTIPLICATIVE "*" | "div" | "mod"
    •	ADDITIVE "+" | "-"
    •	COMPARE "=" | "<>" | "<" | ">" | "<=" | ">="
    Keywords:
    •	IF "if"
    •	THEN "then"
    •	ELSE "else"
    •	BEGIN "begin"
    •	END "end"
    •	ENDIF "endif"
    •	ENDWHILE "endwhile"
    •	WHILE "while"
    •	LOOP "loop"
    •	PROGRAM "program"
    •	VAR "var"
    •	INT "integer"
    Built-in Procedures:
    •	WRITEINT "writeInt"
    •	READINT "readInt"
    */

    #include <stdio.h>
%}

%option noyywrap

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
MULTIPLICATIVE      "*"|"div"|"mod"
ADDITIVE            "+"|"-"
COMPARE             "="|"<>"|"<"|">"|"<="|">="
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
WHITESPACE          [ \t\n]

%%

{PROGRAM}           printf("<\"%s\", PROGRAM>\n", yytext);
{BEGIN}             printf("<\"%s\", BEGIN>\n", yytext);
{NUM}               printf("<\"%s\", NUM>\n", yytext);
{IDENT}             printf("<\"%s\", IDENT>\n", yytext);
{LP}                printf("<\"%s\", LP>\n", yytext);
{RP}                printf("<\"%s\", RP>\n", yytext);
{ASGN}              printf("<\"%s\", ASGN>\n", yytext);    
{SC}                printf("<\"%s\", SC>\n", yytext);
{COLON}             printf("<\"%s\", COLON>\n", yytext);
{POWER}             printf("<\"%s\", POWER>\n", yytext);
{MULTIPLICATIVE}    printf("<\"%s\", MULTIPLICATIVE>\n", yytext);
{ADDITIVE}          printf("<\"%s\", ADDITIVE>\n", yytext);
{COMPARE}           printf("<\"%s\", COMPARE>\n", yytext);

{IF}                printf("<\"%s\", IF>\n", yytext);
{THEN}              printf("<\"%s\", THEN>\n", yytext);
{ELSE}              printf("<\"%s\", ELSE>\n", yytext);
{ENDIF}             printf("<\"%s\", ENDIF>\n", yytext);
{WHILE}             printf("<\"%s\", WHILE>\n", yytext);
{ENDWHILE}          printf("<\"%s\", ENDWHILE>\n", yytext);
{LOOP}              printf("<\"%s\", LOOP>\n", yytext);
{VAR}               printf("<\"%s\", VAR>\n", yytext);
{INT}               printf("<\"%s\", INT>\n", yytext);
{END}               printf("<\"%s\", END>\n", yytext);

{WRITEINT}          printf("<\"%s\", WRITEINT>\n", yytext);
{READINT}           printf("<\"%s\", READINT>\n", yytext);

{COMMENT}           ; //printf("[COMMENT] %s\n", yytext);
{WHITESPACE}        ; // Ignore whitespace.
.                   printf("INVALID TOKEN: %s\n", yytext);

%%

int main(int argc, char** argv)
{
    if ( argc > 0 )
    {
        yyin = fopen( argv[1], "r" );
    }
    else
    {
        yyin = stdin;
    }

    yylex();
    return 0;
}