#include "CodeGen.h"
#include "SymbolTable.h"
#include "TypeCheck.h"
#include "pretty.h"
#include "stdio.h"
#include "string.h"
#include "tree.h"
#include <stdlib.h>
#include "weed.h"

PROGRAM *root;

int yyparse();
int yylex();
int g_tokens = 0;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "need argument: "
                        "scan|tokens|parse|pretty|symbol|typecheck|codegen \n");
    } else {
        if (strcmp("scan", argv[1]) == 0) {
            while (yylex())
                ;
            printf("OK\n");
        } else if (strcmp("tokens", argv[1]) == 0) {
            g_tokens = 1;
            while (yylex()) {
            };
        } else if (strcmp("parse", argv[1]) == 0) {
            int r = yyparse();
            weedPROGRAM(root);
            if (r == 0) {
                printf("OK\n");
            } else {
                exit(1);
            }
        } else if (strcmp("pretty", argv[1]) == 0) {
            int r = yyparse();
            if (r == 0) {
                if (root != NULL) {
                    prettyPROGRAM(root);
                } else {
                    printf("root null\n");
                    exit(1);
                }
            } else {
                printf("parse failed\n");
                exit(1);
            }
        } else if (strcmp("symbol", argv[1]) == 0) {
            int r = yyparse();
            if (r == 0) {
                if (root != NULL) {
                    // makeSymbolTable(root, 1);
                } else {
                    printf("root null\n");
                    exit(1);
                }
            } else {
                printf("parse failed\n");
                exit(1);
            }
        } else if (strcmp("typecheck", argv[1]) == 0) {
            int r = yyparse();
            if (r == 0) {
                if (root != NULL) {
                    // typeCheckProgram(root);
                    printf("OK\n");
                } else {
                    printf("root null\n");
                    exit(1);
                }
            } else {
                printf("parse failed\n");
                exit(1);
            }
        } else if (strcmp("codegen", argv[1]) == 0) {
            freopen(argv[2], "r", stdin);
            int r = yyparse();
            if (r == 0) {
                if (root != NULL) {
                    // codeGenProgram(root, argv[2]);
                    printf("OK\n");
                } else {
                    printf("root null\n");
                    exit(1);
                }
            } else {
                printf("parse failed\n");
                exit(1);
            }
        } else {
            fprintf(stderr,
                    "need argument: "
                    "scan|tokens|parse|pretty|symbol|typecheck|codegen \n");
            exit(1);
        }
    }
    return 0;
}