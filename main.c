#include "simple_shell.h"
#include "stdsh.h"

/**
 * main - Entry point
 * Return: Always 0.
 */

int main(void)
{
	int status = 0;
	shell_t *shell = NULL;

	init_shell(&shell);
	init_cmd_list(&(shell->internal_cmd_list));
	populate_commands(&(shell->internal_cmd_list));
	main_loop(shell);
	cleanup(shell);

	return (status);
}
