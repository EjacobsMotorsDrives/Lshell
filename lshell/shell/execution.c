
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

int execute_ast(const ASTNode *node) {
    if (!node) return 0;

    switch (node->type) {
        case AST_COMMAND: {
            if (!node->argv || !node->argv[0])
                return 0;

            expand_variables(node->argv);
            expand_alias(node->argv);

            int builtin_status;
            if (handle_builtin_command(node->argv, &builtin_status)) {
                return builtin_status;
            }

        // DEBUG: Print the command and its arguments
        printf("[debug] Running command: %s\n", node->argv[0]);
        for (int i = 1; node->argv[i]; ++i)
            printf("[debug] arg[%d] = %s\n", i, node->argv[i]);

            pid_t pid = fork();
            if (pid == 0) {
                execvp(node->argv[0], node->argv);
                perror("execvp");
                exit(127);
            } else if (pid > 0) {
                int status;
                waitpid(pid, &status, 0);
                return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
            } else {
                perror("fork");
                return 1;
            }
        }

        case AST_SEQUENCE:
            execute_ast(node->left);
            return execute_ast(node->right);

        case AST_AND: {
            int status = execute_ast(node->left);
            return (status == 0) ? execute_ast(node->right) : status;
        }

        case AST_OR: {
            int status = execute_ast(node->left);
            return (status != 0) ? execute_ast(node->right) : status;
        }

        default:
            fprintf(stderr, "Unknown AST node type: %d\n", node->type);
            return 1;
    }
}

