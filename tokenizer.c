#include "simple_shell.h"
#include "stdsh.h"
#include "string.h"

#include <stdbool.h>

/**
 * count_tokens - Count the number of tokens in a string
 * @line: The string to count tokens in
 * Return: The number of tokens in the string
 */

int count_tokens(char *line)
{
	char *token;
	int count;

	count = 0;
	token = strtok(line, " \n");
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, " \n");
	}
	return (count);
}

/**
 * tokenize_args - Tokenize a string into an array of tokens
 * @line: The string to tokenize
 * @num_tokens: The number of tokens which is returned to
 * the caller
 * Return: An array of tokens
 */

char **tokenize_args(char *line, int *num_tokens)
{
	int bufsize;
	char **args;
	char *token;

	bufsize = MAX_ARGS;
	args = malloc(bufsize * sizeof(char *));
	token = strtok(line, " \n");
	(*num_tokens) = 0;
	while (token != NULL)
	{
		/* TODO: Add custom implementation for strdup */
		args[*num_tokens] = strdup(token);
		(*num_tokens)++;
		token = strtok(NULL, " \n");
	}
	args[*num_tokens] = NULL;

	return (args);
}

/**
 * trim_input - Trims a string
 * @input: String
 */

void trim_input(char *input)
{
	if (input != NULL)
	{
		size_t len = _strlen(input);

		if (len > 0 && input[len - 1] == '\n')
		{
			input[len - 1] = '\0';
		}
	}
}

/**
 * sanitize_input - Sanitizes input
 * @input: Input
 */
void sanitize_input(char *input)
{
	char *src;

	char *dest = input;
	int prev_space = 0;

	for (src = input; *src != '\0'; ++src)
	{
		if (_isspace((unsigned char)*src))
		{
			if (!prev_space)
			{
				*dest++ = ' ';
				prev_space = 1;
			}
		}
		else
		{
			*dest++ = *src;
			prev_space = 0;
		}
	}

	*dest = '\0';
}
