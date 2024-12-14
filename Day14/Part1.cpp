#include "Day14.h"
#include "Robot.h"

int Day14::Part1() {
    const auto lines = Helpers::readFile(14, false);
    vector<Robot> bots{};
    bots.reserve(lines.size());

    for (const auto &line: lines) {
        bots.emplace_back(line);
    }

    int rounds = 100;

    // const int width = 11;
    // const int height = 7;

    const int width = 101;
    const int height = 103;


    auto centerX = width / 2;
    auto centerY = height / 2;
    vector<tuple<Point, Point> > quads{
        {{0, 0}, {centerX - 1, centerY - 1}},
        {{0, centerY + 1}, {centerX - 1, height - 1}},
        {{centerX + 1, 0}, {width - 1, centerY - 1}},
        {{centerX + 1, centerY + 1}, {width - 1, height - 1}}
    };

    int quadTotals[4]{};

    for (auto r: bots) {
        auto xpos = r.pos.x + r.speed.x * rounds;
        auto ypos = r.pos.y + r.speed.y * rounds;

        auto modX = (xpos % width);
        if (modX < 0) modX = (modX + width) % width;
        auto modY = (ypos % height);
        if (modY < 0) modY = (modY + height) % height;

        r.pos = {modX, modY};

        for (int i = 0; i < 4; i++) {
            if (r.pos.x >= get<0>(quads[i]).x &&
                r.pos.x <= get<1>(quads[i]).x &&
                r.pos.y >= get<0>(quads[i]).y &&
                r.pos.y <= get<1>(quads[i]).y)
                quadTotals[i]++;
        }
    }


    return quadTotals[0] * quadTotals[1] * quadTotals[2] * quadTotals[3];
}
