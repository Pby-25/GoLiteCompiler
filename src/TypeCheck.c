#include "TypeCheck.h"
#include "SymbolTable.h"
#include "stdio.h"
#include "tree.h"
#include "weed.h"
#include <stdlib.h>
#include <string.h>

int type_indentation = 0;
void errorType(char *expected, char *actual, int lineno) {
    fprintf(stderr, "Error: (line %d): Expected type %s, but got %s\n", lineno,
            expected, actual);
    exit(1);
}

TYPE *strToType(char *s){
    TYPE *t = malloc(sizeof(TYPE));
    t->id = s;
    t->kind = k_type_id;
    isIdBaseType(t);
    return t;
}

TYPE *findSelectorIdType(char *name, TYPE *structType){
    if (structType->kind != k_type_struct){
        errorType("struct", structType->id, structType->lineno);
    }
    FIELD_DCL *f_dcl = structType->struct_type.field_dcls;

    while (f_dcl){
        ID_LIST *idl = f_dcl->id_list;
        while (idl){
            if (strcmp(name, idl->id)==0){
                return f_dcl->type;
            }
            idl = idl->next;
        }
        f_dcl = f_dcl->next;
    }
    return NULL;
}

void typeCheckProgram(PROGRAM *prog) {
    makeSymbolTable(prog);
    typeTopDecl(prog->top_decl);
}

bool isBool(TYPE *t){
    return checkSameType(t, strToType("bool"));
} 

bool isInteger(TYPE *t){
    return checkSameType(t, strToType("int")) || checkSameType(t, strToType("rune"));
}

bool isNumeric(TYPE *t){
    return isInteger(t) || checkSameType(t, strToType("float64"));
}

bool isOrdered(TYPE *t){
    return isNumeric(t) || checkSameType(t, strToType("string"));
}

bool isComparable(TYPE *t){
    if (isOrdered(t) || isBool(t)) return true;
    switch (t->kind) {
        case k_array:
            return isComparable(t->array_type.type);
        case k_type_struct:;
            FIELD_DCL *anyField = t->struct_type.field_dcls;
            while (anyField){
                if (!isComparable(anyField->type)) return false;
                anyField = anyField->next;
            }
            return true;
        default:
            return false;
    }
}



bool checkSameType(TYPE *t1, TYPE *t2) {
    if (t1 == NULL || t2 == NULL) {
        fprintf(stderr, "\ncheck same type null\n");
        exit(1);
        return false;
    }
    switch (t1->kind) {
        case k_slices:
            if(t2->kind == k_slices){
                return checkSameType(t1->slices_type.type, t2->slices_type.type);
            }else{
                return false;
            }
            break;
        case k_array:
            if(t2->kind == k_array){
                return checkSameType(t1->array_type.type, t2->array_type.type);
            } else {
                return false;
            }
            break;
        case k_type_struct:
            return strcmp(t1->id, t2->id)==0;
            break;
        case k_type_id:
            // printf("k_type_id %d %d",t1->id_type.baseTypeKind,t2->id_type.baseTypeKind);
            isIdBaseType(t1);
            isIdBaseType(t2);
            // printf("k_type_id %d %d",t1->id_type.baseTypeKind,t2->id_type.baseTypeKind);
            // return t1->id_type.baseTypeKind == t2->id_type.baseTypeKind;
            printf("names: %s, %s",t1->id, t2->id);
            return strcmp(t1->id, t2->id)==0;
            break;
        case k_type_type:
            if(t2->kind == k_type_type){
                return checkSameType(t1->types, t2->types);
            }else{
                return false;
            }
            break;
        case k_infer:
            // t1 = t2;
            return false;
            break;
    }
    
    return false;
}

void typeDecl(DCL *d, int infunc) {
    if (d != NULL) {
        switch (d->kind) {
        case typeDcl:
            typeTypeDcl(d->val.typeDecl);
            break;
        case varDcl:
            typeVarDcl(d->val.varDecl,infunc);
            break;
        }
    }
}

void typeTypeDcl(TYPEDECL *t) {
    if (t != NULL) {
        typeTypeSpec(t->typeSpec, 1);
    }
}

void typeVarDcl(VARDECL *v, int infunc) {
    if (v != NULL) {
        typeVarSpec(v->var_specs);
    }
}

void typeTypeSpec(TYPESPEC *ts, int needParen) {
    if (ts == NULL) {
        return;
    }
    typeTypeSpec(ts->next,0);
}

void typeIdListExpList(ID_LIST *idl, EXP *el){
    ID_LIST *ic = idl;
    EXP *ec = el;
    while(ic != NULL && ec != NULL){
        if (!checkSameType(ic->type, ec->type)) {
            errorType(ic->type->id,ec->type->id, ic->lineno);
        }
        ic = ic->next;
        ec = ec->next;
    }
}

void typeVarSpec(VARSPEC *vs) {
    if (vs == NULL) {
        return;
    }

    if (vs->type != NULL) {
        typeIdListExpList(vs->id_list,vs->exp_list);
    }
    typeVarSpec(vs->next);
}

void typeField_Dcl(FIELD_DCL *f) {
    if (f == NULL) {
        return;
    }
    printIndentation();
    typeIDList(f->id_list);
    
    typeType(f->type);
    
    typeField_Dcl(f->next);
}

void typeIDList(ID_LIST *i) {
    if (i != NULL) {
        
        if (i->next != NULL) {
             
        }
        typeIDList(i->next);
    }
}

void typeType(TYPE *t) {
    if (t != NULL) {
        switch (t->kind) {
        case k_type_id:
            
            break;
        case k_slices:
            
            typeType(t->slices_type.type);
            break;
        case k_array:
            
            typeType(t->array_type.type);
            break;
        case k_type_struct:
            
            type_indentation ++;
            typeField_Dcl(t->struct_type.field_dcls);
            type_indentation --;
            printIndentation();
            
            break;
        case k_type_type:
            
            typeType(t->types);
            
            break;
        case k_infer:
            break;
        }
    }
}

void typeParams(PARAMS *p) {
    if (p != NULL) {
        typeIDList(p->id_list);
        
        typeType(p->type);
        if(p->next !=NULL){
            
            typeParams(p->next);
        }
        
    }
}

void typeFuncDecl(FUNCDECL *f) {
    if (f != NULL) {
        STMT *body = f->body;
        if (f->signature != NULL) {
            if (f->signature->result == NULL) {
                typeSTMT(body, NULL);
            } else {
                bool terminate  = weedTerminateStmt(body);
                if (!terminate) {
                    fprintf(stderr, "Error: (line %d) this function does not terminate\n", f->lineno);
                    exit(1);
                }
                typeSTMT(body, f->signature->result->type);
            }
        }
        // body = body->val.block;
        // // function return type is not void
        // // check if there is a return statement
        // if (f->signature->result != NULL) {
        //     int hasReturn = 0;
        //     while (body != NULL) {
        //         if (body->kind = returnStmt) {
        //             hasReturn = 1;
        //             break;
        //         }
        //         body = body->next;
        //     }
        //     if (!hasReturn) {
        //         fprintf(stderr, "Error: (line %d) function should return something\n", f->lineno);
        //         exit(1);
        //     } 
        // } 
    }
}

void typeTopDecl(TOPDECL *t) {
    if (t != NULL) {
        switch (t->kind) {
        case dclK:
            typeDecl(t->val.dcl, 0);
            break;
        case funcDeclK:
            typeFuncDecl(t->val.funcDecl);
            break;
        }
        typeTopDecl(t->next);
    }
}

void typePROGRAM(PROGRAM *root) {
    if (root != NULL) {
        typeTopDecl(root->top_decl);
    }
}

void typeEXP(EXP *exp) {
    // return;
    if (exp == NULL)
        return;
    switch (exp->kind) {
    case orExpr:
    case andExpr:  
        typeEXP(exp->val.binary.lhs);
        typeEXP(exp->val.binary.rhs);
        if (!isBool(exp->val.binary.lhs->type)){
            errorType("bool",exp->val.binary.lhs->type->id,exp->lineno);
        } else if (!isBool(exp->val.binary.rhs->type)){
            errorType("bool",exp->val.binary.rhs->type->id,exp->lineno);
        } else {
            exp->type = strToType("bool");
        }
        break;
    case equalsExpr:
    case notequalsExpr:
        typeEXP(exp->val.binary.lhs);
        typeEXP(exp->val.binary.rhs);
        if (!checkSameType(exp->val.binary.lhs->type, exp->val.binary.rhs->type)){
            errorType(exp->val.binary.lhs->type->id,exp->val.binary.rhs->type->id,exp->lineno);
        } else if (!isComparable(exp->val.binary.lhs->type)){
            errorType("comparable",exp->val.binary.lhs->type->id,exp->lineno);
        } else if (!isComparable(exp->val.binary.rhs->type)){
            errorType("comparable",exp->val.binary.rhs->type->id,exp->lineno);
        } else {
            exp->type = strToType("bool");
        }
        break;
    case lessExpr:
    case greaterExpr:
    case lessEqualsExpr:
    case greaterEqualsExpr:
        typeEXP(exp->val.binary.lhs);
        typeEXP(exp->val.binary.rhs);
        if (!checkSameType(exp->val.binary.lhs->type, exp->val.binary.rhs->type)){
            errorType(exp->val.binary.lhs->type->id,exp->val.binary.rhs->type->id,exp->lineno);
        } else if (!isOrdered(exp->val.binary.lhs->type)){
            errorType("ordered",exp->val.binary.lhs->type->id,exp->lineno);
        } else if (!isOrdered(exp->val.binary.rhs->type)){
            errorType("ordered",exp->val.binary.rhs->type->id,exp->lineno);
        } else {
            exp->type = strToType("bool");
        }
        break;
    case plusExpr:
        typeEXP(exp->val.binary.lhs);
        typeEXP(exp->val.binary.rhs);
        if (!checkSameType(exp->val.binary.lhs->type, exp->val.binary.rhs->type)){
            errorType(exp->val.binary.lhs->type->id,exp->val.binary.rhs->type->id,exp->lineno);
        } else if (!isOrdered(exp->val.binary.lhs->type)){
            errorType("ordered",exp->val.binary.lhs->type->id,exp->lineno);
        } else if (!isOrdered(exp->val.binary.rhs->type)){
            errorType("ordered",exp->val.binary.rhs->type->id,exp->lineno);
        } else {
            exp->type = exp->val.binary.lhs->type;
        }
        break;
    case minusExpr:
    case timesExpr:
    case divExpr:
        typeEXP(exp->val.binary.lhs);
        typeEXP(exp->val.binary.rhs);
        if (!checkSameType(exp->val.binary.lhs->type, exp->val.binary.rhs->type)){
            errorType(exp->val.binary.lhs->type->id,exp->val.binary.rhs->type->id,exp->lineno);
        } else if (!isNumeric(exp->val.binary.lhs->type)){
            errorType("numeric",exp->val.binary.lhs->type->id,exp->lineno);
        } else if (!isNumeric(exp->val.binary.rhs->type)){
            errorType("numeric",exp->val.binary.rhs->type->id,exp->lineno);
        } else {
            exp->type = exp->val.binary.lhs->type;
        }
        break;
    case bitwiseOrExpr:
    case bitwiseXorExpr:
    case bitwiseAndExpr:
    case bitClearExpr:
    case modExpr:
    case leftShiftExpr:
    case rightShiftExpr:
        typeEXP(exp->val.binary.lhs);
        typeEXP(exp->val.binary.rhs);
        if (!checkSameType(exp->val.binary.lhs->type, exp->val.binary.rhs->type)){
            errorType(exp->val.binary.lhs->type->id,exp->val.binary.rhs->type->id,exp->lineno);
        } else if (!isInteger(exp->val.binary.lhs->type)){
            errorType("integer",exp->val.binary.lhs->type->id,exp->lineno);
        } else if (!isInteger(exp->val.binary.rhs->type)){
            errorType("integer",exp->val.binary.rhs->type->id,exp->lineno);
        } else {
            exp->type = exp->val.binary.lhs->type;
        }
        break;
    case uMinusExpr:
    case uPlusExpr:
        typeEXP(exp->val.unary.exp);
        if (!isNumeric(exp->val.unary.exp->type)){
            errorType("numeric",exp->val.unary.exp->type->id,exp->lineno);
        } else{
            exp->type = exp->val.unary.exp->type;
        }
        break;
    case uBangExpr:
        typeEXP(exp->val.unary.exp);
        if (!isBool(exp->val.unary.exp->type)){
            errorType("bool",exp->val.unary.exp->type->id,exp->lineno);
        } else {
            exp->type = exp->val.unary.exp->type;
        }
        break;
    case uCaretExpr:
    case uBitwiseAndExpr:
        typeEXP(exp->val.unary.exp);
        if (!isInteger(exp->val.unary.exp->type)){
            errorType("integer",exp->val.unary.exp->type->id,exp->lineno);
        } else{
            exp->type = exp->val.unary.exp->type;
        }
        break;
    case funcExpr:
        typeEXP(exp->val.func.name);
        typeEXP(exp->val.func.args);
        if (strcmp(exp->val.func.name->val.id, "init")==0){
            fprintf(stderr, "Error: (line %d): Function \"init\" shall never be called\n", exp->lineno);
            exit(1);
        }
        // function type assigned in symbol
        break;

    case castExpr:
        typeEXP(exp->val.cast.type);
        typeEXP(exp->val.cast.exp);
        if (!isIdBaseType(exp->val.cast.type->type)){
            errorType("base",exp->val.cast.type->type->id,exp->lineno);
        }
        if (!checkSameType(exp->val.cast.type->type, exp->val.cast.exp->type)){
            if (!isNumeric(exp->val.cast.type->type) || !isNumeric(exp->val.cast.exp->type)){
                if (!checkSameType(exp->val.cast.type->type, strToType("string")) || !isInteger(exp->val.cast.exp->type)){
                    errorType("valid cast type","invalid cast type",exp->lineno);
                }
            }
        }
        exp->type = exp->val.cast.type->type;
        break;

    case appendExpr:
        typeEXP(exp->val.append.head);
        typeEXP(exp->val.append.tail);
        if (exp->val.append.head->type->kind != k_array && exp->val.append.head->type->kind != k_slices){
            errorType("array or slice", exp->val.append.head->type->id, exp->lineno);
        }
        TYPE *expectedType = exp->val.append.head->val.array.exp->type;
        if (!checkSameType(expectedType, exp->val.append.tail->type)){
            errorType(expectedType->id, exp->val.append.tail->type->id, exp->lineno);
        }
        exp->type = exp->val.append.head->type;
        exp->kind = exp->val.append.head->kind;
        break;
    case lenExpr:
        typeEXP(exp->val.expr);
        if (exp->val.expr->type->kind != k_array && exp->val.expr->type->kind != k_slices 
            && !checkSameType(exp->type, strToType("string"))){
            errorType("array or slice or string", exp->val.expr->type->id, exp->lineno);
        }
        exp->type = strToType("int");
        break;
    case capExpr:
        typeEXP(exp->val.expr);
        if (exp->val.expr->type->kind != k_array && exp->val.expr->type->kind != k_slices){
            errorType("array or slice", exp->val.expr->type->id, exp->lineno);
        }
        exp->type = strToType("int");
        break;
    case arrayExpr:
    case sliceExpr:
        typeEXP(exp->val.array.exp);
        typeEXP(exp->val.array.index);
        if (exp->val.array.exp->type->kind != k_array && exp->val.array.exp->type->kind != k_slices){
            errorType("array or slice", exp->val.array.exp->type->id, exp->lineno);
        }
        // Allow index to be null, maybe create new kind later
        if (!isInteger(exp->val.array.index->type)){
            errorType("integer", exp->val.array.index->type->id, exp->lineno);
        }
        exp->type = exp->val.array.exp->type;  
        break;
    case selectorExpr:
        typeEXP(exp->val.selector.exp);
        if (exp->val.selector.exp->type->kind != k_type_struct){
            errorType("struct", exp->val.array.exp->type->id, exp->lineno);
        }
        TYPE *correspondingType = findSelectorIdType(exp->val.selector.name, exp->val.selector.exp->type);
        if (correspondingType == NULL){
            errorType(exp->val.selector.name, "Does Not Exist", exp->lineno);
        } else {
            exp->type = correspondingType;
        }
        break;
    // case idExpr:
    //     break;
    // case intExpr:
    //     break;
    // case floatExpr:
    //     break;
    // case runeExpr:
    //     break;
    // case stringItpExpr:
    //     break;
    // case stringRawExpr:
    //     break;
    // case boolExpr:
    //     break;
    default:
        break;
    }

    if (exp->next != NULL) {
            
            typeEXP(exp->next);
    }
}

void typeCASE_CLAUSE(CASE_CLAUSE *c, TYPE *returnType) {
    if (c != NULL) {
        printIndentation();
        switch (c->kind) {
        case caseK:
            typeEXP(c->caseExp);
            type_indentation++;
            typeSTMT(c->caseStmt, returnType);
            type_indentation--;
            break;
        case defaultK:
            type_indentation++;
            typeSTMT(c->caseStmt, returnType);
            type_indentation--;
            break;
        }
        typeCASE_CLAUSE(c->next, returnType);
    }
}

void typeAssignStmt(STMT *stmt) {
    if (stmt != NULL) {
        EXP *lhs = stmt->val.assignStmtVal.lhs;
        EXP *rhs = stmt->val.assignStmtVal.rhs;
        typeEXP(lhs);
        typeEXP(rhs);
        switch (stmt->val.assignStmtVal.assignKind) {
        case normal:
            if (!checkSameType(lhs->type, rhs->type)) {
                // printf("alhs: %d, rhs: %d\n", lhs->type->kind,rhs->type->kind);
                fprintf(stderr, "Error: (line %d) invalid assignment\n", lhs->lineno);
                exit(1);
            }
            break;
        case plus:
        case minus:
        case mult:
        case divide:
        case or:
        case xor:
        case mod:
        case leftShift:
        case rightShift:
        case and:
        case bitclear:
        // TODO: what to do for these cases? 
            break;
        }
    }
}

void typeFOR_CLAUSE(FOR_CLAUSE *f, TYPE *returnType) {
    if (f != NULL) {
        typeSTMT(f->first, returnType);
        typeEXP(f->condtion);
        // printf("f cond type %s", f->condtion->type->id);
        if (f->condtion != NULL && !checkSameType(f->condtion->type, strToType("bool"))) {
            fprintf(stderr, "Error: (line %d) for condition must be a boolean\n", f->lineno);
            exit(1);
        }
        typeSTMT(f->post, returnType);
    }
}

void typeSTMT(STMT *stmt, TYPE *returnType) {
    if (stmt != NULL) {
        switch (stmt->kind) {
        case continueStmt:
        case breakStmt:
            break;
        case blockStmt:
            typeSTMT(stmt->val.block, returnType);
            break;
        case ifStmt:
            if (stmt->val.ifStmtVal.ifSimpleStmt != NULL) {
                typeSTMT(stmt->val.ifStmtVal.ifSimpleStmt, returnType);
            }
            typeEXP(stmt->val.ifStmtVal.ifCond);
            if (!checkSameType(stmt->val.ifStmtVal.ifCond->type, strToType("bool"))) {
                fprintf(stderr, "Error: (line %d) if condition must be a boolean\n", stmt->lineno);
                exit(1);
            }
            typeSTMT(stmt->val.ifStmtVal.ifBody, returnType);
            typeSTMT(stmt->val.ifStmtVal.elseStmt, returnType);
            break;
        case elseStmt:
            typeSTMT(stmt->val.elseStmtVal.elseBody, returnType);
            typeSTMT(stmt->val.elseStmtVal.ifStmt, returnType);
            break;
        case printStmt:
            typeEXP(stmt->val.printExpList);
            break;
        case printlnStmt:
            typeEXP(stmt->val.printlnExpList);
            break;
        case returnStmt:;
            EXP *returnExp = stmt->val.returnExp;
            if (returnType == NULL && returnExp != NULL) {
                fprintf(stderr, "Error: (line %d) this function should not return anything\n", stmt->lineno);
                exit(1);
            }
            else if (returnType != NULL && returnExp == NULL){
                fprintf(stderr, "Error: (line %d) this function should return something\n", stmt->lineno);
                exit(1);
            }
            else {
                typeEXP(returnExp);
                if (!checkSameType(returnExp->type, returnType)) {
                    fprintf(stderr, "Error: (line %d) wrong return type\n", stmt->lineno);
                    exit(1); 
                }
            } 
            if (stmt->next != NULL) {
                fprintf(stderr, "Error: (line %d) dead code\n", stmt->lineno + 1);
                exit(1); 
            }
            break;
        case switchStmt:
            if (stmt->val.switchStmtVal.switchSimpleStmt != NULL) {
                typeSTMT(stmt->val.switchStmtVal.switchSimpleStmt, returnType);
            }
            EXP *switchExp = stmt->val.switchStmtVal.switchExp;
            typeEXP(switchExp);
            if (switchExp != NULL && !isComparable(switchExp->type)) {
                fprintf(stderr, "Error: (line %d) switch expression must be a comparable\n", stmt->lineno);
                exit(1);
            }
            typeCASE_CLAUSE(stmt->val.switchStmtVal.switchCases, returnType);
            break;
        case emptyStmt:
            break;
        case expStmt:
            typeEXP(stmt->val.expStmtVal);
            break;
        case assignStmt:
            typeAssignStmt(stmt);
            break;
        case incStmt:
            typeEXP(stmt->val.incExp);
            if (!checkSameType(stmt->val.incExp->type, strToType("int")) && !checkSameType(stmt->val.incExp->type, strToType("float64")) && !checkSameType(stmt->val.incExp->type, strToType("rune"))) {
                fprintf(stderr, "Error: (line %d) invalid increment statement\n", stmt->lineno);
                exit(1);
            }
            break;
        case decStmt:
            typeEXP(stmt->val.decExp);
            if (!checkSameType(stmt->val.decExp->type, strToType("int")) && !checkSameType(stmt->val.decExp->type, strToType("float64")) && !checkSameType(stmt->val.decExp->type, strToType("rune"))) {
                fprintf(stderr, "Error: (line %d) invalid decrement statement\n", stmt->lineno);
                exit(1);
            }
            break;
        case shortVarDecStmt:
            typeIdListExpList(stmt->val.shortVarDecStmtVal.ids, stmt->val.shortVarDecStmtVal.exps);
            // TODO: check redeclaration typechecks!
            break;
        case forStmt:
            ;
            EXP *forCond = stmt->val.forStmtVal.forCond;
            if (forCond != NULL) {
                typeEXP(forCond);
                if (!checkSameType(forCond->type, strToType("bool"))) {
                    fprintf(stderr, "Error: (line %d) for condition must be a boolean but got %s\n", stmt->lineno, forCond->type->id);
                    exit(1);
                }
            }
            typeFOR_CLAUSE(stmt->val.forStmtVal.forClause, returnType);
            typeSTMT(stmt->val.forStmtVal.forBody, returnType);
            break;
        case dclStmt:
            typeDecl(stmt->val.decStmtVal, 1);
            break;
        }
        if (stmt->next){
            typeSTMT(stmt->next, returnType);    
        }
    }
}