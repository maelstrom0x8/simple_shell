#include "main.h"
#include <stdlib.h>

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
	size_t i;

	if (buffer == NULL)
		return (NULL);

	new_buffer = (char *)malloc(size * sizeof(char));
	if (new_buffer == NULL)
		return (NULL);

	for (i = 0; i < size; i++)
		new_buffer[i] = buffer[i];

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
	int length = 0;
	char *str;

	do {
		length++;
		num_copy /= 10;
	} while (num_copy != 0);

	str = (char *)malloc((length + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);

	str[length] = '\0';
	do {
		length--;
		str[length] = '0' + (num % 10);
		num /= 10;
	} while (num != 0);

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

	write(STDOUT_FILENO, av[0], _strlen(av[0]));
	write(STDOUT_FILENO, ": ", 2);
	error_message = num_to_string(i);
	if (error_message != NULL)
	{
		write(STDOUT_FILENO, error_message, _strlen(error_message));
		free(error_message);
		write(STDOUT_FILENO, ": ", 2);
		write(STDOUT_FILENO, arg[0], _strlen(arg[0]));
		write(STDOUT_FILENO, ": ", 2);
		write(STDOUT_FILENO, "Not found\n", 10);
	}
}


