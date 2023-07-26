#include "alias.h"


/**
 * add_alias - Adds an alias to the shell
 * @aliasct: Alias info object
 * @alias: New alias to be added
 * Return: int
*/
int add_alias(alias_ct *aliasct, alias_t alias)
{
	int i;
	int *countPtr = &(aliasct->alias_count);

	for (i = 0; i < ALIAS_MAX_LIMIT; i++)
	{
		if ((strlen(aliasct->aliases[i].name) == 0) ||
			(aliasct->aliases[i].name == NULL))
		{
			aliasct->aliases[i] = alias;
			(*countPtr)++;
			break;
		}
	}
	return (SS_OK);
}

/**
 * find_alias - Searches for an alias stored in the shell
 * @aliasct: Alias info object
 * @name: Name of the alias
 * Return: Pointer to the alias if found or NULL
*/
alias_t *find_alias(alias_ct *aliasct, char *name)
{
	int i;
	int count = aliasct->alias_count;

	for (i = 0; i < count; i++)
	{
		if (strcmp((aliasct->aliases)[i].name, name) == 0)
		{
			return (&aliasct->aliases[i]);
		}
	}
	return (NULL);
}


/**
 * print_aliases - Prints all aliases
 * @alias_info: Alias info object
*/
void print_aliases(alias_ct *alias_info)
{
	int i;
	int count = alias_info->alias_count;

	for (i = 0; i < count; i++)
	{
		printf("alias %s=\'%s\'\n", alias_info->aliases[i].name,
			alias_info->aliases[i].value);
	}
}

/**
 * create_alias - Creates an alias object
 * @arg: String argument
 * Return: An alias object
*/
alias_t create_alias(char *arg)
{
	alias_t new_alias;
	char *value, *eq, *singlestart, *doublestart;
	char buffer[225];

	memset(&new_alias, 0, sizeof(alias_t));
	if (arg == NULL || strlen(arg) == 0)
		return (new_alias);
	eq = strchr(arg, '=');

	if (eq != NULL)
	{
		strncpy(new_alias.name, arg, (eq - arg));
	}
	else
	{
		strcpy(new_alias.name, arg);
		strcpy(new_alias.value, "");
		return (new_alias);
	}
	value = eq + 1;

	if (value != NULL)
		strncpy(new_alias.name, arg, (eq - arg));
	singlestart = strchr(eq + 1, '\'');
	doublestart = strchr(eq + 1, '\"');

	if (singlestart != NULL && is_enclosed(singlestart, '\'') == 0)
	{
		get_enclosed_string(singlestart, buffer, '\'');
		strcpy(new_alias.value, buffer);
		return (new_alias);
	}
	else if (doublestart != NULL && is_enclosed(doublestart, '\"') == 0)
	{
		get_enclosed_string(doublestart, buffer, '\"');
		strcpy(new_alias.value, buffer);
		return (new_alias);
	}
	strcpy(new_alias.value, value);
	return (new_alias);
}


/**
 * set_alias - Overwrites and existing alias
 * @aliasct: Alias info object
 * @alias: Alias object with existing name and new value
 * Return: int
*/
int set_alias(alias_ct *aliasct, alias_t alias)
{
	int i;
	int count = aliasct->alias_count;

	for (i = 0; i < count; i++)
	{
		if (strcmp(aliasct->aliases[i].name, alias.name) == 0)
		{
			aliasct->aliases[i] = alias;
			return (0);
		}
	}
	return (1);
}
