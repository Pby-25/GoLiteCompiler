#include "pretty.h"
#include "SymbolTable.h"
#include "stdio.h"
#include "string.h"
#include "tree.h"
#include <stdlib.h>

int indentation = 0;

void printIndentation() {
    for (int i = 0; i < indentation; i++) {
        printf("    ");
    }
}

void prettyImports(IMPORT *i) {
    if (i != NULL) {
        printf("import %s\n", i->id);
        prettyImports(i->next);
    }
}

void prettyDecl(DCL *d, int infunc) {
    if (d != NULL) {
        switch (d->kind) {
        case typeDcl:
            prettyTypeDcl(d->val.typeDecl);
            break;
        case varDcl:
            prettyVarDcl(d->val.varDecl,infunc);
            break;
        }
    }
}
void prettyTypeDcl(TYPEDECL *t) {
    if (t != NULL) {
        printf("type ");
        indentation ++;
        prettyTypeSpec(t->typeSpec, 1);
        indentation --;
    }
}
void prettyVarDcl(VARDECL *v, int infunc) {
    if (v != NULL) {
        prettyVarSpec(v->var_specs, infunc);
    }
}

void prettyTypeSpec(TYPESPEC *ts, int needParen) {
    if (ts == NULL) {
        if(needParen){
            printf("( )\n");
        }
        return;
    }
    if (needParen) {
        printf("(");
    }
    printf("\n");
    printIndentation();
    printf("%s ", ts->id);
    prettyType(ts->type);
    prettyTypeSpec(ts->next,0);
    if (ts->next == NULL) {
        printf("\n");
        indentation --;
        printIndentation();
        printf(")\n");
        indentation ++;
    }
}

void prettyVarSpec(VARSPEC *vs, int infunc) {
    if (vs == NULL) {
        return;
    }
    VARSPEC *vsPtr = vs;
    printf("var ");
    if (vsPtr->next){
        printf("(\n");
        indentation++;
        while (vsPtr){
            printIndentation();
            prettyIDList(vsPtr->id_list);
            printf(" ");
            prettyType(vsPtr->type);

            EXP *c = vsPtr->exp_list;
            if(c!=NULL){
                printf("= ");
            }
            prettyEXP(c);
            if(vsPtr->next != NULL && infunc){
                printf("\n");
            }
            if(!infunc){
                printf("\n");
            }
            vsPtr = vsPtr->next;
        }
        printf("\n");
        indentation--;
        printIndentation();
        printf(")\n");
    } else {
        prettyIDList(vs->id_list);
        printf(" ");
        prettyType(vs->type);

        EXP *c = vs->exp_list;
        if(c!=NULL){
            printf("= ");
        }
        prettyEXP(c);
        if(vs->next != NULL && infunc){
            printf("\n");
        }
        if(!infunc){
            printf("\n");
        }
    }
}

void prettyField_Dcl(FIELD_DCL *f) {
    if (f == NULL) {
        return;
    }
    printIndentation();
    prettyIDList(f->id_list);
    printf(" ");
    prettyType(f->type);
    printf("\n");
    prettyField_Dcl(f->next);
}

void prettyIDList(ID_LIST *i) {
    if (i != NULL) {
        printf("%s", i->id);
        if (i->next != NULL) {
            printf(", "); 
        }
        prettyIDList(i->next);
    }
}

void prettyType(TYPE *t) {
    if (t != NULL) {
        switch (t->kind) {
        case k_type_id:
            printf("%s ", t->id);
            break;
        case k_slices:
            printf("[]");
            prettyType(t->slices_type.type);
            break;
        case k_array:
            printf("[%d] ", t->array_type.size);
            prettyType(t->array_type.type);
            break;
        case k_type_struct:
            printf("struct {\n");
            indentation ++;
            prettyField_Dcl(t->struct_type.field_dcls);
            indentation --;
            printIndentation();
            printf("}");
            break;
        case k_type_type:
            printf("(");
            prettyType(t->types);
            printf(")");
            break;
        }
    }
}

void prettyParams(PARAMS *p) {
    if (p != NULL) {
        prettyIDList(p->id_list);
        printf(" ");
        prettyType(p->type);
        if(p->next !=NULL){
            printf(",");
            prettyParams(p->next);
        }
        
    }
}

void prettyResult(RESULT *r) {
    if (r != NULL) {
        prettyParams(r->params);
        prettyType(r->type);
    }
}

void prettySig(SIGNATURE *s) {
    if (s != NULL) {
        prettyParams(s->params);
        printf(")");
        prettyResult(s->result);
    }
}

void prettyFuncDecl(FUNCDECL *f) {
    if (f != NULL) {
        printf("func %s", f->id);
        printf("(");
        prettySig(f->signature);
        prettySTMT(f->body, true, true);
    }
}

void prettyTopDecl(TOPDECL *t) {
    if (t != NULL) {
        switch (t->kind) {
        case dclK:
            prettyDecl(t->val.dcl, 0);
            break;
        case funcDeclK:
            prettyFuncDecl(t->val.funcDecl);
            break;
        }
        prettyTopDecl(t->next);
    }
}

void prettyPROGRAM(PROGRAM *root) {
    if (root != NULL) {
        printf("package %s;\n", root->package->id);
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
        printf(" %% ");
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
        prettyType(exp->val.cast.type);
        printf("(");
        prettyEXP(exp->val.cast.exp);
        printf(")");
        break;

    case appendExpr:
        printf("append(");
        prettyEXP(exp->val.append.head);
        printf(",");
        prettyEXP(exp->val.append.tail);
        printf(")");
        break;
    case lenExpr:
        printf("len(");
        prettyEXP(exp->val.expr);
        printf(")");
        break;
    case capExpr:
        printf("cap(");
        prettyEXP(exp->val.expr);
        printf(")");
        break;
    case arrayExpr:
        prettyEXP(exp->val.array.exp);
        printf("[");
        prettyEXP(exp->val.array.index);
        printf("]");
        break;
    case selectorExpr:
        prettyEXP(exp->val.selector.exp);
        printf(".%s", exp->val.selector.name);
        break;
    case idExpr:
        printf("%s", exp->val.id);
        break;
    case intExpr:
        printf("%d", exp->val.intVal);
        break;
    case floatExpr:
        printf("%f", exp->val.floatVal);
        break;
    case runeExpr:
        printf("%d", exp->val.runeVal);
        break;
    case stringItpExpr:
        printf("%s", exp->val.stringVal);
        break;
    case stringRawExpr:
        printf("%s", exp->val.stringVal);
        break;
    default:
        break;
    }

    if (exp->next != NULL) {
            printf(", ");
            prettyEXP(exp->next);
    }
}

void prettyCASE_CLAUSE(CASE_CLAUSE *c) {
    if (c != NULL) {
        printIndentation();
        switch (c->kind) {
        case caseK:
            printf("case ");
            prettyEXP(c->caseExp);
            printf(" :\n");
            indentation++;
            prettySTMT(c->caseStmt, true, true);
            indentation--;
            break;
        case defaultK:
            printf("default:\n");
            indentation++;
            prettySTMT(c->caseStmt, true, true);
            indentation--;
            break;
        }
        prettyCASE_CLAUSE(c->next);
    }
}

void prettyAssignStmt(STMT *stmt) {
    if (stmt != NULL) {
        prettyEXP(stmt->val.assignStmtVal.lhs);
        switch (stmt->val.assignStmtVal.assignKind) {
        case normal:
            printf(" = ");
            break;
        case plus:
            printf(" += ");
            break;
        case minus:
            printf(" -= ");
            break;
        case mult:
            printf(" *= ");
            break;
        case divide:
            printf(" /= ");
            break;
        case or:
            printf(" |= ");
            break;
        case xor:
            printf(" ^= ");
            break;
        case mod:
            printf(" %%= ");
            break;
        case leftShift:
            printf(" <<= ");
            break;
        case rightShift:
            printf(" >>= ");
            break;
        case and:
            printf(" &= ");
            break;
        case bitclear:
            printf(" &^= ");
            break;
        }
        prettyEXP(stmt->val.assignStmtVal.rhs);
    }
}

void prettyFOR_CLAUSE(FOR_CLAUSE *f) {
    if (f != NULL) {
        prettySTMT(f->first, false, false);
        printf(";");
        prettyEXP(f->condtion);
        printf(";");
        prettySTMT(f->post, false, false);
    }
}

void prettySTMT(STMT *stmt, bool to_indent, bool new_line) {
    if (to_indent && stmt!=NULL && stmt->kind != emptyStmt) {
        printIndentation();
    }
    if (stmt != NULL) {
        switch (stmt->kind) {
        case continueStmt:
            printf("continue");
            break;
        case breakStmt:
            printf("break");
            break;
        case blockStmt:
            printf("{");
            printf("\n");
            indentation++;
            prettySTMT(stmt->val.block, true, true);
            indentation--;
            printIndentation();
            printf("}");
            break;
        case ifStmt:
            printf("if ");
            if (stmt->val.ifStmtVal.ifSimpleStmt != NULL) {
                prettySTMT(stmt->val.ifStmtVal.ifSimpleStmt, false, false);
                printf(";");
            }
            prettyEXP(stmt->val.ifStmtVal.ifCond);
            bool newLine = false;
            if(stmt->val.ifStmtVal.elseStmt == NULL){
                newLine = true;
            }
            prettySTMT(stmt->val.ifStmtVal.ifBody, false, newLine);
            prettySTMT(stmt->val.ifStmtVal.elseStmt, false, newLine);
            break;
        case elseStmt:
            printf("else ");
            prettySTMT(stmt->val.elseStmtVal.elseBody, false, newLine);
            prettySTMT(stmt->val.elseStmtVal.ifStmt, false, newLine);
            break;
        case printStmt:
            printf("print(");
            prettyEXP(stmt->val.printExpList);
            printf(")");
            break;
        case printlnStmt:
            printf("println(");
            prettyEXP(stmt->val.printlnExpList);
            printf(")");
            break;
        case returnStmt:
            printf("return ");
            prettyEXP(stmt->val.returnExp);
            break;
        case switchStmt:
            printf("switch ");
            if (stmt->val.switchStmtVal.switchSimpleStmt != NULL) {
                prettySTMT(stmt->val.switchStmtVal.switchSimpleStmt, false, false);
                printf(";");
            }
            prettyEXP(stmt->val.switchStmtVal.switchExp);
            printf("{");
            printf("\n");
            prettyCASE_CLAUSE(stmt->val.switchStmtVal.switchCases);
            printf("}");
            break;
        case emptyStmt:
            break;
        case expStmt:
            printf("(");
            prettyEXP(stmt->val.expStmtVal);
            printf(")");
            break;
        case assignStmt:
            prettyAssignStmt(stmt);
            break;
        case incStmt:
            prettyEXP(stmt->val.incExp);
            printf("++");
            break;
        case decStmt:
            prettyEXP(stmt->val.decExp);
            printf("--");
            break;
        case shortVarDecStmt:
            prettyIDList(stmt->val.shortVarDecStmtVal.ids);
            printf(" := ");
            prettyEXP(stmt->val.shortVarDecStmtVal.exps);
            break;
        case forStmt:
            printf("for ");
            prettyEXP(stmt->val.forStmtVal.forCond);
            prettyFOR_CLAUSE(stmt->val.forStmtVal.forClause);
            printf(" ");
            prettySTMT(stmt->val.forStmtVal.forBody, false, true);
            break;
        case dclStmt:
            prettyDecl(stmt->val.decStmtVal, 1);
            break;
        }
        if (new_line && stmt->kind != emptyStmt) {
            printf("\n");
        }
        if (stmt->next){
            prettySTMT(stmt->next, to_indent, new_line);    
        }
    }
}