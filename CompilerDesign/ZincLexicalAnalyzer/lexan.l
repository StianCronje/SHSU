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

    #define I_NUM            1
    #define I_IDENT          2
    #define I_LP             3
    #define I_RP             4
    #define I_ASGN           5
    #define I_SC             6
    #define I_COLON          7
    #define I_POWER          8
    #define I_MULTIPLICATIVE 9
    #define I_ADDITIVE       10
    #define I_COMPARE        11
    #define I_IF             12
    #define I_THEN           13
    #define I_ELSE           14
    #define I_BEGIN          15
    #define I_END            16
    #define I_ENDIF          17
    #define I_ENDWHILE       18
    #define I_WHILE          19
    #define I_LOOP           20
    #define I_PROGRAM        21
    #define I_VAR            22
    #define I_INT            23
    #define I_WRITEINT       24
    #define I_READINT        25

    char *lexeme;
    char token[12];

    typedef struct
    {
        char lexeme[12];
        char type[12];
        int address;
    } Symbol;

    Symbol symbolTable[100];
    int symCount = 0;
    int lineNum = 0;

    void insert_into_sym_tab(char *_lex, char * _typ, int _addr)
    {
        for(int i = 0; i < symCount; i++){
            if(strcmp(symbolTable[i].lexeme, _lex) == 0){
                //strcpy(_typ, "CODE");
                return;
            }
        }

        strcpy(symbolTable[symCount].lexeme, _lex);
        strcpy(symbolTable[symCount].type, _typ);
        // symbolTable[symCount].type = _typ;
        symbolTable[symCount].address = _addr;
        symCount++;
    }
    void print_symbol_table()
    {
        fprintf(stderr, "%-15s%-15s%-12s\n", "Lexeme", "Type", "Address");
        for (int i = 0; i < symCount; i++)
        {
            fprintf(stderr, "%-15s%-15s%-12d\n", symbolTable[i].lexeme, symbolTable[i].type, symbolTable[i].address);
        }
    }
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
WHITESPACE          [ \t]
NEWLINE             [\n]

%%

{PROGRAM}           {lexeme = yytext; sprintf(token, "PROGRAM"); return I_PROGRAM;}
{BEGIN}             {lexeme = yytext; sprintf(token, "BEGIN"); return I_BEGIN;}
{NUM}               {lexeme = yytext; sprintf(token, "NUM"); return I_NUM;}
{IDENT}             {lexeme = yytext; sprintf(token, "IDENT"); return I_IDENT;}
{LP}                {lexeme = yytext; sprintf(token, "LP"); return I_LP;}
{RP}                {lexeme = yytext; sprintf(token, "RP"); return I_RP;}
{ASGN}              {lexeme = yytext; sprintf(token, "ASGN"); return I_ASGN;}
{SC}                {lexeme = yytext; sprintf(token, "SC"); return I_SC;}
{COLON}             {lexeme = yytext; sprintf(token, "COLON"); return I_COLON;}
{POWER}             {lexeme = yytext; sprintf(token, "POWER"); return I_POWER;}
{MULTIPLICATIVE}    {lexeme = yytext; sprintf(token, "MULTIPLICATIVE"); return I_MULTIPLICATIVE;}
{ADDITIVE}          {lexeme = yytext; sprintf(token, "ADDITIVE"); return I_ADDITIVE;}
{COMPARE}           {lexeme = yytext; sprintf(token, "COMPARE"); return I_COMPARE;}

{IF}                {lexeme = yytext; sprintf(token, "IF"); return I_IF;}
{THEN}              {lexeme = yytext; sprintf(token, "THEN"); return I_THEN;}
{ELSE}              {lexeme = yytext; sprintf(token, "ELSE"); return I_ELSE;}
{ENDIF}             {lexeme = yytext; sprintf(token, "ENDIF"); return I_ENDIF;}
{WHILE}             {lexeme = yytext; sprintf(token, "WHILE"); return I_WHILE;}
{ENDWHILE}          {lexeme = yytext; sprintf(token, "ENDWHILE"); return I_ENDWHILE;}
{LOOP}              {lexeme = yytext; sprintf(token, "LOOP"); return I_LOOP;}
{VAR}               {lexeme = yytext; sprintf(token, "VAR"); return I_VAR;}
{INT}               {lexeme = yytext; sprintf(token, "INT"); return I_INT;}
{END}               {lexeme = yytext; sprintf(token, "END"); return I_END;}

{WRITEINT}          {lexeme = yytext; sprintf(token, "WRITEINT"); return I_WRITEINT;}
{READINT}           {lexeme = yytext; sprintf(token, "READINT"); return I_READINT;}

{COMMENT}           ; //printf("[COMMENT] %s\n", yytext);
{WHITESPACE}        ; // Ignore whitespace.
{NEWLINE}           {++lineNum;}
.                   {printf("INVALID TOKEN: %s\n", yytext);}

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

    int tokenType;

    while((tokenType = yylex()) != 0)
    {
        printf("<\"%s\", %s>\n", lexeme, token);

        if(tokenType == 2)
            insert_into_sym_tab(lexeme, token, lineNum);
    }

    print_symbol_table();

    return 0;
}