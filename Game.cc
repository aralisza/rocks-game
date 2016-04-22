#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "TestLevel.cc"

using namespace std;

Game::Game() {
    curLev = 0;

    TestLevel *l1 = new TestLevel;
    RSE *l2 = new RSE;
    RGB *l3 = new RGB;
    ESV *l4 = new ESV;

    levels.push_back(l1);
    levels.push_back(l2);
    levels.push_back(l3);
    levels.push_back(l4);
}

void Game::print() {
    printf("Current Level: %d\n", curLev + 1);
    levels[curLev]->printBoard();
}

void Game::setLevel(int level) {
    if (level > levels.size()) {
        curLev = levels.size() - 1;
    }
    else if (level < 0) {
        curLev = 0;
    }
    else
        curLev = level;
}

// handle key inputs
void Game::onKey(char key) {
    // move player
    if (key == 'w' ||
        key == 'a' ||
        key == 's' ||
        key == 'd') {
        levels[curLev]->movePlayer(key);
    }
    // reset level, also resets win to 0
    else if (key == 'r') {
        levels[curLev]->reset();
    }
    // previous level
    else if (key == '[') {
        curLev = max(curLev - 1, 0);
    }
    // next level
    else if (key == ']') {
        curLev = min(curLev + 1, (int)levels.size() - 1);
    }

    print();
}

bool Game::winAll() {
    bool r = true;
    //  for (Level* l : levels) {
    for (int i = 0; i < levels.size(); i++) {
        r = r && levels[i]->win;
    }
    return r;
}
