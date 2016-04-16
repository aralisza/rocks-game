#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "Level.h"

using namespace std;

TestLevel::TestLevel() {
    reset();
}

void TestLevel::reset() {
    vector<char*> aboard;

    aboard.push_back((char[5]){'w', 'w', 'e', 'w', 'w'});
    aboard.push_back((char[5]){'w', ' ', 'r', ' ', 'w'});
    aboard.push_back((char[5]){'w', ' ', ' ', ' ', 'w'});
    aboard.push_back((char[5]){'w', 'p', ' ', ' ', 'w'});
    aboard.push_back((char[5]){'w', 'w', 'w', 'w', 'w'});

    convertBoard(aboard, 5);

    win = false;
}
