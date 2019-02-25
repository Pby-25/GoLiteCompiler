#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

EXP *makeBooleanExp(bool boolval, int lineno){
  EXP *e = malloc(sizeof(EXP));
  e->lineno = lineno;
  e->kind = boolExpr;
  e->val.boolVal = boolval;
  return e;
}

EXP *makeIdentifierExp(char *identifier, int lineno){
  if(strcmp(identifier, "true") == 0)
    return makeBooleanExp(true, lineno);
  else if (strcmp(identifier, "false") == 0)
    return makeBooleanExp(false, lineno);
  EXP *e = malloc(sizeof(EXP));
  e->lineno = lineno;
  e->kind = idExpr;
  e->val.id = strdup(identifier);
  return e;
}

EXP *makeStringItpExp(char *stringval, int lineno){
  EXP *e = malloc(sizeof(EXP));
  e->lineno = lineno;
  e->kind = stringItpExpr;
  e->val.stringVal = strdup(stringval);
  return e;
}

EXP *makeStringRawExp(char *stringval, int lineno){
  EXP *e = malloc(sizeof(EXP));
  e->lineno = lineno;
  e->kind = stringRawExpr;
  e->val.stringVal = strdup(stringval);
  return e;
}

EXP *makeRuneExp(char runeval, int lineno){
  EXP *e = malloc(sizeof(EXP));
  e->lineno = lineno;
  e->kind = runeExpr;
  e->val.runeVal = runeval;
  return e;
}

EXP *makeIntExp(int intval, int lineno){
  EXP *e = malloc(sizeof(EXP));
  e->lineno = lineno;
  e->kind = intExpr;
  e->val.intVal = intval;
  return e;

}

EXP *makeFloat64Exp(double float64val, int lineno){
  EXP *e = malloc(sizeof(EXP));
  e->lineno = lineno;
  e->kind = floatExpr;
  e->val.floatVal= float64val;
  return e;

}

EXP *makeBinaryExp(ExpKind kind, EXP *lhs, EXP *rhs, int lineno){
  EXP *e = malloc(sizeof(EXP));
  e->lineno = lineno;
  e->kind = kind;
  e->val.binary.lhs = lhs;
  e->val.binary.rhs = rhs;
  return e;
}

EXP *makeUnaryExp(ExpKind kind, EXP *exp, int lineno){
  EXP *e = malloc(sizeof(EXP));
  e->lineno = lineno;
  e->kind = kind;
  e->val.unary.exp = exp;
  return e;
}

EXP *makeFuncExp(EXP *func_exp, EXP *args, int lineno){
  EXP *e = malloc(sizeof(EXP));
  e->lineno = lineno;
  e->kind = funcExpr;
  e->val.func.name = func_exp;
  e->val.func.args = args;
  return e;
}


EXP *makeCastExp(TYPE *type, EXP *exp, int lineno){
  EXP *e = malloc(sizeof(EXP));
  e->lineno = lineno;
  e->kind = castExpr;
  e->val.cast.type = type;
  e->val.cast.exp = exp;
  return e;
}

EXP *makeAppendExp(EXP *head, EXP *tail, int lineno){
  EXP *e = malloc(sizeof(EXP));
  e->lineno = lineno;
  e->kind = appendExpr;
  e->val.append.head = head;
  e->val.append.tail = tail;
  return e;
}

EXP *makeArrayIndexExp(EXP *array_exp, EXP *index, int lineno){
  EXP *e = malloc(sizeof(EXP));
  e->lineno = lineno;
  e->kind = indexExpr;
  e->val.array.exp = array_exp;
  e->val.array.index = index;
  return e;
}

EXP *makeSelectorExp(EXP *struct_exp, char *field_name, int lineno){
  EXP *e = malloc(sizeof(EXP));
  e->lineno = lineno;
  e->kind = selectorExpr;
  e->val.selector.exp = struct_exp;
  e->val.selector.name = strdup(field_name);
  return e;
}

EXP *makeLenExp(EXP *exp, int lineno){
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = lenExpr;
    e->val.expr = exp;
    return e;
}

EXP *makeCapExp(EXP *exp, int lineno){
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = capExpr;
    e->val.expr = exp;
    return e;
}

EXP *makeCapExp(EXP *exp, int lineno){
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = capExpr;
    e->val.expr = exp;
    return e;
}

ID_LIST *makeIdList(ID_LIST *l, char *id, int lineno) {
    ID_LIST *idl = malloc(sizeof(ID_LIST));
    idl->id = id;
    idl->lineno = lineno;
    if (l == NULL) {
        return idl;
    } else {
        l->next = idl;
        return l;
    }
}

TYPE *makeTypeId(char *id, int lineno) {
    TYPE *t = malloc(sizeof(TYPE));
    t->kind = k_type_id;
    t->id = id;
    return t;
}

TYPE *makeTypeSlices(TYPE *type, int lineno) {
    TYPE *t = malloc(sizeof(TYPE));
    t->kind = k_slices;
    t->slices_type.type = type;
    return t;
}

TYPE *makeTypeArray(int size, TYPE *type, int lineno) {
    TYPE *t = malloc(sizeof(TYPE));
    t->kind = k_array;
    t->array_type.type = type;
    t->array_type.type = size;
    return t;
}

TYPE *makeTypeStruct(FIELD_DCL *f, int lineno) {
    TYPE *t = malloc(sizeof(TYPE));
    t->kind = k_type_struct;
    t->struct_type->field_dcls = f;
    return t;
}

TYPE *makeTypeT(TYPE *t1, int lineno) {
    TYPE *t = malloc(sizeof(TYPE));
    t->kind = k_type_type;
    t->types = t1;
    return t;
}

FIELD_DCL *makeFieldDcl(ID_LIST *id_list, TYPE *type, int lineno) {
    FIELD_DCL *f = malloc(sizeof(FIELD_DCL));
    f->id_list = id_list;
    f->type = type;
    f->lineno = lineno;
    return f;
}

FIELD_DCL *makeFieldDclList(FIELD_DCL *f, FIELD_DCL *f1, int lineno) {
    if (f == NULL) {
        return f1;
    }
    f->next = f1;
    f->lineno = lineno;
    return f;
}

SIGNATURE *makeSignature(PARAMS *params, RESULT *result, int lineno) {
    SIGNATURE *s = malloc(sizeof(SIGNATURE));
    s->params = params;
    s->lineno = lineno;
    s->result = result;
    return s;
}

RESULT *makeResultP(PARAMS *params, int lineno) {
    RESULT *r = malloc(sizeof(RESULT));
    r->params = params;
    r->lineno = lineno;
    return r;
}

RESULT *makeResultType(TYPE *type, int lineno) {
    RESULT *r = malloc(sizeof(RESULT));
    r->type = type;
    r->lineno = lineno;
    return r;
}

PARAMS *makeParamsList(PARAMS *p, ID_LIST *id_list, TYPE *type, int lineno) {
    PARAMS *p_new = makeParams(id_list, type, lineno);
    if (p == NULL) {
        return p_new;
    }
    p->next = p_new;
    return p;
}

FUNCDECL *makeFuncDcl(char *id, SIGNATURE *signature, STMT *body, int lineno) {
    FUNCDECL *f = malloc(sizeof(FUNCDECL));
    f->id = id;
    f->signature = signature;
    f->body = body;
    f->lineno = lineno;
    return f;
}

TYPESPEC *makeTypeSpec(char *id, TYPE *type, int lineno) {
    TYPESPEC *tp = malloc(sizeof(TYPESPEC));
    tp->id = id;
    tp->type = type;
    tp->lineno = lineno;
    return tp;
}

TYPESPEC *makeTypeSpecList(TYPESPEC *list, TYPESPEC *elem) {
    if (list != NULL) {
        list->next = elem;
    }
    return list;
}

VARSPEC *makeVarSpec(ID_LIST *id_list, TYPE *type, EXP *exp, int lineno) {
    VARSPEC *vs = malloc(sizeof(VARSPEC));
    vs->id_list = id_list;
    vs->type = type;
    vs->exp_list = exp;
    vs->lineno = lineno;
    return vs;
}

// TODO: NO BUG???????
VARSPEC *makeVarSpecList(VARSPEC *v, VARSPEC *v2, int lineno) {
    if (v == NULL) {
        return v2;
    }
    v->next = v2;
    v->lineno = lineno;
    return v;
}

VARDECL *makeVarDecl(VARSPEC *vs, int lineno) {
    VARDECL *vd = malloc(sizeof(VARDECL));
    vd->lineno = lineno;
    vd->var_specs = vs;
    return vd;
}

STMT *makeContinueStmt(int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = continueStmt;
    return s;
}

STMT *makeBreakStmt(int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = breakStmt;
    return s;
}

STMT *makeBlockStmt(STMT *block, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = blockStmt;
    s->val.block = block;
    return s;
}

STMT *makeIfStmt(STMT *ifSimpleStmt, EXP *ifCond, STMT *ifBody, STMT *elseStmt,
                 int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = ifStmt;
    s->val.ifStmtVal->ifSimpleStmt = ifSimpleStmt;
    s->val.ifStmtVal->ifCond = ifCond;
    s->val.ifStmtVal->ifBody = ifBody;
    s->val.ifStmtVal->elseStmt = elseStmt;
    return s;
}

STMT *makeElseStmt(STMT *elseBody, STMT *ifStmt, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = elseStmt;
    s->val.elseStmtVal->elseBody = elseBody;
    s->val.elseStmtVal->ifStmt = ifStmt;
    return s;
}

STMT *makePrintStmt(EXP *printExpList, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = printStmt;
    s->val.printExpList = printExpList;
    return s;
}

STMT *makePrintlnStmt(EXP *printlnExpList, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = printlnStmt;
    s->val.printlnExpList = printlnExpList;
    return s;
}

STMT *makeReturnStmt(EXP *returnExp, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = returnStmt;
    s->val.returnExp = returnExp;
    return s;
}

STMT *makeSwitchStmt(STMT *switchSimpleStmt, EXP *switchExp,
                     CASE_CLAUSE *switchCases, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = switchStmt;
    s->val.switchStmtVal->switchSimpleStmt = switchSimpleStmt;
    s->val.switchStmtVal->switchExp = switchExp;
    s->val.switchStmtVal->switchCases = switchCases;
    return s;
}

// is next set correctly??
CASE_CLAUSE *makeCaseClause(CASE_CLAUSE *list, EXP *caseExp, STMT *caseStmt, int lineno) {
    CASE_CLAUSE *c = malloc(sizeof(CASE_CLAUSE));
    c->lineno = lineno;
    if (list == NULL) {
        return c;
    } else {
        list->next = c;
        return list;
    }
}

STMT *makeEmptyStmt(int yylineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = emptyStmt;
    s->isSimpleStmt = 1;
    return s;
}

STMT *makeExpStmt(EXP *expStmtVal, int yylineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = expStmt;
    s->isSimpleStmt = 1;
    s->val.expStmtVal = expStmtVal;
    return s;
}

STMT *makeAssignStmt(EXP *lhs, EXP *rhs, AssignKind assignKind, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = assignStmt;
    s->isSimpleStmt = 1;
    s->val.assignStmtVal->lhs = lhs;
    s->val.assignStmtVal->rhs = rhs;
    s->val.assignStmtVal->assignKind = assignKind;
    return s;
}

STMT *makeIncStmt(EXP *incExp, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = incStmt;
    s->isSimpleStmt = 1;
    s->val.incExp = incExp;
    return s;
}

STMT *makeDecStmt(EXP *decExp, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = decStmt;
    s->isSimpleStmt = 1;
    s->val.decExp = decExp;
    return s;
}

STMT *makeShortVarDecStmt(ID_LIST *ids, EXP *exps, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = shortVarDecStmt;
    s->isSimpleStmt = 1;
    s->val.shortVarDecStmtVal->ids = ids;
    s->val.shortVarDecStmtVal->exps = exps;
    return s;
}





TYPEDECL *makeTypeDecl(TYPESPEC *spec, int lineno) {
    TYPEDECL *td = malloc(sizeof(TYPEDECL));
    td->lineno = lineno;
    td->typeSpec = spec;
    return td;
}

PACKAGE *makePackage(char *id, int lineno) {
    PACKAGE *p = malloc(sizeof(PACKAGE));
    p->id = id;
    p->lineno = lineno;
    return p;
}

IMPORT *makeImport(char *id, int lineno) {
    IMPORT *p = malloc(sizeof(IMPORT));
    p->lineno = lineno;
    p->id = id;
    return p;
}

IMPORT *makeImportList(IMPORT *list, IMPORT *elem) {
    if (list != NULL) {
        list->next = elem;
    }
    return elem;
}

TOPDECL *makeTopVarDecl(TYPEDECL *d, TOPDECL *next, int lineno) {
    TOPDECL *t = malloc(sizeof(TOPDECL));
    t->kind = varDeclK;
}
TOPDECL *makeTopTypeDecl(VARDECL *d, TOPDECL *next, int lineno) {}
TOPDECL *makeTopFuncDecl(FUNCDECL *d, TOPDECL *next, int lineno) {}

ID_LIST *makeIdList(ID_LIST *l, char *id, int lineno) {
    ID_LIST *idl = malloc(sizeof(ID_LIST));
    idl->id = id;
    idl->lineno = lineno;
    if (l == NULL) {
        return idl;
    } else {
        l->next = idl;
        return l;
    }
}

TYPE *makeTypeId(char *id, int lineno) {
    TYPE *t = malloc(sizeof(TYPE));
    t->kind = k_type_id;
    t->id = id;    
    return t;
}

TYPE *makeTypeSlices(TYPE *type, int lineno) {
    TYPE *t = malloc(sizeof(TYPE));
    t->kind = k_slices;
    t->slices_type.type = type;
    return t;
}

TYPE *makeTypeArray(int size, TYPE *type, int lineno) {
    TYPE *t = malloc(sizeof(TYPE));
    t->kind = k_array;
    t->array_type.type = type;
    t->array_type.type = size;
    return t;
}

TYPE *makeTypeStruct(FIELD_DCL *f, int lineno) {
    TYPE *t = malloc(sizeof(TYPE));
    t->kind = k_type_struct;
    t->struct_type->field_dcls = f;
    return t;
}

TYPE *makeTypeT(TYPE *t1, int lineno) {
    TYPE *t = malloc(sizeof(TYPE));
    t->kind = k_type_type;
    t->types = t1;
    return t;
}

FIELD_DCL *makeFieldDcl(ID_LIST *id_list, TYPE *type, int lineno) {
    FIELD_DCL *f = malloc(sizeof(FIELD_DCL));
    f->id_list = id_list;
    f->type = type;
    f->lineno = lineno;
    return f;
}

FIELD_DCL *makeFieldDclList(FIELD_DCL *f, FIELD_DCL *f1, int lineno) {
    if (f == NULL) {
        return f1;
    }
    f->next = f1;
    f->lineno = lineno;
    return f;
}

SIGNATURE *makeSignature(PARAMS *params, RESULT *result, int lineno) {
    SIGNATURE *s = malloc(sizeof(SIGNATURE));
    s->params = params;
    s->lineno = lineno;
    s->result = result;
    return s;
}

RESULT *makeResultP(PARAMS *params, int lineno) {
    RESULT *r = malloc(sizeof(RESULT));
    r->params = params;
    r->lineno = lineno;
    return r;
}

RESULT *makeResultType(TYPE *type, int lineno) {
    RESULT *r = malloc(sizeof(RESULT));
    r->type = type;
    r->lineno = lineno;
    return r;
}

PARAMS *makeParamsList(PARAMS *p, ID_LIST *id_list, TYPE *type, int lineno) {
    PARAMS *p_new = makeParams(id_list, type, lineno);
    if (p == NULL) {
        return p_new;
    }
    p->next = p_new;
    return p;
}

FUNCDECL *makeFuncDcl(char *id, SIGNATURE *signature, STMT *body, int lineno) {
    FUNCDECL *f = malloc(sizeof(FUNCDECL));
    f->id = id;
    f->signature = signature;
    f->body = body;
    f->lineno = lineno;
    return f;
}

TYPESPEC *makeTypeSpec(char *id, TYPE *type, int lineno) {
    TYPESPEC *tp = malloc(sizeof(TYPESPEC));
    tp->id = id;
    tp->type = type;
    tp->lineno = lineno;
    return tp;
}

TYPESPEC *makeTypeSpecList(TYPESPEC *list, TYPESPEC *elem) {
    if (list != NULL) {
        list->next = elem;
    }
    return list;
}

VARSPEC *makeVarSpec(ID_LIST *id_list, TYPE *type, EXP *exp, int lineno) {
    VARSPEC *vs = malloc(sizeof(VARSPEC));
    vs->id_list = id_list;
    vs->type = type;
    vs->exp_list = exp;
    vs->lineno = lineno;
    return vs;
}

// TODO: NO BUG???????
VARSPEC *makeVarSpecList(VARSPEC *v, VARSPEC *v2, int lineno) {
    if (v == NULL) {
        return v2;
    }
    v->next = v2;
    v->lineno = lineno;
    return v;
}

VARDECL *makeVarDecl(VARSPEC *vs, int lineno) {
    VARDECL *vd = malloc(sizeof(VARDECL));
    vd->lineno = lineno;
    vd->var_specs = vs;
    return vd;
}

STMT *makeContinueStmt(int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = continueStmt;
    return s;
}

STMT *makeBreakStmt(int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = breakStmt;
    return s;
}

STMT *makeBlockStmt(STMT *block, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = blockStmt;
    s->val.block = block;
    return s;
}

STMT *makeIfStmt(STMT *ifSimpleStmt, EXP *ifCond, STMT *ifBody, STMT *elseStmt,
                 int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = ifStmt;
    s->val.ifStmtVal->ifSimpleStmt = ifSimpleStmt;
    s->val.ifStmtVal->ifCond = ifCond;
    s->val.ifStmtVal->ifBody = ifBody;
    s->val.ifStmtVal->elseStmt = elseStmt;
    return s;
}

STMT *makeElseStmt(STMT *elseBody, STMT *ifStmt, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = elseStmt;
    s->val.elseStmtVal->elseBody = elseBody;
    s->val.elseStmtVal->ifStmt = ifStmt;
    return s;
}

STMT *makePrintStmt(EXP *printExpList, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = printStmt;
    s->val.printExpList = printExpList;
    return s;
}

STMT *makePrintlnStmt(EXP *printlnExpList, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = printlnStmt;
    s->val.printlnExpList = printlnExpList;
    return s;
}

STMT *makeReturnStmt(EXP *returnExp, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = returnStmt;
    s->val.returnExp = returnExp;
    return s;
}

STMT *makeSwitchStmt(STMT *switchSimpleStmt, EXP *switchExp,
                     CASE_CLAUSE *switchCases, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = switchStmt;
    s->val.switchStmtVal->switchSimpleStmt = switchSimpleStmt;
    s->val.switchStmtVal->switchExp = switchExp;
    s->val.switchStmtVal->switchCases = switchCases;
    return s;
}

// is next set correctly??
CASE_CLAUSE *makeCaseClause(CASE_CLAUSE *list, EXP *caseExp, STMT *caseStmt, int lineno) {
    CASE_CLAUSE *c = malloc(sizeof(CASE_CLAUSE));
    c->lineno = lineno;
    if (list == NULL) {
        return c;
    } else {
        list->next = c;
        return list;
    }
}

STMT *makeEmptyStmt(int yylineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = emptyStmt;
    s->isSimpleStmt = 1;
    return s;
}

STMT *makeExpStmt(EXP *expStmtVal, int yylineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = expStmt;
    s->isSimpleStmt = 1;
    s->val.expStmtVal = expStmtVal;
    return s;
}

STMT *makeAssignStmt(EXP *lhs, EXP *rhs, AssignKind assignKind, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = assignStmt;
    s->isSimpleStmt = 1;
    s->val.assignStmtVal->lhs = lhs;
    s->val.assignStmtVal->rhs = rhs;
    s->val.assignStmtVal->assignKind = assignKind;
    return s;
}

STMT *makeIncStmt(EXP *incExp, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = incStmt;
    s->isSimpleStmt = 1;
    s->val.incExp = incExp;
    return s;
}

STMT *makeDecStmt(EXP *decExp, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = decStmt;
    s->isSimpleStmt = 1;
    s->val.decExp = decExp;
    return s;
}

STMT *makeShortVarDecStmt(ID_LIST *ids, EXP *exps, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = shortVarDecStmt;
    s->isSimpleStmt = 1;
    s->val.shortVarDecStmtVal->ids = ids;
    s->val.shortVarDecStmtVal->exps = exps;
    return s;
}

FOR_CLAUSE *makeForClause(STMT *first, STMT *last, STMT *doStmt, int lineno) {
    FOR_CLAUSE *f = malloc(sizeof(FOR_CLAUSE));
    f->lineno = lineno;
    f->first = first;
    f->last = last;
    f->doStmt = doStmt;
    return f;
}

STMT *makeForStmt(EXP *forCond, FOR_CLAUSE *forClause, STMT *forBody, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = forStmt;
    s->val.forStmtVal->forCond = forCond;
    s->val.forStmtVal->forClause = forClause;
    s->val.forStmtVal->forBody = forBody;
    return s;
}

TYPEDECL *makeTypeDecl(TYPESPEC *spec, int lineno) {
    TYPEDECL *td = malloc(sizeof(TYPEDECL));
    td->lineno = lineno;
    td->typeSpec = spec;
    return td;
}

PACKAGE *makePackage(char *id, int lineno) {
    PACKAGE *p = malloc(sizeof(PACKAGE));
    p->id = id;
    p->lineno = lineno;
    return p;
}

IMPORT *makeImport(char *id, int lineno) {
    IMPORT *p = malloc(sizeof(IMPORT));
    p->lineno = lineno;
    p->id = id;
    return p;
}

IMPORT *makeImportList(IMPORT *list, IMPORT *elem) {
    if (list != NULL) {
        list->next = elem;
    }
    return elem;
}

PROGRAM *makeProgram(PACKAGE *pa, IMPORT *i, TOPDECL *decl) {
    PROGRAM *p = malloc(sizeof(PROGRAM));
    p->package = pa;
    p->imports = i;
    p->top_decl = decl;
    return p;
}
