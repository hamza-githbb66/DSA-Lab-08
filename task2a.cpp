#include <iostream>
#include <iomanip>
using namespace std;

const int MAX = 6;          // plain backtracking is very slow after 6, so i stop at 6
int N;                      // size of the board
int board[MAX][MAX];        // 0 = not visited, otherwise stores the step number
long long calls = 0;        // counts how many times the function is called

// the 8 possible knight moves
int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

// checks if the square is inside the board and not visited yet
bool isSafe(int x, int y) {
    if (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == 0) {
        return true;
    }
    return false;
}

void printBoard() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(3) << board[i][j] << " ";
        }
        cout << endl;
    }
}

// x, y is the current square and step is the number of this move
bool tourSimple(int x, int y, int step) {
    calls++;
    board[x][y] = step;          // mark this square with the step number

    if (step == N * N) {         // all squares are visited so we are done
        return true;
    }

    // try all 8 moves one by one
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (isSafe(nx, ny)) {
            if (tourSimple(nx, ny, step + 1)) {
                return true;
            }
        }
    }

    // none of the moves worked so undo this square and go back (backtrack)
    board[x][y] = 0;
    return false;
}

int main() {
    int startX, startY;

    cout << "Enter the board size N (1 to " << MAX << "): ";
    cin >> N;

    if (N < 1 || N > MAX) {
        cout << "Board size is not allowed!" << endl;
        return 0;
    }

    cout << "Enter starting position x and y (from 0 to N-1): ";
    cin >> startX >> startY;

    if (startX < 0 || startX >= N || startY < 0 || startY >= N) {
        cout << "Starting position is outside the board!" << endl;
        return 0;
    }

    // fill the board with 0 (nothing visited yet)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = 0;
        }
    }

    if (tourSimple(startX, startY, 1)) {
        cout << endl << "Tour found! (numbers show the order of the moves)" << endl;
        printBoard();
    }
    else {
        cout << endl << "No tour exists from this starting position." << endl;
    }

    cout << endl << "Function calls: " << calls << endl;

    return 0;
}