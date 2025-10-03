#ifndef SOLVE_H
#define SOLVE_H

#include <stdbool.h>

#ifndef SIZE
#define SIZE 9
#endif

bool solve_sudoku(int size, int board[size][size]);
bool is_valid(int size, int board[size][size], int row, int col, int num);

#endif
