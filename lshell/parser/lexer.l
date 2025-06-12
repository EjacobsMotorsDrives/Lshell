
/* lexer.l - Flex lexer for shell */
%{
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>      // for isatty(), stdin, etc.
#include <stdlib.h>     // for malloc, free, getenv, exit
#include <string.h>     // for strdup
#include <unistd.h>     // for fileno, isatty
#include "parser.h"
#include "common.h"
%}

%option noyywrap nounput noinput header-file="lexer.h"

%%

"&&"              return AND_IF;
"||"              return OR_IF;
";"               return ';';
">"               return REDIRECT_OUT;
"<"               return REDIRECT_IN;
"("               return '(';
")"               return ')';

[ \t\r]+          ; // Ignore whitespace
\n                { yylineno++; return '\n'; }

[a-zA-Z0-9_./-]+  {
    yylval.str = strdup(yytext);
    return WORD;
}

.                 return yytext[0];

%%

