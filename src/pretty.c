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
        printf("{\n")
        prettyStmts(f->body);
        printf("}\n")
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
        printf(" - ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;    
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

// void prettyExp(EXP *e) {
//     if (e == NULL) {
//         return;
//     }
//     switch (e->kind) {
//     case k_expressionKindIntLiteral:
//         printf("%d", e->val.intLiteral);
//         break;
//     case k_expressionKindStringLiteral:
//         printf("%s", e->val.stringLiteral);
//         break;
//     case k_expressionKindFloatLiteral:
//         printf("%f", e->val.floatLiteral);
//         break;
//     case k_expressionKindBooleanLiteral:
//         switch (e->val.booleanLiteral) {
//         case 0:
//             printf("false");
//             break;
//         case 1:
//             printf("true");
//         }
//         break;
//     case k_expressionKindPlusExp:
//         printf("(");
//         prettyExp(e->val.binary.lhs);
//         printf(" + ");
//         prettyExp(e->val.binary.rhs);
//         printf(")");
//         break;
//     case k_expressionKindMinusExp:
//         printf("(");
//         prettyExp(e->val.binary.lhs);
//         printf(" - ");
//         prettyExp(e->val.binary.rhs);
//         printf(")");
//         break;
//     case k_expressionKindTimesExp:
//         printf("(");
//         prettyExp(e->val.binary.lhs);
//         printf(" * ");
//         prettyExp(e->val.binary.rhs);
//         printf(")");
//         break;
//     case k_expressionKindDivExp:
//         printf("(");
//         prettyExp(e->val.binary.lhs);
//         printf(" / ");
//         prettyExp(e->val.binary.rhs);
//         printf(")");
//         break;
//     case k_expressionKindEqExp:
//         printf("(");
//         prettyExp(e->val.binary.lhs);
//         printf(" == ");
//         prettyExp(e->val.binary.rhs);
//         printf(")");
//         break;
//     case k_expressionKindNeqExp:
//         printf("(");
//         prettyExp(e->val.binary.lhs);
//         printf(" != ");
//         prettyExp(e->val.binary.rhs);
//         printf(")");
//         break;
//     case k_expressionKindGeqExp:
//         printf("(");
//         prettyExp(e->val.binary.lhs);
//         printf(" >= ");
//         prettyExp(e->val.binary.rhs);
//         printf(")");
//         break;
//     case k_expressionKindLeqExp:
//         printf("(");
//         prettyExp(e->val.binary.lhs);
//         printf(" <= ");
//         prettyExp(e->val.binary.rhs);
//         printf(")");
//         break;
//     case k_expressionKindGreaterExp:
//         printf("(");
//         prettyExp(e->val.binary.lhs);
//         printf(" > ");
//         prettyExp(e->val.binary.rhs);
//         printf(")");
//         break;
//     case k_expressionKindLessExp:
//         printf("(");
//         prettyExp(e->val.binary.lhs);
//         printf(" < ");
//         prettyExp(e->val.binary.rhs);
//         printf(")");
//         break;
//     case k_expressionKindAndExp:
//         printf("(");
//         prettyExp(e->val.binary.lhs);
//         printf(" && ");
//         prettyExp(e->val.binary.rhs);
//         printf(")");
//         break;
//     case k_expressionKindOrExp:
//         printf("(");
//         prettyExp(e->val.binary.lhs);
//         printf(" || ");
//         prettyExp(e->val.binary.rhs);
//         printf(")");
//         break;
//     case k_expressionKindBangExp:
//         printf("(");
//         printf("!");
//         prettyExp(e->exp);
//         printf(")");
//         break;
//     case k_expressionKindNegExp:
//         printf("(");
//         printf("-");
//         prettyExp(e->exp);
//         printf(")");
//         break;
//     case k_expressionKindIDExp:
//         printf("%s", e->val.id_string);
//         break;
//     case k_expressionKindParen:
//         prettyExp(e->exp);
//         break;
//     }
// }

// void prettyStmts(STATEMENT *r, int indentation) {
//     if (r == NULL) {
//         return;
//     }

//     switch (r->kind) {
//     case k_stmt_read:
//         indent(indentation);
//         printf("read(%s);\n", r->val.read.identifier->val.id_string);
//         break;
//     case k_stmt_print:
//         indent(indentation);
//         printf("print(");
//         prettyExp(r->val.print.exp);
//         printf(");\n");
//         break;
//     case k_stmt_assign:
//         indent(indentation);
//         printf("%s = ", r->val.assignment.identifier->val.id_string);
//         prettyExp(r->val.assignment.exp);
//         printf(";\n");
//         break;
//     case k_stmt_loop:
//         indent(indentation);
//         printf("while (");
//         prettyExp(r->val.loop.condition);
//         printf(")\n");
//         indent(indentation);
//         printf("{\n");
//         prettyStmts(r->val.loop.body, indentation + 1);
//         indent(indentation);
//         printf("}\n");
//         break;
//     case k_stmt_if:
//         indent(indentation);
//         printf("if (");
//         prettyExp(r->val.if_stmt.condition);
//         printf(")\n");
//         indent(indentation);
//         printf("{\n");
//         prettyStmts(r->val.if_stmt.stmts, indentation + 1);
//         indent(indentation);
//         printf("}\n");
//         prettyStmts(r->val.if_stmt.elseifstmts, indentation);
//         prettyStmts(r->val.if_stmt.elsestmt, indentation);
//         break;
//     case k_stmt_elseif_list:
//         prettyStmts(r->val.elseif_list.current, indentation);
//         prettyStmts(r->val.elseif_list.next, indentation);
//         break;
//     case k_stmt_elseif:
//         printf("else if (");
//         prettyExp(r->val.elseif.exp);
//         printf(")\n");
//         indent(indentation);
//         printf("{\n");
//         prettyStmts(r->val.elseif.stmts, indentation + 1);
//         printf("}\n");
//         break;
//     case k_stmt_else:
//         indent(indentation);
//         printf("else\n");
//         indent(indentation);
//         printf("{\n");
//         prettyStmts(r->val.else_stmt.stmts, indentation + 1);
//         indent(indentation);
//         printf("}\n");
//         break;
//     case k_stmt_dcl:
//         indent(indentation);
//         if (r->val.dcl.exp == NULL) {
//             printf("var %s : %s;\n", r->val.dcl.identifier->val.id_string, r->val.dcl.type->string_val);
//         } else {
//             printf("var %s : %s = ", r->val.dcl.identifier->val.id_string, r->val.dcl.type->string_val);
//             prettyExp(r->val.dcl.exp);
//             printf(";\n");
//         }
//         break;
//     case k_stmt_list:
//         prettyStmts(r->current, indentation);
//         prettyStmts(r->next, indentation);
//         break;
//     }
// }