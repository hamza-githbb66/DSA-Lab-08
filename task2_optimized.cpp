// Optimization: before trying the moves, i sort them so that the square
// with the FEWEST next moves is tried first (Warnsdorff's rule).

#include <iostream>
#include <iomanip>
using namespace std;

const int MAX = 20;         // biggest board we allow
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

// counts how many moves are possible from a square
int countMoves(int x, int y) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        if (isSafe(x + dx[i], y + dy[i])) {
            count++;
        }
    }
    return count;
}

bool tourOptimized(int x, int y, int step) {
    calls++;
    board[x][y] = step;

    if (step == N * N) {
        return true;
    }

    // store every possible next move with how many moves it has after it
    int nxs[8];
    int nys[8];
    int deg[8];
    int cnt = 0;

    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (isSafe(nx, ny)) {
            nxs[cnt] = nx;
            nys[cnt] = ny;
            deg[cnt] = countMoves(nx, ny);
            cnt++;
        }
    }

    // bubble sort (only 8 items max) so the move with the smallest deg is first
    for (int i = 0; i < cnt - 1; i++) {
        for (int j = 0; j < cnt - 1 - i; j++) {
            if (deg[j] > deg[j + 1]) {
                swap(deg[j], deg[j + 1]);
                swap(nxs[j], nxs[j + 1]);
                swap(nys[j], nys[j + 1]);
            }
        }
    }

    // try the moves in the sorted order
    for (int i = 0; i < cnt; i++) {
        if (tourOptimized(nxs[i], nys[i], step + 1)) {
            return true;
        }
    }

    // backtrack
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

    if (tourOptimized(startX, startY, 1)) {
        cout << endl << "Tour found! (numbers show the order of the moves)" << endl;
        printBoard();
    }
    else {
        cout << endl << "No tour exists from this starting position." << endl;
    }

    cout << endl << "Function calls: " << calls << endl;

    return 0;
}