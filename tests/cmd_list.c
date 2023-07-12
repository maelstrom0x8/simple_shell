#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "command.h"

int function_one(char **args)
{
	return 0;
}

int function_two(char **args)
{
	return 0;
}

int function_three(char **args)
{
	return 0;
}

void test_init_list()
{
	cmd_list_t *list;

	init_cmd_list(&list);
	assert(list != NULL);
	assert(list->size == 0);
	assert(list->head == NULL);

	free(list);
}

void test_insert_command()
{
	cmd_list_t *list;
	icmd_mapping cmd = {"cmd", function_one};

	int init_status = init_cmd_list(&list);
	add_command(list, "cmd", function_one);

	assert(init_status == 0);
	assert(list->head != NULL);
	assert(cmd_list_size(list) == 1);

	clear_commands(list);
	free(list);
}

void test_search_command()
{
	cmd_list_t *list;

	int init_status = init_cmd_list(&list);
	add_command(list, "cmd", function_one);

	icmd_mapping *k = find_command(list, "cmd");

	assert(init_status == 0);
	assert(k != NULL);
	assert(cmd_list_size(list) == 1);
	assert(strcmp("cmd", k->command) == 0);
	assert(k->function == function_one);

	clear_commands(list);
	free(list);
}

void test_populate_default_commands()
{
	cmd_list_t *list;

	init_cmd_list(&list);
	populate_commands(&list);

	assert(cmd_list_size(list) == 4);

	clear_commands(list);
	free(list);
}

void test_clear_populated_commands()
{
	cmd_list_t *list;
	init_cmd_list(&list);
	populate_commands(&list);

	clear_commands(list);

	assert(cmd_list_size(list) == 0);
	free(list);
}

void test_find_and_exec_command()
{
	cmd_list_t *list;
	init_cmd_list(&list);
	populate_commands(&list);

	icmd_mapping *env = find_command(list, "env");
	icmd_mapping *exit = find_command(list, "exit");

	assert(strcmp(env->command, "env") == 0);
	assert(env->function == printenv);

	assert(strcmp(env->command, "exit") == 0);
	assert(env->function == terminate);

	clear_commands(list);
	free(list);
}

int main(void)
{

	test_init_list();
	test_insert_command();
	test_search_command();
	test_populate_default_commands();
	test_clear_populated_commands();

	return 0;
}