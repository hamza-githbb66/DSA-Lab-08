#include <iostream>
using namespace std;

const int MAX_DISKS = 20;

int pegs[3][MAX_DISKS];     // pegs[0] = A, pegs[1] = B, pegs[2] = C
int diskCount[3] = {0, 0, 0};   // how many disks are on each peg right now
char names[3] = {'A', 'B', 'C'};

// my own stack functions
void push(int peg, int disk) {
    pegs[peg][diskCount[peg]] = disk;
    diskCount[peg]++;
}

int pop(int peg) {
    diskCount[peg]--;
    return pegs[peg][diskCount[peg]];
}

int topDisk(int peg) {
    return pegs[peg][diskCount[peg] - 1];
}

bool isEmpty(int peg) {
    return diskCount[peg] == 0;
}

// moves one disk from peg "from" to peg "to" and prints it
void makeMove(int from, int to) {
    int disk = pop(from);
    push(to, disk);
    cout << "Move disk " << disk << " from " << names[from] << " to " << names[to] << endl;
}

// moves one disk between two pegs in the legal direction
void moveDisk(int p1, int p2) {
    if (isEmpty(p1)) {
        // p1 is empty so the disk must come from p2
        makeMove(p2, p1);
    }
    else if (isEmpty(p2)) {
        // p2 is empty so the disk comes from p1
        makeMove(p1, p2);
    }
    else if (topDisk(p1) < topDisk(p2)) {
        // top of p1 is smaller so it moves to p2
        makeMove(p1, p2);
    }
    else {
        // top of p2 is smaller so it moves to p1
        makeMove(p2, p1);
    }
}

void hanoiIterative(int n) {
    int src = 0;
    int first = 2;    // C
    int second = 1;   // B

    // for even number of disks we swap first and second
    // (the final destination is still peg C)
    if (n % 2 == 0) {
        int temp = first;
        first = second;
        second = temp;
    }

    // put all the disks on the source peg (biggest disk at the bottom)
    for (int i = n; i >= 1; i--) {
        push(src, i);
    }

    // total moves = 2^n - 1
    int totalMoves = 1;
    for (int i = 0; i < n; i++) {
        totalMoves = totalMoves * 2;
    }
    totalMoves = totalMoves - 1;

    for (int i = 1; i <= totalMoves; i++) {
        if (i % 3 == 1) {
            moveDisk(src, first);
        }
        else if (i % 3 == 2) {
            moveDisk(src, second);
        }
        else {
            moveDisk(second, first);
        }
    }

    cout << endl << "Total moves: " << totalMoves << endl;
}

int main() {
    int n;
    cout << "Enter the number of disks (1 to " << MAX_DISKS << "): ";
    cin >> n;

    if (n < 1 || n > MAX_DISKS) {
        cout << "Number of disks is not allowed" << endl;
        return 0;
    }

    cout << endl;
    hanoiIterative(n);

    return 0;
}