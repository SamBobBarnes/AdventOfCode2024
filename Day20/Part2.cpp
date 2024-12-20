#include <map>
#include <queue>

#include "Day20.h"

uint64_t Day20::Part2() {
    const auto lines = Helpers::readFile(20, false);

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

    auto getShortcutSet = [lines,height,width](const Point &current) -> vector<Point> {
        vector<Point> neighbors{};

        if (current.y != 0) neighbors.emplace_back(current.x, current.y - 1);
        if (current.x < width - 1)
            neighbors.emplace_back(
                current.x + 1, current.y);
        if (current.y < height - 1)
            neighbors.emplace_back(
                current.x, current.y + 1);
        if (current.x != 0) neighbors.emplace_back(current.x - 1, current.y);

        return neighbors;
    };

    auto manhattan = [](const Point &start, const Point &end)-> int {
        return abs(start.x - end.x) + abs(start.y - end.y);
    };

    for (int y = 0; y < lines.size(); ++y) {
        for (int x = 0; x < lines[0].length(); ++x) {
            if (lines[y][x] == 'S') start = {x, y};
            else if (lines[y][x] == 'E') end = {x, y};
        }
    }

    vector<Point> racetrack{}; {
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
    }

    map<int, int> shortcuts{};
    uint64_t total{0};

    for (int i = 0; i < racetrack.size(); ++i) {
        for (int j = i + 1; j < racetrack.size(); ++j) {
            const Point &current = racetrack[i];
            const Point &next = racetrack[j];
            auto length = manhattan(current, next);
            if (length <= 20) {
                int cheatSaves = j - i - length;
                shortcuts[cheatSaves]++;
                if (cheatSaves >= 100)
                    total++;
            }
        }
    }

    // cout << endl;
    // for (auto [size,count]: shortcuts) {
    //     if (count > 1)
    //         cout << "There are " << count << " cheats that save " << size << " picoseconds." << endl;
    //     else
    //         cout << "There is one cheat that saves " << size << " picoseconds." << endl;
    // }

    return total; //< 42575099
}
