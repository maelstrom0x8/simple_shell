#include "simple_shell.h"
#include "stdsh.h"
#include "command.h"




/**
 * init_cmd_list - Initializes the command list
 * @list: Command list
 * Return: int
 */
int init_cmd_list(cmd_list_t **list)
{
	*list = (cmd_list_t *)malloc(sizeof(cmd_list_t));

	if (list == NULL)
		return (-1);

	(*list)->head = NULL;
	(*list)->size = 0;

	/* populate_commands(&list); */

	return (0);
}

/**
 * add_command - Adds a command to a list
 * @list: Command list
 * @name: Name of the command
 * @func: Command function
 */
void add_command(cmd_list_t *list, char *name, icommand_interface func)
{
	cmd_node_t *node = (cmd_node_t *)malloc(sizeof(cmd_node_t));

	if (node != NULL)
	{
		node->cmd_ = (icmd_mapping *) malloc(sizeof(icmd_mapping));
		node->cmd_->command = (char *)malloc(sizeof(char) * (strlen(name) + 1));
		strcpy((char *)node->cmd_->command, name);
		node->cmd_->function = func;
		node->next = NULL;
	}

	if (list->head == NULL)
	{
		list->head = node;
	}
	else
	{
		cmd_node_t *current = list->head;

		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = node;
	}

	list->size++;
}

/**
 * clear_commands - Clears a command list
 * @list: Command list
 */
void clear_commands(cmd_list_t *list)
{
	cmd_node_t *current;
	cmd_node_t *next;

	if (cmd_list_size(list) == 0)
		return;

	current = list->head;

	while (current != NULL)
	{
		next = current->next;
		free(current->cmd_->command);
		free(current->cmd_);
		free(current);
		current = next;
	}

	list->head = NULL;
	list->size = 0;
}

/**
 * find_command - Searches for a command in the command
 * list
 * @list: Command list
 * @name: Command name
 * Return: A command or NULL
 */
icmd_mapping *find_command(cmd_list_t *list, char *name)
{
	cmd_node_t *current = list->head;

	while (current != NULL)
	{
		if (_strcmp(current->cmd_->command, name) == 0)
		{
			return (current->cmd_);
		}
		current = current->next;
	}

	return (NULL);
}

/**
 * remove_command - Removes a command from a command
 * list
 * @list: Command list
 * @name: Command name
 */
void remove_command(cmd_list_t *list, char *name)
{
	cmd_node_t *current = list->head;
	cmd_node_t *prev = NULL;

	while (current != NULL)
	{
		if (_strcmp(current->cmd_->command, name) == 0)
		{
			if (prev == NULL)
				list->head = current->next;
			else
				prev->next = current->next;

			free(current);
			list->size--;
			return;
		}

		prev = current;
		current = current->next;
	}
}
