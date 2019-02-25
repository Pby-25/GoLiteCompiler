#ifndef _SymbolTableH
#define _SymbolTableH
#define HashSize 317

#include "tree.h"

// typedef struct SYMBOL {
//     char *name;
//     TYPE *type;
//     struct SYMBOL *next;

// } SYMBOL;

// typedef struct SymbolTable {
//     SYMBOL *table[HashSize];
//     struct SymbolTable *parent;
// } SymbolTable;

// SYMBOL *getSymbol(SymbolTable *t, char *name);
// SYMBOL *putSymbol(SymbolTable *t, EXP *id_exp, TYPE *type);
// SymbolTable *scopeSymbolTable(SymbolTable *s);
// SymbolTable *initSymbolTable();
// void makeSymbolTable(PROGRAM *prog, int print);
// void makeSymbolStatement(STATEMENT *s, SymbolTable *st, int indentation, int print);

// void indent(int indentation);

#endif