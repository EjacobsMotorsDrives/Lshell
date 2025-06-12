
#ifndef SHELL_H
#define SHELL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h> // For size_t

// ==================================
// Alias Support
// ==================================

#define MAX_ALIASES 64
#define MAX_ALIAS_NAME 64
#define MAX_ALIAS_VALUE 256

typedef struct {
    char name[MAX_ALIAS_NAME];
    char value[MAX_ALIAS_VALUE];
} Alias;

extern Alias alias_table[MAX_ALIASES];

// Alias management
void set_alias(const char *name, const char *value);
void unset_alias(const char *name);
const char *lookup_alias(const char *name);

// ==================================
// Shell AST Support
// ==================================


typedef enum {
    AST_COMMAND,
    AST_SEQUENCE,
    AST_AND,
    AST_OR,
    AST_REDIR_OUT,
    AST_REDIR_IN,
    AST_APPEND
} ASTNodeType;
typedef struct ASTNode {
    ASTNodeType type;
    char *cmd;
    char **argv;
    char *filename;
    int redirect_type;
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;

ASTNode *make_command_node(char **argv);
ASTNode *make_op_node(ASTNodeType type, ASTNode *left, ASTNode *right);
ASTNode *make_redirect_node(ASTNodeType type, ASTNode *command, const char *filename);

void free_ast( ASTNode *node);
void print_ast(const  ASTNode *node);
int execute_ast(const  ASTNode *node);


// Additional AST helpers (needed by parser.y)
ASTNode *append_arg(ASTNode *command, const char *arg);
ASTNode *attach_redirection(ASTNode *command, ASTNode *redir);
ASTNode *make_sequence_node(ASTNode *left, ASTNode *right);
ASTNode *make_and_node(ASTNode *left, ASTNode *right);
ASTNode *make_or_node(ASTNode *left, ASTNode *right);
ASTNode *make_redirection_node(const char *op, const char *filename);


int run_ast(ASTNode *node);
// ==================================
// Shell Utility Functions
// ==================================

void trim_whitespace(char *str);
void parse_command(const char *input, char **args, size_t max_args);
void expand_variables(char **line);
void expand_alias(char **args);

// ==================================
// Main Shell Functions
// ==================================

void shell_loop();
void setup_path();
const char *get_prompt();
void save_history_line(const char *line);
void load_history();

int handle_builtin_command(char **args, int *status);  // External declaration


#ifdef __cplusplus
}
#endif

#endif // SHELL_H

