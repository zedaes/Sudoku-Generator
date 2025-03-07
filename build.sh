
#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: ./build.sh <number_of_puzzles>"
    exit 1
fi

gcc generate.c -o generate -O2

./generate $1