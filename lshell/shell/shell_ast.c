
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shell.h"
#include "../common.h"

ASTNode *make_command_node(char **argv) {
    ASTNode *node = malloc(sizeof(ASTNode));
    if (!node) return NULL;

    node->type = AST_COMMAND;
    node->argv = argv;
    node->filename = NULL;
    node->left = node->right = NULL;
    return node;
}

ASTNode *make_op_node(ASTNodeType type, ASTNode *left, ASTNode *right) {
    ASTNode *node = malloc(sizeof(ASTNode));
    if (!node) return NULL;

    node->type = type;
    node->left = left;
    node->right = right;
    node->argv = NULL;
    node->filename = NULL;
    return node;
}

ASTNode *make_redirect_node(ASTNodeType type, ASTNode *command, const char *filename) {
    ASTNode *node = malloc(sizeof(ASTNode));
    if (!node) return NULL;

    node->type = type;
    node->left = command;
    node->right = NULL;
    node->argv = NULL;
    node->filename = strdup(filename);
    return node;
}

ASTNode *make_redirection_node(const char *op, const char *filename) {
    ASTNodeType type;
    if (strcmp(op, ">") == 0)
        type = AST_REDIR_OUT;
    else if (strcmp(op, "<") == 0)
        type = AST_REDIR_IN;
    else if (strcmp(op, ">>") == 0)
        type = AST_APPEND;
    else
        return NULL;

    return make_redirect_node(type, NULL, filename);
}

ASTNode *append_arg(ASTNode *cmd, const char *arg) {
    if (!cmd || cmd->type != AST_COMMAND) return NULL;

    int count = 0;
    while (cmd->argv && cmd->argv[count]) count++;

    char **new_argv = realloc(cmd->argv, sizeof(char *) * (count + 2));
    if (!new_argv) return NULL;

    new_argv[count] = strdup(arg);
    new_argv[count + 1] = NULL;
    cmd->argv = new_argv;

    return cmd;
}

ASTNode *attach_redirection(ASTNode *cmd, ASTNode *redir) {
    if (!cmd) return redir;
    if (!redir) return cmd;
    redir->left = cmd;
    return redir;
}

ASTNode *make_sequence_node(ASTNode *left, ASTNode *right) {
    return make_op_node(AST_SEQUENCE, left, right);
}

ASTNode *make_and_node(ASTNode *left, ASTNode *right) {
    return make_op_node(AST_AND, left, right);
}

ASTNode *make_or_node(ASTNode *left, ASTNode *right) {
    return make_op_node(AST_OR, left, right);
}

void print_ast(const ASTNode *node) {
    if (!node) return;
    switch (node->type) {
        case AST_COMMAND:
            for (int i = 0; node->argv && node->argv[i]; i++)
                printf("%s ", node->argv[i]);
            break;
        case AST_SEQUENCE:
            print_ast(node->left);
            printf(" ; ");
            print_ast(node->right);
            break;
        case AST_AND:
            print_ast(node->left);
            printf(" && ");
            print_ast(node->right);
            break;
        case AST_OR:
            print_ast(node->left);
            printf(" || ");
            print_ast(node->right);
            break;
        case AST_REDIR_OUT:
        case AST_REDIR_IN:
        case AST_APPEND:
            print_ast(node->left);
            printf(" %s %s",
                node->type == AST_REDIR_OUT ? ">" :
                node->type == AST_REDIR_IN ? "<" : ">>",
                node->filename);
            break;
    }
}

void free_ast(ASTNode *node) {
    if (!node) return;
    if (node->argv) {
        for (int i = 0; node->argv[i]; i++)
            free(node->argv[i]);
        free(node->argv);
    }
    if (node->filename)
        free(node->filename);

    free_ast(node->left);
    free_ast(node->right);
    free(node);
}


int run_ast(ASTNode *node) {
    if (!node) return 0;

    // Optionally print the AST for debugging
    // print_ast(node);
    // printf("\n");

    int status = execute_ast(node);
    return status;
}

