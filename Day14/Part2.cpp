#include <map>
#include <set>
#include <algorithm>

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

long long Day14::Part2() {
    const auto lines = Helpers::readFile(14, false);
    vector<Robot> bots{};
    bots.reserve(lines.size());

    for (const auto &line: lines) {
        bots.emplace_back(line);
    }

    const int width = 101;
    const int height = 103;

    const int rounds{10000};

    ofstream output("output.txt");

    for (int i = 0; i < rounds; i++) {
        auto centerX = width / 2;
        auto centerY = height / 2;
        vector<tuple<Point, Point> > quads{
            {{0, 0}, {centerX - 1, centerY - 1}},
            {{0, centerY + 1}, {centerX - 1, height - 1}},
            {{centerX + 1, 0}, {width - 1, centerY - 1}},
            {{centerX + 1, centerY + 1}, {width - 1, height - 1}}
        };

        int quadTotals[4]{};

        for (auto &r: bots) {
            r.pos.x = (((r.pos.x + r.speed.x) % width) + width) % width;
            r.pos.y = (((r.pos.y + r.speed.y) % height) + height) % height;

            for (int j = 0; j < 4; j++) {
                if (r.pos.x >= get<0>(quads[j]).x &&
                    r.pos.x <= get<1>(quads[j]).x &&
                    r.pos.y >= get<0>(quads[j]).y &&
                    r.pos.y <= get<1>(quads[j]).y)
                    quadTotals[j]++;
            }
        }

        // scores.push_back(quadTotals[0] * quadTotals[1] * quadTotals[2] * quadTotals[3]);

        output << i << endl << Print(i, width, height, &bots) << endl;
    }

    // vector<long long> originalScores = scores;
    //
    // ranges::sort(scores);
    //
    // auto it = ranges::find(originalScores, scores[0]);

    // return distance(originalScores.begin(), it);
    return 0;
}
