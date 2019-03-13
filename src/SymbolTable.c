#include "SymbolTable.h"
#include "stdio.h"
#include "tree.h"
#include <stdlib.h>
#include <string.h>
#include "TypeCheck.h"

bool printSymbol = false;
char *functionSignature = NULL;
int symbol_indentation = 0;

void printFunctionSignature(){
    if (functionSignature != NULL){
        if (printSymbol) printf("%s", functionSignature); 
        functionSignature = NULL;   
    }
}

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

SYMBOL *getSymbolCurrentScope(SymbolTable *t, char *name) {
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
    return NULL;
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

bool isIdBaseType(TYPE *t){
    if(t == NULL || t->id == NULL){
        return false;
    }
    char *id = t->id;
    if(strcmp(id, "float64")==0){
        t->id_type.isBaseType = true;
        t->id_type.baseTypeKind = btk_float64;
        return true;
    }else if(strcmp(id, "bool")==0){
        t->id_type.isBaseType = true;
        t->id_type.baseTypeKind = btk_bool;
        return true;
    }else if(strcmp(id, "rune")==0){
        t->id_type.isBaseType = true;
        t->id_type.baseTypeKind = btk_rune;
        return true;
    }else if(strcmp(id, "string")==0){
        t->id_type.isBaseType = true;
        t->id_type.baseTypeKind = btk_string;
        return true;
    }else if(strcmp(id, "int")==0){
        t->id_type.isBaseType = true;
        t->id_type.baseTypeKind = btk_int;
        return true;
    }else{
        t->id_type.isBaseType = false;
        return false;
    }
    return false;
}

void resolveType(SymbolTable *st, TYPE *ts){
    if (ts == NULL){
        if (printSymbol) printf("\n");
        return;
    }

    if (ts->id != NULL && isIdBaseType(ts)){
        if (printSymbol) printf("%s\n", ts->id);
        return;
    }

    printType(ts);
    
    if (ts->id != NULL){
        SYMBOL *sb = getSymbol(st, ts->id);
        if (sb != NULL) {
            if (printSymbol) printf(" -> ");
            if(sb->type != NULL){
                resolveType(st, sb->type);
            }
        } else {
            errorReDeclared(ts->lineno,"type",ts->id);
            if (printSymbol) printf("null\n");
        }
    }
}

void symbolTypeSpec(TYPESPEC *ts, int needParen, SymbolTable *st) {
 
    if(ts ==NULL){
        return;
    }
    
    putSymbol(st,ts->id,ts->type,sk_typeDcl);
    if (printSymbol) printf("%s [type] = %s -> ", ts->id, ts->id);
    resolveType(st, ts->type);
    symbolTypeSpec(ts->next,0,st);

}


void printType(TYPE *t) {

    if (t != NULL) {
        switch (t->kind) {
        case k_type_id:
            if (printSymbol) printf("%s", t->id); 
            break;
        case k_slices:
            if (printSymbol) printf("[]%s\n", t->slices_type.type->id); 
            break;
        case k_array:
            if (printSymbol) printf("[%d]%s\n", t->array_type.size, t->array_type.type->id);
            break;
        case k_type_struct:
            if (printSymbol) printf("struct { ");
            symbolField_Dcl(t->struct_type.field_dcls);
            if (printSymbol) printf("}\n");
            break;
        case k_type_type:
            printType(t->types);
            break;
        }
    }
}

void symbolVarSpec(SymbolTable *s, VARSPEC *vs, int infunc) {
    if (vs == NULL) {
        return;
    }
    VARSPEC *vsPtr = vs;
    if (vsPtr->next){
        symbol_indentation++;
        while (vsPtr){
            //printIndentation();
            symbolIDList(s, vsPtr->id_list, vsPtr->type, false);
            EXP *c = vsPtr->exp_list;
            symbolEXP(s, c);
            vsPtr = vsPtr->next;
        }
        symbol_indentation--;
        //printIndentation();
    } else {
        TYPE *type = vs->type;
        symbolIDList(s, vs->id_list, type, false);
        EXP *exp_list = vs->exp_list;
        if (exp_list != NULL) {
            symbolEXP(s, exp_list);
        }   
    }
}

void printIDList(ID_LIST *idl){
    if(idl!=NULL){
        if (printSymbol) printf("%s ", idl->id);
        printIDList(idl->next);
    }
}
void symbolField_Dcl(FIELD_DCL *f) {
    if (f == NULL) {
        return;
    }
    // printIndentation();
    printIDList(f->id_list);
    // if (printSymbol) printf(" ");
    printType(f->type);
    if (printSymbol) printf("; ");
    symbolField_Dcl(f->next);
}

void symbolIDList(SymbolTable *s, ID_LIST *i, TYPE *t, bool params){
    if (i != NULL) {
        if(strcmp(i->id,"_")==0){
            return;
        }
        if (getSymbolCurrentScope(s, i->id) != NULL) {
            fprintf(stderr, "Error: (line %d) identifier %s has been declared\n",
                i->lineno, i->id);
            exit(1);
        }

        if (t == NULL) {
            t = malloc(sizeof(TYPE));
            t->id = "<infer>";
            t->kind = k_infer;
        }
        
        i->type = t;
        putSymbol(s, i->id, t, sk_varDcl);
        
        if (params){
            if (printSymbol) printf("%s", t->id);
            if (i->next != NULL){
                if (printSymbol) printf(", ");
            }
            // char *tmpStr = malloc(sizeof(i->id)+sizeof(t->id)+20);
            // sprintf(tmpStr, "%s [variable] = %s\n", i->id, t->id);
            // strcat(functionSignature, tmpStr);
        } else {
            if (printSymbol) printf("%s [variable] = %s\n", i->id, t->id);
        }
        
        symbolIDList(s, i->next, t, false);
    }
}

void symbolParams(SymbolTable *t, PARAMS *p) {
    
    if (p != NULL) {
        symbolIDList(t, p->id_list, p->type, true);
        if(p->next != NULL){
            if (printSymbol) printf(", ");
            symbolParams(t, p->next);
        }
    }
    
}

void symbolResult(SymbolTable *t, SymbolTable *new_st, RESULT *r, char *id) {
    if (printSymbol) printf(" -> ");
    if (r != NULL) {
        if(r->params != NULL){
            // named return, only support one type
            putSymbol(t, id, r->params->type, sk_funcDcl);
            if (printSymbol) printf("(");  
            symbolParams(new_st, r->params); // FIXME if there's time, will be in wrong scope
            if (printSymbol) printf(")");
        } else {
            if (printSymbol) printf("%s", r->type->id);
            putSymbol(t, id, r->type, sk_funcDcl);
        }
    } else {
        if (printSymbol) printf("void");
        putSymbol(t, id, NULL, sk_funcDcl);
    }
    if (printSymbol) printf("\n");
}

SymbolTable *symbolSig(SymbolTable *t, SIGNATURE *s, char *id) {
    SymbolTable *new_st;
    if (s != NULL) {
        new_st = scopeSymbolTable(t);   
        if (printSymbol) printf("(");
        // functionSignature = realloc(functionSignature, sizeof(s->params));     
        symbolParams(new_st, s->params);
        if (printSymbol) printf(")");
        symbolResult(t, new_st, s->result, id);
    }
    return new_st;
}

void symbolFuncDecl(SymbolTable *t, FUNCDECL *f) {
    if (f == NULL) {
        return;
    }
    if (printSymbol) printf("%s [function] = ", f->id);
    if (strcmp(f->id, "main") == 0){
        symbolSpecialFuncDecl(t, f, mainK);
        return;
    }
    if (strcmp(f->id, "init") == 0){
        symbolSpecialFuncDecl(t, f, initK);
        return;
    }
    
    SymbolTable *new_st = symbolSig(t, f->signature, f->id);
    symbolSTMT(t, new_st, f->body, true, true);
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
    if (printSymbol) printf("() -> void\n");
    SymbolTable *new_st = scopeSymbolTable(t);
    switch (spK)
    {
        case mainK:
            putSymbol(t, "main", NULL, sk_funcDcl);
            break;
        case initK:
            putSymbol(t, "init", NULL, sk_funcDcl);
            break;
    }
    symbolSTMT(t, new_st, f->body, true, true);
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
    // return;
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
        printf("func");
        SYMBOL *sb = getSymbol(s,exp->val.func.name->val.id);
        if(sb != NULL){
            exp->type = sb->type;
        } else {
            errorNotDeclared(exp->lineno,"func", exp->val.func.name->val.id);
        }
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
    case idExpr:;
        if (strcmp(exp->val.id,"_")!=0){
            SYMBOL *sbb = getSymbol(s, exp->val.id);
            if (sbb == NULL) {
                fprintf(stderr, "Error: (line %d) identifier %s is not defined\n", exp->lineno, exp->val.id);
                exit(1);
            }else{
                // printf("id exp");
                if(exp->type == NULL){
                    exp->type = malloc(sizeof(TYPE));
                    // printf("aaaa%d", sbb->type->id_type.isBaseType);
                    exp->type = sbb->type;
                    // resolveType(s,sbb->type);
                }
                
            }
        }
        break;
    case intExpr:
        exp->type = strToType("int");
        break;
    case floatExpr:
        exp->type = strToType("float64");
        break;
    case runeExpr:
        exp->type = strToType("rune");
        break;
    case stringItpExpr:
        exp->type = strToType("string");
        break;
    case stringRawExpr:
        exp->type = strToType("string");
        break;
    case boolExpr:
        exp->type = strToType("bool");
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
        SymbolTable *new_new = scopeSymbolTable(s);
        switch (c->kind) {
        case caseK:;
            symbolEXP(new_new, c->caseExp);
            symbol_indentation++;
            symbolSTMT(new_new, NULL, c->caseStmt, true, true);
            symbol_indentation--;
            break;
        case defaultK:;
            symbol_indentation++;
            symbolSTMT(new_new, NULL, c->caseStmt, true, true);
            symbol_indentation--;
            break;
        }
        symbolCASE_CLAUSE(s, c->next);
    }
}

void symbolFOR_CLAUSE(SymbolTable *s, FOR_CLAUSE *f) {
    if (f != NULL) {
        symbolSTMT(s, NULL, f->first, false, false);
        //printf(";");
        symbolEXP(s, f->condtion);
        //printf(";");
        symbolSTMT(s, NULL, f->post, false, false);
    }
}

void symbolSTMT(SymbolTable *s, SymbolTable *new_st, STMT *stmt, bool to_indent, bool new_line) {
    // if (to_indent && stmt!=NULL && stmt->kind != emptyStmt) {
    //     printIndentation();
    // }
    // return;

    if (stmt != NULL) {
        switch (stmt->kind) {
        case continueStmt:
            break;
        case breakStmt:
            break;
        case blockStmt:
            if (new_st == NULL){
                new_st = scopeSymbolTable(s);
            }
            if (printSymbol) printf("{");
            if (printSymbol) printf("\n");
            symbol_indentation++;
            // printFunctionSignature();
            symbolSTMT(new_st, NULL, stmt->val.block, true, true);
            symbol_indentation--;
            //printIndentation();
            if (printSymbol) printf("}");
            break;
        case ifStmt:
            if (stmt->val.ifStmtVal.ifSimpleStmt != NULL) {
                symbolSTMT(s, NULL, stmt->val.ifStmtVal.ifSimpleStmt, false, false);
                //printf(";");
            }
            symbolEXP(s, stmt->val.ifStmtVal.ifCond);
            bool newLine = false;
            if(stmt->val.ifStmtVal.elseStmt == NULL){
                newLine = true;
            }
            symbolSTMT(s, NULL, stmt->val.ifStmtVal.ifBody, false, newLine);
            symbolSTMT(s, NULL, stmt->val.ifStmtVal.elseStmt, false, newLine);
            break;
        case elseStmt:
            //printf("else ");
            symbolSTMT(s, NULL, stmt->val.elseStmtVal.elseBody, false, newLine);
            symbolSTMT(s, NULL, stmt->val.elseStmtVal.ifStmt, false, newLine);
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
        case switchStmt:;
            SymbolTable *new = scopeSymbolTable(s);

            if (stmt->val.switchStmtVal.switchSimpleStmt != NULL) {
                symbolSTMT(new, NULL, stmt->val.switchStmtVal.switchSimpleStmt, false, false);
            }
            symbolEXP(new, stmt->val.switchStmtVal.switchExp);
            SymbolTable *new_new = scopeSymbolTable(new);
            symbolCASE_CLAUSE(new_new, stmt->val.switchStmtVal.switchCases);
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
        case forStmt:;
            SymbolTable *fnew = scopeSymbolTable(s);
            symbolEXP(fnew, stmt->val.forStmtVal.forCond);
            symbolFOR_CLAUSE(fnew, stmt->val.forStmtVal.forClause);
            SymbolTable *fnew_new = scopeSymbolTable(fnew);
            symbolSTMT(fnew_new, NULL, stmt->val.forStmtVal.forBody, false, true);
            break;
        case dclStmt:
            symbolDecl(s, stmt->val.decStmtVal, 1);
            break;
        }
        if (new_line && stmt->kind != emptyStmt) {
            // if (printSymbol) printf("");
        }
        if (stmt->next){
            symbolSTMT(s, NULL, stmt->next, to_indent, new_line);    
        }
    }
}

void symbolBooleanConstant(SymbolTable *s, char *boolVal){
    if (printSymbol) printf("%s [constant] = %s\n", boolVal, boolVal);
}

void symbolBaseType(SymbolTable *s, char *typeName) {
    TYPE *type = malloc(sizeof(TYPE));
    type->id = typeName; 
    if (printSymbol) printf("%s [type] = %s\n", type->id, type->id);
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
        if (printSymbol) printf("{\n");
        symbolAllBaseTypes(s);
        symbolTopDecl(s, root->top_decl);
        if (printSymbol) printf("}\n");
    }
}

void symbolMode(){
    printSymbol = true;
}