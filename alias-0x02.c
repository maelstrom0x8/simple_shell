#include "alias.h"


/**
 * get_enclosed_string - Gets the string enclosed in the
 * specified character
 * @string: String
 * @buffer: Buffer to store the extracted result
 * @c: Character
 * Return: int
*/
int get_enclosed_string(char *string, char *buffer, char c)
{
	char *first = strchr(string, c);
	char *last = strchr(first + 1, c);
	size_t len = get_distance(first, last);

	char *begin = first + 1;

	strncpy(buffer, begin, len);
	buffer[len] = '\0';
	return (1);
}

/**
 * is_pair - Checks if a string is in the form key=value
 * @pair: String
 * Return: int
*/
int is_pair(char *pair)
{
	char *delim = strchr(pair, '=');

	if (delim != NULL)
		return (0);
	return (1);
}
