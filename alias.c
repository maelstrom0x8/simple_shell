#include "simple_shell.h"

#include <assert.h>

alias_t create_alias(char *arg)
{
	alias_t new_alias;
	memset(&new_alias, 0, sizeof(alias_t));

	if (arg == NULL || strlen(arg) == 0)
	{
		return new_alias;
	}

	// Check for single quotes
	char *single_quote = strchr(arg, '\'');
	// Check for double quotes
	char *double_quote = strchr(arg, '\"');
	// Check for equal sign
	char *equal_sign = strchr(arg, '=');

	if (single_quote != NULL && double_quote != NULL)
	{
		// If both single and double quotes are present, handle the one that comes first
		if (single_quote < double_quote)
		{
			single_quote = NULL;
		}
		else
		{
			double_quote = NULL;
		}
	}

	if (single_quote != NULL)
	{
		// If single quotes are found, extract the value between the single quotes
		char *value_start = single_quote + 1;
		char *value_end = strchr(value_start, '\'');

		if (value_end != NULL)
		{
			size_t value_len = value_end - value_start;
			strncpy(new_alias.value, value_start, value_len);
		}

		// Check if the equal sign appears before the single quote and if there is a key
		if (equal_sign != NULL && equal_sign < single_quote)
		{
			size_t key_len = equal_sign - arg;
			strncpy(new_alias.name, arg, key_len);
		}
	}
	else if (double_quote != NULL)
	{
		// If double quotes are found, extract the value between the double quotes
		char *value_start = double_quote + 1;
		char *value_end = strchr(value_start, '\"');

		if (value_end != NULL)
		{
			size_t value_len = value_end - value_start;
			strncpy(new_alias.value, value_start, value_len);
		}

		// Check if the equal sign appears before the double quote and if there is a key
		if (equal_sign != NULL && equal_sign < double_quote)
		{
			size_t key_len = equal_sign - arg;
			strncpy(new_alias.name, arg, key_len);
		}
	}
	else if (equal_sign != NULL)
	{
		// If no quotes are found but the equal sign is present, it's a key=value string
		size_t key_len = equal_sign - arg;
		size_t value_len = strlen(equal_sign + 1);

		strncpy(new_alias.name, arg, key_len);
		strncpy(new_alias.value, equal_sign + 1, value_len);
	}
	else
	{
		strncpy(new_alias.name, arg, sizeof(new_alias.name) - 1);
		strncpy(new_alias.value, "null", 5);
	}

	return new_alias;
}

int is_pair(char *pair)
{
	char *delim = strchr(pair, '=');
	if (delim != NULL)
		return 0;
	return 1;
}

int set_alias(alias_ct *aliasCt, alias_t alias)
{
	int count = aliasCt->alias_count;
	for (int i = 0; i < count; i++)
	{
		if (strcmp(aliasCt->aliases[i].name, alias.name) == 0)
		{
			aliasCt->aliases[i] = alias;
			return 0;
		}
	}
	return -1;
}

int add_alias(alias_ct *aliasCt, alias_t alias)
{
	int *countPtr = &(aliasCt->alias_count);
	for (int i = 0; i < ALIAS_MAX_LIMIT; i++)
	{
		if ((strlen(aliasCt->aliases[i].name) == 0) || (aliasCt->aliases[i].name == NULL))
		{
			aliasCt->aliases[i] = alias;
			(*countPtr)++;
			break;
		}
	}
	return SS_OK;
}

alias_t *find_alias(alias_ct *aliasCt, char *name)
{
	int count = aliasCt->alias_count;
	for (int i = 0; i < count; i++)
	{
		if (strcmp((aliasCt->aliases)[i].name, name) == 0)
		{
			return &aliasCt->aliases[i];
		}
		return NULL;
	}
}

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

void print_aliases(alias_ct *alias_info)
{
	int count = alias_info->alias_count;
	for (int i = 0; i < count; i++)
	{
		printf("alias %s=\'%s\'\n", alias_info->aliases[i].name, alias_info->aliases[i].value);
	}
}
