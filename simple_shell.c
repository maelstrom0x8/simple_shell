#include <stdio.h>
#include <unistd.h>

#include "command.h"
#include "shutils.h"
#include "simple_shell.h"

/**
 * init_shell - Initializes the shell object
 * @shell: Shell object
 * @argc: Argument count
 * @argv: Array of shell arguments
 */
void init_shell(shell_t **shell, int argc, char **argv)
{
	int i;

	UNUSED(argc);
	*shell = (shell_t *)malloc(sizeof(shell_t));
	(*shell)->close = 0;
	(*shell)->input = NULL;
	(*shell)->internal_cmd_list = NULL;
	for (i = 0; i < ALIAS_MAX_LIMIT; i++)
	{
		_strcpy((*shell)->alias.aliases[i].name, "");
		_strcpy((*shell)->alias.aliases[i].value, "");
	}
	_strcpy((*shell)->prompt, argv[0]);
}

/**
 * main_loop - Program loop
 * @shell: Shell object
 * Return: Status
 */
int main_loop(shell_t *shell)
{
	int status;

	while (1)
	{
		if (!isatty(STDIN_FILENO))
		{
			_non_interactive(shell);
			break;
		}
		else
		{
			_puts(shell->prompt);
			_puts("$ ");
			fflush(stdout);
			status = render_shell(shell);
		}
		if (status != SS_EXIT)
			continue;
		else
			break;
	}

	return (status);
}

/**
 * cleanup - Clear up shell
 * @shell: Shell object
 */
void cleanup(shell_t *shell)
{

	clear_commands(shell->internal_cmd_list);
	_free(shell->internal_cmd_list);
	free(shell);
}

/**
 * render_shell - Execute the core logic of the simple_shell
 * @shell: Shell object
 * Description: This function prompts
 * for user input, reads the input from stdin,
 * and processes the command using
 * the parse_command function.
 *
 * Return: Returns the result of the parse_command function.
 *         SS_EXIT if the end-of-file indicator is reached in stdin.
 *         The status returned by the parse_command function otherwise.
 */

int render_shell(shell_t *shell)
{
	size_t n = 0;
	int result;

	getline(&(shell->input), &n, stdin);
	if (feof(stdin))
	{
		free(shell->input);
		_puts("\n");
		return (SS_EXIT);
	}

	result = parse_command(shell);

	if (shell->input != NULL)
	{
		free(shell->input);
		shell->input = NULL;
	}

	return (result);
}

/**
 * parse_command - Parse input command
 * @shell: Shell object
 *
 * Description: This function parses the input command, trims and sanitizes it,
 * tokenizes the arguments, and executes the command.
 *
 * Return: Returns the status of the command execution.
 *         SS_CLOSE if the input is empty or newline.
 *         SS_EOF if an error occurs during tokenization.
 *         The status returned by the run_command function otherwise.
 */
int parse_command(shell_t *shell)
{
	char **args = NULL;
	int status = 0;
	int i;
	char *delim_space;
	int num_tokens = 0;

	trim_input(shell->input);
	sanitize_input(shell->input);

	if (!shell->input || shell->input[0] == '\0' || shell->input[0] == '\n')
		return (SS_CLOSE);

	delim_space = _strchr(shell->input, ' ');

	if (_strncmp(shell->input, "alias", 5) == 0)
	{
		if (delim_space)
			return (handle_builtin_alias(shell, delim_space + 1));
		else
			return (handle_builtin_alias(shell, NULL));
	}

	args = tokenize_args(shell->input, &num_tokens);
	if (args == NULL)
		return (SS_EOF);

	status = run_command(shell, args);

	free(shell->input);
	shell->input = NULL;

	for (i = 0; i < num_tokens; i++)
	{
		free(args[i]);
		args[i] = NULL;
	}
	free(args);
	args = NULL;
	return (status);
}
