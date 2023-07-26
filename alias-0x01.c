#include "alias.h"

/**
 * print_alias - Searches for and prints an alias
 * @aliasct: Alias info object
 * @name: Name of the alias
 * Return: int
*/
int print_alias(alias_ct *aliasct, char *name)
{
	alias_t *alias = find_alias(aliasct, name);
	char *value;

	if (alias == NULL)
	{
		printf("hsh: alias: %s: not found\n", name);
		return (SS_OK);
	}
	printf("alias: %s=\'%s\'\n", alias->name, alias->value);
	return (SS_OK);
}

/**
 * tokenize_alias_arg - Tokenizes the argument passed to the alias
 * command
 * @input_string: The arguement string
 * @num_tokens: Address to store the number of tokens
 * Return: Array of strings
*/
char **tokenize_alias_arg(char *input_string, size_t *num_tokens)
{
	size_t token_count = 0;
	int within_quotes = 0;
	char *current = input_string;

	while (*current != '\0')
	{
		if (*current == '\'' || *current == '\"')
			within_quotes = !within_quotes;
		else if (*current == ' ' && !within_quotes)
			token_count++;
		current++;
	}
	token_count++;
	char **tokens = (char **)malloc(token_count * sizeof(char *));

	if (tokens == NULL)
	{
		*num_tokens = 0;
		return (NULL);
	}
	size_t token_index = 0;

	within_quotes = 0;
	current = input_string;
	tokens[token_index++] = (char *)current;

	while (*current != '\0')
	{
		if (*current == '\'' || *current == '\"')
			within_quotes = !within_quotes;
		else if (*current == ' ' && !within_quotes)
		{
			*current = '\0';
			tokens[token_index++] = (char *)(current + 1);
		}
		current++;
	}
	*num_tokens = token_count;
	return (tokens);
}

/**
 * get_distance - Calculate the distance between pointers
 * @first: First pointer, expected to be before the last pointer
 * @last: Last pointer
 * Return: The distance
*/
size_t get_distance(const char *first, const char *last)
{
	return ((last - first) - 1);
}


/**
 * is_enclosed - Checks if a string is enclosed by a character
 * @string: String
 * @c: Character
 * Return: int
*/
int is_enclosed(char *string, char c)
{
	char *first = strchr(string, c);
	char *last = strchr(first + 1, c);

	if ((first != NULL && last != NULL) && (first != last))
	{
		return (0);
	}
	else
	{
		return (1);
	}
}

