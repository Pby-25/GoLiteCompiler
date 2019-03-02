#ifndef _prettyH
#define _prettyH

#include "tree.h"

void prettyPROGRAM(PROGRAM *root);

void prettySTMT(STMT *stmt, bool to_indent, bool new_line);
void prettyImports(IMPORT *i);
void prettyDecl(DCL* d, int infunc);
void prettyTypeDcl(TYPEDECL *t);
void prettyVarDcl(VARDECL *v, int infunc);
void prettyTypeSpec(TYPESPEC *ts, int needParen);
void prettyVarSpec(VARSPEC *vs, int infunc);
void prettType(TYPE *t);
void prettyField_Dcl(FIELD_DCL *f);
void prettyIDList(ID_LIST *i);
void prettyType(TYPE *t);
void prettyParams(PARAMS *p);
void prettyResult(RESULT *r);
void prettySig(SIGNATURE *s);
void prettyFuncDecl(FUNCDECL *f);
void prettyTopDecl(TOPDECL* t);
void prettyPROGRAM(PROGRAM *root);
void prettyEXP(EXP *exp);
void prettyCASE_CLAUSE(CASE_CLAUSE *c);

void printIndentation();
#endif