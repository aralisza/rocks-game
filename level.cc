#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <sys/mman.h>
#include <math.h>
#include <vector>

using namespace std;

// abstract class for all levels
class Level {
public:

    /*
     * board must have the following characters:
     * p        : player
     * e        : exit
     *
     * and use the following characters to make the puzzle
     * [space]  : clear path
     * r        : rocks
     * w        : wall
     */
    vector< vector<char> > board;
    int win;

    // prints the level
    void printBoard() {
        for (vector<char> row : board) {
            // prints divider between rows
            for (size_t i = 0; i < row.size(); i++) {
                printf("|---");
            }
            printf("|\n");

            // prints elements of the row
            for (char c : row) {
                printf("| %c ", c);
            }
            printf("|\n");
        }

        // prints last divider
        for (size_t i = 0; i < board.at(0).size(); i++) {
            printf("|---");
        }
        printf("|\n\n");
    }

    void makeBoard(vector<char*> aboard, int col) {
        for (size_t i = 0; i < col; i++) {
            board.push_back(vector<char>(aboard[i], aboard[i] + col));
        }
    }
};

class TestLevel : public Level {
public:

    TestLevel() {
        vector<char*> aboard;

        aboard.push_back((char[5]){'w', 'w', 'e', 'w', 'w'});
        aboard.push_back((char[5]){'w', ' ', 'r', ' ', 'w'});
        aboard.push_back((char[5]){'w', ' ', ' ', ' ', 'w'});
        aboard.push_back((char[5]){'w', 'p', ' ', ' ', 'w'});
        aboard.push_back((char[5]){'w', 'w', 'w', 'w', 'w'});

        makeBoard(aboard, 5);
    }
};

int main() {
    TestLevel test;
    Level* lev = &test;

    test.printBoard();
    lev->printBoard();
}
