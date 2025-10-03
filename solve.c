#include <stdbool.h>
#include <math.h>
#include "solve.h"

#ifndef SIZE
#define SIZE 9
#endif

bool is_valid(int size, int board[size][size], int row, int col, int num) {
    for (int i = 0; i < size; i++) {
        if (board[row][i] == num || board[i][col] == num)
            return false;
    }
    int boxSize = 3;
    if (size != 9) {
        boxSize = (int)(sqrt((double)size));
    }
    int startRow = (row / boxSize) * boxSize;
    int startCol = (col / boxSize) * boxSize;
    for (int i = 0; i < boxSize; i++) {
        for (int j = 0; j < boxSize; j++) {
            if (board[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }
    return true;
}

bool solve_sudoku(int size, int board[size][size]) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= size; num++) {
                    if (is_valid(size, board, row, col, num)) {
                        board[row][col] = num;
                        if (solve_sudoku(size, board))
                            return true;
                        board[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}
