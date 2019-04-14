#include "SymbolTable.h"
#include "TypeCheck.h"
#include "stdio.h"
#include "tree.h"
#include "weed.h"
#include <stdlib.h>
#include <string.h>

bool printSymbol = false;
PARAMS *functionParamsId = NULL;
PARAM_TYPE *functionParamsType = NULL;
int symbol_indentation = 0;
SymbolTable *origin_table = NULL;
SymbolTable *top_level_table = NULL;
unsigned long long variable_id = 1;

void printFunctionSignature() {
    PARAMS *p = functionParamsId;
    PARAM_TYPE *t = functionParamsType;
    if (printSymbol) {
        while (p != NULL && t != NULL) {
            ID_LIST *i = p->id_list;
            while (i != NULL) {
                printf("%s [variable] = ", i->id);
                printType(t->type);
                printf("\n");
                i = i->next;
            }
            p = p->next;
            t = t->next;
        }
    }
    functionParamsId = NULL;
    functionParamsType = NULL;
}

SymbolTable *initSymbolTable() {
    SymbolTable *t = malloc(sizeof(SymbolTable));
    for (int i = 0; i < HashSize; i++) {
        t->table[i] = NULL;
    }
    t->parent = NULL;
    return t;
}

// open new scope with s as parent scope
SymbolTable *scopeSymbolTable(SymbolTable *s) {
    SymbolTable *t = initSymbolTable();
    t->parent = s;
    return t;
}

int Hash(char *str) {
    unsigned int hash = 0;
    while (*str)
        hash = (hash << 1) + *str++;
    return hash % HashSize;
}

SYMBOL *putSymbol(SymbolTable *t, char *id, TYPE *type, symbolKind sk) {
    int i = Hash(id);
    for (SYMBOL *s = t->table[i]; s; s = s->next) {
        if (strcmp(s->name, id) == 0) {
            return NULL;
        }
    }
    SYMBOL *s = malloc(sizeof(SYMBOL));
    s->name = id;
    s->uid = sk == sk_varDcl ? variable_id++ : 0;
    s->scope = t;
    SYMBOL *variableType = NULL;
    if (type != NULL && type->id != NULL) {
        variableType = getSymbol(t, type->id);
    }

    if (sk == sk_varDcl && variableType != NULL &&
        variableType->kind == sk_typeDcl) {
        s->type = variableType->type;
    } else {
        s->type = type;
    }
    s->kind = sk;
    s->next = t->table[i];
    t->table[i] = s;
    return s;
}

SYMBOL *getSymbolCurrentScope(SymbolTable *t, char *name) {
    int i = Hash(name);
    // Check the current scope
    for (SYMBOL *s = t->table[i]; s; s = s->next) {
        if (strcmp(s->name, name) == 0)
            return s;
    }
    // Check for existence of a parent scope
    if (t->parent == NULL)
        return NULL;
    // Check the parent scopes
    return NULL;
}

SYMBOL *getSymbol(SymbolTable *t, char *name) {
    int i = Hash(name);
    // Check the current scope
    for (SYMBOL *s = t->table[i]; s; s = s->next) {
        if (strcmp(s->name, name) == 0)
            return s;
    }
    // Check for existence of a parent scope
    if (t->parent == NULL)
        return NULL;
    // Check the parent scopes
    return getSymbol(t->parent, name);
}

void printSymbolTable(SymbolTable *t) {
    if (t != NULL) {
        for (int i = 0; i < HashSize; i++) {
            for (SYMBOL *s = t->table[i]; s; s = s->next) {
                if (s->type == NULL) {
                    printf("symbol: name: %s, kind: %d, type id: null "
                           "underline type: null\n",
                           s->name, s->kind);
                } else {
                    if (s->type->underLineType != NULL) {
                        printf("symbol: name: %s, kind: %d, type kind: %d type "
                               "id: %s, "
                               "underline type: %s\n",
                               s->name, s->kind, s->type->kind, s->type->id,
                               s->type->underLineType->id);
                    } else {
                        printf("symbol: name: %s, kind: %d, type kind: %d type "
                               "id: %s "
                               "underline type: null\n",
                               s->name, s->kind, s->type->kind, s->type->id);
                    }
                }
            }
        }
        printSymbolTable(t->parent);
    }
}

void errorReDeclared(int lineno, char *message, char *id) {
    fprintf(stderr, "Error: (line %d) %s \"%s\" already declared \n", lineno,
            message, id);
    exit(1);
}

void errorNotDeclared(int lineno, char *message, char *id) {
    fprintf(stderr, "Error: (line %d) %s \"%s\" not declared\n", lineno,
            message, id);
    exit(1);
}

void symbolDecl(SymbolTable *s, DCL *d, int infunc) {
    if (d != NULL) {
        switch (d->kind) {
        case typeDcl:
            symbolTypeDcl(s, d->val.typeDecl, s);
            break;
        case varDcl:
            symbolVarDcl(s, d->val.varDecl, infunc);
            break;
        }
    }
}

void symbolTypeDcl(SymbolTable *s, TYPEDECL *t, SymbolTable *st) {
    if (t != NULL) {
        symbol_indentation++;
        symbolTypeSpec(t->typeSpec, 1, st);
        symbol_indentation--;
    }
}

void symbolVarDcl(SymbolTable *s, VARDECL *v, int infunc) {
    if (v != NULL) {
        symbolVarSpec(s, v->var_specs, infunc);
    }
}

BaseTypeKind isIdBaseType(char *id) {
    if (id == NULL) {
        return -1;
    }
    if (strcmp(id, "float64") == 0) {
        return btk_float64;
    } else if (strcmp(id, "bool") == 0) {
        return btk_bool;
    } else if (strcmp(id, "rune") == 0) {
        return btk_rune;
    } else if (strcmp(id, "string") == 0) {
        return btk_string;
    } else if (strcmp(id, "int") == 0) {
        return btk_int;
    } else {
        return -1;
    }
}

bool isTypeBaseType(TYPE *t, bool checkDeep) {
    if (t == NULL || t->id == NULL) {
        return false;
    }
    TYPE *tc = t;
    while (tc != NULL) {
        BaseTypeKind btk = isIdBaseType(tc->id);
        if (btk != -1) {
            t->id_type.baseTypeKind = btk;
            t->id_type.isBaseType = true;
            return true;
        } else {
            if (tc == tc->underLineType) {
            }
        }
        if (!checkDeep) {
            break;
        }
        tc = tc->underLineType;
    }
    return false;
}

TYPE *resolveType(SymbolTable *st, TYPE *ts, bool print) {
    if (ts == NULL || strcmp(ts->id, "struct") == 0) {
        if (printSymbol && print)
            printf("\n");
        return ts;
    }
    if (isTypeBaseType(ts, false)) {
        if (printSymbol && print)
            printf(" -> %s\n", ts->id);
        return ts;
    } else {
        SYMBOL *sb = getSymbol(st, ts->id);
        if (sb != NULL && sb->kind == sk_typeDcl) {
            ts->underLineType = sb->type->underLineType;
            switch (ts->kind) {
            case k_array:
                ts->array_type.type = sb->type->underLineType;
                return ts;
                break;
            case k_slices:
                ts->slices_type.type = sb->type->underLineType;
                return ts;
                break;
            }
            if (printSymbol && print) {
                printf(" -> ");
                printType(ts);
                printf("\n");
            }
            return resolveType(st, ts->underLineType, print);
        } else {
            if (ts->kind == k_array || ts->kind == k_slices) {
                if (isTypeDeclared(st, ts->underLineType, false)) {
                    TYPE *tc = ts;
                    while (tc != NULL &&
                           (tc->kind == k_array || tc->kind == k_slices)) {
                        SYMBOL *sb = putSymbol(st, tc->id, tc, sk_typeDcl);
                        if (sb == NULL) {
                            SYMBOL *ssb = getSymbol(st, tc->id);
                            tc = ssb->type;
                        }
                        tc = tc->underLineType;
                    }
                    SYMBOL *sb = getSymbol(st, ts->underLineType->id);
                    ts->underLineType = sb->type;
                    switch (ts->kind) {
                    case k_array:
                        ts->array_type.type = sb->type;
                        break;
                    case k_slices:
                        ts->slices_type.type = sb->type;
                    }
                    if (printSymbol && print) {
                        printf(" -> ");
                        printf("%s\n", ts->id);
                    }
                    return ts;
                }
            }
            if (ts->kind == k_funcsig) {
                putSymbol(st, ts->id, ts, sk_funcDcl);
                return ts;
            }
            if (ts->kind == k_infer) {
                return ts;
            }
            errorNotDeclared(ts->lineno, "type1", ts->id);
        }
    }
}

void createType(TYPESPEC *ts, SymbolTable *st, TYPE *new_type) {
    new_type->lineno = ts->lineno;
    new_type->id = ts->id;
    new_type->kind = ts->type->kind;
    if (ts->type->id == NULL || strncmp(ts->type->id, "[", 1) == 0) {
        new_type->underLineType = ts->type;
    } else if (ts->type->id == NULL || strcmp(ts->type->id, "struct") == 0) {
        new_type->underLineType = ts->type;
        symbolFieldDcl(st, ts->type->struct_type.field_dcls, ts->id,
                       ts->lineno);
    } else {
        SYMBOL *sbb = getSymbol(st, ts->type->id);
        if (sbb != NULL && sbb->kind == sk_typeDcl) {
            new_type->underLineType = sbb->type;
        } else {
            if (!isTypeDeclared(st, ts->type, false)) {
                errorNotDeclared(ts->lineno, "type2", ts->type->id);
            }
        }
    }
}

void checkTypeNameValid(TYPESPEC *ts) {
    TYPESPEC *temp = ts;
    while (temp != NULL) {
        if (strcmp(temp->id, "main") == 0 || strcmp(temp->id, "init") == 0) {
            fprintf(stderr,
                    "Error: (line %d) main/init can only be used to name a "
                    "function\n",
                    temp->lineno);
            exit(1);
        }
        temp = temp->next;
    }
}

bool isValidRecursive(char *name_id, char *type_id) {
    if (strstr(type_id, "[]") != NULL) {
        char *ptr = type_id;
        while (*ptr != *name_id && *ptr != '\0')
            ptr++;
        if (strcmp(name_id, ptr) == 0) {
            return true;
        }
    }
    return false;
}

void symbolTypeSpec(TYPESPEC *ts, int needParen, SymbolTable *st) {
    if (ts == NULL) {
        return;
    }
    checkTypeNameValid(ts);
    if ((strcmp(ts->type->id, ts->id) == 0 ||
         !isTypeDeclared(st, ts->type, false)) &&
        !isStruct(ts->type)) {
        if (!isValidRecursive(ts->id, ts->type->id)) {
            fprintf(stderr,
                    "Error: (line %d) invalid recursive type declaration\n",
                    ts->lineno);
            exit(1);
        }
    }

    TYPE *t = malloc(sizeof(TYPE));
    if (strcmp(ts->id, "_") != 0) {
        SYMBOL *sb = putSymbol(st, ts->id, t, sk_typeDcl);
        if (sb == NULL) {
            errorReDeclared(ts->lineno, "type", ts->id);
        }
    }

    createType(ts, st, t);
    if (printSymbol)
        printf("%s [type] = %s", ts->id, ts->id);
    TYPE *resolved = resolveType(st, ts->type, true);
    if (resolved != NULL) {
        ts->type->id_type = resolved->id_type;
    }

    symbolTypeSpec(ts->next, 0, st);
}

void printType(TYPE *t) {
    if (t != NULL) {
        switch (t->kind) {
        case k_type_id:
            if (printSymbol)
                printf("%s", t->id);
            break;
        case k_slices:
            if (printSymbol)
                printf("[]%s\n", t->slices_type.type->id);
            break;
        case k_array:
            if (printSymbol)
                printf("[%d]%s\n", t->array_type.size, t->array_type.type->id);
            break;
        case k_type_struct:
            if (printSymbol)
                printf("struct { ");
            symbolField_Dcl(t->struct_type.field_dcls);
            if (printSymbol)
                printf("}\n");
            break;
        case k_type_type:
            printType(t->types);
            break;
        }
    }
}

bool checkIdListValid(ID_LIST *id) {
    bool valid = true;
    ID_LIST *temp = id;
    while (temp != NULL) {
        if (strcmp(temp->id, "main") == 0 || strcmp(temp->id, "init") == 0) {
            valid = false;
            break;
        }
        temp = temp->next;
    }
    return valid;
}

void checkVarNameValid(VARSPEC *vs) {
    VARSPEC *temp = vs;
    while (temp != NULL) {
        bool idValid = checkIdListValid(temp->id_list);
        if (!idValid) {
            fprintf(stderr,
                    "Error: (line %d) main/init can only be used to name a "
                    "function\n",
                    temp->lineno);
            exit(1);
        }
        temp = temp->next;
    }
}

void symbolVarSpec(SymbolTable *s, VARSPEC *vs, int infunc) {
    if (vs == NULL) {
        return;
    }
    if (!infunc) {
        checkVarNameValid(vs);
    }
    VARSPEC *vsPtr = vs;
    if (vsPtr->next) {
        symbol_indentation++;
        while (vsPtr) {
            EXP *c = vsPtr->exp_list;
            symbolEXP(s, c);
            if (vsPtr->type == NULL) {
                vsPtr->type = vsPtr->exp_list->type;
            } else if (vsPtr->type->id != NULL){
                SYMBOL *sb = getSymbol(s, vsPtr->type->id);
                if (sb != NULL && sb->kind == sk_typeDcl){
                    vsPtr->type = sb->type;
                }
            }
            symbolIDList(s, vsPtr->id_list, vsPtr->type, NULL, false, false, true);
            vsPtr = vsPtr->next;
        }
        symbol_indentation--;
    } else {
        EXP *exp_list = vs->exp_list;
        if (exp_list != NULL) {
            symbolEXP(s, exp_list);
        }
        TYPE *type = vs->type;
        if (type == NULL) {
            type = vsPtr->exp_list->type;
        } else if (type->id != NULL){
            SYMBOL *sb = getSymbol(s, type->id);
            if (sb != NULL && sb->kind == sk_typeDcl){
                    type = sb->type;
                    vs->type = type;
            }
            
        }
        symbolIDList(s, vs->id_list, type, NULL, false, false, true);
    }
}

void printIDList(ID_LIST *idl) {
    if (idl != NULL) {
        if (printSymbol)
            printf("%s ", idl->id);
        printIDList(idl->next);
    }
}

void symbolField_Dcl(FIELD_DCL *f) {
    if (f == NULL) {
        return;
    }
    printIDList(f->id_list);
    printType(f->type);
    if (printSymbol)
        printf("; ");
    symbolField_Dcl(f->next);
}

void symbolFieldDcl(SymbolTable *st, FIELD_DCL *fdcl, char *id, int lineno) {
    if (fdcl == NULL) {
        return;
    }
    SymbolTable *inner_table = scopeSymbolTable(st);
    FIELD_DCL *f = fdcl;
    while (f) {
        if (strcmp(f->type->id, id) == 0) {
            errorReDeclared(lineno, id, id);
        }
        TYPE *typeInTable =
            symbolIDList(inner_table, f->id_list, f->type, NULL, false, true, true);
        if (typeInTable != NULL) {
            f->type = typeInTable;
        }
        f = f->next;
    }
}

bool isTypeDeclared(SymbolTable *st, TYPE *t, bool check_outer_scope) {
    if (t != NULL) {
        switch (t->kind) {
        case k_slices:
        case k_array:
            if (isIdBaseType(t->underLineType->id) != -1) {
                return true;
            } else {
                return isTypeDeclared(st, t->underLineType, check_outer_scope);
            }
            break;
        case k_type_struct:
            return getSymbol(st, t->id) != NULL &&
                   getSymbol(st, t->id)->kind == sk_typeDcl;
            break;
        case k_type_id:;
            bool verdict = getSymbol(st, t->id) != NULL &&
                           getSymbol(st, t->id)->kind == sk_typeDcl;
            if (check_outer_scope && !verdict) {
                verdict = getSymbol(st->parent, t->id) != NULL &&
                          getSymbol(st->parent, t->id)->kind == sk_typeDcl;
            }
            return verdict;
            break;
        case k_type_type:
            return isTypeDeclared(st, t->types, check_outer_scope);
            break;
        case k_infer:
            break;
        case k_funcsig:
            break;
        }
    }
    return false;
}

TYPE *symbolIDList(SymbolTable *s, ID_LIST *i, TYPE *ti, TYPE *funcType,
                   bool allowAssignment, bool check_outer_scope, bool check_next) {
    TYPE *typeInTable = NULL;
    TYPE *t = NULL;
    if (ti != NULL && ti->kind==k_funcsig && ti->result != NULL){
        t = ti->result;
    } else {
        t = ti;
    }
    if (i != NULL) {
        SYMBOL *symb = getSymbolCurrentScope(s, i->id);
        if ( symb != NULL && (!allowAssignment || symb->kind != varDcl)) {
            fprintf(stderr,
                    "Error: (line %d) identifier %s has been declared\n",
                    i->lineno, i->id);
            exit(1);
        }
        // if (t == NULL) {
        //     t = malloc(sizeof(TYPE));
        //     t->id = "<infer>";
        //     t->kind = k_infer;
        // }
        SYMBOL *sbb = getSymbol(s, t->id);
        if (check_outer_scope && sbb != NULL && sbb->kind != sk_typeDcl) {
            // Search one stack higher incase it is in a struct or something
            // else
            sbb = getSymbol(s->parent, t->id);
        }
        if (sbb != NULL) {
            if (sbb->kind == sk_typeDcl){
                typeInTable = sbb->type;
                t->underLineType = sbb->type->underLineType;
            } 
        } 

        i->type = t;

        if (t->id == NULL) {
            if (t->underLineType != NULL) {
                t->id = t->underLineType->id;
            } else {
                t->id = i->id;
            }
        } else if (strcmp(t->id, "struct") == 0) {
            symbolFieldDcl(s, t->struct_type.field_dcls, "", i->lineno);
        } else {
            if (!isTypeDeclared(s, t, check_outer_scope)) {
                if (t->kind == k_infer) {

                } else {
                    errorNotDeclared(i->lineno, "type3", t->id);
                }
            }
        }
        
        // i->type = t;
        
        if (strcmp(i->id, "_") != 0) {
            putSymbol(s, i->id, t, sk_varDcl);
            SYMBOL *isb = getSymbol(s, i->id);
            i->uid = isb->uid;
            i->top_level = isb->scope == top_level_table;
        }

        if (funcType != NULL) {
            PARAM_TYPE *p = malloc(sizeof(PARAM_TYPE));
            p->type = t;
            p->next = NULL;
            if (funcType->params == NULL) {
                funcType->params = p;
            } else {
                PARAM_TYPE *next_one = funcType->params;
                while (next_one->next)
                    next_one = next_one->next;
                next_one->next = p;
            }

            if (printSymbol) {
                printf("%s", t->id);
            }

            if (i->next != NULL) {
                if (printSymbol)
                    printf(", ");
            }
        } else {
            if (printSymbol) {
                printf("%s [variable] = ", i->id);
                printType(t);
                printf("\n");
            }
        }

        if (check_next) symbolIDList(s, i->next, t, funcType, allowAssignment, check_outer_scope, check_next);
    }
    return typeInTable;
}

void symbolParams(SymbolTable *t, PARAMS *p, TYPE *funcType) {

    if (p != NULL) {
        if (p->type && p->type->id){
            SYMBOL *sb = getSymbol(t, p->type->id);
            if (strcmp(p->type->id, funcType->id)==0){
                errorReDeclared(p->lineno, "Function params", p->type->id);
            }
            if (sb != NULL && sb->kind == sk_typeDcl){
                    p->type = sb->type;
            }
        }
        symbolIDList(t, p->id_list, p->type, funcType, false, true, true);
        if (p->next != NULL) {
            if (printSymbol)
                printf(", ");
            symbolParams(t, p->next, funcType);
        }
    }
}

void symbolResult(SymbolTable *t, SymbolTable *new_st, RESULT *r,
                  TYPE *funcType) {
    if (printSymbol)
        printf(" -> ");
    if (r != NULL) {
        if (r->params != NULL) {
            // named return, only support one type, not needed in golite
            if (printSymbol)
                printf("(");
            if (printSymbol)
                printf(")");
        } else {
            if (strcmp(r->type->id, funcType->id)==0){
                errorReDeclared(r->lineno, "Function params", r->type->id);
            }
            if (printSymbol)
                printf("%s", r->type->id);
            SYMBOL *symbol = getSymbol(t, r->type->id);
            if (symbol != NULL && symbol->type != NULL) {
                funcType->result = symbol->type;
                r->type = symbol->type;
            } else {
                funcType->result = resolveType(t, r->type, false);
            }
        }
    } else {
        funcType->result = NULL;
        if (printSymbol)
            printf("void");
    }
    if (printSymbol)
        printf("\n");
}

SymbolTable *symbolSig(SymbolTable *t, SIGNATURE *s, TYPE *funcType) {
    SymbolTable *new_st;
    if (s != NULL) {
        new_st = scopeSymbolTable(t);
        if (printSymbol)
            printf("(");
        symbolParams(new_st, s->params, funcType);
        if (printSymbol)
            printf(")");
        symbolResult(t, new_st, s->result, funcType);
    }
    return new_st;
}

void symbolFuncDecl(SymbolTable *t, FUNCDECL *f) {
    if (f == NULL) {
        return;
    }
    if (printSymbol)
        printf("%s [function] = ", f->id);
    if (strcmp(f->id, "main") == 0) {
        symbolSpecialFuncDecl(t, f, mainK);
        return;
    }
    if (strcmp(f->id, "init") == 0) {
        symbolSpecialFuncDecl(t, f, initK);
        return;
    }
    if (getSymbolCurrentScope(t, f->id) != NULL) {
        fprintf(stderr, "Error: (line %d) identifier %s has been declared\n",
                f->lineno, f->id);
        exit(1);
    }
    TYPE *funcType = malloc(sizeof(TYPE));
    funcType->lineno = f->lineno;
    funcType->id = f->id;
    funcType->kind = k_funcsig;
    funcType->params = NULL;
    funcType->result = NULL;
    SymbolTable *new_st = symbolSig(t, f->signature, funcType);
    if (strcmp(f->id, "_") != 0)
        putSymbol(t, f->id, funcType, sk_funcDcl);
    functionParamsId = f->signature->params;
    functionParamsType = funcType->params;
    symbolSTMT(t, new_st, f->body, true, true);
}

void symbolSpecialFuncDecl(SymbolTable *t, FUNCDECL *f, speicialFuncK spK) {
    if (t != top_level_table) {
        fprintf(stderr,
                "Error: (line %d) special function can only be decalared at "
                "top level \n",
                f->lineno);
        exit(1);
    }
    if (f->signature->params != NULL || f->signature->result != NULL) {
        fprintf(stderr,
                "Error: (line %d) special function cannot have any params or "
                "result \n",
                f->lineno);
        exit(1);
    }
    if (printSymbol)
        printf("() -> void\n");
    SymbolTable *new_st = scopeSymbolTable(t);
    switch (spK) {
    case mainK:
        if (getSymbolCurrentScope(t, "main") != NULL) {
            fprintf(stderr,
                    "Error: (line %d) identifier %s has been declared\n",
                    f->lineno, "main");
            exit(1);
        }
        putSymbol(t, "main", NULL, sk_funcDcl);
        break;
    case initK:
        break;
    }
    symbolSTMT(t, new_st, f->body, true, true);
}

void symbolTopDecl(SymbolTable *s, TOPDECL *t) {
    if (t != NULL) {
        switch (t->kind) {
        case dclK:
            symbolDecl(s, t->val.dcl, 0);
            break;
        case funcDeclK:
            symbolFuncDecl(s, t->val.funcDecl);
            break;
        }
        symbolTopDecl(s, t->next);
    }
}

void symbolEXP(SymbolTable *s, EXP *exp) {
    if (exp == NULL)
        return;
    switch (exp->kind) {
    case orExpr:
    case andExpr:
    case equalsExpr:
    case notequalsExpr:
    case lessExpr:
    case greaterExpr:
    case lessEqualsExpr:
    case greaterEqualsExpr:
    case plusExpr:
    case minusExpr:
    case bitwiseOrExpr:
    case bitwiseXorExpr:
    case bitwiseAndExpr:
    case bitClearExpr:
    case timesExpr:
    case divExpr:
    case modExpr:
    case leftShiftExpr:
    case rightShiftExpr:
        symbolEXP(s, exp->val.binary.lhs);
        symbolEXP(s, exp->val.binary.rhs);
        exp->type = exp->val.binary.lhs->type;
        break;
    case uMinusExpr:
    case uPlusExpr:
    case uBangExpr:
    case uCaretExpr:
    case uBitwiseAndExpr:
        symbolEXP(s, exp->val.unary.exp);
        exp->type = exp->val.unary.exp->type;
        break;
    case funcExpr:;
        SYMBOL *sb = getSymbol(s, exp->val.func.name->val.id);
        if (sb != NULL) {
            if (sb->kind == sk_typeDcl) {
                exp->kind = castExpr;
                // exp->val.cast.type = sb->type;
                // exp->val.cast.type->id = sb->name;
                exp->val.cast.exp = exp->val.func.args;
                exp->type = sb->type;
                symbolEXP(s, exp->val.cast.exp);
            } else {
                symbolEXP(s, exp->val.func.args);
                exp->type = sb->type;
            }
        } else {
            errorNotDeclared(exp->lineno, "func", exp->val.func.name->val.id);
        }
        break;
    // case castExpr:
    //     symbolEXP(s, exp->val.cast.exp);
    //     exp->type = exp->val.cast.type;
    //     break;
    case appendExpr:;
        symbolEXP(s, exp->val.append.head);
        symbolEXP(s, exp->val.append.tail);

        TYPE *rr = resolveType(s, exp->val.append.head->type, false);
        while (rr && *rr->id != '[') {
            rr = rr->underLineType;
        }
        if (rr == NULL) {
            exp->type = exp->val.append.head->type;
        } else {
            exp->type = exp->val.append.head->type;
            exp->val.append.head->type = rr;
        }
        break;
    case lenExpr:;
        symbolEXP(s, exp->val.expr);
        SYMBOL *ssbb = getSymbol(s, "int");
        exp->type = ssbb->type;
        break;
    case capExpr:;
        symbolEXP(s, exp->val.expr);
        SYMBOL *ssbs = getSymbol(s, "int");
        exp->type = ssbs->type;
        break;
    case arrayExpr:
    case sliceExpr:
        symbolEXP(s, exp->val.array.exp);
        symbolEXP(s, exp->val.array.index);
        if (!checkSameType(exp->val.array.index->type, strToType("int"),
                           true)) {
            errorNotDeclared(exp->lineno, "index is not a int type", "");
        }
        TYPE *r;
        r = resolveType(s, exp->val.array.exp->type, false);
        while (r && *r->id != '[') {
            r = r->underLineType;
        }
        if (r == NULL) {
            exp->type = exp->val.array.exp->type;
        } else {
            exp->type = r->underLineType;
            exp->val.array.exp->type = r;
        }
        break;
    case selectorExpr:
        symbolEXP(s, exp->val.selector.exp);
        exp->type = exp->val.selector.exp->type;
        break;
    case idExpr:;
        if (strcmp(exp->val.id, "_") != 0) {
            SYMBOL *sbb = getSymbol(s, exp->val.id);
            if (sbb == NULL) {
                fprintf(stderr,
                        "Error: (line %d) identifier %s is not defined\n",
                        exp->lineno, exp->val.id);
                exit(1);
            } else {
                if (sbb->kind == sk_typeDcl) {
                    fprintf(stderr,
                            "Error: (line %d) expression identifier %s is not "
                            "an expression\n",
                            exp->lineno, exp->val.id);
                    exit(1);
                }
                if (sbb->kind == sk_constant){
                    exp->kind = boolExpr;
                    if (strcmp("true", sbb->name) == 0){
                        exp->val.boolVal = true;
                    } else {
                        exp->val.boolVal = false;
                    }
                }
                isTypeBaseType(sbb->type, true);
                exp->uid = sbb->uid;
                exp->top_level = sbb->scope == top_level_table;
                exp->type = sbb->type;
            }
        } else {
            exp->type = strToType("int");
        }
        break;
    case intExpr:
        exp->type = strToType("int");
        break;
    case floatExpr:
        exp->type = strToType("float64");
        break;
    case runeExpr:
        exp->type = strToType("rune");
        break;
    case stringItpExpr:
        exp->type = strToType("string");
        break;
    case stringRawExpr:
        exp->type = strToType("string");
        break;
    case boolExpr:
        exp->type = strToType("bool");
        break;
    default:
        break;
    }
    if (exp->next != NULL) {
        symbolEXP(s, exp->next);
    }
}

void symbolCASE_CLAUSE(SymbolTable *s, CASE_CLAUSE *c) {
    if (c != NULL) {
        SymbolTable *new_new = scopeSymbolTable(s);
        switch (c->kind) {
        case caseK:;
            symbolEXP(new_new, c->caseExp);
            symbol_indentation++;
            symbolSTMT(new_new, NULL, c->caseStmt, true, true);
            symbol_indentation--;
            break;
        case defaultK:;
            symbol_indentation++;
            symbolSTMT(new_new, NULL, c->caseStmt, true, true);
            symbol_indentation--;
            break;
        }
        symbolCASE_CLAUSE(s, c->next);
    }
}

void symbolFOR_CLAUSE(SymbolTable *s, FOR_CLAUSE *f) {
    if (f != NULL) {
        symbolSTMT(s, NULL, f->first, false, false);
        symbolEXP(s, f->condtion);
        symbolSTMT(s, NULL, f->post, false, false);
    }
}

void symbolSTMT(SymbolTable *s, SymbolTable *new_st, STMT *stmt, bool to_indent,
                bool new_line) {
    if (stmt != NULL) {
        switch (stmt->kind) {
        case continueStmt:
            break;
        case breakStmt:
            break;
        case blockStmt:
            if (new_st == NULL) {
                new_st = scopeSymbolTable(s);
            }
            if (printSymbol)
                printf("{");
            if (printSymbol)
                printf("\n");
            symbol_indentation++;
            printFunctionSignature();
            symbolSTMT(new_st, NULL, stmt->val.block, true, true);
            symbol_indentation--;
            if (printSymbol)
                printf("}\n");
            break;
        case ifStmt:;
            SymbolTable *inew = scopeSymbolTable(s);
            if (stmt->val.ifStmtVal.ifSimpleStmt != NULL) {
                symbolSTMT(inew, NULL, stmt->val.ifStmtVal.ifSimpleStmt, false,
                           false);
            }
            symbolEXP(inew, stmt->val.ifStmtVal.ifCond);
            bool newLine = false;
            if (stmt->val.ifStmtVal.elseStmt == NULL) {
                newLine = true;
            }
            symbolSTMT(inew, NULL, stmt->val.ifStmtVal.ifBody, false, newLine);
            symbolSTMT(inew, NULL, stmt->val.ifStmtVal.elseStmt, false, newLine);
            break;
        case elseStmt:
            symbolSTMT(s, NULL, stmt->val.elseStmtVal.elseBody, false, newLine);
            symbolSTMT(s, NULL, stmt->val.elseStmtVal.ifStmt, false, newLine);
            break;
        case printStmt:
            symbolEXP(s, stmt->val.printExpList);
            break;
        case printlnStmt:
            symbolEXP(s, stmt->val.printlnExpList);
            break;
        case returnStmt:
            symbolEXP(s, stmt->val.returnExp);
            break;
        case switchStmt:;
            SymbolTable *new = scopeSymbolTable(s);
            if (stmt->val.switchStmtVal.switchSimpleStmt != NULL) {
                symbolSTMT(new, NULL, stmt->val.switchStmtVal.switchSimpleStmt,
                           false, false);
            }
            symbolEXP(new, stmt->val.switchStmtVal.switchExp);
            SymbolTable *new_new = scopeSymbolTable(new);
            symbolCASE_CLAUSE(new_new, stmt->val.switchStmtVal.switchCases);
            break;
        case emptyStmt:
            break;
        case expStmt:
            symbolEXP(s, stmt->val.expStmtVal);
            weedSTMT(stmt, 0, 0);
            break;
        case assignStmt:
            symbolEXP(s, stmt->val.assignStmtVal.lhs);
            symbolEXP(s, stmt->val.assignStmtVal.rhs);
            break;
        case incStmt:
            symbolEXP(s, stmt->val.incExp);
            break;
        case decStmt:
            symbolEXP(s, stmt->val.decExp);
            break;
        case shortVarDecStmt:
            symbolShortVarDec(s, stmt);
            break;
        case forStmt:;
            SymbolTable *fnew = scopeSymbolTable(s);
            symbolEXP(fnew, stmt->val.forStmtVal.forCond);
            symbolFOR_CLAUSE(fnew, stmt->val.forStmtVal.forClause);
            SymbolTable *fnew_new = scopeSymbolTable(fnew);
            symbolSTMT(fnew_new, NULL, stmt->val.forStmtVal.forBody, false,
                       true);
            break;
        case dclStmt:
            symbolDecl(s, stmt->val.decStmtVal, 1);
            break;
        }

        if (new_line && stmt->kind != emptyStmt) {
        }
        if (stmt->next) {
            symbolSTMT(s, NULL, stmt->next, to_indent, new_line);
        }
    }
}

void symbolShortVarDec(SymbolTable *st, STMT *s) {
    if (s == NULL) {
        return;
    }

    int num_ids = 0;
    ID_LIST *idc = s->val.shortVarDecStmtVal.ids;
    while (idc != NULL) {
        num_ids += 1;
        idc = idc->next;
    }

    int num_defined_ids = 0;
    ID_LIST *ids = s->val.shortVarDecStmtVal.ids;
    while (ids != NULL) {
        if (strcmp(ids->id, "_") == 0 ||
            getSymbolCurrentScope(st, ids->id) != NULL) {
            num_defined_ids += 1;
        }
        ids = ids->next;
    }

    if (num_ids == num_defined_ids) {
        fprintf(stderr,
                "Error: (line %d) all variables in short var declaration have "
                "been defined before\n",
                s->lineno);
        exit(1);
    }

    bool allowAssignment = false;
    if (num_ids > 1) {
        // assignment allowed
        allowAssignment = true;
    } else {
        // assignment not allowed
        allowAssignment = false;
    }
    symbolEXP(st, s->val.shortVarDecStmtVal.exps);
    ID_LIST *next_id;
    ID_LIST *curr_id = s->val.shortVarDecStmtVal.ids;
    EXP *curr_exp = s->val.shortVarDecStmtVal.exps;
    do {
        next_id = curr_id->next;
        symbolEXP(st, curr_exp);
        TYPE *t = curr_exp->type;
        SYMBOL *sb = getSymbolCurrentScope(st, curr_id->id);
        if (sb != NULL) {
            // already declared
            t = sb->type;
        }
        symbolIDList(st, curr_id, t, NULL, allowAssignment, false, false);
        curr_id = next_id;
        curr_exp = curr_exp->next;
    } while (next_id);
}

void symbolBooleanConstant(SymbolTable *s, char *boolVal) {
    putSymbol(s, boolVal, strToType("bool"), sk_constant);
    if (printSymbol)
        printf("%s [constant] = %s\n", boolVal, boolVal);
}

void symbolBaseType(SymbolTable *s, char *typeName) {
    TYPE *type = malloc(sizeof(TYPE));
    type->id = typeName;
    type->kind = k_type_id;
    type->underLineType = NULL;
    isTypeBaseType(type, false);
    if (printSymbol)
        printf("%s [type] = %s\n", type->id, type->id);
    putSymbol(s, type->id, type, sk_typeDcl);
}

void symbolAllBaseTypes(SymbolTable *s) {
    symbolBaseType(s, "int");
    symbolBaseType(s, "float64");
    symbolBaseType(s, "bool");
    symbolBaseType(s, "rune");
    symbolBaseType(s, "string");
    symbolBooleanConstant(s, "true");
    symbolBooleanConstant(s, "false");
}

void makeSymbolTable(PROGRAM *root) {
    if (root != NULL) {
        origin_table = initSymbolTable();
        top_level_table = scopeSymbolTable(origin_table);
        if (printSymbol)
            printf("{\n");
        symbolAllBaseTypes(origin_table);
        
        symbolTopDecl(top_level_table, root->top_decl);
        if (printSymbol)
            printf("}\n");
    }
}

void symbolMode() { printSymbol = true; }
