#include "simple_shell.h"
#include "stdsh.h"
#include "command.h"
#include "utils.h"
#include "types.h"

#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>
/**
 * handle_builtin - Handles builtin commands
 * @list: Command list
 * @args: Arguments
 * Return: int
 */
int handle_builtin(cmd_list_t *list, char **args)
{
	icmd_mapping *cmd = find_command(list, args[0]);

	if (cmd == NULL)
	{
		return (-1);
	}
	else
	{
		cmd->function(args);
	}
	return (0);
}

/**
 * handle_external_command - Handles external commands
 * @args: Arguments
 * Return: int
 */
int handle_external_command(char **args)
{
	int status;
	char *path;

	if (is_absolute(args[0]) == 0)
		path = _strdup(args[0]);
	else
		path = check_path(args[0]);
	if (path == NULL)
	{
		_puts(args[0]);
		_puts(" :  not found\n");
		return (SS_EXIT);
	}
	else
	{
		pid_t pid = fork();

		if (pid == 0)
		{
			char *envp[] = {NULL};

			if (execve(path, args, envp) == -1)
			{
				_puts("./shell: No such file or directory\n");
				return (SS_EXIT);
			}
		}
		else if (pid < 0)
		{
			_puts("./shell: No such file or directory\n");
			return (SS_CLOSE);
		}
		else
		{
			waitpid(pid, &status, 0);
			free(path);
		}
		return (SS_OK);
	}
}

/**
 * run_command - A function that executes a command with given arguments.
 * @shell: Shell structure
 * @args: An array of strings representing the command and its arguments.
 * Return: int
 */

int run_command(shell_t *shell, char **args)
{
	int status;

	status = handle_builtin(shell->internal_cmd_list, args);

	if (strcmp(args[0], "alias"))
	{
		status = handle_builtin_alias(shell);
	}

	if (status == -1)
	{
		status = handle_external_command(args);
	}

	return (status);
}

/**
 * populate_commands - Populates the command list
 * with the default commands
 * @list: Command list
 */
void populate_commands(cmd_list_t **list)
{
	add_command(*list, "env", printenv);
	add_command(*list, "exit", terminate);
	add_command(*list, "setenv", _setenv);
	add_command(*list, "unsetenv", _unsetenv);
	add_command(*list, "cd", change_directory);
}

int handle_builtin_alias(shell_t *shell)
{
	/**
	 * check for valid input
	 * iterate through the input
	 * if the input is a name=value pair
	 * 		if the alias=name already exist
	 * 			set the alias to the value
	 * 		else add the name=value as a new alias
	 * else find the alias=name
	 * 		if alias is found print it [name='value']
	 * 		else print an error hsh: alias: name: not found
	 */

	process_alias(&(shell->alias), &(shell->input));

	/* 	while ((*argv) != NULL) {
			alias_t* alias = create_alias(*argv);
			if (alias == NULL)
				return 1;
			if(alias_exists(alias))
				alias_set(alias);
			else
				alias_add(alias);

		} */
}

alias_t create_alias(char *arg)
{
	alias_t new_alias;
	memset(&new_alias, 0, sizeof(alias_t));

	if (arg == NULL || strlen(arg) == 0)
	{
		return new_alias;
	}

	char *equal_sign = strchr(arg, '=');

	if (equal_sign != NULL)
	{
		size_t key_len = equal_sign - arg;
		size_t value_len = strlen(equal_sign + 1);

		strncpy(new_alias.name, arg, key_len);
		strncpy(new_alias.value, equal_sign + 1, value_len);
	}
	else
	{
		strncpy(new_alias.name, arg, sizeof(new_alias.name) - 1);
	}

	return new_alias;
}

int is_pair(char *pair)
{
	return (1);
}

int set_alias(alias_ct *aliasCt, alias_t alias)
{
}

int add_alias(alias_ct *aliasCt, alias_t alias)
{
}

int print_alias(alias_ct *aliasCt, char *name)
{
}

alias_t *find_alias(alias_ct *aliasCt, char *name)
{
}

int process_alias(alias_ct *alias_info, char **args)
{
	while (*(++args) != NULL)
	{
		if (is_pair(*args))
		{
			alias_t alias = create_alias(*args);	// return an alias_t
			if (find_alias(alias_info, alias.name)) // return the position of alias in alias_info.aliases by name
			{
				set_alias(alias_info, alias); // updates an existing alias value with name alias.name to alias.value
			}
			else
			{
				add_alias(alias_info, alias); // appends an alias to alias_info.aliases
			}
		}
		else
		{
			print_alias(alias_info, *args); // prints and alias in the form name='value'
		}
	}
}
