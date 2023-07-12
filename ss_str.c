#include "stdsh.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>

/**
 * _strlen - Calculate the length of a string.
 * @str: The input string.
 *
 * Return: The length of the string.
 */
size_t _strlen(const char *str)
{
	size_t length = 0;

	while (str[length] != '\0')
	{
		length++;
	}

	return (length);
}

/**
 * _strdup - Duplicate a string.
 * @str: The input string to duplicate.
 *
 * Return: Pointer to the newly duplicated string.
 */
char *_strdup(const char *str)
{
	size_t len;
	char *s_str;

	if (str == NULL)
	{
		return (NULL);
	}

	len = _strlen(str) + 1;
	s_str = malloc(len);
	if (s_str == NULL)
	{
		return (NULL);
	}

	_memcpy(s_str, str, len);

	return (s_str);
}

/**
 * _strcmp - A function that compares two strings.
 * @s1: first
 * @s2: second
 *
 * Return: int
 */
int _strcmp(const char *s1, const char *s2)
{
	if (s1 == NULL || s2 == NULL)
	{
		return (-1);
	}

	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}

	if (*s1 == '\0' && *s2 == '\0')
	{
		return (0);
	}
	else if (*s1 == '\0')
	{
		if (*s2 == '\n')
			return (0);
		return (-(*s2));
	}
	else
	{
		return (*s1);
	}
}

/**
 * _isspace - Returns true if c is a whitespace characcter
 * @c: Character
 * Return: int
 */
int _isspace(int c)
{
	if (c >= '\t' && c <= '\r')
	{
		return (1);
	}
	else if (c == ' ' || c == '\f')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
/**
 * _strtok - tokenize a string based on delimiters
 * @str: the string to tokenize
 * @delimiters: the delimiters to use for tokenization
 *
 * Return: pointer to the next token, or NULL if no more tokens are found
 */

char *_strtok(char *str, const char *delimiters)
{
	char *token_start = NULL;
	char *token_end = NULL;
	char *current_token = NULL;

	if (str != NULL)
	{
		token_start = str;
	}
	else if (token_start == NULL)
	{
		return (NULL);
	}

	token_end = strpbrk(token_start, delimiters);
	if (token_end != NULL)
	{
		*token_end = '\0';
		current_token = token_start;
		token_start = token_end + 1;
		return (current_token);
	}

	if (*token_start == '\0')
	{
		return (NULL);
	}

	current_token = token_start;
	token_start = NULL;
	return (current_token);
}
