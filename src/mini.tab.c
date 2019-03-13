/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Skeleton implementation for Bison GLR parsers in C

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

/* C GLR parser skeleton written by Paul Hilfinger.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "glr.c"

/* Pure parsers.  */
#define YYPURE 0






/* First part of user declarations.  */
#line 1 "mini.y" /* glr.c:240  */

#include <stdio.h>
#include "main.h"
#include "tree.h"

extern PROGRAM *root;
extern int yylineno;
int yylex();
int yyerror(const char *s) { fprintf(stderr, "Error: (line %d) %s\n", yylineno, s); }

#line 65 "mini.tab.c" /* glr.c:240  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "mini.tab.h"

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Default (constant) value used for initialization for null
   right-hand sides.  Unlike the standard yacc.c template, here we set
   the default value of $$ to a zeroed-out value.  Since the default
   value is undefined, this behavior is technically correct.  */
static YYSTYPE yyval_default;
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;

/* Copy the second part of user declarations.  */

#line 98 "mini.tab.c" /* glr.c:263  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YYFREE
# define YYFREE free
#endif
#ifndef YYMALLOC
# define YYMALLOC malloc
#endif
#ifndef YYREALLOC
# define YYREALLOC realloc
#endif

#define YYSIZEMAX ((size_t) -1)

#ifdef __cplusplus
   typedef bool yybool;
#else
   typedef unsigned char yybool;
#endif
#define yytrue 1
#define yyfalse 0

#ifndef YYSETJMP
# include <setjmp.h>
# define YYJMP_BUF jmp_buf
# define YYSETJMP(Env) setjmp (Env)
/* Pacify clang.  */
# define YYLONGJMP(Env, Val) (longjmp (Env, Val), YYASSERT (0))
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#ifndef YYASSERT
# define YYASSERT(Condition) ((void) ((Condition) || (abort (), 0)))
#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1111

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  90
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  152
/* YYNRULES -- Number of states.  */
#define YYNSTATES  284
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule.  */
#define YYMAXRHS 7
/* YYMAXLEFT -- Maximum number of symbols to the left of a handle
   accessed by $0, $-1, etc., in any rule.  */
#define YYMAXLEFT 0

/* YYTRANSLATE(X) -- Bison symbol number corresponding to X.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   344

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89
};

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,    95,    95,    98,   101,   102,   105,   106,   110,   113,
     116,   117,   120,   121,   124,   125,   126,   127,   128,   131,
     132,   135,   138,   139,   142,   143,   146,   147,   148,   151,
     152,   155,   156,   159,   162,   165,   166,   169,   170,   173,
     176,   177,   178,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   208,   209,   212,   213,
     214,   215,   218,   221,   221,   222,   223,   224,   225,   228,
     229,   232,   233,   236,   237,   240,   241,   242,   243,   246,
     247,   248,   251,   252,   255,   256,   257,   258,   261,   262,
     265,   266,   269,   270,   271,   274,   277,   278,   281,   282,
     283,   286,   289,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   304,   305,   306,   307,   308,   311,   312,
     314,   315,   316,   317,   318,   319,   321,   322,   323,   324,
     326,   327,   328,   329,   330,   331,   332,   333,   337,   338,
     339,   340,   341
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "tRUNEVAL", "tSTRINGITPVAL",
  "tSTRINGRAWVAL", "tINTVAL", "tFLOATVAL", "tIDENTIFIER", "tVAR", "tIF",
  "tELSE", "tPRINT", "tCOLON", "tASSIGN", "tSEMICOLON", "tLEFTPAREN",
  "tRIGHTPAREN", "tLEFTBRACE", "tRIGHTBRACE", "tBANG", "tPLUS", "tMINUS",
  "tTIMES", "tDIV", "tEQUALS", "tNOTEQUALS", "tGREATEREQUALS",
  "tLESSEQUALS", "tGREATER", "tLESS", "tAND", "tOR", "tSTRUCT", "tSELECT",
  "tRETURN", "tRANGE", "tPACKAGE", "tMAP", "tINTERFACE", "tIMPORT",
  "tGOTO", "tGO", "tFOR", "tDEFER", "tDEFAULT", "tCONTINUE", "tCONST",
  "tCHAN", "tCASE", "tBREAK", "tFALLTHROUGH", "tSWITCH", "tTYPE",
  "tPRINTLN", "tAPPEND", "tLEN", "tCAP", "tMOD", "tBITWISEAND",
  "tBITWISEOR", "tBITWISEXOR", "tBITCLEAR", "tLEFTSHIFT", "tRIGHTSHIFT",
  "tPLUSEQUAL", "tMINUSEQUAL", "tTIMESEQUAL", "tDIVEQUAL", "tMODEQUAL",
  "tPLUSPLUS", "tMINUSMINUS", "tANDEQUAL", "tOREQUAL", "tXOREQUAL",
  "tLEFTSHIFTEQUAL", "tRIGHTSHIFTEQUAL", "tBITCLEAREQUAL", "tCOLONEQUAL",
  "tDOTDOTDOT", "tCOMMA", "tDOT", "tLEFTSQUAREBRACKET",
  "tRIGHTSQUAREBRACKET", "tFUNC", "UBANG", "UMINUS", "UPLUS", "UCARET",
  "UBITWISEAND", "$accept", "prog", "start", "imports", "top_level_dcls",
  "package", "import", "dcl", "top_level_dcl", "Type", "field_dcls",
  "field_dcl", "var_dcl", "var_specs", "var_spec", "type_dcl",
  "type_specs", "type_spec", "func_dcl", "signature", "result", "params",
  "param_ls", "assign_stmt", "stmt", "stmts", "print_stmt",
  "short_var_dec", "simple_stmt", "$@1", "inc_dec_stmt", "exp_list",
  "ident_list", "switch_stmt", "expr_case_clause", "switch_stmts",
  "ifstmt", "else_stmts", "block_stmt", "for_stmt", "for_clause",
  "for_exp", "post_stmt", "break_stmt", "continue_stmt", "primary_exp",
  "literals", "exp", "unary_exp", YY_NULLPTR
};
#endif

#define YYPACT_NINF -145
#define YYTABLE_NINF -84

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const short int yypact[] =
{
     -26,    18,    27,  -145,  -145,    25,  -145,    23,  -145,    65,
       9,    80,  -145,     5,    90,   100,  -145,    97,  -145,  -145,
    -145,  -145,  -145,  -145,  -145,    56,    57,  -145,  -145,    15,
    -145,     8,  -145,   731,    57,    93,   110,    -3,    86,  -145,
      20,   111,    95,    83,  -145,   106,  -145,  -145,  -145,  -145,
    -145,  -145,   731,   731,   731,   731,   107,   108,   116,   731,
      55,     3,  -145,  1024,  -145,   125,  -145,  -145,    63,    57,
     731,  -145,   133,   -13,     6,   438,  -145,    89,  -145,  -145,
    -145,  -145,   838,  -145,  -145,  -145,   731,   731,   731,  -145,
     731,   576,   146,   731,   731,   731,   731,   731,   731,   731,
     731,   731,   731,   731,   731,   731,   731,   731,   731,   731,
     731,   731,   731,  -145,    -2,    57,  -145,    55,  -145,  -145,
     111,  -145,   -71,   773,   139,  -145,   731,   618,  -145,  -145,
     638,   156,  -145,  -145,   158,   497,  -145,  -145,  -145,  -145,
    -145,     1,   -70,  -145,  -145,  -145,  -145,  -145,  -145,   311,
     159,  -145,   375,   854,   902,  1024,  -145,   -12,  -145,   331,
     105,   105,  -145,  -145,   403,   403,   403,   403,   403,   403,
    1047,  1036,  -145,  -145,   105,   105,  -145,  -145,  -145,  -145,
     164,     6,  -145,     6,   170,   228,   645,  1024,   172,  -145,
      95,   228,  -145,   174,   248,   704,  -145,  -145,   177,   731,
     731,   731,   731,   731,   731,   731,  -145,  -145,   731,   731,
     731,   731,   731,   731,   731,  -145,  -145,  -145,  -145,  -145,
    -145,  -145,   731,   182,  -145,    12,   731,  -145,  -145,    82,
     711,  -145,  -145,    16,  -145,    55,    55,  1024,  1024,  1024,
    1024,  1024,  1024,  1024,  1024,  1024,  1024,  1024,   918,   965,
      92,  -145,  -145,   179,  1024,  -145,   183,   731,  -145,   980,
      85,  -145,  -145,   182,  -145,  -145,   731,   556,    -1,    88,
    -145,  -145,  -145,  -145,  -145,  -145,   777,   556,  -145,   556,
    -145,    96,  -145,  -145
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     2,     4,     0,     1,     6,     8,     0,
       3,     0,     9,     0,     0,     0,    12,     0,    11,    10,
      13,     5,    83,    24,    22,     0,     0,    31,    29,     0,
       7,     0,    14,     0,     0,     0,     0,     0,    27,    33,
       0,    40,     0,    36,    23,     0,   127,   124,   125,   123,
     126,   115,     0,     0,     0,     0,     0,     0,     0,     0,
      28,   148,   114,    81,   147,     0,    19,    84,     0,     0,
       0,    30,     0,     0,     0,    73,    34,    40,    38,    35,
      37,    25,     0,   151,   149,   150,     0,     0,     0,   152,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    18,     0,     0,    15,    26,    32,    39,
       0,    41,   115,    73,     0,   101,    60,    73,   112,   111,
      73,     0,    65,    76,     0,    73,    59,    78,    63,    74,
      77,     0,     0,    62,    58,    57,    64,    56,    55,    81,
      83,   113,     0,     0,     0,    82,   122,     0,   120,     0,
     136,   137,   140,   141,   130,   131,   135,   133,   134,   132,
     129,   128,   142,   145,   138,   139,   146,   143,   144,    17,
       0,     0,    16,     0,     0,    81,     0,    61,     0,   102,
       0,    81,    89,     0,    81,     0,    67,   100,     0,     0,
       0,     0,     0,     0,     0,     0,    79,    80,     0,     0,
       0,     0,     0,     0,     0,   117,   118,   121,   119,    20,
      21,    42,     0,    97,    69,     0,   106,   104,   103,     0,
       0,    89,    71,     0,    66,    43,    72,    44,    45,    48,
      49,    50,    53,    46,    47,    51,    52,    54,     0,     0,
       0,    96,    68,     0,   107,    88,     0,     0,    89,     0,
       0,    70,   116,    95,    98,    99,   108,    92,     0,     0,
      89,    87,    94,   110,   109,   105,    81,    93,    91,    92,
      86,     0,    90,    85
};

  /* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -145,  -145,  -145,  -145,  -145,  -145,  -145,   185,  -145,    51,
    -145,  -145,  -145,  -145,   166,  -145,  -145,   160,  -145,  -145,
    -145,   155,  -145,   -67,  -134,   126,  -145,  -145,    17,  -145,
     -64,    -9,   -11,  -145,  -144,   -76,   -46,   -58,   -10,  -145,
    -145,  -145,  -145,  -145,  -145,  -145,  -145,   -52,   129
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const short int yydefgoto[] =
{
      -1,     2,     3,     7,    10,     4,    11,   132,    17,    65,
     114,   180,    18,    31,    24,    19,    40,    28,    20,    42,
      79,    43,    73,   133,   134,   277,   136,   137,   138,   139,
     140,   141,   142,   143,   229,   278,   144,   251,   145,   146,
     190,   253,   275,   147,   148,    61,    62,    63,    64
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const short int yytable[] =
{
      82,   198,    25,    68,   119,   217,    22,   -83,   200,   -83,
      36,     1,   279,    22,    32,   199,    22,   179,    13,    91,
      25,    23,    34,   149,    60,    44,     5,     6,    26,   252,
      74,    41,    76,   261,   152,   153,   154,    71,   155,    35,
       8,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   117,    14,     9,    32,    32,    74,   120,    90,    12,
      33,   185,    34,    34,   187,   191,    38,    39,   194,    90,
      69,    90,   157,   149,    92,    93,    36,   260,    37,    35,
      35,    32,    90,    15,    78,    21,    90,   150,    26,    77,
      70,   255,   123,   181,   271,    34,    27,   280,    29,   183,
      75,    66,    30,    75,   269,   283,    35,   189,    67,    22,
     116,    81,    35,    86,    87,   121,   281,   256,    96,    97,
     256,   257,    88,   256,   257,    90,    36,   257,    37,    37,
     184,   256,   113,   198,   188,   257,   115,   193,   118,   237,
     238,   239,   240,   241,   158,   186,   242,   243,   244,   245,
     246,   247,   248,   106,   107,    37,   182,   110,   111,   112,
     249,    37,   195,   196,   254,   223,   -14,   225,   259,   219,
     227,   228,    83,    84,    85,   222,   233,   226,    89,   230,
     235,   236,   234,   250,   266,    16,   267,    45,    80,   273,
      72,   135,   274,   282,   264,   272,     0,     0,     0,     0,
       0,     0,     0,     0,   276,   149,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   149,     0,   149,     0,     0,
       0,     0,   220,     0,   221,     0,     0,     0,     0,   263,
     265,     0,     0,   -75,     0,     0,    75,     0,   268,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,     0,     0,   -75,     0,     0,   231,     0,     0,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,     0,     0,     0,     0,     0,   106,   107,   108,   109,
     110,   111,   112,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   106,   107,   108,   109,
     110,   111,   112,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   -75,     0,     0,     0,
       0,     0,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,     0,     0,     0,     0,     0,     0,
       0,     0,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,     0,     0,     0,     0,     0,   106,
     107,   108,   109,   110,   111,   112,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   106,
     107,   108,   109,   110,   111,   112,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,     0,     0,
       0,     0,     0,     0,   218,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    94,    95,    96,    97,     0,     0,
       0,     0,     0,   106,   107,   108,   109,   110,   111,   112,
       0,    46,    47,    48,    49,    50,   122,    13,   123,     0,
     124,     0,     0,     0,    52,   214,    75,   125,    53,    54,
      55,   106,   107,   108,   109,   110,   111,   112,     0,     0,
       0,     0,     0,   126,     0,     0,     0,     0,     0,     0,
       0,   127,     0,     0,   128,     0,     0,     0,   129,     0,
     130,    14,   131,    56,    57,    58,     0,     0,     0,    59,
      46,    47,    48,    49,    50,   122,    13,   123,     0,   124,
       0,     0,     0,    52,     0,    75,   197,    53,    54,    55,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   126,     0,     0,     0,     0,     0,     0,     0,
     127,     0,     0,   128,     0,     0,     0,   129,     0,   130,
      14,   131,    56,    57,    58,     0,     0,     0,    59,    46,
      47,    48,    49,    50,   122,    13,   123,     0,   124,     0,
       0,   -73,    52,     0,    75,     0,    53,    54,    55,    46,
      47,    48,    49,    50,    51,     0,     0,     0,     0,     0,
       0,   126,    52,   156,     0,     0,    53,    54,    55,   127,
       0,     0,   128,     0,     0,     0,   129,     0,   130,    14,
     131,    56,    57,    58,     0,     0,     0,    59,     0,     0,
       0,    46,    47,    48,    49,    50,   122,     0,     0,     0,
       0,    56,    57,    58,    52,     0,    75,    59,    53,    54,
      55,    46,    47,    48,    49,    50,   122,     0,    46,    47,
      48,    49,    50,    51,    52,     0,   192,     0,    53,    54,
      55,    52,   224,     0,     0,    53,    54,    55,     0,     0,
       0,     0,     0,    56,    57,    58,     0,     0,     0,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    56,    57,    58,     0,     0,     0,    59,
      56,    57,    58,     0,     0,     0,    59,    46,    47,    48,
      49,    50,    51,     0,    46,    47,    48,    49,    50,    51,
      52,   232,     0,     0,    53,    54,    55,    52,     0,   258,
       0,    53,    54,    55,    46,    47,    48,    49,    50,    51,
       0,     0,     0,     0,     0,     0,     0,    52,     0,     0,
       0,    53,    54,    55,     0,     0,     0,     0,     0,    56,
      57,    58,     0,     0,     0,    59,    56,    57,    58,     0,
       0,     0,    59,     0,     0,     0,    46,    47,    48,    49,
      50,   122,     0,     0,     0,     0,    56,    57,    58,    52,
       0,     0,    59,    53,    54,    55,     0,     0,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    56,    57,
      58,     0,     0,     0,    59,   106,   107,   108,   109,   110,
     111,   112,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   151,     0,     0,     0,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   215,     0,     0,     0,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   106,   107,   108,   109,
     110,   111,   112,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   106,   107,   108,   109,   110,   111,   112,   216,
       0,     0,     0,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   262,     0,     0,     0,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     106,   107,   108,   109,   110,   111,   112,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   106,   107,   108,   109,
     110,   111,   112,    75,     0,     0,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   270,     0,
       0,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   106,   107,   108,   109,   110,   111,   112,
       0,     0,     0,     0,     0,     0,     0,     0,   106,   107,
     108,   109,   110,   111,   112,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,     0,     0,
       0,     0,   106,   107,   108,   109,   110,   111,   112,     0,
       0,     0,     0,     0,   106,   107,   108,   109,   110,   111,
     112,     0,     0,     0,     0,   106,   107,   108,   109,   110,
     111,   112
};

static const short int yycheck[] =
{
      52,   135,    13,     6,    17,    17,     8,    78,    78,    80,
      80,    37,    13,     8,     8,    14,     8,    19,     9,    16,
      31,    16,    16,    75,    33,    17,     8,     0,     8,    17,
      41,    16,    42,    17,    86,    87,    88,    17,    90,    33,
      15,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,    70,    53,    40,     8,     8,    77,    80,    80,     4,
      14,   123,    16,    16,   126,   127,    25,    26,   130,    80,
      83,    80,    91,   135,    81,    82,    80,   231,    82,    33,
      33,     8,    80,    84,    43,    15,    80,     8,     8,    16,
      14,    19,    10,   114,    19,    16,    16,    19,     8,   120,
      18,    18,    15,    18,   258,    19,    33,   127,     8,     8,
      69,    15,    33,    16,    16,    74,   270,    45,    23,    24,
      45,    49,    16,    45,    49,    80,    80,    49,    82,    82,
     123,    45,    17,   277,   127,    49,    83,   130,    15,   201,
     202,   203,   204,   205,     8,    16,   208,   209,   210,   211,
     212,   213,   214,    58,    59,    82,   115,    62,    63,    64,
     222,    82,    16,    15,   226,   185,    17,   186,   230,    15,
     190,   191,    53,    54,    55,    15,   195,    15,    59,    15,
     199,   200,    15,    11,    15,    10,    13,    31,    43,   266,
      40,    75,   266,   279,   250,   263,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   266,   267,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   277,    -1,   279,    -1,    -1,
      -1,    -1,   181,    -1,   183,    -1,    -1,    -1,    -1,   249,
     250,    -1,    -1,    15,    -1,    -1,    18,    -1,   257,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    -1,    15,    -1,    -1,    18,    -1,    -1,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    -1,    -1,    -1,    -1,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    15,    -1,    -1,    -1,
      -1,    -1,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    -1,    -1,    -1,    -1,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    58,
      59,    60,    61,    62,    63,    64,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    -1,
      -1,    -1,    -1,    -1,    83,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    58,    59,    60,    61,    62,    63,    64,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      12,    -1,    -1,    -1,    16,    80,    18,    19,    20,    21,
      22,    58,    59,    60,    61,    62,    63,    64,    -1,    -1,
      -1,    -1,    -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    -1,    -1,    46,    -1,    -1,    -1,    50,    -1,
      52,    53,    54,    55,    56,    57,    -1,    -1,    -1,    61,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    12,
      -1,    -1,    -1,    16,    -1,    18,    19,    20,    21,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    -1,    -1,    46,    -1,    -1,    -1,    50,    -1,    52,
      53,    54,    55,    56,    57,    -1,    -1,    -1,    61,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    12,    -1,
      -1,    15,    16,    -1,    18,    -1,    20,    21,    22,     3,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    16,    17,    -1,    -1,    20,    21,    22,    43,
      -1,    -1,    46,    -1,    -1,    -1,    50,    -1,    52,    53,
      54,    55,    56,    57,    -1,    -1,    -1,    61,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      -1,    55,    56,    57,    16,    -1,    18,    61,    20,    21,
      22,     3,     4,     5,     6,     7,     8,    -1,     3,     4,
       5,     6,     7,     8,    16,    -1,    18,    -1,    20,    21,
      22,    16,    17,    -1,    -1,    20,    21,    22,    -1,    -1,
      -1,    -1,    -1,    55,    56,    57,    -1,    -1,    -1,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    56,    57,    -1,    -1,    -1,    61,
      55,    56,    57,    -1,    -1,    -1,    61,     3,     4,     5,
       6,     7,     8,    -1,     3,     4,     5,     6,     7,     8,
      16,    17,    -1,    -1,    20,    21,    22,    16,    -1,    18,
      -1,    20,    21,    22,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    16,    -1,    -1,
      -1,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,    55,
      56,    57,    -1,    -1,    -1,    61,    55,    56,    57,    -1,
      -1,    -1,    61,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    -1,    55,    56,    57,    16,
      -1,    -1,    61,    20,    21,    22,    -1,    -1,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,
      57,    -1,    -1,    -1,    61,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    17,    -1,    -1,    -1,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    17,    -1,    -1,    -1,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    58,    59,    60,    61,
      62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    58,    59,    60,    61,    62,    63,    64,    17,
      -1,    -1,    -1,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    17,    -1,    -1,    -1,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      58,    59,    60,    61,    62,    63,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    58,    59,    60,    61,
      62,    63,    64,    18,    -1,    -1,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    18,    -1,
      -1,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,
      60,    61,    62,    63,    64,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    -1,    -1,
      -1,    -1,    58,    59,    60,    61,    62,    63,    64,    -1,
      -1,    -1,    -1,    -1,    58,    59,    60,    61,    62,    63,
      64,    -1,    -1,    -1,    -1,    58,    59,    60,    61,    62,
      63,    64
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    37,    91,    92,    95,     8,     0,    93,    15,    40,
      94,    96,     4,     9,    53,    84,    97,    98,   102,   105,
     108,    15,     8,    16,   104,   122,     8,    16,   107,     8,
      15,   103,     8,    14,    16,    33,    80,    82,    99,    99,
     106,    16,   109,   111,    17,   104,     3,     4,     5,     6,
       7,     8,    16,    20,    21,    22,    55,    56,    57,    61,
     121,   135,   136,   137,   138,    99,    18,     8,     6,    83,
      14,    17,   107,   112,   122,    18,   128,    16,    99,   110,
     111,    15,   137,   138,   138,   138,    16,    16,    16,   138,
      80,    16,    81,    82,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    58,    59,    60,    61,
      62,    63,    64,    17,   100,    83,    99,   121,    15,    17,
      80,    99,     8,    10,    12,    19,    35,    43,    46,    50,
      52,    54,    97,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   126,   128,   129,   133,   134,   137,
       8,    17,   137,   137,   137,   137,    17,   121,     8,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,    19,
     101,   122,    99,   122,   118,   137,    16,   137,   118,   128,
     130,   137,    18,   118,   137,    16,    15,    19,   114,    14,
      78,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    80,    17,    17,    17,    83,    15,
      99,    99,    15,   128,    17,   121,    15,   128,   128,   124,
      15,    18,    17,   121,    15,   121,   121,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
      11,   127,    17,   131,   137,    19,    45,    49,    18,   137,
     124,    17,    17,   128,   126,   128,    15,    13,   121,   124,
      18,    19,   127,   113,   120,   132,   137,   115,   125,    13,
      19,   124,   125,    19
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    90,    91,    92,    93,    93,    94,    94,    95,    96,
      97,    97,    98,    98,    99,    99,    99,    99,    99,   100,
     100,   101,   102,   102,   103,   103,   104,   104,   104,   105,
     105,   106,   106,   107,   108,   109,   109,   110,   110,   111,
     112,   112,   112,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   115,   115,   116,   116,
     116,   116,   117,   119,   118,   118,   118,   118,   118,   120,
     120,   121,   121,   122,   122,   123,   123,   123,   123,   124,
     124,   124,   125,   125,   126,   126,   126,   126,   127,   127,
     128,   128,   129,   129,   129,   130,   131,   131,   132,   132,
     132,   133,   134,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   136,   136,   136,   136,   136,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   138,   138,
     138,   138,   138
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     3,     0,     3,     0,     3,     3,     2,
       1,     1,     1,     1,     1,     3,     4,     4,     3,     0,
       3,     2,     2,     4,     0,     3,     4,     2,     3,     2,
       4,     0,     3,     2,     4,     2,     1,     1,     1,     3,
       0,     2,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     3,     2,     4,     3,
       4,     3,     3,     0,     1,     1,     1,     1,     1,     2,
       2,     1,     3,     1,     3,     7,     6,     5,     4,     0,
       5,     4,     0,     1,     6,     5,     4,     3,     2,     2,
       3,     2,     2,     3,     3,     5,     0,     1,     0,     1,
       1,     1,     1,     3,     1,     1,     6,     4,     4,     4,
       3,     4,     3,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     2,
       2,     2,     2
};


/* YYDPREC[RULE-NUM] -- Dynamic precedence of rule #RULE-NUM (0 if none).  */
static const unsigned char yydprec[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0
};

/* YYMERGER[RULE-NUM] -- Index of merging function for rule #RULE-NUM.  */
static const unsigned char yymerger[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0
};

/* YYIMMEDIATE[RULE-NUM] -- True iff rule #RULE-NUM is not to be deferred, as
   in the case of predicates.  */
static const yybool yyimmediate[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0
};

/* YYCONFLP[YYPACT[STATE-NUM]] -- Pointer into YYCONFL of start of
   list of conflicting reductions corresponding to action entry for
   state STATE-NUM in yytable.  0 means no conflicts.  The list in
   yyconfl is terminated by a rule number of 0.  */
static const unsigned char yyconflp[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     1,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0
};

/* YYCONFL[I] -- lists of conflicting rule numbers, each terminated by
   0, pointed into by YYCONFLP.  */
static const short int yyconfl[] =
{
       0,   115,     0
};

/* Error token number */
#define YYTERROR 1


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

# define YYRHSLOC(Rhs, K) ((Rhs)[K].yystate.yyloc)


YYSTYPE yylval;
YYLTYPE yylloc;

int yynerrs;
int yychar;

static const int YYEOF = 0;
static const int YYEMPTY = -2;

typedef enum { yyok, yyaccept, yyabort, yyerr } YYRESULTTAG;

#define YYCHK(YYE)                              \
  do {                                          \
    YYRESULTTAG yychk_flag = YYE;               \
    if (yychk_flag != yyok)                     \
      return yychk_flag;                        \
  } while (0)

#if YYDEBUG

# ifndef YYFPRINTF
#  define YYFPRINTF fprintf
# endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YYDPRINTF(Args)                        \
  do {                                          \
    if (yydebug)                                \
      YYFPRINTF Args;                           \
  } while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                  \
  do {                                                                  \
    if (yydebug)                                                        \
      {                                                                 \
        YYFPRINTF (stderr, "%s ", Title);                               \
        yy_symbol_print (stderr, Type, Value, Location);        \
        YYFPRINTF (stderr, "\n");                                       \
      }                                                                 \
  } while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;

struct yyGLRStack;
static void yypstack (struct yyGLRStack* yystackp, size_t yyk)
  YY_ATTRIBUTE_UNUSED;
static void yypdumpstack (struct yyGLRStack* yystackp)
  YY_ATTRIBUTE_UNUSED;

#else /* !YYDEBUG */

# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)

#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYMAXDEPTH * sizeof (GLRStackItem)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Minimum number of free items on the stack allowed after an
   allocation.  This is to allow allocation and initialization
   to be completed by functions that call yyexpandGLRStack before the
   stack is expanded, thus insuring that all necessary pointers get
   properly redirected to new data.  */
#define YYHEADROOM 2

#ifndef YYSTACKEXPANDABLE
#  define YYSTACKEXPANDABLE 1
#endif

#if YYSTACKEXPANDABLE
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyexpandGLRStack (Yystack);                       \
  } while (0)
#else
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyMemoryExhausted (Yystack);                      \
  } while (0)
#endif


#if YYERROR_VERBOSE

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static size_t
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      size_t yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return strlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

#endif /* !YYERROR_VERBOSE */

/** State numbers, as in LALR(1) machine */
typedef int yyStateNum;

/** Rule numbers, as in LALR(1) machine */
typedef int yyRuleNum;

/** Grammar symbol */
typedef int yySymbol;

/** Item references, as in LALR(1) machine */
typedef short int yyItemNum;

typedef struct yyGLRState yyGLRState;
typedef struct yyGLRStateSet yyGLRStateSet;
typedef struct yySemanticOption yySemanticOption;
typedef union yyGLRStackItem yyGLRStackItem;
typedef struct yyGLRStack yyGLRStack;

struct yyGLRState {
  /** Type tag: always true.  */
  yybool yyisState;
  /** Type tag for yysemantics.  If true, yysval applies, otherwise
   *  yyfirstVal applies.  */
  yybool yyresolved;
  /** Number of corresponding LALR(1) machine state.  */
  yyStateNum yylrState;
  /** Preceding state in this stack */
  yyGLRState* yypred;
  /** Source position of the last token produced by my symbol */
  size_t yyposn;
  union {
    /** First in a chain of alternative reductions producing the
     *  non-terminal corresponding to this state, threaded through
     *  yynext.  */
    yySemanticOption* yyfirstVal;
    /** Semantic value for this state.  */
    YYSTYPE yysval;
  } yysemantics;
  /** Source location for this state.  */
  YYLTYPE yyloc;
};

struct yyGLRStateSet {
  yyGLRState** yystates;
  /** During nondeterministic operation, yylookaheadNeeds tracks which
   *  stacks have actually needed the current lookahead.  During deterministic
   *  operation, yylookaheadNeeds[0] is not maintained since it would merely
   *  duplicate yychar != YYEMPTY.  */
  yybool* yylookaheadNeeds;
  size_t yysize, yycapacity;
};

struct yySemanticOption {
  /** Type tag: always false.  */
  yybool yyisState;
  /** Rule number for this reduction */
  yyRuleNum yyrule;
  /** The last RHS state in the list of states to be reduced.  */
  yyGLRState* yystate;
  /** The lookahead for this reduction.  */
  int yyrawchar;
  YYSTYPE yyval;
  YYLTYPE yyloc;
  /** Next sibling in chain of options.  To facilitate merging,
   *  options are chained in decreasing order by address.  */
  yySemanticOption* yynext;
};

/** Type of the items in the GLR stack.  The yyisState field
 *  indicates which item of the union is valid.  */
union yyGLRStackItem {
  yyGLRState yystate;
  yySemanticOption yyoption;
};

struct yyGLRStack {
  int yyerrState;
  /* To compute the location of the error token.  */
  yyGLRStackItem yyerror_range[3];

  YYJMP_BUF yyexception_buffer;
  yyGLRStackItem* yyitems;
  yyGLRStackItem* yynextFree;
  size_t yyspaceLeft;
  yyGLRState* yysplitPoint;
  yyGLRState* yylastDeleted;
  yyGLRStateSet yytops;
};

#if YYSTACKEXPANDABLE
static void yyexpandGLRStack (yyGLRStack* yystackp);
#endif

static _Noreturn void
yyFail (yyGLRStack* yystackp, const char* yymsg)
{
  if (yymsg != YY_NULLPTR)
    yyerror (yymsg);
  YYLONGJMP (yystackp->yyexception_buffer, 1);
}

static _Noreturn void
yyMemoryExhausted (yyGLRStack* yystackp)
{
  YYLONGJMP (yystackp->yyexception_buffer, 2);
}

#if YYDEBUG || YYERROR_VERBOSE
/** A printable representation of TOKEN.  */
static inline const char*
yytokenName (yySymbol yytoken)
{
  if (yytoken == YYEMPTY)
    return "";

  return yytname[yytoken];
}
#endif

/** Fill in YYVSP[YYLOW1 .. YYLOW0-1] from the chain of states starting
 *  at YYVSP[YYLOW0].yystate.yypred.  Leaves YYVSP[YYLOW1].yystate.yypred
 *  containing the pointer to the next state in the chain.  */
static void yyfillin (yyGLRStackItem *, int, int) YY_ATTRIBUTE_UNUSED;
static void
yyfillin (yyGLRStackItem *yyvsp, int yylow0, int yylow1)
{
  int i;
  yyGLRState *s = yyvsp[yylow0].yystate.yypred;
  for (i = yylow0-1; i >= yylow1; i -= 1)
    {
#if YYDEBUG
      yyvsp[i].yystate.yylrState = s->yylrState;
#endif
      yyvsp[i].yystate.yyresolved = s->yyresolved;
      if (s->yyresolved)
        yyvsp[i].yystate.yysemantics.yysval = s->yysemantics.yysval;
      else
        /* The effect of using yysval or yyloc (in an immediate rule) is
         * undefined.  */
        yyvsp[i].yystate.yysemantics.yyfirstVal = YY_NULLPTR;
      yyvsp[i].yystate.yyloc = s->yyloc;
      s = yyvsp[i].yystate.yypred = s->yypred;
    }
}

/* Do nothing if YYNORMAL or if *YYLOW <= YYLOW1.  Otherwise, fill in
 * YYVSP[YYLOW1 .. *YYLOW-1] as in yyfillin and set *YYLOW = YYLOW1.
 * For convenience, always return YYLOW1.  */
static inline int yyfill (yyGLRStackItem *, int *, int, yybool)
     YY_ATTRIBUTE_UNUSED;
static inline int
yyfill (yyGLRStackItem *yyvsp, int *yylow, int yylow1, yybool yynormal)
{
  if (!yynormal && yylow1 < *yylow)
    {
      yyfillin (yyvsp, *yylow, yylow1);
      *yylow = yylow1;
    }
  return yylow1;
}

/** Perform user action for rule number YYN, with RHS length YYRHSLEN,
 *  and top stack item YYVSP.  YYLVALP points to place to put semantic
 *  value ($$), and yylocp points to place for location information
 *  (@$).  Returns yyok for normal return, yyaccept for YYACCEPT,
 *  yyerr for YYERROR, yyabort for YYABORT.  */
static YYRESULTTAG
yyuserAction (yyRuleNum yyn, size_t yyrhslen, yyGLRStackItem* yyvsp,
              yyGLRStack* yystackp,
              YYSTYPE* yyvalp, YYLTYPE *yylocp)
{
  yybool yynormal YY_ATTRIBUTE_UNUSED = (yystackp->yysplitPoint == YY_NULLPTR);
  int yylow;
  YYUSE (yyvalp);
  YYUSE (yylocp);
  YYUSE (yyrhslen);
# undef yyerrok
# define yyerrok (yystackp->yyerrState = 0)
# undef YYACCEPT
# define YYACCEPT return yyaccept
# undef YYABORT
# define YYABORT return yyabort
# undef YYERROR
# define YYERROR return yyerrok, yyerr
# undef YYRECOVERING
# define YYRECOVERING() (yystackp->yyerrState != 0)
# undef yyclearin
# define yyclearin (yychar = YYEMPTY)
# undef YYFILL
# define YYFILL(N) yyfill (yyvsp, &yylow, N, yynormal)
# undef YYBACKUP
# define YYBACKUP(Token, Value)                                              \
  return yyerror (YY_("syntax error: cannot back up")),     \
         yyerrok, yyerr

  yylow = 1;
  if (yyrhslen == 0)
    *yyvalp = yyval_default;
  else
    *yyvalp = yyvsp[YYFILL (1-yyrhslen)].yystate.yysemantics.yysval;
  YYLLOC_DEFAULT ((*yylocp), (yyvsp - yyrhslen), yyrhslen);
  yystackp->yyerror_range[1].yystate.yyloc = *yylocp;

  switch (yyn)
    {
        case 2:
#line 95 "mini.y" /* glr.c:816  */
    {root = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.PROGRAM);}
#line 1411 "mini.tab.c" /* glr.c:816  */
    break;

  case 3:
#line 98 "mini.y" /* glr.c:816  */
    { ((*yyvalp).PROGRAM) = makeProgram((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.PACKAGE), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.IMPORT), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.TOPDECL), yylineno); }
#line 1417 "mini.tab.c" /* glr.c:816  */
    break;

  case 4:
#line 101 "mini.y" /* glr.c:816  */
    {((*yyvalp).IMPORT) = NULL;}
#line 1423 "mini.tab.c" /* glr.c:816  */
    break;

  case 5:
#line 102 "mini.y" /* glr.c:816  */
    { ((*yyvalp).IMPORT) = makeImportList((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.IMPORT), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.IMPORT)); }
#line 1429 "mini.tab.c" /* glr.c:816  */
    break;

  case 6:
#line 105 "mini.y" /* glr.c:816  */
    {((*yyvalp).TOPDECL) = NULL;}
#line 1435 "mini.tab.c" /* glr.c:816  */
    break;

  case 7:
#line 106 "mini.y" /* glr.c:816  */
    { ((*yyvalp).TOPDECL) = makeTopVarDeclList((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.TOPDECL), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.TOPDECL), yylineno);}
#line 1441 "mini.tab.c" /* glr.c:816  */
    break;

  case 8:
#line 110 "mini.y" /* glr.c:816  */
    { ((*yyvalp).PACKAGE) = makePackage((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.id), yylineno);}
#line 1447 "mini.tab.c" /* glr.c:816  */
    break;

  case 9:
#line 113 "mini.y" /* glr.c:816  */
    { ((*yyvalp).IMPORT) = makeImport((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.stringval), yylineno); }
#line 1453 "mini.tab.c" /* glr.c:816  */
    break;

  case 10:
#line 116 "mini.y" /* glr.c:816  */
    { ((*yyvalp).DCL) = makeTypeDcl((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.TYPEDECL), yylineno); }
#line 1459 "mini.tab.c" /* glr.c:816  */
    break;

  case 11:
#line 117 "mini.y" /* glr.c:816  */
    { ((*yyvalp).DCL) = makeVarDcl((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.VARDECL), yylineno); }
#line 1465 "mini.tab.c" /* glr.c:816  */
    break;

  case 12:
#line 120 "mini.y" /* glr.c:816  */
    { ((*yyvalp).TOPDECL) = makeTopDeclFromDcl((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.DCL)); }
#line 1471 "mini.tab.c" /* glr.c:816  */
    break;

  case 13:
#line 121 "mini.y" /* glr.c:816  */
    { ((*yyvalp).TOPDECL) = makeTopDeclFromFuncDcl((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.FUNCDECL)); }
#line 1477 "mini.tab.c" /* glr.c:816  */
    break;

  case 14:
#line 124 "mini.y" /* glr.c:816  */
    {((*yyvalp).TYPE) = makeTypeId((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.id), yylineno);}
#line 1483 "mini.tab.c" /* glr.c:816  */
    break;

  case 15:
#line 125 "mini.y" /* glr.c:816  */
    {((*yyvalp).TYPE) = makeTypeSlices((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.TYPE), yylineno);}
#line 1489 "mini.tab.c" /* glr.c:816  */
    break;

  case 16:
#line 126 "mini.y" /* glr.c:816  */
    {((*yyvalp).TYPE) = makeTypeArray((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.intval),(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.TYPE), yylineno);}
#line 1495 "mini.tab.c" /* glr.c:816  */
    break;

  case 17:
#line 127 "mini.y" /* glr.c:816  */
    {((*yyvalp).TYPE) = makeTypeStruct((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.FIELD_DCL), yylineno);}
#line 1501 "mini.tab.c" /* glr.c:816  */
    break;

  case 18:
#line 128 "mini.y" /* glr.c:816  */
    {((*yyvalp).TYPE) = makeTypeT((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.TYPE), yylineno);}
#line 1507 "mini.tab.c" /* glr.c:816  */
    break;

  case 19:
#line 131 "mini.y" /* glr.c:816  */
    {((*yyvalp).FIELD_DCL) = NULL;}
#line 1513 "mini.tab.c" /* glr.c:816  */
    break;

  case 20:
#line 132 "mini.y" /* glr.c:816  */
    {((*yyvalp).FIELD_DCL) = makeFieldDclList((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.FIELD_DCL), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.FIELD_DCL), yylineno);}
#line 1519 "mini.tab.c" /* glr.c:816  */
    break;

  case 21:
#line 135 "mini.y" /* glr.c:816  */
    {((*yyvalp).FIELD_DCL) = makeFieldDcl((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ID_LIST), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.TYPE), yylineno);}
#line 1525 "mini.tab.c" /* glr.c:816  */
    break;

  case 22:
#line 138 "mini.y" /* glr.c:816  */
    {((*yyvalp).VARDECL) = makeVarDecl((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.VARSPEC), yylineno);}
#line 1531 "mini.tab.c" /* glr.c:816  */
    break;

  case 23:
#line 139 "mini.y" /* glr.c:816  */
    {((*yyvalp).VARDECL) = makeVarDecl((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.VARSPEC), yylineno);}
#line 1537 "mini.tab.c" /* glr.c:816  */
    break;

  case 24:
#line 142 "mini.y" /* glr.c:816  */
    {((*yyvalp).VARSPEC) = NULL;}
#line 1543 "mini.tab.c" /* glr.c:816  */
    break;

  case 25:
#line 143 "mini.y" /* glr.c:816  */
    {((*yyvalp).VARSPEC) = makeVarSpecList((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.VARSPEC),(((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.VARSPEC),yylineno);}
#line 1549 "mini.tab.c" /* glr.c:816  */
    break;

  case 26:
#line 146 "mini.y" /* glr.c:816  */
    {((*yyvalp).VARSPEC) = makeVarSpec((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ID_LIST),(((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.TYPE),(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno);}
#line 1555 "mini.tab.c" /* glr.c:816  */
    break;

  case 27:
#line 147 "mini.y" /* glr.c:816  */
    {((*yyvalp).VARSPEC) = makeVarSpec((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ID_LIST),(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.TYPE),NULL, yylineno);}
#line 1561 "mini.tab.c" /* glr.c:816  */
    break;

  case 28:
#line 148 "mini.y" /* glr.c:816  */
    {((*yyvalp).VARSPEC) = makeVarSpec((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ID_LIST),NULL,(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno);}
#line 1567 "mini.tab.c" /* glr.c:816  */
    break;

  case 29:
#line 151 "mini.y" /* glr.c:816  */
    { ((*yyvalp).TYPEDECL) = makeTypeDecl((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.TYPESPEC), yylineno); }
#line 1573 "mini.tab.c" /* glr.c:816  */
    break;

  case 30:
#line 152 "mini.y" /* glr.c:816  */
    { ((*yyvalp).TYPEDECL) = makeTypeDecl((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.TYPESPEC), yylineno); }
#line 1579 "mini.tab.c" /* glr.c:816  */
    break;

  case 31:
#line 155 "mini.y" /* glr.c:816  */
    { ((*yyvalp).TYPESPEC) = NULL; }
#line 1585 "mini.tab.c" /* glr.c:816  */
    break;

  case 32:
#line 156 "mini.y" /* glr.c:816  */
    { ((*yyvalp).TYPESPEC) = makeTypeSpecList((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.TYPESPEC), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.TYPESPEC)); }
#line 1591 "mini.tab.c" /* glr.c:816  */
    break;

  case 33:
#line 159 "mini.y" /* glr.c:816  */
    { ((*yyvalp).TYPESPEC) = makeTypeSpec((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.id), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.TYPE), yylineno); }
#line 1597 "mini.tab.c" /* glr.c:816  */
    break;

  case 34:
#line 162 "mini.y" /* glr.c:816  */
    { ((*yyvalp).FUNCDECL) = makeFuncDcl((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.id), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.SIGNATURE), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.STMT), yylineno);}
#line 1603 "mini.tab.c" /* glr.c:816  */
    break;

  case 35:
#line 165 "mini.y" /* glr.c:816  */
    {((*yyvalp).SIGNATURE) = makeSignature((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.PARAMS), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.RESULT), yylineno);}
#line 1609 "mini.tab.c" /* glr.c:816  */
    break;

  case 36:
#line 166 "mini.y" /* glr.c:816  */
    {((*yyvalp).SIGNATURE) = makeSignature((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.PARAMS), NULL, yylineno);}
#line 1615 "mini.tab.c" /* glr.c:816  */
    break;

  case 37:
#line 169 "mini.y" /* glr.c:816  */
    {((*yyvalp).RESULT) = makeResultP((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.PARAMS), yylineno);}
#line 1621 "mini.tab.c" /* glr.c:816  */
    break;

  case 38:
#line 170 "mini.y" /* glr.c:816  */
    {((*yyvalp).RESULT) = makeResultType((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.TYPE), yylineno);}
#line 1627 "mini.tab.c" /* glr.c:816  */
    break;

  case 39:
#line 173 "mini.y" /* glr.c:816  */
    {((*yyvalp).PARAMS) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.PARAMS);}
#line 1633 "mini.tab.c" /* glr.c:816  */
    break;

  case 40:
#line 176 "mini.y" /* glr.c:816  */
    {((*yyvalp).PARAMS) = NULL;}
#line 1639 "mini.tab.c" /* glr.c:816  */
    break;

  case 41:
#line 177 "mini.y" /* glr.c:816  */
    {((*yyvalp).PARAMS) = makeParams((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ID_LIST), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.TYPE), yylineno);}
#line 1645 "mini.tab.c" /* glr.c:816  */
    break;

  case 42:
#line 178 "mini.y" /* glr.c:816  */
    {((*yyvalp).PARAMS) = makeParamsList((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.PARAMS), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ID_LIST), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.TYPE), yylineno);}
#line 1651 "mini.tab.c" /* glr.c:816  */
    break;

  case 43:
#line 181 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeAssignStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), normal, yylineno); }
#line 1657 "mini.tab.c" /* glr.c:816  */
    break;

  case 44:
#line 182 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeAssignStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), plus, yylineno); }
#line 1663 "mini.tab.c" /* glr.c:816  */
    break;

  case 45:
#line 183 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeAssignStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), minus, yylineno); }
#line 1669 "mini.tab.c" /* glr.c:816  */
    break;

  case 46:
#line 184 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeAssignStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), or, yylineno); }
#line 1675 "mini.tab.c" /* glr.c:816  */
    break;

  case 47:
#line 185 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeAssignStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), xor, yylineno); }
#line 1681 "mini.tab.c" /* glr.c:816  */
    break;

  case 48:
#line 186 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeAssignStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), mult, yylineno); }
#line 1687 "mini.tab.c" /* glr.c:816  */
    break;

  case 49:
#line 187 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeAssignStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), divide, yylineno); }
#line 1693 "mini.tab.c" /* glr.c:816  */
    break;

  case 50:
#line 188 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeAssignStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), mod, yylineno); }
#line 1699 "mini.tab.c" /* glr.c:816  */
    break;

  case 51:
#line 189 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeAssignStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), leftShift, yylineno); }
#line 1705 "mini.tab.c" /* glr.c:816  */
    break;

  case 52:
#line 190 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeAssignStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), rightShift, yylineno); }
#line 1711 "mini.tab.c" /* glr.c:816  */
    break;

  case 53:
#line 191 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeAssignStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), and, yylineno); }
#line 1717 "mini.tab.c" /* glr.c:816  */
    break;

  case 54:
#line 192 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeAssignStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), bitclear, yylineno); }
#line 1723 "mini.tab.c" /* glr.c:816  */
    break;

  case 55:
#line 195 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.STMT); }
#line 1729 "mini.tab.c" /* glr.c:816  */
    break;

  case 56:
#line 196 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.STMT); }
#line 1735 "mini.tab.c" /* glr.c:816  */
    break;

  case 57:
#line 197 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.STMT); }
#line 1741 "mini.tab.c" /* glr.c:816  */
    break;

  case 58:
#line 198 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.STMT); }
#line 1747 "mini.tab.c" /* glr.c:816  */
    break;

  case 59:
#line 199 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.STMT); }
#line 1753 "mini.tab.c" /* glr.c:816  */
    break;

  case 60:
#line 200 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeReturnStmt(NULL, yylineno); }
#line 1759 "mini.tab.c" /* glr.c:816  */
    break;

  case 61:
#line 201 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeReturnStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 1765 "mini.tab.c" /* glr.c:816  */
    break;

  case 62:
#line 202 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.STMT); }
#line 1771 "mini.tab.c" /* glr.c:816  */
    break;

  case 63:
#line 203 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.STMT); }
#line 1777 "mini.tab.c" /* glr.c:816  */
    break;

  case 64:
#line 204 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.STMT); }
#line 1783 "mini.tab.c" /* glr.c:816  */
    break;

  case 65:
#line 205 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeDclStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.DCL), yylineno); }
#line 1789 "mini.tab.c" /* glr.c:816  */
    break;

  case 66:
#line 208 "mini.y" /* glr.c:816  */
    {((*yyvalp).STMT) = makeStmtList((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.STMT),(((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.STMT),yylineno);}
#line 1795 "mini.tab.c" /* glr.c:816  */
    break;

  case 67:
#line 209 "mini.y" /* glr.c:816  */
    {((*yyvalp).STMT) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.STMT);}
#line 1801 "mini.tab.c" /* glr.c:816  */
    break;

  case 68:
#line 212 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makePrintStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 1807 "mini.tab.c" /* glr.c:816  */
    break;

  case 69:
#line 213 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makePrintStmt(NULL, yylineno); }
#line 1813 "mini.tab.c" /* glr.c:816  */
    break;

  case 70:
#line 214 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makePrintlnStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 1819 "mini.tab.c" /* glr.c:816  */
    break;

  case 71:
#line 215 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makePrintlnStmt(NULL, yylineno); }
#line 1825 "mini.tab.c" /* glr.c:816  */
    break;

  case 72:
#line 218 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeShortVarDecStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ID_LIST), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 1831 "mini.tab.c" /* glr.c:816  */
    break;

  case 73:
#line 221 "mini.y" /* glr.c:816  */
    {}
#line 1837 "mini.tab.c" /* glr.c:816  */
    break;

  case 74:
#line 221 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeEmptyStmt(yylineno); }
#line 1843 "mini.tab.c" /* glr.c:816  */
    break;

  case 75:
#line 222 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeExpStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 1849 "mini.tab.c" /* glr.c:816  */
    break;

  case 76:
#line 223 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.STMT); }
#line 1855 "mini.tab.c" /* glr.c:816  */
    break;

  case 77:
#line 224 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.STMT); }
#line 1861 "mini.tab.c" /* glr.c:816  */
    break;

  case 78:
#line 225 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.STMT); }
#line 1867 "mini.tab.c" /* glr.c:816  */
    break;

  case 79:
#line 228 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeIncStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 1873 "mini.tab.c" /* glr.c:816  */
    break;

  case 80:
#line 229 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeDecStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 1879 "mini.tab.c" /* glr.c:816  */
    break;

  case 81:
#line 232 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeExpList(NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno);}
#line 1885 "mini.tab.c" /* glr.c:816  */
    break;

  case 82:
#line 233 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeExpList((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno);}
#line 1891 "mini.tab.c" /* glr.c:816  */
    break;

  case 83:
#line 236 "mini.y" /* glr.c:816  */
    {((*yyvalp).ID_LIST) = makeIdList(NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.id), yylineno);}
#line 1897 "mini.tab.c" /* glr.c:816  */
    break;

  case 84:
#line 237 "mini.y" /* glr.c:816  */
    {((*yyvalp).ID_LIST) = makeIdList((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ID_LIST), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.id), yylineno);}
#line 1903 "mini.tab.c" /* glr.c:816  */
    break;

  case 85:
#line 240 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeSwitchStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.STMT), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.CASE_CLAUSE), yylineno); }
#line 1909 "mini.tab.c" /* glr.c:816  */
    break;

  case 86:
#line 241 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeSwitchStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.STMT), NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.CASE_CLAUSE), yylineno); }
#line 1915 "mini.tab.c" /* glr.c:816  */
    break;

  case 87:
#line 242 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeSwitchStmt(NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.CASE_CLAUSE), yylineno); }
#line 1921 "mini.tab.c" /* glr.c:816  */
    break;

  case 88:
#line 243 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeSwitchStmt(NULL, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.CASE_CLAUSE), yylineno); }
#line 1927 "mini.tab.c" /* glr.c:816  */
    break;

  case 89:
#line 246 "mini.y" /* glr.c:816  */
    { ((*yyvalp).CASE_CLAUSE) = NULL; }
#line 1933 "mini.tab.c" /* glr.c:816  */
    break;

  case 90:
#line 247 "mini.y" /* glr.c:816  */
    { ((*yyvalp).CASE_CLAUSE) = makeCaseClause(1, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.CASE_CLAUSE), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.STMT), yylineno); }
#line 1939 "mini.tab.c" /* glr.c:816  */
    break;

  case 91:
#line 248 "mini.y" /* glr.c:816  */
    { ((*yyvalp).CASE_CLAUSE) = makeCaseClause(0, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.CASE_CLAUSE), NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.STMT), yylineno); }
#line 1945 "mini.tab.c" /* glr.c:816  */
    break;

  case 92:
#line 251 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = NULL; }
#line 1951 "mini.tab.c" /* glr.c:816  */
    break;

  case 93:
#line 252 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.STMT); }
#line 1957 "mini.tab.c" /* glr.c:816  */
    break;

  case 94:
#line 255 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeIfStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.STMT), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.STMT), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.STMT), yylineno); }
#line 1963 "mini.tab.c" /* glr.c:816  */
    break;

  case 95:
#line 256 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeIfStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.STMT), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.STMT), NULL, yylineno); }
#line 1969 "mini.tab.c" /* glr.c:816  */
    break;

  case 96:
#line 257 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeIfStmt(NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.STMT), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.STMT), yylineno); }
#line 1975 "mini.tab.c" /* glr.c:816  */
    break;

  case 97:
#line 258 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeIfStmt(NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.STMT), NULL, yylineno); }
#line 1981 "mini.tab.c" /* glr.c:816  */
    break;

  case 98:
#line 261 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeElseStmt(NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.STMT), yylineno); }
#line 1987 "mini.tab.c" /* glr.c:816  */
    break;

  case 99:
#line 262 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeElseStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.STMT), NULL, yylineno); }
#line 1993 "mini.tab.c" /* glr.c:816  */
    break;

  case 100:
#line 265 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeBlockStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.STMT), yylineno); }
#line 1999 "mini.tab.c" /* glr.c:816  */
    break;

  case 101:
#line 266 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeBlockStmt(NULL, yylineno); }
#line 2005 "mini.tab.c" /* glr.c:816  */
    break;

  case 102:
#line 269 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeForStmt(NULL, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.STMT), yylineno); }
#line 2011 "mini.tab.c" /* glr.c:816  */
    break;

  case 103:
#line 270 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeForStmt((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.EXP), NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.STMT), yylineno); }
#line 2017 "mini.tab.c" /* glr.c:816  */
    break;

  case 104:
#line 271 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeForStmt(NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.FOR_CLAUSE), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.STMT), yylineno); }
#line 2023 "mini.tab.c" /* glr.c:816  */
    break;

  case 105:
#line 274 "mini.y" /* glr.c:816  */
    { ((*yyvalp).FOR_CLAUSE) = makeForClause((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.STMT), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.STMT), yylineno); }
#line 2029 "mini.tab.c" /* glr.c:816  */
    break;

  case 106:
#line 277 "mini.y" /* glr.c:816  */
    {((*yyvalp).EXP)=NULL;}
#line 2035 "mini.tab.c" /* glr.c:816  */
    break;

  case 107:
#line 278 "mini.y" /* glr.c:816  */
    {((*yyvalp).EXP)=(((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP);}
#line 2041 "mini.tab.c" /* glr.c:816  */
    break;

  case 108:
#line 281 "mini.y" /* glr.c:816  */
    {}
#line 2047 "mini.tab.c" /* glr.c:816  */
    break;

  case 111:
#line 286 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeBreakStmt(yylineno); }
#line 2053 "mini.tab.c" /* glr.c:816  */
    break;

  case 112:
#line 289 "mini.y" /* glr.c:816  */
    { ((*yyvalp).STMT) = makeContinueStmt(yylineno); }
#line 2059 "mini.tab.c" /* glr.c:816  */
    break;

  case 113:
#line 292 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.EXP); }
#line 2065 "mini.tab.c" /* glr.c:816  */
    break;

  case 114:
#line 293 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP); }
#line 2071 "mini.tab.c" /* glr.c:816  */
    break;

  case 115:
#line 294 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeIdentifierExp((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.id), yylineno); }
#line 2077 "mini.tab.c" /* glr.c:816  */
    break;

  case 116:
#line 295 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeAppendExp((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2083 "mini.tab.c" /* glr.c:816  */
    break;

  case 117:
#line 296 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeLenExp ((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2089 "mini.tab.c" /* glr.c:816  */
    break;

  case 118:
#line 297 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeCapExp ((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2095 "mini.tab.c" /* glr.c:816  */
    break;

  case 119:
#line 298 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeArrayIndexExp((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2101 "mini.tab.c" /* glr.c:816  */
    break;

  case 120:
#line 299 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeSelectorExp((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.id), yylineno); }
#line 2107 "mini.tab.c" /* glr.c:816  */
    break;

  case 121:
#line 300 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeFuncExp((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2113 "mini.tab.c" /* glr.c:816  */
    break;

  case 122:
#line 301 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeFuncExp((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), NULL, yylineno); }
#line 2119 "mini.tab.c" /* glr.c:816  */
    break;

  case 123:
#line 304 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeIntExp((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.intval), yylineno); }
#line 2125 "mini.tab.c" /* glr.c:816  */
    break;

  case 124:
#line 305 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeStringItpExp((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.stringval), yylineno); }
#line 2131 "mini.tab.c" /* glr.c:816  */
    break;

  case 125:
#line 306 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeStringRawExp((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.stringval), yylineno); }
#line 2137 "mini.tab.c" /* glr.c:816  */
    break;

  case 126:
#line 307 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeFloat64Exp((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.floatval), yylineno); }
#line 2143 "mini.tab.c" /* glr.c:816  */
    break;

  case 127:
#line 308 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeRuneExp((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.runeval), yylineno); }
#line 2149 "mini.tab.c" /* glr.c:816  */
    break;

  case 128:
#line 311 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeBinaryExp(orExpr, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2155 "mini.tab.c" /* glr.c:816  */
    break;

  case 129:
#line 312 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeBinaryExp(andExpr, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2161 "mini.tab.c" /* glr.c:816  */
    break;

  case 130:
#line 314 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeBinaryExp(equalsExpr, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2167 "mini.tab.c" /* glr.c:816  */
    break;

  case 131:
#line 315 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeBinaryExp(notequalsExpr, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2173 "mini.tab.c" /* glr.c:816  */
    break;

  case 132:
#line 316 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeBinaryExp(lessExpr, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2179 "mini.tab.c" /* glr.c:816  */
    break;

  case 133:
#line 317 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeBinaryExp(lessEqualsExpr, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2185 "mini.tab.c" /* glr.c:816  */
    break;

  case 134:
#line 318 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeBinaryExp(greaterExpr, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2191 "mini.tab.c" /* glr.c:816  */
    break;

  case 135:
#line 319 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeBinaryExp(greaterEqualsExpr, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2197 "mini.tab.c" /* glr.c:816  */
    break;

  case 136:
#line 321 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeBinaryExp(plusExpr, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2203 "mini.tab.c" /* glr.c:816  */
    break;

  case 137:
#line 322 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeBinaryExp(minusExpr, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2209 "mini.tab.c" /* glr.c:816  */
    break;

  case 138:
#line 323 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeBinaryExp(bitwiseOrExpr, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2215 "mini.tab.c" /* glr.c:816  */
    break;

  case 139:
#line 324 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeBinaryExp(bitwiseXorExpr, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2221 "mini.tab.c" /* glr.c:816  */
    break;

  case 140:
#line 326 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeBinaryExp(timesExpr, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2227 "mini.tab.c" /* glr.c:816  */
    break;

  case 141:
#line 327 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeBinaryExp(divExpr, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2233 "mini.tab.c" /* glr.c:816  */
    break;

  case 142:
#line 328 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeBinaryExp(modExpr, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2239 "mini.tab.c" /* glr.c:816  */
    break;

  case 143:
#line 329 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeBinaryExp(leftShiftExpr, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2245 "mini.tab.c" /* glr.c:816  */
    break;

  case 144:
#line 330 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeBinaryExp(rightShiftExpr, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2251 "mini.tab.c" /* glr.c:816  */
    break;

  case 145:
#line 331 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeBinaryExp(bitwiseAndExpr, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2257 "mini.tab.c" /* glr.c:816  */
    break;

  case 146:
#line 332 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeBinaryExp(bitClearExpr, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.EXP), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2263 "mini.tab.c" /* glr.c:816  */
    break;

  case 147:
#line 333 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP); }
#line 2269 "mini.tab.c" /* glr.c:816  */
    break;

  case 148:
#line 337 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP); }
#line 2275 "mini.tab.c" /* glr.c:816  */
    break;

  case 149:
#line 338 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeUnaryExp(uPlusExpr, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2281 "mini.tab.c" /* glr.c:816  */
    break;

  case 150:
#line 339 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeUnaryExp(uMinusExpr, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2287 "mini.tab.c" /* glr.c:816  */
    break;

  case 151:
#line 340 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeUnaryExp(uBangExpr, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2293 "mini.tab.c" /* glr.c:816  */
    break;

  case 152:
#line 341 "mini.y" /* glr.c:816  */
    { ((*yyvalp).EXP) = makeUnaryExp(uCaretExpr, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.EXP), yylineno); }
#line 2299 "mini.tab.c" /* glr.c:816  */
    break;


#line 2303 "mini.tab.c" /* glr.c:816  */
      default: break;
    }

  return yyok;
# undef yyerrok
# undef YYABORT
# undef YYACCEPT
# undef YYERROR
# undef YYBACKUP
# undef yyclearin
# undef YYRECOVERING
}


static void
yyuserMerge (int yyn, YYSTYPE* yy0, YYSTYPE* yy1)
{
  YYUSE (yy0);
  YYUSE (yy1);

  switch (yyn)
    {

      default: break;
    }
}

                              /* Bison grammar-table manipulation.  */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}

/** Number of symbols composing the right hand side of rule #RULE.  */
static inline int
yyrhsLength (yyRuleNum yyrule)
{
  return yyr2[yyrule];
}

static void
yydestroyGLRState (char const *yymsg, yyGLRState *yys)
{
  if (yys->yyresolved)
    yydestruct (yymsg, yystos[yys->yylrState],
                &yys->yysemantics.yysval, &yys->yyloc);
  else
    {
#if YYDEBUG
      if (yydebug)
        {
          if (yys->yysemantics.yyfirstVal)
            YYFPRINTF (stderr, "%s unresolved", yymsg);
          else
            YYFPRINTF (stderr, "%s incomplete", yymsg);
          YY_SYMBOL_PRINT ("", yystos[yys->yylrState], YY_NULLPTR, &yys->yyloc);
        }
#endif

      if (yys->yysemantics.yyfirstVal)
        {
          yySemanticOption *yyoption = yys->yysemantics.yyfirstVal;
          yyGLRState *yyrh;
          int yyn;
          for (yyrh = yyoption->yystate, yyn = yyrhsLength (yyoption->yyrule);
               yyn > 0;
               yyrh = yyrh->yypred, yyn -= 1)
            yydestroyGLRState (yymsg, yyrh);
        }
    }
}

/** Left-hand-side symbol for rule #YYRULE.  */
static inline yySymbol
yylhsNonterm (yyRuleNum yyrule)
{
  return yyr1[yyrule];
}

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-145)))

/** True iff LR state YYSTATE has only a default reduction (regardless
 *  of token).  */
static inline yybool
yyisDefaultedState (yyStateNum yystate)
{
  return yypact_value_is_default (yypact[yystate]);
}

/** The default reduction for YYSTATE, assuming it has one.  */
static inline yyRuleNum
yydefaultAction (yyStateNum yystate)
{
  return yydefact[yystate];
}

#define yytable_value_is_error(Yytable_value) \
  0

/** Set *YYACTION to the action to take in YYSTATE on seeing YYTOKEN.
 *  Result R means
 *    R < 0:  Reduce on rule -R.
 *    R = 0:  Error.
 *    R > 0:  Shift to state R.
 *  Set *YYCONFLICTS to a pointer into yyconfl to a 0-terminated list
 *  of conflicting reductions.
 */
static inline void
yygetLRActions (yyStateNum yystate, int yytoken,
                int* yyaction, const short int** yyconflicts)
{
  int yyindex = yypact[yystate] + yytoken;
  if (yypact_value_is_default (yypact[yystate])
      || yyindex < 0 || YYLAST < yyindex || yycheck[yyindex] != yytoken)
    {
      *yyaction = -yydefact[yystate];
      *yyconflicts = yyconfl;
    }
  else if (! yytable_value_is_error (yytable[yyindex]))
    {
      *yyaction = yytable[yyindex];
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
  else
    {
      *yyaction = 0;
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
}

/** Compute post-reduction state.
 * \param yystate   the current state
 * \param yysym     the nonterminal to push on the stack
 */
static inline yyStateNum
yyLRgotoState (yyStateNum yystate, yySymbol yysym)
{
  int yyr = yypgoto[yysym - YYNTOKENS] + yystate;
  if (0 <= yyr && yyr <= YYLAST && yycheck[yyr] == yystate)
    return yytable[yyr];
  else
    return yydefgoto[yysym - YYNTOKENS];
}

static inline yybool
yyisShiftAction (int yyaction)
{
  return 0 < yyaction;
}

static inline yybool
yyisErrorAction (int yyaction)
{
  return yyaction == 0;
}

                                /* GLRStates */

/** Return a fresh GLRStackItem in YYSTACKP.  The item is an LR state
 *  if YYISSTATE, and otherwise a semantic option.  Callers should call
 *  YY_RESERVE_GLRSTACK afterwards to make sure there is sufficient
 *  headroom.  */

static inline yyGLRStackItem*
yynewGLRStackItem (yyGLRStack* yystackp, yybool yyisState)
{
  yyGLRStackItem* yynewItem = yystackp->yynextFree;
  yystackp->yyspaceLeft -= 1;
  yystackp->yynextFree += 1;
  yynewItem->yystate.yyisState = yyisState;
  return yynewItem;
}

/** Add a new semantic action that will execute the action for rule
 *  YYRULE on the semantic values in YYRHS to the list of
 *  alternative actions for YYSTATE.  Assumes that YYRHS comes from
 *  stack #YYK of *YYSTACKP. */
static void
yyaddDeferredAction (yyGLRStack* yystackp, size_t yyk, yyGLRState* yystate,
                     yyGLRState* yyrhs, yyRuleNum yyrule)
{
  yySemanticOption* yynewOption =
    &yynewGLRStackItem (yystackp, yyfalse)->yyoption;
  YYASSERT (!yynewOption->yyisState);
  yynewOption->yystate = yyrhs;
  yynewOption->yyrule = yyrule;
  if (yystackp->yytops.yylookaheadNeeds[yyk])
    {
      yynewOption->yyrawchar = yychar;
      yynewOption->yyval = yylval;
      yynewOption->yyloc = yylloc;
    }
  else
    yynewOption->yyrawchar = YYEMPTY;
  yynewOption->yynext = yystate->yysemantics.yyfirstVal;
  yystate->yysemantics.yyfirstVal = yynewOption;

  YY_RESERVE_GLRSTACK (yystackp);
}

                                /* GLRStacks */

/** Initialize YYSET to a singleton set containing an empty stack.  */
static yybool
yyinitStateSet (yyGLRStateSet* yyset)
{
  yyset->yysize = 1;
  yyset->yycapacity = 16;
  yyset->yystates = (yyGLRState**) YYMALLOC (16 * sizeof yyset->yystates[0]);
  if (! yyset->yystates)
    return yyfalse;
  yyset->yystates[0] = YY_NULLPTR;
  yyset->yylookaheadNeeds =
    (yybool*) YYMALLOC (16 * sizeof yyset->yylookaheadNeeds[0]);
  if (! yyset->yylookaheadNeeds)
    {
      YYFREE (yyset->yystates);
      return yyfalse;
    }
  return yytrue;
}

static void yyfreeStateSet (yyGLRStateSet* yyset)
{
  YYFREE (yyset->yystates);
  YYFREE (yyset->yylookaheadNeeds);
}

/** Initialize *YYSTACKP to a single empty stack, with total maximum
 *  capacity for all stacks of YYSIZE.  */
static yybool
yyinitGLRStack (yyGLRStack* yystackp, size_t yysize)
{
  yystackp->yyerrState = 0;
  yynerrs = 0;
  yystackp->yyspaceLeft = yysize;
  yystackp->yyitems =
    (yyGLRStackItem*) YYMALLOC (yysize * sizeof yystackp->yynextFree[0]);
  if (!yystackp->yyitems)
    return yyfalse;
  yystackp->yynextFree = yystackp->yyitems;
  yystackp->yysplitPoint = YY_NULLPTR;
  yystackp->yylastDeleted = YY_NULLPTR;
  return yyinitStateSet (&yystackp->yytops);
}


#if YYSTACKEXPANDABLE
# define YYRELOC(YYFROMITEMS,YYTOITEMS,YYX,YYTYPE) \
  &((YYTOITEMS) - ((YYFROMITEMS) - (yyGLRStackItem*) (YYX)))->YYTYPE

/** If *YYSTACKP is expandable, extend it.  WARNING: Pointers into the
    stack from outside should be considered invalid after this call.
    We always expand when there are 1 or fewer items left AFTER an
    allocation, so that we can avoid having external pointers exist
    across an allocation.  */
static void
yyexpandGLRStack (yyGLRStack* yystackp)
{
  yyGLRStackItem* yynewItems;
  yyGLRStackItem* yyp0, *yyp1;
  size_t yynewSize;
  size_t yyn;
  size_t yysize = yystackp->yynextFree - yystackp->yyitems;
  if (YYMAXDEPTH - YYHEADROOM < yysize)
    yyMemoryExhausted (yystackp);
  yynewSize = 2*yysize;
  if (YYMAXDEPTH < yynewSize)
    yynewSize = YYMAXDEPTH;
  yynewItems = (yyGLRStackItem*) YYMALLOC (yynewSize * sizeof yynewItems[0]);
  if (! yynewItems)
    yyMemoryExhausted (yystackp);
  for (yyp0 = yystackp->yyitems, yyp1 = yynewItems, yyn = yysize;
       0 < yyn;
       yyn -= 1, yyp0 += 1, yyp1 += 1)
    {
      *yyp1 = *yyp0;
      if (*(yybool *) yyp0)
        {
          yyGLRState* yys0 = &yyp0->yystate;
          yyGLRState* yys1 = &yyp1->yystate;
          if (yys0->yypred != YY_NULLPTR)
            yys1->yypred =
              YYRELOC (yyp0, yyp1, yys0->yypred, yystate);
          if (! yys0->yyresolved && yys0->yysemantics.yyfirstVal != YY_NULLPTR)
            yys1->yysemantics.yyfirstVal =
              YYRELOC (yyp0, yyp1, yys0->yysemantics.yyfirstVal, yyoption);
        }
      else
        {
          yySemanticOption* yyv0 = &yyp0->yyoption;
          yySemanticOption* yyv1 = &yyp1->yyoption;
          if (yyv0->yystate != YY_NULLPTR)
            yyv1->yystate = YYRELOC (yyp0, yyp1, yyv0->yystate, yystate);
          if (yyv0->yynext != YY_NULLPTR)
            yyv1->yynext = YYRELOC (yyp0, yyp1, yyv0->yynext, yyoption);
        }
    }
  if (yystackp->yysplitPoint != YY_NULLPTR)
    yystackp->yysplitPoint = YYRELOC (yystackp->yyitems, yynewItems,
                                      yystackp->yysplitPoint, yystate);

  for (yyn = 0; yyn < yystackp->yytops.yysize; yyn += 1)
    if (yystackp->yytops.yystates[yyn] != YY_NULLPTR)
      yystackp->yytops.yystates[yyn] =
        YYRELOC (yystackp->yyitems, yynewItems,
                 yystackp->yytops.yystates[yyn], yystate);
  YYFREE (yystackp->yyitems);
  yystackp->yyitems = yynewItems;
  yystackp->yynextFree = yynewItems + yysize;
  yystackp->yyspaceLeft = yynewSize - yysize;
}
#endif

static void
yyfreeGLRStack (yyGLRStack* yystackp)
{
  YYFREE (yystackp->yyitems);
  yyfreeStateSet (&yystackp->yytops);
}

/** Assuming that YYS is a GLRState somewhere on *YYSTACKP, update the
 *  splitpoint of *YYSTACKP, if needed, so that it is at least as deep as
 *  YYS.  */
static inline void
yyupdateSplit (yyGLRStack* yystackp, yyGLRState* yys)
{
  if (yystackp->yysplitPoint != YY_NULLPTR && yystackp->yysplitPoint > yys)
    yystackp->yysplitPoint = yys;
}

/** Invalidate stack #YYK in *YYSTACKP.  */
static inline void
yymarkStackDeleted (yyGLRStack* yystackp, size_t yyk)
{
  if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
    yystackp->yylastDeleted = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yystates[yyk] = YY_NULLPTR;
}

/** Undelete the last stack in *YYSTACKP that was marked as deleted.  Can
    only be done once after a deletion, and only when all other stacks have
    been deleted.  */
static void
yyundeleteLastStack (yyGLRStack* yystackp)
{
  if (yystackp->yylastDeleted == YY_NULLPTR || yystackp->yytops.yysize != 0)
    return;
  yystackp->yytops.yystates[0] = yystackp->yylastDeleted;
  yystackp->yytops.yysize = 1;
  YYDPRINTF ((stderr, "Restoring last deleted stack as stack #0.\n"));
  yystackp->yylastDeleted = YY_NULLPTR;
}

static inline void
yyremoveDeletes (yyGLRStack* yystackp)
{
  size_t yyi, yyj;
  yyi = yyj = 0;
  while (yyj < yystackp->yytops.yysize)
    {
      if (yystackp->yytops.yystates[yyi] == YY_NULLPTR)
        {
          if (yyi == yyj)
            {
              YYDPRINTF ((stderr, "Removing dead stacks.\n"));
            }
          yystackp->yytops.yysize -= 1;
        }
      else
        {
          yystackp->yytops.yystates[yyj] = yystackp->yytops.yystates[yyi];
          /* In the current implementation, it's unnecessary to copy
             yystackp->yytops.yylookaheadNeeds[yyi] since, after
             yyremoveDeletes returns, the parser immediately either enters
             deterministic operation or shifts a token.  However, it doesn't
             hurt, and the code might evolve to need it.  */
          yystackp->yytops.yylookaheadNeeds[yyj] =
            yystackp->yytops.yylookaheadNeeds[yyi];
          if (yyj != yyi)
            {
              YYDPRINTF ((stderr, "Rename stack %lu -> %lu.\n",
                          (unsigned long int) yyi, (unsigned long int) yyj));
            }
          yyj += 1;
        }
      yyi += 1;
    }
}

/** Shift to a new state on stack #YYK of *YYSTACKP, corresponding to LR
 * state YYLRSTATE, at input position YYPOSN, with (resolved) semantic
 * value *YYVALP and source location *YYLOCP.  */
static inline void
yyglrShift (yyGLRStack* yystackp, size_t yyk, yyStateNum yylrState,
            size_t yyposn,
            YYSTYPE* yyvalp, YYLTYPE* yylocp)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yytrue;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yysval = *yyvalp;
  yynewState->yyloc = *yylocp;
  yystackp->yytops.yystates[yyk] = yynewState;

  YY_RESERVE_GLRSTACK (yystackp);
}

/** Shift stack #YYK of *YYSTACKP, to a new state corresponding to LR
 *  state YYLRSTATE, at input position YYPOSN, with the (unresolved)
 *  semantic value of YYRHS under the action for YYRULE.  */
static inline void
yyglrShiftDefer (yyGLRStack* yystackp, size_t yyk, yyStateNum yylrState,
                 size_t yyposn, yyGLRState* yyrhs, yyRuleNum yyrule)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;
  YYASSERT (yynewState->yyisState);

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yyfalse;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yyfirstVal = YY_NULLPTR;
  yystackp->yytops.yystates[yyk] = yynewState;

  /* Invokes YY_RESERVE_GLRSTACK.  */
  yyaddDeferredAction (yystackp, yyk, yynewState, yyrhs, yyrule);
}

#if !YYDEBUG
# define YY_REDUCE_PRINT(Args)
#else
# define YY_REDUCE_PRINT(Args)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print Args;               \
} while (0)

/*----------------------------------------------------------------------.
| Report that stack #YYK of *YYSTACKP is going to be reduced by YYRULE. |
`----------------------------------------------------------------------*/

static inline void
yy_reduce_print (int yynormal, yyGLRStackItem* yyvsp, size_t yyk,
                 yyRuleNum yyrule)
{
  int yynrhs = yyrhsLength (yyrule);
  int yylow = 1;
  int yyi;
  YYFPRINTF (stderr, "Reducing stack %lu by rule %d (line %lu):\n",
             (unsigned long int) yyk, yyrule - 1,
             (unsigned long int) yyrline[yyrule]);
  if (! yynormal)
    yyfillin (yyvsp, 1, -yynrhs);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyvsp[yyi - yynrhs + 1].yystate.yylrState],
                       &yyvsp[yyi - yynrhs + 1].yystate.yysemantics.yysval
                       , &(((yyGLRStackItem const *)yyvsp)[YYFILL ((yyi + 1) - (yynrhs))].yystate.yyloc)                       );
      if (!yyvsp[yyi - yynrhs + 1].yystate.yyresolved)
        YYFPRINTF (stderr, " (unresolved)");
      YYFPRINTF (stderr, "\n");
    }
}
#endif

/** Pop the symbols consumed by reduction #YYRULE from the top of stack
 *  #YYK of *YYSTACKP, and perform the appropriate semantic action on their
 *  semantic values.  Assumes that all ambiguities in semantic values
 *  have been previously resolved.  Set *YYVALP to the resulting value,
 *  and *YYLOCP to the computed location (if any).  Return value is as
 *  for userAction.  */
static inline YYRESULTTAG
yydoAction (yyGLRStack* yystackp, size_t yyk, yyRuleNum yyrule,
            YYSTYPE* yyvalp, YYLTYPE *yylocp)
{
  int yynrhs = yyrhsLength (yyrule);

  if (yystackp->yysplitPoint == YY_NULLPTR)
    {
      /* Standard special case: single stack.  */
      yyGLRStackItem* yyrhs = (yyGLRStackItem*) yystackp->yytops.yystates[yyk];
      YYASSERT (yyk == 0);
      yystackp->yynextFree -= yynrhs;
      yystackp->yyspaceLeft += yynrhs;
      yystackp->yytops.yystates[0] = & yystackp->yynextFree[-1].yystate;
      YY_REDUCE_PRINT ((1, yyrhs, yyk, yyrule));
      return yyuserAction (yyrule, yynrhs, yyrhs, yystackp,
                           yyvalp, yylocp);
    }
  else
    {
      int yyi;
      yyGLRState* yys;
      yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
      yys = yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred
        = yystackp->yytops.yystates[yyk];
      if (yynrhs == 0)
        /* Set default location.  */
        yyrhsVals[YYMAXRHS + YYMAXLEFT - 1].yystate.yyloc = yys->yyloc;
      for (yyi = 0; yyi < yynrhs; yyi += 1)
        {
          yys = yys->yypred;
          YYASSERT (yys);
        }
      yyupdateSplit (yystackp, yys);
      yystackp->yytops.yystates[yyk] = yys;
      YY_REDUCE_PRINT ((0, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1, yyk, yyrule));
      return yyuserAction (yyrule, yynrhs, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, yyvalp, yylocp);
    }
}

/** Pop items off stack #YYK of *YYSTACKP according to grammar rule YYRULE,
 *  and push back on the resulting nonterminal symbol.  Perform the
 *  semantic action associated with YYRULE and store its value with the
 *  newly pushed state, if YYFORCEEVAL or if *YYSTACKP is currently
 *  unambiguous.  Otherwise, store the deferred semantic action with
 *  the new state.  If the new state would have an identical input
 *  position, LR state, and predecessor to an existing state on the stack,
 *  it is identified with that existing state, eliminating stack #YYK from
 *  *YYSTACKP.  In this case, the semantic value is
 *  added to the options for the existing state's semantic value.
 */
static inline YYRESULTTAG
yyglrReduce (yyGLRStack* yystackp, size_t yyk, yyRuleNum yyrule,
             yybool yyforceEval)
{
  size_t yyposn = yystackp->yytops.yystates[yyk]->yyposn;

  if (yyforceEval || yystackp->yysplitPoint == YY_NULLPTR)
    {
      YYSTYPE yysval;
      YYLTYPE yyloc;

      YYRESULTTAG yyflag = yydoAction (yystackp, yyk, yyrule, &yysval, &yyloc);
      if (yyflag == yyerr && yystackp->yysplitPoint != YY_NULLPTR)
        {
          YYDPRINTF ((stderr, "Parse on stack %lu rejected by rule #%d.\n",
                     (unsigned long int) yyk, yyrule - 1));
        }
      if (yyflag != yyok)
        return yyflag;
      YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyrule], &yysval, &yyloc);
      yyglrShift (yystackp, yyk,
                  yyLRgotoState (yystackp->yytops.yystates[yyk]->yylrState,
                                 yylhsNonterm (yyrule)),
                  yyposn, &yysval, &yyloc);
    }
  else
    {
      size_t yyi;
      int yyn;
      yyGLRState* yys, *yys0 = yystackp->yytops.yystates[yyk];
      yyStateNum yynewLRState;

      for (yys = yystackp->yytops.yystates[yyk], yyn = yyrhsLength (yyrule);
           0 < yyn; yyn -= 1)
        {
          yys = yys->yypred;
          YYASSERT (yys);
        }
      yyupdateSplit (yystackp, yys);
      yynewLRState = yyLRgotoState (yys->yylrState, yylhsNonterm (yyrule));
      YYDPRINTF ((stderr,
                  "Reduced stack %lu by rule #%d; action deferred.  "
                  "Now in state %d.\n",
                  (unsigned long int) yyk, yyrule - 1, yynewLRState));
      for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
        if (yyi != yyk && yystackp->yytops.yystates[yyi] != YY_NULLPTR)
          {
            yyGLRState *yysplit = yystackp->yysplitPoint;
            yyGLRState *yyp = yystackp->yytops.yystates[yyi];
            while (yyp != yys && yyp != yysplit && yyp->yyposn >= yyposn)
              {
                if (yyp->yylrState == yynewLRState && yyp->yypred == yys)
                  {
                    yyaddDeferredAction (yystackp, yyk, yyp, yys0, yyrule);
                    yymarkStackDeleted (yystackp, yyk);
                    YYDPRINTF ((stderr, "Merging stack %lu into stack %lu.\n",
                                (unsigned long int) yyk,
                                (unsigned long int) yyi));
                    return yyok;
                  }
                yyp = yyp->yypred;
              }
          }
      yystackp->yytops.yystates[yyk] = yys;
      yyglrShiftDefer (yystackp, yyk, yynewLRState, yyposn, yys0, yyrule);
    }
  return yyok;
}

static size_t
yysplitStack (yyGLRStack* yystackp, size_t yyk)
{
  if (yystackp->yysplitPoint == YY_NULLPTR)
    {
      YYASSERT (yyk == 0);
      yystackp->yysplitPoint = yystackp->yytops.yystates[yyk];
    }
  if (yystackp->yytops.yysize >= yystackp->yytops.yycapacity)
    {
      yyGLRState** yynewStates;
      yybool* yynewLookaheadNeeds;

      yynewStates = YY_NULLPTR;

      if (yystackp->yytops.yycapacity
          > (YYSIZEMAX / (2 * sizeof yynewStates[0])))
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yycapacity *= 2;

      yynewStates =
        (yyGLRState**) YYREALLOC (yystackp->yytops.yystates,
                                  (yystackp->yytops.yycapacity
                                   * sizeof yynewStates[0]));
      if (yynewStates == YY_NULLPTR)
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yystates = yynewStates;

      yynewLookaheadNeeds =
        (yybool*) YYREALLOC (yystackp->yytops.yylookaheadNeeds,
                             (yystackp->yytops.yycapacity
                              * sizeof yynewLookaheadNeeds[0]));
      if (yynewLookaheadNeeds == YY_NULLPTR)
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yylookaheadNeeds = yynewLookaheadNeeds;
    }
  yystackp->yytops.yystates[yystackp->yytops.yysize]
    = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yylookaheadNeeds[yystackp->yytops.yysize]
    = yystackp->yytops.yylookaheadNeeds[yyk];
  yystackp->yytops.yysize += 1;
  return yystackp->yytops.yysize-1;
}

/** True iff YYY0 and YYY1 represent identical options at the top level.
 *  That is, they represent the same rule applied to RHS symbols
 *  that produce the same terminal symbols.  */
static yybool
yyidenticalOptions (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  if (yyy0->yyrule == yyy1->yyrule)
    {
      yyGLRState *yys0, *yys1;
      int yyn;
      for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
           yyn = yyrhsLength (yyy0->yyrule);
           yyn > 0;
           yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
        if (yys0->yyposn != yys1->yyposn)
          return yyfalse;
      return yytrue;
    }
  else
    return yyfalse;
}

/** Assuming identicalOptions (YYY0,YYY1), destructively merge the
 *  alternative semantic values for the RHS-symbols of YYY1 and YYY0.  */
static void
yymergeOptionSets (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  yyGLRState *yys0, *yys1;
  int yyn;
  for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
       yyn = yyrhsLength (yyy0->yyrule);
       yyn > 0;
       yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
    {
      if (yys0 == yys1)
        break;
      else if (yys0->yyresolved)
        {
          yys1->yyresolved = yytrue;
          yys1->yysemantics.yysval = yys0->yysemantics.yysval;
        }
      else if (yys1->yyresolved)
        {
          yys0->yyresolved = yytrue;
          yys0->yysemantics.yysval = yys1->yysemantics.yysval;
        }
      else
        {
          yySemanticOption** yyz0p = &yys0->yysemantics.yyfirstVal;
          yySemanticOption* yyz1 = yys1->yysemantics.yyfirstVal;
          while (yytrue)
            {
              if (yyz1 == *yyz0p || yyz1 == YY_NULLPTR)
                break;
              else if (*yyz0p == YY_NULLPTR)
                {
                  *yyz0p = yyz1;
                  break;
                }
              else if (*yyz0p < yyz1)
                {
                  yySemanticOption* yyz = *yyz0p;
                  *yyz0p = yyz1;
                  yyz1 = yyz1->yynext;
                  (*yyz0p)->yynext = yyz;
                }
              yyz0p = &(*yyz0p)->yynext;
            }
          yys1->yysemantics.yyfirstVal = yys0->yysemantics.yyfirstVal;
        }
    }
}

/** Y0 and Y1 represent two possible actions to take in a given
 *  parsing state; return 0 if no combination is possible,
 *  1 if user-mergeable, 2 if Y0 is preferred, 3 if Y1 is preferred.  */
static int
yypreference (yySemanticOption* y0, yySemanticOption* y1)
{
  yyRuleNum r0 = y0->yyrule, r1 = y1->yyrule;
  int p0 = yydprec[r0], p1 = yydprec[r1];

  if (p0 == p1)
    {
      if (yymerger[r0] == 0 || yymerger[r0] != yymerger[r1])
        return 0;
      else
        return 1;
    }
  if (p0 == 0 || p1 == 0)
    return 0;
  if (p0 < p1)
    return 3;
  if (p1 < p0)
    return 2;
  return 0;
}

static YYRESULTTAG yyresolveValue (yyGLRState* yys,
                                   yyGLRStack* yystackp);


/** Resolve the previous YYN states starting at and including state YYS
 *  on *YYSTACKP. If result != yyok, some states may have been left
 *  unresolved possibly with empty semantic option chains.  Regardless
 *  of whether result = yyok, each state has been left with consistent
 *  data so that yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveStates (yyGLRState* yys, int yyn,
                 yyGLRStack* yystackp)
{
  if (0 < yyn)
    {
      YYASSERT (yys->yypred);
      YYCHK (yyresolveStates (yys->yypred, yyn-1, yystackp));
      if (! yys->yyresolved)
        YYCHK (yyresolveValue (yys, yystackp));
    }
  return yyok;
}

/** Resolve the states for the RHS of YYOPT on *YYSTACKP, perform its
 *  user action, and return the semantic value and location in *YYVALP
 *  and *YYLOCP.  Regardless of whether result = yyok, all RHS states
 *  have been destroyed (assuming the user action destroys all RHS
 *  semantic values if invoked).  */
static YYRESULTTAG
yyresolveAction (yySemanticOption* yyopt, yyGLRStack* yystackp,
                 YYSTYPE* yyvalp, YYLTYPE *yylocp)
{
  yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
  int yynrhs = yyrhsLength (yyopt->yyrule);
  YYRESULTTAG yyflag =
    yyresolveStates (yyopt->yystate, yynrhs, yystackp);
  if (yyflag != yyok)
    {
      yyGLRState *yys;
      for (yys = yyopt->yystate; yynrhs > 0; yys = yys->yypred, yynrhs -= 1)
        yydestroyGLRState ("Cleanup: popping", yys);
      return yyflag;
    }

  yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred = yyopt->yystate;
  if (yynrhs == 0)
    /* Set default location.  */
    yyrhsVals[YYMAXRHS + YYMAXLEFT - 1].yystate.yyloc = yyopt->yystate->yyloc;
  {
    int yychar_current = yychar;
    YYSTYPE yylval_current = yylval;
    YYLTYPE yylloc_current = yylloc;
    yychar = yyopt->yyrawchar;
    yylval = yyopt->yyval;
    yylloc = yyopt->yyloc;
    yyflag = yyuserAction (yyopt->yyrule, yynrhs,
                           yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, yyvalp, yylocp);
    yychar = yychar_current;
    yylval = yylval_current;
    yylloc = yylloc_current;
  }
  return yyflag;
}

#if YYDEBUG
static void
yyreportTree (yySemanticOption* yyx, int yyindent)
{
  int yynrhs = yyrhsLength (yyx->yyrule);
  int yyi;
  yyGLRState* yys;
  yyGLRState* yystates[1 + YYMAXRHS];
  yyGLRState yyleftmost_state;

  for (yyi = yynrhs, yys = yyx->yystate; 0 < yyi; yyi -= 1, yys = yys->yypred)
    yystates[yyi] = yys;
  if (yys == YY_NULLPTR)
    {
      yyleftmost_state.yyposn = 0;
      yystates[0] = &yyleftmost_state;
    }
  else
    yystates[0] = yys;

  if (yyx->yystate->yyposn < yys->yyposn + 1)
    YYFPRINTF (stderr, "%*s%s -> <Rule %d, empty>\n",
               yyindent, "", yytokenName (yylhsNonterm (yyx->yyrule)),
               yyx->yyrule - 1);
  else
    YYFPRINTF (stderr, "%*s%s -> <Rule %d, tokens %lu .. %lu>\n",
               yyindent, "", yytokenName (yylhsNonterm (yyx->yyrule)),
               yyx->yyrule - 1, (unsigned long int) (yys->yyposn + 1),
               (unsigned long int) yyx->yystate->yyposn);
  for (yyi = 1; yyi <= yynrhs; yyi += 1)
    {
      if (yystates[yyi]->yyresolved)
        {
          if (yystates[yyi-1]->yyposn+1 > yystates[yyi]->yyposn)
            YYFPRINTF (stderr, "%*s%s <empty>\n", yyindent+2, "",
                       yytokenName (yystos[yystates[yyi]->yylrState]));
          else
            YYFPRINTF (stderr, "%*s%s <tokens %lu .. %lu>\n", yyindent+2, "",
                       yytokenName (yystos[yystates[yyi]->yylrState]),
                       (unsigned long int) (yystates[yyi-1]->yyposn + 1),
                       (unsigned long int) yystates[yyi]->yyposn);
        }
      else
        yyreportTree (yystates[yyi]->yysemantics.yyfirstVal, yyindent+2);
    }
}
#endif

static YYRESULTTAG
yyreportAmbiguity (yySemanticOption* yyx0,
                   yySemanticOption* yyx1)
{
  YYUSE (yyx0);
  YYUSE (yyx1);

#if YYDEBUG
  YYFPRINTF (stderr, "Ambiguity detected.\n");
  YYFPRINTF (stderr, "Option 1,\n");
  yyreportTree (yyx0, 2);
  YYFPRINTF (stderr, "\nOption 2,\n");
  yyreportTree (yyx1, 2);
  YYFPRINTF (stderr, "\n");
#endif

  yyerror (YY_("syntax is ambiguous"));
  return yyabort;
}

/** Resolve the locations for each of the YYN1 states in *YYSTACKP,
 *  ending at YYS1.  Has no effect on previously resolved states.
 *  The first semantic option of a state is always chosen.  */
static void
yyresolveLocations (yyGLRState* yys1, int yyn1,
                    yyGLRStack *yystackp)
{
  if (0 < yyn1)
    {
      yyresolveLocations (yys1->yypred, yyn1 - 1, yystackp);
      if (!yys1->yyresolved)
        {
          yyGLRStackItem yyrhsloc[1 + YYMAXRHS];
          int yynrhs;
          yySemanticOption *yyoption = yys1->yysemantics.yyfirstVal;
          YYASSERT (yyoption != YY_NULLPTR);
          yynrhs = yyrhsLength (yyoption->yyrule);
          if (yynrhs > 0)
            {
              yyGLRState *yys;
              int yyn;
              yyresolveLocations (yyoption->yystate, yynrhs,
                                  yystackp);
              for (yys = yyoption->yystate, yyn = yynrhs;
                   yyn > 0;
                   yys = yys->yypred, yyn -= 1)
                yyrhsloc[yyn].yystate.yyloc = yys->yyloc;
            }
          else
            {
              /* Both yyresolveAction and yyresolveLocations traverse the GSS
                 in reverse rightmost order.  It is only necessary to invoke
                 yyresolveLocations on a subforest for which yyresolveAction
                 would have been invoked next had an ambiguity not been
                 detected.  Thus the location of the previous state (but not
                 necessarily the previous state itself) is guaranteed to be
                 resolved already.  */
              yyGLRState *yyprevious = yyoption->yystate;
              yyrhsloc[0].yystate.yyloc = yyprevious->yyloc;
            }
          {
            int yychar_current = yychar;
            YYSTYPE yylval_current = yylval;
            YYLTYPE yylloc_current = yylloc;
            yychar = yyoption->yyrawchar;
            yylval = yyoption->yyval;
            yylloc = yyoption->yyloc;
            YYLLOC_DEFAULT ((yys1->yyloc), yyrhsloc, yynrhs);
            yychar = yychar_current;
            yylval = yylval_current;
            yylloc = yylloc_current;
          }
        }
    }
}

/** Resolve the ambiguity represented in state YYS in *YYSTACKP,
 *  perform the indicated actions, and set the semantic value of YYS.
 *  If result != yyok, the chain of semantic options in YYS has been
 *  cleared instead or it has been left unmodified except that
 *  redundant options may have been removed.  Regardless of whether
 *  result = yyok, YYS has been left with consistent data so that
 *  yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveValue (yyGLRState* yys, yyGLRStack* yystackp)
{
  yySemanticOption* yyoptionList = yys->yysemantics.yyfirstVal;
  yySemanticOption* yybest = yyoptionList;
  yySemanticOption** yypp;
  yybool yymerge = yyfalse;
  YYSTYPE yysval;
  YYRESULTTAG yyflag;
  YYLTYPE *yylocp = &yys->yyloc;

  for (yypp = &yyoptionList->yynext; *yypp != YY_NULLPTR; )
    {
      yySemanticOption* yyp = *yypp;

      if (yyidenticalOptions (yybest, yyp))
        {
          yymergeOptionSets (yybest, yyp);
          *yypp = yyp->yynext;
        }
      else
        {
          switch (yypreference (yybest, yyp))
            {
            case 0:
              yyresolveLocations (yys, 1, yystackp);
              return yyreportAmbiguity (yybest, yyp);
              break;
            case 1:
              yymerge = yytrue;
              break;
            case 2:
              break;
            case 3:
              yybest = yyp;
              yymerge = yyfalse;
              break;
            default:
              /* This cannot happen so it is not worth a YYASSERT (yyfalse),
                 but some compilers complain if the default case is
                 omitted.  */
              break;
            }
          yypp = &yyp->yynext;
        }
    }

  if (yymerge)
    {
      yySemanticOption* yyp;
      int yyprec = yydprec[yybest->yyrule];
      yyflag = yyresolveAction (yybest, yystackp, &yysval, yylocp);
      if (yyflag == yyok)
        for (yyp = yybest->yynext; yyp != YY_NULLPTR; yyp = yyp->yynext)
          {
            if (yyprec == yydprec[yyp->yyrule])
              {
                YYSTYPE yysval_other;
                YYLTYPE yydummy;
                yyflag = yyresolveAction (yyp, yystackp, &yysval_other, &yydummy);
                if (yyflag != yyok)
                  {
                    yydestruct ("Cleanup: discarding incompletely merged value for",
                                yystos[yys->yylrState],
                                &yysval, yylocp);
                    break;
                  }
                yyuserMerge (yymerger[yyp->yyrule], &yysval, &yysval_other);
              }
          }
    }
  else
    yyflag = yyresolveAction (yybest, yystackp, &yysval, yylocp);

  if (yyflag == yyok)
    {
      yys->yyresolved = yytrue;
      yys->yysemantics.yysval = yysval;
    }
  else
    yys->yysemantics.yyfirstVal = YY_NULLPTR;
  return yyflag;
}

static YYRESULTTAG
yyresolveStack (yyGLRStack* yystackp)
{
  if (yystackp->yysplitPoint != YY_NULLPTR)
    {
      yyGLRState* yys;
      int yyn;

      for (yyn = 0, yys = yystackp->yytops.yystates[0];
           yys != yystackp->yysplitPoint;
           yys = yys->yypred, yyn += 1)
        continue;
      YYCHK (yyresolveStates (yystackp->yytops.yystates[0], yyn, yystackp
                             ));
    }
  return yyok;
}

static void
yycompressStack (yyGLRStack* yystackp)
{
  yyGLRState* yyp, *yyq, *yyr;

  if (yystackp->yytops.yysize != 1 || yystackp->yysplitPoint == YY_NULLPTR)
    return;

  for (yyp = yystackp->yytops.yystates[0], yyq = yyp->yypred, yyr = YY_NULLPTR;
       yyp != yystackp->yysplitPoint;
       yyr = yyp, yyp = yyq, yyq = yyp->yypred)
    yyp->yypred = yyr;

  yystackp->yyspaceLeft += yystackp->yynextFree - yystackp->yyitems;
  yystackp->yynextFree = ((yyGLRStackItem*) yystackp->yysplitPoint) + 1;
  yystackp->yyspaceLeft -= yystackp->yynextFree - yystackp->yyitems;
  yystackp->yysplitPoint = YY_NULLPTR;
  yystackp->yylastDeleted = YY_NULLPTR;

  while (yyr != YY_NULLPTR)
    {
      yystackp->yynextFree->yystate = *yyr;
      yyr = yyr->yypred;
      yystackp->yynextFree->yystate.yypred = &yystackp->yynextFree[-1].yystate;
      yystackp->yytops.yystates[0] = &yystackp->yynextFree->yystate;
      yystackp->yynextFree += 1;
      yystackp->yyspaceLeft -= 1;
    }
}

static YYRESULTTAG
yyprocessOneStack (yyGLRStack* yystackp, size_t yyk,
                   size_t yyposn)
{
  while (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
    {
      yyStateNum yystate = yystackp->yytops.yystates[yyk]->yylrState;
      YYDPRINTF ((stderr, "Stack %lu Entering state %d\n",
                  (unsigned long int) yyk, yystate));

      YYASSERT (yystate != YYFINAL);

      if (yyisDefaultedState (yystate))
        {
          YYRESULTTAG yyflag;
          yyRuleNum yyrule = yydefaultAction (yystate);
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, "Stack %lu dies.\n",
                          (unsigned long int) yyk));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          yyflag = yyglrReduce (yystackp, yyk, yyrule, yyimmediate[yyrule]);
          if (yyflag == yyerr)
            {
              YYDPRINTF ((stderr,
                          "Stack %lu dies "
                          "(predicate failure or explicit user error).\n",
                          (unsigned long int) yyk));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          if (yyflag != yyok)
            return yyflag;
        }
      else
        {
          yySymbol yytoken;
          int yyaction;
          const short int* yyconflicts;

          yystackp->yytops.yylookaheadNeeds[yyk] = yytrue;
          if (yychar == YYEMPTY)
            {
              YYDPRINTF ((stderr, "Reading a token: "));
              yychar = yylex ();
            }

          if (yychar <= YYEOF)
            {
              yychar = yytoken = YYEOF;
              YYDPRINTF ((stderr, "Now at end of input.\n"));
            }
          else
            {
              yytoken = YYTRANSLATE (yychar);
              YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
            }

          yygetLRActions (yystate, yytoken, &yyaction, &yyconflicts);

          while (*yyconflicts != 0)
            {
              YYRESULTTAG yyflag;
              size_t yynewStack = yysplitStack (yystackp, yyk);
              YYDPRINTF ((stderr, "Splitting off stack %lu from %lu.\n",
                          (unsigned long int) yynewStack,
                          (unsigned long int) yyk));
              yyflag = yyglrReduce (yystackp, yynewStack,
                                    *yyconflicts,
                                    yyimmediate[*yyconflicts]);
              if (yyflag == yyok)
                YYCHK (yyprocessOneStack (yystackp, yynewStack,
                                          yyposn));
              else if (yyflag == yyerr)
                {
                  YYDPRINTF ((stderr, "Stack %lu dies.\n",
                              (unsigned long int) yynewStack));
                  yymarkStackDeleted (yystackp, yynewStack);
                }
              else
                return yyflag;
              yyconflicts += 1;
            }

          if (yyisShiftAction (yyaction))
            break;
          else if (yyisErrorAction (yyaction))
            {
              YYDPRINTF ((stderr, "Stack %lu dies.\n",
                          (unsigned long int) yyk));
              yymarkStackDeleted (yystackp, yyk);
              break;
            }
          else
            {
              YYRESULTTAG yyflag = yyglrReduce (yystackp, yyk, -yyaction,
                                                yyimmediate[-yyaction]);
              if (yyflag == yyerr)
                {
                  YYDPRINTF ((stderr,
                              "Stack %lu dies "
                              "(predicate failure or explicit user error).\n",
                              (unsigned long int) yyk));
                  yymarkStackDeleted (yystackp, yyk);
                  break;
                }
              else if (yyflag != yyok)
                return yyflag;
            }
        }
    }
  return yyok;
}

static void
yyreportSyntaxError (yyGLRStack* yystackp)
{
  if (yystackp->yyerrState != 0)
    return;
#if ! YYERROR_VERBOSE
  yyerror (YY_("syntax error"));
#else
  {
  yySymbol yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);
  size_t yysize0 = yytnamerr (YY_NULLPTR, yytokenName (yytoken));
  size_t yysize = yysize0;
  yybool yysize_overflow = yyfalse;
  char* yymsg = YY_NULLPTR;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected").  */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[yystackp->yytops.yystates[0]->yylrState];
      yyarg[yycount++] = yytokenName (yytoken);
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for this
             state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;
          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytokenName (yyx);
                {
                  size_t yysz = yysize + yytnamerr (YY_NULLPTR, yytokenName (yyx));
                  yysize_overflow |= yysz < yysize;
                  yysize = yysz;
                }
              }
        }
    }

  switch (yycount)
    {
#define YYCASE_(N, S)                   \
      case N:                           \
        yyformat = S;                   \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  {
    size_t yysz = yysize + strlen (yyformat);
    yysize_overflow |= yysz < yysize;
    yysize = yysz;
  }

  if (!yysize_overflow)
    yymsg = (char *) YYMALLOC (yysize);

  if (yymsg)
    {
      char *yyp = yymsg;
      int yyi = 0;
      while ((*yyp = *yyformat))
        {
          if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
            {
              yyp += yytnamerr (yyp, yyarg[yyi++]);
              yyformat += 2;
            }
          else
            {
              yyp++;
              yyformat++;
            }
        }
      yyerror (yymsg);
      YYFREE (yymsg);
    }
  else
    {
      yyerror (YY_("syntax error"));
      yyMemoryExhausted (yystackp);
    }
  }
#endif /* YYERROR_VERBOSE */
  yynerrs += 1;
}

/* Recover from a syntax error on *YYSTACKP, assuming that *YYSTACKP->YYTOKENP,
   yylval, and yylloc are the syntactic category, semantic value, and location
   of the lookahead.  */
static void
yyrecoverSyntaxError (yyGLRStack* yystackp)
{
  size_t yyk;
  int yyj;

  if (yystackp->yyerrState == 3)
    /* We just shifted the error token and (perhaps) took some
       reductions.  Skip tokens until we can proceed.  */
    while (yytrue)
      {
        yySymbol yytoken;
        if (yychar == YYEOF)
          yyFail (yystackp, YY_NULLPTR);
        if (yychar != YYEMPTY)
          {
            /* We throw away the lookahead, but the error range
               of the shifted error token must take it into account.  */
            yyGLRState *yys = yystackp->yytops.yystates[0];
            yyGLRStackItem yyerror_range[3];
            yyerror_range[1].yystate.yyloc = yys->yyloc;
            yyerror_range[2].yystate.yyloc = yylloc;
            YYLLOC_DEFAULT ((yys->yyloc), yyerror_range, 2);
            yytoken = YYTRANSLATE (yychar);
            yydestruct ("Error: discarding",
                        yytoken, &yylval, &yylloc);
          }
        YYDPRINTF ((stderr, "Reading a token: "));
        yychar = yylex ();
        if (yychar <= YYEOF)
          {
            yychar = yytoken = YYEOF;
            YYDPRINTF ((stderr, "Now at end of input.\n"));
          }
        else
          {
            yytoken = YYTRANSLATE (yychar);
            YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
          }
        yyj = yypact[yystackp->yytops.yystates[0]->yylrState];
        if (yypact_value_is_default (yyj))
          return;
        yyj += yytoken;
        if (yyj < 0 || YYLAST < yyj || yycheck[yyj] != yytoken)
          {
            if (yydefact[yystackp->yytops.yystates[0]->yylrState] != 0)
              return;
          }
        else if (! yytable_value_is_error (yytable[yyj]))
          return;
      }

  /* Reduce to one stack.  */
  for (yyk = 0; yyk < yystackp->yytops.yysize; yyk += 1)
    if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
      break;
  if (yyk >= yystackp->yytops.yysize)
    yyFail (yystackp, YY_NULLPTR);
  for (yyk += 1; yyk < yystackp->yytops.yysize; yyk += 1)
    yymarkStackDeleted (yystackp, yyk);
  yyremoveDeletes (yystackp);
  yycompressStack (yystackp);

  /* Now pop stack until we find a state that shifts the error token.  */
  yystackp->yyerrState = 3;
  while (yystackp->yytops.yystates[0] != YY_NULLPTR)
    {
      yyGLRState *yys = yystackp->yytops.yystates[0];
      yyj = yypact[yys->yylrState];
      if (! yypact_value_is_default (yyj))
        {
          yyj += YYTERROR;
          if (0 <= yyj && yyj <= YYLAST && yycheck[yyj] == YYTERROR
              && yyisShiftAction (yytable[yyj]))
            {
              /* Shift the error token.  */
              /* First adjust its location.*/
              YYLTYPE yyerrloc;
              yystackp->yyerror_range[2].yystate.yyloc = yylloc;
              YYLLOC_DEFAULT (yyerrloc, (yystackp->yyerror_range), 2);
              YY_SYMBOL_PRINT ("Shifting", yystos[yytable[yyj]],
                               &yylval, &yyerrloc);
              yyglrShift (yystackp, 0, yytable[yyj],
                          yys->yyposn, &yylval, &yyerrloc);
              yys = yystackp->yytops.yystates[0];
              break;
            }
        }
      yystackp->yyerror_range[1].yystate.yyloc = yys->yyloc;
      if (yys->yypred != YY_NULLPTR)
        yydestroyGLRState ("Error: popping", yys);
      yystackp->yytops.yystates[0] = yys->yypred;
      yystackp->yynextFree -= 1;
      yystackp->yyspaceLeft += 1;
    }
  if (yystackp->yytops.yystates[0] == YY_NULLPTR)
    yyFail (yystackp, YY_NULLPTR);
}

#define YYCHK1(YYE)                                                          \
  do {                                                                       \
    switch (YYE) {                                                           \
    case yyok:                                                               \
      break;                                                                 \
    case yyabort:                                                            \
      goto yyabortlab;                                                       \
    case yyaccept:                                                           \
      goto yyacceptlab;                                                      \
    case yyerr:                                                              \
      goto yyuser_error;                                                     \
    default:                                                                 \
      goto yybuglab;                                                         \
    }                                                                        \
  } while (0)

/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
  int yyresult;
  yyGLRStack yystack;
  yyGLRStack* const yystackp = &yystack;
  size_t yyposn;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY;
  yylval = yyval_default;
  yylloc = yyloc_default;

  if (! yyinitGLRStack (yystackp, YYINITDEPTH))
    goto yyexhaustedlab;
  switch (YYSETJMP (yystack.yyexception_buffer))
    {
    case 0: break;
    case 1: goto yyabortlab;
    case 2: goto yyexhaustedlab;
    default: goto yybuglab;
    }
  yyglrShift (&yystack, 0, 0, 0, &yylval, &yylloc);
  yyposn = 0;

  while (yytrue)
    {
      /* For efficiency, we have two loops, the first of which is
         specialized to deterministic operation (single stack, no
         potential ambiguity).  */
      /* Standard mode */
      while (yytrue)
        {
          yyRuleNum yyrule;
          int yyaction;
          const short int* yyconflicts;

          yyStateNum yystate = yystack.yytops.yystates[0]->yylrState;
          YYDPRINTF ((stderr, "Entering state %d\n", yystate));
          if (yystate == YYFINAL)
            goto yyacceptlab;
          if (yyisDefaultedState (yystate))
            {
              yyrule = yydefaultAction (yystate);
              if (yyrule == 0)
                {
               yystack.yyerror_range[1].yystate.yyloc = yylloc;
                  yyreportSyntaxError (&yystack);
                  goto yyuser_error;
                }
              YYCHK1 (yyglrReduce (&yystack, 0, yyrule, yytrue));
            }
          else
            {
              yySymbol yytoken;
              if (yychar == YYEMPTY)
                {
                  YYDPRINTF ((stderr, "Reading a token: "));
                  yychar = yylex ();
                }

              if (yychar <= YYEOF)
                {
                  yychar = yytoken = YYEOF;
                  YYDPRINTF ((stderr, "Now at end of input.\n"));
                }
              else
                {
                  yytoken = YYTRANSLATE (yychar);
                  YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
                }

              yygetLRActions (yystate, yytoken, &yyaction, &yyconflicts);
              if (*yyconflicts != 0)
                break;
              if (yyisShiftAction (yyaction))
                {
                  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
                  yychar = YYEMPTY;
                  yyposn += 1;
                  yyglrShift (&yystack, 0, yyaction, yyposn, &yylval, &yylloc);
                  if (0 < yystack.yyerrState)
                    yystack.yyerrState -= 1;
                }
              else if (yyisErrorAction (yyaction))
                {
               yystack.yyerror_range[1].yystate.yyloc = yylloc;
                  yyreportSyntaxError (&yystack);
                  goto yyuser_error;
                }
              else
                YYCHK1 (yyglrReduce (&yystack, 0, -yyaction, yytrue));
            }
        }

      while (yytrue)
        {
          yySymbol yytoken_to_shift;
          size_t yys;

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            yystackp->yytops.yylookaheadNeeds[yys] = yychar != YYEMPTY;

          /* yyprocessOneStack returns one of three things:

              - An error flag.  If the caller is yyprocessOneStack, it
                immediately returns as well.  When the caller is finally
                yyparse, it jumps to an error label via YYCHK1.

              - yyok, but yyprocessOneStack has invoked yymarkStackDeleted
                (&yystack, yys), which sets the top state of yys to NULL.  Thus,
                yyparse's following invocation of yyremoveDeletes will remove
                the stack.

              - yyok, when ready to shift a token.

             Except in the first case, yyparse will invoke yyremoveDeletes and
             then shift the next token onto all remaining stacks.  This
             synchronization of the shift (that is, after all preceding
             reductions on all stacks) helps prevent double destructor calls
             on yylval in the event of memory exhaustion.  */

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            YYCHK1 (yyprocessOneStack (&yystack, yys, yyposn));
          yyremoveDeletes (&yystack);
          if (yystack.yytops.yysize == 0)
            {
              yyundeleteLastStack (&yystack);
              if (yystack.yytops.yysize == 0)
                yyFail (&yystack, YY_("syntax error"));
              YYCHK1 (yyresolveStack (&yystack));
              YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));
           yystack.yyerror_range[1].yystate.yyloc = yylloc;
              yyreportSyntaxError (&yystack);
              goto yyuser_error;
            }

          /* If any yyglrShift call fails, it will fail after shifting.  Thus,
             a copy of yylval will already be on stack 0 in the event of a
             failure in the following loop.  Thus, yychar is set to YYEMPTY
             before the loop to make sure the user destructor for yylval isn't
             called twice.  */
          yytoken_to_shift = YYTRANSLATE (yychar);
          yychar = YYEMPTY;
          yyposn += 1;
          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            {
              int yyaction;
              const short int* yyconflicts;
              yyStateNum yystate = yystack.yytops.yystates[yys]->yylrState;
              yygetLRActions (yystate, yytoken_to_shift, &yyaction,
                              &yyconflicts);
              /* Note that yyconflicts were handled by yyprocessOneStack.  */
              YYDPRINTF ((stderr, "On stack %lu, ", (unsigned long int) yys));
              YY_SYMBOL_PRINT ("shifting", yytoken_to_shift, &yylval, &yylloc);
              yyglrShift (&yystack, yys, yyaction, yyposn,
                          &yylval, &yylloc);
              YYDPRINTF ((stderr, "Stack %lu now in state #%d\n",
                          (unsigned long int) yys,
                          yystack.yytops.yystates[yys]->yylrState));
            }

          if (yystack.yytops.yysize == 1)
            {
              YYCHK1 (yyresolveStack (&yystack));
              YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));
              yycompressStack (&yystack);
              break;
            }
        }
      continue;
    yyuser_error:
      yyrecoverSyntaxError (&yystack);
      yyposn = yystack.yytops.yystates[0]->yyposn;
    }

 yyacceptlab:
  yyresult = 0;
  goto yyreturn;

 yybuglab:
  YYASSERT (yyfalse);
  goto yyabortlab;

 yyabortlab:
  yyresult = 1;
  goto yyreturn;

 yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;

 yyreturn:
  if (yychar != YYEMPTY)
    yydestruct ("Cleanup: discarding lookahead",
                YYTRANSLATE (yychar), &yylval, &yylloc);

  /* If the stack is well-formed, pop the stack until it is empty,
     destroying its entries as we go.  But free the stack regardless
     of whether it is well-formed.  */
  if (yystack.yyitems)
    {
      yyGLRState** yystates = yystack.yytops.yystates;
      if (yystates)
        {
          size_t yysize = yystack.yytops.yysize;
          size_t yyk;
          for (yyk = 0; yyk < yysize; yyk += 1)
            if (yystates[yyk])
              {
                while (yystates[yyk])
                  {
                    yyGLRState *yys = yystates[yyk];
                 yystack.yyerror_range[1].yystate.yyloc = yys->yyloc;
                  if (yys->yypred != YY_NULLPTR)
                      yydestroyGLRState ("Cleanup: popping", yys);
                    yystates[yyk] = yys->yypred;
                    yystack.yynextFree -= 1;
                    yystack.yyspaceLeft += 1;
                  }
                break;
              }
        }
      yyfreeGLRStack (&yystack);
    }

  return yyresult;
}

/* DEBUGGING ONLY */
#if YYDEBUG
static void
yy_yypstack (yyGLRState* yys)
{
  if (yys->yypred)
    {
      yy_yypstack (yys->yypred);
      YYFPRINTF (stderr, " -> ");
    }
  YYFPRINTF (stderr, "%d@%lu", yys->yylrState,
             (unsigned long int) yys->yyposn);
}

static void
yypstates (yyGLRState* yyst)
{
  if (yyst == YY_NULLPTR)
    YYFPRINTF (stderr, "<null>");
  else
    yy_yypstack (yyst);
  YYFPRINTF (stderr, "\n");
}

static void
yypstack (yyGLRStack* yystackp, size_t yyk)
{
  yypstates (yystackp->yytops.yystates[yyk]);
}

#define YYINDEX(YYX)                                                         \
    ((YYX) == YY_NULLPTR ? -1 : (yyGLRStackItem*) (YYX) - yystackp->yyitems)


static void
yypdumpstack (yyGLRStack* yystackp)
{
  yyGLRStackItem* yyp;
  size_t yyi;
  for (yyp = yystackp->yyitems; yyp < yystackp->yynextFree; yyp += 1)
    {
      YYFPRINTF (stderr, "%3lu. ",
                 (unsigned long int) (yyp - yystackp->yyitems));
      if (*(yybool *) yyp)
        {
          YYASSERT (yyp->yystate.yyisState);
          YYASSERT (yyp->yyoption.yyisState);
          YYFPRINTF (stderr, "Res: %d, LR State: %d, posn: %lu, pred: %ld",
                     yyp->yystate.yyresolved, yyp->yystate.yylrState,
                     (unsigned long int) yyp->yystate.yyposn,
                     (long int) YYINDEX (yyp->yystate.yypred));
          if (! yyp->yystate.yyresolved)
            YYFPRINTF (stderr, ", firstVal: %ld",
                       (long int) YYINDEX (yyp->yystate
                                             .yysemantics.yyfirstVal));
        }
      else
        {
          YYASSERT (!yyp->yystate.yyisState);
          YYASSERT (!yyp->yyoption.yyisState);
          YYFPRINTF (stderr, "Option. rule: %d, state: %ld, next: %ld",
                     yyp->yyoption.yyrule - 1,
                     (long int) YYINDEX (yyp->yyoption.yystate),
                     (long int) YYINDEX (yyp->yyoption.yynext));
        }
      YYFPRINTF (stderr, "\n");
    }
  YYFPRINTF (stderr, "Tops:");
  for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
    YYFPRINTF (stderr, "%lu: %ld; ", (unsigned long int) yyi,
               (long int) YYINDEX (yystackp->yytops.yystates[yyi]));
  YYFPRINTF (stderr, "\n");
}
#endif

#undef yylval
#undef yychar
#undef yynerrs
#undef yylloc



#line 344 "mini.y" /* glr.c:2584  */

