#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>

#include "constants.h"

#define UNUSED(x) (void)(x)

typedef int (*icommand_interface)(char **args);
/**
 * struct CommandInfo - Structure to hold information for reading data
 * @input_line: A string generated from getline containing arguments
 * @arguments: An array of strings generated from input_line
 * @command_path: A string representing the path for the current command
 * @arg_count: The argument count
 * @line_num: The error count (line number)
 * @error_code: The error code for exit()s
 * @count_this_line: If on, count this line of input
 * @program_name: The program filename
 * @environment: Linked list local copy of environment variables
 * @history_node: The history node
 * @alias_node: The alias node
 * @modified_env: Custom modified copy of the environment variables from LL env
 * @env_changed: Flag indicating if the environment was changed
 * @return_status: The return status of the last exec'd command
 * @cmd_chain_buf: Address of the pointer to the command chaining buffer (cmd_buf)
 * @cmd_chain_type: Command chaining type (CMD_type) ||, &&, ;
 * @read_fd: The file descriptor from which to read line input
 * @history_line_count: The history line number count
 */
typedef struct command_info
{
    char *input_line;
    char **arguments;
    char *command_path;
    int arg_count;
    unsigned int line_num;
    int error_code;
    int count_this_line;
    char *program_name;
    list_t *environment;
    list_t *history_node;
    list_t *alias_node;
    char **modified_env;
    int env_changed;
    int return_status;
    char **cmd_chain_buf;
    int cmd_chain_type;
    int read_fd;
    int history_line_count;
} CommandInfo;

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
 */
typedef struct shell_tag
{
	int close;
	char *input;
	alias_ct alias;
	cmd_list_t *internal_cmd_list;

} shell_t;


#endif
