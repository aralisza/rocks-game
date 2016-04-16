#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "Game.cc"

using namespace std;

int main() {
    TestLevel test;
    Level* lev = &test;
    char input;

    lev->printBoard();

    while (true) {
        cin >> input;
        printf("\n");

        lev->movePlayer(input);
        lev->printBoard();
    }
}
