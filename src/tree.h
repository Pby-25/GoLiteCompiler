#ifndef _treeH
#define _treeH
#include <stdbool.h>

typedef enum {
    inLoop,
    inSwitch,
    other
} State;

typedef enum {
    caseK,
    defaultK
} SwitchCaseK;

typedef enum {
    typeDcl,
    varDcl
} DclKind;

typedef enum {
    btk_int,
    btk_float64,
    btk_rune,
    btk_bool,
    btk_string,
} BaseTypeKind;

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
    k_type_type,
    k_infer,
    k_funcsig
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
    arrayExpr,
    sliceExpr,
    selectorExpr,
    funcExpr,
    castExpr,
    // expList
} ExpKind;

typedef struct FIELD_DCL FIELD_DCL;
typedef struct TYPE TYPE;
typedef struct ID_LIST ID_LIST;
typedef struct EXP EXP;
typedef struct DCL DCL;
typedef struct STMT STMT;
typedef struct TYPESPEC TYPESPEC;
typedef struct TYPEDECL TYPEDECL;
typedef struct VARSPEC VARSPEC;
typedef struct VARDECL VARDECL;
typedef struct PARAMS PARAMS;
typedef struct RESULT RESULT;
typedef struct SIGNATURE SIGNATURE;
typedef struct FUNCDECL FUNCDECL;
typedef struct TOPDECL TOPDECL;
typedef struct PACKAGE PACKAGE;
typedef struct IMPORT IMPORT;
typedef struct PROGRAM PROGRAM;
typedef struct PARAM_TYPE PARAM_TYPE;

struct FIELD_DCL {
    ID_LIST *id_list;
    TYPE *type;
    FIELD_DCL *next;
    int lineno;
};
FIELD_DCL *makeFieldDcl(ID_LIST *id_list, TYPE *type, int lineno);
FIELD_DCL *makeFieldDclList(FIELD_DCL *f, FIELD_DCL *f1, int lineno);
// j
struct PARAM_TYPE {
    TYPE *type;
    PARAM_TYPE *next;
};

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
    struct{
        bool isBaseType;
        BaseTypeKind baseTypeKind;
    } id_type;
    TYPE *types;
    PARAM_TYPE *params;
    TYPE *result;
};
TYPE *makeTypeId(char *id, int lineno);
TYPE *makeTypeSlices(TYPE *type, int lineno);
TYPE *makeTypeArray(int size, TYPE *type, int lineno);
TYPE *makeTypeStruct(FIELD_DCL *f, int lineno);
TYPE *makeTypeT(TYPE *t1, int lineno);

// j

struct ID_LIST {
    int lineno;
    char *id;
    TYPE *type;
    ID_LIST *next;
};

ID_LIST *makeIdList(ID_LIST *l, char *id, int lineno);

// du

struct EXP {
    int lineno;
    ExpKind kind;
    union {
        char *id;
        char *stringVal;
        char *runeVal;
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
            EXP *index;
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
EXP *makeStringItpExp(char *stringval, int lineno);
EXP *makeStringRawExp(char *stringval, int lineno);
EXP *makeRuneExp(char *runeval, int lineno);
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



struct DCL {
    int lineno;
    DclKind kind;
    union {
        TYPEDECL *typeDecl;
        VARDECL *varDecl;
    } val;
};

typedef struct FOR_CLAUSE FOR_CLAUSE;
typedef struct CASE_CLAUSE CASE_CLAUSE;


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
            ExpKind returnKind;
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


struct FOR_CLAUSE {
    int lineno;
    STMT *first;
    EXP *condtion;
    STMT *post;
};

struct CASE_CLAUSE {
    int lineno;
    SwitchCaseK kind;
    EXP *caseExp;
    STMT *caseStmt;
    CASE_CLAUSE *next;
};


struct TYPESPEC {
    int lineno;
    char *id;
    TYPE *type;
    TYPESPEC *next;
};

// K

struct TYPEDECL {
    int lineno;
    TYPESPEC *typeSpec;
};


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

struct VARDECL {
    int lineno;
    struct VARSPEC *var_specs;
};
VARDECL *makeVarDecl(VARSPEC *vs, int lineno);


struct PARAMS {
    int lineno;
    PARAMS *next;
    ID_LIST *id_list;
    TYPE *type;
};


struct RESULT {
    int lineno;
    PARAMS *params;
    TYPE *type;
};


struct SIGNATURE {
    int lineno;
    PARAMS *params;
    RESULT *result;
};

// j

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

struct TOPDECL {
    int lineno;
    enum { dclK, funcDeclK } kind;
    union {
        DCL *dcl;
        FUNCDECL *funcDecl;
    } val;
    TOPDECL *next;
};

TOPDECL *makeTopDecl(TYPEDECL *t, TOPDECL *t2, int lineno);

// du

struct PACKAGE {
    int lineno;
    char *id;
};

PACKAGE *makePackage(char *id, int lineno);

// k

struct IMPORT {
    int lineno;
    char *id;
    IMPORT *next;
};


struct PROGRAM {
    int lineno;
    PACKAGE *package;
    IMPORT *imports;
    TOPDECL *top_decl;
};

PROGRAM *makeProgram(PACKAGE *p, IMPORT *i, TOPDECL *decl, int lineno);

// K
TYPESPEC *makeTypeSpec(char *id, TYPE *type, int lineno);
TYPESPEC *makeTypeSpecList(TYPESPEC *list, TYPESPEC *elem);
TYPEDECL *makeTypeDecl(TYPESPEC *spec, int lineno);

IMPORT *makeImport(char *id, int lineno);
IMPORT *makeImportList(IMPORT *list, IMPORT *elem);

CASE_CLAUSE *makeCaseClause(int kind, CASE_CLAUSE *list, EXP *caseExp, STMT *caseStmt,int lineno);

FOR_CLAUSE *makeForClause(STMT *first, EXP *last, STMT *doStmt, int lineno);

DCL *makeVarDcl(VARDECL *dcl, int lineno);
DCL *makeTypeDcl(TYPEDECL *dcl, int lineno);

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
STMT *makeDclStmt(DCL *dcl, int lineno);
STMT *makeStmtList(STMT *list, STMT *current, int lineno);

TOPDECL *makeTopDeclFromDcl(DCL *d);
TOPDECL *makeTopDeclFromFuncDcl(FUNCDECL *d);
TOPDECL *makeTopVarDeclList(TOPDECL *l, TOPDECL *next, int lineno);

#endif
