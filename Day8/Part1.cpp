#include <map>
#include <set>

#include "Day8.h"
#include "../Point.h"

int Day8::Part1() {
    const auto lines = Helpers::readFile(8, false);

    const int width = lines[0].length();
    const int height = lines.size();

    map<char, vector<Point> > antennaGroups{};
    set<Point> antiNodes{};

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const char point = lines[y][x];
            if (point == '.')continue;
            if (!antennaGroups.contains(point)) antennaGroups[point] = {{x, y}};
            else antennaGroups[point].emplace_back(x, y);
        }
    }

    for (auto group: antennaGroups | views::values) {
        for (int i = 0; i < group.size() - 1; ++i) {
            const Point *current = &group[i];
            for (int j = i + 1; j < group.size(); ++j) {
                const Point *second = &group[j];

                const int xDiff = abs(current->x - second->x);
                const int yDiff = abs(current->y - second->y);

                Point a1;
                Point a2;

                if (current->x < second->x && current->y < second->y) {
                    a1 = {current->x - xDiff, current->y - yDiff};
                    a2 = {second->x + xDiff, second->y + yDiff};
                } else if (current->x > second->x && current->y < second->y) {
                    a1 = {current->x + xDiff, current->y - yDiff};
                    a2 = {second->x - xDiff, second->y + yDiff};
                } else if (current->x == second->x) {
                    a1 = {current->x, current->y - yDiff};
                    a2 = {second->x, second->y + yDiff};
                } else {
                    a1 = {current->x - xDiff, current->y};
                    a2 = {second->x + xDiff, second->y};
                }

                if (!(a1.x < 0 || a1.x >= width || a1.y < 0 || a1.y >= height))
                    antiNodes.insert(a1);
                if (!(a2.x < 0 || a2.x >= width || a2.y < 0 || a2.y >= height))
                    antiNodes.insert(a2);
            }
        }
    }

    // Print(&lines, &antiNodes);


    return antiNodes.size();
}
