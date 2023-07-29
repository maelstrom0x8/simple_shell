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


