#include "main.h"
/**
 * execute_command - Executes a command.
 * @arguments: The arguments in the command.
 * @buffer: The buffer where the command is stored.
 * @copy_buffer: Pointer to character (unused in this function).
 * @args_vector: The argument vector.
 * @cmd_index: The number of commands.
 *
 * Return: None.
 */
void execute_command(char **arguments, char *buffer, char *copy_buffer,
char **args_vector, int cmd_index)
{
	char *command = NULL;
	int result;
	pid_t child_pid;

	if (arguments == NULL)
		return;

	command = arguments[0];
	child_pid = fork();

	if (child_pid == -1)
	{
		free_everything(buffer, copy_buffer, arguments);
	}
	if (child_pid == 0)
	{
		result = execve(command, arguments, environ);

		if (result == -1)
		{
			print_not_found_error(args_vector, arguments, cmd_index);
			free_everything(buffer, copy_buffer, arguments);
			exit(EXIT_FAILURE);
		}
	}

	wait(NULL);
}
/**
 * process_command - Process a command and execute it.
 * @input_buffer: The buffer where the command is stored.
 * @command_index: The number of the command.
 * @command_copy: Pointer to character (unused in this function).
 * @arg_vector: The argument vector.
 *
 * Return: 1 on success, -1 on failure.
 */
int process_command(char *input_buffer, int command_index,
char *command_copy, char **arg_vector)
{
	char **arguments;
	const char *file_path;
	int token_count;

	token_count = count_tokens(input_buffer, command_copy);
	if (token_count > 0)
	{
		arguments = extract_tokens(command_copy, token_count);
		if (arguments == NULL)
		{
			free_everything(input_buffer, command_copy, arguments);
			return (-1);
		}

		file_path = arguments[0];
		if (access(file_path, F_OK) == -1)
			envirem(arguments, input_buffer, command_copy,
			token_count, arg_vector, command_index);
		else
			execute_command(arguments, input_buffer,
			command_copy, arg_vector, command_index);

		free(command_copy);
		freeargum(arguments);
	}
	return (1);
}


