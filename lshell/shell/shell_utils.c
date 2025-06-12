
#define _POSIX_C_SOURCE 200809L
#include "shell.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

// Trim leading and trailing whitespace
void trim_whitespace(char *str) {
    if (!str) return;

    // Trim leading
    while (isspace((unsigned char)*str)) str++;

    // Trim trailing
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    *(end + 1) = '\0';
}

// Parse input into arguments
void parse_command(const char *input, char **args, size_t max_args) {
    char *temp = strdup(input);
    char *token = strtok(temp, " \t");
    size_t i = 0;

    while (token && i < max_args - 1) {
        args[i++] = strdup(token);
        token = strtok(NULL, " \t");
    }
    args[i] = NULL;

    free(temp);
}

// Expand environment variables in-place (e.g., $HOME)

void expand_variables(char **line) {
    if (!line || !*line) return;

    const char *src = *line;
    char result[1024] = {0};
    char *r = result;

    while (*src) {
        if (*src == '$') {
            src++;
            char var[64] = {0};
            char *v = var;
            while (*src && (isalnum((unsigned char)*src) || *src == '_')) {
                *v++ = *src++;
            }
            *v = '\0';
            char *val = getenv(var);
            if (val) r += sprintf(r, "%s", val);
        } else {
            *r++ = *src++;
        }
    }

    *r = '\0';
    free(*line);
    *line = strdup(result);
}
// Replace argument with alias value if matched
void expand_alias(char **args) {
    if (!args || !args[0]) return;

    const char *val = lookup_alias(args[0]);
    if (val) {
        free(args[0]);
        args[0] = strdup(val);
    }
}

int handle_builtin_command(char **args, int *status) {
    if (!args || !args[0]) return 0;

    if (strcmp(args[0], "exit") == 0) {
        exit(0);
    } else if (strcmp(args[0], "cd") == 0) {
        const char *path = args[1] ? args[1] : getenv("HOME");
        if (chdir(path) != 0) {
            perror("cd");
            *status = 1;
        } else {
            *status = 0;
        }
        return 1;
    }

    // Add other built-ins here if needed
    return 0; // Not a built-in
}
