#include "simple_shell.h"

/**
 * main - Entry point
 * @argc: Argument count
 * @argv:  Array of program arguments
 * Return: Always 0.
 */

int main(int argc, char **argv)
{
	int status = 0;
	shell_t *shell = NULL;

	init_shell(&shell, argc, argv);
	init_cmd_list(&(shell->internal_cmd_list));
	populate_commands(&(shell->internal_cmd_list));
	main_loop(shell);
	cleanup(shell);

	return (status);
}
