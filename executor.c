#include "simple_shell.h"
#include "stdsh.h"
#include "utils.h"
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
