#include "pretty.h"
#include "SymbolTable.h"
#include "stdio.h"
#include "string.h"
#include "tree.h"
#include <stdlib.h>

void prettyImports(IMPORT *i) {
    if (i != NULL) {
        printf("import %s; \n", i->id);
        prettyImports(i->next);
    }
}

void prettyDecl(DCL* d) {
    if (d != NULL) {
        
    }
}

void prettyIDList(ID_LIST *i) {
    if (i != NULL) {
        printf("%s", i->id);
        if (i->next != NULL) {
            printf(", ");
            prettyIDList(i->next);
        }
    }
}

void prettyType(TYPE *t) {
    if (t != NULL) {
        
    }
}

void prettyParams(PARAMS *p) {
    if (p != NULL) {
        prettyIDList(p->id_list);
        prettyType(p->type);
        prettyParams(p->next);
    }
}

void prettyResult(RESULT *r) {

}

void prettySig(SIGNATURE *s) {
    if (s != NULL) {
        prettyParams(s->params);
        prettyResult(s->result);
    }
}

void prettyFuncDecl(FUNCDECL *f) {
    if (f != NULL) {
        printf("func %s", f->id);
        printf("(");
        prettySig(f->signature);
        printf(")");
        prettyStmts(f->body);
    }
}

void prettyTopDecl(TOPDECL* t) {
    if (t != NULL) {
        switch (t->kind) {
            case dclK:
                prettyDecl(t->val.dcl);
                break;
            case funcDeclK:
                prettyFuncDecl(t->val.funcDecl);
                break;
        }
        prettyTopDecl(t->next);
    }
}

void prettyProg(PROGRAM *root) { 
    if (root != NULL) {
        printf("package %s ;\n", root->package->id);
        prettyImports(root->imports);
        prettyTopDecl(root->top_decl);
    }
}





void prettyEXP(EXP *exp) {

    if (exp == NULL)
        return;
    switch (exp->kind) {
    case orExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" || ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;                                                            
    case andExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" && ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case equalsExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" == ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case notequalsExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" != ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case lessExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" < ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;        
    case greaterExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" > ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;        
    case lessEqualsExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" <= ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case greaterEqualsExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" >= ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case plusExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" + ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case minusExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" - ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case bitwiseOrExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" | ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case bitwiseXorExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" ^ ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case bitwiseAndExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" & ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case bitClearExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" &^ ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;    
    case timesExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" * ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;    
    case divExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" / ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case modExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" % ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;    
    case leftShiftExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" << ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case rightShiftExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" >> ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case uMinusExpr:
        printf(" -");
        prettyEXP(exp->val.unary.exp);
        break;    
    case uPlusExpr:
        printf(" +");
        prettyEXP(exp->val.unary.exp);
        break;
    case uBangExpr:
        printf(" !");
        prettyEXP(exp->val.unary.exp);
        break;
    case uCaretExpr:
        printf(" ^");
        prettyEXP(exp->val.unary.exp);
        break;    
    case uBitwiseAndExpr:
        printf(" &");
        prettyEXP(exp->val.unary.exp);
        break;

    case funcExpr:
        prettyEXP(exp->val.func.name);
        printf("(");
        prettyEXP(exp->val.func.args);
        printf(")");
        break;

    case castExpr:
        prettyEXP(exp->val.cast.type);
        printf("(");
        prettyEXP(exp->val.cast.exp);
        printf(")");
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

    case intExpr:
    case floatExpr:
    case runeExpr:
    case stringItpExpr:
    case stringRawExpr:
    case idExpr:
    case boolExpr:
    default:
        break;
    }
}

void prettySTMT(STMT *stmt) {
    if (stmt != NULL) {
        switch (stmt->kind) {
        case continueStmt:
            printf("continue\n");
            break;
        case breakStmt:
            printf("break\n");
            break;
        case blockStmt:
            printf("{\n");
            prettySTMT(stmt->val.block);
            printf("}\n");
            break;
        case ifStmt:
            printf("if ");
            if (stmt->val.ifStmtVal.ifSimpleStmt != NULL){
                prettySTMT(stmt->val.ifStmtVal.ifSimpleStmt);
                printf(";");
            }
            prettyEXP(stmt->val.ifStmtVal.ifCond);
            prettySTMT(stmt->val.ifStmtVal.ifBody);
            prettySTMT(stmt->val.ifStmtVal.elseStmt);
            break;
        case elseStmt:
            printf("else ");
            prettySTMT(stmt->val.elseStmtVal.elseBody);
            prettySTMT(stmt->val.elseStmtVal.ifStmt);
            break;
        case printStmt:
            printf("print(");
            prettyEXP(stmt->val.printExpList);
            printf(")\n");
            break;
        case printlnStmt:
            printf("println(");
            prettyEXP(stmt->val.printlnExpList);
            printf(")\n");
            break;
        case returnStmt:
            printf("return ")
            prettyEXP(stmt->val.returnExp);
            printf("\n");
            break;
        case switchStmt:
            printf("switch");
            prettySTMT(stmt->val.switchStmtVal.switchSimpleStmt);
            prettyEXP(stmt->val.switchStmtVal.switchExp);
            
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
            prettySTMT(stmt->val.forStmtVal.forBody, 1, inSwitch);
            break;
        case dclStmt:
            weedDECL(stmt->val.decStmtVal);
            break;
        default:
            break;
        }
        prettySTMT(stmt->next, inLoop, inSwitch);
    }
}