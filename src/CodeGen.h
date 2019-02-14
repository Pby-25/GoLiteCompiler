#ifndef _CodeGenH
#define _CodeGenH
#include "TypeCheck.h"

void codeGenProgram(PROGRAM *root, char *file_name);
void codeGenStatement(STATEMENT *r, int indentation);

#endif