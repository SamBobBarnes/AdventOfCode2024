#include <map>
#include <queue>

#include "Day12.h"
#include "GardenPlot.h"

int Day12::Part1() {
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
    map<int, int> groupPerimeters{};

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
                    if (garden[y][x - 1].Plant == plant) {
                        if (!garden[y][x - 1].hasGroup())q.push(&garden[y][x - 1]);
                    } else {
                        groupPerimeters[groupIndex]++;
                    }
                } else groupPerimeters[groupIndex]++;
                if (x < width - 1) {
                    if (garden[y][x + 1].Plant == plant) {
                        if (!garden[y][x + 1].hasGroup())q.push(&garden[y][x + 1]);
                    } else {
                        groupPerimeters[groupIndex]++;
                    }
                } else groupPerimeters[groupIndex]++;
                if (y > 0) {
                    if (garden[y - 1][x].Plant == plant) {
                        if (!garden[y - 1][x].hasGroup())q.push(&garden[y - 1][x]);
                    } else {
                        groupPerimeters[groupIndex]++;
                    }
                } else groupPerimeters[groupIndex]++;
                if (y < height - 1) {
                    if (garden[y + 1][x].Plant == plant) {
                        if (!garden[y + 1][x].hasGroup())q.push(&garden[y + 1][x]);
                    } else {
                        groupPerimeters[groupIndex]++;
                    }
                } else groupPerimeters[groupIndex]++;
            }

            groupIndex++;
        }
    }

    int total{0};

    for (const auto group: groupPerimeters | views::keys) {
        total += groupAreas[group] * groupPerimeters[group];
    }

    return total;
}
