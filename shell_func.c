#include "main.h"
#include <stdlib.h>

/**
 * handle_sharp - Find the position of '#' in the input
 * @input_line: Pointer to the source buffer.
 *
 * Return: Nothing.
 */
void handle_sharp(char *input_line)
{
	char *comment_start = strchr(input_line, '#');

	if (comment_start != NULL)
	{
		if (comment_start == input_line  || *(comment_start - 1) == ' ')
		{
			size_t comment_index = comment_start - input_line;

			input_line[comment_index] = '\0';
		}
	}

}

/**
 * copy_buffer - Copies the contents of a buffer to a new buffer.
 * @buffer: Pointer to the source buffer.
 * @size: Size of the buffer.
 *
 * Return: Pointer to the new buffer containing the copied data.
 */
char *copy_buffer(char *buffer, size_t size)
{
	char *new_buffer;

	if (buffer == NULL)
		return (NULL);

	new_buffer = malloc((size + 1) * sizeof(char));
	if (new_buffer == NULL)
		return (NULL);

	_strcpy(new_buffer, buffer);
	return (new_buffer);
}
/**
 * int_to_string - Converts an integer to a string.
 * @num: The integer number to be converted.
 * Return: Pointer to the string representation of the number.
 */
char *int_to_string(int num)
{
	int num_copy = num;
	int num_copy2 = 0;
	int j = 0;
	int start = 0, end, length = 0;
	char c;
	char *str;

	do {
		length++;
		num_copy /= 10;
	} while (num_copy != 0);

	str = malloc((length + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);

	while (num != 0)
	{
		num_copy2 = num % 10;
		str[j] = num_copy2 + '0';
		j++;
		num = num / 10;
	}
	str[j] = '\0';
	end = length - 1;
	while (start < end)
	{
		c = str[start];
		str[start] = str[end];
		str[end] = c;
		start++;
		end--;
	}
	return (str);
}
/**
 * print_not_found_error - Prints a "not found" error message.
 * @av: The argument vector (unused in this function).
 * @arg: Array of pointers to character containing the command or
 * program that was not found.
 * @i: The number of commands (unused in this function).
 *
 * Return: None.
 */
void print_not_found_error(char **av, char **arg, int i)
{
	char *error_message;

	write(STDOUT_FILENO, av[0], string_length(av[0]));
	write(STDOUT_FILENO, ": ", 2);
	error_message = int_to_string(i);
	if (error_message != NULL)
	{
		write(STDOUT_FILENO, error_message, string_length(error_message));
		free(error_message);
		write(STDOUT_FILENO, ": ", 2);
		write(STDOUT_FILENO, arg[0], string_length(arg[0]));
		write(STDOUT_FILENO, ": ", 2);
		write(STDOUT_FILENO, "Not found\n", 10);
	}
}


