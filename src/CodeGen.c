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
#include <float.h>


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

void codeHelperBreak(){
    printf("class Broke(Exception):\n");
    printf("    pass\n");
}

void codeHelperSlice(){
    printf("class Slice(list):\n");
    printf("    def __init__(self, iterable=None, previous_cap=0):\n");
    printf("        if iterable is None:\n");
    printf("            super().__init__()\n");
    printf("        else:\n");
    printf("            super().__init__(iterable)\n");
    printf("        if previous_cap == 1:\n");
    printf("            self.capacity = 2\n");
    printf("            self.extend([None] * 2)\n");
    printf("        else:\n");
    printf("            self.capacity = previous_cap*2\n");
    printf("            self.extend([None]*previous_cap)\n");
    printf("        self.len_dict = {}\n");
    printf("    def copy_to(self, new_name, old_name):\n");
    printf("        if old_name == 0:\n");
    printf("            if len(self.len_dict) > 0:\n");
    printf("                self.len_dict[new_name] = max(self.len_dict.values())\n");
    printf("            else:\n");
    printf("                self.len_dict[new_name] = self.capacity\n");
    printf("        else:\n");
    printf("            self.len_dict[new_name] = self.len_dict.get(old_name, 0)\n");
    printf("        return self\n");
    printf("    def append_to(self, name, item):\n");
    printf("        if name == 0:\n");
    printf("            if len(self.len_dict) > 0:\n");
    printf("                my_length = max(self.len_dict.values())\n");
    printf("            else:\n");
    printf("                my_length = self.capacity\n");
    printf("        else:\n");
    printf("            my_length = self.len_dict.get(name, 0)\n");
    printf("        if my_length == self.capacity:\n");
    printf("            if self.capacity == 0:\n");
    printf("                new_slice = Slice(self, 1)\n");
    printf("            else:\n");
    printf("                new_slice = Slice(self, self.capacity)\n");
    printf("            new_slice[self.capacity] = item\n");
    printf("            new_slice.len_dict[name] = my_length+1\n");
    printf("            return new_slice\n");
    printf("        else:\n");
    printf("            self[my_length] = item\n");
    printf("            self.len_dict[name] = my_length+1\n");
    printf("            return self\n");
    printf("    def __getitem__(self, item):\n");
    printf("        if not isinstance(item, int):\n");
    printf("            name, key = item\n");
    printf("            if key < self.len_dict.get(name, 0):\n");
    printf("                return super().__getitem__(key)\n");
    printf("            elif name not in self.len_dict:\n");
    printf("                element = super().__getitem__(key)\n");
    printf("                if element is None:\n");
    printf("                    raise IndexError\n");
    printf("                return element\n");
    printf("            else:\n");
    printf("                raise IndexError\n");
    printf("        else:\n");
    printf("            return super().__getitem__(item)\n");
    printf("    def __setitem__(self, item, value):\n");
    printf("        if not isinstance(item, int):\n");
    printf("            name, key = item\n");
    printf("            if key < self.len_dict.get(name, 0):\n");
    printf("                return super().__setitem__(key, value)\n");
    printf("            elif name not in self.len_dict:\n");
    printf("                if super().__getitem__(key) is None:\n");
    printf("                    raise IndexError\n");
    printf("                return super().__setitem__(key, value)\n");
    printf("            else:\n");
    printf("                raise IndexError\n");
    printf("        else:\n");
    printf("            return super().__setitem__(item, value)\n");
    printf("    def get_length(self, name):\n");
    printf("        return self.len_dict.get(name, 0)\n");
    printf("    def get_capacity(self):\n");
    printf("        return self.capacity\n");
}

void codeHelperFloatFormatCheck(){
    printf("def format_check(*args):\n");
    printf("    res=[]\n");
    printf("    for arg in args:\n");
    printf("        if isinstance(arg, float):\n");
    printf("            floating_str = '{}{:.6e}'.format('+' if arg>=0 else '', arg)\n");
    printf("            floating_str = floating_str if floating_str[-3].isdigit() else floating_str[:-2] + '0' + floating_str[-2:]\n");
    printf("            res.append(floating_str)\n");
    printf("        elif isinstance(arg, bool):\n");
    printf("            res.append('true' if arg else 'false')\n");
    printf("        else:\n");
    printf("            res.append(arg)\n");
    printf("    return res\n");
}

void codeHelperCast(){
    printf("def casting(typa, exp):\n");
    printf("    if isinstance(typa, str):\n");
    printf("        if isinstance(exp, int):\n");
    printf("            return chr(exp)\n");
    printf("        return str(exp)\n");
    printf("    if isinstance(typa, int):\n");
    printf("        return int(exp)\n");
    printf("    if isinstance(typa, float):\n");
    printf("        return float(exp)\n");
    printf("    if isinstance(typa, bool):\n");
    printf("        return bool(exp)\n");
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
    printf("from copy import deepcopy\n");
    codeHelperBreak();
    codeHelperSlice();
    codeHelperFloatFormatCheck();
    codeHelperCast();
    codeHelperBasicTypes();
}

void codeDecl(DCL *d, int to_indent) {
    if (d != NULL) {
        switch (d->kind) {
        case typeDcl:
            codeTypeDcl(d->val.typeDecl, to_indent);
            break;
        case varDcl:
            codeVarDcl(d->val.varDecl,to_indent);
            break;
        }
    }
}
void codeTypeDcl(TYPEDECL *t, int to_indent) {
    if (t != NULL) {
        codeTypeSpec(t->typeSpec, to_indent);
    }
}

void codeVarDcl(VARDECL *v, int to_indent) {
    if (v != NULL) {
        codeVarSpec(v->var_specs, to_indent);
    }
}

void codeDefaultValues(TYPE *t){
    switch (t->kind)
    {
        case k_slices:
            printf("Slice()");
            break;
        case k_array:
            printf("[");
            codeDefaultValues(t->underLineType);
            printf(" for _ in range(%d)]", t->array_type.size);
            break;
        case k_type_struct:
            if (strcmp(t->id, "struct") == 0){
                printf("{");
                FIELD_DCL *f = t->struct_type.field_dcls;
                    while(f){
                    ID_LIST *i = f->id_list;
                    while(i){
                        printf("\"%s\": ", i->id);
                        codeDefaultValues(f->type);
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
                printf("}");
            } else {
                printf("deepcopy(___%s)", t->id);
            }
            break;
        default:
            printf("___%s", t->id);
            break;
    }
}

void codeTypeSpec(TYPESPEC *ts, int to_indent) {
    if (ts == NULL) {
        return;
    }
    if (to_indent){
        indent();
    }
    printf("___%s = ", ts->id);
    codeDefaultValues(ts->type);
    printf("\n");
    codeTypeSpec(ts->next,1);
}

void codeVarSpec(VARSPEC *vs, int to_indent) {
    if (vs == NULL) {
        return;
    }
    if (to_indent){
        indent();
    }
    codeIDList(vs->id_list, false);
    printf(" ");
    EXP *c = vs->exp_list;
    if (c != NULL) {
        printf("= ");
        codeEXP(c, true, NULL, NULL, vs->id_list);
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
    }
    printf("\n");
    codeVarSpec(vs->next, 1);
}

void codeIDList(ID_LIST *i, bool func_params) {
    if (i != NULL) {
        if (func_params && strcmp(i->id, "_") == 0){
            printf("___%d", getUID());
        } else if (i->top_level){
            printf("globals()['_%llu']", i->uid);
        } else {
            printf("_%llu", i->uid);
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
            main_body = f->body->val.block;
            return;
        }
        printf("def ___%s(", f->id);
        codeSig(f->signature);
        code_indentation++;
        if (f->body->val.block != NULL){
            codeSTMT(f->body->val.block, true, true, NULL);
        } else {
            indent();
            printf("pass\n");
        }
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

void codeEXP(EXP *exp, bool to_copy, char *switch_clause, EXP *lhs_exp, ID_LIST *lhs_id) {
    if (exp == NULL)
        return;
    if (switch_clause != NULL){
        printf("%s", switch_clause);
    }
    if (to_copy && (isArray(exp->type) || isStruct(exp->type))){
        printf("deepcopy(");
    }
    switch (exp->kind) {
    case orExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, NULL, NULL, NULL);
        printf(" or ");
        codeEXP(exp->val.binary.rhs, false, NULL, NULL, NULL);
        printf(")");
        break;
    case andExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, NULL, NULL, NULL);
        printf(" and ");
        codeEXP(exp->val.binary.rhs, false, NULL, NULL, NULL);
        printf(")");
        break;
    case equalsExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, NULL, NULL, NULL);
        printf(" == ");
        codeEXP(exp->val.binary.rhs, false, NULL, NULL, NULL);
        printf(")");
        break;
    case notequalsExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, NULL, NULL, NULL);
        printf(" != ");
        codeEXP(exp->val.binary.rhs, false, NULL, NULL, NULL);
        printf(")");
        break;
    case lessExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, NULL, NULL, NULL);
        printf(" < ");
        codeEXP(exp->val.binary.rhs, false, NULL, NULL, NULL);
        printf(")");
        break;
    case greaterExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, NULL, NULL, NULL);
        printf(" > ");
        codeEXP(exp->val.binary.rhs, false, NULL, NULL, NULL);
        printf(")");
        break;
    case lessEqualsExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, NULL, NULL, NULL);
        printf(" <= ");
        codeEXP(exp->val.binary.rhs, false, NULL, NULL, NULL);
        printf(")");
        break;
    case greaterEqualsExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, NULL, NULL, NULL);
        printf(" >= ");
        codeEXP(exp->val.binary.rhs, false, NULL, NULL, NULL);
        printf(")");
        break;
    case plusExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, NULL, NULL, NULL);
        printf(" + ");
        codeEXP(exp->val.binary.rhs, false, NULL, NULL, NULL);
        printf(")");
        break;
    case minusExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, NULL, NULL, NULL);
        printf(" - ");
        codeEXP(exp->val.binary.rhs, false, NULL, NULL, NULL);
        printf(")");
        break;
    case bitwiseOrExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, NULL, NULL, NULL);
        printf(" | ");
        codeEXP(exp->val.binary.rhs, false, NULL, NULL, NULL);
        printf(")");
        break;
    case bitwiseXorExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, NULL, NULL, NULL);
        printf(" ^ ");
        codeEXP(exp->val.binary.rhs, false, NULL, NULL, NULL);
        printf(")");
        break;
    case bitwiseAndExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, NULL, NULL, NULL);
        printf(" & ");
        codeEXP(exp->val.binary.rhs, false, NULL, NULL, NULL);
        printf(")");
        break;
    case bitClearExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, NULL, NULL, NULL);
        printf(" &~ ");
        codeEXP(exp->val.binary.rhs, false, NULL, NULL, NULL);
        printf(")");
        break;
    case timesExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, NULL, NULL, NULL);
        printf(" * ");
        codeEXP(exp->val.binary.rhs, false, NULL, NULL, NULL);
        printf(")");
        break;
    case divExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, NULL, NULL, NULL);
        printf(" / ");
        codeEXP(exp->val.binary.rhs, false, NULL, NULL, NULL);
        printf(")");
        break;
    case modExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, NULL, NULL, NULL);
        printf(" %% ");
        codeEXP(exp->val.binary.rhs, false, NULL, NULL, NULL);
        printf(")");
        break;
    case leftShiftExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, NULL, NULL, NULL);
        printf(" << ");
        codeEXP(exp->val.binary.rhs, false, NULL, NULL, NULL);
        printf(")");
        break;
    case rightShiftExpr:
        printf("(");
        codeEXP(exp->val.binary.lhs, false, NULL, NULL, NULL);
        printf(" >> ");
        codeEXP(exp->val.binary.rhs, false, NULL, NULL, NULL);
        printf(")");
        break;
    case uMinusExpr:
        printf(" -");
        codeEXP(exp->val.unary.exp, false, NULL, NULL, NULL);
        break;
    case uPlusExpr:
        printf(" +");
        codeEXP(exp->val.unary.exp, false, NULL, NULL, NULL);
        break;
    case uBangExpr:
        printf(" not ");
        codeEXP(exp->val.unary.exp, false, NULL, NULL, NULL);
        break;
    case uCaretExpr:
        printf(" ^");
        codeEXP(exp->val.unary.exp, false, NULL, NULL, NULL);
        break;
    case uBitwiseAndExpr:
        printf(" &");
        codeEXP(exp->val.unary.exp, false, NULL, NULL, NULL);
        break;

    case funcExpr:
        printf("___%s(", exp->val.func.name->val.id);
        codeEXP(exp->val.func.args, true, NULL, NULL, NULL);
        printf(")");
        break;

    case castExpr:
        printf("casting(___%s, ", exp->type->id);
        codeEXP(exp->val.cast.exp, false, NULL, NULL, NULL);
        printf(")");
        break;

    case appendExpr:
        codeEXP(exp->val.append.head, false, NULL, NULL, NULL);
        printf(".append_to(%llu, ", exp->val.append.head->uid);
        codeEXP(exp->val.append.tail, false, NULL, NULL, NULL);
        printf(")");
        break;
    case lenExpr:
        if (isSlices(exp->val.expr->type)) {
            codeEXP(exp->val.expr, false, NULL, NULL, NULL);
            printf(".get_length(%llu)", exp->val.expr->uid);
        } else {
            printf("len(");
            codeEXP(exp->val.expr, false, NULL, NULL, NULL);
            printf(")");
        }
        break;
    case capExpr:
        if (isSlices(exp->val.expr->type)) {
            codeEXP(exp->val.expr, false, NULL, NULL, NULL);
            printf(".get_capacity()");
        } else {
            printf("len(");
            codeEXP(exp->val.expr, false, NULL, NULL, NULL);
            printf(")");
        }
        break;
    case arrayExpr:
        codeEXP(exp->val.array.exp, false, NULL, NULL, NULL);
        printf("[");
        codeEXP(exp->val.array.index, false, NULL, NULL, NULL);
        printf("]");
        break;
    case sliceExpr:
        codeEXP(exp->val.array.exp, false, NULL, NULL, NULL);
        printf("[%llu, ", exp->val.array.exp->uid);
        codeEXP(exp->val.array.index, false, NULL, NULL, NULL);
        printf("]");
        break;
    case selectorExpr:
        codeEXP(exp->val.selector.exp, false, NULL, NULL, NULL);
        printf("[\"%s\"]", exp->val.selector.name);
        break;
    case idExpr:
        if (exp->top_level){
            printf("globals()['_%llu']", exp->uid);
        } else {
            printf("_%llu", exp->uid);
        }
        break;
    case intExpr:
        printf("%ld", exp->val.intVal);
        break;
    case floatExpr:
        printf("%.*f", DBL_DIG-1, exp->val.floatVal);
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
    if (to_copy && (isArray(exp->type) || isStruct(exp->type))){
        printf(")");
    } else if (to_copy && isSlices(exp->type)){
        if (lhs_exp != NULL){
            printf(".copy_to(%llu, %llu)", lhs_exp->uid, exp->uid);
        } else if (lhs_id != NULL){
            printf(".copy_to(%llu, %llu)", lhs_id->uid, exp->uid);
        }
    }
    if (switch_clause != NULL){
        printf(")");
    }
    if (exp->next != NULL) {
        if (switch_clause != NULL){
            printf(" or ");
        } else { 
            printf(", ");
        }

        if (lhs_exp != NULL){
            codeEXP(exp->next, to_copy, switch_clause, lhs_exp->next, NULL);
        } else if (lhs_id != NULL){
            codeEXP(exp->next, to_copy, switch_clause, NULL, lhs_id->next);
        } else {
            codeEXP(exp->next, to_copy, switch_clause, NULL, NULL);
        }
    }
}

void codeCASE_CLAUSE(CASE_CLAUSE *c, int cond_var, bool first_case, STMT *post_stmt) {
    if (c != NULL) {
        indent();
        switch (c->kind) {
        case caseK:
            
            if (first_case){
                printf("if ");
            } else {
                printf("elif ");
            }
            char *clause = malloc(256);
            sprintf(clause, "___%d == (", cond_var);
            codeEXP(c->caseExp, false, clause, NULL, NULL);
            free(clause);
            printf(":\n");
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
        if (c->caseStmt != NULL){
            codeSTMT(c->caseStmt, true, true, post_stmt);
        } else {
            indent();
            printf("pass\n");
        }
        code_indentation--;
        codeCASE_CLAUSE(c->next, cond_var, false, post_stmt);
    }
}

void codeAssignStmt(STMT *stmt) {
    if (stmt != NULL) {
        codeEXP(stmt->val.assignStmtVal.lhs, false, NULL, NULL, NULL);
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
        codeEXP(stmt->val.assignStmtVal.rhs, true, NULL, stmt->val.assignStmtVal.lhs, NULL);
    }
}

void codeSTMT(STMT *stmt, bool to_indent, bool new_line, STMT *post_stmt) {
    if (to_indent && stmt!=NULL && stmt->kind != emptyStmt && stmt->kind != blockStmt) {
        indent();
    }
    if (stmt != NULL) {
        switch (stmt->kind) {
        case continueStmt:
            if (post_stmt != NULL){
                codeSTMT(post_stmt, false, true, NULL);
            }
            indent();
            printf("continue");
            break;
        case breakStmt:
            printf("raise Broke");
            break;
        case blockStmt:
            codeSTMT(stmt->val.block, true, true, post_stmt);
            break;
        case ifStmt:            
            if (stmt->val.ifStmtVal.ifSimpleStmt != NULL) {
                codeSTMT(stmt->val.ifStmtVal.ifSimpleStmt, false, true, NULL);
                indent();
            }
            printf("if ");
            codeEXP(stmt->val.ifStmtVal.ifCond, false, NULL, NULL, NULL);
            printf(":\n");
            code_indentation++;
            if (stmt->val.ifStmtVal.ifBody->val.block != NULL){
                codeSTMT(stmt->val.ifStmtVal.ifBody->val.block, true, true, post_stmt);
            } else {
                indent();
                printf("pass\n");
            }            
            code_indentation--;
            if (stmt->val.ifStmtVal.elseStmt != NULL){
                codeSTMT(stmt->val.ifStmtVal.elseStmt, true, true, post_stmt);
            }
            break;
        case elseStmt:
            printf("else:\n");
            if(stmt->val.elseStmtVal.elseBody != NULL){
                code_indentation++;
                if (stmt->val.elseStmtVal.elseBody->val.block != NULL){
                    codeSTMT(stmt->val.elseStmtVal.elseBody->val.block, true, true, post_stmt);
                } else {
                    indent();
                    printf("pass\n");
                }  
                code_indentation--;
            }
            if (stmt->val.elseStmtVal.ifStmt != NULL){
                code_indentation++;
                codeSTMT(stmt->val.elseStmtVal.ifStmt, true, true, post_stmt);
                code_indentation--;
            }

            break;
        case printStmt:
            printf("print(*format_check(");
            codeEXP(stmt->val.printExpList, false, NULL, NULL, NULL);
            printf("), sep='', end='')");
            break;
        case printlnStmt:
            printf("print(*format_check(");
            codeEXP(stmt->val.printlnExpList, false, NULL, NULL, NULL);
            printf("), sep=' ', end='\\n')");
            break;
        case returnStmt:
            printf("return ");
            codeEXP(stmt->val.returnExp, false, NULL, NULL, NULL);
            break;
        case switchStmt:
            printf("try:\n");
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
                codeEXP(stmt->val.switchStmtVal.switchExp, false, NULL, NULL, NULL);
            }
            printf("\n");
            codeCASE_CLAUSE(stmt->val.switchStmtVal.switchCases, temporaryVar, true, post_stmt);
            code_indentation--;
            indent();
            printf("except Broke:\n");
            code_indentation++;
            indent();
            printf("pass");
            code_indentation--;
            freeUID(temporaryVar);
            break;
        case emptyStmt:
            break;
        case expStmt:
            printf("(");
            codeEXP(stmt->val.expStmtVal, false, NULL, NULL, NULL);
            printf(")");
            break;
        case assignStmt:
            codeAssignStmt(stmt);
            break;
        case incStmt:
            codeEXP(stmt->val.incExp, false, NULL, NULL, NULL);
            printf("+=1");
            break;
        case decStmt:
            codeEXP(stmt->val.decExp, false, NULL, NULL, NULL);
            printf("-=1");
            break;
        case shortVarDecStmt:
            codeIDList(stmt->val.shortVarDecStmtVal.ids, false);
            printf(" = ");
            codeEXP(stmt->val.shortVarDecStmtVal.exps, true, NULL, NULL, stmt->val.shortVarDecStmtVal.ids);
            break;
        case forStmt:
            printf("try:\n");
            code_indentation++;
            if (stmt->val.forStmtVal.forClause == NULL){
                indent();
                if (stmt->val.forStmtVal.forCond == NULL){
                    printf("while True:\n");
                } else {
                    printf("while ");
                    codeEXP(stmt->val.forStmtVal.forCond, false, NULL, NULL, NULL);
                    printf(":\n");
                }
                code_indentation++;
                if (stmt->val.forStmtVal.forBody->val.block != NULL){
                    codeSTMT(stmt->val.forStmtVal.forBody->val.block, true, true, NULL);
                } else {
                    indent();
                    printf("pass\n");
                }
                code_indentation--;
            } else {
                codeSTMT(stmt->val.forStmtVal.forClause->first, true, true, NULL);
                indent();
                printf("while ");
                if (stmt->val.forStmtVal.forClause->condtion == NULL){
                    printf("True");
                } else {
                    codeEXP(stmt->val.forStmtVal.forClause->condtion, false, NULL, NULL, NULL);
                }
                printf(":\n");
                code_indentation++;
                if (stmt->val.forStmtVal.forBody->val.block != NULL){
                    codeSTMT(stmt->val.forStmtVal.forBody->val.block, true, true, stmt->val.forStmtVal.forClause->post);
                    codeSTMT(stmt->val.forStmtVal.forClause->post, true, true, NULL);
                } else {
                    indent();
                    printf("pass\n");
                }

                code_indentation--;
            }
            code_indentation--;
            indent();
            printf("except Broke:\n");
            code_indentation++;
            indent();
            printf("pass");
            code_indentation--;
            break;
        case dclStmt:
            codeDecl(stmt->val.decStmtVal, 0);
            break;
        }
        if (new_line && stmt->kind != emptyStmt) {
            printf("\n");
        }
        if (stmt->next){
            codeSTMT(stmt->next, to_indent, new_line, post_stmt);    
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

    // append .c to file name
    str_replace(file_name, ".go", ".py");
    remove(file_name);

    // // redirect stdout to new file
    int out = open(file_name, O_RDWR | O_APPEND | O_CREAT, 0600);
    if (-1 == out) {
        perror("Error: open file");
        return;
    }
    int save_out = dup(fileno(stdout));
    if (-1 == dup2(out, fileno(stdout))) {
        perror("Error: cannot redirect stdout");
        return;
    }

   
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

    // put stdout back
    fflush(stdout);
    close(out);
    dup2(save_out, fileno(stdout));
    close(save_out);
}
