#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solve.c" 

void shuffle(int *array, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void generate_full_board(int board[SIZE][SIZE]) {
    int numbers[SIZE];
    for (int i = 0; i < SIZE; i++) numbers[i] = i + 1;
    shuffle(numbers, SIZE);

    for (int i = 0; i < SIZE; i++) {
        board[0][i] = numbers[i];
    }

    solve_sudoku(board);
}

void remove_numbers(int board[SIZE][SIZE], int holes) {
    for (int i = 0; i < holes; i++) {
        int row, col;
        do {
            row = rand() % SIZE;
            col = rand() % SIZE;
        } while (board[row][col] == 0);

        int temp = board[row][col];
        board[row][col] = 0;

        int test_board[SIZE][SIZE];
        for (int r = 0; r < SIZE; r++)
            for (int c = 0; c < SIZE; c++)
                test_board[r][c] = board[r][c];

        if (!solve_sudoku(test_board)) {
            board[row][col] = temp;
        }
    }
}

void save_puzzle(FILE *file, int puzzle[SIZE][SIZE], int solution[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            fprintf(file, "%d", puzzle[i][j]);
    
    fprintf(file, ",");

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            fprintf(file, "%d", solution[i][j]);
    
    fprintf(file, "\n");
}

int main() {
    srand(time(NULL));
    FILE *file = fopen("sudoku.csv", "w");
    if (!file) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(file, "puzzle,solution\n");

    int puzzle[SIZE][SIZE] = {0}, solution[SIZE][SIZE] = {0};

    for (int i = 0; i < 100; i++) {  // Change this number to the number of sudokus you want to generate
        generate_full_board(solution);
        for (int r = 0; r < SIZE; r++)
            for (int c = 0; c < SIZE; c++)
                puzzle[r][c] = solution[r][c];

        remove_numbers(puzzle, rand() % 40 + 20);  

        save_puzzle(file, puzzle, solution);
        printf("Generated Sudoku #%d\n", i + 1);
    }

    fclose(file);
    printf("Sudoku puzzles saved to sudoku.csv!\n");
    return 0;
}
