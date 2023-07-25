#include "alias.h"

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

int is_pair(char *pair)
{
	char *delim = strchr(pair, '=');
	if (delim != NULL)
		return 0;
	return 1;
}
