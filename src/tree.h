#ifndef _treeH
#define _treeH
#include <stdbool.h>

typedef enum {
    normal, 
    plus, 
    minus,
    mult,
    divide,
    or,
    xor, 
    mod, 
    leftShift,
    rightShift,
    and,
    bitclear
} AssignKind;

typedef enum {
    continueStmt,
    breakStmt,
    blockStmt,
    ifStmt,
    elseStmt,
    printStmt,
    printlnStmt,
    returnStmt,
    switchStmt,
    emptyStmt,
    expStmt,
    assignStmt,
    incStmt,
    decStmt,
    shortVarDecStmt,
    forStmt,
    dclStmt
} StatementKind;

typedef enum {
    k_slices,
    k_array,
    k_type_struct,
    k_type_id,
    k_type_type
} TypeKind;

typedef enum {
    orExpr,
    andExpr,
    equalsExpr,
    notequalsExpr,
    lessExpr,
    lessEqualsExpr,
    greaterExpr,
    greaterEqualsExpr,
    plusExpr,
    minusExpr,
    timesExpr,
    divExpr,
    modExpr,
    leftShiftExpr,
    rightShiftExpr,
    bitwiseOrExpr,
    bitwiseXorExpr,
    bitwiseAndExpr,
    bitClearExpr,
    uPlusExpr,
    uMinusExpr,
    uBangExpr,
    uCaretExpr,
    uBitwiseAndExpr,
    intExpr,
    floatExpr,
    runeExpr,
    stringItpExpr,
    stringRawExpr,
    idExpr,
    boolExpr,
    appendExpr,
    lenExpr,
    capExpr,
    indexExpr,
    selectorExpr,
    funcExpr,
    castExpr,
    lenExpr,
    capExpr
} ExpKind;

// j
typedef struct ID_LIST ID_LIST;
struct ID_LIST {
    int lineno;
    char *id;
    ID_LIST *next;
};

ID_LIST *makeIdList(ID_LIST *l, char *id, int lineno);

// du
typedef struct EXP EXP;
struct EXP {
    int lineno;
    ExpKind kind;
    union {
        char *id;
        char *stringVal;
        char runeVal;
        int intVal;
        bool boolVal;
        double floatVal;
        struct {
            EXP *lhs;
            EXP *rhs;
        } binary;
        struct {
            EXP *exp;
        } unary;
        struct {
            EXP *name;
            EXP *args;
        } func;
        struct {
            EXP *type;
            EXP *exp;
        } cast;
        struct {
            EXP *head;
            EXP *tail;
        } append;
        struct {
            EXP *exp;
            int *index;
        } array;
        struct {
            EXP *exp;
            char *name;
        } selector;
        EXP *expr;
    } val;
    TYPE *type;
    EXP *next;
};
EXP *makeExpList();
EXP *makeBooleanExp(bool boolean, int lineno);
EXP *makeIdentifierExp(char *identifier, int lineno);
EXP *makeStringExp(char *stringval, int lineno);
EXP *makeRuneExp(char runeval, int lineno);
EXP *makeIntExp(int intval, int lineno);
EXP *makeFloat64Exp(double float64val, int lineno);
EXP *makeBoolExp(int boolval, int lineno);
EXP *makeBinaryExp(ExpKind kind, EXP *lhs, EXP *rhs, int lineno);
EXP *makeUnaryExp(ExpKind kind, EXP *exp, int lineno);
EXP *makeFuncExp(EXP *func_exp, EXP *args, int lineno);
EXP *makeCastExp(TYPE *type, EXP *exp, int lineno);
EXP *makeAppendExp(EXP *head, EXP *tail, int lineno);
EXP *makeArrayIndexExp(EXP *array_exp, EXP *index, int lineno);
EXP *makeSelectorExp(EXP *struct_exp, char *field_name, int lineno);
EXP *makeLenExp(EXP *exp, int lineno);
EXP *makeCapExp(EXP *exp, int lineno);

typedef struct FIELD_DCL FIELD_DCL;
struct FIELD_DCL {
    ID_LIST *id_list;
    TYPE *type;
    FIELD_DCL *next;
    int lineno;
};
FIELD_DCL *makeFieldDcl(ID_LIST *id_list, TYPE *type, int lineno);
FIELD_DCL *makeFieldDclList(FIELD_DCL *f, FIELD_DCL *f1, int lineno);
// j
typedef struct TYPE TYPE;
struct TYPE {
    int lineno;
    char *id;
    TypeKind kind;
    struct {
        TYPE *type;
    } slices_type;
    struct {
        int size;
        TYPE *type;
    } array_type;
    struct {
        FIELD_DCL *field_dcls;
    } struct_type;

    TYPE *types;
};
TYPE *makeTypeId(char *id, int lineno);
TYPE *makeTypeSlices(TYPE *type, int lineno);
TYPE *makeTypeArray(int size, TYPE *type, int lineno);
TYPE *makeTypeStruct(FIELD_DCL *f, int lineno);
TYPE *makeTypeT(TYPE *t1, int lineno);

typedef struct CASE_CLAUSE CASE_CLAUSE;
struct CASE_CLAUSE {
    int lineno;
    EXP *caseExp;
    STMT *caseStmt;
    CASE_CLAUSE *next;
};
TYPE *makeTypeId(char *id, int lineno);
TYPE *makeTypeSlices(TYPE *type, int lineno);
TYPE *makeTypeArray(int size, TYPE *type, int lineno);
TYPE *makeTypeStruct(FIELD_DCL *f, int lineno);
TYPE *makeTypeT(TYPE *t1, int lineno);

typedef struct FOR_CLAUSE FOR_CLAUSE;
struct FOR_CLAUSE {
    int lineno;
    STMT *first;
    STMT *last;
    STMT *doStmt;
};

typedef struct DCL DCL;
struct DCL {
    FUNCDECL *funcDecl;
    VARDECL *valDecl;
};


typedef struct CASE_CLAUSE CASE_CLAUSE;
struct CASE_CLAUSE {
    int lineno;
    EXP *caseExp;
    STMT *caseStmt;
    CASE_CLAUSE *next;
};

// k
typedef struct STMT STMT;
struct STMT {
    int lineno;
    int isSimpleStmt;
    StatementKind kind;
    union {
        STMT *block;
        struct {
            EXP *ifCond;
            STMT *ifSimpleStmt;
            STMT *ifBody;
            STMT *elseStmt;
        } ifStmtVal;
        struct {
            STMT *elseBody;
            STMT *ifStmt;
        } elseStmtVal;
        EXP *printExpList;
        EXP *printlnExpList;
        EXP *returnExp;
        struct {
            STMT *switchSimpleStmt;
            EXP *switchExp;
            CASE_CLAUSE *switchCases;
        } switchStmtVal;
        EXP *expStmtVal;
        EXP *incExp;
        EXP *decExp;
        struct {
            EXP *lhs;
            EXP *rhs;
            AssignKind assignKind;
        } assignStmtVal;
        struct {
            ID_LIST *ids;
            EXP *exps;
        } shortVarDecStmtVal;
        struct {
            EXP *forCond;
            FOR_CLAUSE *forClause;
            STMT *forBody;
        } forStmtVal;
        DCL *decStmtVal;
    } val;
    STMT *next;
};

typedef struct TYPESPEC TYPESPEC;
struct TYPESPEC {
    int lineno;
    char *id;
    TYPE *type;
    TYPESPEC *next;
};

typedef struct TYPESPEC TYPESPEC;
struct TYPESPEC {
    int lineno;
    char *id;
    TYPE *type;
    TYPESPEC *next;
};

// K
typedef struct TYPEDECL TYPEDECL;
struct TYPEDECL {
    int lineno;
    TYPESPEC *typeSpec;
};

typedef struct VARSPEC VARSPEC;
struct VARSPEC {
    int lineno;
    ID_LIST *id_list;
    TYPE *type;
    EXP *exp_list;
    VARSPEC *next;
};
VARSPEC *makeVarSpec(ID_LIST *id_list, TYPE *type, EXP *exp, int lineno);
VARSPEC *makeVarSpecList(VARSPEC *v, VARSPEC *v2, int lineno);
// j
typedef struct VARDECL VARDECL;
struct VARDECL {
    int lineno;
    struct VARSPEC *var_specs;
};
VARDECL *makeVarDecl(VARSPEC *vs, int lineno);

typedef struct PARAMS PARAMS;
struct PARAMS {
    PARAMS *next;
    ID_LIST *id_list;
    TYPE *type;
};

typedef struct RESULT RESULT;
struct RESULT {
    int lineno;
    PARAMS *params;
    TYPE *type;
};

typedef struct SIGNATURE SIGNATURE;
struct SIGNATURE {
    int lineno;
    PARAMS *params;
    RESULT *result;
};

// j
typedef struct FUNCDECL FUNCDECL;
struct FUNCDECL {
    int lineno;
    char *id;
    SIGNATURE *signature;
    STMT *body;
};

FUNCDECL *makeFuncDcl(char *id, SIGNATURE *signature, STMT *body, int lineno);
SIGNATURE *makeSignature(PARAMS *params, RESULT *result, int lineno);
RESULT *makeResultP(PARAMS *params, int lineno);
RESULT *makeResultType(TYPE *type, int lineno);
PARAMS *makeParams(ID_LIST *id_list, TYPE *type, int lineno);
PARAMS *makeParamsList(PARAMS *p, ID_LIST *id_list, TYPE *type, int lineno);

// du
typedef struct TOPDECL TOPDECL;
struct TOPDECL {
    int lineno;
    enum { dcl, funcDeclK } kind;
    union {
        // TYPEDECL *typeDecl;
        // VARDECL *varDecl;
        FUNCDECL *funcDecl;
    } val;
    TOPDECL *next;
};

TOPDECL *makeTopDecl(TYPEDECL *t, TOPDECL *t2, int lineno);

// du
typedef struct PACKAGE PACKAGE;
struct PACKAGE {
    int lineno;
    char *id;
};

PACKAGE *makePackage(char *id, int lineno);

// k
typedef struct IMPORT IMPORT;
struct IMPORT {
    int lineno;
    char *id;
    IMPORT *next;
};

typedef struct PROGRAM PROGRAM;
struct PROGRAM {
    PACKAGE *package;
    IMPORT *imports;
    TOPDECL *top_decl;
};

PROGRAM *makeProgram(PACKAGE *p, IMPORT *i, TOPDECL *decl);

// K
TYPESPEC *makeTypeSpec(char *id, TYPE *type, int lineno);
TYPESPEC *makeTypeSpecList(TYPESPEC *list, TYPESPEC *elem);
TYPEDECL *makeTypeDecl(TYPESPEC *spec, int lineno);

IMPORT *makeImport(char *id, int lineno);
IMPORT *makeImportList(IMPORT *list, IMPORT *elem);

CASE_CLAUSE *makeCaseClause(CASE_CLAUSE *list, EXP *caseExp, STMT *caseStmt, int lineno);
FOR_CLAUSE *makeForClause(STMT *first, STMT *last, STMT *doStmt, int lineno);

STMT *makeContinueStmt(int lineno);
STMT *makeBreakStmt(int lineno);
STMT *makeBlockStmt(STMT *block, int lineno);
STMT *makeIfStmt(STMT *ifSimpleStmt, EXP *ifCond, STMT *ifBody, STMT *elseStmt, int lineno);
STMT *makeElseStmt(STMT *elseBody, STMT *ifStmt, int lineno);
STMT *makePrintStmt(EXP *printExpList, int lineno);
STMT *makePrintlnStmt(EXP *printlnExpList, int lineno);
STMT *makeReturnStmt(EXP *returnExp, int lineno);
STMT *makeSwitchStmt(STMT *switchSimpleStmt, EXP *switchExp, CASE_CLAUSE *switchCases, int lineno);
STMT *makeEmptyStmt(int yylineno);
STMT *makeExpStmt(EXP *expStmtVal, int yylineno);
STMT *makeAssignStmt(EXP *lhs, EXP *rhs, AssignKind assignKind, int lineno);
STMT *makeIncStmt(EXP *incExp, int lineno);
STMT *makeDecStmt(EXP *decExp, int lineno);
STMT *makeShortVarDecStmt(ID_LIST *ids, EXP *exps, int lineno);
STMT *makeForStmt(EXP *forCond, FOR_CLAUSE *forClause, STMT *forBody, int lineno);

STMT *makeContinueStmt(int lineno);
STMT *makeBreakStmt(int lineno);
STMT *makeBlockStmt(STMT *block, int lineno);
STMT *makeIfStmt(STMT *ifSimpleStmt, EXP *ifCond, STMT *ifBody, STMT *elseStmt, int lineno);
STMT *makeElseStmt(STMT *elseBody, STMT *ifStmt, int lineno);
STMT *makePrintStmt(EXP *printExpList, int lineno);
STMT *makePrintlnStmt(EXP *printlnExpList, int lineno);
STMT *makeReturnStmt(EXP *returnExp, int lineno);
STMT *makeSwitchStmt(STMT *switchSimpleStmt, EXP *switchExp, CASE_CLAUSE *switchCases, int lineno);
STMT *makeEmptyStmt(int yylineno);
STMT *makeExpStmt(EXP *expStmtVal, int yylineno);
STMT *makeAssignStmt(EXP *lhs, EXP *rhs, AssignKind assignKind, int lineno);
STMT *makeIncStmt(EXP *incExp, int lineno);
STMT *makeDecStmt(EXP *decExp, int lineno);
STMT *makeShortVarDecStmt(ID_LIST *ids, EXP *exps, int lineno);

#endif
