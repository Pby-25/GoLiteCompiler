#include "tree.h"
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



STMT *makeStmtList(STMT *list, STMT *v, int lineno) {
    if (list == NULL) {
        return v;
    }
    STMT *cur = list;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = v;
    return list;
}

EXP *makeExpList(EXP *list, EXP *v, int lineno) {
    if (list == NULL) {
        return v;
    }
    EXP *cur = list;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = v;
    return list;
}

EXP *makeBooleanExp(bool boolval, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = boolExpr;
    e->val.boolVal = boolval;
    return e;
}

EXP *makeIdentifierExp(char *identifier, int lineno) {
    if (strcmp(identifier, "true") == 0)
        return makeBooleanExp(true, lineno);
    else if (strcmp(identifier, "false") == 0)
        return makeBooleanExp(false, lineno);
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = idExpr;
    e->val.id = strdup(identifier);
    return e;
}

EXP *makeStringItpExp(char *stringval, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = stringItpExpr;
    e->val.stringVal = strdup(stringval);
    return e;
}

EXP *makeStringRawExp(char *stringval, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = stringRawExpr;
    char *itpString = malloc(strlen(stringval)*2+1);
    char *ptrSource = stringval;
    char *ptrDest = itpString;

    while (*ptrSource){
        switch (*ptrSource){
            case '\\':
                *ptrDest = '\\';
                ptrDest ++;
                *ptrDest = '\\';
                ptrDest ++;
                break;
            case '\a':
                *ptrDest = '\\';
                ptrDest ++;
                *ptrDest = 'a';
                ptrDest ++;
                break;
            case '\b':
                *ptrDest = '\\';
                ptrDest ++;
                *ptrDest = 'b';
                ptrDest ++;
                break;
            case '\f':
                *ptrDest = '\\';
                ptrDest ++;
                *ptrDest = 'f';
                ptrDest ++;
                break;
            case '\n':
                *ptrDest = '\\';
                ptrDest ++;
                *ptrDest = 'n';
                ptrDest ++;
                break;
            case '\r':
                *ptrDest = '\\';
                ptrDest ++;
                *ptrDest = 'r';
                ptrDest ++;
                break;
            case '\t':
                *ptrDest = '\\';
                ptrDest ++;
                *ptrDest = 't';
                ptrDest ++;
                break;
            case '\v':
                *ptrDest = '\\';
                ptrDest ++;
                *ptrDest = 'v';
                ptrDest ++;
                break;
            case '"':
                *ptrDest = '\\';
                ptrDest ++;
                *ptrDest = '"';
                ptrDest ++;
                break;
            case '`':
                break;
            default:
                *ptrDest = *ptrSource;
                ptrDest ++;
                break;
        }   
        ptrSource ++;
    }
    *ptrDest = '\0';
    e->val.stringVal = strdup(itpString);
    return e;
}

EXP *makeRuneExp(char *runeval, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = runeExpr;
    e->val.runeVal = runeval;
    return e;
}

EXP *makeIntExp(int intval, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = intExpr;
    e->val.intVal = intval;
    return e;
}

EXP *makeFloat64Exp(double float64val, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = floatExpr;
    e->val.floatVal = float64val;
    return e;
}

EXP *makeBinaryExp(ExpKind kind, EXP *lhs, EXP *rhs, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = kind;
    e->val.binary.lhs = lhs;
    e->val.binary.rhs = rhs;
    return e;
}

EXP *makeUnaryExp(ExpKind kind, EXP *exp, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = kind;
    e->val.unary.exp = exp;
    return e;
}

EXP *makeFuncExp(EXP *func_exp, EXP *args, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = funcExpr;
    e->val.func.name = func_exp;
    e->val.func.args = args;
    return e;
}

EXP *makeCastExp(TYPE *type, EXP *exp, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = castExpr;
    e->val.cast.exp = exp;
    return e;
}

EXP *makeAppendExp(EXP *head, EXP *tail, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = appendExpr;
    e->val.append.head = head;
    e->val.append.tail = tail;
    return e;
}

EXP *makeArrayIndexExp(EXP *array_exp, EXP *index, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = arrayExpr;
    e->val.array.exp = array_exp;
    e->val.array.index = index;
    return e;
}

EXP *makeSelectorExp(EXP *struct_exp, char *field_name, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = selectorExpr;
    e->val.selector.exp = struct_exp;
    e->val.selector.name = strdup(field_name);
    return e;
}

EXP *makeLenExp(EXP *exp, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = lenExpr;
    e->val.expr = exp;
    return e;
}

EXP *makeCapExp(EXP *exp, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = capExpr;
    e->val.expr = exp;
    return e;
}

ID_LIST *makeIdList(ID_LIST *list, char *id, int lineno) {
    ID_LIST *idl = malloc(sizeof(ID_LIST));
    idl->id = id;
    idl->lineno = lineno;
    if (list == NULL) {
        return idl;
    }
    ID_LIST *cur = list;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = idl;
    return list;
}

TYPE *makeTypeId(char *id, int lineno) {
    TYPE *t = malloc(sizeof(TYPE));
    t->kind = k_type_id;
    t->id = id;
    return t;
}

char *str_cat(char *str1, char *str2){
    char *str3 = (char *)malloc(1 + strlen(str1) + strlen(str2));
    strcpy(str3, str1);
    strcat(str3, str2);
    return str3;
}

TYPE *makeTypeSlices(TYPE *type, int lineno) {
    TYPE *t = malloc(sizeof(TYPE));
    t->id = str_cat("[]", type->id);
    t->kind = k_slices;
    t->slices_type.type = type;
    t->underLineType = type;
    return t;
}

TYPE *makeTypeArray(int size, TYPE *type, int lineno) {
    TYPE *t = malloc(sizeof(TYPE));
    char* size_str;
    asprintf (&size_str, "%i", size);
    t->id = str_cat(str_cat(str_cat("[",size_str),"]"),type->id);
    t->kind = k_array;
    t->array_type.type = type;
    t->array_type.size = size;
    t->underLineType = type;
    return t;
}

TYPE *makeTypeStruct(FIELD_DCL *f, int lineno) {
    TYPE *t = malloc(sizeof(TYPE));
    t->id = str_cat("struct","");
    t->kind = k_type_struct;
    t->struct_type.field_dcls = f;
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

FIELD_DCL *makeFieldDclList(FIELD_DCL *list, FIELD_DCL *f, int lineno) {
    if (list == NULL) {
        return f;
    }
    FIELD_DCL *cur = list;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = f;
    return list;
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

PARAMS *makeParams(ID_LIST *i, TYPE *t, int lineno) {
    PARAMS *p = malloc(sizeof(PARAMS));
    p->id_list = i;
    p->type = t;
    p->lineno = lineno;
    return p;
}

PARAMS *makeParamsList(PARAMS *p, ID_LIST *id_list, TYPE *type, int lineno) {
    PARAMS *p_new = makeParams(id_list, type, lineno);
    if (p == NULL) {
        return p_new;
    }
    PARAMS *cur = p;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = p_new;
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
    if (list == NULL) {
        return elem;
    }
    TYPESPEC *cur = list;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = elem;
    return list;
}

TYPEDECL *makeTypeDecl(TYPESPEC *spec, int lineno) {
    TYPEDECL *td = malloc(sizeof(TYPEDECL));
    td->lineno = lineno;
    td->typeSpec = spec;
    return td;
}

VARSPEC *makeVarSpec(ID_LIST *id_list, TYPE *type, EXP *exp, int lineno) {
    VARSPEC *vs = malloc(sizeof(VARSPEC));
    vs->id_list = id_list;
    vs->type = type;
    vs->exp_list = exp;
    vs->lineno = lineno;
    return vs;
}

VARSPEC *makeVarSpecList(VARSPEC *list, VARSPEC *v, int lineno) {
    if (list == NULL) {
        return v;
    }
    VARSPEC *cur = list;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = v;
    return list;
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
    s->val.ifStmtVal.ifSimpleStmt = ifSimpleStmt;
    s->val.ifStmtVal.ifCond = ifCond;
    s->val.ifStmtVal.ifBody = ifBody;
    s->val.ifStmtVal.elseStmt = elseStmt;
    return s;
}

STMT *makeElseStmt(STMT *elseBody, STMT *ifStmt, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = elseStmt;
    s->val.elseStmtVal.elseBody = elseBody;
    s->val.elseStmtVal.ifStmt = ifStmt;
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
    s->val.switchStmtVal.switchSimpleStmt = switchSimpleStmt;
    s->val.switchStmtVal.switchExp = switchExp;
    s->val.switchStmtVal.switchCases = switchCases;
    return s;
}

CASE_CLAUSE *makeCaseClause(int kind, CASE_CLAUSE *list, EXP *caseExp,
                            STMT *caseStmt, int lineno) {
    CASE_CLAUSE *c = malloc(sizeof(CASE_CLAUSE));
    c->lineno = lineno;
    if (kind == 0) {
        c->kind = defaultK;
    } else {
        c->kind = caseK;
    }

    c->caseExp = caseExp;
    c->caseStmt = caseStmt;

    if (list == NULL) {
        return c;
    }
    CASE_CLAUSE *cur = list;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = c;
    return list;
}

STMT *makeEmptyStmt(int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = emptyStmt;
    s->isSimpleStmt = 1;
    return s;
}

STMT *makeExpStmt(EXP *expStmtVal, int lineno) {
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
    s->val.assignStmtVal.lhs = lhs;
    s->val.assignStmtVal.rhs = rhs;
    s->val.assignStmtVal.assignKind = assignKind;
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
    s->val.shortVarDecStmtVal.ids = ids;
    s->val.shortVarDecStmtVal.exps = exps;
    return s;
}

FOR_CLAUSE *makeForClause(STMT *first, EXP *con, STMT *post, int lineno) {
    FOR_CLAUSE *f = malloc(sizeof(FOR_CLAUSE));
    f->lineno = lineno;
    f->first = first;
    f->condtion = con;
    f->post = post;
    return f;
}

DCL *makeTypeDcl(TYPEDECL *dcl, int lineno) {
    DCL *d = malloc(sizeof(DCL));
    d->lineno = lineno;
    d->kind = typeDcl;
    d->val.typeDecl = dcl;
    return d;
}

DCL *makeVarDcl(VARDECL *dcl, int lineno) {
    DCL *d = malloc(sizeof(DCL));
    d->lineno = lineno;
    d->kind = varDcl;
    d->val.varDecl = dcl;
    return d;
}

STMT *makeForStmt(EXP *forCond, FOR_CLAUSE *forClause, STMT *forBody,
                  int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = forStmt;
    s->val.forStmtVal.forCond = forCond;
    s->val.forStmtVal.forClause = forClause;
    s->val.forStmtVal.forBody = forBody;
    return s;
}

STMT *makeDclStmt(DCL *dcl, int lineno) {
    STMT *s = malloc(sizeof(STMT));
    s->lineno = lineno;
    s->kind = dclStmt;
    s->val.decStmtVal = dcl;
    return s;
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

IMPORT *makeImportList(IMPORT *list, IMPORT *v) {
    if (list == NULL) {
        return v;
    }
    IMPORT *cur = list;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = v;
    return list;
}

TOPDECL *makeTopVarDeclList(TOPDECL *list, TOPDECL *v, int lineno) {
    if (list == NULL) {
        return v;
    }
    TOPDECL *cur = list;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = v;
    return list;
}

PROGRAM *makeProgram(PACKAGE *pa, IMPORT *i, TOPDECL *decl, int lineno) {
    PROGRAM *p = malloc(sizeof(PROGRAM));
    p->lineno = lineno;
    p->package = pa;
    p->imports = i;
    p->top_decl = decl;
    return p;
}

TOPDECL *makeTopDeclFromDcl(DCL *d) {
    TOPDECL *t = malloc(sizeof(TOPDECL));
    t->kind = dclK;
    t->val.dcl = d;
    return t;
}
TOPDECL *makeTopDeclFromFuncDcl(FUNCDECL *d) {
    TOPDECL *t = malloc(sizeof(TOPDECL));
    t->kind = funcDeclK;
    t->val.funcDecl = d;
    return t;
}
