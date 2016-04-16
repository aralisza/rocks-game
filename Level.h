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
    bool win;

    // resets the board
    virtual void reset() = 0;

    // prints the level
    void printBoard();

    // builds the board from a vector of arrays.
    // this is useful because filling vectors is a pain.
    void convertBoard(vector<char*> aboard, int col);

    // returns an array of [x, y] player position
    int* getPlayerXY();

    void movePlayer(char dir);

    void move(int* xy, char dir);

    bool isOutOfBounds(int* xy);

    int* getTargetPosn(int* xy, char dir);
};

class TestLevel : public Level {
public:
    TestLevel();

    void reset();
};
