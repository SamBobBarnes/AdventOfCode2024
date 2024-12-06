#ifndef DAY6_H
#define DAY6_H

#include <set>

#include "../Helpers.h"
#include "../Point.h"

using namespace std;

class Day6 {
public:
    static int Part1();

    static int Part2();

    static bool CheckForOutOfBounds(const int width, const int height, const Point *current) {
        return current->y == height || current->y == -1 || current->x == width || current->x == -1;
    }

    static Point GetTurnPoint(const vector<vector<bool> > *grid, int dir, const Point *start) {
        const int width = (*grid)[0].size();
        const int height = grid->size();
        Point current = *start;
        do {
            switch (dir) {
                case 0:
                    //up
                    current = {current.x, current.y - 1};
                    break;
                case 1:
                    //right
                    current = {current.x + 1, current.y};
                    break;
                case 2:
                    //down
                    current = {current.x, current.y + 1};
                    break;
                case 3:
                    //left
                    current = {current.x - 1, current.y};
                    break;
            }
            if (CheckForOutOfBounds(width, height, &current)) return current;
        } while (!(*grid)[current.y][current.x]);

        switch (dir) {
            case 0:
                //up
                current = {current.x, current.y + 1};
                break;
            case 1:
                //right
                current = {current.x - 1, current.y};
                break;
            case 2:
                //down
                current = {current.x, current.y - 1};
                break;
            case 3:
                //left
                current = {current.x + 1, current.y};
                break;
        }

        return current;
    }

    static set<Point> GetSteps(const tuple<Point, Point> *path) {
        const Point start = get<0>(*path);
        const Point end = get<1>(*path);

        set<Point> steps{start, end};

        if (start.x == end.x) {
            if (start.y < end.y) {
                for (int y = start.y + 1; y < end.y; ++y) {
                    steps.emplace(start.x, y);
                }
            } else {
                for (int y = end.y + 1; y < start.y; ++y) {
                    steps.emplace(start.x, y);
                }
            }
        } else {
            if (start.x < end.x) {
                for (int x = start.x + 1; x < end.x; ++x) {
                    steps.emplace(x, start.y);
                }
            } else {
                for (int x = end.x + 1; x < start.x; ++x) {
                    steps.emplace(x, start.y);
                }
            }
        }

        return steps;
    }
};

#endif //DAY6_H
