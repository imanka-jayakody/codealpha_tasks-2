#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function declarations
void printGrid(const vector<vector<int>>& grid);
bool isSafe(const vector<vector<int>>& grid, int row, int col, int num);
bool findEmptyCell(const vector<vector<int>>& grid, int& row, int& col);
bool solveSudoku(vector<vector<int>>& grid);
void generateSudoku(vector<vector<int>>& grid, int size);

// Function to print the Sudoku grid
void printGrid(const vector<vector<int>>& grid) {
    int N = grid.size();
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if a number can be placed in a cell
bool isSafe(const vector<vector<int>>& grid, int row, int col, int num) {
    int N = grid.size();
    // Check row and column
    for (int i = 0; i < N; ++i) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }

    // Check subgrid
    int sqrtN = sqrt(N);
    int startRow = row - row % sqrtN;
    int startCol = col - col % sqrtN;
    for (int i = 0; i < sqrtN; ++i) {
        for (int j = 0; j < sqrtN; ++j) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to find an empty cell
bool findEmptyCell(const vector<vector<int>>& grid, int& row, int& col) {
    int N = grid.size();
    for (row = 0; row < N; ++row) {
        for (col = 0; col < N; ++col) {
            if (grid[row][col] == 0) {
                return true; // Empty cell found
            }
        }
    }
    return false; // No empty cell found
}

// Function to solve Sudoku
bool solveSudoku(vector<vector<int>>& grid) {
    int row, col;

    // Check for empty cell
    if (!findEmptyCell(grid, row, col)) {
        return true; // No empty cell, puzzle solved
    }

    int N = grid.size();
    // Try different numbers in the cell
    for (int num = 1; num <= N; ++num) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid)) {
                return true;
            }

            grid[row][col] = 0; // Backtrack
        }
    }

    return false; // No solution found
}

// Function to generate a valid Sudoku puzzle of given size
void generateSudoku(vector<vector<int>>& grid, int size) {
    srand(time(NULL));

    // Fill the diagonal with random values
    for (int i = 0; i < size; ++i) {
        int num = rand() % size + 1;
        while (!isSafe(grid, i, i, num)) {
            num = rand() % size + 1;
        }
        grid[i][i] = num;
    }

    // Solve the puzzle
    solveSudoku(grid);
}

int main() {
    int size;
    string difficulty;
    char choice;

    do {
        cout << "Select difficulty level (easy, medium, hard): ";
        cin >> difficulty;

        if (difficulty == "easy") {
            size = 4;
        } else if (difficulty == "medium") {
            size = 9;
        } else if (difficulty == "hard") {
            size = 16;
        } else {
            cout << "Invalid difficulty level.\n";
            continue;
        }

        vector<vector<int>> grid(size, vector<int>(size, 0));
        generateSudoku(grid, size);

        if (solveSudoku(grid)) {
            cout << "Sudoku puzzle solved:\n";
            printGrid(grid);
        } else {
            cout << "No solution exists for the given Sudoku puzzle.\n";
        }

        cout << "Do you want to continue playing? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    cout << "Thanks for playing Sudoku!\n";

    return 0;
}
