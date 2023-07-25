#ifndef STDSH_H_
#define STDSH_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <string.h>

ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

char *_strtok(char *str, const char *delimiters);

void *_memcpy(void *dest, const void *src, size_t n);

size_t _strlen(const char *str);

char *_strdup(const char *str);

char *_strcpy(char *s1, const char *s2);

int _strcmp(const char *s1, const char *s2);

void _puts(const char *string);

int _putchar(char c);

int _isspace(int c);

int get_enclosed_string(char *string, char *buffer, char c);

int is_enclosed(char *string, char c);

size_t get_distance(const char *first, const char *last);

char* concatenate_strings(char** string_array, size_t num_strings);

char **tokenize_alias_arg(char *input_string, size_t *num_tokens);

#endif
