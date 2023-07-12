#include <unistd.h>
#include <string.h>
#include "simple_shell.h"
#include "stdsh.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * check_path - A function that checks if a command is
 * in the PATH environment variable.
 * @command: A string representing the command to check.
 * Return: A string representing the full path of the
 * command if it is found in PATH, otherwise NULL.
 */
char *check_path(char *command)
{
	char *path_copy;
	char *dir;

	char *path = getenv("PATH");

	if (path == NULL)
	{
		printf("Error: PATH environment variable not found.\n");
		return (NULL);
	}

	path_copy = strdup(path);
	dir = strtok(path_copy, ":");

	while (dir != NULL)
	{
		char command_path[4096];

		snprintf(command_path, sizeof(command_path), "%s/%s", dir, command);

		if (access(command_path, X_OK) == 0)
		{
			free(path_copy);
			return (strdup(command_path));
		}

		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * basename - A function that returns the filename component of
 * a path string.
 * Description: This function takes a string representing a path
 * as an argument and returns the filename
 * component of the path. For example, if the path is "/usr/bin/cat",
 * the function returns "cat".
 * @path: A string representing a path.
 * Return: A string representing the filename component of the path.
 */
char *basename(char *path)
{
	char *base = strrchr(path, '/');

	if (base == NULL)
		return (path);
	else
		return ((base) + 1);
}

/**
 * is_absolute - Checks if a path is absolute
 * @path: Path supplied to function
 * Return: O if true or 1 if false
*/
int is_absolute(char *path)
{
	if (path[0] == '/')
		return (0);
	else
		return (1);
}
