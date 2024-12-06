#include "Day6.h"
#include "../Timer.h"

int getPathDir(tuple<Point, Point> *path) {
    int startX = get<0>(*path).x;
    int startY = get<0>(*path).y;
    int endX = get<1>(*path).x;
    int endY = get<1>(*path).y;
    if (startX == endX) {
        if (startY < endY) return 2; //down
        return 0; //up
    }
    if (startX < endX) return 1; //right
    return 3; //left
}

void Print(const int width, const int height, set<Point> *points) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Point current = {x, y};
            if (ranges::find(*points, current) == points->end()) cout << ".";
            else cout << "O";
        }
        cout << endl;
    }
}

int Day6::Part2() {
    Timer timer{};
    const auto lines = Helpers::readFile(6, false);

    vector<tuple<Point, Point> > paths{};
    vector<vector<bool> > layout{};

    Point start;
    int dir{0};

    int index{0};
    for (auto &line: lines) {
        vector<bool> row{};
        int x{0};
        for (char tile: line) {
            if (tile == '#') row.push_back(true);
            else row.push_back(false);
            if (tile == '^') {
                start = {x, index};
            }
            x++;
        }
        layout.push_back(row);
        index++;
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

    set<Point> possibleLoops{};

    index = 0;
    for (auto &i: paths) {
        // timer.Start("search-outer");
        int currentDir = getPathDir(&i);
        if (currentDir == 0 || currentDir == 2) {
            int x = get<0>(i).x;
            for (int j = currentDir == 0 ? get<0>(i).y : get<1>(i).y;
                 j >= (currentDir == 0
                           ? get<1>(i).y
                           : get<0>(i).y);
                 j--) {
                if (start == *new Point{x, j} || CheckForOutOfBounds(width, height, new Point{x, j}))continue;
                layout[j][x] = true;
                current = start;
                dir = 0;
                vector<tuple<Point, Point> > tempPaths{};

                while (!CheckForOutOfBounds(width, height, &current)) {
                    auto next = GetTurnPoint(&layout, dir, &current);
                    dir += 1;
                    if (dir == 4) dir = 0;
                    tuple<Point, Point> path{current, next};
                    if (ranges::find(tempPaths, path) != tempPaths.end()) {
                        possibleLoops.emplace(x, j);
                        break;
                    }

                    tempPaths.push_back(path);

                    current = next;
                }
                layout[j][x] = false;
            }
        } else {
            int y = get<0>(i).y;
            for (int j = currentDir == 3 ? get<0>(i).x : get<1>(i).x;
                 j >= (currentDir == 3
                           ? get<1>(i).x
                           : get<0>(i).x);
                 j--) {
                if (start == *new Point{j, y} || CheckForOutOfBounds(width, height, new Point{j, y}))continue;
                layout[y][j] = true;
                current = start;
                dir = 0;
                vector<tuple<Point, Point> > tempPaths{};

                while (!CheckForOutOfBounds(width, height, &current)) {
                    auto next = GetTurnPoint(&layout, dir, &current);
                    dir += 1;
                    if (dir == 4) dir = 0;
                    tuple<Point, Point> path{current, next};
                    if (ranges::find(tempPaths, path) != tempPaths.end()) {
                        possibleLoops.emplace(j, y);
                        break;
                    }

                    tempPaths.push_back(path);

                    current = next;
                }

                layout[y][j] = false;
            }
        }


        // timer.End("search-outer");
        // cout << "Search-outer: " << timer.GetTime("search-outer") << endl;
        // timer.Clear("search-outer");
        index++;
    }

    // Print(width, height, &possibeLoops);

    return possibleLoops.size();
}
