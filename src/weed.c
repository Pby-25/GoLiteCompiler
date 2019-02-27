#include "weed.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void checkIdBlank(char *name, char *id, int lineno) {
    if (strcmp(id, "_") == 0) {
        fprintf(stderr, "Error: (line %d) %s cannot be blank identifier\n",
                lineno, name);
        exit(1);
    }
}

void weedIMPORTS(IMPORT *i) {
    if (i == NULL) {
        return;
    }
    checkIdBlank("Import name", i->id, i->lineno);
    weedIMPORTS(i->next);
}

void weedPROGRAM(PROGRAM *p) {
    if (p != NULL) {
        checkIdBlank("Package name", p->package->id, p->package->lineno);
        weedIMPORTS(p->imports);
        weedTOPDECL(p->top_decl);
    }
}

void weedTOPDECL(TOPDECL *top_decl) {
    
    if (top_decl == NULL) {
        return;
    }
    switch (top_decl->kind) {
    case dclK:
        weedDECL(top_decl->val.dcl);
        break;
    case funcDeclK:
        weedFUNCDECL(top_decl->val.funcDecl);
        break;
    }
    weedTOPDECL(top_decl->next);
}

void weedDECL(DCL *dcl) {
    
    if (dcl == NULL) {
        return;
    }
    switch (dcl->kind) {
    case typeDcl:
        weedTypeDcl(dcl->val.typeDecl);
        break;
    case varDcl:
        weedVarDcl(dcl->val.varDecl);
        break;
    }
}

void weedTypeDcl(TYPEDECL *t) {
    

    if (t == NULL) {
        return;
    }
    weedTypeSpec(t->typeSpec);
}

void weedTypeSpec(TYPESPEC *ts) {
    

    if (ts == NULL) {
        return;
    }
    weedType(ts->type);
    weedTypeSpec(ts->next);
}

void weedType(TYPE *t) {
    
    
    if (t == NULL) {
        return;
    }
    switch (t->kind) {
    case k_slices:
        break;
    case k_array:
        break;
    case k_type_struct:
        weedField_Dcl(t->struct_type.field_dcls);
        break;
    case k_type_id:
        checkIdBlank("Type ",t->id, t->lineno);
        break;
    case k_type_type:
        weedType(t->types);
        break;
    }
}
void weedField_Dcl(FIELD_DCL *f) {
    

    if (f == NULL) {
        return;
    }
    weedType(f->type);
    weedField_Dcl(f->next);
}

void weedIdListExpList(ID_LIST *i, EXP *e, int lineno) {
    
    
    if (e == NULL) {
        return;
    }
    ID_LIST *hi = i;
    EXP *ei = e;
    while (hi != NULL && ei != NULL) {
        hi = hi->next;
        ei = ei->next;
    }
    if (hi != NULL || ei != NULL) {
        fprintf(
            stderr,
            "Error: (line %d) Identifier list not same length with exp list\n",
            lineno);
        exit(1);
    }
}

void weedVarDcl(VARDECL *v) {
    

    if (v == NULL) {
        return;
    }
    weedVarSpec(v->var_specs);
}

void weedVarSpec(VARSPEC *vs) {
    

    if (vs == NULL) {
        return;
    }
    weedIdListExpList(vs->id_list, vs->exp_list, vs->lineno);
    weedType(vs->type);
    weedVarSpec(vs->next);
}

void weedFUNCDECL(FUNCDECL *func_decl) {
    
    if (func_decl != NULL && func_decl->signature != NULL) {
        if (func_decl->signature->result != NULL) {
            weedPARAMS(func_decl->signature->params);
            weedPARAMS(func_decl->signature->result->params);
            weedType(func_decl->signature->result->type);
        }
    }
    weedSTMT(func_decl->body, 0, 0);
}

void weedPARAMS(PARAMS *params) {
    

    if (params == NULL) {
        return;
    }
    PARAMS *p = params;
    while (p != NULL && p->id_list != NULL) {
        ID_LIST *il = p->id_list;
        while (il != NULL) {
            // checkIdBlank("Params", il->id, il->lineno);
            il = il->next;
        }
        weedType(params->type);
        p = p->next;
    }
}

void weedEXP(EXP *exp, int blank_allow) {
    

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
    case timesExpr:
    case divExpr:
    case modExpr:
    case leftShiftExpr:
    case rightShiftExpr:
    case bitwiseAndExpr:
    case bitClearExpr:
        weedEXP(exp->val.binary.lhs, 0);
        weedEXP(exp->val.binary.rhs, 0);
        break;
    case uMinusExpr:
    case uPlusExpr:
    case uBangExpr:
    case uCaretExpr:
    case uBitwiseAndExpr:
        weedEXP(exp->val.unary.exp, 0);
        break;

    case idExpr:
        if (blank_allow == 0) {
            if (strcmp(exp->val.id, "_") == 0) {
                fprintf(stderr,
                        "Error: (line %d) Illegal use of blank identifier.\n",
                        exp->lineno);
                exit(1);
            }
        }
        break;

    case funcExpr:
        weedEXP(exp->val.func.name, 0);
        weedEXP(exp->val.func.args, 0);
        break;

    case castExpr:
        weedEXP(exp->val.cast.type, 0);
        weedEXP(exp->val.cast.exp, 0);
        break;

    case appendExpr:
        weedEXP(exp->val.append.head, 0);
        weedEXP(exp->val.append.tail, 0);
        break;

    case arrayExpr:
    case sliceExpr:
        weedEXP(exp->val.array.exp, 0);
        weedEXP(exp->val.array.index, 0);
        break;

    case selectorExpr:
        weedEXP(exp->val.selector.exp, 0);
        if (blank_allow == 0) {
            if (strcmp(exp->val.selector.name, "_") == 0) {
                fprintf(stderr,
                        "Error: (line %d) Illegal use of blank identifier.\n",
                        exp->lineno);
                exit(1);
            }
        }
        break;

    case expList:;
        EXP *e = exp;
        while (e->val.expr != NULL) {
            weedEXP(e->val.expr, blank_allow);
            e = e->next;
        }

    default:
        break;
    }
}

void weedCASE_CLAUSE(CASE_CLAUSE *case_clause, int inLoop, int inSwitch,
                     int hasDefault) {
    if (case_clause != NULL) {
        weedEXP(case_clause->caseExp, 0);
        weedSTMT(case_clause->caseStmt, inLoop, inSwitch);
        switch (case_clause->kind) {
            case caseK:
                weedCASE_CLAUSE(case_clause->next, inLoop, inSwitch, hasDefault);
                break;
            case defaultK:
                if (hasDefault) {
                    fprintf(stderr, "Error: (line %d) multiple default cases.\n",
                            case_clause->lineno);
                    exit(1);
                }
                weedCASE_CLAUSE(case_clause->next, inLoop, inSwitch, 1);
                break;
        }
    }
}

void weedFOR_CLAUSE(FOR_CLAUSE *for_clause, int inLoop, int inSwitch) {
    if (for_clause != NULL) {
        weedSTMT(for_clause->first, inLoop, inSwitch);
        weedSTMT(for_clause->last, inLoop, inSwitch);
        if (for_clause->doStmt != NULL && for_clause->doStmt->kind == shortVarDecStmt) {
            fprintf(stderr, "Error: (line %d) for loop post statement cannot be short declaration.\n", for_clause->doStmt->lineno);
            exit(1);
        }
        weedSTMT(for_clause->doStmt, inLoop, inSwitch);
    }
}

void checkExpListLengthEqual(EXP *e1, EXP *e2){
    if (e1 != NULL && e2 != NULL) {
        EXP *a = e1;
        EXP *b = e2;
        while (a != NULL && b != NULL) {
            a = a->next;
            b = b->next;
        } 
        if (a != NULL || b != NULL) {
            fprintf(stderr, "Error: (line %d) Illegal use of blank identifier.\n", e1->lineno);
            exit(1);
        }
    }
}

void weedSTMT(STMT *stmt, int inLoop, int inSwitch) {
    if (stmt != NULL) {
        switch (stmt->kind) {
        case continueStmt:
            if (inLoop != 1) {
                fprintf(stderr,
                        "Error: (line %d) invalid continue statement.\n",
                        stmt->lineno);
                exit(1);
            }
            break;
        case breakStmt:
            if (inLoop != 1 && inSwitch != 1) {
                fprintf(stderr, "Error: (line %d) invalid break statement.\n",
                        stmt->lineno);
                exit(1);
            }
            break;
        case blockStmt:
            weedSTMT(stmt->val.block, inLoop, inSwitch);
            break;
        case ifStmt:
            weedEXP(stmt->val.ifStmtVal.ifCond, 0);
            weedSTMT(stmt->val.ifStmtVal.ifSimpleStmt, inLoop, inSwitch);
            weedSTMT(stmt->val.ifStmtVal.ifBody, inLoop, inSwitch);
            weedSTMT(stmt->val.ifStmtVal.elseStmt, inLoop, inSwitch);
            break;
        case elseStmt:
            weedSTMT(stmt->val.elseStmtVal.elseBody, inLoop, inSwitch);
            weedSTMT(stmt->val.elseStmtVal.ifStmt, inLoop, inSwitch);
            break;
        case printStmt:
            weedEXP(stmt->val.printExpList, 0);
            break;
        case printlnStmt:
            weedEXP(stmt->val.printlnExpList, 0);
            break;
        case returnStmt:
            weedEXP(stmt->val.returnExp, 0);
            break;
        case switchStmt:
            weedEXP(stmt->val.switchStmtVal.switchExp, 0);
            weedSTMT(stmt->val.switchStmtVal.switchSimpleStmt, inLoop,
                     inSwitch);
            weedCASE_CLAUSE(stmt->val.switchStmtVal.switchCases, inLoop, 1, 0);
            break;
        case emptyStmt:
            break;
        case expStmt:
            if(stmt->val.expStmtVal->kind != funcExpr ){
                fprintf(stderr,
                        "Error: (line %d) Exp stmt must be func call.\n",
                        stmt->lineno);
                exit(1);
            }
            weedEXP(stmt->val.expStmtVal, 0);
            break;
        case assignStmt:
            checkExpListLengthEqual(stmt->val.assignStmtVal.lhs, stmt->val.assignStmtVal.rhs);
            weedEXP(stmt->val.assignStmtVal.lhs, 1);
            weedEXP(stmt->val.assignStmtVal.rhs, 0);
            break;
        case incStmt:
            weedEXP(stmt->val.incExp, 1);
            break;
        case decStmt:
            weedEXP(stmt->val.decExp, 1);
            break;
        case shortVarDecStmt:
            weedIdListExpList(stmt->val.shortVarDecStmtVal.ids,
                              stmt->val.shortVarDecStmtVal.exps, stmt->lineno);
            weedEXP(stmt->val.shortVarDecStmtVal.exps, 0);
            break;
        case forStmt:
            weedEXP(stmt->val.forStmtVal.forCond, 0);
            weedFOR_CLAUSE(stmt->val.forStmtVal.forClause, inLoop, inSwitch);
            weedSTMT(stmt->val.forStmtVal.forBody, 1, inSwitch);
            break;
        case dclStmt:
            weedDECL(stmt->val.decStmtVal);
            break;
        default:
            break;
        }
        weedSTMT(stmt->next, inLoop, inSwitch);
    }
}