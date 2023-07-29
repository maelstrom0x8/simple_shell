#include "main.h"
/**
 * handle_path - Handles the path for command execution.
 * @env_copy: Copy of the environment variable "PATH".
 * @arg: Array of pointers to character
 * containing the command and its arguments.
 * @buffer: Buffer where the command is stored.
 * @num_tokens: Number of tokens.
 * @arg_vector: The argument vector.
 * @command_index: Index of the command.
 * @copy_buffer: Pointer to character (unused in this function).
 *
 * Return: None.
 */
void handle_path(char *env_copy, char **arg, char *buffer,
int num_tokens, char **arg_vector,
int command_index, char *copy_buffer __attribute__((unused)))
{
	char *token;
	char **arg2 = NULL;
	char path_buffer[1024];
	char slash_buffer[3] = "/";
	const char *file_path;

	for (token = strtok(env_copy, ":"); token != NULL; token = strtok(NULL, ":"))
	{
		_strcpy(path_buffer, token);
		_strcat(path_buffer, slash_buffer);
		_strcat(path_buffer, arg[0]);
		file_path = path_buffer;

		if (access(file_path, F_OK) == 0)
		{
			free(env_copy);
			arg2 = extract_and_copy_tokens(path_buffer, num_tokens, arg);
			execute_command(arg2, buffer, copy_buffer, arg_vector, command_index);
			free_arguments(arg2);
			return;
		}
	}

	if (token == NULL)
	{
		print_error(arg_vector, arg, command_index);
		free(env_copy);
		return;
	}
}
/**
 * extract_tokens - Extracts and copies tokens from copied buffer.
 * @copy_buffer: Pointer to character (copied buffer).
 * @num_tokens: Number of tokens to be extracted.
 *
 * Return: NULL if it fails or a pointer to character if it succeeds.
 */
char **extract_tokens(char *copy_buffer, int num_tokens)
{
	char *token;
	int i = 0, j;
	char **arg_array;

	arg_array = malloc(sizeof(char *) * (num_tokens + 1));
	if (arg_array == NULL)
		return (NULL);

	token = strtok(copy_buffer, " \t\n");
	while (token != NULL)
	{
		arg_array[i] = malloc(sizeof(char) * (_strlen(token) + 1));
		if (arg_array[i] == NULL)
		{
			for (j = 0; j < i; j++)
			{
				free(arg_array[j]);
			}
			free(arg_array);
			return (NULL);
		}
		_strcpy(arg_array[i], token);
		token = strtok(NULL, " \t\n");
		i++;
	}

	arg_array[i] = NULL;
	return (arg_array);
}


