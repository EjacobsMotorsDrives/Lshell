

%{
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "shell/shell.h"

int yylex(void);
void yyerror(const char *s);
%}
%union {
    char *str;
    struct ASTNode *node;
};

%token <str> WORD
%token AND_IF OR_IF SEMI PIPE REDIRECT_IN REDIRECT_OUT

%type <node> input command command_list redirection

%left OR_IF
%left AND_IF
%left SEMI
%left PIPE

%%

input:
    /* empty */
    | command_list            { run_ast($1); free_ast($1); }
    ;

command_list:
      command_list SEMI command      { $$ = make_sequence_node($1, $3); }
    | command_list AND_IF command    { $$ = make_and_node($1, $3); }
    | command_list OR_IF command     { $$ = make_or_node($1, $3); }
    | command                        { $$ = $1; }
    ;

command:
      WORD {
          char **argv = malloc(2 * sizeof(char *));
          argv[0] = strdup($1);
          argv[1] = NULL;
          $$ = make_command_node(argv);
      }
    | command WORD {
          $$ = append_arg($1, $2);
      }
    | command redirection {
          $$ = attach_redirection($1, $2);
      }
    ;

redirection:
      REDIRECT_IN WORD                { $$ = make_redirection_node("<", $2); }
    | REDIRECT_OUT WORD               { $$ = make_redirection_node(">", $2); }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}

