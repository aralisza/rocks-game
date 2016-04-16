#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "TestLevel.cc"

using namespace std;

class Game {
public:
    int curLev;
    vector<Level*> levels;
    bool winner;

    Game() {
        curLev = 0;

        TestLevel *l1 = new TestLevel;
        TestLevel *l2 = new TestLevel;
        TestLevel *l3 = new TestLevel;

        levels.push_back(l1);
        levels.push_back(l2);
        levels.push_back(l3);
    }

    void print() {
        printf("Current Level: %d\n", curLev + 1);
        levels[curLev]->printBoard();
    }

    // handle key inputs
    void onKey(char key) {
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
    }

    bool winAll() {
        bool r = true;
        for (Level* l : levels) {
            r = r && l->win;
        }

        return r;
    }
};

int main() {
    Game g;
    char input;
    bool control = true;

    while (control) {
        g.print();

        cin >> input;
        g.onKey(input);

        if (g.winAll()) {
            g.print();
            printf("You Win!\n");
            control = false;
        }
    }
}
