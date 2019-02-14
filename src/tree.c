#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void checkEXPisID(EXP *identifier) {
    if (identifier->isIdentifier != 1) {
        fprintf(stderr, "Error: declaration identifier must be an identifier "
                        "not an exp \n");
        exit(1);
    }
}

EXP *makeEXP_Paren(EXP *exp, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindParen;
    e->exp = exp;
    return e;
}

EXP *makeEXP_intLiteral(int intLiteral, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindIntLiteral;
    e->val.intLiteral = intLiteral;
    return e;
}

EXP *makeEXP_StringLiteral(char *stringLiteral, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindStringLiteral;
    e->val.stringLiteral = stringLiteral;
    return e;
}

EXP *makeEXP_FloatLiteral(float floatLiteral, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindFloatLiteral;
    e->val.floatLiteral = floatLiteral;
    return e;
}

EXP *makeEXP_BooleanLiteral(int booleanLiteral, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindBooleanLiteral;
    e->val.booleanLiteral = booleanLiteral;
    return e;
}

EXP *makeEXP_plus(EXP *lhs, EXP *rhs, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindPlusExp;
    e->val.binary.lhs = lhs;
    e->val.binary.rhs = rhs;
    return e;
}

EXP *makeEXP_minus(EXP *lhs, EXP *rhs, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindMinusExp;
    e->val.binary.lhs = lhs;
    e->val.binary.rhs = rhs;
    return e;
}
EXP *makeEXP_times(EXP *lhs, EXP *rhs, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindTimesExp;
    e->val.binary.lhs = lhs;
    e->val.binary.rhs = rhs;
    return e;
}
EXP *makeEXP_div(EXP *lhs, EXP *rhs, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindDivExp;
    e->val.binary.lhs = lhs;
    e->val.binary.rhs = rhs;
    return e;
}
EXP *makeEXP_eq(EXP *lhs, EXP *rhs, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindEqExp;
    e->val.binary.lhs = lhs;
    e->val.binary.rhs = rhs;
    return e;
}
EXP *makeEXP_neq(EXP *lhs, EXP *rhs, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindNeqExp;
    e->val.binary.lhs = lhs;
    e->val.binary.rhs = rhs;
    return e;
}
EXP *makeEXP_geq(EXP *lhs, EXP *rhs, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindGeqExp;
    e->val.binary.lhs = lhs;
    e->val.binary.rhs = rhs;
    return e;
}
EXP *makeEXP_leq(EXP *lhs, EXP *rhs, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindLeqExp;
    e->val.binary.lhs = lhs;
    e->val.binary.rhs = rhs;
    return e;
}
EXP *makeEXP_greater(EXP *lhs, EXP *rhs, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindGreaterExp;
    e->val.binary.lhs = lhs;
    e->val.binary.rhs = rhs;
    return e;
}
EXP *makeEXP_less(EXP *lhs, EXP *rhs, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindLessExp;
    e->val.binary.lhs = lhs;
    e->val.binary.rhs = rhs;
    return e;
}
EXP *makeEXP_and(EXP *lhs, EXP *rhs, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindAndExp;
    e->val.binary.lhs = lhs;
    e->val.binary.rhs = rhs;
    return e;
}
EXP *makeEXP_or(EXP *lhs, EXP *rhs, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindOrExp;
    e->val.binary.lhs = lhs;
    e->val.binary.rhs = rhs;
    return e;
}
EXP *makeEXP_Bang(EXP *exp, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindBangExp;
    e->exp = exp;
    return e;
}
EXP *makeEXP_Neg(EXP *exp, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindNegExp;
    e->exp = exp;
    return e;
}
EXP *makeEXP_ID(char *identifier, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindIDExp;
    e->val.id_string = identifier;
    e->isIdentifier = 1;
    return e;
}

//////////////////////////////////////////////////////////////////////////////

STATEMENT *makeStatement_assign(EXP *identifier, EXP *exp, int lineno) {
    checkEXPisID(identifier);
    STATEMENT *s = malloc(sizeof(STATEMENT));
    s->lineno = lineno;
    s->kind = k_stmt_assign;
    s->val.assignment.identifier = identifier;
    s->val.assignment.exp = exp;
    s->current = s;
    return s;
}

STATEMENT *makeStatememnt_list(STATEMENT *s1, STATEMENT *s2, int lineno) {
    STATEMENT *s = malloc(sizeof(STATEMENT));
    s->lineno = lineno;
    s->kind = k_stmt_list;
    // s1->next = s2;
    s->current = s1;
    s->next = s2;
    return s;
}

STATEMENT *makeStatememnt_read(EXP *identifier, int lineno) {
    checkEXPisID(identifier);
    STATEMENT *s = malloc(sizeof(STATEMENT));
    s->lineno = lineno;
    s->kind = k_stmt_read;
    s->val.read.identifier = identifier;
    s->current = s;
    return s;
}
STATEMENT *makeStatememnt_print(EXP *exp, int lineno) {

    STATEMENT *s = malloc(sizeof(STATEMENT));
    s->lineno = lineno;
    s->kind = k_stmt_print;
    s->val.print.exp = exp;
    s->current = s;
    return s;
}
STATEMENT *makeStatememnt_if(EXP *condition, STATEMENT *stmts,
                             STATEMENT *elseifstmts, STATEMENT *elsestmt,
                             int lineno) {
    STATEMENT *s = malloc(sizeof(STATEMENT));
    s->lineno = lineno;
    s->kind = k_stmt_if;
    s->val.if_stmt.condition = condition;
    s->val.if_stmt.stmts = stmts;
    s->val.if_stmt.elseifstmts = elseifstmts;
    s->val.if_stmt.elsestmt = elsestmt;
    s->current = s;
    return s;
}

STATEMENT *makeStatememnt_elseifstmt_list(STATEMENT *s1, STATEMENT *s2,
                                          int lineno) {
    STATEMENT *s = malloc(sizeof(STATEMENT));
    s->lineno = lineno;
    s->kind = k_stmt_elseif_list;
    s->val.elseif_list.current = s1;
    s->val.elseif_list.next = s2;
    s->current = s1;
    return s;
}

STATEMENT *makeStatememnt_elseifstmt(EXP *exp, STATEMENT *stmts, int lineno) {
    STATEMENT *s = malloc(sizeof(STATEMENT));
    s->lineno = lineno;
    s->kind = k_stmt_elseif;
    s->val.elseif.exp = exp;
    s->val.elseif.stmts = stmts;
    s->current = s;
    return s;
}

STATEMENT *makeStatememnt_else(STATEMENT *stmts, int lineno) {
    STATEMENT *s = malloc(sizeof(STATEMENT));
    s->lineno = lineno;
    s->kind = k_stmt_else;
    s->val.else_stmt.stmts = stmts;
    s->current = s;
    return s;
}

STATEMENT *makeStatememnt_while(EXP *exp, STATEMENT *stmts, int lineno) {
    STATEMENT *s = malloc(sizeof(STATEMENT));
    s->lineno = lineno;
    s->kind = k_stmt_loop;
    s->val.loop.condition = exp;
    s->val.loop.body = stmts;
    s->current = s;
    return s;
}

STATEMENT *makeStatememnt_dcl(EXP *identifier, TYPE *type, EXP *exp,
                              int lineno) {
    checkEXPisID(identifier);
    STATEMENT *s = malloc(sizeof(STATEMENT));
    s->lineno = lineno;
    s->kind = k_stmt_dcl;
    s->val.dcl.exp = exp;
    s->val.dcl.identifier = identifier;
    s->val.dcl.type = type;
    identifier->type = type;
    s->current = s;
    return s;
}

PROGRAM *makeProgram(STATEMENT *stmts) {
    PROGRAM *prog = malloc(sizeof(PROGRAM));
    prog->statements = stmts;
    return prog;
}

TYPE *stingToTYPE(char *s) {
    TYPE *t = malloc(sizeof(TYPE));
    t->string_val = s;
    if (strcmp(s, "string") == 0) {
        t->t_type = t_string;
    } else if (strcmp(s, "boolean") == 0) {
        t->t_type = t_boolean;
    } else if (strcmp(s, "float") == 0) {
        t->t_type = t_float;
    } else {
        t->t_type = t_int;
    }
    return t;
}