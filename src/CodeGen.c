#include "CodeGen.h"
#include "SymbolTable.h"
#include "TypeCheck.h"
#include "stdio.h"
#include "string.h"
#include "tree.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int code_indentation = 0;
int uid = 0;
STMT *main_body = NULL; // todo execute main at end of file

int getUID(){
    return uid++;
}

void freeUID(int u){
    if (uid == u + 1){
        uid--;
    } // Else too bad
}


void indent() {
    for (int i = 0; i < code_indentation; i++) {
        printf("    ");
    }
}

void codeImports(IMPORT *i) {
    printf("import copy\n");
    printf("append = lambda l, x: (l.append(x) or l)\n");
    // if (i != NULL) {
    //     // printf("#import %s\n", i->id);
    //     codeImports(i->next);
    // }
}

void codeDecl(DCL *d, int infunc) {
    if (d != NULL) {
        switch (d->kind) {
        case typeDcl:
            codeTypeDcl(d->val.typeDecl);
            break;
        case varDcl:
            codeVarDcl(d->val.varDecl,infunc);
            break;
        }
    }
}
void codeTypeDcl(TYPEDECL *t) {
    if (t != NULL) {
        // printf("type ");
        // code_indentation ++;
        codeTypeSpec(t->typeSpec, 1);
        // code_indentation --;
    }
}

void codeVarDcl(VARDECL *v, int infunc) {
    if (v != NULL) {
        codeVarSpec(v->var_specs, infunc);
    }
}

char *getDefalutValues(TYPE *t){
    if(t==NULL || t->id == NULL){
        return NULL;
    }
    char *id = t->id;
    char *defVal;
    if (strcmp(id, "float64") == 0) {
        return "0.0";
    } else if (strcmp(id, "bool") == 0) {
       return"False";
    } else if (strcmp(id, "rune") == 0) {
        return"\"\"";
    } else if (strcmp(id, "string") == 0) {
       return"\"\"";
    } else if (strcmp(id, "int") == 0) {
        return "0";
    } else { 
        // define new thpe
        if(t->kind == k_slices) {
            char *s = (char*)malloc(100 * sizeof(char));
            char *defVal;
            if(t->underLineType && isTypeBaseType(t->underLineType, false)){
                defVal = "";
                sprintf(s, "list(%s)", defVal);
                return s;
            }else{
                defVal = getDefalutValues(t->underLineType);
            }
            sprintf(s, "list(%s)", defVal);
            return s;
        } else if(t->kind == k_array){
            char *s = (char*)malloc(100 * sizeof(char));
            char *defVal = getDefalutValues(t->underLineType);
            sprintf(s, "[%s for _ in range(%d)]", defVal, t->array_type.size);
            return s;
        } else if(t->kind == k_type_struct){
            char defVal[1000];
            memset(defVal ,'\0', 1000);
            FIELD_DCL *f = t->struct_type.field_dcls;
            while(f){
                ID_LIST *t = f->id_list;
                while(t){
                    char *st = (char*)malloc(100 * sizeof(char));
                    char *dd = getDefalutValues(f->type);
                    sprintf(st, "\"%s\": %s", t->id, dd);
                    strcat(defVal, st);
                    if(t->next){
                        strcat(defVal, ", ");
                    }
                    t = t->next;
                }
                if(f->next){
                    strcat(defVal, ", ");
                }
                f = f->next;
            }
            char *s = (char*)malloc(1000 * sizeof(char));
            memset(s ,'\0', 1000);
            sprintf(s, "{%s}", defVal);
            return s;
        } else {
            // type already defined
            char *s = (char*)malloc(1000 * sizeof(char));
            memset(s ,'\0', 1000);
            sprintf(s, "copy.deepcopy(%s)", id);
            return s;
        }
    }
    // } else {
    //     return getDefalutValues(t->underLineType);
    // }
    return NULL;
}

void codeTypeSpec(TYPESPEC *ts, int needParen) {
    if (ts == NULL) {
        return;
    }

    char *defVal = getDefalutValues(ts->type);
    printf("%s = ", ts->id);
    printf("%s\n", defVal);
    codeTypeSpec(ts->next,0);
}

void codeVarTypes(TYPE *t){
     if(t==NULL || t->id == NULL){
        return;
    }

    char *defVal = getDefalutValues(t);
    printf("%s", defVal);
    // if(t->kind == k_array){
    //     char *defVal = getDefalutValues(t);
    //     printf("%s", defVal);
    // }else if( t->kind == k_slices){
    //     char *defVal = getDefalutValues(t);
    //     printf("%s", defVal);
    // }else {
    //     printf("%s", defVal);
    // }
}

void codeVarSpec(VARSPEC *vs, int infunc) {
    if (vs == NULL) {
        return;
    }
    codeIDList(vs->id_list, false);
    printf(" ");
    EXP *c = vs->exp_list;
    if (c != NULL) {
        printf("= ");
        codeEXP(c);
    } else {
        printf("= ");
        ID_LIST * t = vs->id_list;
        while(t){
            codeVarTypes(vs->type);
            if(t->next){
                printf(", ");
            }
            t = t->next;
        }
    }
    printf("\n");
    codeVarSpec(vs->next, infunc);
}

void codeIDList(ID_LIST *i, bool func_params) {
    if (i != NULL) {
        if (func_params && strcmp(i->id, "_") == 0){
            printf("___%d", getUID());
        } else {
            printf("___%s", i->id);
        }
        if (i->next != NULL) {
            printf(", "); 
        }
        codeIDList(i->next, func_params);
    }
}


void codeParams(PARAMS *p) {
    if (p != NULL) {
        codeIDList(p->id_list, true);
        if(p->next !=NULL){
            printf(", ");
            codeParams(p->next);
        }
        
    }
}


void codeSig(SIGNATURE *s) {
    if (s != NULL) {
        codeParams(s->params);
        printf("):\n");
    }
}

void codeFuncDecl(FUNCDECL *f) {
    if (f != NULL) {
        if (strcmp(f->id, "main") == 0){
            main_body = f->body;
            return;
        }
        printf("def ___%s(", f->id);
        codeSig(f->signature);
        code_indentation++;
        codeSTMT(f->body, true, true, NULL);
        code_indentation--;
        if (strcmp(f->id, "init") == 0){
            printf("___init()\n");
        }
    }
}

void codeTopDecl(TOPDECL *t) {
    if (t != NULL) {
        switch (t->kind) {
        case dclK:
            codeDecl(t->val.dcl, 0);
            break;
        case funcDeclK:
            codeFuncDecl(t->val.funcDecl);
            break;
        }
        codeTopDecl(t->next);
    }
}

void codeAppend(EXP *head, EXP *tail){
    codeEXP(head);
    printf (" + [");
    codeEXP(tail);
    printf ("]");
    if (isSlices(head->type)){
        printf("\n");
        indent();
        printf("if len(");
        codeEXP(head);
        printf(") %% 2 == 1:");
    } 
}

void codeCastBaseType(TYPE *type, EXP *exp ) {
    // if (type == NULL || exp == NULL) return;
    // switch (type->id) {
    //     case "int": 
    //     case "float64":
    //     case "bool":
        
    // }
}

void codeEXP(EXP *exp) {
    if (exp == NULL)
        return;
    switch (exp->kind) {
    case orExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs);
        printf(" or ");
        codeEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case andExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs);
        printf(" and ");
        codeEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case equalsExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs);
        printf(" == ");
        codeEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case notequalsExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs);
        printf(" != ");
        codeEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case lessExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs);
        printf(" < ");
        codeEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case greaterExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs);
        printf(" > ");
        codeEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case lessEqualsExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs);
        printf(" <= ");
        codeEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case greaterEqualsExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs);
        printf(" >= ");
        codeEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case plusExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs);
        printf(" + ");
        codeEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case minusExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs);
        printf(" - ");
        codeEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case bitwiseOrExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs);
        printf(" | ");
        codeEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case bitwiseXorExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs);
        printf(" ^ ");
        codeEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case bitwiseAndExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs);
        printf(" & ");
        codeEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case bitClearExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs);
        printf(" &~ ");
        codeEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case timesExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs);
        printf(" * ");
        codeEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case divExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs);
        printf(" / ");
        codeEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case modExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs);
        printf(" %% ");
        codeEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case leftShiftExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs);
        printf(" << ");
        codeEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case rightShiftExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs);
        printf(" >> ");
        codeEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case uMinusExpr:
        printf(" -");
        codeEXP(exp->val.unary.exp);
        break;
    case uPlusExpr:
        printf(" +");
        codeEXP(exp->val.unary.exp);
        break;
    case uBangExpr:
        printf(" !");
        codeEXP(exp->val.unary.exp);
        break;
    case uCaretExpr:
        printf(" ^");
        codeEXP(exp->val.unary.exp);
        break;
    case uBitwiseAndExpr:
        printf(" &");
        codeEXP(exp->val.unary.exp);
        break;

    case funcExpr:
        codeEXP(exp->val.func.name);
        printf("(");
        codeEXP(exp->val.func.args);
        printf(")");
        break;

    case castExpr:
        codeCastBaseType(exp->val.cast.type, exp->val.cast.exp);
        (exp->val.cast.type);
        printf("(");
        codeEXP(exp->val.cast.exp);
        printf(")");
        break;

    case appendExpr:
        codeAppend(exp->val.append.head, exp->val.append.tail);
        break;
    case lenExpr:
        ;
        ExpKind kind = exp->val.expr->kind;
        if (kind == stringItpExpr || kind == stringRawExpr || kind == arrayExpr) {
            printf("len(");
            codeEXP(exp->val.expr);
            printf(")");
        } else if (kind == sliceExpr) {
            printf("sum(x is not None for x in ");
            codeEXP(exp->val.expr);
            printf(")");
        }
        break;
    case capExpr:
        printf("len(");
        codeEXP(exp->val.expr);
        printf(")");
        break;
    case arrayExpr:
        codeEXP(exp->val.array.exp);
        printf("[");
        codeEXP(exp->val.array.index);
        printf("]");
        break;
    case selectorExpr:
        codeEXP(exp->val.selector.exp);
        printf(".%s", exp->val.selector.name);
        break;
    case idExpr:
        printf("___%s", exp->val.id);
        break;
    case intExpr:
        printf("%d", exp->val.intVal);
        break;
    case floatExpr:
        printf("%f", exp->val.floatVal);
        break;
    case runeExpr:
        printf("%s", exp->val.runeVal);
        break;
    case stringItpExpr: // might need escape
        printf("%s", exp->val.stringVal);
        break;
    case stringRawExpr:
        printf("\"%s\"", exp->val.stringVal);
        break;
    case boolExpr:
        exp->val.boolVal ? printf("True") : printf("False");
        break;
    default:
        break;
    }

    if (exp->next != NULL) {
            printf(", ");
            codeEXP(exp->next);
    }
}

void codeCASE_CLAUSE(CASE_CLAUSE *c, int cond_var, bool first_case) {
    if (c != NULL) {
        indent();
        switch (c->kind) {
        case caseK:
            if (first_case){
                printf("if ___%d == (", cond_var);
            } else {
                printf("elif ___%d == (", cond_var);
            }
            codeEXP(c->caseExp);
            printf("):\n");
            break;
        case defaultK:
            if (first_case){
                printf("if True:\n");
            } else {
                printf("else:\n");
            }
            break;
        }
        code_indentation++;
        indent();
        printf("def ___():\n");
        code_indentation++;
        codeSTMT(c->caseStmt, true, true, NULL);
        code_indentation--;
        indent();
        printf("___()\n");
        code_indentation--;
        codeCASE_CLAUSE(c->next, cond_var, false);
    }
}

void codeAssignStmt(STMT *stmt) {
    if (stmt != NULL) {
        codeEXP(stmt->val.assignStmtVal.lhs);
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
            printf(" &= ~");
            break;
        }
        codeEXP(stmt->val.assignStmtVal.rhs);
    }
}


void codeSTMT(STMT *stmt, bool to_indent, bool new_line, STMT *post_stmt) {
    if (to_indent && stmt!=NULL && stmt->kind != emptyStmt) {
        indent();
    }
    if (stmt != NULL) {
        switch (stmt->kind) {
        case continueStmt:
            if (post_stmt != NULL){
                codeSTMT(post_stmt, true, true, NULL);
            }
            printf("continue");
            break;
        case breakStmt:
            printf("break");
            break;
        case blockStmt:
            code_indentation++;
            codeSTMT(stmt->val.block, true, true, NULL);
            code_indentation--;
            break;
        case ifStmt:
            printf("def ___():\n");
            code_indentation++;
            if (stmt->val.ifStmtVal.ifSimpleStmt != NULL) {
                codeSTMT(stmt->val.ifStmtVal.ifSimpleStmt, true, true, NULL);  
            }
            indent();
            printf("if ");
            codeEXP(stmt->val.ifStmtVal.ifCond);
            printf(":\n");
            bool newLine = false;
            if(stmt->val.ifStmtVal.elseStmt == NULL){
                newLine = true;
            }
            codeSTMT(stmt->val.ifStmtVal.ifBody, false, newLine, NULL);
            codeSTMT(stmt->val.ifStmtVal.elseStmt, true, newLine, NULL);
            code_indentation--;
            indent();
            printf("___()\n");
            break;
        case elseStmt:
            printf("else:\n");
            codeSTMT(stmt->val.elseStmtVal.elseBody, false, true, NULL);
            code_indentation++;
            codeSTMT(stmt->val.elseStmtVal.ifStmt, true, true, NULL);
            code_indentation--;
            break;
        case printStmt:
            printf("print(");
            codeEXP(stmt->val.printExpList);
            printf(")");
            break;
        case printlnStmt:
            printf("println(");
            codeEXP(stmt->val.printlnExpList);
            printf(")");
            break;
        case returnStmt:
            printf("return ");
            codeEXP(stmt->val.returnExp);
            break;
        case switchStmt:
            printf("def ___():\n");
            code_indentation++;
            if (stmt->val.switchStmtVal.switchSimpleStmt != NULL) {
                codeSTMT(stmt->val.switchStmtVal.switchSimpleStmt, true, true, NULL);
            }
            int temporaryVar = getUID();
            indent();
            printf("___%d = ", temporaryVar);
            if (stmt->val.switchStmtVal.switchExp == NULL){
                printf("True");
            } else {
                codeEXP(stmt->val.switchStmtVal.switchExp);
            }
            printf("\n");
            codeCASE_CLAUSE(stmt->val.switchStmtVal.switchCases, temporaryVar, true);
            freeUID(temporaryVar);
            break;
        case emptyStmt:
            break;
        case expStmt:
            printf("(");
            codeEXP(stmt->val.expStmtVal);
            printf(")");
            break;
        case assignStmt:
            codeAssignStmt(stmt);
            break;
        case incStmt:
            codeEXP(stmt->val.incExp);
            printf("+=1");
            break;
        case decStmt:
            codeEXP(stmt->val.decExp);
            printf("-=1");
            break;
        case shortVarDecStmt:
            codeIDList(stmt->val.shortVarDecStmtVal.ids, false);
            printf(" = ");
            codeEXP(stmt->val.shortVarDecStmtVal.exps);
            break;
        case forStmt:
            printf("def ___():\n");
            code_indentation++;
            if (stmt->val.forStmtVal.forClause == NULL){
                indent();
                if (stmt->val.forStmtVal.forCond == NULL){
                    printf("while True:\n");
                } else {
                    printf("while ");
                    codeEXP(stmt->val.forStmtVal.forCond);
                    printf(":\n");
                }
                code_indentation++;
                codeSTMT(stmt->val.forStmtVal.forBody, true, true, NULL);
                code_indentation--;
            } else {
                codeSTMT(stmt->val.forStmtVal.forClause->first, true, true, NULL);
                indent();
                printf("while ");
                if (stmt->val.forStmtVal.forClause->condtion == NULL){
                    printf("True");
                } else {
                    codeEXP(stmt->val.forStmtVal.forClause->condtion);
                }
                printf(":\n");
                code_indentation++;
                codeSTMT(stmt->val.forStmtVal.forBody, true, true, stmt->val.forStmtVal.forClause->post);
                codeSTMT(stmt->val.forStmtVal.forClause->post, true, true, NULL);
                code_indentation--;
            }
            code_indentation--;
            printf("___()");
            break;
        case dclStmt:
            codeDecl(stmt->val.decStmtVal, 1);
            break;
        }
        if (new_line && stmt->kind != emptyStmt) {
            printf("\n");
        }
        if (stmt->next){
            codeSTMT(stmt->next, to_indent, new_line, NULL);    
        }
    }
}

void str_replace(char *target, const char *needle, const char *replacement) {
    char buffer[1024] = {0};
    char *insert_point = &buffer[0];
    const char *tmp = target;
    size_t needle_len = strlen(needle);
    size_t repl_len = strlen(replacement);

    while (1) {
        const char *p = strstr(tmp, needle);

        // walked past last occurrence of needle; copy remaining part
        if (p == NULL) {
            strcpy(insert_point, tmp);
            break;
        }

        // copy part before needle
        memcpy(insert_point, tmp, p - tmp);
        insert_point += p - tmp;

        // copy replacement string
        memcpy(insert_point, replacement, repl_len);
        insert_point += repl_len;

        // adjust pointers, move on
        tmp = p + needle_len;
    }

    // write altered string back to target
    strcpy(target, buffer);
}

void codePROGRAM(PROGRAM *root, char *file_name) {

    typeCheckProgram(root);

    // // append .c to file name
    // str_replace(file_name, ".go", ".py");
    // remove(file_name);

    // // // redirect stdout to new file
    // int out = open(file_name, O_RDWR | O_APPEND | O_CREAT, 0600);
    // if (-1 == out) {
    //     perror("Error: open file");
    //     return;
    // }
    // int save_out = dup(fileno(stdout));
    // if (-1 == dup2(out, fileno(stdout))) {
    //     perror("Error: cannot redirect stdout");
    //     return;
    // }

   
    if (root != NULL) {
        codeImports(root->imports);
        codeTopDecl(root->top_decl);
        if (main_body != NULL){
            printf("def ___main():\n");
            code_indentation++;
            codeSTMT(main_body, true, true, NULL);
            code_indentation--;
            printf("___main()\n");
        }
        
    }

    // // put stdout back
    // fflush(stdout);
    // close(out);
    // dup2(save_out, fileno(stdout));
    // close(save_out);
}
