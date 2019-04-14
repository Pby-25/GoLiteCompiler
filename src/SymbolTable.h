#ifndef _SymbolTableH
#define _SymbolTableH
#define HashSize 317

#include "tree.h"
typedef enum { sk_typeDcl, sk_varDcl, sk_funcDcl, sk_constant } symbolKind;

typedef enum { mainK, initK } speicialFuncK;

typedef struct SYMBOL {
    char *name;
    unsigned long long uid;
    struct SymbolTable *scope;
    TYPE *type;
    symbolKind kind;
    struct SYMBOL *next;
} SYMBOL;

typedef struct SymbolTable {
    SYMBOL *table[HashSize];
    struct SymbolTable *parent;
} SymbolTable;

void symbolMode();
void printFunctionSignature();
void makeSymbolTable(PROGRAM *root);
SYMBOL *getSymbol(SymbolTable *t, char *name);
SYMBOL *putSymbol(SymbolTable *t, char *id, TYPE *type, symbolKind sk);
SymbolTable *scopeSymbolTable(SymbolTable *s);
SymbolTable *initSymbolTable();
void symbolTypeDcl(SymbolTable *s, TYPEDECL *t, SymbolTable *st);
void symbolSTMT(SymbolTable *s, SymbolTable *new_st, STMT *stmt, bool to_indent,
                bool new_line);
void symbolImports(IMPORT *i);
void symbolDecl(SymbolTable *s, DCL *d, int infunc);
void symbolTopDecl(SymbolTable *s, TOPDECL *t);
void symbolVarDcl(SymbolTable *s, VARDECL *v, int infunc);
void symbolTypeSpec(TYPESPEC *ts, int needParen, SymbolTable *st);
void symbolVarSpec(SymbolTable *s, VARSPEC *vs, int infunc);
void printType(TYPE *t);
void symbolField_Dcl(FIELD_DCL *f);
TYPE *symbolIDList(SymbolTable *s, ID_LIST *i, TYPE *t, TYPE *funcType,
                   bool allowAssignment, bool field_dcl, bool check_next);
void symbolParams(SymbolTable *t, PARAMS *p, TYPE *funcType);
void symbolResult(SymbolTable *t, SymbolTable *new_st, RESULT *r,
                  TYPE *funcType);
SymbolTable *symbolSig(SymbolTable *t, SIGNATURE *s, TYPE *funcType);
void symbolFuncDecl(SymbolTable *t, FUNCDECL *f);
void makeSymbolTable(PROGRAM *root);
void symbolEXP(SymbolTable *s, EXP *exp);
void symbolCASE_CLAUSE(SymbolTable *s, CASE_CLAUSE *c);
void symbolSpecialFuncDecl(SymbolTable *t, FUNCDECL *f, speicialFuncK spK);
void symbolShortVarDec(SymbolTable *st, STMT *s);
TYPE *resolveType(SymbolTable *st, TYPE *ts, bool print);
bool isTypeBaseType(TYPE *t, bool checkDeep);
BaseTypeKind isIdBaseType(char *id);
void printSymbolTable(SymbolTable *t);
bool isTypeDeclared(SymbolTable *st, TYPE *t, bool field_dcl);
void symbolFieldDcl(SymbolTable *st, FIELD_DCL *fdcl, char *id, int lineno);
bool checkSameExpType(EXP *lhs, EXP *rhs);

extern SymbolTable *top_level_table;
#endif