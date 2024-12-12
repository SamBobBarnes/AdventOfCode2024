#include <map>
#include <queue>

#include "Day12.h"
#include "GardenPlot.h"

int Day12::Part2() {
    const auto lines = Helpers::readFile(12, false);

    int height = lines.size();
    int width = lines[0].length();
    vector<vector<GardenPlot> > garden{};

    for (int y = 0; y < lines.size(); ++y) {
        vector<GardenPlot> row{};
        row.reserve(lines[0].length());
        for (int x = 0; x < lines[0].length(); ++x) {
            row.push_back({lines[y][x], {x, y}});
        }
        garden.push_back(row);
    }

    int groupIndex{0};

    map<int, int> groupAreas{};
    map<int, int> groupSides{};

    for (auto &row: garden) {
        for (auto &plot: row) {
            if (plot.hasGroup()) continue;

            queue<GardenPlot *> q{};
            q.push(&plot);

            while (!q.empty()) {
                auto u = q.front();
                q.pop();

                if (u->hasGroup()) continue;
                u->group = groupIndex;
                groupAreas[groupIndex]++;

                int x = u->Position.x;
                int y = u->Position.y;
                char plant = u->Plant;

                if (x > 0) {
                    //left
                    if (garden[y][x - 1].Plant == plant) {
                        if (!garden[y][x - 1].hasGroup())q.push(&garden[y][x - 1]);
                    } else {
                        u->Perimeters[3] = true;
                    }
                } else u->Perimeters[3] = true;
                if (x < width - 1) {
                    //right
                    if (garden[y][x + 1].Plant == plant) {
                        if (!garden[y][x + 1].hasGroup())q.push(&garden[y][x + 1]);
                    } else {
                        u->Perimeters[1] = true;
                    }
                } else u->Perimeters[1] = true;
                if (y > 0) {
                    //up
                    if (garden[y - 1][x].Plant == plant) {
                        if (!garden[y - 1][x].hasGroup())q.push(&garden[y - 1][x]);
                    } else {
                        u->Perimeters[0] = true;
                    }
                } else u->Perimeters[0] = true;
                if (y < height - 1) {
                    //down
                    if (garden[y + 1][x].Plant == plant) {
                        if (!garden[y + 1][x].hasGroup())q.push(&garden[y + 1][x]);
                    } else {
                        u->Perimeters[2] = true;
                    }
                } else u->Perimeters[2] = true;
            }

            groupIndex++;
        }
    }

    for (int y = 0; y < garden.size(); ++y) {
        int lastGroup = -1;
        bool topColine{false};
        bool bottomColine{false};
        for (int x = 0; x < garden[0].size(); ++x) {
            int group = garden[y][x].group;
            bool top = garden[y][x].Perimeters[0];
            bool bottom = garden[y][x].Perimeters[2];
            if (!top && !bottom) {
                topColine = false;
                bottomColine = false;
                continue;
            }

            if (lastGroup != group) {
                topColine = false;
                bottomColine = false;
            }
            if (bottom) {
                if (!bottomColine) {
                    groupSides[group]++;
                    bottomColine = true;
                }
            } else {
                bottomColine = false;
            }
            if (top) {
                if (!topColine) {
                    groupSides[group]++;
                    topColine = true;
                }
            } else {
                topColine = false;
            }


            lastGroup = group;
        }
    }

    for (int x = 0; x < garden.size(); ++x) {
        int lastGroup = -1;
        bool leftColine{false};
        bool rightColine{false};
        for (int y = 0; y < garden[0].size(); ++y) {
            int group = garden[y][x].group;
            bool left = garden[y][x].Perimeters[3];
            bool right = garden[y][x].Perimeters[1];
            if (!left && !right) {
                leftColine = false;
                rightColine = false;
                continue;
            }

            if (lastGroup != group) {
                leftColine = false;
                rightColine = false;
            }
            if (right) {
                if (!rightColine) {
                    groupSides[group]++;
                    rightColine = true;
                }
            } else {
                rightColine = false;
            }
            if (left) {
                if (!leftColine) {
                    groupSides[group]++;
                    leftColine = true;
                }
            } else {
                leftColine = false;
            }


            lastGroup = group;
        }
    }

    int total{0};

    for (const auto group: groupSides | views::keys) {
        total += groupAreas[group] * groupSides[group];
    }

    return total;
}
