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

SYMBOL *putSymbol(SymbolTable *t, char *id, TYPE *type, symbolKind sk) {
    int i = Hash(id);
    for (SYMBOL *s = t->table[i]; s; s = s->next) {
        if (strcmp(s->name, id) == 0) {
            return NULL;
        }
    }
    SYMBOL *s = malloc(sizeof(SYMBOL));
    s->name = id;
    s->type = type;
    s->kind = sk;
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

void errorReDeclared(int lineno, char *message, char *id) {
    fprintf(stderr, "Error: (line %d) %s \"%s\" already declared \n",
            lineno, message, id);
    exit(1);
}

void errorNotDeclared(int lineno, char *message, char *id) {
    fprintf(stderr, "Error: (line %d) %s \"%s\" not declared\n", lineno,
            message, id);
    exit(1);
}
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

// void indent(int symbol_indentation) {
//     for (int i = 0; i < symbol_indentation; i++) {
//         printf("\t");
//     }
// }

// void makeSymbolStatement(STATEMENT *s, SymbolTable *st, int symbol_indentation,
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
//             indent(symbol_indentation);
//             printf("{\n");
//         }

//         l_symbolTable = scopeSymbolTable(st);
//         makeSymbolExp(s->val.if_stmt.condition, st);
//         makeSymbolStatement(s->val.if_stmt.stmts, l_symbolTable,
//                             symbol_indentation + 1, print);
//         if (print) {
//             indent(symbol_indentation);
//             printf("}\n");
//         }
//         if (s->val.if_stmt.elseifstmts != NULL) {
//             l_symbolTable = scopeSymbolTable(st);
//             makeSymbolStatement(s->val.if_stmt.elseifstmts, l_symbolTable,
//                                 symbol_indentation, print);
//         }
//         if (s->val.if_stmt.elsestmt != NULL) {
//             l_symbolTable = scopeSymbolTable(st);
//             makeSymbolStatement(s->val.if_stmt.elsestmt, l_symbolTable,
//                                 symbol_indentation, print);
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
//             indent(symbol_indentation);
//             printf("%s: %s \n", s->val.dcl.identifier->val.id_string,
//                    s->val.dcl.type->string_val);
//         }
//         break;
//     case k_stmt_list:
//         makeSymbolStatement(s->current, st, symbol_indentation, print);
//         makeSymbolStatement(s->next, st, symbol_indentation, print);
//         break;
//     case k_stmt_elseif_list:
//         makeSymbolStatement(s->val.elseif_list.current, st, symbol_indentation, print);
//         makeSymbolStatement(s->val.elseif_list.next, st, symbol_indentation, print);
//         break;
//     case k_stmt_elseif:
//         if (print) {
//             indent(symbol_indentation);
//             printf("{\n");
//         }
//         l_symbolTable = scopeSymbolTable(st);
//         makeSymbolExp(s->val.elseif.exp, st);
//         makeSymbolStatement(s->val.elseif.stmts, l_symbolTable, symbol_indentation + 1,
//                             print);
//         if (print) {
//             indent(symbol_indentation);
//             printf("}\n");
//         }
//         break;
//     case k_stmt_else:
//         if (print) {
//             indent(symbol_indentation);
//             printf("{\n");
//         }
//         l_symbolTable = scopeSymbolTable(st);
//         makeSymbolStatement(s->val.else_stmt.stmts, l_symbolTable,
//                             symbol_indentation + 1, print);
//         if (print) {
//             indent(symbol_indentation);
//             printf("}\n");
//         }
//         break;
//     case k_stmt_loop:
//         if (print) {
//             indent(symbol_indentation);
//             printf("{\n");
//         }
//         l_symbolTable = scopeSymbolTable(st);
//         makeSymbolExp(s->val.loop.condition, st);
//         makeSymbolStatement(s->val.loop.body, l_symbolTable, symbol_indentation + 1,
//                             print);
//         if (print) {
//             indent(symbol_indentation);
//             printf("}\n");
//         }
//         break;
//     }
// }

int symbol_indentation = 0;

// void printIndentation() {
//     for (int i = 0; i < symbol_indentation; i++) {
//         printf("    ");
//     }
// }

void symbolImports(IMPORT *i) {
    if (i != NULL) {
        printf("import %s\n", i->id);
        symbolImports(i->next);
    }
}

void symbolDecl(SymbolTable *s, DCL *d, int infunc) {
    if (d != NULL) {
        switch (d->kind) {
        case typeDcl:
            symbolTypeDcl(s, d->val.typeDecl, s);
            break;
        case varDcl:
            symbolVarDcl(s, d->val.varDecl, infunc);
            break;
        }
    }
}
void symbolTypeDcl(SymbolTable *s, TYPEDECL *t, SymbolTable *st) {
    if (t != NULL) {
        symbol_indentation ++;
        symbolTypeSpec(t->typeSpec, 1, st);
        symbol_indentation --;
    }
}

void symbolVarDcl(SymbolTable *s, VARDECL *v, int infunc) {
    if (v != NULL) {
        symbolVarSpec(s, v->var_specs, infunc);
    }
}

bool isIdBaseType(char *id){
    if(id == NULL){
        return false;
    }
    if(strcmp(id, "int")==0||strcmp(id, "float64")==0||strcmp(id, "bool")==0||strcmp(id, "rune")==0||strcmp(id, "string")==0||strcmp(id, "true")==0||strcmp(id, "false")==0){
        return true;
    }
    return false;
}

void resolveType(SymbolTable *st, TYPE *ts){
    if (ts == NULL){
        printf("\n");
        return;
    }

    if (ts->id != NULL && isIdBaseType(ts->id)){
        printf("%s\n", ts->id);
        return;
    }

    printType(ts);
    
    if (ts->id != NULL){
        SYMBOL *sb = getSymbol(st, ts->id);
        if (sb != NULL){
            printf(" -> ");
            resolveType(st, sb->type);
        }else{
            printf("null\n");
        }
    }
}

void symbolTypeSpec(TYPESPEC *ts, int needParen, SymbolTable *st) {
    // printf("ssas\n");
    // if (ts == NULL) {
    //     if(needParen){
    //         printf("( )\n");
    //     }
    //     return;
    // }
    // if (needParen) {
    //     printf("(");
    // }
    // printf("\n");
    // printIndentation();
    if(ts ==NULL){
        return;
    }
    
    putSymbol(st,ts->id,ts->type,sk_typeDcl);
    printf("%s [type] = %s -> ", ts->id, ts->id);
    // printf("%d %s\n",ts->type->kind,ts->type->slices_type.type->id);
    resolveType(st, ts->type);
    symbolTypeSpec(ts->next,0,st);

    // printf("%s\n",s->type->id);
    // if (ts->next == NULL) {
    //     printf("\n");
    //     symbol_indentation --;
    //     printIndentation();
    //     printf(")\n");
    //     symbol_indentation ++;
    // }
}


void printType(TYPE *t) {

    if (t != NULL) {
        // printf("%d", t->kind);
        switch (t->kind) {
        case k_type_id:
            printf("%s", t->id); 
            break;
        case k_slices:
            printf("[]%s\n", t->slices_type.type->id); 
            break;
        case k_array:
            printf("[%d]%s\n", t->array_type.size, t->array_type.type->id);
            // symbolType(t->array_type.type, st, sk);
            break;
        case k_type_struct:

            printf("struct { ");
            // symbol_indentation ++;
            symbolField_Dcl(t->struct_type.field_dcls);
            // symbol_indentation --;
            // printIndentation();
            printf("}\n");
            break;
        case k_type_type:
        
            // printf("(");
            printType(t->types);
            // printf(")");
            break;
        }
    }
}

void symbolVarSpec(SymbolTable *s, VARSPEC *vs, int infunc) {
    // if (vs == NULL) {
    //     return;
    // }
    // VARSPEC *vsPtr = vs;
    // if (vsPtr->next){
    //     symbol_indentation++;
    //     while (vsPtr){
    //         printIndentation();
    //         symbolIDList(s, vsPtr->id_list, vsPtr->type);
    //         EXP *c = vsPtr->exp_list;
    //         // if(c!=NULL){
    //         //     printf("= ");
    //         // }
    //         symbolEXP(c);
    //         // if(vsPtr->next != NULL && infunc){
    //         //     printf("\n");
    //         // }
    //         // if(!infunc){
    //         //     printf("\n");
    //         // }
    //         vsPtr = vsPtr->next;
    //     }
    //     // printf("\n");
    //     symbol_indentation--;
    //     printIndentation();
    //     // printf(")\n");
    // } else {
    //     TYPE *type = vs->type;
    //     symbolIDList(s, vs->id_list, type);
    //     EXP *exp_list = vs->exp_list;
    //     if (exp_list != NULL) {
    //         symbolEXP(exp_list);
    //     }   
    //     // if(vs->next != NULL && infunc){
    //     //     printf("\n");
    //     // }
    //     // if(!infunc){
    //     //     printf("\n");
    //     // }
    // }
}

void printIDList(ID_LIST *idl){
    if(idl!=NULL){
        printf("%s ", idl->id);
        printIDList(idl->next);
    }
}
void symbolField_Dcl(FIELD_DCL *f) {
    if (f == NULL) {
        return;
    }
    // printIndentation();
    printIDList(f->id_list);
    // printf(" ");
    printType(f->type);
    printf("; ");
    symbolField_Dcl(f->next);
}

// void symbolIDList(ID_LIST *i) {
//     if (i != NULL) {
//         printf("%s", i->id);
//         if (i->next != NULL) {
//             printf(", "); 
//         }
//         symbolIDList(i->next);
//     }
// }

void symbolIDList(SymbolTable *s, ID_LIST *i, TYPE *t, bool params){
    if (i != NULL) {
        if (getSymbol(s, i->id) != NULL) {
            fprintf(stderr, "Error: (line %d) identifier %s has been declared\n",
                i->lineno, i->id);
            exit(1);
        }

        if (t == NULL) {
            t = malloc(sizeof(TYPE));
            t->id = "<infer>";
            t->kind = k_infer;
        }

        putSymbol(s, i->id, t, sk_varDcl);

        if (params){
            printf("%s", t->id);
            if (i->next != NULL){
                printf(", ");
            }
        } else {
            printf("%s [variable] = %s\n", i->id, t->id);
        }
        
        symbolIDList(s, i->next, t, false);
    }
}

void symbolParams(SymbolTable *t, PARAMS *p) {
    
    if (p != NULL) {
        symbolIDList(t, p->id_list, p->type, true);
        if(p->next != NULL){
            printf(", ");
            symbolParams(t, p->next);
        }
    }
    
}

void symbolResult(SymbolTable *t, SymbolTable *new_st, RESULT *r, char *id) {
    printf(" -> ");
    if (r != NULL) {
        if(r->params != NULL){
            // named return, only support one type
            putSymbol(t, id, r->params->type, sk_funcDcl);
            printf("(");  
            symbolParams(new_st, r->params);
            printf(")");
        } else {
            printf("%s", r->type->id);
            putSymbol(t, id, r->type, sk_funcDcl);
        }
    } else {
        printf("void");
        putSymbol(t, id, NULL, sk_funcDcl);
    }
    printf("\n");
}

SymbolTable *symbolSig(SymbolTable *t, SIGNATURE *s, char *id) {
    SymbolTable *new_st;
    if (s != NULL) {
        new_st = scopeSymbolTable(t);   
        printf("(");     
        symbolParams(new_st, s->params);
        printf(")");
        symbolResult(t, new_st, s->result, id);
    }
    return new_st;
}

void symbolFuncDecl(SymbolTable *t, FUNCDECL *f) {
    if (f == NULL) {
        return;
    }
    printf("%s [function] = ", f->id);
    if (strcmp(f->id, "main") == 0){
        symbolSpecialFuncDecl(t, f, mainK);
        return;
    }
    if (strcmp(f->id, "init") == 0){
        symbolSpecialFuncDecl(t, f, initK);
        return;
    }
    
    SymbolTable *new_st = symbolSig(t, f->signature, f->id);
    symbolSTMT(new_st, f->body, true, true);
}


void symbolSpecialFuncDecl(SymbolTable *t, FUNCDECL *f, speicialFuncK spK){
    if (t->parent != NULL){
        fprintf(stderr, "Error: (line %d) special function can only be decalared at top level \n", f->lineno);
        exit(1);
    }
    if (f->signature->params != NULL || f->signature->result != NULL){
        fprintf(stderr, "Error: (line %d) special function cannot have any params or result \n", f->lineno);
        exit(1);
    }
    printf("() -> void\n");
    SymbolTable *new_st = scopeSymbolTable(t);
    switch (spK)
    {
        case mainK:
            putSymbol(t, "main", NULL, sk_funcDcl);
            break;
        case initK:
            putSymbol(t, NULL, NULL, sk_funcDcl);
            break;
    }
    symbolSTMT(new_st, f->body, true, true);

}

void symbolTopDecl(SymbolTable *s, TOPDECL *t) {
    if (t != NULL) {
        switch (t->kind) {
        case dclK:
            symbolDecl(s, t->val.dcl, 0);
            break;
        case funcDeclK:
            symbolFuncDecl(s, t->val.funcDecl);
            break;
        }
        symbolTopDecl(s, t->next);
    }
}



void symbolEXP(SymbolTable *s, EXP *exp) {
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
    case bitwiseAndExpr:
    case bitClearExpr:
    case timesExpr:
    case divExpr:
    case modExpr:
    case leftShiftExpr:
    case rightShiftExpr:
        symbolEXP(s, exp->val.binary.lhs);
        symbolEXP(s, exp->val.binary.rhs);
        break;
    case uMinusExpr:
    case uPlusExpr:
    case uBangExpr:
    case uCaretExpr:
    case uBitwiseAndExpr:
        symbolEXP(s, exp->val.unary.exp);
        break;
    case funcExpr:
        symbolEXP(s, exp->val.func.name);
        symbolEXP(s, exp->val.func.args);
        break;
    case castExpr:
        symbolEXP(s, exp->val.cast.type);
        symbolEXP(s, exp->val.cast.exp);
        break;
    case appendExpr:
        symbolEXP(s, exp->val.append.head);
        symbolEXP(s, exp->val.append.tail);
        break;
    case lenExpr:
        symbolEXP(s, exp->val.expr);
        break;
    case capExpr:
        symbolEXP(s, exp->val.expr);
        break;
    case arrayExpr:
        symbolEXP(s, exp->val.array.exp);
        symbolEXP(s, exp->val.array.index);
        break;
    case selectorExpr:
        symbolEXP(s, exp->val.selector.exp);
        break;
    case idExpr:
        if (getSymbol(s, exp->val.id) == NULL) {
            fprintf(stderr, "Error: (line %d) identifier %s is not defined\n", exp->lineno, exp->val.id);
            exit(1);
        }
        break;
    case intExpr:
    case floatExpr:
    case runeExpr:
    case stringItpExpr:
    case stringRawExpr:
    case boolExpr:
        break;
    default:
        break;
    }
    if (exp->next != NULL) {
            symbolEXP(s, exp->next);
    }
}

void symbolCASE_CLAUSE(SymbolTable *s, CASE_CLAUSE *c) {
    if (c != NULL) {
     //   printIndentation();
        switch (c->kind) {
        case caseK:
            symbolEXP(s, c->caseExp);
            symbol_indentation++;
            symbolSTMT(s, c->caseStmt, true, true);
            symbol_indentation--;
            break;
        case defaultK:
            symbol_indentation++;
            symbolSTMT(s, c->caseStmt, true, true);
            symbol_indentation--;
            break;
        }
        symbolCASE_CLAUSE(s, c->next);
    }
}

void symbolFOR_CLAUSE(SymbolTable *s, FOR_CLAUSE *f) {
    if (f != NULL) {
        symbolSTMT(s, f->first, false, false);
        printf(";");
        symbolEXP(s, f->condtion);
        printf(";");
        symbolSTMT(s, f->post, false, false);
    }
}

void symbolSTMT(SymbolTable *s, STMT *stmt, bool to_indent, bool new_line) {
    // if (to_indent && stmt!=NULL && stmt->kind != emptyStmt) {
    //     printIndentation();
    // }
    if (stmt != NULL) {
        switch (stmt->kind) {
        case continueStmt:
            break;
        case breakStmt:
            break;
        case blockStmt:
            printf("{");
            printf("\n");
            symbol_indentation++;
            symbolSTMT(scopeSymbolTable(s), stmt->val.block, true, true);
            symbol_indentation--;
            //printIndentation();
            printf("}");
            break;
        case ifStmt:
            if (stmt->val.ifStmtVal.ifSimpleStmt != NULL) {
                symbolSTMT(s, stmt->val.ifStmtVal.ifSimpleStmt, false, false);
                printf(";");
            }
            symbolEXP(s, stmt->val.ifStmtVal.ifCond);
            bool newLine = false;
            if(stmt->val.ifStmtVal.elseStmt == NULL){
                newLine = true;
            }
            symbolSTMT(scopeSymbolTable(s), stmt->val.ifStmtVal.ifBody, false, newLine);
            symbolSTMT(s, stmt->val.ifStmtVal.elseStmt, false, newLine);
            break;
        case elseStmt:
            printf("else ");
            symbolSTMT(scopeSymbolTable(s), stmt->val.elseStmtVal.elseBody, false, newLine);
            symbolSTMT(s, stmt->val.elseStmtVal.ifStmt, false, newLine);
            break;
        case printStmt:
            symbolEXP(s, stmt->val.printExpList);
            break;
        case printlnStmt:
            symbolEXP(s, stmt->val.printlnExpList);
            break;
        case returnStmt:
            symbolEXP(s, stmt->val.returnExp);
            break;
        case switchStmt:
            printf("switch ");
            if (stmt->val.switchStmtVal.switchSimpleStmt != NULL) {
                symbolSTMT(s, stmt->val.switchStmtVal.switchSimpleStmt, false, false);
            }
            symbolEXP(s, stmt->val.switchStmtVal.switchExp);
            symbolCASE_CLAUSE(s, stmt->val.switchStmtVal.switchCases);
            break;
        case emptyStmt:
            break;
        case expStmt:
            symbolEXP(s, stmt->val.expStmtVal);
            break;
        case assignStmt:
            symbolEXP(s, stmt->val.assignStmtVal.lhs);
            symbolEXP(s, stmt->val.assignStmtVal.rhs);
            break;
        case incStmt:
            symbolEXP(s, stmt->val.incExp);
            break;
        case decStmt:
            symbolEXP(s, stmt->val.decExp);
            break;
        case shortVarDecStmt:
            symbolIDList(s, stmt->val.shortVarDecStmtVal.ids, NULL, false);
            symbolEXP(s, stmt->val.shortVarDecStmtVal.exps);
            break;
        case forStmt:
            symbolEXP(s, stmt->val.forStmtVal.forCond);
            symbolFOR_CLAUSE(s, stmt->val.forStmtVal.forClause);
            symbolSTMT(scopeSymbolTable(s), stmt->val.forStmtVal.forBody, false, true);
            break;
        case dclStmt:
            symbolDecl(s, stmt->val.decStmtVal, 1);
            break;
        }
        if (new_line && stmt->kind != emptyStmt) {
            printf("\n");
        }
        if (stmt->next){
            symbolSTMT(s, stmt->next, to_indent, new_line);    
        }
    }
}

void symbolBooleanConstant(SymbolTable *s, char *boolVal){
    printf("%s [constant] = %s\n", boolVal, boolVal);
}

void symbolBaseType(SymbolTable *s, char *typeName) {
    TYPE *type = malloc(sizeof(TYPE));
    type->id = typeName; 
    printf("%s [type] = %s\n", type->id, type->id);
    putSymbol(s, type->id, type, sk_typeDcl);
}

void symbolAllBaseTypes(SymbolTable *s) {
    symbolBaseType(s, "int");
    symbolBaseType(s, "float64");
    symbolBaseType(s, "bool");
    symbolBaseType(s, "rune");
    symbolBaseType(s, "string");
    symbolBooleanConstant(s, "true");
    symbolBooleanConstant(s, "false");
}

void makeSymbolTable(PROGRAM *root) {
    if (root != NULL) {
        SymbolTable *s = initSymbolTable();
        symbolAllBaseTypes(s);
        symbolTopDecl(s, root->top_decl);
    }
}