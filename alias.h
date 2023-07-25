#ifndef ALIAS_H
#define ALIAS_H

#include <stdlib.h>
#include "types.h"



alias_t *find_alias(alias_ct *aliasCt, char *name);

alias_t create_alias(char *arg);

char **tokenize_alias_arg(char *input_string, size_t *num_tokens);

char *concatenate_strings(char **string_array, size_t num_strings);

int add_alias(alias_ct *aliasCt, alias_t alias);

int get_enclosed_string(char *string, char *buffer, char c);

int is_enclosed(char *string, char c);

int is_pair(char *pair);

int print_alias(alias_ct *aliasCt, char *name);

int set_alias(alias_ct *aliasCt, alias_t alias);

size_t get_distance(const char *first, const char *last);

void print_aliases(alias_ct *alias_info);

#endif
