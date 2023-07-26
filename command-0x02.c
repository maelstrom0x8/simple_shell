#include <libgen.h>
#include <limits.h>
#include <sys/wait.h>

#include "alias.h"
#include "command.h"
#include "shutils.h"
#include "simple_shell.h"

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

/**
 * run_command - A function that executes a command with given arguments.
 * @shell: Shell structure
 * @args: An array of strings representing the command and its arguments.
 * Return: int
 */

int run_command(shell_t *shell, char **args)
{
	int status;

	status = handle_builtin(shell, args);

	if (status != SS_CLOSE)
	{
		status = handle_external_command(args);
	}

	return (status);
}

/**
 * handle_builtin - Handles builtin commands
 * @shell: Global shell object
 * @args: Arguments
 * Return: int
 */
int handle_builtin(shell_t *shell, char **args)
{
	icmd_mapping *cmd = find_command(shell->internal_cmd_list, args[0]);

	if (cmd != NULL)
	{
		return (cmd->function(args));
	}

	return (SS_OK);
}


/**
 * handle_builtin_alias - Handle alias command
 * @shell: Global shell object
 * @args: Arguments
 * Return: int
*/
int handle_builtin_alias(shell_t *shell, char *args)
{
	int status;
	alias_ct *aliases = &(shell->alias);

	if (args == NULL)
	{
		print_aliases(aliases);
		fflush(stdin);
		return (SS_CLOSE);
	}

	size_t num_tokens = 0;
	char **tokens = tokenize_alias_arg(args, &num_tokens);

	for (size_t i = 0; i < num_tokens; ++i)
	{
		if (is_pair(tokens[i]) == 0)
		{
			alias_t alias = create_alias(tokens[i]);

			if (find_alias(&(shell->alias), alias.name) != NULL)
			{
				status = set_alias(&(shell->alias), alias);
			}
			else
			{
				status = add_alias(&(shell->alias), alias);
			}
		}
		else
		{
			status = print_alias(&(shell->alias), tokens[i]);
		}
	}
	free(tokens);
	return (SS_CLOSE);
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
		return (SS_CLOSE);
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
				return (SS_CLOSE);
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
		return (SS_CLOSE);
	}
}
