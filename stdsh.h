#ifndef STDSH_H_
#define STDSH_H_

#include <stdio.h>
#include <stdlib.h>
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

#endif
