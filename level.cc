#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "Level.h"

using namespace std;

// prints the level
void Level::printBoard() {
    //for (vector<char> row: board) {
    for (int i =0; i < board.size(); i++) {
        // prints divider between rows
        //for (char c: board[i]) {
        for (int j = 0; j < board[i].size(); j++) {
            printf("|---");
        }
        printf("|\n");

        // prints elements of the row
       // for (char c : row) {
	for (int k = 0; k < board[i].size(); k++) {
            printf("| %c ", board[i][k]);
        }
        printf("|\n");
    }

    // prints last divider
    // for (char c: board[0]) {
	for (int l = 0; l < board[0].size(); l++) {
        printf("|---");
    }
    printf("|\n\n");

    if (win) {
        printf("Complete!\n\n");
    }
}

// builds the board from a vector of arrays.
// this is useful because filling vectors is a pain.
void Level::convertBoard(vector<char*> aboard, int col) {
    vector< vector<char> > newb;
    for (size_t i = 0; i < aboard.size(); i++) {
        newb.push_back(vector<char>(aboard[i], aboard[i] + col));
    }

    board = newb;
}

// returns an array of [x, y] player position
int* Level::getPlayerXY() {
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

void Level::movePlayer(char dir) {
    if (!win) {
        //printf("playerxy: (%d, %d)\n\n", getPlayerXY()[0], getPlayerXY()[1]);
        int ugh[2] = {getPlayerXY()[0], getPlayerXY()[1]};
        move(ugh, dir);
    }
}

void Level::move(int* xy, char dir) {
    int targ[2];
    targ[0] = getTargetPosn(xy, dir)[0];
    targ[1] = getTargetPosn(xy, dir)[1];
    char cur = board[xy[1]][xy[0]];

    //printf("confirm: (%d, %d)\n\n", xy[0], xy[1]);

    //printf("move '%c' from (%d, %d) to: (%d, %d)\n\n", cur, xy[0], xy[1], targ[0], targ[1]);

    if (isOutOfBounds(targ)) {
        //printf("out of bounds\n");
        return;
    }
    else if (board[targ[1]][targ[0]] == ' ') {
        board[xy[1]][xy[0]] = ' ';
        board[targ[1]][targ[0]] = cur;
        //printf("successful move of %c to empty space\n", cur);
    }
    else if (board[targ[1]][targ[0]] == ' ') {
        board[xy[1]][xy[0]] = ' ';
        board[targ[1]][targ[0]] = cur;
    }
    else if (board[targ[1]][targ[0]] == 'O') {
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
        board[xy[1]][xy[0]] = ' ';
        board[targ[1]][targ[0]] = 'p';
        win = true;
    }
}

bool Level::isOutOfBounds(int* xy) {
    //printf("bounds: (%d, %d)\n", board[0].size(), board.size());

    return
        xy[1] < 0 &&
        xy[1] >= board.size() &&
        xy[0] < 0 &&
        xy[0] >= board[xy[1]].size();
}

int* Level::getTargetPosn(int* xy, char dir) {
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

    //printf("(%d, %d)\n\n", targ[0], targ[1]);
    return targ;
}
