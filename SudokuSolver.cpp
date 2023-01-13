// Sudoku Solver Using Backtracking
#include <bits/stdc++.h>
using namespace std;

// for empty cells in sudoku grid
#define EMPTYCELLS 0

// N is used for the size of Sudoku grid.
#define N 9

// This function finds an entry in grid which is empty
bool FindEMPTYCELLS(int grid[N][N],
                            int &row, int &col);

// bool indicates whether legal to assign num to given row, col
bool isSafe(int grid[N][N], int row,
            int col, int num);


/* Input is partially filled grid and this functions 
tries to assign way in empty cell to get solution of sudoku
*/
bool SolveSudoku(int grid[N][N])
{
    int row, col;

    // If there is no empty cells,  we are done
    if (!FindEMPTYCELLS(grid, row, col))
        // success!
        return true;

    // Consider digits 1 to 9
    for (int num = 1; num <= 9; num++)
    {

        // Check if looks promising
        if (isSafe(grid, row, col, num))
        {

            // tentative assignment
            grid[row][col] = num;

            // Return, if success
            if (SolveSudoku(grid))
                return true;

            // Failure, unmake & try again
            grid[row][col] = EMPTYCELLS;
        }
    }

    // This triggers backtracking
    return false;
}

/* bool returns check whether there is still empty cells, no empty cells false is returned*/
bool FindEMPTYCELLS(int grid[N][N],
                            int &row, int &col)
{
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == EMPTYCELLS)
                return true;
    return false;
}

/* Returns a boolean indicates whether
an assigned entry in the specified row matches
the given number. */
bool isMatchInRow(int grid[N][N], int row, int num)
{
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}

/* Returns a boolean which indicates whether
an assigned entry in the specified column
matches the given number. */
bool isMatchInCol(int grid[N][N], int col, int num)
{
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

/* Returns a boolean which indicates whether
an assigned entry within the specified 3x3 box
matches the given number. */
bool isMatchInBox(int grid[N][N], int boxStartRow,
               int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row + boxStartRow]
                    [col + boxStartCol] ==
                num)
                return true;
    return false;
}

/* Returns a boolean which indicates whether
it will be legal to assign num to the given
row, col location. */
bool isSafe(int grid[N][N], int row,
            int col, int num)
{
    /* Check if 'num' is not already placed in
    current row, current column
    and current 3x3 box */
    return !isMatchInRow(grid, row, num) && !isMatchInCol(grid, col, num) && !isMatchInBox(grid, row - row % 3, col - col % 3, num) && grid[row][col] == EMPTYCELLS;
}

/* A utility function to print grid */
void printGrid(int grid[N][N])
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
            cout << grid[row][col] << " ";
        cout << endl;
    }
}

// Driver Code
int main()
{
    // 0 means unassigned cells
    int grid[N][N] = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
                      {5, 2, 0, 0, 0, 0, 0, 0, 0},
                      {0, 8, 7, 0, 0, 0, 0, 3, 1},
                      {0, 0, 3, 0, 1, 0, 0, 8, 0},
                      {9, 0, 0, 8, 6, 3, 0, 0, 5},
                      {0, 5, 0, 0, 9, 0, 6, 0, 0},
                      {1, 3, 0, 0, 0, 0, 2, 5, 0},
                      {0, 0, 0, 0, 0, 0, 0, 7, 4},
                      {0, 0, 5, 2, 0, 6, 3, 0, 0}};
    if (SolveSudoku(grid) == true)
        printGrid(grid);
    else
        cout << "No solution exists";

    return 0;
}
