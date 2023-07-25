#ifndef TYPES_H
#define TYPES_H

#include "constants.h"



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

typedef struct alias_tag {
	char name[255];
	char value[255];
} alias_t;

typedef struct alias_conf_tag {
	alias_t aliases[ALIAS_MAX_LIMIT];
	int alias_count;
} alias_ct;

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
	alias_ct alias;
	cmd_list_t *internal_cmd_list;

} shell_t;


#endif