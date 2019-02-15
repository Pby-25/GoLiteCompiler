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

// %type <exp> exp
// %type <stmts> stmts stmt dcl ifstmt elseifstmts elseifstmt elsestmt  
// %type <prog> start
// %type <type> Type
// %type <type> tINT tFLOAT64 tBOOLEAN tSTRING

// %token <stringval> tSTRINGITPVAL tSTRINGRAWVAL 
%token <intval> tINTVAL
%token <floatval> tFLOATVAL
%token <identifier> tIDENTIFIER
%token tVAR tFLOAT64 tINT tSTRING tBOOLEAN tIF tELSE tWHILE tREAD tPRINT tTRUE tFALSE
%token tCOLON tASSIGN tSEMICOLON tLEFTPAREN tRIGHTPAREN tLEFTBRACE tRIGHTBRACE tBANG
%token tPLUS tMINUS tTIMES tDIV tEQUALS tNOTEQUALS tGREATEREQUALS tLESSEQUALS tGREATER tLESS tAND tOR
%token tSTRUCT tSELECT tRETURN tRANGE tPACKAGE tMAP tINTERFACE tIMPORT tGOTO tGO tFOR tDEFER tDEFAULT
%token tCONTINUE tCONST tCHAN tCASE tBREAK tFALLTHROUGH tSWITCH tTYPE tPRINTLN tAPPEND tLEN tCAP
%token tMOD tBITWISEAND tBITWISEOR tBITWISEXOR tBITCLEAR tLEFTSHIFT tRIGHTSHIFT tPLUSEQUAL
%token tMINUSEQUAL tTIMESEQUAL tDIVEQUAL tMODEQUAL tPLUSPLUS tMINUSMINUS tANDEQUAL tOREQUAL 
%token tXOREQUAL tLEFTSHIFTEQUAL tRIGHTSHIFTEQUAL tBITCLEAREQUAL tCOLONEQUAL tDOTDOTDOT tCOMMA
%token tDOT tLEFTSQUAREBRACKET tRIGHTSQUAREBRACKET tRUNEVAL tSTRINGITPVAL tSTRINGRAWVAL tFUNC


%left tOR
%left tAND
%left tEQUALS tNOTEQUALS
%left tGREATEREQUALS tLESSEQUALS tGREATER tLESS
%left tPLUS tMINUS
%left tTIMES tDIV
%left tBANG UMINUS


%start prog
%%
Slices: tLEFTSQUAREBRACKET tRIGHTSQUAREBRACKET
    | tLEFTSQUAREBRACKET exp tRIGHTSQUAREBRACKET
;

Type: tINT 
    | tFLOAT64
    | tBOOLEAN
    | tSTRING
    | Slices Type
;

prog: start
;

start: stmts
;

package: tPACKAGE tIDENTIFIER tSEMICOLON 
;

import: tIMPORT tSTRINGITPVAL tSEMICOLON 
;

dcl_id_list: { }
    | tCOMMA exp dcl_id_list 
;

var_dcl: tVAR var_dcl_details   
    | tVAR tLEFTPAREN var_dcl_details_list tRIGHTPAREN tSEMICOLON 
;

var_dcl_details_list:{}
    | var_dcl_details var_dcl_details_list
;

var_dcl_details: exp dcl_id_list Type tSEMICOLON 
    | exp dcl_id_list Type tASSIGN exp dcl_id_list tSEMICOLON 
    | exp dcl_id_list tASSIGN exp dcl_id_list tSEMICOLON 
;

type_dcl: tTYPE type_dcl_details_list
    | tTYPE tLEFTPAREN type_dcl_details_list tRIGHTPAREN tSEMICOLON
;

type_dcl_details_list: {}
    | type_dcl_details type_dcl_details_list
;

type_dcl_details: exp Type tSEMICOLON 
    | exp tSTRUCT tLEFTBRACE type_dcl_mul_var tRIGHTBRACE tSEMICOLON
;

type_dcl_mul_var: {}
    | exp dcl_id_list Type tSEMICOLON type_dcl_mul_var
;

func_dcl: tFUNC exp tLEFTPAREN func_param tRIGHTPAREN tLEFTBRACE stmt stmts tRIGHTBRACE tSEMICOLON  
;

func_param: {}
    | exp dcl_id_list Type func_param 
    | tCOMMA func_param
    | exp Type func_param 
    | tCOMMA func_param
;

stmts: {}
    | stmt stmts 
;

stmt: tREAD tLEFTPAREN exp tRIGHTPAREN tSEMICOLON
    | tPRINT tLEFTPAREN exp tRIGHTPAREN tSEMICOLON
    | exp tASSIGN exp tSEMICOLON
    | tWHILE tLEFTPAREN exp tRIGHTPAREN tLEFTBRACE stmts tRIGHTBRACE
    | ifstmt
    | var_dcl
    | type_dcl
    | package
    | import
    | func_dcl
    | tLEFTBRACE stmts tRIGHTBRACE
;

elseifstmt: tELSE tIF tLEFTPAREN exp tRIGHTPAREN tLEFTBRACE stmts tRIGHTBRACE
;

elseifstmts: {}
    | elseifstmts elseifstmt
;

elsestmt: {}
    | tELSE tLEFTBRACE stmts tRIGHTBRACE
;

ifstmt: tIF tLEFTPAREN exp tRIGHTPAREN tLEFTBRACE stmts tRIGHTBRACE elseifstmts elsestmt
;

exp: tIDENTIFIER 
    | tINTVAL
    | tSTRINGITPVAL 
    | tFLOATVAL 
    | tTRUE 
    | tFALSE
    | exp tPLUS exp
    | exp tMINUS exp
    | exp tTIMES exp
    | exp tDIV exp
    | exp tEQUALS exp
    | exp tNOTEQUALS exp
    | exp tGREATEREQUALS exp
    | exp tLESSEQUALS exp
    | exp tGREATER exp
    | exp tLESS exp
    | exp tAND exp
    | exp tOR exp
    | tLEFTPAREN exp tRIGHTPAREN
    | tBANG exp
    | tMINUS exp %prec UMINUS
    | tIDENTIFIER Slices
    | tIDENTIFIER tDOT tIDENTIFIER
;

%%