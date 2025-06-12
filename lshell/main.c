
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#include "shell/shell.h"
#include "parser/build/parser.h"
#include "common.h"
#include "parser/build/lexer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>


struct ASTNode *root = NULL;

int main() {
    setup_path();
    load_history();

    while (1) {
        char *input = readline(get_prompt());

        if (!input) {
            printf("\nexit\n");
            break;
        }

        if (*input == '\0') {
            free(input);
            continue;
        }

        add_history(input);
        save_history_line(input);

        // Parse the input into an AST
        extern ASTNode *root;
        YY_BUFFER_STATE buf = yy_scan_string(input);
        yyparse();
        yy_delete_buffer(buf);
        free(input);

        if (root) {

            int last_exit_status = run_ast(root);
            printf("Exit status: %d\n", last_exit_status);
            free_ast(root);
            root = NULL;
        }
           }

    return 0;
}

