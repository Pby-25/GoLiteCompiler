#ifndef _CodeGenH
#define _CodeGenH
#include "TypeCheck.h"

void codePROGRAM(PROGRAM *root, char *file_name);
void codeSTMT(STMT *stmt, bool to_indent, bool new_line, STMT *post_stmt);
void codeImports(IMPORT *i);
void codeDecl(DCL* d, int infunc);
void codeTypeDcl(TYPEDECL *t);
void codeVarDcl(VARDECL *v, int infunc);
void codeTypeSpec(TYPESPEC *ts, int needParen);
void codeVarSpec(VARSPEC *vs, int infunc);
void prettType(TYPE *t);
void codeField_Dcl(FIELD_DCL *f);
void codeIDList(ID_LIST *i, bool func_params);
void codeType(TYPE *t);
void codeParams(PARAMS *p);
void codeResult(RESULT *r);
void codeSig(SIGNATURE *s);
void codeFuncDecl(FUNCDECL *f);
void codeTopDecl(TOPDECL* t);
void codeEXP(EXP *exp, bool to_copy);
void codeCASE_CLAUSE(CASE_CLAUSE *c, int cond_var, bool first_case);
void typeIdListExpList(ID_LIST *idl, EXP *el);

void indent();
#endif