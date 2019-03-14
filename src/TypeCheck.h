#ifndef _TypeCheckH
#define _TypeCheckH
#include "tree.h"
#include "SymbolTable.h"

void printIndentation();
// void typeCheckProgram(PROGRAM *porg);
// void typeExp(EXP *e);
// void typeStatement(STATEMENT *s);
bool checkSameType(TYPE *t1, TYPE *t2);

void typeCheckProgram(PROGRAM *root);

void typeSTMT(STMT *stmt, TYPE *returnType);
void typeImports(IMPORT *i);
void typeDecl(DCL* d, int infunc);
void typeTypeDcl(TYPEDECL *t);
void typeVarDcl(VARDECL *v, int infunc);
void typeTypeSpec(TYPESPEC *ts, int needParen);
void typeVarSpec(VARSPEC *vs);
void prettType(TYPE *t);
void typeField_Dcl(FIELD_DCL *f);
void typeIDList(ID_LIST *i);
void typeType(TYPE *t);
void typeParams(PARAMS *p);
void typeResult(RESULT *r);
void typeSig(SIGNATURE *s);
void typeFuncDecl(FUNCDECL *f);
void typeTopDecl(TOPDECL* t);
void typeEXP(EXP *exp);
void typeCASE_CLAUSE(CASE_CLAUSE *c, TYPE *returnType);
void typeFOR_CLAUSE(FOR_CLAUSE *f, TYPE *returnType);
TYPE *strToType(char *s);
TYPE *findSelectorIdType(char *name, TYPE *structType);

#endif