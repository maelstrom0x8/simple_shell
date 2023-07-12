#ifndef SIMPLE_SH_H
#define SIMPLE_SH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include "command.h"
extern char **environ;

#define SS_OK 0
#define SS_NOEXIST 1
#define SS_EXIT 2
#define SS_CLOSE 3
#define SS_EOF 65280

#define MAX_ARGS 1024
#define MAX_CMD_LEN 1024

#define UNUSED(x) (void)(x)

/**
 * struct shell_tag - This structure holds the shell information
 * @close: Status for closing the shell
 * @input: Holds the input passed into the shell
 * @internal_cmd_list: Default commands for the shell
 */
typedef struct shell_tag
{
	int close;
	char *input;
	cmd_list_t *internal_cmd_list;

} shell_t;


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

#endif
