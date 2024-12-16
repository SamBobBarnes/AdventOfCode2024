#ifndef DAY15_H
#define DAY15_H

#include "../Helpers.h"
#include "../Point.h"

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
        Floor,
        BoxL,
        BoxR
    };

    static void Print(const vector<vector<WH> > *warehouse, const Point robot = {0, 0}) {
        cout << endl;
        for (int y = 0; y < warehouse->size(); ++y) {
            for (int x = 0; x < (*warehouse)[0].size(); ++x) {
                if (robot.x == x && robot.y == y)
                    cout << '@';
                else if ((*warehouse)[y][x] == Box)
                    cout << 'O';
                else if ((*warehouse)[y][x] == BoxL)
                    cout << '[';
                else if ((*warehouse)[y][x] == BoxR)
                    cout << ']';
                else if ((*warehouse)[y][x] == Wall)
                    cout << '#';
                else cout << '.';
            }
            cout << endl;
        }
    }
};

#endif //DAY15_H
