#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
extern char **environ;
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *string_duplicate(char *source);
int string_length(char *string_0);
int string_compare(char *string1, char *string2, int num);
char *copy_buffer(char *buffer, size_t size);
char *int_to_string(int num);
void print_not_found_error(char **av, char **arg, int i);
void envirem(char **arg, char *buffer, char *p, int n, char **av, int num);
void _puts(char *strg, int iden);
void handle_envirem(char *buffer);
void execute_command(char **arguments, char *buffer, char *copy_buffer,
char **args_vector, int cmd_index);
int process_command(char *input_buffer, int command_index,
char *command_copy, char **arg_vector);
int count_tokens(char *input_buffer, char *copy_buffer);
char **extract_and_copy_tokens(char *copy_buffer,
int num_tokens, char **original_args);
void handle_path(char *env_copy, char **arg, char *buffer,
int num_tokens, char **arg_vector,
int command_index, char *copy_buffer);
char **extract_tokens(char *copy_buffer, int num_tokens);
void free_everything(char *buffer, char *point_tt, char **arg);
void freeargum(char **arg);
void handle_sharp(char *input_line);
void handle_cd(char **arguments __attribute__((unused)));




#endif
