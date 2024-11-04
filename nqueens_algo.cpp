#include <iostream>
#include <vector>

using namespace std;

// Helper function to print the board
void printBoard(const vector<int>& queens) {
    int n = queens.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (queens[i] == j) cout << " Q ";
            else cout << " . ";
        }
        cout << endl;
    }
    cout << "-----------------" << endl;
}

// Recursive backtracking function to count solutions using bit manipulation
void solveNQueens(int n, int row, int &count, int cols, int leftDiag, int rightDiag, vector<int>& queens) {
    if (row == n) {  // All queens are placed
        count++;
        printBoard(queens);
        return;
    }

    int availablePositions = ((1 << n) - 1) & ~(cols | leftDiag | rightDiag);

    while (availablePositions) {
        int pos = availablePositions & -availablePositions;  // Rightmost available position
        availablePositions -= pos;  // Remove the position from available spots
        
        int col = __builtin_ctz(pos);  // Find the column index for the current position
        queens[row] = col;  // Place the queen on this position

        // Move to the next row and update bitmasks for columns and diagonals
        solveNQueens(n, row + 1, count, cols | pos, (leftDiag | pos) << 1, (rightDiag | pos) >> 1, queens);
    }
}

// Main function to solve N-Queens
int totalNQueens(int n) {
    int count = 0;
    vector<int> queens(n, -1);  // Track queen positions in each row
    solveNQueens(n, 0, count, 0, 0, 0, queens);
    return count;
}

int main() {
    int n;
    cout << "Enter the number of Queens for the solution: ";
    cin >> n;

    int totalSolutions = totalNQueens(n);
    cout << "There are " << totalSolutions << " solutions to the " << n << " queens problem." << endl;

    return 0;
}