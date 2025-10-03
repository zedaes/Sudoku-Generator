#!/bin/bash

SIZE=${2:-9}

if [ -z "$1" ]; then
    echo "Usage: ./build.sh <number_of_puzzles> [sudoku_size]"
    exit 1
fi

gcc -o generate -O2 -DSIZE=$SIZE generate.c solve.c -lm

./generate "$1"
