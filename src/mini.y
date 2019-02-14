%{
#include <stdio.h>
#include "main.h"
#include "tree.h"

extern PROGRAM *root;
int yylex();
void yyerror(const char *s) { fprintf(stderr, "Error: %s\n", s); }
%}
%locations
%error-verbose



%union {
    int intval;
    struct TYPE *type;
    char *identifier;
    char *stringval;
    float floatval;
    struct EXP *exp;
    struct STATEMENT *stmts;
    struct PROGRAM *prog;
}

%type <exp> exp
%type <stmts> stmts stmt dcl ifstmt elseifstmts elseifstmt elsestmt  
%type <prog> start
%type <type> Type
%type <type> tINT tFLOAT tBOOLEAN tSTRING

%token <stringval> tSTRINGVAL 
%token <intval> tINTVAL
%token <floatval> tFLOATVAL
%token <identifier> tIDENTIFIER
%token tVAR tFLOAT tINT tSTRING tBOOLEAN tIF tELSE tWHILE tREAD tPRINT tTRUE tFALSE
%token tCOLON tASSIGN tSEMICOLON tLEFTPAREN tRIGHTPAREN tLEFTBRACE tRIGHTBRACE tBANG
%token tPLUS tMINUS tTIMES tDIV tEQUALS tNOTEQUALS tGREATEREQUALS tLESSEQUALS tGREATER tLESS tAND tOR
%token tSTRUCT tSELECT tRETURN tRANGE tPACKAGE tMAP tINTERFACE tIMPORT tGOTO tGO tFOR tDEFER tDEFAULT
%token tCONTINUE tCONST tCHAN tCASE tBREAK tFALLTHROUGH tSWITCH tTYPE tPRINTLN tAPPEND tLEN tCAP
%token tMOD tBITWISEAND tBITWISEOR tBITWISEXOR tBITCLEAR tLEFTSHIFT tRIGHTSHIFT tPLUSEQUAL
%token tMINUSEQUAL tTIMESEQUAL tDIVEQUAL tMODEQUAL tPLUSPLUS tMINUSMINUS tANDEQUAL tOREQUAL 
%token tXOREQUAL tLEFTSHIFTEQUAL tRIGHTSHIFTEQUAL tBITCLEAREQUAL tCOLONEQUAL tDOTDOTDOT tCOMMA
%token tDOT tLEFTSQUAREBRACKET tRIGHTSQUAREBRACKET tRUNEVAL tSTRINGITPVAL tSTRINGRAWVAL


%left tOR
%left tAND
%left tEQUALS tNOTEQUALS
%left tGREATEREQUALS tLESSEQUALS tGREATER tLESS
%left tPLUS tMINUS
%left tTIMES tDIV
%left tBANG UMINUS


%start prog
%%
Type: tINT { $$ = $1; }
    | tFLOAT { $$ = $1; }
    | tBOOLEAN { $$ = $1; }
    | tSTRING { $$ = $1; }
;

prog: start { root=$1; }
;

start: stmts { $$=makeProgram($1); }
;

stmts: { $$ = NULL; }
    | stmt stmts {  $$ = makeStatememnt_list($1, $2, @1.first_line); }
;


dcl: tVAR exp tCOLON Type tSEMICOLON { $$ = makeStatememnt_dcl($2,$4,NULL, @1.first_line); }
    | tVAR exp tCOLON Type tASSIGN exp tSEMICOLON { $$ = makeStatememnt_dcl($2,$4,$6, @1.first_line); }
;

stmt: tREAD tLEFTPAREN exp tRIGHTPAREN tSEMICOLON { $$=makeStatememnt_read($3, @1.first_line); }
    | tPRINT tLEFTPAREN exp tRIGHTPAREN tSEMICOLON { $$=makeStatememnt_print($3, @1.first_line); }
    | exp tASSIGN exp tSEMICOLON { $$=makeStatement_assign($1,$3, @1.first_line); }
    | tWHILE tLEFTPAREN exp tRIGHTPAREN tLEFTBRACE stmts tRIGHTBRACE {  $$= makeStatememnt_while($3, $6, @1.first_line);}
    | ifstmt
    | dcl
;

elseifstmt: tELSE tIF tLEFTPAREN exp tRIGHTPAREN tLEFTBRACE stmts tRIGHTBRACE { $$= makeStatememnt_elseifstmt($4,$7, @1.first_line);  }
;

elseifstmts: {$$=NULL;}
    | elseifstmts elseifstmt {$$ = makeStatememnt_elseifstmt_list($1,$2, @1.first_line);  }
;

elsestmt: {$$ = NULL;}
    | tELSE tLEFTBRACE stmts tRIGHTBRACE { $$=makeStatememnt_else($3, @1.first_line);  }
;

ifstmt: tIF tLEFTPAREN exp tRIGHTPAREN tLEFTBRACE stmts tRIGHTBRACE elseifstmts elsestmt { $$ = makeStatememnt_if($3,$6,$8,$9, @1.first_line);  }
;

exp: tIDENTIFIER { $$ = makeEXP_ID($1, @1.first_line);  }
    | tINTVAL { $$ = makeEXP_intLiteral($1, @1.first_line); }
    | tSTRINGVAL { $$ = makeEXP_StringLiteral($1, @1.first_line); }
    | tFLOATVAL {$$ = makeEXP_FloatLiteral($1, @1.first_line); }
    | tTRUE { $$ = makeEXP_BooleanLiteral(1, @1.first_line); }
    | tFALSE { $$ = makeEXP_BooleanLiteral(0, @1.first_line); }
    | exp tPLUS exp { $$ = makeEXP_plus($1, $3, @1.first_line);  }
    | exp tMINUS exp { $$ = makeEXP_minus($1, $3, @1.first_line); }
    | exp tTIMES exp { $$ = makeEXP_times($1, $3, @1.first_line); }
    | exp tDIV exp { $$ = makeEXP_div($1, $3, @1.first_line); }
    | exp tEQUALS exp { $$ = makeEXP_eq($1, $3, @1.first_line); }
    | exp tNOTEQUALS exp { $$ = makeEXP_neq($1, $3, @1.first_line); }
    | exp tGREATEREQUALS exp { $$ = makeEXP_geq($1, $3, @1.first_line); }
    | exp tLESSEQUALS exp { $$ = makeEXP_leq($1, $3, @1.first_line); }
    | exp tGREATER exp { $$ = makeEXP_greater($1, $3, @1.first_line); }
    | exp tLESS exp { $$ = makeEXP_less($1, $3, @1.first_line); }
    | exp tAND exp { $$ = makeEXP_and($1, $3, @1.first_line); }
    | exp tOR exp { $$ = makeEXP_or($1, $3, @1.first_line); }
    | tLEFTPAREN exp tRIGHTPAREN { $$ = makeEXP_Paren($2, @1.first_line); }
    | tBANG exp { $$ = makeEXP_Bang($2, @1.first_line); }
    | tMINUS exp %prec UMINUS { $$ = makeEXP_Neg($2, @1.first_line); }
;

%%