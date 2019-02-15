#ifndef _treeH
#define _treeH
typedef struct TYPE {
    enum { t_int, t_float64, t_boolean, t_string } t_type;
    char *string_val;
} TYPE;

typedef enum {
    k_expressionKindIntLiteral,
    k_expressionKindStringLiteral,
    k_expressionKindFloatLiteral,
    k_expressionKindBooleanLiteral,
    k_expressionKindPlusExp,
    k_expressionKindMinusExp,
    k_expressionKindTimesExp,
    k_expressionKindDivExp,
    k_expressionKindEqExp,
    k_expressionKindNeqExp,
    k_expressionKindGeqExp,
    k_expressionKindLeqExp,
    k_expressionKindGreaterExp,
    k_expressionKindLessExp,
    k_expressionKindAndExp,
    k_expressionKindOrExp,
    k_expressionKindBangExp,
    k_expressionKindNegExp,
    k_expressionKindIDExp,
    k_expressionKindParen,
} ExpressionKind;

typedef struct EXP EXP;
struct EXP {
    int lineno;
    ExpressionKind kind;
    EXP *exp;
    union {
        char *id_string;
        int intLiteral;
        char *stringLiteral;
        float floatLiteral;
        int booleanLiteral;
        struct {
            EXP *lhs;
            EXP *rhs;
        } binary;
    } val;
    TYPE *type;
    int isIdentifier;
};

EXP *makeEXP_intLiteral(int intLiteral, int lineno);
EXP *makeEXP_StringLiteral(char *stringLiteral, int lineno);
EXP *makeEXP_FloatLiteral(float floatLiteral, int lineno);
EXP *makeEXP_BooleanLiteral(int booleanLiteral, int lineno);
EXP *makeEXP_plus(EXP *lhs, EXP *rhs, int lineno);
EXP *makeEXP_minus(EXP *lhs, EXP *rhs, int lineno);
EXP *makeEXP_times(EXP *lhs, EXP *rhs, int lineno);
EXP *makeEXP_div(EXP *lhs, EXP *rhs, int lineno);
EXP *makeEXP_eq(EXP *lhs, EXP *rhs, int lineno);
EXP *makeEXP_neq(EXP *lhs, EXP *rhs, int lineno);
EXP *makeEXP_geq(EXP *lhs, EXP *rhs, int lineno);
EXP *makeEXP_leq(EXP *lhs, EXP *rhs, int lineno);
EXP *makeEXP_greater(EXP *lhs, EXP *rhs, int lineno);
EXP *makeEXP_less(EXP *lhs, EXP *rhs, int lineno);
EXP *makeEXP_and(EXP *lhs, EXP *rhs, int lineno);
EXP *makeEXP_or(EXP *lhs, EXP *rhs, int lineno);
EXP *makeEXP_Bang(EXP *exp, int lineno);
EXP *makeEXP_Neg(EXP *exp, int lineno);
EXP *makeEXP_ID(char *identifier, int lineno);
EXP *makeEXP_Paren(EXP *exp, int lineno);

typedef enum {
    k_stmt_read,
    k_stmt_print,
    k_stmt_assign,
    k_stmt_if,
    k_stmt_dcl,
    k_stmt_list,
    k_stmt_elseif_list,
    k_stmt_elseif,
    k_stmt_else,
    k_stmt_loop
} StatementKind;

typedef struct STATEMENT STATEMENT;
struct STATEMENT {
    StatementKind kind;
    int lineno;
    union {
        struct {
            EXP *identifier;
            EXP *exp;
        } assignment;
        struct {
            EXP *condition;
            STATEMENT *body;
        } loop;
        struct {
            EXP *identifier;
            TYPE *type;
            EXP *exp;
        } dcl;
        struct {
            EXP *identifier;
        } read;
        struct {
            EXP *exp;
        } print;
        struct {
            EXP *condition;
            STATEMENT *stmts;
            STATEMENT *elseifstmts;
            STATEMENT *elsestmt;
        } if_stmt;
        struct {
            STATEMENT *current;
            STATEMENT *next;
        } elseif_list;
        struct {
            EXP *exp;
            STATEMENT *stmts;
        } elseif;
        struct {
            STATEMENT *stmts;
        } else_stmt;
        struct {
            STATEMENT *dcl;
            STATEMENT *stmts;
        } dcl_stmts;
    } val;
    STATEMENT *current;
    STATEMENT *next;
};

STATEMENT *makeStatememnt_read(EXP *identifier, int lineno);
STATEMENT *makeStatememnt_print(EXP *exp, int lineno);
STATEMENT *makeStatement_assign(EXP *identifier, EXP *exp, int lineno);
STATEMENT *makeStatememnt_while(EXP *exp, STATEMENT *stmts, int lineno);
STATEMENT *makeStatememnt_if(EXP *condition, STATEMENT *stmts,
                             STATEMENT *elseifstmts, STATEMENT *elsestmt,
                             int lineno);
STATEMENT *makeStatememnt_list(STATEMENT *s1, STATEMENT *s2, int lineno);
STATEMENT *makeStatememnt_elseifstmt_list(STATEMENT *s1, STATEMENT *s2,
                                          int lineno);
STATEMENT *makeStatememnt_else(STATEMENT *stmts, int lineno);
STATEMENT *makeStatememnt_elseifstmt(EXP *exp, STATEMENT *stmts, int lineno);
STATEMENT *makeStatememnt_dcl(EXP *identifier, TYPE *type, EXP *exp,
                              int lineno);
STATEMENT *makeDcl_Stmt_list(STATEMENT *dcl, STATEMENT *stmts, int lineno);

typedef struct PROGRAM PROGRAM;
struct PROGRAM {
    STATEMENT *statements;
};

PROGRAM *makeProgram(STATEMENT *stmts);

TYPE *stingToTYPE(char *s);

#endif