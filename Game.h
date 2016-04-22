#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "Level.h"

using namespace std;

class Game {
public:
    int curLev;
    vector<Level*> levels;
    bool winner;

    Game();
    void print();

    void setLevel(int level);

    // handle key inputs
    void onKey(char key);
    
    bool winAll();
};


