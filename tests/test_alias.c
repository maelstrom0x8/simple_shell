#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <execinfo.h>

#include "simple_shell.h"

shell_t *shell;

void print_stacktrace()
{
	void *arr[10];
	char **strings;
	int size, i;

	size = backtrace(arr, 10);
	strings = backtrace_symbols(arr, size);
	if (strings != NULL)
	{
		for (i = 0; i < size; i++)
			printf("%s\n", strings[i]);
		printf("\n");
	}

	free(strings);
}

void __attribute__((constructor)) before_all()
{
	init_shell(&shell);
}

void __attribute__((destructor)) after_all()
{
	cleanup(shell);
}

int assert_alias_equals(alias_t *alias, const char *expected_name, const char *expected_value)
{

	if ((strcmp(expected_name, alias->name) != 0) ||
		(strcmp(expected_value, alias->value) != 0))
	{
		fprintf(stderr, "FAILURE: Expected %s=%s but Got %s=%s\n", expected_name, expected_value, alias->name, alias->value);
		print_stacktrace();
		// exit(EXIT_FAILURE);
	}
	return 0;
}

void test_should_create_alias_with_valid_args()
{
	alias_t a1 = create_alias("ls=ls -la");
	alias_t a2 = create_alias("g=./gradlew");
	alias_t a3 = create_alias("mvn");
	alias_t a4 = create_alias("kafka-topics=\'/usr/bin/kafka-topics --bootstrap-server localhost:9092\'");
	alias_t a5 = create_alias("");

	assert_alias_equals(&a1, "ls", "ls -la");
	assert_alias_equals(&a2, "g", "./gradlew");
	assert_alias_equals(&a3, "mvn", "null");
	assert_alias_equals(&a4, "kafka-topics", "\'/usr/bin/kafka-topics --bootstrap-server localhost:9092\'");
	assert_alias_equals(&a5, "", "null");
}

void test_should_add_new_alias()
{
	alias_ct *aliases = &(shell->alias);

	alias_t a1 = create_alias("ls=ls -la");
	alias_t a2 = create_alias("g=./gradlew");
	add_alias(aliases, a1);
	add_alias(aliases, a2);

	alias_t *aa1 = find_alias(aliases, "ls");

	assert(aliases->alias_count == 2);
	assert(strcmp(aa1->name, "ls"));
	assert(strcmp(aa1->value, "ls -la"));
	
}

void test_should_set_existing_alias()
{
}

void test_should_return_correct_alias_or_null()
{
}

int main(void)
{
	//test_should_create_alias_with_valid_args();
	test_should_add_new_alias();
	test_should_set_existing_alias();
	test_should_return_correct_alias_or_null();
}
