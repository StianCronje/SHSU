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
    T_POWER = 264,
    T_EQ = 265,
    T_NE = 266,
    T_LT = 267,
    T_GT = 268,
    T_LE = 269,
    T_GE = 270,
    T_IF = 271,
    T_THEN = 272,
    T_ELSE = 273,
    T_BEGIN = 274,
    T_END = 275,
    T_ENDIF = 276,
    T_ENDWHILE = 277,
    T_WHILE = 278,
    T_LOOP = 279,
    T_PROGRAM = 280,
    T_VAR = 281,
    T_INT = 282,
    T_WRITEINT = 283,
    T_READINT = 284,
    T_ASGN = 285,
    T_ADD = 286,
    T_SUB = 287,
    T_MULT = 288,
    T_DIV = 289,
    T_MOD = 290
  };
#endif
/* Tokens.  */
#define T_NUM 258
#define T_IDENT 259
#define T_LP 260
#define T_RP 261
#define T_SC 262
#define T_COLON 263
#define T_POWER 264
#define T_EQ 265
#define T_NE 266
#define T_LT 267
#define T_GT 268
#define T_LE 269
#define T_GE 270
#define T_IF 271
#define T_THEN 272
#define T_ELSE 273
#define T_BEGIN 274
#define T_END 275
#define T_ENDIF 276
#define T_ENDWHILE 277
#define T_WHILE 278
#define T_LOOP 279
#define T_PROGRAM 280
#define T_VAR 281
#define T_INT 282
#define T_WRITEINT 283
#define T_READINT 284
#define T_ASGN 285
#define T_ADD 286
#define T_SUB 287
#define T_MULT 288
#define T_DIV 289
#define T_MOD 290

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
