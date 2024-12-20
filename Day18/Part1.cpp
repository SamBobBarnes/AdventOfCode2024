#include <map>
#include <queue>

#include "Day18.h"

int Day18::Part1() {
    bool example = false;
    const auto lines = Helpers::readFile(18, example);

    const int width = example ? 6 : 70;
    const int height = example ? 6 : 70;
    const int fallenBytes = example ? 12 : 1024;


    auto Print = [width,height](const map<Point, bool> *bytes) {
        cout << endl;
        for (int y = 0; y <= height; ++y) {
            for (int x = 0; x <= width; ++x) {
                if (bytes->contains({x, y})) cout << "#";
                else cout << ".";
            }
            cout << endl;
        }
    };

    map<Point, bool> bytes{};

    for (int i = 0; i < fallenBytes; i++) {
        auto coords = Helpers::split(lines[i], ',');
        Point p{stoi(coords[0]), stoi(coords[1])};
        bytes[p] = true;
    }

    // Print(&bytes);

    map<Point, Point> prev{};
    map<Point, int> dist{};

    Point start{0, 0};
    const Point end{width, height};

    for (int y = 0; y <= height; ++y) {
        for (int x = 0; x <= width; ++x) {
            prev[{x, y}] = {};
            dist[{x, y}] = Helpers::Max;
        }
    }

    dist[{0, 0}] = 0;

    priority_queue<PointScore> q{};
    q.emplace(start, 0);

    while (!q.empty()) {
        auto u = q.top();
        if (u == end) {
            break;
        }
        q.pop();

        Point neighbors[4]{
            {u.x, u.y - 1},
            {u.x + 1, u.y},
            {u.x, u.y + 1},
            {u.x - 1, u.y}
        };

        for (auto v: neighbors) {
            if (v.x < 0 || v.y < 0 || v.x > width || v.y > height || bytes[v])
                continue;

            auto alt = dist[u] + 1;
            if (alt < dist[v]) {
                prev[v] = u;
                dist[v] = alt;
                q.emplace(v.x, v.y, alt);
            }
        }
    }

    return q.top().Score;
}
