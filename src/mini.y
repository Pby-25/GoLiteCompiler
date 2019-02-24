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
%token tVAR tIF tELSE tWHILE tREAD tPRINT tTRUE tFALSE
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
%left tBANG UMINUS UPLUS UCARET


%start prog
%%
slices_type: tLEFTSQUAREBRACKET tRIGHTSQUAREBRACKET element_type
;

element_type: Type
;

array_type: tLEFTSQUAREBRACKET tINTVAL tRIGHTSQUAREBRACKET element_type
;

Type: type_name
    | type_lit
    | tLEFTPAREN Type tRIGHTPAREN
;

type_name: tIDENTIFIER
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

type_spec: tIDENTIFIER tASSIGN Type 
    | tIDENTIFIER Type
;

func_dcl: tFUNC func_name signature func_body
;

func_body: {}
    block_stmt
;

func_name: tIDENTIFIER
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

param_dcl:  Type {}
    | ident_list Type
;

assign_stmt: exp_list assign_op exp_list
    | ident_list assign_op exp_list
;

assign_op: add_op tASSIGN
    | mul_op tASSIGN
    | tASSIGN
;

dcl: type_dcl
    | var_dcl
;

top_level_dcl: dcl
    | func_dcl
;

stmt: exp_list tEQUALS exp_list
    | continue_stmt
    | break_stmt
    | block_stmt
    | ifstmt
    | print_stmt
    | tRETURN 
    | tRETURN exp
    | switch_stmt           
    | simple_stmt
    | for_stmt
;    

stmts:{}
    | stmts dcl tSEMICOLON
    | stmts stmt tSEMICOLON   
;

print_stmt: tPRINT tLEFTPAREN exp_list_0_1 tRIGHTPAREN 
    | tPRINTLN tLEFTPAREN exp_list_0_1 tRIGHTPAREN
;

short_var_dec: ident_list tCOLONEQUAL exp_list
;

simple_stmt: {}                                 // empty_stmt
           | exp_stmt                           // exp_stmt
           | assign_stmt                    
           | exp tPLUSPLUS                      // inc
           | exp tMINUSMINUS                    // dec
           | short_var_dec
;

exp_stmt: exp
;

exp_list: exp 
    | exp_list tCOMMA exp
;

ident_list: tIDENTIFIER 
    | ident_list tCOMMA tIDENTIFIER
;

switch_stmt: tSWITCH simple_stmt exp_0_1 tLEFTBRACE expr_case_clause tRIGHTBRACE
;

simpel_stmt_0_1: {}
    | simple_stmt tSEMICOLON
;

exp_0_1: {}
    | exp tSEMICOLON
;

expr_case_clause: {}
    | expr_case_clause expr_switch_case tCOLON stmts
; 

expr_switch_case: tCASE exp_list 
    | tDEFAULT
;

elseifstmt: tELSE tIF exp_list tLEFTBRACE stmts tRIGHTBRACE
;

elseifstmts: {}
    | elseifstmts elseifstmt
;

elsestmt: {}
    | tELSE tLEFTBRACE stmts tRIGHTBRACE
;

ifstmt: tIF exp_list tLEFTBRACE stmts tRIGHTBRACE elseifstmts elsestmt
;

block_stmt: {}
    | tLEFTBRACE stmts tRIGHTBRACE
;


for_stmt: tFOR for_condition block_stmt
    | tFOR for_clause block_stmt
;

for_condition: {}
    | exp
;

for_clause: for_init_stmt tSEMICOLON for_condition tSEMICOLON for_post_stmt
;

for_post_stmt: {}
    | simple_stmt
;

for_init_stmt: {}
    | simple_stmt
;

break_stmt: tBREAK
;

continue_stmt: tCONTINUE
;

exp:  exp binary_op exp  
   | unary_exp 
;

unary_exp:  primary_exp 
         |  unary_op unary_exp  
;

primary_exp: operand
           | tAPPEND tLEFTPAREN tIDENTIFIER tCOMMA exp tRIGHTPAREN
           | tLEN tLEFTPAREN exp tRIGHTPAREN
           | tCAP tLEFTPAREN exp tRIGHTPAREN
           | primary_exp tLEFTSQUAREBRACKET tINTVAL tRIGHTSQUAREBRACKET 
           | primary_exp selector
           | primary_exp tLEFTPAREN exp_list_0_1 tRIGHTPAREN
;

exp_list_0_1: {}
    | exp_list
;

selector: tDOT tIDENTIFIER 
;

operand: tLEFTPAREN exp tRIGHTPAREN 
    | literals
    | tIDENTIFIER 
;

literals: tINTVAL
        | tSTRINGITPVAL 
        | tSTRINGRAWVAL
        | tFLOATVAL 
        | tRUNEVAL
        ;


unary_op: tPLUS %prec UPLUS
        | tMINUS %prec UMINUS
        | tBANG 
        | tBITWISEXOR %prec UCARET
        | tBITWISEAND
        ;

binary_op: tOR
    | tAND
    | rel_op 
    | add_op 
    | mul_op 
;

rel_op: tEQUALS
    | tNOTEQUALS
    | tLESS
    | tLESSEQUALS
    | tGREATER
    | tGREATEREQUALS
;

add_op: tPLUS
    | tMINUS
    | tBITWISEOR
    | tBITWISEXOR
;

mul_op: tTIMES
    | tDIV
    | tMOD
    | tLEFTSHIFT 
    | tRIGHTSHIFT
    | tBITWISEAND
    | tBITCLEAR
;

%%