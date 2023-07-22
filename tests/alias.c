#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "simple_shell.h"

int assert_alias_equals(alias_t *alias, const char *expected_name, const char *expected_value)
{

	if ((strcmp(expected_name, alias->name) != 0) ||
		(strcmp(expected_value, alias->value) != 0))
	{
		fprintf(stderr, "FAILURE: Expected %s=%s but Got %s=%s\n", expected_name, expected_value, alias->name, alias->value);
		exit(EXIT_FAILURE);
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
	assert_alias_equals(&a3, "mvn", "");
	assert_alias_equals(&a4, "kafka-topics", "\'/usr/bin/kafka-topics --bootstrap-server localhost:9092\'");
	assert_alias_equals(&a5, "", "");
}

int main(void)
{
	test_should_create_alias_with_valid_args();
}
