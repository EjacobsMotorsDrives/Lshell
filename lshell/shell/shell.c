
#define _POSIX_C_SOURCE 200809L
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <readline/readline.h>
#include <readline/history.h>

#define PROMPT_MAX 512
#define HISTORY_FILE ".lshell_history"

static char prompt[PROMPT_MAX];

// Return shell prompt string
const char *get_prompt() {
    char *user = getenv("USER");
    if (!user) {
        struct passwd *pw = getpwuid(getuid());
        user = pw ? pw->pw_name : "user";
    }

    char cwd[256];
    getcwd(cwd, sizeof(cwd));

    snprintf(prompt, PROMPT_MAX, "%s@lshell:%s$ ", user, cwd);
    return prompt;
}

// Initialize PATH to include /bin and /usr/bin
void setup_path() {
    const char *path = getenv("PATH");
    if (!path || !strstr(path, "/bin")) {
        setenv("PATH", "/bin:/usr/bin", 1);
    }
}

// Load shell command history from file
void load_history() {
    char *home = getenv("HOME");
    if (home) {
        char path[512];
        snprintf(path, sizeof(path), "%s/%s", home, HISTORY_FILE);
        read_history(path);
    }
}

// Save new line to shell history file
void save_history_line(const char *line) {
    char *home = getenv("HOME");
    if (home) {
        char path[512];
        snprintf(path, sizeof(path), "%s/%s", home, HISTORY_FILE);
        append_history(1, path);
    }
}

