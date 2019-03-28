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

int getUID(){
    return uid++;
}

void printID(char *id){
    printf("___%s", id);
}

void printindentation() {
    for (int i = 0; i < code_indentation; i++) {
        printf("    ");
    }
}

void codeImports(IMPORT *i) {
    if (i != NULL) {
        // printf("#import %s\n", i->id);
        codeImports(i->next);
    }
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
        // codeTypeSpec(t->typeSpec, 1);
        // code_indentation --;
    }
}

void codeVarDcl(VARDECL *v, int infunc) {
    if (v != NULL) {
        codeVarSpec(v->var_specs, infunc);
    }
}

void codeTypeSpec(TYPESPEC *ts, int needParen) {
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
    // codeType\(.*;
    codeTypeSpec(ts->next,0);
    if (ts->next == NULL) {
        printf("\n");
        code_indentation --;
        printIndentation();
        printf(")\n");
        code_indentation ++;
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
    } else if(t->kind == k_slices) {
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
    }else if(t->kind == k_array){
        // printf("here\n");
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
    }else {
        return getDefalutValues(t->underLineType);
    }
    return NULL;
}

void codeVarTypes(TYPE *t){
     if(t==NULL || t->id == NULL){
        return;
    }

    char *defVal = getDefalutValues(t);
    if(t->kind == k_array){
        char *defVal = getDefalutValues(t);
        printf("%s", defVal);
    }else if( t->kind == k_slices){
        char *defVal = getDefalutValues(t);
        printf("%s", defVal);
    }else {
        printf("%s", defVal);
    }
}

void codeVarSpec(VARSPEC *vs, int infunc) {
    if (vs == NULL) {
        return;
    }
    codeIDList(vs->id_list);
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

void codeIDList(ID_LIST *i) {
    if (i != NULL) {
        printf("%s", i->id);
        if (i->next != NULL) {
            printf(", "); 
        }
        codeIDList(i->next);
    }
}


void codeParams(PARAMS *p) {
    if (p != NULL) {
        codeIDList(p->id_list);
        printf(" ");
        // codeType\(.*;
        if(p->next !=NULL){
            printf(",");
            codeParams(p->next);
        }
        
    }
}

// void codeResult(RESULT *r) {
//     if (r != NULL) {
//         codeParams(r->params);
//         // codeType\(.*;
//     }
// }

void codeSig(SIGNATURE *s) {
    if (s != NULL) {
        codeParams(s->params);
        printf("):\n");
        // codeResult(s->result);
    }
}

void codeFuncDecl(FUNCDECL *f) {
    if (f != NULL) {
        printf("def %s", f->id);
        printf("(");
        codeSig(f->signature);
        codeSTMT(f->body, true, true);
    }
}

void codeTopDecl(TOPDECL *t) {
    if (t != NULL) {
        switch (t->kind) {
        case dclK:
            codeDecl(t->val.dcl, 0);
            break;
        case funcDeclK:
            // codeFuncDecl(t->val.funcDecl);
            break;
        }
        codeTopDecl(t->next);
    }
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
        (exp->val.cast.type);
        printf("(");
        codeEXP(exp->val.cast.exp);
        printf(")");
        break;

    case appendExpr:
        printf("append(");
        codeEXP(exp->val.append.head);
        printf(",");
        codeEXP(exp->val.append.tail);
        printf(")");
        break;
    case lenExpr:
        printf("len(");
        codeEXP(exp->val.expr);
        printf(")");
        break;
    case capExpr:
        printf("cap(");
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
        printf("%s", exp->val.id);
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
    case stringItpExpr:
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

void codeCASE_CLAUSE(CASE_CLAUSE *c) {
    if (c != NULL) {
        printIndentation();
        switch (c->kind) {
        case caseK:
            printf("case ");
            codeEXP(c->caseExp);
            printf(" :\n");
            code_indentation++;
            codeSTMT(c->caseStmt, true, true);
            code_indentation--;
            break;
        case defaultK:
            printf("default:\n");
            code_indentation++;
            codeSTMT(c->caseStmt, true, true);
            code_indentation--;
            break;
        }
        codeCASE_CLAUSE(c->next);
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

// void codeFOR_CLAUSE(FOR_CLAUSE *f) {
//     if (f != NULL) {
//         codeSTMT(f->first, false, false);
//         printf(";");
//         codeEXP(f->condtion);
//         printf(";");
//         codeSTMT(f->post, false, false);
//     } 
// }

void codeSTMT(STMT *stmt, bool to_indent, bool new_line) {
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
            code_indentation++;
            codeSTMT(stmt->val.block, true, true);
            code_indentation--;
            break;
        case ifStmt:
            printf("def ___():\n");
            code_indentation++;
            if (stmt->val.ifStmtVal.ifSimpleStmt != NULL) {
                codeSTMT(stmt->val.ifStmtVal.ifSimpleStmt, true, false);  
            }
            printindentation();
            printf("if ");
            codeEXP(stmt->val.ifStmtVal.ifCond);
            printf(":\n");
            bool newLine = false;
            if(stmt->val.ifStmtVal.elseStmt == NULL){
                newLine = true;
            }
            codeSTMT(stmt->val.ifStmtVal.ifBody, false, newLine);
            code_indentation--;
            codeSTMT(stmt->val.ifStmtVal.elseStmt, false, newLine);
            printf("___()\n");
            break;
        case elseStmt:
            printf("else:\n");
            codeSTMT(stmt->val.elseStmtVal.elseBody, false, newLine);
            code_indentation++;
            codeSTMT(stmt->val.elseStmtVal.ifStmt, true, newLine);
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
            printf("switch ");
            if (stmt->val.switchStmtVal.switchSimpleStmt != NULL) {
                codeSTMT(stmt->val.switchStmtVal.switchSimpleStmt, false, false);
                printf(";");
            }
            codeEXP(stmt->val.switchStmtVal.switchExp);
            printf("{");
            printf("\n");
            codeCASE_CLAUSE(stmt->val.switchStmtVal.switchCases);
            printf("}");
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
            printf("++");
            break;
        case decStmt:
            codeEXP(stmt->val.decExp);
            printf("--");
            break;
        case shortVarDecStmt:
            codeIDList(stmt->val.shortVarDecStmtVal.ids);
            printf(" := ");
            codeEXP(stmt->val.shortVarDecStmtVal.exps);
            break;
        case forStmt:
            printf("def ___():\n");
            code_indentation++;
            if (stmt->val.forStmtVal.forClause == NULL){
                if (stmt->val.forStmtVal.forCond == NULL){
                    printf("while True:\n");
                } else {
                    printf("while ");
                    codeEXP(stmt->val.forStmtVal.forCond);
                    printf(":\n");
                }
            } else {
                codeSTMT(stmt->val.forStmtVal.forClause->first, true, true);
                // TODO 
            }
            code_indentation++; // Need decrease soon todo
            
            // codeFOR_CLAUSE(stmt->val.forStmtVal.forClause);
            printf(" ");
            codeSTMT(stmt->val.forStmtVal.forBody, false, true);
            code_indentation--;
            printf("___()\n");
            break;
        case dclStmt:
            codeDecl(stmt->val.decStmtVal, 1);
            break;
        }
        if (new_line && stmt->kind != emptyStmt) {
            printf("\n");
        }
        if (stmt->next){
            codeSTMT(stmt->next, to_indent, new_line);    
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
        // codeImports(root->imports);
        codeTopDecl(root->top_decl);
    }

    // // put stdout back
    // fflush(stdout);
    // close(out);
    // dup2(save_out, fileno(stdout));
    // close(save_out);
}
