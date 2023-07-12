#!/bin/bash
clear
printf "simple_shell v0.2\n"


if [ "$1" = "--debug:build" ]; then
    gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -fsanitize=address *.c -o shell
elif [ "$1" = "--debug:run" ]; then
    gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -fsanitize=address *.c -o shell
    if [ $? -eq 0 ]; then
        ./shell
    fi
elif [ "$1" = "--check" ]; then
    betty *.h *.c
elif [ "$1" = "--clean" ]; then
    rm -rf build shell
else
    gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o shell
    if [ $? -eq 0 ]; then
        ./shell
    fi
fi

