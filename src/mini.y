%{
#include <stdio.h>
#include "main.h"
#include "tree.h"

extern PROGRAM *root;
extern int yylineno;
int yylex();
void yyerror(const char *s) { fprintf(stderr, "Error: (line %d) %s\n", yylineno, s); }
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
%token tVAR tIF tELSE tPRINT
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
%left tEQUALS tNOTEQUALS tLESS tLESSEQUALS tGREATER tGREATEREQUALS 
%left tPLUS tMINUS tBITWISEOR tBITWISEXOR
%left tTIMES tDIV tMOD tLEFTSHIFT tRIGHTSHIFT tBITWISEAND tBITCLEAR
// %precedence UBANG UMINUS UPLUS UCARET UBITWISEAND

%glr-parser
%expect-rr 1

%start prog
%%

prog: start
;

start: package imports top_level_dcls
;

imports: {}
    | imports import tSEMICOLON
;

top_level_dcls: {}
    | top_level_dcls top_level_dcl tSEMICOLON
;

package: tPACKAGE tIDENTIFIER tSEMICOLON 
;

import: tIMPORT tSTRINGITPVAL 
;

dcl: type_dcl
    | var_dcl
;

top_level_dcl: dcl
    | func_dcl
;

slices_type: tLEFTSQUAREBRACKET tRIGHTSQUAREBRACKET Type
;

array_type: tLEFTSQUAREBRACKET tINTVAL tRIGHTSQUAREBRACKET Type
;

Type: tIDENTIFIER
    | type_lit
    | tLEFTPAREN Type tRIGHTPAREN
;

type_lit: slices_type
    | array_type
    | struct_type
;

struct_type: tSTRUCT tLEFTBRACE field_dcls tRIGHTBRACE
;

field_dcls: {}
    | field_dcls field_dcl tSEMICOLON
;

field_dcl: ident_list Type
;


var_dcl: tVAR var_spec
    | tVAR tLEFTPAREN var_specs tRIGHTPAREN 
;

var_specs: {}
    | var_specs var_spec tSEMICOLON
;

var_spec: ident_list Type tASSIGN exp_list
    | ident_list Type
    | ident_list tASSIGN exp_list
;

type_dcl: tTYPE type_spec
    | tTYPE tLEFTPAREN type_specs tRIGHTPAREN 
;

type_specs: {}
    | type_specs type_spec tSEMICOLON
;

type_spec: tIDENTIFIER Type
;

func_dcl: tFUNC tIDENTIFIER signature block_stmt
;

signature: params result
    | params
;

result: params
    | Type
;

params: tLEFTPAREN param_ls tRIGHTPAREN
;

param_ls: {}
    | param_dcl 
    | param_ls tCOMMA param_dcl
;

param_dcl: ident_list Type
;

assign_stmt: exp_list tASSIGN exp_list
            | exp tPLUSEQUAL exp   
            | exp tMINUSEQUAL exp    
            | exp tOREQUAL exp
            | exp tXOREQUAL exp   
            | exp tTIMESEQUAL exp   
            | exp tDIVEQUAL exp  
            | exp tMODEQUAL exp  
            | exp tLEFTSHIFTEQUAL exp 
            | exp tRIGHTSHIFTEQUAL exp
            | exp tANDEQUAL exp 
            | exp tBITCLEAREQUAL exp  
;

stmt: continue_stmt
    | break_stmt
    | block_stmt
    | ifstmt
    | print_stmt
    | tRETURN 
    | tRETURN exp
    | switch_stmt           
    | simple_stmt
    | for_stmt
    | dcl
;

stmts: stmts stmt tSEMICOLON;
    | stmt tSEMICOLON;
;

print_stmt: tPRINT tLEFTPAREN exp_list tRIGHTPAREN 
    | tPRINT tLEFTPAREN tRIGHTPAREN 
    | tPRINTLN tLEFTPAREN exp_list tRIGHTPAREN
    | tPRINTLN tLEFTPAREN tRIGHTPAREN
;

short_var_dec: ident_list tCOLONEQUAL exp_list
;

simple_stmt: {}                                 // empty_stmt
           | exp                           // exp_stmt
           | assign_stmt                    
           | exp tPLUSPLUS                      // inc
           | exp tMINUSMINUS                    // dec
           | short_var_dec
;

exp_list: exp 
    | exp_list tCOMMA exp
;

ident_list: tIDENTIFIER 
    | ident_list tCOMMA tIDENTIFIER
;

switch_stmt: tSWITCH simple_stmt tSEMICOLON exp tLEFTBRACE expr_case_clause tRIGHTBRACE
    | tSWITCH simple_stmt tSEMICOLON tLEFTBRACE expr_case_clause tRIGHTBRACE
    | tSWITCH exp tLEFTBRACE expr_case_clause tRIGHTBRACE
    | tSWITCH tLEFTBRACE expr_case_clause tRIGHTBRACE
;

expr_case_clause: {}
    | expr_case_clause expr_switch_case tCOLON stmts
; 

expr_switch_case: tCASE exp_list 
    | tDEFAULT
;

ifstmt: tIF simple_stmt tSEMICOLON exp block_stmt else_stmts
    | tIF exp block_stmt else_stmts
;

else_stmts: {}
    | tELSE ifstmt
    | tELSE block_stmt
;

block_stmt: tLEFTBRACE stmts tRIGHTBRACE
;


for_stmt: tFOR block_stmt
    | tFOR exp block_stmt
    | tFOR for_clause block_stmt
;

for_clause: simple_stmt tSEMICOLON simple_stmt tSEMICOLON simple_stmt
;

break_stmt: tBREAK
;

continue_stmt: tCONTINUE
;

primary_exp: tLEFTPAREN exp tRIGHTPAREN 
            | literals
            | tIDENTIFIER 
            | tAPPEND tLEFTPAREN exp tCOMMA exp tRIGHTPAREN
            | tLEN tLEFTPAREN exp tRIGHTPAREN
            | tCAP tLEFTPAREN exp tRIGHTPAREN
            | primary_exp tLEFTSQUAREBRACKET exp tRIGHTSQUAREBRACKET 
            | primary_exp selector
            | primary_exp tLEFTPAREN exp_list tRIGHTPAREN
            | primary_exp tLEFTPAREN tRIGHTPAREN
;

selector: tDOT tIDENTIFIER 
;

literals: tINTVAL
        | tSTRINGITPVAL 
        | tSTRINGRAWVAL
        | tFLOATVAL 
        | tRUNEVAL
        ;

exp:  exp tOR exp
   |  exp tAND exp 
   // rel_ops
   |  exp tEQUALS exp 
   |  exp tNOTEQUALS exp 
   |  exp tLESS exp 
   |  exp tLESSEQUALS exp 
   |  exp tGREATER exp 
   |  exp tGREATEREQUALS exp 
   // add_ops
    | exp tPLUS exp
    | exp tMINUS exp
    | exp tBITWISEOR
    | exp tBITWISEXOR exp
    // mul_op
    | exp tTIMES exp
    | exp tDIV exp
    | exp tMOD exp
    | exp tLEFTSHIFT exp
    | exp tRIGHTSHIFT exp
    | exp tBITWISEAND exp
    | exp tBITCLEAR exp
    | unary_exp 
;


unary_exp:  primary_exp 
         | unary_op unary_exp  
;

unary_op: tPLUS   //%prec UPLUS
        | tMINUS  //%prec UMINUS
        | tBANG   //%prec UBANG 
        | tBITWISEXOR //%prec UCARET
        | tBITWISEAND //%prec UBITWISEAND
;

%%