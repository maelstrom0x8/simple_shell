#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "main.h"

/**
 * main - entry point
 * @argc: the number of arguments
 * @argv: the argument vector
 * Return: 0 on success, -1 on failure
 */
int main(int argc __attribute__((unused)), char **argv)
{
	char *input_line = NULL, *buffer_copy;
	size_t buffer_size;
	ssize_t read_result;
	int line_number = 0, interactive_mode, process_result;

	interactive_mode = isatty(STDIN_FILENO);
	if (interactive_mode == 1)
		write(1, "$ ", 3);
	while ((read_result = getline(&input_line, &buffer_size, stdin)) != -1)
	{
		line_number++;
		handle_sharp(input_line);
		handle_envirem(input_line);
		if (_strcmp(input_line, "env\n") != 0)
		{
			if (_strcmp(input_line, "exit\n") == 0)
			{
				free(input_line);
				exit(EXIT_SUCCESS);
			}
			buffer_copy = copy_buffer(input_line, read_result);
			if (buffer_copy == NULL)
			{
				free(input_line);
				return (-1);
			}
			process_result = process_command(input_line, line_number,
			buffer_copy, argv);
			if (process_result == -1)
				return (-1);
		}
		if (interactive_mode == 1)
			write(1, "$ ", 3);
	}
	if (read_result == -1)
	{
		free(input_line);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

