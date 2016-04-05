/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
    NEGATION = 258,
    PLUS = 259,
    MINUS = 260,
    TIMES = 261,
    DIV = 262,
    LTE = 263,
    GTE = 264,
    LT = 265,
    GT = 266,
    EQU = 267,
    ASSIGN = 268,
    SEMI = 269,
    COMMA = 270,
    COLON = 271,
    LP = 272,
    RP = 273,
    NUM = 274,
    IF = 275,
    THEN = 276,
    ELSE = 277,
    WHILE = 278,
    DO = 279,
    BEGIN1 = 280,
    END = 281,
    INT = 282,
    BOOL = 283,
    CHAR = 284,
    VOID = 285,
    TRUE = 286,
    FALSE = 287,
    CHARACTER = 288,
    CIN = 289,
    COUT = 290,
    ID = 291,
    LL = 292,
    GG = 293,
    RETURN = 294
  };
#endif
/* Tokens.  */
#define NEGATION 258
#define PLUS 259
#define MINUS 260
#define TIMES 261
#define DIV 262
#define LTE 263
#define GTE 264
#define LT 265
#define GT 266
#define EQU 267
#define ASSIGN 268
#define SEMI 269
#define COMMA 270
#define COLON 271
#define LP 272
#define RP 273
#define NUM 274
#define IF 275
#define THEN 276
#define ELSE 277
#define WHILE 278
#define DO 279
#define BEGIN1 280
#define END 281
#define INT 282
#define BOOL 283
#define CHAR 284
#define VOID 285
#define TRUE 286
#define FALSE 287
#define CHARACTER 288
#define CIN 289
#define COUT 290
#define ID 291
#define LL 292
#define GG 293
#define RETURN 294

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 34 "b.y" /* yacc.c:1909  */

    struct node *node1;

#line 136 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
