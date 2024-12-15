#include <map>

#include "Day14.h"
#include "Robot.h"
#include "../Point.h"

string Print(const int i, const int width, const int height, const vector<Robot> *bots) {
    map<Point, int> botMap{};

    for (auto bot: (*bots)) {
        botMap[bot.pos] = 1;
    }

    string printedMap = to_string(i) + "\n";

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (botMap[{x, y}] > 0) printedMap += "#";
            else printedMap += ".";
        }
        printedMap += "\n";
    }

    return printedMap;
}

int Day14::Part2() {
    const auto lines = Helpers::readFile(14, false);
    vector<Robot> bots{};
    bots.reserve(lines.size());

    for (const auto &line: lines) {
        bots.emplace_back(line);
    }

    int rounds = 1000000;

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

    long long minDanger{Helpers::MaxLL};
    int minDangerRound{-1};

    system("touch output.txt");

    std::ofstream outfile;

    outfile.open("output.txt", std::ios_base::app); // append instead of overwrite

    for (int round = 0; round < rounds; round++) {
        int quadTotals[4]{};
        map<Point, int> uniqueMap{};

        for (auto r: bots) {
            auto xpos = r.pos.x + r.speed.x;
            auto ypos = r.pos.y + r.speed.y;

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
            uniqueMap[r.pos]++;
        }

        bool unique = true;
        for (auto count: uniqueMap | views::values) {
            if (count > 1) unique = false;
        }

        if (unique) cout << round << endl;

        // long long danger = quadTotals[0] * quadTotals[1] * quadTotals[2] * quadTotals[3];
        //
        // if (danger < minDanger) {
        //     minDanger = danger;
        //     minDangerRound = round;
        // }
        // outfile << Print(round, width, height, &bots);
    }

    return minDangerRound;
}
