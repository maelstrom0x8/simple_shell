# Simple Shell

This is a custom implementation of a simple shell program for Unix-like systems. The program allows you to execute commands and programs from the command line, similar to the built-in shells like bash, zsh, or fish.

## Features
* Supports executing external programs and commands.

## Coming Soon
* Supports built-in commands like cd, exit, and help.
* Supports command-line arguments and redirection (>, <).
* Supports piping commands (|).
* Supports running in interactive or batch mode.

## Usage
To run the shell program, simply compile the source code and run the resulting executable file:

```
$ ./run.sh
```
This will start the shell program in interactive mode, where you can type commands and see the output:
```
$ /bin/echo "Hello, world!"
Hello, world!
$
```
You can also start the the shell in non-interactive mode
```
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```