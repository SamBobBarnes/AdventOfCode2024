#ifndef DAY15_H
#define DAY15_H

#include "../Helpers.h"

using namespace std;

class Day15 {
public:
    static int Part1();

    static int Part2();

    enum Dir {
        Up = 0,
        Right = 1,
        Down = 2,
        Left = 3
    };

    enum WH {
        Box,
        Wall,
        Floor
    };
};

#endif //DAY15_H
