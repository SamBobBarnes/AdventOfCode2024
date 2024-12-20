#include <map>
#include <queue>

#include "Day20.h"

int Day20::Part2() {
    const auto lines = Helpers::readFile(20, true);

    Point start;
    Point end;
    const int height = lines.size();
    const int width = lines[0].size();

    map<Point, Point> prevI{};
    map<Point, int> distI{};

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            prevI[{x, y}] = {};
            distI[{x, y}] = Helpers::Max;
        }
    }

    auto getSet = [lines](const Point &current) -> vector<Point> {
        vector<Point> neighbors{};

        if (lines[current.y - 1][current.x] != '#') neighbors.emplace_back(current.x, current.y - 1);
        if (lines[current.y][current.x + 1] != '#') neighbors.emplace_back(current.x + 1, current.y);
        if (lines[current.y + 1][current.x] != '#') neighbors.emplace_back(current.x, current.y + 1);
        if (lines[current.y][current.x - 1] != '#') neighbors.emplace_back(current.x - 1, current.y);

        return neighbors;
    };

    auto getShortcutSet = [lines](const Point &current) -> vector<Point> {
        vector<Point> neighbors{};

        if (lines[current.y - 1][current.x] == '#') neighbors.emplace_back(current.x, current.y - 1);
        if (lines[current.y][current.x + 1] == '#') neighbors.emplace_back(current.x + 1, current.y);
        if (lines[current.y + 1][current.x] == '#') neighbors.emplace_back(current.x, current.y + 1);
        if (lines[current.y][current.x - 1] == '#') neighbors.emplace_back(current.x - 1, current.y);

        return neighbors;
    };

    auto dijkstra = [getShortcutSet
            ](const Point &start, const Point &end, map<Point, Point> prev, map<Point, int> dist)-> int {
        dist[start] = 0;

        priority_queue<PointScore> q{};
        q.emplace(start, 1);

        while (!q.empty()) {
            auto u = q.top();
            if (u.Score > 20) {
                return -1;
            }
            if (u == end) {
                break;
            }
            q.pop();

            auto neighbors = getShortcutSet(u);

            for (auto v: neighbors) {
                auto alt = dist[u] + 1;
                if (alt < dist[v]) {
                    prev[v] = static_cast<Point>(u);
                    dist[v] = alt;
                    q.emplace(v, alt);
                }
            }
        }

        return q.top().Score;
    };

    for (int y = 0; y < lines.size(); ++y) {
        for (int x = 0; x < lines[0].length(); ++x) {
            if (lines[y][x] == 'S') start = {x, y};
            else if (lines[y][x] == 'E') end = {x, y};
        }
    }

    vector<Point> racetrack{};

    Point current = start;
    while (current != end) {
        auto neighbors = getSet(current);
        for (auto neighbor: neighbors) {
            if (!racetrack.empty() && neighbor == racetrack.back()) continue;
            racetrack.push_back(current);
            current = neighbor;
            break;
        }
    }
    racetrack.push_back(current);

    for (int i = 0; i < racetrack.size(); ++i) {
        for (int j = i + 1; j < racetrack.size(); ++j) {
            const Point *current = &racetrack[i];
            const Point *next = &racetrack[j];
        }
    }


    return racetrack.size();
}
