/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_NUM = 258,
    T_IDENT = 259,
    T_LP = 260,
    T_RP = 261,
    T_SC = 262,
    T_COLON = 263,
    T_ASGN = 264,
    T_ADD = 265,
    T_SUB = 266,
    T_MULT = 267,
    T_DIV = 268,
    T_MOD = 269,
    T_POWER = 270,
    T_EQ = 271,
    T_NE = 272,
    T_LT = 273,
    T_GT = 274,
    T_LE = 275,
    T_GE = 276,
    T_IF = 277,
    T_THEN = 278,
    T_ELSE = 279,
    T_BEGIN = 280,
    T_END = 281,
    T_ENDIF = 282,
    T_ENDWHILE = 283,
    T_WHILE = 284,
    T_LOOP = 285,
    T_PROGRAM = 286,
    T_VAR = 287,
    T_INT = 288,
    T_WRITEINT = 289,
    T_READINT = 290
  };
#endif
/* Tokens.  */
#define T_NUM 258
#define T_IDENT 259
#define T_LP 260
#define T_RP 261
#define T_SC 262
#define T_COLON 263
#define T_ASGN 264
#define T_ADD 265
#define T_SUB 266
#define T_MULT 267
#define T_DIV 268
#define T_MOD 269
#define T_POWER 270
#define T_EQ 271
#define T_NE 272
#define T_LT 273
#define T_GT 274
#define T_LE 275
#define T_GE 276
#define T_IF 277
#define T_THEN 278
#define T_ELSE 279
#define T_BEGIN 280
#define T_END 281
#define T_ENDIF 282
#define T_ENDWHILE 283
#define T_WHILE 284
#define T_LOOP 285
#define T_PROGRAM 286
#define T_VAR 287
#define T_INT 288
#define T_WRITEINT 289
#define T_READINT 290

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 52 "zinc.y" /* yacc.c:1909  */

    char str[50];
    int num;

#line 129 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
