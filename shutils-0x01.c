#include "shutils.h"


#define BUFFSIZE 1024

/**
 * _puts - Prints string
 * @string: Input string to print
 */
void _puts(const char *string)
{
	int k;

	k = 0;

	if (string == NULL)
		return;

	while (string[k] != '\0')
	{
		_putchar(string[k]);
		k++;
	}
}

/**
 * _putchar - Writes a character
 * @c: Character
 * Return: int
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * malloc_or_realloc - malloc or realloc a buffer
 * @line: pointer to a string
 * @i: index
 * @n: size of the buffer
 *
 * Return: 0 on success, -1 on failure
 */
int malloc_or_realloc(char **line, ssize_t i, size_t *n)
{
	if (i == 0)
	{
		*line = malloc(BUFFSIZE);
		if (*line == NULL)
			return (-1);
	}
	else if (i >= (ssize_t)(*n))
	{
		char *new_line = realloc(*line, *n * 2);

		if (new_line == NULL)
		{
			free(*line);
			return (-1);
		}
		*line = new_line;
		*n = *n * 2;
	}
	return (0);
}

/**
 * _getline - reads an entire line from stream
 * @lineptr: pointer to a buffer to store the line read
 * @n: pointer to the size of the buffer
 * @stream: stream to read from
 *
 * Return: number of characters read, including the delimiter
 *         -1 on failure or end of file
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	char c = '\0';
	ssize_t i = 0;
	char *line = NULL;

	if (!stream || stream != stdin)
		return (-1);

	*n = BUFFSIZE;

	while (c != '\n')
	{
		int rread = fread(&c, sizeof(char), 1, stream);

		if (rread <= 0)
			break;
		if (malloc_or_realloc(&line, i, n) == -1)
		{
			free(line);
			return (-1);
		}
		line[i++] = c;
	}

	if (i > 0 || c == '\n')
	{
		line[i] = '\0';
		*lineptr = line;
		if (i >= (ssize_t)(*n))
			*n = i + 1;
		return (i);
	}

	if (feof(stream))
	{
		free(line);
		return (-1);
	}

	free(line);
	return (-1);
}
