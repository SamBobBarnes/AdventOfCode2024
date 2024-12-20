#include <map>
#include <queue>

#include "Day16.h"
#include "../Point.h"

int Day16::Part1() {
    const auto lines = Helpers::readFile(16, false);

    Point end;
    Point start;
    const int height = lines.size();
    const int width = lines[0].length();

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
    q.emplace(start, 0, 1);

    while (!q.empty()) {
        auto u = q.top();
        if (u == end) {
            break;
        }
        q.pop();

        bool dirs[4]{
            lines[u.y - 1][u.x] == '.' || lines[u.y - 1][u.x] == 'E',
            lines[u.y][u.x + 1] == '.' || lines[u.y][u.x + 1] == 'E',
            lines[u.y + 1][u.x] == '.' || lines[u.y + 1][u.x] == 'E',
            lines[u.y][u.x - 1] == '.' || lines[u.y][u.x - 1] == 'E',
        };

        Point dirPoints[4]{
            {u.x, u.y - 1},
            {u.x + 1, u.y},
            {u.x, u.y + 1},
            {u.x - 1, u.y}
        };

        for (int i = 0; i < 4; ++i) {
            if (!dirs[i]) continue;
            auto v = dirPoints[i];
            auto dirScoreAdj = 0;

            switch (u.Dir) {
                case 0:
                    switch (i) {
                        case 1:
                        case 3:
                            dirScoreAdj = 1;
                            break;
                        case 2:
                            dirScoreAdj = 2;
                    }
                    break;
                case 1:
                    switch (i) {
                        case 0:
                        case 2:
                            dirScoreAdj = 1;
                            break;
                        case 3:
                            dirScoreAdj = 2;
                    }
                    break;
                case 2:
                    switch (i) {
                        case 1:
                        case 3:
                            dirScoreAdj = 1;
                            break;
                        case 0:
                            dirScoreAdj = 2;
                    }
                    break;
                case 3:
                    switch (i) {
                        case 0:
                        case 2:
                            dirScoreAdj = 1;
                            break;
                        case 1:
                            dirScoreAdj = 2;
                    }
            }

            auto alt = dist[u] + 1 + 1000 * dirScoreAdj; // add more if turn is required
            if (alt < dist[v]) {
                prev[v] = static_cast<Point>(u);
                dist[v] = alt;
                q.emplace(v, alt, i);
            }
        }
    }

    return q.top().Score;
}
