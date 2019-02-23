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
    | field_dcls field_dcl 
;

field_dcl: ident_list Type tSEMICOLON
;

prog: start
;

start: package stmts
;

package: tPACKAGE tIDENTIFIER tSEMICOLON 
;

import: tIMPORT tSTRINGITPVAL tSEMICOLON 
;

comma_id_list: {}
    | tCOMMA exp comma_id_list 
;

var_dcl: tVAR var_specs
    | tVAR tLEFTPAREN var_specs tRIGHTPAREN tSEMICOLON 
;

var_specs: {}
    | var_specs var_spec
;

var_spec: ident_list Type tASSIGN exp_list tSEMICOLON
    | ident_list Type tSEMICOLON
    | ident_list tASSIGN exp_list tSEMICOLON
;

type_dcl: tTYPE type_spec
    | tTYPE tLEFTPAREN type_specs tRIGHTPAREN tSEMICOLON
;

type_specs: {}
    | type_specs type_spec
;

type_spec: tIDENTIFIER tASSIGN Type tSEMICOLON 
    | tIDENTIFIER Type tSEMICOLON
;

func_dcl: tFUNC exp tLEFTPAREN func_param tRIGHTPAREN tLEFTBRACE stmt stmts tRIGHTBRACE tSEMICOLON  
;

func_param: {}
    | exp comma_id_list Type func_param 
    | tCOMMA func_param
    | exp Type func_param 
;

assign_stmt: exp_list assign_op exp_list
;

assign_op: add_op tASSIGN
    | mul_op tASSIGN
    | tASSIGN
;

stmts: {}
    | stmts stmt
;

dcl_stmt: type_dcl 
    | var_dcl 
;

stmt: exp_list tEQUALS exp_list
    | continue_stmt
    | break_stmt
    | import
    | block_stmt
    | func_dcl // TODO, not a stmt
    | ifstmt
    | tPRINT tLEFTPAREN exp_list tRIGHTPAREN
    | tPRINTLN tLEFTPAREN exp_list tRIGHTPAREN
    | tRETURN 
    | tRETURN exp
    | switch_stmt           // To be tested!
    | simple_stmt
    | dcl_stmt
    | for_stmt
    ;

simple_stmt: {}                                 // empty_stmt
           | exp_stmt                           // exp_stmt
           | assign_stmt                    
           | ident_list tCOLONEQUAL exp_list    // short_decl
           | exp tPLUSPLUS                      // inc
           | exp tMINUSMINUS                    // dec
           ;

exp_stmt: exp
;

ident_list: ident_list tCOMMA tIDENTIFIER
          | tIDENTIFIER
          | {}
;

exp_list: exp_list tCOMMA exp 
        | exp 
        | {}
;

switch_stmt: tSWITCH switch_simple_stmt switch_exp tLEFTBRACE expr_case_clause tRIGHTBRACE 
           ;

switch_simple_stmt: simple_stmt tSEMICOLON
                | {}
                ;

switch_exp: exp
          | {}
          ;

expr_case_clause: expr_switch_case tCOLON stmts
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

block_stmt: tLEFTBRACE stmts tRIGHTBRACE
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

break_stmt: tBREAK tSEMICOLON
;

continue_stmt: tCONTINUE tSEMICOLON
;


exp: tIDENTIFIER 
    | tLEFTPAREN exp tRIGHTPAREN
    | literals
    | unary_op exp 
    | exp binary_op exp
    | tAPPEND tLEFTPAREN exp tCOMMA exp tRIGHTPAREN
    | tLEN tLEFTPAREN exp tRIGHTPAREN
    | tCAP tLEFTPAREN exp tRIGHTPAREN
    | func_call
    | type_cast
    | tIDENTIFIER tLEFTSQUAREBRACKET tINTVAL tRIGHTSQUAREBRACKET  // array index
;

literals: tINTVAL
        | tSTRINGITPVAL 
        | tFLOATVAL 
        | tRUNEVAL
        ;

unary_op: tPLUS %prec UPLUS
        | tMINUS %prec UMINUS
        | tBANG 
        | tBITWISEXOR %prec UCARET
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

func_call: exp tLEFTPAREN exp comma_id_list tRIGHTPAREN tSEMICOLON
;

type_cast: Type tLEFTPAREN exp tRIGHTPAREN
;

%%