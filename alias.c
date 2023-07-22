#include "simple_shell.h"



alias_t create_alias(char *arg)
{
	alias_t new_alias;
	memset(&new_alias, 0, sizeof(alias_t));

	if (arg == NULL || strlen(arg) == 0)
	{
		return new_alias;
	}

	char *equal_sign = strchr(arg, '=');

	if (equal_sign != NULL)
	{
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
	int count = aliasCt->alias_count;
	for (int i = 0; i < count; i++)
	{
		if (strcmp(aliasCt->aliases[i].name, "") == 0)
		{
			aliasCt->aliases[i] = alias;
			aliasCt->alias_count++;
		}
	}
	return 0;
}


alias_t *find_alias(alias_ct *aliasCt, char *name)
{
	for (int i = 0; i < aliasCt->alias_count; i++)
	{
		printf("Searching aliases 0/%d\n", aliasCt->alias_count);
		if (strcmp((aliasCt->aliases)[i].name, name) == 0)
		{
			printf("Found alias %s  = \'%s\'", aliasCt->aliases[i].name, aliasCt->aliases[i].value);
			return &aliasCt->aliases[i];
		}
		return NULL;
	}
}

int print_alias(alias_ct *aliasCt, char *name)
{
	alias_t *alias = find_alias(aliasCt, name);
	char *value;

	if (alias != NULL)
	{
		if (strlen(alias->value) == 0)
			printf("alias %s=\'%s\'\n", alias->name, value);
		printf("alias %s=\'%s\'\n", alias->name, alias->value);
	}
}

void print_aliases(alias_ct *alias_info)
{
	int count = alias_info->alias_count;
	for (int i = 0; i < count; i++)
	{
		printf("alias %s=\'%s\'\n", alias_info->aliases[i].name, alias_info->aliases[i].value);
	}
}
