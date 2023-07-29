#include "main.h"

/**
 * string_duplicate - Duplicates a string.
 * @source: Pointer to the source string.
 * Return: Pointer to the duplicated string, or NULL if source is NULL.
 */
char *string_duplicate(char *source)
{
	int source_len = 0, i;
	char *duplicate;

	if (source == NULL)
		return (NULL);

	for (; source[source_len] != '\0'; source_len++)
		;

	duplicate = (char *)malloc(source_len + 1);
	if (duplicate == NULL)
		return (NULL);

	for (i = 0; i < source_len; i++)
		duplicate[i] = source[i];

	duplicate[i] = '\0';

	return (duplicate);
}

/**
 * string_length - Returns the length of a string.
 * @string_0: Pointer to the string.
 * Return: Length of the string.
 */
int string_length(char *string_0)
{
	int length = 0;

	for (; string_0[length] != '\0'; length++)
		;

	return (length);
}

/**
 * string_compare - Compares two strings up to a specified number of characters.
 * @string1: Pointer to the first string.
 * @string2: Pointer to the second string.
 * @num: Number of characters to compare.
 * Return: 0 if the first n characters of string1 are equal to string2,
 * negative if string1 is less than string2, or positive if string1 is greater than str2.
 */
int string_compare(char *string1, char *string2, int num)
{
	for (; num > 0 && *string1 && (*string1 == *string2); num--)
	{
		string1++;
		string2++;
	}

	if (num == 0)
		return (0);
	else
		return ((unsigned char)*string1 - (unsigned char)*string2);
}
