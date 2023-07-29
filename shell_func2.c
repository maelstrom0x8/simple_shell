#include "main.h"
/**
 * envirem - Handles the environment variable and
 * extracts paths for command execution.
 * @arg: Array of pointers to character containing the
 * command and its arguments.
 * @buffer: Buffer where getline stores the commands.
 * @p: Pointer to character (unused in this function).
 * @n: Number of tokens (unused in this function).
 * @av: The argument vector (unused in this function).
 * @num: Number of commands (unused in this function).
 *
 * Return: None.
 */
void envirem(char **arg, char *buffer, char *p, int n, char **av, int num)
{
	char *env_path = NULL, *env_copy;
	int index = 0;

	while (environ[index] != NULL)
	{
		if (string_compare(environ[index], "PATH=", 5) == 0)
		{
			env_path = environ[index] + 5;
			break;
		}
		index++;
	}

	if (env_path == NULL)
	{
		perror("No envirement path\n");
		return;
	}

	env_copy = string_duplicate(env_path);
	if (env_copy == NULL)
	{
		perror("No envirement copy\n");
		return;
	}

	handle_path(env_copy, arg, buffer, n, av, num, p);
}
/**
 * _puts - its a function that print a string
 * @strg: pointer to character
 * @iden: identifier
 * Return: None
 */
void _puts(char *strg, int iden)
{
	write(iden, strg, string_length(strg));
}
/**
 * handle_envirem - Handles the 'env' command.
 * @buffer: Buffer where getline stores the commands.
 *
 * Return: None.
 */
void handle_envirem(char *buffer)
{
	int i = 0;

	if (_strcmp(buffer, "env\n") == 0)
	{
		while (environ[i] != NULL)
		{
			_puts(environ[i], STDOUT_FILENO);
			_puts("\n", STDOUT_FILENO);
			i++;
		}
	}
}



