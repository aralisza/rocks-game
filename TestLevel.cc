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

    aboard.push_back((char[5]){'X', 'X', 'e', 'X', 'X'});
    aboard.push_back((char[5]){'X', ' ', 'O', ' ', 'X'});
    aboard.push_back((char[5]){'X', ' ', ' ', ' ', 'X'});
    aboard.push_back((char[5]){'X', 'p', ' ', ' ', 'X'});
    aboard.push_back((char[5]){'X', 'X', 'X', 'X', 'X'});

    convertBoard(aboard, 5);

    win = false;
}

RSE::RSE() {
    reset();
}

void RSE::reset() {
    vector<char*> aboard;

    aboard.push_back((char[9]){'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'});
    aboard.push_back((char[9]){'X', 'X', 'X', 'X', 'e', 'X', 'X', 'X', 'X'});
    aboard.push_back((char[9]){'X', 'X', 'X', ' ', ' ', ' ', 'X', 'X', 'X'});
    aboard.push_back((char[9]){'X', 'X', 'O', 'O', ' ', 'O', 'O', 'X', 'X'});
    aboard.push_back((char[9]){'X', 'X', ' ', 'O', 'O', 'O', ' ', 'X', 'X'});
    aboard.push_back((char[9]){'X', 'X', 'O', ' ', ' ', ' ', 'O', 'X', 'X'});
    aboard.push_back((char[9]){'X', 'X', ' ', 'O', 'O', 'O', ' ', 'X', 'X'});
    aboard.push_back((char[9]){'X', 'X', ' ', ' ', 'p', ' ', ' ', 'X', 'X'});
    aboard.push_back((char[9]){'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'});

    convertBoard(aboard, 9);

    win = false;
}
