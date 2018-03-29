%{
    /* c Declarations */
    #include <stdio.h>
    #include <string.h>
    int yylex();
    void yyerror (char* s);
    // char* label;
    // char countStr[4];
    // int labelCount = 0;
    // char* get_label()
    // {
    //     sprintf(countStr, "%03d", labelCount);
    //     strcpy(label, "LABEL");
    //     strcat(label, countStr);
    //     return label;
    // }

    #define YYSTYPE char*
    extern char * yytext;
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

program             : T_PROGRAM declarations T_BEGIN statementSequence T_END
                    ;
declarations        : T_VAR primary T_COLON type T_SC declarations
                    |
                    ;
type                : T_INT
                    ;
statementSequence   : statement T_SC statementSequence
                    |
                    ;
statement           : assignment
                    | ifStatement
                    | whileStatement
                    | writeInt
                    |
                    ;
assignment          : primary T_ASGN expression {
                                                    printf("STO\n");
                                                }
                    | primary T_ASGN T_READINT  {
                                                    printf("READ\n");
                                                    printf("STO\n");
                                                }
                    ;
ifStatement         : T_IF expression T_THEN statementSequence elseClause T_ENDIF   {
                                                                                        // get_label();
                                                                                        printf("GOFALSE %s\n", "label");
                                                                                        printf("--- stmt sqns ---\n");
                                                                                        printf("--- end ---\n");
                                                                                        printf("LABEL %s\n", "label");
                                                                                    }
                    ;
elseClause          : T_ELSE statementSequence {printf("elseClause\n");}
                    |
                    ;
whileStatement      : T_WHILE expression T_LOOP statementSequence T_ENDWHILE    {
                                                                                    // char* loopLabel = get_label();
                                                                                    // char* skipLabel = get_label();
                                                                                    printf("LABEL %s\n", "loopLabel");
                                                                                    printf("GOFALSE %s\n", "skipLabel");
                                                                                    printf("--- stmt sqns ---\n");
                                                                                    printf("LABEL %s\n", "skipLabel");
                                                                                }
                    ;
writeInt            : T_WRITEINT expression {
                                                printf("PRINT\n");
                                            }
                    ;
expression          : simpleExpression
                    | simpleExpression T_EQ expression  {
                                                            printf("EQ\n");
                                                        }
                    | simpleExpression T_NE expression  {
                                                            printf("NE\n");
                                                        }
                    | simpleExpression T_LT expression  {
                                                            printf("LT\n");
                                                        }
                    | simpleExpression T_GT expression  {
                                                            printf("GTLT\n");
                                                        }
                    | simpleExpression T_LE expression  {
                                                            printf("LE\n");
                                                        }
                    | simpleExpression T_GE expression  {
                                                            printf("GE\n");
                                                        }
                    ;
simpleExpression    : term T_ADD simpleExpression  {
                                                        printf("ADD\n");
                                                    }
                    | term T_SUB simpleExpression   {
                                                        printf("SUB\n");
                                                    }
                    | term
                    ;
term                : factor T_MULT term    {
                                                printf("MPY\n");
                                            }
                    | factor T_DIV term {
                                            printf("DIV\n");
                                        }
                    | factor T_MOD term {
                                            printf("MOD\n");
                                        }
                    | factor
                    ;
factor              : primary T_POWER factor    {
                                                    printf("POW\n");
                                                }
                    | primary
                    ;
primary             : T_IDENT {printf("LVALUE %s\n", yytext);}
                    | T_NUM {printf("PUSH %s\n", yytext);}
                    | T_LP expression T_RP
                    ;

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