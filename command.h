#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>

typedef int (*icommand_interface)(char **args);

/**
 * struct icmd_mapping_tag - Command structure
 * @command: Name of the command
 * @function: Command routine
*/
typedef struct icmd_mapping_tag
{
	char *command;
	icommand_interface function;
} icmd_mapping;

/**
 * struct cmd_node_tag - Command node structure
 * @cmd_: Node data
 * @next: Next node
*/
typedef struct cmd_node_tag
{
	icmd_mapping *cmd_;
	struct cmd_node_tag *next;
} cmd_node_t;


/**
 * struct cmd_list_tag - A linked list for command nodes
 * @head: Head of the list
 * @size: Size of the list
*/
typedef struct cmd_list_tag
{
	cmd_node_t *head;
	size_t size;
} cmd_list_t;


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

void populate_commands(cmd_list_t **list);

#endif
