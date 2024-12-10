#ifndef DAY10_H
#define DAY10_H

#include <set>
#include <map>

#include "../Helpers.h"
#include "../Point.h"

using namespace std;

class Day10 {
public:
    static int Part1();

    static int Part2();

    static set<Point> FindTrails(const vector<vector<int> > *topoMap, const Point current);

    static map<Point, int> FindTrails2(const vector<vector<int> > *topoMap, const Point current);
};

#endif //DAY10_H
