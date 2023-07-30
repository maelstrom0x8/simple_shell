#include "simple_shell.h"



/**
 * _non_interactive - This function is handles the input in the
 * non-intercative mode
 * @shell: Global shell object
*/
void _non_interactive(shell_t *shell)
{
	int result;
	size_t n = 0;

	while (getline(&(shell->input), &n, stdin) != -1)
	{
		result = parse_command(shell);

		if (shell->input != NULL)
		{
			free(shell->input);
			shell->input = NULL;
		}
	}

	exit(result);
}
