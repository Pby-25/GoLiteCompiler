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
    char runeval;
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
}

%type <TYPE> Type
%type <FIELD_DCL> field_dcls field_dcl
%type <ID_LIST> ident_list
%type <VARDECL> var_dcl 
%type <VARSPEC> var_specs var_spec
%type <PARAMS> params param_ls
%type <RESULT> result
%type <SIGNATURE> signature
%type <FUNCDECL> func_dcl
%type <PROGRAM> prog start
%type <EXP> exp unary_exp primary_exp exp_list literals for_exp
%type <STMT> stmt stmts break_stmt continue_stmt assign_stmt simple_stmt print_stmt short_var_dec switch_stmt ifstmt else_stmts block_stmt for_stmt inc_dec_stmt post_stmt
%type <IMPORT> import imports
%type <PACKAGE> package
%type <TOPDECL> top_level_dcl top_level_dcls
%type <TYPEDECL> type_dcl
%type <CASE_CLAUSE> expr_case_clause
%type <TYPESPEC> type_spec type_specs
%type <FOR_CLAUSE> for_clause
%type <DCL> dcl

%token <runeval> tRUNEVAL
%token <stringval> tSTRINGITPVAL tSTRINGRAWVAL 
%token <intval> tINTVAL
%token <floatval> tFLOATVAL
%token <id> tIDENTIFIER

%token tVAR tIF tELSE tPRINT
%token tCOLON tASSIGN tSEMICOLON tLEFTPAREN tRIGHTPAREN tLEFTBRACE tRIGHTBRACE tBANG
%token tPLUS tMINUS tTIMES tDIV tEQUALS tNOTEQUALS tGREATEREQUALS tLESSEQUALS tGREATER tLESS tAND tOR
%token tSTRUCT tSELECT tRETURN tRANGE tPACKAGE tMAP tINTERFACE tIMPORT tGOTO tGO tFOR tDEFER tDEFAULT
%token tCONTINUE tCONST tCHAN tCASE tBREAK tFALLTHROUGH tSWITCH tTYPE tPRINTLN tAPPEND tLEN tCAP
%token tMOD tBITWISEAND tBITWISEOR tBITWISEXOR tBITCLEAR tLEFTSHIFT tRIGHTSHIFT tPLUSEQUAL
%token tMINUSEQUAL tTIMESEQUAL tDIVEQUAL tMODEQUAL tPLUSPLUS tMINUSMINUS tANDEQUAL tOREQUAL 
%token tXOREQUAL tLEFTSHIFTEQUAL tRIGHTSHIFTEQUAL tBITCLEAREQUAL tCOLONEQUAL tDOTDOTDOT tCOMMA
%token tDOT tLEFTSQUAREBRACKET tRIGHTSQUAREBRACKET tFUNC

%left tOR
%left tAND
%left tEQUALS tNOTEQUALS tLESS tLESSEQUALS tGREATER tGREATEREQUALS 
%left tPLUS tMINUS tBITWISEOR tBITWISEXOR
%left tTIMES tDIV tMOD tLEFTSHIFT tRIGHTSHIFT tBITWISEAND tBITCLEAR
%left UBANG UMINUS UPLUS UCARET UBITWISEAND
// precedence
%glr-parser
%expect-rr 1

%start prog
%%

prog: start {root = $1;}
;

start: package imports top_level_dcls { $$ = makeProgram($1, $2, $3, yylineno); }
;

imports: {$$ = NULL;}
    | imports import tSEMICOLON { $$ = makeImportList($1, $2); }
;

top_level_dcls: {$$ = NULL;}
    | top_level_dcls top_level_dcl tSEMICOLON { $$ = makeTopVarDeclList($1, $2, yylineno);}
;


package: tPACKAGE tIDENTIFIER tSEMICOLON { $$ = makePackage($2, yylineno);}
;

import: tIMPORT tSTRINGITPVAL { $$ = makeImport($2, yylineno); }
;

dcl: type_dcl      { $$ = makeTypeDcl($1, yylineno); }         
    | var_dcl      { $$ = makeVarDcl($1, yylineno); }   
;

top_level_dcl: dcl { $$ = makeTopDeclFromDcl($1); }
    | func_dcl { $$ = makeTopDeclFromFuncDcl($1); }
;

Type: tIDENTIFIER {$$ = makeTypeId($1, yylineno);}
    | tLEFTSQUAREBRACKET tRIGHTSQUAREBRACKET Type {$$ = makeTypeSlices($3, yylineno);}
    | tLEFTSQUAREBRACKET tINTVAL tRIGHTSQUAREBRACKET Type {$$ = makeTypeArray($2,$4, yylineno);}
    | tSTRUCT tLEFTBRACE field_dcls tRIGHTBRACE {$$ = makeTypeStruct($3, yylineno);}
    | tLEFTPAREN Type tRIGHTPAREN {$$ = makeTypeT($2, yylineno);}
;

field_dcls: {$$ = NULL;}
    | field_dcls field_dcl tSEMICOLON {$$ = makeFieldDclList($1, $2, yylineno);}
;

field_dcl: ident_list Type {$$ = makeFieldDcl($1, $2, yylineno);}
;

var_dcl: tVAR var_spec {$$ = makeVarDecl($2, yylineno);}
    | tVAR tLEFTPAREN var_specs tRIGHTPAREN {$$ = makeVarDecl($3, yylineno);}
;

var_specs: {$$ = NULL;}
    | var_specs var_spec tSEMICOLON {$$ = makeVarSpecList($1,$2,yylineno);}
;

var_spec: ident_list Type tASSIGN exp_list {$$ = makeVarSpec($1,$2,$4, yylineno);}
    | ident_list Type {$$ = makeVarSpec($1,$2,NULL, yylineno);}
    | ident_list tASSIGN exp_list {$$ = makeVarSpec($1,NULL,$3, yylineno);}
;

type_dcl: tTYPE type_spec { $$ = makeTypeDecl($2, yylineno); }
    | tTYPE tLEFTPAREN type_specs tRIGHTPAREN { $$ = makeTypeDecl($3, yylineno); }
;

type_specs: { $$ = NULL; }
    | type_specs type_spec tSEMICOLON { $$ = makeTypeSpecList($1, $2); }
;

type_spec: tIDENTIFIER Type { $$ = makeTypeSpec($1, $2, yylineno); }
;

func_dcl: tFUNC tIDENTIFIER signature block_stmt { $$ = makeFuncDcl($2, $3, $4, yylineno);}
;

signature: params result {$$ = makeSignature($1, $2, yylineno);}
    | params {$$ = makeSignature($1, NULL, yylineno);}
;

result: params {$$ = makeResultP($1, yylineno);}
    | Type {$$ = makeResultType($1, yylineno);}
;

params: tLEFTPAREN param_ls tRIGHTPAREN {$$ = $2;}
;

param_ls: {$$ = NULL;}
    | ident_list Type {$$ = makeParams($1, $2, yylineno);}
    | param_ls tCOMMA ident_list Type {$$ = makeParamsList($1, $3, $4, yylineno);}
;

assign_stmt: exp_list tASSIGN exp_list { $$ = makeAssignStmt($1, $3, normal, yylineno); }
            | exp tPLUSEQUAL exp       { $$ = makeAssignStmt($1, $3, plus, yylineno); }
            | exp tMINUSEQUAL exp      { $$ = makeAssignStmt($1, $3, minus, yylineno); }
            | exp tOREQUAL exp         { $$ = makeAssignStmt($1, $3, or, yylineno); }
            | exp tXOREQUAL exp        { $$ = makeAssignStmt($1, $3, xor, yylineno); }
            | exp tTIMESEQUAL exp      { $$ = makeAssignStmt($1, $3, mult, yylineno); } 
            | exp tDIVEQUAL exp        { $$ = makeAssignStmt($1, $3, divide, yylineno); }
            | exp tMODEQUAL exp        { $$ = makeAssignStmt($1, $3, mod, yylineno); }
            | exp tLEFTSHIFTEQUAL exp  { $$ = makeAssignStmt($1, $3, leftShift, yylineno); }
            | exp tRIGHTSHIFTEQUAL exp { $$ = makeAssignStmt($1, $3, rightShift, yylineno); }
            | exp tANDEQUAL exp        { $$ = makeAssignStmt($1, $3, and, yylineno); }
            | exp tBITCLEAREQUAL exp   { $$ = makeAssignStmt($1, $3, bitclear, yylineno); }
;

stmt: continue_stmt { $$ = $1; }
    | break_stmt    { $$ = $1; }
    | block_stmt    { $$ = $1; }
    | ifstmt        { $$ = $1; }
    | print_stmt    { $$ = $1; }
    | tRETURN       { $$ = makeReturnStmt(NULL, yylineno); }
    | tRETURN exp   { $$ = makeReturnStmt($2, yylineno); }
    | switch_stmt   { $$ = $1; }        
    | simple_stmt   { $$ = $1; }
    | for_stmt      { $$ = $1; }
    | dcl           { $$ = makeDclStmt($1, yylineno); }
;

stmts: stmts stmt tSEMICOLON {$$ = makeStmtList($1,$2,yylineno);}
    | stmt tSEMICOLON {$$ = $1;}
;

print_stmt: tPRINT tLEFTPAREN exp_list tRIGHTPAREN          { $$ = makePrintStmt($3, yylineno); }
    | tPRINT tLEFTPAREN tRIGHTPAREN                         { $$ = makePrintStmt(NULL, yylineno); }
    | tPRINTLN tLEFTPAREN exp_list tRIGHTPAREN              { $$ = makePrintlnStmt($3, yylineno); }
    | tPRINTLN tLEFTPAREN tRIGHTPAREN                       { $$ = makePrintlnStmt(NULL, yylineno); }
;

short_var_dec: ident_list tCOLONEQUAL exp_list { $$ = makeShortVarDecStmt($1, $3, yylineno); }
;

simple_stmt: {}                         { $$ = makeEmptyStmt(yylineno); }
           | exp                        { $$ = makeExpStmt($1, yylineno); }
           | assign_stmt                { $$ = $1; } 
           | inc_dec_stmt               { $$ = $1; }
           | short_var_dec              { $$ = $1; }
;

inc_dec_stmt: exp tPLUSPLUS              { $$ = makeIncStmt($1, yylineno); }
           | exp tMINUSMINUS            { $$ = makeDecStmt($1, yylineno); }
;

exp_list: exp { $$ = makeExpList(NULL, $1, yylineno);}
    | exp_list tCOMMA exp { $$ = makeExpList($1, $3, yylineno);}
;

ident_list: tIDENTIFIER {$$ = makeIdList(NULL, $1, yylineno);}
    | ident_list tCOMMA tIDENTIFIER {$$ = makeIdList($1, $3, yylineno);}
;

switch_stmt: tSWITCH simple_stmt tSEMICOLON exp tLEFTBRACE expr_case_clause tRIGHTBRACE { $$ = makeSwitchStmt($2, $4, $6, yylineno); } 
    | tSWITCH simple_stmt tSEMICOLON tLEFTBRACE expr_case_clause tRIGHTBRACE { $$ = makeSwitchStmt($2, NULL, $5, yylineno); } 
    | tSWITCH exp tLEFTBRACE expr_case_clause tRIGHTBRACE { $$ = makeSwitchStmt(NULL, $2, $4, yylineno); } 
    | tSWITCH tLEFTBRACE expr_case_clause tRIGHTBRACE { $$ = makeSwitchStmt(NULL, NULL, $3, yylineno); } 
;

expr_case_clause: { $$ = NULL; }
    | expr_case_clause tCASE exp_list tCOLON stmts { $$ = makeCaseClause(1, $1, $3, $5, yylineno); }
    | expr_case_clause tDEFAULT tCOLON stmts { $$ = makeCaseClause(0, $1, NULL, $4, yylineno); }
; 

ifstmt: tIF simple_stmt tSEMICOLON exp block_stmt else_stmts { $$ = makeIfStmt($2, $4, $5, $6, yylineno); }
    | tIF simple_stmt tSEMICOLON exp block_stmt { $$ = makeIfStmt($2, $4, $5, NULL, yylineno); }
    | tIF exp block_stmt else_stmts { $$ = makeIfStmt(NULL, $2, $3, $4, yylineno); }
    | tIF exp block_stmt { $$ = makeIfStmt(NULL, $2, $3, NULL, yylineno); }
;

else_stmts: tELSE ifstmt { $$ = makeElseStmt(NULL, $2, yylineno); }
    | tELSE block_stmt { $$ = makeElseStmt($2, NULL, yylineno); }
;

block_stmt: tLEFTBRACE stmts tRIGHTBRACE { $$ = makeBlockStmt($2, yylineno); }
    | tLEFTBRACE tRIGHTBRACE { $$ = makeBlockStmt(NULL, yylineno); }
;

for_stmt: tFOR block_stmt           { $$ = makeForStmt(NULL, NULL, $2, yylineno); }
    | tFOR exp block_stmt           { $$ = makeForStmt($2, NULL, $3, yylineno); }
    | tFOR for_clause block_stmt    { $$ = makeForStmt(NULL, $2, $3, yylineno); }
;

for_clause: simple_stmt tSEMICOLON for_exp tSEMICOLON post_stmt  { $$ = makeForClause($1, $3, $5, yylineno); }
;

for_exp: {$$=NULL;}
    | exp {$$=$1;}
;

post_stmt: {}
    | inc_dec_stmt
    | assign_stmt
;

break_stmt: tBREAK { $$ = makeBreakStmt(yylineno); }
;

continue_stmt: tCONTINUE { $$ = makeContinueStmt(yylineno); }
;

primary_exp: tLEFTPAREN exp tRIGHTPAREN { $$ = $2; }
            | literals { $$ = $1; }
            | tIDENTIFIER { $$ = makeIdentifierExp($1, yylineno); }
            | tAPPEND tLEFTPAREN exp tCOMMA exp tRIGHTPAREN { $$ = makeAppendExp($3, $5, yylineno); }
            | tLEN tLEFTPAREN exp tRIGHTPAREN { $$ = makeLenExp ($3, yylineno); }
            | tCAP tLEFTPAREN exp tRIGHTPAREN { $$ = makeCapExp ($3, yylineno); }
            | primary_exp tLEFTSQUAREBRACKET exp tRIGHTSQUAREBRACKET { $$ = makeArrayIndexExp($1, $3, yylineno); }
            | primary_exp tDOT tIDENTIFIER { $$ = makeSelectorExp($1, $3, yylineno); }
            | primary_exp tLEFTPAREN exp_list tRIGHTPAREN { $$ = makeFuncExp($1, $3, yylineno); }
            | primary_exp tLEFTPAREN tRIGHTPAREN { $$ = makeFuncExp($1, NULL, yylineno); }
;

literals: tINTVAL { $$ = makeIntExp($1, yylineno); }
        | tSTRINGITPVAL { $$ = makeStringItpExp($1, yylineno); }
        | tSTRINGRAWVAL { $$ = makeStringRawExp($1, yylineno); }
        | tFLOATVAL { $$ = makeFloat64Exp($1, yylineno); } 
        | tRUNEVAL { $$ = makeRuneExp($1, yylineno); }
        ;

exp:  exp tOR exp { $$ = makeBinaryExp(orExpr, $1, $3, yylineno); }
   |  exp tAND exp { $$ = makeBinaryExp(andExpr, $1, $3, yylineno); }
   // rel_ops
   |  exp tEQUALS exp { $$ = makeBinaryExp(equalsExpr, $1, $3, yylineno); }
   |  exp tNOTEQUALS exp { $$ = makeBinaryExp(notequalsExpr, $1, $3, yylineno); }
   |  exp tLESS exp { $$ = makeBinaryExp(lessExpr, $1, $3, yylineno); }
   |  exp tLESSEQUALS exp { $$ = makeBinaryExp(lessEqualsExpr, $1, $3, yylineno); }
   |  exp tGREATER exp { $$ = makeBinaryExp(greaterExpr, $1, $3, yylineno); }
   |  exp tGREATEREQUALS exp { $$ = makeBinaryExp(greaterEqualsExpr, $1, $3, yylineno); }
   // add_ops
    | exp tPLUS exp { $$ = makeBinaryExp(plusExpr, $1, $3, yylineno); }
    | exp tMINUS exp { $$ = makeBinaryExp(minusExpr, $1, $3, yylineno); }
    | exp tBITWISEOR exp { $$ = makeBinaryExp(bitwiseOrExpr, $1, $3, yylineno); }
    | exp tBITWISEXOR exp { $$ = makeBinaryExp(bitwiseXorExpr, $1, $3, yylineno); }
    // mul_op
    | exp tTIMES exp { $$ = makeBinaryExp(timesExpr, $1, $3, yylineno); }
    | exp tDIV exp { $$ = makeBinaryExp(divExpr, $1, $3, yylineno); }
    | exp tMOD exp { $$ = makeBinaryExp(modExpr, $1, $3, yylineno); }
    | exp tLEFTSHIFT exp { $$ = makeBinaryExp(leftShiftExpr, $1, $3, yylineno); }
    | exp tRIGHTSHIFT exp { $$ = makeBinaryExp(rightShiftExpr, $1, $3, yylineno); }
    | exp tBITWISEAND exp { $$ = makeBinaryExp(bitwiseAndExpr, $1, $3, yylineno); }
    | exp tBITCLEAR exp { $$ = makeBinaryExp(bitClearExpr, $1, $3, yylineno); }
    | unary_exp { $$ = $1; }
;


unary_exp:  primary_exp { $$ = $1; }
        | tPLUS unary_exp   %prec UPLUS { $$ = makeUnaryExp(uPlusExpr, $2, yylineno); }
        | tMINUS unary_exp  %prec UMINUS { $$ = makeUnaryExp(uMinusExpr, $2, yylineno); }
        | tBANG unary_exp   %prec UBANG  { $$ = makeUnaryExp(uBangExpr, $2, yylineno); }
        | tBITWISEXOR unary_exp %prec UCARET { $$ = makeUnaryExp(uCaretExpr, $2, yylineno); }
        | tBITWISEAND unary_exp %prec UBITWISEAND { $$ = makeUnaryExp(uBitwiseAndExpr, $2, yylineno); }
;

%%
