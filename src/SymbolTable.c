#include "SymbolTable.h"
#include "stdio.h"
#include "tree.h"
#include <stdlib.h>
#include <string.h>

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

SYMBOL *putSymbol(SymbolTable *t, EXP *id_exp, TYPE *type) {
    int i = Hash(id_exp->val.id);
    id_exp->type = type;
    for (SYMBOL *s = t->table[i]; s; s = s->next) {
        if (strcmp(s->name, id_exp->val.id) == 0) {
            return NULL;
        }
    }
    SYMBOL *s = malloc(sizeof(SYMBOL));
    s->name = id_exp->val.id;
    s->type = type;
    s->next = t->table[i];
    t->table[i] = s;
    return s;
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

// void errorReDeclared(int lineno, char *id) {
//     fprintf(stderr, "Error: (line %d) identifier \"%s\" already declared \n",
//             lineno, id);
//     exit(1);
// }

// void errorNotDeclared(int lineno, char *id) {
//     fprintf(stderr, "Error: (line %d) identifier \"%s\" not declared\n", lineno,
//             id);
//     exit(1);
// }
// void makeSymbolExp(EXP *e, SymbolTable *st) {
//     if (e == NULL) {
//         return;
//     }
//     SYMBOL *sb;
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
//         makeSymbolExp(e->val.binary.lhs, st);
//         makeSymbolExp(e->val.binary.rhs, st);
//         break;
//     case k_expressionKindMinusExp:
//         makeSymbolExp(e->val.binary.lhs, st);
//         makeSymbolExp(e->val.binary.rhs, st);
//         break;
//     case k_expressionKindTimesExp:
//         makeSymbolExp(e->val.binary.lhs, st);
//         makeSymbolExp(e->val.binary.rhs, st);
//         break;
//     case k_expressionKindDivExp:
//         makeSymbolExp(e->val.binary.lhs, st);
//         makeSymbolExp(e->val.binary.rhs, st);
//         break;
//     case k_expressionKindEqExp:
//         makeSymbolExp(e->val.binary.lhs, st);
//         makeSymbolExp(e->val.binary.rhs, st);
//         break;
//     case k_expressionKindNeqExp:
//         makeSymbolExp(e->val.binary.lhs, st);
//         makeSymbolExp(e->val.binary.rhs, st);
//         break;
//     case k_expressionKindGeqExp:
//         makeSymbolExp(e->val.binary.lhs, st);
//         makeSymbolExp(e->val.binary.rhs, st);
//         break;
//     case k_expressionKindLeqExp:
//         makeSymbolExp(e->val.binary.lhs, st);
//         makeSymbolExp(e->val.binary.rhs, st);
//         break;
//     case k_expressionKindGreaterExp:
//         makeSymbolExp(e->val.binary.lhs, st);
//         makeSymbolExp(e->val.binary.rhs, st);
//         break;
//     case k_expressionKindLessExp:
//         makeSymbolExp(e->val.binary.lhs, st);
//         makeSymbolExp(e->val.binary.rhs, st);
//         break;
//     case k_expressionKindAndExp:
//         makeSymbolExp(e->val.binary.lhs, st);
//         makeSymbolExp(e->val.binary.rhs, st);
//         break;
//     case k_expressionKindOrExp:
//         makeSymbolExp(e->val.binary.lhs, st);
//         makeSymbolExp(e->val.binary.rhs, st);
//         break;
//     case k_expressionKindBangExp:
//         makeSymbolExp(e->exp, st);
//         break;
//     case k_expressionKindNegExp:
//         makeSymbolExp(e->exp, st);
//         break;
//     case k_expressionKindIDExp:
//         sb = getSymbol(st, e->val.id_string);
//         if (sb == NULL) {
//             errorNotDeclared(e->lineno, e->val.id_string);
//         }
//         e->type = sb->type;
//         break;
//     case k_expressionKindParen:
//         makeSymbolExp(e->exp, st);
//         e->type = e->exp->type;
//         break;
//     }
// }

// void indent(int indentation) {
//     for (int i = 0; i < indentation; i++) {
//         printf("\t");
//     }
// }

// void makeSymbolStatement(STATEMENT *s, SymbolTable *st, int indentation,
//                          int print) {
//     if (s == NULL) {
//         return;
//     }
//     SYMBOL *sb;
//     SymbolTable *l_symbolTable;
//     switch (s->kind) {
//     case k_stmt_read:
//         sb = getSymbol(st, s->val.assignment.identifier->val.id_string);
//         if (sb == NULL) {
//             errorNotDeclared(s->lineno, s->val.read.identifier->val.id_string);
//         }
//         s->val.read.identifier->type = sb->type;
//         break;
//     case k_stmt_print:
//         makeSymbolExp(s->val.print.exp, st);
//         break;
//     case k_stmt_assign:
//         sb = getSymbol(st, s->val.assignment.identifier->val.id_string);

//         if (sb == NULL) {
//             errorNotDeclared(s->lineno, s->val.read.identifier->val.id_string);
//         }
//         s->val.assignment.identifier->type = sb->type;
//         makeSymbolExp(s->val.assignment.exp, st);
//         break;
//     case k_stmt_if:
//         if (print) {
//             indent(indentation);
//             printf("{\n");
//         }

//         l_symbolTable = scopeSymbolTable(st);
//         makeSymbolExp(s->val.if_stmt.condition, st);
//         makeSymbolStatement(s->val.if_stmt.stmts, l_symbolTable,
//                             indentation + 1, print);
//         if (print) {
//             indent(indentation);
//             printf("}\n");
//         }
//         if (s->val.if_stmt.elseifstmts != NULL) {
//             l_symbolTable = scopeSymbolTable(st);
//             makeSymbolStatement(s->val.if_stmt.elseifstmts, l_symbolTable,
//                                 indentation, print);
//         }
//         if (s->val.if_stmt.elsestmt != NULL) {
//             l_symbolTable = scopeSymbolTable(st);
//             makeSymbolStatement(s->val.if_stmt.elsestmt, l_symbolTable,
//                                 indentation, print);
//         }
//         break;
//     case k_stmt_dcl:
//         sb = putSymbol(st, s->val.dcl.identifier, s->val.dcl.type);
//         if (sb == NULL) {
//             errorReDeclared(s->lineno, s->val.dcl.identifier->val.id_string);
//         }

//         s->val.dcl.identifier->type = sb->type;
//         makeSymbolExp(s->val.dcl.exp, st);
//         if (print) {
//             indent(indentation);
//             printf("%s: %s \n", s->val.dcl.identifier->val.id_string,
//                    s->val.dcl.type->string_val);
//         }
//         break;
//     case k_stmt_list:
//         makeSymbolStatement(s->current, st, indentation, print);
//         makeSymbolStatement(s->next, st, indentation, print);
//         break;
//     case k_stmt_elseif_list:
//         makeSymbolStatement(s->val.elseif_list.current, st, indentation, print);
//         makeSymbolStatement(s->val.elseif_list.next, st, indentation, print);
//         break;
//     case k_stmt_elseif:
//         if (print) {
//             indent(indentation);
//             printf("{\n");
//         }
//         l_symbolTable = scopeSymbolTable(st);
//         makeSymbolExp(s->val.elseif.exp, st);
//         makeSymbolStatement(s->val.elseif.stmts, l_symbolTable, indentation + 1,
//                             print);
//         if (print) {
//             indent(indentation);
//             printf("}\n");
//         }
//         break;
//     case k_stmt_else:
//         if (print) {
//             indent(indentation);
//             printf("{\n");
//         }
//         l_symbolTable = scopeSymbolTable(st);
//         makeSymbolStatement(s->val.else_stmt.stmts, l_symbolTable,
//                             indentation + 1, print);
//         if (print) {
//             indent(indentation);
//             printf("}\n");
//         }
//         break;
//     case k_stmt_loop:
//         if (print) {
//             indent(indentation);
//             printf("{\n");
//         }
//         l_symbolTable = scopeSymbolTable(st);
//         makeSymbolExp(s->val.loop.condition, st);
//         makeSymbolStatement(s->val.loop.body, l_symbolTable, indentation + 1,
//                             print);
//         if (print) {
//             indent(indentation);
//             printf("}\n");
//         }
//         break;
//     }
// }

void makeSymbolVarDecl(VARDECL *v) {
    // if (t != NULL) {
        
    // }
}

void makeSymbolTypeDecl(TYPEDECL *t) {
    if(t!=NULL){
        
    }
}

void makeSymbolDecl(DCL *d) {
    if (d != NULL) {
        switch (d->kind) {
            case varDcl:
                makeSymbolVarDecl(d->val.varDecl);
            case typeDcl: 
                makeSymbolTypeDecl(d->val.typeDecl);
                break;
        }  
    }
}

void makeSymbolFuncDecl(FUNCDECL *f) {

}

void makeSymbolTopDecl(TOPDECL * t) {
    if (t != NULL) {
        switch (t->kind) {
            case dclK:
                makeSymbolDecl(t->val.dcl);
                break;
            case funcDeclK:
                makeSymbolFuncDecl(t->val.funcDecl);
                break;
        }
        makeSymbolTopDecl(t->next);
    }
}


void makeSymbolTable(PROGRAM *prog, int print) {
    SymbolTable *root = initSymbolTable();
    // makeSymbolStatement(prog->top_decl, root, 0, print);
}