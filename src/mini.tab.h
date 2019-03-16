/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Skeleton interface for Bison GLR parsers in C

   Copyright (C) 2002-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_MINI_TAB_H_INCLUDED
# define YY_YY_MINI_TAB_H_INCLUDED
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
    tRUNEVAL = 258,
    tSTRINGITPVAL = 259,
    tSTRINGRAWVAL = 260,
    tINTVAL = 261,
    tFLOATVAL = 262,
    tIDENTIFIER = 263,
    tVAR = 264,
    tIF = 265,
    tELSE = 266,
    tPRINT = 267,
    tCOLON = 268,
    tASSIGN = 269,
    tSEMICOLON = 270,
    tLEFTPAREN = 271,
    tRIGHTPAREN = 272,
    tLEFTBRACE = 273,
    tRIGHTBRACE = 274,
    tBANG = 275,
    tPLUS = 276,
    tMINUS = 277,
    tTIMES = 278,
    tDIV = 279,
    tEQUALS = 280,
    tNOTEQUALS = 281,
    tGREATEREQUALS = 282,
    tLESSEQUALS = 283,
    tGREATER = 284,
    tLESS = 285,
    tAND = 286,
    tOR = 287,
    tSTRUCT = 288,
    tSELECT = 289,
    tRETURN = 290,
    tRANGE = 291,
    tPACKAGE = 292,
    tMAP = 293,
    tINTERFACE = 294,
    tIMPORT = 295,
    tGOTO = 296,
    tGO = 297,
    tFOR = 298,
    tDEFER = 299,
    tDEFAULT = 300,
    tCONTINUE = 301,
    tCONST = 302,
    tCHAN = 303,
    tCASE = 304,
    tBREAK = 305,
    tFALLTHROUGH = 306,
    tSWITCH = 307,
    tTYPE = 308,
    tPRINTLN = 309,
    tAPPEND = 310,
    tLEN = 311,
    tCAP = 312,
    tMOD = 313,
    tBITWISEAND = 314,
    tBITWISEOR = 315,
    tBITWISEXOR = 316,
    tBITCLEAR = 317,
    tLEFTSHIFT = 318,
    tRIGHTSHIFT = 319,
    tPLUSEQUAL = 320,
    tMINUSEQUAL = 321,
    tTIMESEQUAL = 322,
    tDIVEQUAL = 323,
    tMODEQUAL = 324,
    tPLUSPLUS = 325,
    tMINUSMINUS = 326,
    tANDEQUAL = 327,
    tOREQUAL = 328,
    tXOREQUAL = 329,
    tLEFTSHIFTEQUAL = 330,
    tRIGHTSHIFTEQUAL = 331,
    tBITCLEAREQUAL = 332,
    tCOLONEQUAL = 333,
    tDOTDOTDOT = 334,
    tCOMMA = 335,
    tDOT = 336,
    tLEFTSQUAREBRACKET = 337,
    tRIGHTSQUAREBRACKET = 338,
    tFUNC = 339,
    UBANG = 340,
    UMINUS = 341,
    UPLUS = 342,
    UCARET = 343,
    UBITWISEAND = 344
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 16 "mini.y" /* glr.c:197  */

    int intval;
    struct TYPE *type;
    char *runeval;
    char *id;
    char *stringval;
    float floatval;
    struct EXP *EXP;
    struct STMT *STMT;
    struct PROGRAM *PROGRAM;
    struct TYPE *TYPE;
    struct FIELD_DCL *FIELD_DCL;
    struct ID_LIST *ID_LIST;
    struct VARDECL *VARDECL;
    struct PARAMS *PARAMS;
    struct RESULT *RESULT;
    struct SIGNATURE *SIGNATURE;
    struct FUNCDECL *FUNCDECL;
    struct VARSPEC *VARSPEC;
    struct IMPORT *IMPORT;
    struct PACKAGE *PACKAGE;
    struct TOPDECL *TOPDECL;
    struct TYPEDECL *TYPEDECL;
    struct CASE_CLAUSE *CASE_CLAUSE;
    struct TYPESPEC *TYPESPEC;
    struct FOR_CLAUSE *FOR_CLAUSE;
    struct DCL *DCL;

#line 173 "mini.tab.h" /* glr.c:197  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_MINI_TAB_H_INCLUDED  */
