#include "main.h"
/**
 * count_tokens - Counts the number of tokens in a string.
 * @input_buffer: The buffer where the commands are stored.
 * @copy_buffer: Pointer to character (copy of the buffer).
 *
 * Return: 0 if there are no tokens, else return the number of tokens.
 */
int count_tokens(char *input_buffer, char *copy_buffer)
{
	char *token;
	int token_count = 0;

	token = strtok(input_buffer, " \n");
	if (token == NULL)
	{
		free(copy_buffer);
		return (0);
	}
	while (token != NULL)
	{
		token_count++;
		token = strtok(NULL, " \n");
		}
	return (token_count);
}
/**
 * extract_and_copy_tokens - Extracts and copies tokens from input buffers.
 * @copy_buffer: Pointer to character (copy of the buffer).
 * @num_tokens: Number of tokens to be extracted.
 * @original_args: Array of pointers to character
 * containing the original arguments.
 *
 * Return: NULL if it fails or a pointer
 * to character if it succeeds.
 */
char **extract_and_copy_tokens(char *copy_buffer,
int num_tokens, char **original_args)
{
	int i, j;
	char **copied_args;

	copied_args = malloc(sizeof(char *) * (num_tokens + 1));
	if (copied_args == NULL)
		return (NULL);

	copied_args[0] = malloc(sizeof(char) * (string_length(copy_buffer) + 1));
	if (copied_args[0] == NULL)
	{
		free(copied_args);
		return (NULL);
	}

	_strcpy(copied_args[0], copy_buffer);
	i = 1;

	while (i < num_tokens)
	{
		copied_args[i] = malloc(sizeof(char) *
		(string_length(original_args[i]) + 1));
		if (copied_args[i] == NULL)
		{
			j = 0;
			while (j < i)
			{
				free(copied_args[j]);
				j++;
			}
			free(copied_args);
			return (NULL);
		}

		_strcpy(copied_args[i], original_args[i]);
		i++;
	}

	copied_args[i] = NULL;
	return (copied_args);
}
/**
 * handle_cd - Handle the cd command.
 * @arguments: The arguments passed to cd command.
 *
 * Return: None.
 */
void handle_cd(char **arguments)
{
	char *new_dir;
	char current_dir[1024];
	char *pwd;

	if (arguments[1] == NULL || strcmp(arguments[1], "~") == 0)
		new_dir = getenv("HOME");
	else if (strcmp(arguments[1], "-") == 0)
	{
		new_dir = getenv("OLDPWD");
		if (new_dir == NULL)
		{
			fprintf(stderr, "OLDPWD not set\n");
			return;
		}
		printf("%s\n", new_dir);
	}
	else
		new_dir = arguments[1];
	if (chdir(new_dir) == -1)
	{
		perror("cd error");
		return;
	}
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
	{
		perror("getcwd error");
		return;
	}
	pwd = getenv("PWD");

	if (setenv("OLDPWD", pwd, 1) == -1)
	{
		perror("setenv error");
		return;
	}
	if (setenv("PWD", current_dir, 1) == -1)
	{
		perror("setenv error");
		return;
	}
}
