#include "command.h"




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
		return (SS_CMD_ERR);
	}

	if (getcwd(current_directory, sizeof(current_directory)) == NULL)
	{
		perror("getcwd");
		return (SS_CMD_ERR);
	}

	if (chdir(new_directory) != 0)
	{
		perror("chdir");
		return (SS_CMD_ERR);
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
	return (SS_OK);
}

