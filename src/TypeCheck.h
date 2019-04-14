#ifndef _TypeCheckH
#define _TypeCheckH
#include "SymbolTable.h"
#include "tree.h"

void printIndentation();
bool checkSameType(TYPE *t1, TYPE *t2, bool checkSameType);
void typeCheckProgram(PROGRAM *root);
void typeSTMT(STMT *stmt, TYPE *returnType);
void typeImports(IMPORT *i);
void typeDecl(DCL *d, int infunc);
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
void typeTopDecl(TOPDECL *t);
void typeEXP(EXP *exp);
void typeCASE_CLAUSE(CASE_CLAUSE *c, TYPE *returnType, TYPE *switchExpType);
void typeFOR_CLAUSE(FOR_CLAUSE *f, TYPE *returnType);
TYPE *strToType(char *s);
TYPE *findSelectorIdType(char *name, TYPE *structType);
bool isArrayOrSlice(TYPE *t);
bool isStruct(TYPE *t);
bool isSlices(TYPE *t);
bool isArray(TYPE *t);
bool isInteger(TYPE *t);

#endif