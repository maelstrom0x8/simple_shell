#include "alias.h"


int print_alias(alias_ct *aliasCt, char *name)
{
	alias_t *alias = find_alias(aliasCt, name);
	char *value;

	if (alias == NULL)
	{
		printf("hsh: alias: %s: not found\n", name);
		return SS_OK;
	}
	printf("alias: %s=\'%s\'\n", alias->name, alias->value);
	return SS_OK;
}

char *concatenate_strings(char **string_array, size_t num_strings)
{
	size_t total_length = 0;
	for (size_t i = 0; i < num_strings; ++i)
	{
		total_length += strlen(string_array[i]);
		if (i < num_strings - 1)
		{
			total_length += 1;
		}
	}

	char *concatenated_string = (char *)malloc(total_length + 1);
	if (concatenated_string == NULL)
	{
		return NULL;
	}

	size_t current_pos = 0;
	for (size_t i = 0; i < num_strings; ++i)
	{
		size_t str_length = strlen(string_array[i]);
		strncpy(&concatenated_string[current_pos], string_array[i], str_length);
		current_pos += str_length;
	
		if (i < num_strings - 1)
		{
			concatenated_string[current_pos] = ' ';
			current_pos += 1;
		}
	}
	concatenated_string[total_length] = '\0';
	return concatenated_string;
}

char **tokenize_alias_arg(char *input_string, size_t *num_tokens)
{
	size_t token_count = 0;
	int within_quotes = 0;
	char *current = input_string;

	while (*current != '\0')
	{
		if (*current == '\'' || *current == '\"')
		{
			within_quotes = !within_quotes;
		}
		else if (*current == ' ' && !within_quotes)
		{
			token_count++;
		}
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

size_t get_distance(const char *first, const char *last)
{
	return (last - first) - 1;
}

int is_enclosed(char *string, char c)
{
	char *first = strchr(string, c);
	char *last = strchr(first + 1, c);

	if ((first != NULL && last != NULL) && (first != last))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

