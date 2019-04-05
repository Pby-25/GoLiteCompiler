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

void codeHelperPass(){
    printf("def do_nothing():\n");
    printf("    pass\n");
}

void codeHelperStrutToStr(){
    printf("def struct_to_str(s):\n");
    printf("    if not s:\n");
    printf("        return '{}'\n");
    printf("    res='{'\n");
    printf("    for e in s.values():\n");
    printf("        res += str(e) + ' '\n");
    printf("    return res[:-1] + '}'\n");
}

void codeHelperArrayToStr(){
    printf("def array_to_str(l):\n");
    printf("    if not l:\n");
    printf("        return '[]'\n");
    printf("    res='['\n");
    printf("    for e in l:\n");
    printf("        res += str(e) + ' '\n");
    printf("    return res[:-1] + ']'\n");
}

void codeHelperFloatFormatCheck(){
    printf("def format_check(*args):\n");
    printf("    res=[]\n");
    printf("    for arg in args:\n");
    printf("        if isinstance(arg, float):\n");
    printf("            floating_str = '{}{:.6e}'.format('+' if arg>=0 else '', arg)\n");
    printf("            floating_str = floating_str if floating_str[-3].isdigit() else floating_str[:-2] + '0' + floating_str[-2:]\n");
    printf("            res.append(floating_str)\n");
    printf("        else:\n");
    printf("            res.append(arg)\n");
    printf("    return res\n");
}

void codeHelperCast(){
    printf("def casting(typa, exp):\n");
    printf("    if isinstance(typa, str):\n");
    printf("        return chr(exp)\n");
    printf("    if isinstance(typa, int):\n");
    printf("        return int(exp)\n");
    printf("    if isinstance(typa, float):\n");
    printf("        return float(exp)\n");
    printf("    if isinstance(typa, bool):\n");
    printf("        return bool(exp)\n");
    printf("    return exp\n");   
}

void codeHelperAppend(){
    printf("def appending(slicer, newcomer):\n");
    printf("    if slicer.count(None) > 0:\n");
    printf("        if slicer.count(None) != 1:\n");
    printf("            i = slicer.index(None)\n");
    printf("            return [element if index != i for index, element in enumerate(slicer)]\n");
    printf("        else:\n");
    printf("            slicer[-1] = newcomer\n");
    printf("            return slicer\n");
    printf("    else:\n");
    printf("        return slicer + [newcomer] + [None]*abs(len(newcomer)-1)\n");
    printf("    return exp\n");   
}

void codeHelperBasicTypes(){
    printf("___int = 0\n");
    printf("___float64 = 0.0\n");
    printf("___rune = 0\n");
    printf("___string = ''\n");
    printf("___bool = False\n");
}

void indent() {
    for (int i = 0; i < code_indentation; i++) {
        printf("    ");
    }
}

void codeImports(IMPORT *i) {
    // printf("import copy\n");
    printf("from copy import deepcopy\n");
    printf("from collections import OrderedDict\n");
    // if (i != NULL) {
    //     // printf("#import %s\n", i->id);
    //     codeImports(i->next);
    // }
    codeHelperPass();
    codeHelperStrutToStr();
    codeHelperArrayToStr();
    codeHelperFloatFormatCheck();
    codeHelperCast();
    codeHelperBasicTypes();
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

void codeDefaultValues(TYPE *t){
    switch (t->kind)
    {
        case k_slices:
            printf("[]");
            break;
        case k_array:
            printf("[");
            codeDefaultValues(t->underLineType);
            printf(" for _ in range(%d)]", t->array_type.size);
            break;
        case k_type_struct:
            printf("OrderedDict([");
            FIELD_DCL *f = t->struct_type.field_dcls;
            while(f){
                ID_LIST *i = f->id_list;
                while(i){
                    printf("(\"%s\", ", i->id);
                    codeDefaultValues(f->type);
                    printf(")");
                    if(i->next){
                        printf(", ");
                    }
                    i = i->next;
                }
                if(f->next){
                    printf(", ");
                }
                f = f->next;
            }
            printf("])");
            break;
    
        default:
            printf("deepcopy(___%s)", t->id);
            break;
    }
}

void codeTypeSpec(TYPESPEC *ts, int needParen) {
    if (ts == NULL) {
        return;
    }

    indent();
    printf("___%s = ", ts->id);
    codeDefaultValues(ts->type);
    printf("\n");

    // char *defVal = getDefalutValues(ts->type);
    // printf("%s = ", ts->id);
    // printf("%s\n", defVal);

    codeTypeSpec(ts->next,0);
}

void codeVarTypes(TYPE *t){
     if(t==NULL || t->id == NULL){
        return;
    }

    char *defVal = getDefalutValues(t);
    printf("%s", defVal);
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
    codeIDList(vs->id_list, false);
    printf(" ");
    EXP *c = vs->exp_list;
    if (c != NULL) {
        printf("= ");
        codeEXP(c, false, true);
    } else {
        printf("= ");
        ID_LIST * i = vs->id_list;
        while(i){
            codeDefaultValues(vs->type);
            if(i->next){
                printf(", ");
            }
            i = i->next;
        }

        // printf("= ");
        // ID_LIST * t = vs->id_list;
        // while(t){
        //     codeVarTypes(vs->type);
        //     if(t->next){
        //         printf(", ");
        //     }
        //     t = t->next;
        // }
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
            indent();
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

// void codeAppend(EXP *head, EXP *tail){
//     codeEXP(head, false, false);
//     printf (" + [");
//     codeEXP(tail, false, false);
//     printf ("]");
//     if (isSlices(head->type)){
//         printf("\n");
//         indent();
//         printf("_ = len(");
//         codeEXP(head, false, false);
//         printf(")\n");
//         indent();
//         printf("if (_-1)&(_-2) == 0:\n"); // check if _-1 is power of 2
//         code_indentation++;
//         indent();
//         codeEXP(head, false, false);
//         printf (" + [None]*abs(_-2)");
//         code_indentation--;
//     } 
// }

// void codeCastBaseType(TYPE *type, EXP *exp ) {
    // if (type == NULL || exp == NULL) return;
    // switch (type->id) {
    //     case "int": 
    //     case "float64":
    //     case "bool":
        
    // }
// }

void codeEXP(EXP *exp, bool to_print, bool to_copy) {
    if (exp == NULL)
        return;
    if (to_copy && !isSlices(exp->type)){
        printf("deepcopy(");
    }
    switch (exp->kind) {
    case orExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, false);
        printf(" or ");
        codeEXP(exp->val.binary.rhs, false, false);
        printf(")");
        break;
    case andExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, false);
        printf(" and ");
        codeEXP(exp->val.binary.rhs, false, false);
        printf(")");
        break;
    case equalsExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, false);
        printf(" == ");
        codeEXP(exp->val.binary.rhs, false, false);
        printf(")");
        break;
    case notequalsExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, false);
        printf(" != ");
        codeEXP(exp->val.binary.rhs, false, false);
        printf(")");
        break;
    case lessExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, false);
        printf(" < ");
        codeEXP(exp->val.binary.rhs, false, false);
        printf(")");
        break;
    case greaterExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, false);
        printf(" > ");
        codeEXP(exp->val.binary.rhs, false, false);
        printf(")");
        break;
    case lessEqualsExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, false);
        printf(" <= ");
        codeEXP(exp->val.binary.rhs, false, false);
        printf(")");
        break;
    case greaterEqualsExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, false);
        printf(" >= ");
        codeEXP(exp->val.binary.rhs, false, false);
        printf(")");
        break;
    case plusExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, false);
        printf(" + ");
        codeEXP(exp->val.binary.rhs, false, false);
        printf(")");
        break;
    case minusExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, false);
        printf(" - ");
        codeEXP(exp->val.binary.rhs, false, false);
        printf(")");
        break;
    case bitwiseOrExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, false);
        printf(" | ");
        codeEXP(exp->val.binary.rhs, false, false);
        printf(")");
        break;
    case bitwiseXorExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, false);
        printf(" ^ ");
        codeEXP(exp->val.binary.rhs, false, false);
        printf(")");
        break;
    case bitwiseAndExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, false);
        printf(" & ");
        codeEXP(exp->val.binary.rhs, false, false);
        printf(")");
        break;
    case bitClearExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, false);
        printf(" &~ ");
        codeEXP(exp->val.binary.rhs, false, false);
        printf(")");
        break;
    case timesExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, false);
        printf(" * ");
        codeEXP(exp->val.binary.rhs, false, false);
        printf(")");
        break;
    case divExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, false);
        printf(" / ");
        codeEXP(exp->val.binary.rhs, false, false);
        printf(")");
        break;
    case modExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, false);
        printf(" %% ");
        codeEXP(exp->val.binary.rhs, false, false);
        printf(")");
        break;
    case leftShiftExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, false);
        printf(" << ");
        codeEXP(exp->val.binary.rhs, false, false);
        printf(")");
        break;
    case rightShiftExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, false);
        printf(" >> ");
        codeEXP(exp->val.binary.rhs, false, false);
        printf(")");
        break;
    case uMinusExpr:
        printf(" -");
        codeEXP(exp->val.unary.exp, false, false);
        break;
    case uPlusExpr:
        printf(" +");
        codeEXP(exp->val.unary.exp, false, false);
        break;
    case uBangExpr:
        printf(" !");
        codeEXP(exp->val.unary.exp, false, false);
        break;
    case uCaretExpr:
        printf(" ^");
        codeEXP(exp->val.unary.exp, false, false);
        break;
    case uBitwiseAndExpr:
        printf(" &");
        codeEXP(exp->val.unary.exp, false, false);
        break;

    case funcExpr:
        codeEXP(exp->val.func.name, false, false);
        printf("(");
        codeEXP(exp->val.func.args, false, false);
        printf(")");
        break;

    case castExpr:
        // codeCastBaseType(exp->val.cast.type, exp->val.cast.exp);
        // (exp->val.cast.type);
        printf("casting(___%s, ", exp->type->id);
        codeEXP(exp->val.cast.exp, false, false);
        printf(")");
        break;

    case appendExpr:
        printf("appending(");
        codeEXP(exp->val.append.head, false, false);
        printf(", ");
        codeEXP(exp->val.append.tail, false, false);
        printf(")");
        // codeAppend(exp->val.append.head, exp->val.append.tail);
        break;
    case lenExpr:
        if (isSlices(exp->type)) {
            printf("sum(x is not None for x in ");
            codeEXP(exp->val.expr, false, false);
            printf(")");
        } else {
            printf("len(");
            codeEXP(exp->val.expr, false, false);
            printf(")");
        }
        break;
    case capExpr:
        printf("len(");
        codeEXP(exp->val.expr, false, false);
        printf(")");
        break;
    case arrayExpr:
        codeEXP(exp->val.array.exp, false, false);
        printf("[");
        codeEXP(exp->val.array.index, false, false);
        printf("]");
        break;
    case sliceExpr:
        codeEXP(exp->val.array.exp, false, false);
        printf("[");
        codeEXP(exp->val.array.index, false, false);
        printf(" if ");
        codeEXP(exp->val.array.exp, false, false);
        printf("[");
        codeEXP(exp->val.array.index, false, false);
        printf("] is not None else len(");
        codeEXP(exp->val.array.exp, false, false);
        printf(")]");
        break;
    case selectorExpr:
        codeEXP(exp->val.selector.exp, false, false);
        printf(".%s", exp->val.selector.name);
        break;
    case idExpr:
        if (to_print && exp->type != NULL){
            switch (exp->type->kind)
            {
                case k_slices:
                case k_array:
                    printf("array_to_str(___%s)", exp->val.id);
                    break;
                case k_type_struct:
                    printf("struct_to_str(___%s)", exp->val.id);
                    break;                
                default:
                    printf("___%s", exp->val.id);
                    break;
            }
        } else {
            printf("___%s", exp->val.id);
        }
        break;
    case intExpr:
        printf("%d", exp->val.intVal);
        break;
    case floatExpr:
        printf("%f", exp->val.floatVal);
        break;
    case runeExpr:
        printf("%d", exp->val.runeVal);
        break;
    case stringItpExpr: 
    case stringRawExpr:
        printf("\"%s\"", exp->val.stringVal);
        break;
    case boolExpr:
        exp->val.boolVal ? printf("True") : printf("False");
        break;
    default:
        break;
    }
    if (to_copy && !isSlices(exp->type)){
        printf(")");
    }
    if (exp->next != NULL) {
            printf(", ");
            codeEXP(exp->next, to_print, to_copy);
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
            codeEXP(c->caseExp, false, false);
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
        codeEXP(stmt->val.assignStmtVal.lhs, false, false);
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
        codeEXP(stmt->val.assignStmtVal.rhs, false, true);
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
            printf("do_nothing()\n");
            indent();
            printf("def ___():\n");
            code_indentation++;
            codeSTMT(stmt->val.block, true, true, NULL);
            code_indentation--;
            indent();
            printf("___()\n");
            break;
        case ifStmt:
            printf("def ___():\n");
            code_indentation++;
            if (stmt->val.ifStmtVal.ifSimpleStmt != NULL) {
                codeSTMT(stmt->val.ifStmtVal.ifSimpleStmt, true, true, NULL);  
            }
            indent();
            printf("if ");
            codeEXP(stmt->val.ifStmtVal.ifCond, false, false);
            printf(":\n");
            bool newLine = false;
            if(stmt->val.ifStmtVal.elseStmt == NULL){
                newLine = true;
            }
            codeSTMT(stmt->val.ifStmtVal.ifBody->val.block, false, newLine, NULL);
            codeSTMT(stmt->val.ifStmtVal.elseStmt, true, newLine, NULL);
            code_indentation--;
            indent();
            printf("___()");
            break;
        case elseStmt:
            printf("else:\n");
            codeSTMT(stmt->val.elseStmtVal.elseBody->val.block, false, true, NULL);
            code_indentation++;
            codeSTMT(stmt->val.elseStmtVal.ifStmt, true, true, NULL);
            code_indentation--;
            break;
        case printStmt:
            printf("print(*format_check(");
            codeEXP(stmt->val.printExpList, true, false);
            printf("), sep='', end='')");
            break;
        case printlnStmt:
            printf("print(*format_check(");
            codeEXP(stmt->val.printlnExpList, true, false);
            printf("), sep=' ', end='\\n')");
            break;
        case returnStmt:
            printf("return ");
            codeEXP(stmt->val.returnExp, false, false);
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
                codeEXP(stmt->val.switchStmtVal.switchExp, false, false);
            }
            printf("\n");
            codeCASE_CLAUSE(stmt->val.switchStmtVal.switchCases, temporaryVar, true);
            code_indentation--;
            indent();
            printf("___()");
            freeUID(temporaryVar);
            break;
        case emptyStmt:
            break;
        case expStmt:
            printf("(");
            codeEXP(stmt->val.expStmtVal, false, false);
            printf(")");
            break;
        case assignStmt:
            codeAssignStmt(stmt);
            break;
        case incStmt:
            codeEXP(stmt->val.incExp, false, false);
            printf("+=1");
            break;
        case decStmt:
            codeEXP(stmt->val.decExp, false, false);
            printf("-=1");
            break;
        case shortVarDecStmt:
            codeIDList(stmt->val.shortVarDecStmtVal.ids, false);
            printf(" = ");
            codeEXP(stmt->val.shortVarDecStmtVal.exps, false, true);
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
                    codeEXP(stmt->val.forStmtVal.forCond, false, false);
                    printf(":\n");
                }
                code_indentation++;
                codeSTMT(stmt->val.forStmtVal.forBody->val.block, true, true, NULL);
                code_indentation--;
            } else {
                codeSTMT(stmt->val.forStmtVal.forClause->first, true, true, NULL);
                indent();
                printf("while ");
                if (stmt->val.forStmtVal.forClause->condtion == NULL){
                    printf("True");
                } else {
                    codeEXP(stmt->val.forStmtVal.forClause->condtion, false, false);
                }
                printf(":\n");
                code_indentation++;
                codeSTMT(stmt->val.forStmtVal.forBody->val.block, true, true, stmt->val.forStmtVal.forClause->post);
                codeSTMT(stmt->val.forStmtVal.forClause->post, true, true, NULL);
                code_indentation--;
            }
            code_indentation--;
            indent();
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
            indent();
            printf("def ___main():\n");
            code_indentation++;
            codeSTMT(main_body, true, true, NULL);
            code_indentation--;
            indent();
            printf("___main()\n");
        }
        
    }

    // // put stdout back
    // fflush(stdout);
    // close(out);
    // dup2(save_out, fileno(stdout));
    // close(save_out);
}
