#include <map>
#include <queue>
#include <set>

#include "Day20.h"

void Print(const vector<string> &lines, vector<Point> &racingLine, map<Point, int> &shortcuts) {
    cout << endl;
    for (int y = 0; y < lines.size(); ++y) {
        for (int x = 0; x < lines[0].length(); ++x) {
            Point current{x, y};
            if (shortcuts[current]) cout << "\033[96m" << '#' << "\033[0m";
            else if (ranges::find(racingLine, current) != racingLine.end())
                cout << "\033[91m" << '8' << "\033[0m";
            else cout << lines[y][x];
        }
        cout << endl;
    }
}

int Day20::Part1() {
    const auto lines = Helpers::readFile(20, false);

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

    vector<Point> racingLine{}; {
        Point current = q.top();
        while (current != start) {
            racingLine.push_back(current);
            current = prev[current];
        }
        racingLine.push_back(current);
    }
    map<Point, int> shortcuts{};

    for (int i = racingLine.size() - 1; i >= 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            const Point *current = &racingLine[i];
            const Point *next = &racingLine[j];

            if (current->x == next->x - 2 && current->y == next->y && lines[next->y][next->x - 1] == '#')
                shortcuts[{next->x - 1, next->y}] = i - j - 2;
            else if (current->y == next->y - 2 && current->x == next->x && lines[next->y - 1][next->x] == '#')
                shortcuts[{next->x, next->y - 1}] = i - j - 2;
            else if (current->x == next->x + 2 && current->y == next->y && lines[next->y][next->x + 1] == '#')
                shortcuts[{next->x + 1, next->y}] = i - j - 2;
            else if (current->y == next->y + 2 && current->x == next->x && lines[next->y + 1][next->x] == '#')
                shortcuts[{next->x, next->y + 1}] = i - j - 2;
        }
    }

    map<int, int> shortcutSizes{};

    int total = 0;

    for (auto size: shortcuts | views::values) {
        shortcutSizes[size]++;
        if (size >= 100) total++;
    }

    // cout << endl;
    // for (auto [size,count]: shortcutSizes) {
    //     if (count > 1)
    //         cout << "There are " << count << " cheats that save " << size << " picoseconds." << endl;
    //     else
    //         cout << "There is one cheat that saves " << size << " picoseconds." << endl;
    // }

    // Print(lines, racingLine, shortcuts);

    return total;
}
