#include <set>

#include "Day6.h"
#include "../Point.h"

bool CheckForOutOfBounds(const int width, const int height, const Point *current) {
    return current->y == height || current->y == -1 || current->x == width || current->x == -1;
}

Point GetTurnPoint(const vector<vector<bool> > *grid, int dir, const Point *start) {
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

set<Point> GetSteps(const tuple<Point, Point> *path) {
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

int Day6::Part1() {
    const auto lines = Helpers::readFile(6, false);

    vector<tuple<Point, Point> > paths{};
    vector<vector<bool> > layout{};

    Point start;
    int dir{0};

    int y{0};
    for (auto &line: lines) {
        vector<bool> row{};
        int x{0};
        for (char tile: line) {
            if (tile == '#') row.push_back(true);
            else row.push_back(false);
            if (tile == '^') {
                start = {x, y};
            }
            x++;
        }
        layout.push_back(row);
        y++;
    }

    int width = lines[0].length();
    int height = lines.size();

    Point current = start;

    while (!CheckForOutOfBounds(width, height, &current)) {
        auto next = GetTurnPoint(&layout, dir, &current);
        dir += 1;
        if (dir == 4) dir = 0;

        paths.emplace_back(current, next);

        current = next;
    }

    set<Point> steps{};

    for (auto path: paths) {
        steps.insert_range(GetSteps(&path));
    }

    return steps.size() - 1;
}
