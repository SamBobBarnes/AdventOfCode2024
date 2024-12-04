#include <regex>
#include <set>

#include "Day4.h"
#include "../Point.h"

int Day4::Part1() {
    const auto wordSearch = Helpers::readFile(4, false);

    int height = wordSearch.size();
    int width = wordSearch[0].length();

    // up ur right dr down dl left ul
    vector<string> rotations[8]{{}, {}, wordSearch, {}, {}, {}, {}, {}};
    for (int y = 0; y < height; ++y) {
        string left;
        for (int x = 0; x < width; ++x) {
            left += wordSearch[y][width - x - 1];
        }
        rotations[6].push_back(left);
    }

    for (int x = 0; x < width; ++x) {
        string up{};
        string down{};
        for (int y = 0; y < height; ++y) {
            up += wordSearch[height - y - 1][x];
            down += wordSearch[y][x];
        }
        rotations[0].push_back(up);
        rotations[4].push_back(down);
    }

    for (int col = width - 1; col > 0; col--) {
        string ur;
        string dr;
        string dl;
        string ul;
        int x{col}, y{0};
        while (x < width && y < height) {
            ur += rotations[0][y][x];
            dr += rotations[2][y][x];
            dl += rotations[4][height - y - 1][x];
            ul += rotations[6][height - y - 1][x];
            x++;
            y++;
        }
        rotations[1].push_back(ur);
        rotations[3].push_back(dr);
        rotations[5].push_back(dl);
        rotations[7].push_back(ul);
    }
    for (int row = 0; row < height; row++) {
        string ur;
        string dr;
        string dl;
        string ul;
        int x{0}, y{row};
        while (x < width && y < height) {
            ur += rotations[0][y][x];
            dr += rotations[2][y][x];
            dl += rotations[4][height - y - 1][x];
            ul += rotations[6][height - y - 1][x];
            x++;
            y++;
        }
        rotations[1].push_back(ur);
        rotations[3].push_back(dr);
        rotations[5].push_back(dl);
        rotations[7].push_back(ul);
    }

    regex word{R"(XMAS)"};

    int total{0};

    for (auto rotation: rotations) {
        for (int i = 0; i < rotation.size(); ++i) {
            string log = rotation[i];
            for (std::smatch sm; regex_search(log, sm, word);) {
                total++;
                log = sm.suffix();
            }
        }
    }

    return total;
}
