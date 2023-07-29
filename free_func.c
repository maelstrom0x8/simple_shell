#include "main.h"
/**
 * free_everything - function that frees all allocated memory
 * that needed to be free
 * @buffer: buffer where getline stocks the commands
 * @point_tt: pointer to character
 * @arg: array of pointers to character
 * Return: None
 */
void free_everything(char *buffer, char *point_tt, char **arg)
{
	free(buffer);
	free(point_tt);
	freeargum(arg);
}
/**
 * freeargum - function that frees the array of commands
 * @arg: array of pointers to character
 * Return: None
 */
void freeargum(char **arg)
{
	int j;

	if (arg == NULL)
		exit(EXIT_FAILURE);
	for (j = 0; arg[j] != NULL; j++)
		free(arg[j]);
	free(arg);
}

