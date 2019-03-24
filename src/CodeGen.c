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

// void codeGenExp(EXP *e) {
//     if (e == NULL) {
//         return;
//     }
//     switch (e->kind) {
//     case k_expressionKindIntLiteral:
//         printf("%d", e->val.intLiteral);
//         break;
//     case k_expressionKindStringLiteral:
//         printf("%s", e->val.stringLiteral);
//         break;
//     case k_expressionKindFloatLiteral:
//         printf("%f", e->val.floatLiteral);
//         break;
//     case k_expressionKindBooleanLiteral:
//         switch (e->val.booleanLiteral) {
//         case 0:
//             printf("false");
//             break;
//         case 1:
//             printf("true");
//         }
//         break;
//     case k_expressionKindPlusExp:
//         if (e->val.binary.rhs->type->t_type == t_string &&
//             e->val.binary.rhs->type->t_type == t_string) {
//             printf("str_cat(");
//             codeGenExp(e->val.binary.lhs);
//             printf(",");
//             codeGenExp(e->val.binary.rhs);
//             printf(")");
//         } else {
//             printf("(");
//             codeGenExp(e->val.binary.lhs);
//             printf(" + ");
//             codeGenExp(e->val.binary.rhs);
//             printf(")");
//         }

//         break;
//     case k_expressionKindMinusExp:
//         printf("(");
//         codeGenExp(e->val.binary.lhs);
//         printf(" - ");
//         codeGenExp(e->val.binary.rhs);
//         printf(")");
//         break;
//     case k_expressionKindTimesExp:
//         printf("(");
//         codeGenExp(e->val.binary.lhs);
//         printf(" * ");
//         codeGenExp(e->val.binary.rhs);
//         printf(")");
//         break;
//     case k_expressionKindDivExp:
//         printf("(");
//         codeGenExp(e->val.binary.lhs);
//         printf(" / ");
//         codeGenExp(e->val.binary.rhs);
//         printf(")");
//         break;
//     case k_expressionKindEqExp:
//         printf("(");
//         codeGenExp(e->val.binary.lhs);
//         printf(" == ");
//         codeGenExp(e->val.binary.rhs);
//         printf(")");
//         break;
//     case k_expressionKindNeqExp:
//         printf("(");
//         codeGenExp(e->val.binary.lhs);
//         printf(" != ");
//         codeGenExp(e->val.binary.rhs);
//         printf(")");
//         break;
//     case k_expressionKindGeqExp:
//         printf("(");
//         codeGenExp(e->val.binary.lhs);
//         printf(" >= ");
//         codeGenExp(e->val.binary.rhs);
//         printf(")");
//         break;
//     case k_expressionKindLeqExp:
//         printf("(");
//         codeGenExp(e->val.binary.lhs);
//         printf(" <= ");
//         codeGenExp(e->val.binary.rhs);
//         printf(")");
//         break;
//     case k_expressionKindGreaterExp:
//         printf("(");
//         codeGenExp(e->val.binary.lhs);
//         printf(" > ");
//         codeGenExp(e->val.binary.rhs);
//         printf(")");
//         break;
//     case k_expressionKindLessExp:
//         printf("(");
//         codeGenExp(e->val.binary.lhs);
//         printf(" < ");
//         codeGenExp(e->val.binary.rhs);
//         printf(")");
//         break;
//     case k_expressionKindAndExp:
//         printf("(");
//         codeGenExp(e->val.binary.lhs);
//         printf(" && ");
//         codeGenExp(e->val.binary.rhs);
//         printf(")");
//         break;
//     case k_expressionKindOrExp:
//         printf("(");
//         codeGenExp(e->val.binary.lhs);
//         printf(" || ");
//         codeGenExp(e->val.binary.rhs);
//         printf(")");
//         break;
//     case k_expressionKindBangExp:
//         printf("(");
//         printf("!");
//         codeGenExp(e->exp);
//         printf(")");
//         break;
//     case k_expressionKindNegExp:
//         printf("(");
//         printf("-");
//         codeGenExp(e->exp);
//         printf(")");
//         break;
//     case k_expressionKindIDExp:
//         printf("%s", e->val.id_string);
//         break;
//     case k_expressionKindParen:
//         codeGenExp(e->exp);
//         break;
//     }
// }

// void codeGenStatement(STATEMENT *r, int indentation) {
//     if (r == NULL) {
//         return;
//     }

//     switch (r->kind) {
//     case k_stmt_read:
//         indent(indentation);
//         switch (r->val.read.identifier->type->t_type) {
//         case t_boolean:
//             printf("%s = scan_boolean();\n",
//                    r->val.read.identifier->val.id_string);
//             break;
//         case t_int:
//             printf("scanf(\"%%d\", &%s);\n",
//                    r->val.read.identifier->val.id_string);
//             break;
//         case t_float64:
//             printf("scanf(\"%%f\", &%s);\n",
//                    r->val.read.identifier->val.id_string);
//             break;
//         case t_string:
//             printf("%s = malloc(sizeof(char) * 1024);\n", r->val.read.identifier->val.id_string);
//             indent(indentation);
//             printf("scanf(\"%%s\", %s);\n",
//                    r->val.read.identifier->val.id_string);
//             break;
//         }
//         break;
//     case k_stmt_print:
//         indent(indentation);
//         switch (r->val.print.exp->type->t_type) {
//         case t_boolean:
//             printf("if(");
//             codeGenExp(r->val.print.exp);
//             printf("){\n");
//             indent(indentation);
//             indent(indentation);
//             printf("printf(\"true\");\n");
//             indent(indentation);
//             printf("} else {\n");
//             indent(indentation);
//             indent(indentation);
//             printf("printf(\"false\");\n");
//             indent(indentation);
//             printf("}\n");
//             break;
//         case t_int:
//             printf("printf(\"%%d\", ");
//             codeGenExp(r->val.print.exp);
//             printf(");\n");
//             break;
//         case t_float64:
//             printf("printf(\"%%f\", ");
//             codeGenExp(r->val.print.exp);
//             printf(");\n");
//             break;
//         case t_string:
//             printf("printf(\"%%s\", ");
//             codeGenExp(r->val.print.exp);
//             printf(");\n");
//             break;
//         }
//         break;
//     case k_stmt_assign:
//         indent(indentation);
//         printf("%s = ", r->val.assignment.identifier->val.id_string);
//         codeGenExp(r->val.assignment.exp);
//         printf(";\n");
//         break;
//     case k_stmt_loop:
//         indent(indentation);
//         printf("while (");
//         codeGenExp(r->val.loop.condition);
//         printf(")\n");
//         indent(indentation);
//         printf("{\n");
//         codeGenStatement(r->val.loop.body, indentation + 1);
//         indent(indentation);
//         printf("}\n");
//         break;
//     case k_stmt_if:
//         indent(indentation);
//         printf("if (");
//         codeGenExp(r->val.if_stmt.condition);
//         printf(")\n");
//         indent(indentation);
//         printf("{\n");
//         codeGenStatement(r->val.if_stmt.stmts, indentation + 1);
//         indent(indentation);
//         printf("}\n");
//         codeGenStatement(r->val.if_stmt.elseifstmts, indentation);
//         codeGenStatement(r->val.if_stmt.elsestmt, indentation);
//         break;
//     case k_stmt_elseif_list:
//         codeGenStatement(r->val.elseif_list.current, indentation);
//         codeGenStatement(r->val.elseif_list.next, indentation);
//         break;
//     case k_stmt_elseif:
//         printf("else if (");
//         codeGenExp(r->val.elseif.exp);
//         printf(")\n");
//         indent(indentation);
//         printf("{\n");
//         codeGenStatement(r->val.elseif.stmts, indentation + 1);
//         printf("}\n");
//         break;
//     case k_stmt_else:
//         indent(indentation);
//         printf("else\n");
//         indent(indentation);
//         printf("{\n");
//         codeGenStatement(r->val.else_stmt.stmts, indentation + 1);
//         indent(indentation);
//         printf("}\n");
//         break;
//     case k_stmt_dcl:
//         indent(indentation);
//         if (r->val.dcl.exp == NULL) {
//             if (r->val.dcl.type->t_type == t_string) {
//                 printf("%s%s = malloc(sizeof(char) * 1024);\n", "char *",
//                        r->val.dcl.identifier->val.id_string);
//             } else if (r->val.dcl.type->t_type == t_boolean) {
//                 printf("%s %s = false;\n", "bool",
//                        r->val.dcl.identifier->val.id_string);
//             } else if (r->val.dcl.type->t_type == t_float64) {
//                 printf("%s %s = 0.0;\n", r->val.dcl.type->string_val,
//                        r->val.dcl.identifier->val.id_string);
//             } else {
//                 printf("%s %s = 0;\n", r->val.dcl.type->string_val,
//                        r->val.dcl.identifier->val.id_string);
//             }

//         } else {
//             if (r->val.dcl.type->t_type == t_string) {
//                 printf("%s%s = ", "char *",
//                        r->val.dcl.identifier->val.id_string);
//             } else if (r->val.dcl.type->t_type == t_boolean) {
//                 printf("%s %s = ", "bool",
//                        r->val.dcl.identifier->val.id_string);
//             } else {
//                 printf("%s %s = ", r->val.dcl.type->string_val,
//                        r->val.dcl.identifier->val.id_string);
//             }
//             codeGenExp(r->val.dcl.exp);
//             printf(";\n");
//         }
//         break;
//     case k_stmt_list:
//         codeGenStatement(r->current, indentation);
//         codeGenStatement(r->next, indentation);
//         break;
//     }
// }

// void codeGenHeader() {
//     printf("#include \"stdio.h\"\n#include \"string.h\"\n#include "
//            "<stdlib.h>\n#include <stdbool.h>\n\n"
//            "char *str_cat(char *s1, char *s2) {\n"
//            "\tchar *t = malloc(sizeof(char) * (strlen(s1) + strlen(s2)));\n"
//            "\tchar *a = t;\n"
//            "\twhile (*s1 != '\\0') {\n"
//            "\t\t*t++ = *s1++;\n"
//            "\t}\n"
//            "\twhile (*s2 != '\\0') {\n"
//            "\t\t*t++ = *s2++;\n"
//            "\t}\n"
//            "\treturn a;\n"
//            "}\n"
//            "bool scan_boolean() {\n"
//            "\tchar *buffer = malloc(sizeof(char) * 1024);\n"
//            "\tscanf(\"%%s\", buffer);\n"
//            "\tif (strcmp(buffer, \"true\") == 0) {\n"
//            "\t\treturn true;\n"
//            "\t} else if (strcmp(buffer, \"false\") == 0) {\n"
//            "\t\treturn false;\n"
//            "\t} else {\n"
//            "\t\tfprintf(stderr, \"Error: read boolean can only accept true or "
//            "false\");\n"
//            "\t\texit(1);\n"
//            "\t}\n"
//            "\treturn false;\n"
//            "}\n"
//            "int main(int argc, char "
//            "*argv[])\n{\n");
// }

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

void codeGenProgram(PROGRAM *root, char *file_name) {

    typeCheckProgram(root);

    // append .c to file name
    str_replace(file_name, ".min", ".py");
    remove(file_name);

    // // redirect stdout to new file
    int out = open(file_name, O_RDWR | O_APPEND | O_CREAT, 0600);
    if (-1 == out) {
        perror("Error: ");
        return;
    }
    int save_out = dup(fileno(stdout));
    if (-1 == dup2(out, fileno(stdout))) {
        perror("Error: cannot redirect stdout");
        return;
    }

    //
    // codeGenHeader();
    // codeGenStatement(root->top_decl, 1);
    printf("}\n");

    // put stdout back
    fflush(stdout);
    close(out);
    dup2(save_out, fileno(stdout));
    close(save_out);
}
