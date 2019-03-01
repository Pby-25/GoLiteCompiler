#include "pretty.h"
#include "SymbolTable.h"
#include "stdio.h"
#include "string.h"
#include "tree.h"
#include <stdlib.h>

void prettyImports(IMPORT *i) {
    if (i != NULL) {
        printf("import %s \n", i->id);
        prettyImports(i->next);
    }
}

void prettyDecl(DCL* d) {
    if (d != NULL) {
        switch (d->kind)
        {
            case typeDcl:
                prettyTypeDcl(d->val.typeDecl);
                break;
            case varDcl:
                prettyVarDcl(d->val.varDecl);
                break;
        }
    }
}
void prettyTypeDcl(TYPEDECL *t){
    if(t!=NULL){
        printf("type ");
        
        prettyTypeSpec(t->typeSpec);
    }
}
void prettyVarDcl(VARDECL *v){
     if(v!=NULL){
        prettyVarSpec(v->var_specs);
    }
}

void prettyTypeSpec(TYPESPEC *ts){
    if (ts == NULL) {
            return;
        }
        if(ts->next == NULL){
            printf("(");
        }
        printf("%s", ts->id);
        prettyType(ts->type);
        prettyTypeSpec(ts->next);
        if(ts->next == NULL){
            printf(")");
        }
}

void prettyVarSpec(VARSPEC *vs){
    if (vs == NULL) {
        return;
    }
    prettyIdListExpList(vs->id_list, vs->exp_list, vs->lineno);
    prettyType(vs->type);
    prettyVarSpec(vs->next);
}

void prettType(TYPE *t){
    if (t == NULL) {
        return;
    }
    switch (t->kind) {
    case k_slices:
        printf("[]");
        prettType(t->slices_type.type);
        break;
    case k_array:
        printf("[%d]", t->array_type.size);
        prettType(t->array_type.type);
        break;
    case k_type_struct:
        printf("struct ");
        printf("[");
        prettyField_Dcl(t->struct_type.field_dcls);
        printf("]");
        break;
    case k_type_id:
        printf("%s", t->id);
        break;
    case k_type_type:
        printf("(");
        prettyType(t->types);
        printf(")");
        break;
    }
}

void prettyField_Dcl(FIELD_DCL *f) {
    if (f == NULL) {
        return;
    }
    prettyIDList(f->id_list);
    prettyType(f->type);
    prettyField_Dcl(f->next);
}


void prettyIDList(ID_LIST *i) {
    if (i != NULL) {
        printf("%s", i->id);
        if (i->next != NULL) {
            printf(", ");
            prettyIDList(i->next);
        }
    }
}

   
    
void prettyType(TYPE *t) {
    if (t != NULL) {
        switch (t->kind) {
            case k_type_id:
                printf("%s", id);
                break;
            case k_slices:
                printf("[] ", );
                prettyType(t->slices_type.type);
                break;
            case k_array:
                printf("[%d] ", t->array_type.size);
                prettyType(t->array_type.type);
                break;
            case k_type_struct:
                printf("struct {\n");
                prettyField_Dcl(t->struct_type.field_dcls);
                printf("}\n");
                break;
            case k_type_type:
                printf("(");
                prettyType(t->types);
                printf(")");
                break;
        }
    }
}

void prettyParams(PARAMS *p) {
    if (p != NULL) {
        prettyIDList(p->id_list);
        prettyType(p->type);
        prettyParams(p->next);
    }
}

void prettyResult(RESULT *r) {

}

void prettySig(SIGNATURE *s) {
    if (s != NULL) {
        prettyParams(s->params);
        prettyResult(s->result);
    }
}

void prettyFuncDecl(FUNCDECL *f) {
    if (f != NULL) {
        printf("func %s", f->id);
        printf("(");
        prettySig(f->signature);
        printf(")");
        prettyStmts(f->body);
    }
}

void prettyTopDecl(TOPDECL* t) {
    if (t != NULL) {
        switch (t->kind) {
            case dclK:
                prettyDecl(t->val.dcl);
                break;
            case funcDeclK:
                prettyFuncDecl(t->val.funcDecl);
                break;
        }
        prettyTopDecl(t->next);
    }
}

void prettyPROGRAM(PROGRAM *root) { 
    if (root != NULL) {
        printf("package %s ;\n", root->package->id);
        prettyImports(root->imports);
        prettyTopDecl(root->top_decl);
    }
}


void prettyEXP(EXP *exp) {

    if (exp == NULL)
        return;
    switch (exp->kind) {
    case orExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" || ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;                                                            
    case andExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" && ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case equalsExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" == ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case notequalsExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" != ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case lessExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" < ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;        
    case greaterExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" > ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;        
    case lessEqualsExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" <= ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case greaterEqualsExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" >= ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case plusExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" + ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case minusExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" - ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case bitwiseOrExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" | ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case bitwiseXorExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" ^ ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case bitwiseAndExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" & ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case bitClearExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" &^ ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;    
    case timesExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" * ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;    
    case divExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" / ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case modExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" % ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;    
    case leftShiftExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" << ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case rightShiftExpr:
        printf("(");
        prettyEXP(exp->val.binary.lhs);
        printf(" >> ");
        prettyEXP(exp->val.binary.rhs);
        printf(")");
        break;
    case uMinusExpr:
        printf(" -");
        prettyEXP(exp->val.unary.exp);
        break;    
    case uPlusExpr:
        printf(" +");
        prettyEXP(exp->val.unary.exp);
        break;
    case uBangExpr:
        printf(" !");
        prettyEXP(exp->val.unary.exp);
        break;
    case uCaretExpr:
        printf(" ^");
        prettyEXP(exp->val.unary.exp);
        break;    
    case uBitwiseAndExpr:
        printf(" &");
        prettyEXP(exp->val.unary.exp);
        break;

    case funcExpr:
        prettyEXP(exp->val.func.name);
        printf("(");
        prettyEXP(exp->val.func.args);
        printf(")");
        break;

    case castExpr:
        prettyEXP(exp->val.cast.type);
        printf("(");
        prettyEXP(exp->val.cast.exp);
        printf(")");
        break;

    case appendExpr:
        printf("append(");
        prettyEXP(exp->val.append.head);
        printf(",");
        prettyEXP(exp->val.append.tail);
        printf(")");
        break;

    case arrayExpr:
    case sliceExpr:
        prettyEXP(exp->val.array.exp);
        printf("[");   
        prettyEXP(exp->val.array.index);                                                                            
        printf("]");
        break;

    case selectorExpr:
        prettyEXP(exp->val.selector.exp);
        printf(".%s", exp->val.selector.name);        
        break;

    case expList:;
        EXP *e = exp;
        while (e->val.expr != NULL) {
            prettyEXP(e->val.expr);
            if ( e->next != NULL) {
                printf(", ");
            }
            e = e->next;
        }
    
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
        printf("%c", exp->val.runeVal);
        break;
    case stringItpExpr:
    case stringRawExpr:
        printf("\"%s\"", exp->val.stringVal);
        break;       
    case boolExpr:
        exp->val.boolVal ? printf("true") : printf("false");
        break;
    default:
        break;
    }
}

void prettyCASE_CLAUSE(CASE_CLAUSE *c){
    if (c != NULL) {
        switch (c->kind) {
            case caseK:
                printf("case ");
                prettyEXP(c->caseExp);
                printf(" :\n");
                prettySTMT(c->caseStmt);
                break;
            case defaultK:
                printf("default:\n");
                prettySTMT(c->caseStmt);
                break;
        }
        prettyCASE_CLAUSE(c->next);        
    }
}

void prettyAssignStmt(STMT *stmt) {
    if (stmt != NULL) {
        prettyEXP(stmt->val.assignStmtVal.lhs);
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
                printf(" \%= ");
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
                printf(" &^= ");      
                break;  
        }
        prettyEXP(stmt->val.assignStmtVal.rhs);
        printf("\n");
    }
}

void prettyFOR_CLAUSE(FOR_CLAUSE *f) {
    if (f != NULL) {
        prettySTMT(f->first);
        printf(";");
        prettyEXP(f->condtion);
        printf(";");
        prettySTMT(f->post);
    }
}

void prettySTMT(STMT *stmt) {
    if (stmt != NULL) {
        switch (stmt->kind) {
        case continueStmt:
            printf("continue\n");
            break;
        case breakStmt:
            printf("break\n");
            break;
        case blockStmt:
            printf("{\n");
            prettySTMT(stmt->val.block);
            printf("}\n");
            break;
        case ifStmt:
            printf("if ");
            if (stmt->val.ifStmtVal.ifSimpleStmt != NULL){
                prettySTMT(stmt->val.ifStmtVal.ifSimpleStmt);
                printf(";");
            }
            prettyEXP(stmt->val.ifStmtVal.ifCond);
            prettySTMT(stmt->val.ifStmtVal.ifBody);
            prettySTMT(stmt->val.ifStmtVal.elseStmt);
            break;
        case elseStmt:
            printf("else ");
            prettySTMT(stmt->val.elseStmtVal.elseBody);
            prettySTMT(stmt->val.elseStmtVal.ifStmt);
            break;
        case printStmt:
            printf("print(");
            prettyEXP(stmt->val.printExpList);
            printf(")\n");
            break;
        case printlnStmt:
            printf("println(");
            prettyEXP(stmt->val.printlnExpList);
            printf(")\n");
            break;
        case returnStmt:
            printf("return ")
            prettyEXP(stmt->val.returnExp);
            printf("\n");
            break;
        case switchStmt:
            printf("switch");
            if (stmt->val.switchStmtVal.switchSimpleStmt != NULL) {
                prettySTMT(stmt->val.switchStmtVal.switchSimpleStmt);
                printf(";");
            }
            prettyEXP(stmt->val.switchStmtVal.switchExp);
            printf("{\n");
            prettyCASE_CLAUSE(stmt->val.switchStmtVal.switchCases);
            printf("}\n");
            break;
        case emptyStmt:
            break;
        case expStmt:
            prettyEXP(stmt->val.expStmtVal);
            break;
        case assignStmt:
            prettyAssignStmt(stmt);
            break;
        case incStmt:
            prettyEXP(stmt->val.incExp);
            printf("++\n");
            break;
        case decStmt:
            prettyEXP(stmt->val.decExp);
            printf("--\n");
            break;
        case shortVarDecStmt:
            prettyID_LIST(stmt->val.shortVarDecStmtVal.ids);
            printf(" := ");
            prettyEXP(stmt->val.shortVarDecStmtVal.exps);
            printf("\n");
            break;
        case forStmt:
            printf("for ");
            prettyEXP(stmt->val.forStmtVal.forCond);
            prettyFOR_CLAUSE(stmt->val.forStmtVal.forClause);
            printf(" ");
            prettySTMT(stmt->val.forStmtVal.forBody);
            break;
        case dclStmt:
            prettyDECL(stmt->val.decStmtVal);
            break;
        default:
            break;
        }
        prettySTMT(stmt->next);
    }
}