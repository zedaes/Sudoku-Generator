# Sudoku Generator
## Setup

Make sure you have a C compiler installed (e.g., gcc).

Clone this repository:
```bash
git clone https://github.com/zedaes/Sudoku-Generator.git
```

Make the build script executable:
```bash
chmod +x build.sh
```

## How to Run

Run the generator by calling the build script with the number of Sudoku puzzles you want to generate as the first argument. Optionally, specify the Sudoku size (default is 9):

```bash
./build.sh <number_of_puzzles> [sudoku_size]
```

Example: Generate 100 standard 9x9 puzzles:
```bash
./build.sh 100
```

Example: Generate 10 puzzles of size 16x16 (if supported):
```bash
./build.sh 10 16
```

The puzzles and their solutions will be saved in a file named `sudoku.csv` with two columns: one for the puzzle and one for the solution.