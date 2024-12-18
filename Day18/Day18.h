#ifndef DAY18_H
#define DAY18_H

#include "../Helpers.h"
#include "../Point.h"

using namespace std;

class Day18 {
public:
    static int Part1();

    static string Part2();

    static void resetDijkstra(const int width, const int height, map<Point, Point> *prev, map<Point, int> *dist);
};

#endif //DAY18_H
