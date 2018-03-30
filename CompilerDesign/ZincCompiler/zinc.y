%{
    /* c Declarations */
    #include <stdio.h>
    #include <string.h>
    int yylex();
    void yyerror (char* s);
    extern char * yytext;

    char labelStack[10][100];
    int stackPointer = 0;

    void push(char* l)
    {
        if(stackPointer < 99)
        {
            strcpy(labelStack[stackPointer], l);
            stackPointer++;
        }
    }
    char* pop()
    {
        if(stackPointer > 0)
        {
            stackPointer--;
            return labelStack[stackPointer];
        }
    }

    int declaring = 0;

    char countStr[4];
    int labelCount = 0;
    void make_label(char* label)
    {
        labelCount++;
        sprintf(label, "%s", "LABEL");
        sprintf(countStr, "%03d", labelCount);
        strcat(label, countStr);
        push(label);
    }
    void get_label(char* label)
    {
        strcpy(label, pop());
    }


    // RVALUE FLAG
    // GOTRUE TRUE
    // elseClause
    // GOTO ENDIF
    // LABEL TRUE
    // RVALUE X
    // PRINT
    // RVALUE Y
    // PRINT
    // LABEL ENDIF
%}

/* Definitions */
%token T_NUM T_IDENT 
%token T_LP T_RP T_SC T_COLON T_POWER T_EQ T_NE T_LT T_GT T_LE T_GE 
%token T_IF T_THEN T_ELSE T_BEGIN T_END T_ENDIF T_ENDWHILE T_WHILE T_LOOP T_PROGRAM T_VAR T_INT 
%token T_WRITEINT T_READINT 

%left T_ASGN 
%left T_ADD T_SUB 
%left T_MULT T_DIV T_MOD


%%
/* productions */

program             : T_PROGRAM beginDeclarations T_BEGIN beginStatements T_END {printf("HALT\n");}
                    ;
beginDeclarations   :  { printf("Section .data\n"); } declarations
                    ;
declarations        : T_VAR varId T_COLON type T_SC declarations
                    | /* empty */
                    ;
type                : T_INT { printf("word\n"); }
                    ;
beginStatements     :{ printf("Section .code\n"); } statementSequence
                    ;
statementSequence   : statement T_SC statementSequence
                    | /* empty */
                    ;
statement           : assignment
                    | ifStatement
                    | whileStatement
                    | writeInt
                    | /* empty */
                    ;
assignment          : ident T_ASGN expression { printf("STO\n"); }
                    | ident T_ASGN T_READINT    {
                                                    printf("READ\n");
                                                    printf("STO\n");
                                                }
                    ;
ifStatement         : T_IF expression T_THEN
                                    {  char skipLabel[10];
                                        make_label(skipLabel);
                                        printf("GOFALSE %s\n", skipLabel); }
                        statementSequence elseClause T_ENDIF
                                                    {   char skipLabel[10];
                                                        get_label(skipLabel);
                                                        printf("LABEL %s\n", skipLabel); }
                    ;
elseClause          : T_ELSE statementSequence {printf("elseClause\n");}
                    | /* empty */
                    ;
whileStatement      : T_WHILE expression T_LOOP
                                        {   char loopLabel[10];
                                            char skipLabel[10];
                                            make_label(loopLabel);
                                            make_label(skipLabel);
                                            printf("LABEL %s\n", loopLabel);
                                            printf("GOFALSE %s\n", skipLabel); }
                        statementSequence T_ENDWHILE
                                        {   char loopLabel[10];
                                            char skipLabel[10];
                                            get_label(skipLabel);
                                            get_label(loopLabel);
                                            printf("GOTO %s\n", loopLabel);
                                            printf("LABEL %s\n", skipLabel); }
                    ;
writeInt            : T_WRITEINT expression { printf("PRINT\n"); }
                    ;
expression          : simpleExpression
                    | simpleExpression T_EQ expression  { printf("EQ\n"); }
                    | simpleExpression T_NE expression  { printf("NE\n"); }
                    | simpleExpression T_LT expression  { printf("LT\n"); }
                    | simpleExpression T_GT expression  { printf("GTLT\n"); }
                    | simpleExpression T_LE expression  { printf("LE\n"); }
                    | simpleExpression T_GE expression  { printf("GE\n"); }
                    ;
simpleExpression    : term T_ADD simpleExpression  { printf("ADD\n"); }
                    | term T_SUB simpleExpression   { printf("SUB\n"); }
                    | term
                    ;
term                : factor T_MULT term    { printf("MPY\n"); }
                    | factor T_DIV term { printf("DIV\n"); }
                    | factor T_MOD term { printf("MOD\n"); }
                    | factor
                    ;
factor              : primary T_POWER factor    { printf("POW\n"); }
                    | primary
                    ;
primary             : T_NUM {printf("PUSH %s\n", yytext);}
                    | T_LP expression T_RP
                    | T_IDENT { printf("RVALUE %s\n", yytext);}
                    ;
ident               : T_IDENT {printf("LVALUE %s\n", yytext);}
                    ;
varId              : T_IDENT {printf("%s: ", yytext);}

%%
/* User subroutines */

int main()
{
    yyparse();
    return 0;
}

void yyerror (char* s)
{
    fprintf(stderr, "ERROR: %s\n", s);
}