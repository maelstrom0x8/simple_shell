#include "shutils.h"



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

	path_copy = _strdup(path);
	dir = strtok(path_copy, ":");

	while (dir != NULL)
	{
		char command_path[4096];

		snprintf(command_path, sizeof(command_path), "%s/%s", dir, command);

		if (access(command_path, X_OK) == 0)
		{
			free(path_copy);
			return (_strdup(command_path));
		}

		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
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

/**
 * _strncmp - Compares two strings up to a limit
 * @s1: First string
 * @s2: Second string
 * @nbytes: Number of characters to compare
 * Return: int
*/
int _strncmp(const char *s1, const char *s2, int nbytes)
{
	if (s1 == NULL && s2 == NULL)
	{
		return (1);
	}

	while (nbytes > 0)
	{
		if (*s1 != *s2)
		{
			return ((*s1) - (*s2));
		}
		if (*s1 == '\0')
		{
			return (0);
		}
		s1++;
		s2++;
		nbytes--;
	}
	return (0);
}


/**
 * _strncpy -  A function that copies a string
 * @dest: pointer to resulting string
 * @src: string source
 * @n: size of string to copy
 * Return: string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i = 0;

	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}

	return (dest);
}
