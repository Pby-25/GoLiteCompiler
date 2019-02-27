#ifndef _weedH
#define _weedH
#include "tree.h"

void weedIMPORTS(IMPORT *i);
void weedProgram(PROGRAM *root);
void weedStmts(STMT *stmts);
void weedTOPDECL(TOPDECL *top_decl);
void weedEXP(EXP* exp, int blank_allow);
void weedSTMT(STMT *stmt, int inLoop, int inSwitch);
void weedField_Dcl(FIELD_DCL *f);
void weedFOR_CLAUSE(FOR_CLAUSE *for_clause, int inLoop, int inSwitch);
void weedCASE_CLAUSE(CASE_CLAUSE *case_clause, int inLoop, int inSwitch, int hasDefault);
void weedPARAMS(PARAMS *params);
void weedFUNCDECL(FUNCDECL *func_decl);
void weedVarSpec(VARSPEC *vs);
void weedVarDcl(VARDECL *v);
void weedType(TYPE *t);
void weedIdListExpList(ID_LIST *i, EXP *e, int lineno);
void weedType(TYPE *t);
void weedTypeSpec(TYPESPEC *ts);
void weedTypeDcl(TYPEDECL *t);
void weedDECL(DCL *dcl);
void weedTOPDECL(TOPDECL *top_decl);
void weedPROGRAM(PROGRAM *p);
void checkIdBlank(char *name, char *id, int lineno);

#endif