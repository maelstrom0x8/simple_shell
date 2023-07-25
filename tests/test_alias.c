#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <execinfo.h>

#include "simple_shell.h"
#include "shutils.h"

shell_t *shell;

void __attribute__((constructor)) before_all()
{
	init_shell(&shell);
}

void __attribute__((destructor)) after_all()
{
	cleanup(shell);
}

void test_should_create_alias_with_valid_args()
{
	alias_t a1 = create_alias("ls='ls --color-auto'");
	alias_t a2 = create_alias("g=./gradlew");
	alias_t a3 = create_alias("mvn");
	alias_t a4 = create_alias("kafka-topics=\"/usr/bin/kafka-topics --bootstrap-server localhost:9092\"");
	alias_t a5 = create_alias("");

	assert((strcmp(a1.name, "ls") == 0) && (strcmp(a1.value, "ls --color-auto") == 0));
	assert((strcmp(a2.name, "g") == 0) && (strcmp(a2.value, "./gradlew") == 0));
	assert((strcmp(a3.name, "mvn") == 0));
	assert(strcmp(a3.value, "") == 0);
	assert((strcmp(a4.name, "kafka-topics") == 0));
	assert(strcmp(a4.value, "/usr/bin/kafka-topics --bootstrap-server localhost:9092") == 0);
	assert((strcmp(a5.name, "") == 0) && (strcmp(a5.value, "") == 0));
}

void test_should_add_new_alias()
{
	alias_ct *aliases = &(shell->alias);

	alias_t a1 = create_alias("ls=ls -la");
	alias_t a2 = create_alias("g=./gradlew");
	add_alias(aliases, a1);
	add_alias(aliases, a2);

	alias_t *aa1 = find_alias(aliases, "ls");

	assert(aa1 != NULL);
	assert(strcmp(aa1->name, "ls") == 0);
	assert(strcmp(aa1->value, "ls -la") == 0);
	assert(aliases->alias_count == 2);
}

void test_should_set_existing_alias()
{
	char *arg = "key=\"value --og-curve -b\"";
	char *q1 = strchr(arg, '\"');
	char *q2 = strchr(q1 + 1, '\"');
	assert(q1 != NULL);
	assert(q2 != NULL);
	size_t len = get_distance(q1, q2);
	int N = len + 1;
	char value[N];
	char *start = q1 + 1;
	int i = 0;
	while (start != q2)
	{
		value[i] = *start;
		i++;
		start++;
	}
	value[i] = '\0';
	assert(strcmp(value, "value --og-curve -b") == 0);
}

void test_should_return_correct_alias_or_null()
{
	char *f = "'hello sasc";
	char *g = "\"mvn clean\"";
	assert(is_enclosed(f, '\'') == 1);
	assert(is_enclosed(g, '\"') == 0);
}

void test_should_create_valid_alias_from_cli_arg()
{
	

}

int main(void)
{
	// test_should_create_alias_with_valid_args();
	// test_should_add_new_alias();
	// test_should_set_existing_alias();
	// test_should_return_correct_alias_or_null();

	test_should_create_valid_alias_from_cli_arg();
}
