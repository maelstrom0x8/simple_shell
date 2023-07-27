#!/bin/bash
clear


if [ "$1" = "--debug:build" ]; then
    gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -fsanitize=address *.c -o build/shell
elif [ "$1" = "--debug:run" ]; then
    gcc -Wall -Werror -Wextra -pedantic -std=gnu11 -fsanitize=address *.c -o build/shell
    if [ $? -eq 0 ]; then
        ./build/shell
    fi
elif [ "$1" = "--check" ]; then
    betty *.h *.c
elif [ "$1" = "--clean" ]; then
    rm -rf build
else
    gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o build/shell
    if [ $? -eq 0 ]; then
        ./build/shell
    fi
fi

