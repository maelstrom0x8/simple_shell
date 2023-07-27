#ifndef SIMPLE_SH_H
#define SIMPLE_SH_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "command.h"
#include "constants.h"
#include "types.h"


void init_shell(shell_t **shell, int argc, char **argv);

int main_loop(shell_t *shell);

void cleanup(shell_t *shell);

int render_shell(shell_t *shell);



#endif
