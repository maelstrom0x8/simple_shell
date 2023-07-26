#include "shutils.h"

/**
 * _strchr - A function that locates a character in a string.
 * @s: A null-terminated string
 * @c: The character to find
 *
 * Return:  The return value is a pointer to the located
 * character, or a null pointer if no match was found.
 */
char *_strchr(char *s, char c)
{
	int i;
	char *res = s;

	for (i = 0; *s != '\0'; ++i)
	{
		res = s;
		if (*res == c)
			return (res);
		++s;
	}
	if (c == '\0')
	{
		return (s);
	}
	return ('\0');

}


/**
 * *_memset - This function copies the value of b (converted to
 * an unsigned char) into each of the first size bytes of the
 * object beginning at s. It returns the value of s.
 * Description:  Fills memory with a constant byte
 * @block: the block of memory
 * @c: value to copy
 * @n: size of bytes to copy
 *
 * Return: string
 */
void *_memset(void *block, int c, size_t n)
{
	size_t i;

	unsigned char *block_ptr = (unsigned char *)block;
	unsigned char value = (unsigned char)c;

	for (i = 0; i < n; i++)
	{
		block_ptr[i] = value;
	}

	return (block);
}

/**
 * _strpbrk - A function that searches a string for any of a set of bytes.
 * @s: string
 * @accept: stop set
 * Return: returns a pointer to the first character
 * in string that is a member of the set stopset
 */
char *_strpbrk(char *s, char *accept)
{
	char *res;
	char *ax;

	for (res = s; *res != '\0'; ++res)
	{
		char beg = *res;

		for (ax = accept; *ax != '\0'; ++ax)
		{
			if (*ax == beg)
			{
				return (res);
			}
		}
	}

	return (NULL);
}
