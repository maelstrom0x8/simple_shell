#include "simple_shell.h"
#include "stdsh.h"
#include "command.h"

/**
 * _setenv - Sets an environment variable
 * @args: Arguments
 * Return: int
 */

int _setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		_puts("setenv: invalid arguments\n");
		return (SS_CLOSE);
	}

	if (setenv(args[1], args[2], 1) != 0)
	{
		_puts("setenv: failed to set environment variable\n");
		return (SS_CLOSE);
	}

	return (SS_CLOSE);
}

/**
 * _unsetenv - Unsets an environment variable
 * @args: Arguments
 * Return: int
 */
int _unsetenv(char **args)
{
	if (unsetenv(args[1]) == -1)
		_puts("unsetenv: failed to unset environment variable\n");
	return (SS_CLOSE);
}

/**
 * terminate - Terminates the program
 * @args: Arguments
 * Return: int
*/
int terminate(char **args)
{
	UNUSED(args);
	printf("exit\n");
	exit(SS_OK);
	return (SS_OK);
}

/**
 * printenv - A function that prints the current environment variables.
 * @args: Arguments
 * Description: This function prints the current environment variables
 * to the standard output
 * using the environ global variable. It returns 0 if successful.
 * Return: An integer representing the status of the function execution.
 */

int printenv(char **args)
{
	char **envp;

	UNUSED(args);
	envp = environ;

	while (*envp)
	{
		_puts(*envp);
		_puts("\n");
		envp++;
	}
	return (SS_CLOSE);
}


/**
 * cmd_list_size - Size of a command list
 * @list: Command list
 * Return: The size of the list
 */
size_t cmd_list_size(cmd_list_t *list)
{
	if (list == NULL)
		return (0);

	return (list->size);
}

