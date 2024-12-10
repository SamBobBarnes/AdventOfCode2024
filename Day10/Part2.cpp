
#include <map>
#include "Day10.h"

map<Point, int> Day10::FindTrails2(const vector<vector<int> > *topoMap, const Point current) {
    map<Point, int> total{};
    int currentValue = (*topoMap)[current.y][current.x];
    if (currentValue == 9) return {{current, 1}};
    vector<Point> nextSteps{};

    if (current.y > 0 && (*topoMap)[current.y - 1][current.x] == currentValue + 1)
        nextSteps.emplace_back(
            current.x, current.y - 1);
    if (current.x > 0 && (*topoMap)[current.y][current.x - 1] == currentValue + 1)
        nextSteps.emplace_back(
            current.x - 1, current.y);
    if (current.x < (*topoMap)[0].size() - 1 && (*topoMap)[current.y][current.x + 1] == currentValue + 1)
        nextSteps.
                emplace_back(current.x + 1, current.y);
    if (current.y < topoMap->size() - 1 && (*topoMap)[current.y + 1][current.x] == currentValue + 1)
        nextSteps.
                emplace_back(current.x, current.y + 1);

    for (const auto &step: nextSteps) {
        for (auto &[key, val]: FindTrails2(topoMap, step)) {
            total[key] += val;
        }
    }
    return total;
}

int Day10::Part2() {
    const auto lines = Helpers::readFile(10, false);

    vector<vector<int> > topoMap{};
    vector<Point> trailHeads{};

    for (int y = 0; y < lines.size(); ++y) {
        vector<int> row{};
        for (int x = 0; x < lines[0].length(); ++x) {
            row.push_back(lines[y][x] - '0');
            if (lines[y][x] == '0') trailHeads.emplace_back(x, y);
        }
        topoMap.push_back(row);
    }

    int total{0};

    for (const auto &head: trailHeads) {
        for (auto &[key, val]: FindTrails2(&topoMap, head)) {
            total += val;
        }
    }

    return total;
}
