#include <set>

#include "Day10.h"
#include "../Point.h"

set<Point> Day10::FindTrails(const vector<vector<int> > *topoMap, const Point current) {
    set<Point> total{};
    int currentValue = (*topoMap)[current.y][current.x];
    if (currentValue == 9) return {current};
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
        auto trails = FindTrails(topoMap, step);
        for (auto trail: trails) {
            total.insert(trail);
        }
    }
    return total;
}


int Day10::Part1() {
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
        total += FindTrails(&topoMap, head).size();
    }

    return total;
}
