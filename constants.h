#ifndef CONSTANTS_H
#define CONSTANTS_H

#define PROGRAM_NAME "hsh"
#define DEFAULT_PROMPT "($) "
#define ALIAS_MAX_LIMIT 1024
#define SS_OK 0
#define SS_NOEXIST 1
#define SS_EXIT 2
#define SS_CLOSE 3
#define SS_EOF 65280

#define MAX_ARGS 1024
#define MAX_CMD_LEN 1024

extern char **environ;

#endif
