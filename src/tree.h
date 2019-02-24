#ifndef _treeH
#define _treeH



// j
typedef struct ID_LIST ID_LIST;
struct ID_LIST {
    int lineno;
    // a lot of shit
    // next
};

// du
typedef struct EXP EXP;
struct EXP {
    int lineno;

    // next
};

// j
typedef struct TYPE TYPE;
struct TYPE {
    int lineno;
    // type_list{
// slices_type
// array_type
// struct_type{
// field_dcls
// }
    // }
};

//k
typedef struct STMT STMT;
struct STMT {
    int lineno;
    // a lot of shit
    // next
};


// K 
typedef struct TYPEDECL TYPEDECL;
struct TYPEDECL {
    int lineno;
    // var_spec {
// next
    // }
    // next
};


//j
typedef struct VARDECL VARDECL;
struct VARDECL {
    int lineno;
    //short_var_dec
    
};
// j
typedef struct FUNCDECL FUNCDECL;
struct FUNCDECL {
    int lineno;
    // signature { 
            // reuslt{}
            // params{}

    // }

};

// du
typedef struct TOPDECL TOPDECL;
struct TOPDECL {
    int lineno;
    
    TOPDECL *next;
};


// du
typedef struct PACKAGE PACKAGE;
struct PACKAGE {
    int lineno;
    char *id;
};

// k
typedef struct IMPORT IMPORT;
struct IMPORT{
    int lineno;
    char *importName;
};




typedef struct PROGRAM PROGRAM;
struct PROGRAM {
    PACKAGE *statements;
    IMPORT *imports;
    TOPDECL *top_decl;
};

PROGRAM *makeProgram(PACKAGE *p, IMPORT *i,  TOPDECL *decl)



#endif