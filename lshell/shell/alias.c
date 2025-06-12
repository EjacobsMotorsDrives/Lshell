
#define _POSIX_C_SOURCE 200809L
#include "shell.h"
#include <string.h>
#include <stdio.h>

Alias alias_table[MAX_ALIASES];
int alias_count = 0;

void set_alias(const char *name, const char *value) {
    for (int i = 0; i < alias_count; ++i) {
        if (strcmp(alias_table[i].name, name) == 0) {
            strncpy(alias_table[i].value, value, MAX_ALIAS_VALUE - 1);
            alias_table[i].value[MAX_ALIAS_VALUE - 1] = '\0';
            return;
        }
    }

    if (alias_count < MAX_ALIASES) {
        strncpy(alias_table[alias_count].name, name, MAX_ALIAS_NAME - 1);
        alias_table[alias_count].name[MAX_ALIAS_NAME - 1] = '\0';

        strncpy(alias_table[alias_count].value, value, MAX_ALIAS_VALUE - 1);
        alias_table[alias_count].value[MAX_ALIAS_VALUE - 1] = '\0';

        alias_count++;
    } else {
        fprintf(stderr, "alias: alias table full\n");
    }
}

void unset_alias(const char *name) {
    for (int i = 0; i < alias_count; ++i) {
        if (strcmp(alias_table[i].name, name) == 0) {
            // Shift remaining entries down
            for (int j = i; j < alias_count - 1; ++j) {
                alias_table[j] = alias_table[j + 1];
            }
            alias_count--;
            return;
        }
    }
}

const char *lookup_alias(const char *name) {
    for (int i = 0; i < alias_count; ++i) {
        if (strcmp(alias_table[i].name, name) == 0) {
            return alias_table[i].value;
        }
    }
    return NULL;
}

