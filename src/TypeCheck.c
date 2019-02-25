#include "TypeCheck.h"
#include "SymbolTable.h"
#include "stdio.h"
#include "tree.h"
#include <stdlib.h>
#include <string.h>

// void errorType(char *e, char *a, int lineno) {
//     fprintf(stderr, "Error: (line %d): Expected type %s, but got %s\n", lineno,
//             e, a);
//     exit(1);
// }

// void typeExp(EXP *e) {
//     if (e == NULL) {
//         return;
//     }
//     switch (e->kind) {
//     case k_expressionKindIntLiteral:
//         e->type = stingToTYPE("int");
//         break;
//     case k_expressionKindStringLiteral:
//         e->type = stingToTYPE("string");
//         break;
//     case k_expressionKindFloatLiteral:
//         e->type = stingToTYPE("float");
//         break;
//     case k_expressionKindBooleanLiteral:
//         e->type = stingToTYPE("boolean");
//         break;
//     case k_expressionKindPlusExp:
//         typeExp(e->val.binary.lhs);
//         typeExp(e->val.binary.rhs);
//         if (e->val.binary.lhs->type->t_type ==
//                 e->val.binary.rhs->type->t_type &&
//             e->val.binary.lhs->type->t_type != t_boolean) {
//             e->type = e->val.binary.lhs->type;
//         } else {
//             if (e->val.binary.lhs->type->t_type == t_int &&
//                 e->val.binary.rhs->type->t_type == t_float64) {
//                 e->type = e->val.binary.rhs->type;
//             } else if (e->val.binary.lhs->type->t_type == t_float64 &&
//                        e->val.binary.rhs->type->t_type == t_int) {
//                 e->type = e->val.binary.lhs->type;
//             } else {
//                 errorType(e->val.binary.lhs->type->string_val,
//                           e->val.binary.rhs->type->string_val, e->lineno);
//             }
//         }
//         break;
//     case k_expressionKindMinusExp:
//         typeExp(e->val.binary.lhs);
//         typeExp(e->val.binary.rhs);
//         if (e->val.binary.lhs->type->t_type ==
//                 e->val.binary.rhs->type->t_type &&
//             e->val.binary.lhs->type->t_type != t_string &&
//             e->val.binary.lhs->type->t_type != t_boolean) {
//             e->type = e->val.binary.lhs->type;
//         } else {
//             if (e->val.binary.lhs->type->t_type == t_int &&
//                 e->val.binary.rhs->type->t_type == t_float64) {
//                 e->type = e->val.binary.rhs->type;
//             } else if (e->val.binary.lhs->type->t_type == t_float64 &&
//                        e->val.binary.rhs->type->t_type == t_int) {
//                 e->type = e->val.binary.lhs->type;
//             } else {
//                 errorType(e->val.binary.lhs->type->string_val,
//                           e->val.binary.rhs->type->string_val, e->lineno);
//             }
//         }
//         break;
//     case k_expressionKindTimesExp:
//         typeExp(e->val.binary.lhs);
//         typeExp(e->val.binary.rhs);
//         if (e->val.binary.lhs->type->t_type ==
//                 e->val.binary.rhs->type->t_type &&
//             e->val.binary.lhs->type->t_type != t_string &&
//             e->val.binary.lhs->type->t_type != t_boolean) {
//             e->type = e->val.binary.lhs->type;
//         } else {
//             if (e->val.binary.lhs->type->t_type == t_int &&
//                 e->val.binary.rhs->type->t_type == t_float64) {
//                 e->type = e->val.binary.rhs->type;
//             } else if (e->val.binary.lhs->type->t_type == t_float64 &&
//                        e->val.binary.rhs->type->t_type == t_int) {
//                 e->type = e->val.binary.lhs->type;
//             } else {
//                 errorType(e->val.binary.lhs->type->string_val,
//                           e->val.binary.rhs->type->string_val, e->lineno);
//             }
//         }
//         break;
//     case k_expressionKindDivExp:
//         typeExp(e->val.binary.lhs);
//         typeExp(e->val.binary.rhs);
//         if (e->val.binary.lhs->type->t_type ==
//                 e->val.binary.rhs->type->t_type &&
//             e->val.binary.lhs->type->t_type != t_string &&
//             e->val.binary.lhs->type->t_type != t_boolean) {
//             e->type = e->val.binary.lhs->type;
//         } else {
//             if (e->val.binary.lhs->type->t_type == t_int &&
//                 e->val.binary.rhs->type->t_type == t_float64) {
//                 e->type = e->val.binary.rhs->type;
//             } else if (e->val.binary.lhs->type->t_type == t_float64 &&
//                        e->val.binary.rhs->type->t_type == t_int) {
//                 e->type = e->val.binary.lhs->type;
//             } else {
//                 errorType(e->val.binary.lhs->type->string_val,
//                           e->val.binary.rhs->type->string_val, e->lineno);
//             }
//         }
//         break;
//     case k_expressionKindEqExp:
//         typeExp(e->val.binary.lhs);
//         typeExp(e->val.binary.rhs);
//         if (e->val.binary.lhs->type->t_type ==
//             e->val.binary.rhs->type->t_type) {
//             e->type = stingToTYPE("boolean");
//         } else {
//             errorType(e->val.binary.lhs->type->string_val,
//                       e->val.binary.rhs->type->string_val, e->lineno);
//         }
//         break;
//     case k_expressionKindNeqExp:
//         typeExp(e->val.binary.lhs);
//         typeExp(e->val.binary.rhs);
//         if (e->val.binary.lhs->type->t_type ==
//             e->val.binary.rhs->type->t_type) {
//             e->type = stingToTYPE("boolean");
//         } else {
//             errorType(e->val.binary.lhs->type->string_val,
//                       e->val.binary.rhs->type->string_val, e->lineno);
//         }
//         break;
//     case k_expressionKindGeqExp:
//         typeExp(e->val.binary.lhs);
//         typeExp(e->val.binary.rhs);
//         if (e->val.binary.lhs->type->t_type ==
//             e->val.binary.rhs->type->t_type) {
//             e->type = stingToTYPE("boolean");
//         } else {
//             errorType(e->val.binary.lhs->type->string_val,
//                       e->val.binary.rhs->type->string_val, e->lineno);
//         }
//         break;
//     case k_expressionKindLeqExp:
//         typeExp(e->val.binary.lhs);
//         typeExp(e->val.binary.rhs);
//         if (e->val.binary.lhs->type->t_type ==
//             e->val.binary.rhs->type->t_type) {
//             e->type = stingToTYPE("boolean");
//         } else {
//             errorType(e->val.binary.lhs->type->string_val,
//                       e->val.binary.rhs->type->string_val, e->lineno);
//         }
//         break;
//     case k_expressionKindGreaterExp:
//         typeExp(e->val.binary.lhs);
//         typeExp(e->val.binary.rhs);
//         if (e->val.binary.lhs->type->t_type ==
//             e->val.binary.rhs->type->t_type) {
//             e->type = stingToTYPE("boolean");
//         } else {
//             errorType(e->val.binary.lhs->type->string_val,
//                       e->val.binary.rhs->type->string_val, e->lineno);
//         }
//         break;
//     case k_expressionKindLessExp:
//         typeExp(e->val.binary.lhs);
//         typeExp(e->val.binary.rhs);
//         if (e->val.binary.lhs->type->t_type ==
//             e->val.binary.rhs->type->t_type) {
//             e->type = stingToTYPE("boolean");
//         } else {
//             errorType(e->val.binary.lhs->type->string_val,
//                       e->val.binary.rhs->type->string_val, e->lineno);
//         }
//         break;
//     case k_expressionKindAndExp:
//         typeExp(e->val.binary.lhs);
//         typeExp(e->val.binary.rhs);
//         if (e->val.binary.lhs->type->t_type ==
//                 e->val.binary.rhs->type->t_type &&
//             e->val.binary.lhs->type->t_type == t_boolean) {
//             e->type = stingToTYPE("boolean");
//         } else {
//             errorType(e->val.binary.lhs->type->string_val,
//                       e->val.binary.rhs->type->string_val, e->lineno);
//         }
//         break;
//     case k_expressionKindOrExp:
//         typeExp(e->val.binary.lhs);
//         typeExp(e->val.binary.rhs);
//         if (e->val.binary.lhs->type->t_type ==
//                 e->val.binary.rhs->type->t_type &&
//             e->val.binary.lhs->type->t_type == t_boolean) {
//             e->type = stingToTYPE("boolean");
//         } else {
//             errorType(e->val.binary.lhs->type->string_val,
//                       e->val.binary.rhs->type->string_val, e->lineno);
//         }
//         break;
//     case k_expressionKindBangExp:
//         typeExp(e->exp);
//         if (e->exp->type->t_type == t_boolean) {
//             e->type = stingToTYPE("boolean");
//         } else {
//             errorType("boolean", e->exp->type->string_val, e->lineno);
//         }
//         break;
//     case k_expressionKindNegExp:
//         typeExp(e->exp);
//         if (e->exp->type->t_type == t_int || e->exp->type->t_type == t_float64) {
//             e->type = e->exp->type;
//         } else {
//             errorType("int or float", e->exp->type->string_val, e->lineno);
//         }
//         break;
//     case k_expressionKindIDExp:
//         if (e->type == NULL) {
//             fprintf(stderr, "identifier type null\n");
//             exit(1);
//         }
//         break;
//     case k_expressionKindParen:
//         typeExp(e->exp);
//         e->type = e->exp->type;
//         break;
//     }
// }
// int checkSameType(TYPE *t1, TYPE *t2) {
//     if (t1 == NULL || t2 == NULL) {
//         return 0;
//     }
//     switch (t1->t_type) {
//     case t_int:
//         if (t2->t_type == t_int)
//             return 1;
//         if (t2->t_type == t_float64)
//             return 0;
//         if (t2->t_type == t_string)
//             return 0;
//         if (t2->t_type == t_boolean)
//             return 0;
//         break;
//     case t_float64:
//         if (t2->t_type == t_int)
//             return 1;
//         if (t2->t_type == t_float64)
//             return 1;
//         if (t2->t_type == t_string)
//             return 0;
//         if (t2->t_type == t_boolean)
//             return 0;
//         break;
//     case t_string:
//         if (t2->t_type == t_int)
//             return 0;
//         if (t2->t_type == t_float64)
//             return 0;
//         if (t2->t_type == t_string)
//             return 1;
//         if (t2->t_type == t_boolean)
//             return 0;
//         break;
//     case t_boolean:
//         if (t2->t_type == t_int)
//             return 0;
//         if (t2->t_type == t_float64)
//             return 0;
//         if (t2->t_type == t_string)
//             return 0;
//         if (t2->t_type == t_boolean)
//             return 1;
//         break;
//     }
//     return 0;
// }

// void typeStatement(STATEMENT *s) {
//     if (s == NULL) {
//         return;
//     }
//     switch (s->kind) {
//     case k_stmt_read:
//         typeExp(s->val.read.identifier);
//         break;
//     case k_stmt_print:
//         typeExp(s->val.print.exp);
//         break;
//     case k_stmt_assign:
//         typeExp(s->val.assignment.exp);
//         int r = checkSameType(s->val.assignment.identifier->type,
//                               s->val.assignment.exp->type);
//         if (!r) {
//             errorType(s->val.assignment.identifier->type->string_val,
//                       s->val.assignment.exp->type->string_val, s->lineno);
//         }
//         break;
//     case k_stmt_if:
//         typeExp(s->val.if_stmt.condition);
//         if (s->val.if_stmt.condition->type->t_type != t_boolean) {
//             errorType("boolean", s->val.if_stmt.condition->type->string_val,
//                       s->lineno);
//         }
//         typeStatement(s->val.if_stmt.stmts);
//         typeStatement(s->val.if_stmt.elseifstmts);
//         typeStatement(s->val.if_stmt.elsestmt);
//         break;
//     case k_stmt_dcl:
//         if (s->val.dcl.exp != NULL) {
//             typeExp(s->val.dcl.exp);
//             if (!checkSameType(s->val.dcl.type, s->val.dcl.exp->type)) {
//                 errorType(s->val.dcl.type->string_val,
//                           s->val.dcl.exp->type->string_val, s->lineno);
//             }
//         } else {
//             if (!checkSameType(s->val.dcl.identifier->type, s->val.dcl.type)) {
//                 errorType(s->val.dcl.type->string_val,
//                           s->val.dcl.identifier->type->string_val, s->lineno);
//             }
//         }
//         break;
//     case k_stmt_list:
//         typeStatement(s->current);
//         typeStatement(s->next);
//         break;
//     case k_stmt_elseif_list:
//         typeStatement(s->val.elseif_list.current);
//         typeStatement(s->val.elseif_list.next);
//         break;
//     case k_stmt_elseif:
//         typeExp(s->val.elseif.exp);
//         if (s->val.elseif.exp->type->t_type != t_boolean) {
//             errorType("boolean", s->val.elseif.exp->type->string_val,
//                       s->lineno);
//         }
//         typeStatement(s->val.elseif.stmts);
//         break;
//     case k_stmt_else:
//         typeStatement(s->val.else_stmt.stmts);
//         break;
//     case k_stmt_loop:
//         typeExp(s->val.loop.condition);
//         if (s->val.loop.condition->type->t_type != t_boolean) {
//             errorType("boolean", s->val.loop.condition->type->string_val,
//                       s->lineno);
//         }
//         typeStatement(s->val.loop.body);
//         break;
//     }
// }

// void typeCheckProgram(PROGRAM *prog) {
//     makeSymbolTable(prog, 0);
//     typeStatement(prog->statements);
// }