#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>

#include "types.h"


int init_cmd_list(cmd_list_t **list);

void add_command(cmd_list_t *list, char *name, icommand_interface func);

void remove_command(cmd_list_t *list, char *name);

void clear_commands(cmd_list_t *list);

size_t cmd_list_size(cmd_list_t *list);

icmd_mapping *find_command(cmd_list_t *list, char *name);

int printenv(char **args);

int _unsetenv(char **args);

int _setenv(char **args);

int terminate(char **args);

int change_directory(char **args);

int handle_external_command(char **args);

int handle_builtin_alias(shell_t *shell);

void populate_commands(cmd_list_t **list);

#endif
