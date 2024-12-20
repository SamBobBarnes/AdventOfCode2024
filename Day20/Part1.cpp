#include <map>
#include <queue>

#include "Day20.h"

int Day20::Part1() {
    const auto lines = Helpers::readFile(20, true);

    Point start;
    Point end;
    const int height = lines.size();
    const int width = lines[0].size();

    auto getSet = [lines](const Point &current) -> vector<Point> {
        vector<Point> neighbors{};

        if (lines[current.y - 1][current.x] != '#') neighbors.emplace_back(current.x, current.y - 1);
        if (lines[current.y][current.x + 1] != '#') neighbors.emplace_back(current.x + 1, current.y);
        if (lines[current.y + 1][current.x] != '#') neighbors.emplace_back(current.x, current.y + 1);
        if (lines[current.y][current.x - 1] != '#') neighbors.emplace_back(current.x - 1, current.y);

        return neighbors;
    };

    map<Point, Point> prev{};
    map<Point, int> dist{};

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (lines[y][x] == 'E') {
                end = {x, y};
                prev[{x, y}] = {};
                dist[{x, y}] = Helpers::Max;
            } else if (lines[y][x] == 'S') {
                start = {x, y};
                prev[{x, y}] = {};
                dist[{x, y}] = 0;
            } else if (lines[y][x] == '.') {
                prev[{x, y}] = {};
                dist[{x, y}] = Helpers::Max;
            }
        }
    }

    priority_queue<PointScore> q{};
    q.emplace(start, 1);

    while (!q.empty()) {
        auto u = q.top();
        if (u == end) {
            break;
        }
        q.pop();

        auto neighbors = getSet(u);

        for (auto v: neighbors) {
            auto alt = dist[u] + 1;
            if (alt < dist[v]) {
                prev[v] = static_cast<Point>(u);
                dist[v] = alt;
                q.emplace(v, alt);
            }
        }
    }

    Point current = q.top();
    vector<Point> racingLine{};
    while (current != start) {
        racingLine.push_back(current);
        current = prev[current];
    }

    return racingLine.size() - 1;
}
