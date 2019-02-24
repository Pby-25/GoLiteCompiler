#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

EXP *makeEXP_Paren(EXP *exp, int lineno) {
    EXP *e = malloc(sizeof(EXP));
    e->lineno = lineno;
    e->kind = k_expressionKindParen;
    e->exp = exp;
    return e;
}



PROGRAM *makeProgram(PACKAGE p, IMPORT i,  DECL d ){
    return NULL;
}