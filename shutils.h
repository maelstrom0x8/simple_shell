#ifndef SHUTILS_H
#define SHUTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

char *_strcpy(char *s1, const char *s2);

char *_strdup(const char *str);

int _strncmp(const char *s1, const char *s2, int nbytes);

char *_strtok(char *str, const char *delimiters);

char *_strncpy(char *dest, char *src, int n);

char *_strpbrk(char *s, char *accept);

void *_memset(void *block, int c, size_t n);

char *_strchr(char *s, char c);

char **tokenize_args(char *args, int *num_tokens);

char *check_path(char *cmd);

int _feof(void);

int _isspace(int c);

int _putchar(char c);

int _strcmp(const char *s1, const char *s2);

int count_tokens(char *line);

int is_absolute(char *path);

size_t _strlen(const char *str);

ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

void _free(void *ptr);

void _puts(const char *string);

void *_memcpy(void *dest, const void *src, size_t n);

void sanitize_input(char *input);

void trim_input(char *input);


#endif
