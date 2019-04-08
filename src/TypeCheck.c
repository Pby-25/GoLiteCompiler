#include "TypeCheck.h"
#include "SymbolTable.h"
#include "stdio.h"
#include "tree.h"
#include "weed.h"
#include <stdlib.h>
#include <string.h>

int type_indentation = 0;
void errorType(char *expected, char *actual, int lineno) {
    fprintf(stderr, "Error: (line %d): Expected type %s, but got %s\n", lineno,
            expected, actual);
    exit(1);
}

TYPE *strToType(char *s) {
    SYMBOL *symbol = getSymbol(top_level_table, s);
    return symbol->type;
}

TYPE *findSelectorIdType(char *name, TYPE *structType) {
    TYPE *t = structType;
    while (t->kind != k_type_struct || t->underLineType) {
        t = t->underLineType;
    }
    FIELD_DCL *f_dcl = t->struct_type.field_dcls;

    while (f_dcl) {
        ID_LIST *idl = f_dcl->id_list;
        while (idl) {
            if (strcmp(name, idl->id) == 0) {
                return f_dcl->type;
            }
            idl = idl->next;
        }
        f_dcl = f_dcl->next;
    }
    return NULL;
}

void typeCheckProgram(PROGRAM *prog) {
    makeSymbolTable(prog);
    typeTopDecl(prog->top_decl);
}

bool isBool(TYPE *t) { return checkSameType(t, strToType("bool"), true); }

bool isInteger(TYPE *t) {
    return checkSameType(t, strToType("int"), true) ||
           checkSameType(t, strToType("rune"), true);
}

bool isNumeric(TYPE *t) {
    return isInteger(t) || checkSameType(t, strToType("float64"), true);
}

bool isOrdered(TYPE *t) {
    return isNumeric(t) || checkSameType(t, strToType("string"), true);
}

bool isComparable(TYPE *t) {
    if (isOrdered(t) || isBool(t))
        return true;
    switch (t->kind) {
    case k_array:
        return isComparable(t->array_type.type);
    case k_type_struct:;
        FIELD_DCL *anyField = t->struct_type.field_dcls;
        while (anyField) {
            if (!isComparable(anyField->type))
                return false;
            anyField = anyField->next;
        }
        return true;
    default:
        return false;
    }
}

bool checkSameStruct(FIELD_DCL *field1, FIELD_DCL *field2) {
    if (!field1 || !field2) {
        return false;
    }
    ID_LIST *idlist1 = field1->id_list;
    ID_LIST *idlist2 = field2->id_list;
    while (field1 && field2) {
        if (!checkSameType(field1->type, field2->type, false)) {
            return false;
        }
        while (idlist1 && idlist2) {
            if (strcmp(idlist1->id, idlist2->id) != 0) {
                return false;
            }
            idlist1 = idlist1->next;
            idlist2 = idlist2->next;
        }
        if (!idlist1) {
            field1 = field1->next;
            if (field1) {
                idlist1 = field1->id_list;
            }
        }

        if (!idlist2) {
            field2 = field2->next;
            if (field2) {
                idlist2 = field2->id_list;
            }
        }
    }
    if (field1 || field2) {
        return false;
    }
    return true;
}

bool checkSameType(TYPE *t1, TYPE *t2, bool checkBaseType) {
    if (t1 == NULL || t2 == NULL) {
        if (t1 && strcmp(t1->id, "_") == 0) {
            return true;
        }
        if (t2 && strcmp(t2->id, "_") == 0) {
            return true;
        }
        fprintf(stderr, "\ncheck same type null\n");
        exit(1);
        return false;
    }

    isTypeBaseType(t1, true);
    isTypeBaseType(t2, true);

    switch (t1->kind) {
    case k_slices:
        if (t2->kind == k_slices) {
            if (strcmp(t1->id, t2->id) == 0) {
                return true;
            }
            return checkSameType(t1->slices_type.type, t2->slices_type.type,
                                 checkBaseType);
        } else {
            return false;
        }
        break;
    case k_array:
        if (t2->kind == k_array) {
            if (strcmp(t1->id, t2->id) == 0) {
                return true;
            }
            return checkSameType(t1->array_type.type, t2->array_type.type,
                                 checkBaseType) &&
                   t1->array_type.size == t2->array_type.size;
        } else {
            return false;
        }
        break;
    case k_type_struct:
        if (t2->kind != k_type_struct)
            return false;
        if (strcmp(t1->id, "struct") == 0 || strcmp(t2->id, "struct") == 0) {
            return checkSameStruct(t1->struct_type.field_dcls,
                                   t2->struct_type.field_dcls);
        } else {
            return strcmp(t1->id, t2->id) == 0;
        }

        break;
    case k_type_id:
        if (checkBaseType) {
            return t1->id_type.baseTypeKind == t2->id_type.baseTypeKind;
        }
        if(t1 == t2){
            return true;
        }else{
            if(isIdBaseType(t2->id)!=-1 && isIdBaseType(t2->id)!=-1){
                return strcmp(t1->id, t2->id) == 0;
            }else{
                return false;
            }
            
        }
        // return ;
        // if(t1->id_type.isBaseType && t2->id_type.isBaseType){
        //     return strcmp(t1->id, t2->id) == 0;
        // }else{
        //     // printf("here\n");
        //     return t1 == t2;
        // }
        // return strcmp(t1->id, t2->id) == 0 && &t1 == &t2;
        break;
    case k_type_type:
        if (t2->kind == k_type_type) {
            return checkSameType(t1->types, t2->types, checkBaseType);
        } else {
            return false;
        }
        break;
    case k_infer:
        t1 = t2;
        return true;
        break;
    }

    return false;
}

void typeDecl(DCL *d, int infunc) {
    if (d != NULL) {
        switch (d->kind) {
        case typeDcl:
            typeTypeDcl(d->val.typeDecl);
            break;
        case varDcl:
            typeVarDcl(d->val.varDecl, infunc);
            break;
        }
    }
}

void typeTypeDcl(TYPEDECL *t) {
    if (t != NULL) {
        typeTypeSpec(t->typeSpec, 1);
    }
}

void typeVarDcl(VARDECL *v, int infunc) {
    if (v != NULL) {
        typeVarSpec(v->var_specs);
    }
}

void typeTypeSpec(TYPESPEC *ts, int needParen) {
    if (ts == NULL) {
        return;
    }
    typeTypeSpec(ts->next, 0);
}

void typeIdListExpList(ID_LIST *idl, EXP *el) {
    ID_LIST *ic = idl;
    EXP *ec = el;
    typeEXP(ec);
    while (ic != NULL && ec != NULL) {
        if (!checkSameType(ic->type, ec->type, false)) {
            // printf("maybe here\n");
            errorType(ic->type->id, ec->type->id, ic->lineno);
        }
        ic = ic->next;
        ec = ec->next;
    }
}

void typeVarSpec(VARSPEC *vs) {
    if (vs == NULL) {
        return;
    }
    // typeEXP(vs->exp_list);
    typeIdListExpList(vs->id_list, vs->exp_list);
    typeVarSpec(vs->next);
}

void typeField_Dcl(FIELD_DCL *f) {
    if (f == NULL) {
        return;
    }
    printIndentation();
    typeIDList(f->id_list);

    typeType(f->type);

    typeField_Dcl(f->next);
}

void typeIDList(ID_LIST *i) {
    if (i != NULL) {

        if (i->next != NULL) {
        }
        typeIDList(i->next);
    }
}

void typeType(TYPE *t) {
    if (t != NULL) {
        switch (t->kind) {
        case k_type_id:

            break;
        case k_slices:

            typeType(t->slices_type.type);
            break;
        case k_array:

            typeType(t->array_type.type);
            break;
        case k_type_struct:

            type_indentation++;
            typeField_Dcl(t->struct_type.field_dcls);
            type_indentation--;
            printIndentation();

            break;
        case k_type_type:

            typeType(t->types);

            break;
        case k_infer:
            break;
        }
    }
}

void typeParams(PARAMS *p) {
    if (p != NULL) {
        typeIDList(p->id_list);
        typeType(p->type);
        if (p->next != NULL) {

            typeParams(p->next);
        }
    }
}

void typeFuncDecl(FUNCDECL *f) {
    if (f != NULL) {
        STMT *body = f->body;
        if (f->signature != NULL) {
            if (f->signature->result == NULL) {
                typeSTMT(body, NULL);
            } else {
                bool terminate = weedTerminateStmt(body);
                if (!terminate) {
                    fprintf(
                        stderr,
                        "Error: (line %d) this function does not terminate\n",
                        f->lineno);
                    exit(1);
                }
                typeSTMT(body, f->signature->result->type);
            }
        }
    }
}

void typeTopDecl(TOPDECL *t) {
    if (t != NULL) {
        switch (t->kind) {
        case dclK:
            typeDecl(t->val.dcl, 0);
            break;
        case funcDeclK:
            typeFuncDecl(t->val.funcDecl);
            break;
        }
        typeTopDecl(t->next);
    }
}

void typePROGRAM(PROGRAM *root) {
    if (root != NULL) {
        typeTopDecl(root->top_decl);
    }
}

bool isSlices(TYPE *t) {
    if (t == NULL) {
        return false;
    }
    if (t->kind == k_slices) {
        return true;
    } else {
        return isSlices(t->underLineType);
    }
    return false;
}

bool isArrayOrSlice(TYPE *t) {
    if (t == NULL) {
        return false;
    }
    if (t->kind == k_array || t->kind == k_slices) {
        return true;
    } else {
        return isArrayOrSlice(t->underLineType);
    }
    return false;
}

bool isArray(TYPE *t) {
    if (t == NULL) {
        return false;
    }
    if (t->kind == k_array) {
        return true;
    } else {
        return isArray(t->underLineType);
    }
    return false;
}

bool isValidSliceType(TYPE *type) {
    if (type == NULL)
        return false;
    bool valid = true;
    char *id = type->id;
    int i;
    for (i = 0; i < strlen(id); i++) {
        if (id[i] == '[' && id[i + 1] != ']') {
            valid = false;
            break;
        }
    }
    return valid;
}

bool isStruct(TYPE *t) {
    if (t == NULL) {
        return false;
    }
    if (t->kind == k_type_struct) {
        return true;
    } else {
        return isStruct(t->underLineType);
    }
    return false;
}

void checkExpLength(EXP *exp) {
    EXP *temp = exp;
    int num = 0;
    while (temp != NULL) {
        num++;
        temp = temp->next;
    }
    if (num != 1) {
        fprintf(stderr, "Error: type cast expects only 1 expression\n");
        exit(1);
    }
}

void typeEXP(EXP *exp) {
    if (exp == NULL)
        return;
    switch (exp->kind) {
    case orExpr:
    case andExpr:
        typeEXP(exp->val.binary.lhs);
        typeEXP(exp->val.binary.rhs);
        if (!checkSameExpType(exp->val.binary.lhs, exp->val.binary.rhs)) {
            errorType(exp->val.binary.lhs->type->id,
                      exp->val.binary.rhs->type->id, exp->lineno);
        } else if (!isBool(exp->val.binary.lhs->type)) {
            errorType("bool", exp->val.binary.lhs->type->id, exp->lineno);
        } else if (!isBool(exp->val.binary.rhs->type)) {
            errorType("bool", exp->val.binary.rhs->type->id, exp->lineno);
        } else {
            exp->type = exp->val.binary.lhs->type;
        }
        break;
    case equalsExpr:
    case notequalsExpr:
        typeEXP(exp->val.binary.lhs);
        typeEXP(exp->val.binary.rhs);
        if (!checkSameExpType(exp->val.binary.lhs, exp->val.binary.rhs)) {
            errorType(exp->val.binary.lhs->type->id,
                      exp->val.binary.rhs->type->id, exp->lineno);
        } else if (!isComparable(exp->val.binary.lhs->type)) {
            errorType("comparable", exp->val.binary.lhs->type->id, exp->lineno);
        } else if (!isComparable(exp->val.binary.rhs->type)) {
            errorType("comparable", exp->val.binary.rhs->type->id, exp->lineno);
        } else {
            exp->type = strToType("bool");
        }
        break;
    case lessExpr:
    case greaterExpr:
    case lessEqualsExpr:
    case greaterEqualsExpr:
        typeEXP(exp->val.binary.lhs);
        typeEXP(exp->val.binary.rhs);
        if (!checkSameExpType(exp->val.binary.lhs, exp->val.binary.rhs)) {
            errorType(exp->val.binary.lhs->type->id,
                      exp->val.binary.rhs->type->id, exp->lineno);
        } else if (!isOrdered(exp->val.binary.lhs->type)) {
            errorType("ordered", exp->val.binary.lhs->type->id, exp->lineno);
        } else if (!isOrdered(exp->val.binary.rhs->type)) {
            errorType("ordered", exp->val.binary.rhs->type->id, exp->lineno);
        } else {
            exp->type = strToType("bool");
        }
        break;
    case plusExpr:
        typeEXP(exp->val.binary.lhs);
        typeEXP(exp->val.binary.rhs);
        if (!checkSameExpType(exp->val.binary.lhs, exp->val.binary.rhs)) {
            errorType(exp->val.binary.lhs->type->id,
                      exp->val.binary.rhs->type->id, exp->lineno);
        } else if (!isOrdered(exp->val.binary.lhs->type)) {
            errorType("ordered", exp->val.binary.lhs->type->id, exp->lineno);
        } else if (!isOrdered(exp->val.binary.rhs->type)) {
            errorType("ordered", exp->val.binary.rhs->type->id, exp->lineno);
        } else {
            exp->type = exp->val.binary.lhs->type;
        }
        break;
    case minusExpr:
    case timesExpr:
    case divExpr:
        typeEXP(exp->val.binary.lhs);
        typeEXP(exp->val.binary.rhs);
        if (!checkSameExpType(exp->val.binary.lhs, exp->val.binary.rhs)) {
            errorType(exp->val.binary.lhs->type->id,
                      exp->val.binary.rhs->type->id, exp->lineno);
        } else if (!isNumeric(exp->val.binary.lhs->type)) {
            errorType("numeric", exp->val.binary.lhs->type->id, exp->lineno);
        } else if (!isNumeric(exp->val.binary.rhs->type)) {
            errorType("numeric", exp->val.binary.rhs->type->id, exp->lineno);
        } else {
            exp->type = exp->val.binary.lhs->type;
        }
        break;
    case bitwiseOrExpr:
    case bitwiseXorExpr:
    case bitwiseAndExpr:
    case bitClearExpr:
    case modExpr:
    case leftShiftExpr:
    case rightShiftExpr:
        typeEXP(exp->val.binary.lhs);
        typeEXP(exp->val.binary.rhs);
        if (!checkSameExpType(exp->val.binary.lhs, exp->val.binary.rhs)) {
            errorType(exp->val.binary.lhs->type->id,
                      exp->val.binary.rhs->type->id, exp->lineno);
        } else if (!isInteger(exp->val.binary.lhs->type)) {
            errorType("integer", exp->val.binary.lhs->type->id, exp->lineno);
        } else if (!isInteger(exp->val.binary.rhs->type)) {
            errorType("integer", exp->val.binary.rhs->type->id, exp->lineno);
        } else {
            exp->type = exp->val.binary.lhs->type;
        }
        break;
    case uMinusExpr:
    case uPlusExpr:
        typeEXP(exp->val.unary.exp);
        if (!isNumeric(exp->val.unary.exp->type)) {
            errorType("numeric", exp->val.unary.exp->type->id, exp->lineno);
        } else {
            exp->type = exp->val.unary.exp->type;
        }
        break;
    case uBangExpr:
        typeEXP(exp->val.unary.exp);
        if (!isBool(exp->val.unary.exp->type)) {
            errorType("bool", exp->val.unary.exp->type->id, exp->lineno);
        } else {
            exp->type = exp->val.unary.exp->type;
        }
        break;
    case uCaretExpr:
    case uBitwiseAndExpr:
        typeEXP(exp->val.unary.exp);
        if (!isInteger(exp->val.unary.exp->type)) {
            errorType("integer", exp->val.unary.exp->type->id, exp->lineno);
        } else {
            exp->type = exp->val.unary.exp->type;
        }
        break;
    case funcExpr:
        typeEXP(exp->val.func.name);
        typeEXP(exp->val.func.args);
        if (strcmp(exp->val.func.name->val.id, "init") == 0) {
            fprintf(
                stderr,
                "Error: (line %d): Function \"init\" shall never be called\n",
                exp->lineno);
            exit(1);
        }
        EXP *arg = exp->val.func.args;
        PARAM_TYPE *p = exp->type->params;
        while (p) {
            if (arg == NULL) {
                fprintf(stderr,
                        "Error: (line %d): Function call [%s] has unmatched "
                        "number of paramters from its declaration\n",
                        exp->lineno, exp->val.func.name->val.id);
                exit(1);
            }
            if (!checkSameType(p->type, arg->type, false)) {
                errorType(p->type->id, arg->type->id, exp->lineno);
            }
            p = p->next;
            arg = arg->next;
        }
        if (arg != NULL) {
            fprintf(stderr,
                    "Error: (line %d): Function call [%s] has unmatched number "
                    "of paramters from its declaration\n",
                    exp->lineno, exp->val.func.name->val.id);
            exit(1);
        }
        // Done checking parameters, update type to exp return type
        exp->type = exp->type->result;
        break;

    case castExpr:
        checkExpLength(exp->val.cast.exp);
        typeEXP(exp->val.cast.exp);
        if (!isTypeBaseType(exp->type, true) ||
            isArrayOrSlice(exp->type)) {
            errorType("expected base type", exp->type->id,
                      exp->lineno);
        }
        if (!checkSameType(exp->type, exp->val.cast.exp->type, true)) {
            if (!isNumeric(exp->type) ||
                !isNumeric(exp->val.cast.exp->type)) {
                if (!checkSameType(exp->type, strToType("string"),
                                   true) ||
                    !isInteger(exp->val.cast.exp->type)) {
                    errorType(exp->type->id,
                              exp->val.cast.exp->type->id, exp->lineno);
                }
            }
        }
        // exp->type = exp->val.cast.type;
        break;

    case appendExpr:
        typeEXP(exp->val.append.head);
        typeEXP(exp->val.append.tail);
        if (!isSlices(exp->val.append.head->type)) {
            errorType("slice", exp->val.append.head->type->id, exp->lineno);
        }
        if (!isValidSliceType(exp->val.append.head->type)) {
            errorType("slice1", exp->val.append.head->type->id, exp->lineno);
        }
        TYPE *expectedType = exp->val.append.head->type->underLineType;
        if (!checkSameType(expectedType, exp->val.append.tail->type, false)) {
            errorType(expectedType->id, exp->val.append.tail->type->id,
                      exp->lineno);
        }
        break;
    case lenExpr:
        typeEXP(exp->val.expr);
        if (!isArrayOrSlice(exp->val.expr->type) &&
            !checkSameType(exp->val.expr->type, strToType("string"), false)) {
            errorType("array or slice or string", exp->val.expr->type->id,
                      exp->lineno);
        }
        if (!checkSameType(exp->type, strToType("int"), false)) {
            errorType("int", exp->type->id, exp->lineno);
        }
        break;
    case capExpr:
        typeEXP(exp->val.expr);
        if (!isArrayOrSlice(exp->val.expr->type)) {
            errorType("array or slice", exp->val.expr->type->id, exp->lineno);
        }
        if (!checkSameType(exp->type, strToType("int"), false)) {
            errorType("int", exp->type->id, exp->lineno);
        }
        break;
    case arrayExpr:
    case sliceExpr:;
        typeEXP(exp->val.array.exp);
        typeEXP(exp->val.array.index);
        if (!isArrayOrSlice(exp->val.array.exp->type)) {
            errorType("array or slice", exp->val.array.exp->type->id,
                      exp->lineno);
        }

        // Allow index to be null, maybe create new kind later
        if (!isInteger(exp->val.array.index->type)) {
            errorType("integer", exp->val.array.index->type->id, exp->lineno);
        }

        if(isSlices(exp->val.array.exp->type)){
            exp->kind = sliceExpr;
        }

        break;
    case selectorExpr:
        typeEXP(exp->val.selector.exp);
        if (!isStruct(exp->val.array.exp->type)) {
            errorType("struct", exp->val.array.exp->type->id, exp->lineno);
        }
        TYPE *correspondingType = findSelectorIdType(
            exp->val.selector.name, exp->val.selector.exp->type);
        if (correspondingType == NULL) {
            errorType(exp->val.selector.name, "Does Not Exist", exp->lineno);
        } else {
            exp->type = correspondingType;
        }
        break;
    default:
        break;
    }

    if (exp->next != NULL) {
        typeEXP(exp->next);
    }
}

bool checkExpListSameType(EXP *list, TYPE *type) {
    bool same = true;
    EXP *temp = list;
    while (temp != NULL) {
        if (!checkSameType(temp->type, type, false)) {
            same = false;
            break;
        }
        temp = temp->next;
    }
    return same;
}

void typeCASE_CLAUSE(CASE_CLAUSE *c, TYPE *returnType, TYPE *switchExpType) {
    if (c != NULL) {
        switch (c->kind) {
        case caseK:
            typeEXP(c->caseExp);
            bool expListTypeCorrect = true;
            if (switchExpType != NULL) {
                expListTypeCorrect =
                    checkExpListSameType(c->caseExp, switchExpType);
            } else {
                expListTypeCorrect =
                    checkExpListSameType(c->caseExp, strToType("bool"));
            }
            if (!expListTypeCorrect) {
                fprintf(stderr,
                        "Error: (line %d) expression type does not match "
                        "switch expression type\n",
                        c->lineno);
                exit(1);
            }
            typeSTMT(c->caseStmt, returnType);
            break;
        case defaultK:
            typeSTMT(c->caseStmt, returnType);
            break;
        }
        typeCASE_CLAUSE(c->next, returnType, switchExpType);
    }
}

bool isAddressable(EXP *exp) {
    switch (exp->kind) {
    case idExpr:
        return true;
    case funcExpr:
        if (isSlices(exp->type)) {
            return true;
        } else {
            return false;
        }
    case arrayExpr:
    case sliceExpr:
        return isAddressable(exp->val.array.exp);
    case selectorExpr:
        return isAddressable(exp->val.selector.exp);
    default:
        return false;
    }
}

void checkExpListLValue(EXP *exp) {
    EXP *temp = exp;
    while (temp != NULL) {
        if (!isAddressable(temp)) {
            fprintf(stderr, "Error: (line %d) not an lvalue\n", temp->lineno);
            exit(1);
        }
        temp = temp->next;
    }
}

bool checkSameExpType(EXP *lhs, EXP *rhs) {
    if (strcmp(lhs->type->id, rhs->type->id) == 0 &&
        lhs->type->kind == k_type_id && rhs->type->kind == k_type_id &&
        lhs->type != rhs->type) {
        return false;
    }
    return checkSameType(lhs->type, rhs->type, false);
}

void typeAssignStmt(STMT *stmt) {
    if (stmt != NULL) {
        EXP *lhs = stmt->val.assignStmtVal.lhs;

        EXP *rhs = stmt->val.assignStmtVal.rhs;
        typeEXP(lhs);
        typeEXP(rhs);
        checkExpListLValue(lhs);

        if (!checkSameType(lhs->type, rhs->type, false)) {
            if (lhs && strcmp(lhs->val.id, "_") == 0) {
                return;
            } else {
                if (lhs && lhs->kind == sliceExpr && lhs->val.array.exp &&
                    lhs->val.array.exp->type->kind == k_slices &&
                    checkSameType(lhs->val.array.exp->type->underLineType,
                                  rhs->type, false)) {
                    return;
                } else {
                    fprintf(stderr, "Error: (line %d) invalid assignment1\n",
                            lhs->lineno);
                    exit(1);
                }
            }
        }
        switch (stmt->val.assignStmtVal.assignKind) {
        case normal:
            while (lhs != NULL && rhs != NULL) {
                bool sameType = false;
                if (!checkSameType(lhs->type, rhs->type, false)) {
                    fprintf(stderr, "Error: (line %d) invalid assignment2\n",
                            lhs->lineno);
                    exit(1);
                }
                lhs = lhs->next;
                rhs = rhs->next;
            }
            break;
        case plus:
            if (!isOrdered(lhs->type)) {
                errorType("ordered", lhs->type->id, lhs->lineno);
            } else if (!isOrdered(rhs->type)) {
                errorType("ordered", rhs->type->id, rhs->lineno);
            }
            break;
        case minus:
        case mult:
        case divide:
            if (!isNumeric(lhs->type)) {
                errorType("numeric", lhs->type->id, lhs->lineno);
            } else if (!isNumeric(rhs->type)) {
                errorType("numeric", rhs->type->id, rhs->lineno);
            }
            break;
        case or:
        case xor:
        case mod:
        case leftShift:
        case rightShift:
        case and:
        case bitclear:
            if (!isInteger(lhs->type)) {
                errorType("integer", lhs->type->id, lhs->lineno);
            } else if (!isInteger(rhs->type)) {
                errorType("integer", rhs->type->id, rhs->lineno);
            }
            break;
        }
    }
}

void typeFOR_CLAUSE(FOR_CLAUSE *f, TYPE *returnType) {
    if (f != NULL) {
        typeSTMT(f->first, returnType);
        typeEXP(f->condtion);
        if (f->condtion != NULL &&
            !checkSameType(f->condtion->type, strToType("bool"), true)) {
            fprintf(stderr,
                    "Error: (line %d) for condition must be a boolean\n",
                    f->lineno);
            exit(1);
        }
        typeSTMT(f->post, returnType);
    }
}

bool checkExpListBaseType(EXP *exp_list) {
    EXP *temp = exp_list;
    bool base = true;
    while (temp != NULL) {
        if (isArrayOrSlice(temp->type) || !isTypeBaseType(temp->type, true)) {
            base = false;
            break;
        }
        temp = temp->next;
    }
    return base;
}

void checkDuplicateIdInList(ID_LIST *i) {
    if (i == NULL)
        return;
    ID_LIST *temp = i;
    ID_LIST *curr = i;
    while (temp != NULL) {
        curr = temp->next;
        while (curr != NULL) {
            if (strcmp(temp->id, curr->id) == 0) {
                fprintf(stderr,
                        "Error: (line %d) duplicate variable in one short "
                        "declaration\n",
                        i->lineno);
                exit(1);
            }
            curr = curr->next;
        }
        temp = temp->next;
    }
}

void typeSTMT(STMT *stmt, TYPE *returnType) {
    if (stmt != NULL) {
        switch (stmt->kind) {
        case continueStmt:
        case breakStmt:
            break;
        case blockStmt:
            typeSTMT(stmt->val.block, returnType);
            break;
        case ifStmt:
            if (stmt->val.ifStmtVal.ifSimpleStmt != NULL) {
                typeSTMT(stmt->val.ifStmtVal.ifSimpleStmt, returnType);
            }
            typeEXP(stmt->val.ifStmtVal.ifCond);
            if (!checkSameType(stmt->val.ifStmtVal.ifCond->type,
                               strToType("bool"), true)) {
                fprintf(stderr,
                        "Error: (line %d) if condition must be a boolean\n",
                        stmt->lineno);
                exit(1);
            }
            typeSTMT(stmt->val.ifStmtVal.ifBody, returnType);
            typeSTMT(stmt->val.ifStmtVal.elseStmt, returnType);
            break;
        case elseStmt:
            typeSTMT(stmt->val.elseStmtVal.elseBody, returnType);
            typeSTMT(stmt->val.elseStmtVal.ifStmt, returnType);
            break;
        case printStmt:
            typeEXP(stmt->val.printExpList);
            if (!checkExpListBaseType(stmt->val.printExpList)) {
                fprintf(stderr,
                        "Error: (line %d) expression in print statement must "
                        "be of base type\n",
                        stmt->lineno);
                exit(1);
            }
            break;
        case printlnStmt:
            typeEXP(stmt->val.printlnExpList);
            if (!checkExpListBaseType(stmt->val.printExpList)) {
                fprintf(stderr,
                        "Error: (line %d) expression in println statement must "
                        "be of base type\n",
                        stmt->lineno);
                exit(1);
            }
            break;
        case returnStmt:;
            EXP *returnExp = stmt->val.returnExp;
            if (returnType == NULL && returnExp != NULL) {
                fprintf(stderr,
                        "Error: (line %d) this function should not return "
                        "anything\n",
                        stmt->lineno);
                exit(1);
            } else if (returnType != NULL && returnExp == NULL) {
                fprintf(
                    stderr,
                    "Error: (line %d) this function should return something\n",
                    stmt->lineno);
                exit(1);
            } else if (returnType != NULL && returnExp != NULL) {
                typeEXP(returnExp);
                if (!checkSameType(returnExp->type, returnType, false)) {
                    fprintf(stderr, "Error: (line %d) wrong return type\n",
                            stmt->lineno);
                    exit(1);
                }
            }
            if (stmt->next != NULL) {
                fprintf(stderr, "Error: (line %d) dead code\n",
                        stmt->lineno + 1);
                exit(1);
            }
            break;
        case switchStmt:
            if (stmt->val.switchStmtVal.switchSimpleStmt != NULL) {
                typeSTMT(stmt->val.switchStmtVal.switchSimpleStmt, returnType);
            }
            EXP *switchExp = stmt->val.switchStmtVal.switchExp;
            typeEXP(switchExp);
            if (switchExp != NULL) {
                if (switchExp->type != NULL) {
                    if (!isComparable(switchExp->type)) {
                        fprintf(stderr,
                                "Error: (line %d) switch expression must be a "
                                "comparable expression\n",
                                stmt->lineno);
                        exit(1);
                    } else {
                        typeCASE_CLAUSE(stmt->val.switchStmtVal.switchCases,
                                        returnType, switchExp->type);
                    }
                } else {
                    fprintf(stderr,
                            "Error: (line %d) void cannot be used as switch "
                            "expression\n",
                            stmt->lineno);
                    exit(1);
                }
            } else {
                typeCASE_CLAUSE(stmt->val.switchStmtVal.switchCases, returnType,
                                NULL);
            }
            break;
        case emptyStmt:
            break;
        case expStmt:
            typeEXP(stmt->val.expStmtVal);
            break;
        case assignStmt:
            typeAssignStmt(stmt);
            break;
        case incStmt:
            typeEXP(stmt->val.incExp);
            if (!isAddressable(stmt->val.incExp)) {
                fprintf(
                    stderr,
                    "Error: (line %d) increment expression must be lvalue\n",
                    stmt->lineno);
                exit(1);
            }
            if (!checkSameType(stmt->val.incExp->type, strToType("int"),
                               true) &&
                !checkSameType(stmt->val.incExp->type, strToType("float64"),
                               true) &&
                !checkSameType(stmt->val.incExp->type, strToType("rune"),
                               true)) {
                fprintf(stderr,
                        "Error: (line %d) invalid increment statement\n",
                        stmt->lineno);
                exit(1);
            }
            break;
        case decStmt:
            typeEXP(stmt->val.decExp);
            if (!isAddressable(stmt->val.decExp)) {
                fprintf(
                    stderr,
                    "Error: (line %d) decrement expression must be lvalue\n",
                    stmt->lineno);
                exit(1);
            }
            if (!checkSameType(stmt->val.decExp->type, strToType("int"),
                               true) &&
                !checkSameType(stmt->val.decExp->type, strToType("float64"),
                               true) &&
                !checkSameType(stmt->val.decExp->type, strToType("rune"),
                               true)) {
                fprintf(stderr,
                        "Error: (line %d) invalid decrement statement\n",
                        stmt->lineno);
                exit(1);
            }
            break;
        case shortVarDecStmt:
            checkDuplicateIdInList(stmt->val.shortVarDecStmtVal.ids);
            typeIdListExpList(stmt->val.shortVarDecStmtVal.ids,
                              stmt->val.shortVarDecStmtVal.exps);
            break;
        case forStmt:;
            EXP *forCond = stmt->val.forStmtVal.forCond;
            if (forCond != NULL) {
                typeEXP(forCond);
                if (!checkSameType(forCond->type, strToType("bool"), true)) {
                    fprintf(stderr,
                            "Error: (line %d) for condition must be a boolean "
                            "but got %s\n",
                            stmt->lineno, forCond->type->id);
                    exit(1);
                }
            }
            typeFOR_CLAUSE(stmt->val.forStmtVal.forClause, returnType);
            typeSTMT(stmt->val.forStmtVal.forBody, returnType);
            break;
        case dclStmt:
            typeDecl(stmt->val.decStmtVal, 1);
            break;
        }
        if (stmt->next) {
            typeSTMT(stmt->next, returnType);
        }
    }
}
