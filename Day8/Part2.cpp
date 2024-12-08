#include <set>
#include <map>

#include "Day8.h"
#include "../Point.h"

int Day8::Part2() {
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
            antiNodes.insert(*current);
            for (int j = i + 1; j < group.size(); ++j) {
                const Point *second = &group[j];
                const int xDiff = abs(current->x - second->x);
                const int yDiff = abs(current->y - second->y);

                Point a1;
                Point a2;

                int arrangement;

                if (current->x < second->x && current->y < second->y) {
                    arrangement = 0;
                } else if (current->x > second->x && current->y < second->y) {
                    arrangement = 1;
                } else if (current->x == second->x) {
                    arrangement = 2;
                } else {
                    arrangement = 3;
                }

                switch (arrangement) {
                    case 0:
                        a1 = {current->x - xDiff, current->y - yDiff};
                        a2 = {second->x + xDiff, second->y + yDiff};
                        break;
                    case 1:
                        a1 = {current->x + xDiff, current->y - yDiff};
                        a2 = {second->x - xDiff, second->y + yDiff};
                        break;
                    case 2:
                        a1 = {current->x, current->y - yDiff};
                        a2 = {second->x, second->y + yDiff};
                        break;
                    case 3:
                        a1 = {current->x - xDiff, current->y};
                        a2 = {second->x + xDiff, second->y};
                        break;
                }

                while (!(a1.x < 0 || a1.x >= width || a1.y < 0 || a1.y >= height)) {
                    antiNodes.insert(a1);

                    switch (arrangement) {
                        case 0:
                            a1 = {a1.x - xDiff, a1.y - yDiff};
                            break;
                        case 1:
                            a1 = {a1.x + xDiff, a1.y - yDiff};
                            break;
                        case 2:
                            a1 = {a1.x, a1.y - yDiff};
                            break;
                        case 3:
                            a1 = {a1.x - xDiff, a1.y};
                            break;
                    }
                }
                while (!(a2.x < 0 || a2.x >= width || a2.y < 0 || a2.y >= height)) {
                    antiNodes.insert(a2);

                    switch (arrangement) {
                        case 0:
                            a2 = {a2.x + xDiff, a2.y + yDiff};
                            break;
                        case 1:
                            a2 = {a2.x - xDiff, a2.y + yDiff};
                            break;
                        case 2:
                            a2 = {a2.x, a2.y + yDiff};
                            break;
                        case 3:
                            a2 = {a2.x + xDiff, a2.y};
                            break;
                    }
                }
            }
        }
        antiNodes.insert(group.back());
    }

    // Print(&lines, &antiNodes);

    return antiNodes.size();
}
