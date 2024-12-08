#ifndef DAY8_H
#define DAY8_H

#include "../Helpers.h"
#include "../Point.h"

using namespace std;

class Day8 {
public:
    static int Part1();

    static int Part2();

    static void Print(const vector<string> *lines, const set<Point> *antiNodes) {
        cout << endl;
        for (int y = 0; y < lines->size(); ++y) {
            for (int x = 0; x < (*lines)[0].length(); ++x) {
                if (antiNodes->contains({x, y}))
                    cout << '#';
                else
                    cout << (*lines)[y][x];
            }
            cout << endl;
        }
    }
};

#endif //DAY8_H
