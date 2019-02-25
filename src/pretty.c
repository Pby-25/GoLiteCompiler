#include "pretty.h"
#include "SymbolTable.h"
#include "stdio.h"
#include "string.h"
#include "tree.h"
#include <stdlib.h>

// void prettyProg(PROGRAM *root) { prettyStmts(root->statements, 0); }

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