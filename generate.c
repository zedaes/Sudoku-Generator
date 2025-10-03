#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solve.h"


#ifndef SIZE
#define SIZE 9
#endif

void shuffle(int *array, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void generate_full_board(int size, int board[size][size]) {
    int numbers[size];
    for (int i = 0; i < size; i++)
        numbers[i] = i + 1;
    shuffle(numbers, size);

    for (int i = 0; i < size; i++)
        board[0][i] = numbers[i];

    solve_sudoku(size, board);
}

void remove_numbers(int size, int board[size][size], int holes) {
    for (int i = 0; i < holes; i++) {
        int row, col;
        do {
            row = rand() % size;
            col = rand() % size;
        } while (board[row][col] == 0);

        int temp = board[row][col];
        board[row][col] = 0;

        int test_board[size][size];
        for (int r = 0; r < size; r++)
            for (int c = 0; c < size; c++)
                test_board[r][c] = board[r][c];

        if (!solve_sudoku(size, test_board)) {
            board[row][col] = temp;
        }
    }
}

void save_puzzle(FILE *file, int size, int puzzle[size][size], int solution[size][size]) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            fprintf(file, "%d", puzzle[i][j]);
    fprintf(file, ",");

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            fprintf(file, "%d", solution[i][j]);
    fprintf(file, "\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_puzzles>\n", argv[0]);
        return 1;
    }

    int num_puzzles = atoi(argv[1]);
    if (num_puzzles <= 0) {
        printf("Please provide a valid number of puzzles.\n");
        return 1;
    }

    srand(time(NULL));

    FILE *file = fopen("sudoku.csv", "w");
    if (!file) {
        printf("Error opening file!\n");
        return 1;
    }
    fprintf(file, "puzzle,solution\n");

    int puzzle[SIZE][SIZE];
    int solution[SIZE][SIZE];

    for (int i = 0; i < num_puzzles; i++) {
        for (int r = 0; r < SIZE; r++)
            for (int c = 0; c < SIZE; c++) {
                puzzle[r][c] = 0;
                solution[r][c] = 0;
            }

        generate_full_board(SIZE, solution);

        for (int r = 0; r < SIZE; r++)
            for (int c = 0; c < SIZE; c++)
                puzzle[r][c] = solution[r][c];

        remove_numbers(SIZE, puzzle, rand() % (SIZE * 4) + SIZE * 2); // Holes scaled by size

        save_puzzle(file, SIZE, puzzle, solution);
        printf("Generated Sudoku #%d (Size %d)\n", i + 1, SIZE);
    }

    fclose(file);
    printf("Sudoku puzzles saved to sudoku.csv!\n");
    return 0;
}
