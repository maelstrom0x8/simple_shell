#include "stdsh.h"
#include "command.h"
#include <unistd.h>
#include <string.h>

/**
 * _memcpy - Copy memory from source to destination
 * @dest: Pointer to the destination memory
 * @src: Pointer to the source memory
 * @n: Number of bytes to copy
 *
 * Return: Pointer to the destination memory
 */

void *_memcpy(void *dest, const void *src, size_t n)
{
	char *dest_ptr = (char *)dest;
	const char *src_ptr = (const char *)src;
	size_t i;

	for (i = 0; i < n; i++)
	{
		dest_ptr[i] = src_ptr[i];
	}

	return (dest);
}

/**
 * _feof - Checks EOF status
 * Return: int
 */

int _feof(void)
{
	int c = fgetc(stdin);

	if (c == EOF)
	{
		return (1);
	}
	else
	{
		ungetc(c, stdin);
		return (0);
	}
}

/**
 * _free - Deallocates memory
 * @ptr: Pointer
 */
void _free(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
	}
}


/**
 * change_directory - This functions changes the
 * directory
 * @args: Arguments
 * Return: int
*/
int change_directory(char **args)
{
	char current_directory[4096];
	char *new_directory;
	static char previous_directory[4096] = "";

	if (args[1] == NULL || _strcmp(args[1], "") == 0)
		new_directory = getenv("HOME");
	else if (_strcmp(args[1], "-") == 0)
		new_directory = previous_directory;
	else
		new_directory = (char *)args[1];
	if (new_directory == NULL)
	{
		_puts("Error: Home directory not found.\n");
		return (-1);
	}

	if (getcwd(current_directory, sizeof(current_directory)) == NULL)
	{
		perror("getcwd");
		return (-1);
	}

	if (chdir(new_directory) != 0)
	{
		perror("chdir");
		return (-1);
	}
	else
	{
		char **arg = (char **)malloc(3 * sizeof(char *));

		arg[0] = NULL;
		arg[1] = "PWD";
		arg[2] = new_directory;
		_setenv(arg);
		_strcpy(previous_directory, current_directory);
		free(arg);
	}
	return (0);
}

/**
 * _strcpy -  function that copies the string pointed to by src, including
 * the terminating null byte (\0), to the buffer pointed to by dest.
 * @dest: The destination
 * @src: The source
 *
 * Return: void
 */
char *_strcpy(char *dest, const char *src)
{
	char *start = dest;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';

	return (start);
}
