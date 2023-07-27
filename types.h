#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>

#include "constants.h"

#define UNUSED(x) (void)(x)

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

/**
 * struct alias_tag - An alias object
 * @name: Name of the alias
 * @value: Value of the alias
*/
typedef struct alias_tag
{
	char name[255];
	char value[255];
} alias_t;


/**
 * struct alias_conf_tag - Holds the shell's alias info
 * @aliases: Array of all aliases
 * @alias_count: Number of aliases
*/
typedef struct alias_conf_tag
{
	alias_t aliases[ALIAS_MAX_LIMIT];
	int alias_count;
} alias_ct;

/**
 * struct shell_tag - This structure holds the shell information
 * @close: Status for closing the shell
 * @input: Holds the input passed into the shell
 * @alias: Alias info object
 * @internal_cmd_list: Default commands for the shell
 * @prompt: Default prompt for the shell
 */
typedef struct shell_tag
{
	int close;
	char *input;
	alias_ct alias;
	cmd_list_t *internal_cmd_list;
	char prompt[255];
} shell_t;


#endif
