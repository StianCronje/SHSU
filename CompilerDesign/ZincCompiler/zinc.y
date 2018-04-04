%{
    /* c Declarations */
    #include <stdio.h>
    #include <string.h>
    int yylex();
    void yyerror (char* s);
    extern char * yytext;

    char trueLabel[10];
    char endLabel[10];

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
        return NULL;
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

%union{
    char id[12];
    int num;
}
%token T_NUM <id> T_IDENT 
%token T_LP T_RP T_SC T_COLON T_POWER T_EQ T_NE T_LT T_GT T_LE T_GE 
%token T_IF T_THEN T_ELSE T_BEGIN T_END T_ENDIF T_ENDWHILE T_WHILE T_LOOP T_PROGRAM T_VAR T_INT 
%token T_WRITEINT T_READINT 

%left T_ASGN 
%left T_ADD T_SUB 
%left T_MULT T_DIV T_MOD

%type <id> type


%%
/* productions */

program             : T_PROGRAM beginDeclarations T_BEGIN beginStatements T_END {printf("HALT\n");}
                    ;
beginDeclarations   :  { printf("Section .data\n"); } declarations
                    ;
declarations        : T_VAR T_IDENT T_COLON type T_SC declarations {printf("%s : %s\n", $2, $4);}
                    | /* empty */
                    | error T_IDENT T_COLON type T_SC declarations {printf("error in declarations : 'var' expected\n"); yyerrok;}
                    | T_VAR T_IDENT error type T_SC declarations {printf("error in declarations : ':' expected\n"); yyerrok;}
                    | T_VAR T_IDENT T_COLON type error declarations {printf("error in declarations : ';' expected\n"); yyerrok;}
                    ;
type                : T_INT { strcpy($$, "word"); }
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
assignment          : T_IDENT T_ASGN expression {
                                                    printf("LVALUE %s\n", $1);
                                                    printf("STO\n");
                                                }
                    | T_IDENT T_ASGN T_READINT  {
                                                    printf("LVALUE %s\n", $1);
                                                    printf("READ\n");
                                                    printf("STO\n");
                                                }
                    ;
ifStatement         : T_IF expression T_THEN
                                    {
                                        make_label(trueLabel);
                                        printf("GOFALSE %s\n", trueLabel);
                                    }
                        statementSequence elseClause T_ENDIF
                                    {
                                        get_label(endLabel);
                                        printf("LABEL %s\n", endLabel);
                                    }
                    ;
elseClause          : T_ELSE {
                                        get_label(trueLabel);
                                        make_label(endLabel);
                                        printf("GOTO %s\n", endLabel);                                        
                                        printf("LABEL %s\n", trueLabel);
                                    } statementSequence
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
term                : factor T_MULT term { printf("MPY\n"); }
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

%%
/* User subroutines */

int main()
{
    printf("\n\n\n");
    yyparse();
    return 0;
}

void yyerror (char* s)
{
    fprintf(stderr, "ERROR: %s\n", s);
}