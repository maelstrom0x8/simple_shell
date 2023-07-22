#ifndef SIMPLE_SH_H
#define SIMPLE_SH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include "command.h"
#include "constants.h"
#include "types.h"

extern char **environ;


#define UNUSED(x) (void)(x)


void init_shell(shell_t **shell);

int main_loop(shell_t *shell);

void cleanup(shell_t *shell);

int count_tokens(char *line);

char **tokenize_args(char *args, int *num_tokens);

int render_shell(shell_t *shell);

int parse_command(shell_t *shell);

int run_command(shell_t *shell, char **args);

char *basename(char *path);

char *check_path(char *cmd);

int _feof(void);

void trim_input(char *input);

void sanitize_input(char *input);

void _free(void *ptr);

int process_alias(alias_ct *alias, char **args);

alias_t create_alias(char *argv);

int is_pair(char *pair);

alias_t* find_alias(alias_ct *aliasCt, char *name);

int set_alias(alias_ct *aliasCt, alias_t alias);

int add_alias(alias_ct *aliasCt, alias_t alias);

int print_alias(alias_ct *aliasCt, char *name);

#endif
