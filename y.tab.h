/* A Bison parser, made by GNU Bison 3.0.  */

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
    PLUS = 258,
    MINUS = 259,
    TIMES = 260,
    OVER = 261,
    LT = 262,
    LTEQ = 263,
    GT = 264,
    GTEQ = 265,
    EQ = 266,
    NEQ = 267,
    ASSIGN = 268,
    SEMI = 269,
    COMMA = 270,
    LPAREN = 271,
    RPAREN = 272,
    LBRACK = 273,
    RBRACK = 274,
    LBRACE = 275,
    RBRACE = 276,
    NUM = 277,
    ID = 278,
    ARRAY = 279,
    ERROR = 280,
    ELSE = 281,
    IF = 282,
    INT = 283,
    RETURN = 284,
    VOID = 285,
    WHILE = 286,
    OUTPUT = 287,
    INPUT = 288,
    MUL = 289,
    POW = 290,
    NEG = 291
  };
#endif
/* Tokens.  */
#define PLUS 258
#define MINUS 259
#define TIMES 260
#define OVER 261
#define LT 262
#define LTEQ 263
#define GT 264
#define GTEQ 265
#define EQ 266
#define NEQ 267
#define ASSIGN 268
#define SEMI 269
#define COMMA 270
#define LPAREN 271
#define RPAREN 272
#define LBRACK 273
#define RBRACK 274
#define LBRACE 275
#define RBRACE 276
#define NUM 277
#define ID 278
#define ARRAY 279
#define ERROR 280
#define ELSE 281
#define IF 282
#define INT 283
#define RETURN 284
#define VOID 285
#define WHILE 286
#define OUTPUT 287
#define INPUT 288
#define MUL 289
#define POW 290
#define NEG 291

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
