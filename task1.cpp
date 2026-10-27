// Task 1: Peak Element in a 2D array

#include <iostream>
using namespace std;

// size of my matrix 
const int ROWS = 4;
const int COLS = 4;

// returns true if a peak is found and saves its position in peakRow and peakCol
bool findPeak(int mat[ROWS][COLS], int &peakRow, int &peakCol) {
    int rows = ROWS;
    int cols = COLS;

    int low = 0;
    int high = cols - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        // find the row that has the biggest value in the middle column
        int maxRow = 0;
        for (int i = 1; i < rows; i++) {
            if (mat[i][mid] > mat[maxRow][mid]) {
                maxRow = i;
            }
        }

        int current = mat[maxRow][mid];

        // check left and right neighbour
        // if we are on the edge there is no neighbour so it is fine
        bool leftOk = true;
        bool rightOk = true;

        if (mid > 0 && mat[maxRow][mid - 1] > current) {
            leftOk = false;
        }
        if (mid < cols - 1 && mat[maxRow][mid + 1] > current) {
            rightOk = false;
        }

        if (leftOk && rightOk) {
            // found it
            peakRow = maxRow;
            peakCol = mid;
            return true;
        }
        else if (leftOk == false) {
            // left neighbour is bigger so go left
            high = mid - 1;
        }
        else {
            // right neighbour is bigger so go right
            low = mid + 1;
        }
    }

    return false; // we should never reach here but the function needs a return
}

int main() {
    // this is my sample matrix (4 x 4)
    int mat[ROWS][COLS] = {
        {10,  8, 10, 10},
        {14, 13, 12, 11},
        {15,  9, 11, 21},
        {16, 17, 19, 20}
    };

    cout << "The matrix is:" << endl;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << mat[i][j] << "\t";
        }
        cout << endl;
    }

    int r = -1, c = -1;

    if (findPeak(mat, r, c)) {
        cout << endl;
        cout << "Peak element found: " << mat[r][c] << endl;
        cout << "Position (row, col): (" << r << ", " << c << ")" << endl;
    }
    else {
        cout << "No peak found" << endl;
    }

    return 0;
}