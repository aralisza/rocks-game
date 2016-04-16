#include <stdlib.h>
#include <stdio.h>
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
    bool win; // 1 = win, 0 = not yet

    // resets the board
    virtual void reset() = 0;

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
        for (size_t i = 0; i < board[0].size(); i++) {
            printf("|---");
        }
        printf("|\n\n");
    }

    // builds the board from a vector of arrays.
    // this is useful because filling vectors is a pain.
    void convertBoard(vector<char*> aboard, int col) {
        for (size_t i = 0; i < col; i++) {
            board.push_back(vector<char>(aboard[i], aboard[i] + col));
        }
    }

    // returns an array of [x, y] player position
    int* getPlayerXY() {
        int r[2] = {-1, -1};
        for (size_t i = 0; i < board.size(); i++) {
            for (size_t j = 0; j < board[i].size(); j++) {
                if (board[i][j] == 'p') {
                    r[0] = j;
                    r[1] = i;
                }
            }
        }
        return r;
    }

    void movePlayer(char dir) {
        printf("playerxy: (%d, %d)\n\n", getPlayerXY()[0], getPlayerXY()[1]);
        int ugh[2] = {getPlayerXY()[0], getPlayerXY()[1]};
        move(ugh, dir);
    }

    void move(int* xy, char dir) {
        int targ[2];
        targ[0] = getTargetPosn(xy, dir)[0];
        targ[1] = getTargetPosn(xy, dir)[1];
        char cur = board[xy[1]][xy[0]];

        printf("confirm: (%d, %d)\n\n", xy[0], xy[1]);

        printf("move '%c' from (%d, %d) to: (%d, %d)\n\n", cur, xy[0], xy[1], targ[0], targ[1]);

        if (isOutOfBounds(targ)) {
            printf("out of bounds\n");
            return;
        }
        else if (board[targ[1]][targ[0]] == ' ') {
            board[xy[1]][xy[0]] = ' ';
            board[targ[1]][targ[0]] = cur;
            printf("successful move of %c to empty space\n", cur);
        }
        else if (board[targ[1]][targ[0]] == ' ') {
            board[xy[1]][xy[0]] = ' ';
            board[targ[1]][targ[0]] = cur;
        }
        else if (board[targ[1]][targ[0]] == 'r') {
            int next[2];
            next[0] = getTargetPosn(targ, dir)[0];
            next[1] = getTargetPosn(targ, dir)[1];
            if (!isOutOfBounds(next) && board[next[1]][next[0]] == ' ') {
                move(targ, dir);
                board[xy[1]][xy[0]] = ' ';
                board[targ[1]][targ[0]] = cur;
            }
        }
        else if (board[targ[1]][targ[0]] == 'e') {
            board[targ[1]][targ[0]] = 'p';
            win = true;
        }
    }

    bool isOutOfBounds(int* xy) {
        printf("bounds: (%d, %d)\n", board[0].size(), board.size());

        return
            xy[1] < 0 &&
            xy[1] >= board.size() &&
            xy[0] < 0 &&
            xy[0] >= board[xy[1]].size();
    }

    int* getTargetPosn(int* xy, char dir) {
        int targ[2];

        if (dir == 'w') { // up
            targ[0] = xy[0];
            targ[1] = xy[1] - 1;
        }

        else if (dir == 'a') { // left
            targ[0] = xy[0] - 1;
            targ[1] = xy[1];
        }

        else if (dir == 's') { // down
            targ[0] = xy[0];
            targ[1] = xy[1] + 1;
        }

        else if (dir == 'd') { // right
            targ[0] = xy[0] + 1;
            targ[1] = xy[1];
        }
        else {
            targ[0] = xy[0];
            targ[1] = xy[1];
        }

        printf("(%d, %d)\n\n", targ[0], targ[1]);
        return targ;
    }
};