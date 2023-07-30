#include "shutils.h"


/**
 * _memcpy - Copy memory from source to destination
 * @dest: Pointer to the destination memory
 * @src: Pointer to the source memory
 * @n: Number of bytes to copy
 *
 * Return: Pointer to the destination memory
 */

void *_memcpy(void *dest, const void *src, size_t n)
{
	char *dest_ptr = (char *)dest;
	const char *src_ptr = (const char *)src;
	size_t i;

	for (i = 0; i < n; i++)
	{
		dest_ptr[i] = src_ptr[i];
	}

	return (dest);
}

/**
 * _feof - Checks EOF status
 * Return: int
 */

int _feof(void)
{
	int c = fgetc(stdin);

	if (c == EOF)
	{
		return (1);
	}
	else
	{
		ungetc(c, stdin);
		return (0);
	}
}

/**
 * _free - Deallocates memory
 * @ptr: Pointer
 */
void _free(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
	}
}


/**
 * _strcpy -  function that copies the string pointed to by src, including
 * the terminating null byte (\0), to the buffer pointed to by dest.
 * @dest: The destination
 * @src: The source
 *
 * Return: void
 */
char *_strcpy(char *dest, const char *src)
{
	char *start = dest;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';

	return (start);
}
