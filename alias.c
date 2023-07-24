#include "stdsh.h"
#include "simple_shell.h"


size_t get_distance(const char *first, const char *last)
{
	return (last - first) - 1;
}

int is_enclosed(char *string, char c)
{
	char *first = strchr(string, c);
	char *last = strchr(first + 1, c);

	if ((first != NULL && last != NULL) && (last - first) > 0)
		return 0;
	else
		return 1;
}

int get_enclosed_string(char *string, char *buffer, char c)
{
	char *first = strchr(string, c);
	char *last = strchr(first + 1, c);
	size_t len = get_distance(first, last);

	char *begin = first + 1;
	strncpy(buffer, begin, len);
	buffer[len] = '\0';
	return 1;
}

alias_t create_alias(char *arg)
{
	alias_t new_alias;
	memset(&new_alias, 0, sizeof(alias_t));
	char buffer[225];

	if (arg == NULL || strlen(arg) == 0)
		return new_alias;

	char *eq = strchr(arg, '=');
	if (eq != NULL) {
		strncpy(new_alias.name, arg, (eq - arg));
	} else {
		strcpy(new_alias.name, arg);
		strcpy(new_alias.value, "");
		return new_alias;
	}

	char *value = eq + 1;
	if(value != NULL)
	strncpy(new_alias.name, arg, (eq - arg));
	char *singlestart = strchr(eq + 1, '\'');
	char *doublestart = strchr(eq + 1, '\"');

	if (singlestart != NULL && is_enclosed(singlestart, '\'') == 0)
	{
		get_enclosed_string(singlestart, buffer, '\'');
		printf("Got single quoted alias -> %s\n", buffer);
		strcpy(new_alias.value, buffer);
		return new_alias;
	}
	else if (doublestart != NULL && is_enclosed(doublestart, '\"') == 0)
	{
		get_enclosed_string(doublestart, buffer, '\"');
		printf("Got double quoted alias -> %s\n", buffer);
		strcpy(new_alias.value, buffer);
		return new_alias;
	}
	printf("Got unquoted alias -> %s\n", value != NULL? value : buffer );
	strcpy(new_alias.value, value);
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
