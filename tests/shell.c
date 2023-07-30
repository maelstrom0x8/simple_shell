#include <assert.h>

#include "simple_shell.h"

void test_init_shell()
{
	shell_t *shell = NULL;
	init_shell(&shell);

	assert(shell != NULL);
	assert(shell->close == 0);
	assert(shell->input == NULL);
	assert(shell->internal_cmd_list == NULL);

	free(shell);
}

int main()
{

	test_init_shell();

	return 0;
}
