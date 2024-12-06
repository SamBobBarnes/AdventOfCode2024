#include <set>

#include "Day6.h"
#include "../Point.h"

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
        for (auto i: GetSteps(&path)) {
            steps.insert(i);
        }
    }

    return steps.size() - 1;
}