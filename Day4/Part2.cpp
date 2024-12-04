#include <regex>
#include <set>
#include <map>
#include <__algorithm/ranges_set_intersection.h>

#include "Day4.h"
#include "../Point.h"

int Day4::Part2() {
    const auto wordSearch = Helpers::readFile(4, true);

    int height = wordSearch.size();
    int width = wordSearch[0].length();

    vector<map<Point, Point> > pointMappings{
        {}, {}, {}, {}, {}, {}, {}, {},
    };

    // up ur right dr down dl left ul
    vector<string> rotations[8]{{}, {}, wordSearch, {}, {}, {}, {}, {}};
    for (int y = 0; y < height; ++y) {
        string left;
        for (int x = 0; x < width; ++x) {
            left += wordSearch[y][width - x - 1];
            pointMappings[6][{width - x - 1, y}] = {x, y};
            pointMappings[2][{x, y}] = {x, y};
        }
        rotations[6].push_back(left);
    }

    for (int x = 0; x < width; ++x) {
        string up{};
        string down{};
        for (int y = 0; y < height; ++y) {
            up += wordSearch[height - y - 1][x];
            pointMappings[0][{x, height - y - 1}] = {x, y};
            down += wordSearch[y][x];
            pointMappings[4][{x, y}] = {y, x};
        }
        rotations[0].push_back(up);
        rotations[4].push_back(down);
    }

    int mx{0}, my{0};
    for (int col = width - 1; col > 0; col--) {
        string ur;
        string dr;
        string dl;
        string ul;
        int x{col}, y{0};
        while (x < width && y < height) {
            ur += rotations[0][y][x]; //TODO: fix this
            pointMappings[1][{mx, my}] = pointMappings[0][{x, y}];
            dr += rotations[2][y][x];
            pointMappings[3][{mx, my}] = pointMappings[2][{x, y}];
            dl += rotations[4][height - y - 1][x];
            pointMappings[5][{mx, my}] = pointMappings[4][{x, height - y - 1}];
            ul += rotations[6][height - y - 1][x];
            pointMappings[7][{mx, my}] = pointMappings[6][{x, height - y - 1}];
            x++;
            y++;
            mx++;
        }
        rotations[1].push_back(ur);
        rotations[3].push_back(dr);
        rotations[5].push_back(dl);
        rotations[7].push_back(ul);
        my++;
        mx = 0;
    }
    for (int row = 0; row < height; row++) {
        string ur;
        string dr;
        string dl;
        string ul;
        int x{0}, y{row};
        while (x < width && y < height) {
            ur += rotations[0][y][x];
            pointMappings[1][{mx, my}] = pointMappings[0][{x, y}];
            dr += rotations[2][y][x];
            pointMappings[3][{mx, my}] = pointMappings[2][{x, y}];
            dl += rotations[4][height - y - 1][x];
            pointMappings[5][{mx, my}] = pointMappings[4][{x, height - y - 1}];
            ul += rotations[6][height - y - 1][x];
            pointMappings[7][{mx, my}] = pointMappings[6][{x, height - y - 1}];
            x++;
            y++;
            mx++;
        }
        rotations[1].push_back(ur);
        rotations[3].push_back(dr);
        rotations[5].push_back(dl);
        rotations[7].push_back(ul);
        my++;
        mx = 0;
    }

    regex word{R"(MAS)"};

    int total{0};

    vector<Point> points[8]{{}, {}, {}, {}, {}, {}, {}, {}};

    int index = 0;
    for (auto rotation: rotations) {
        for (int i = 0; i < rotation.size(); ++i) {
            string log = rotation[i];
            int offset = 0;
            for (std::smatch sm; regex_search(log, sm, word);) {
                points[index].push_back(pointMappings[index][{static_cast<int>(sm.position() + 1 + offset), i}]);
                offset += sm.position() + 3;
                log = sm.suffix();
            }
        }
        index++;
    }

    set<Point> rectifiedPoints[4]{{}, {}, {}, {}};

    rectifiedPoints[0].insert_range(points[2]);
    rectifiedPoints[0].insert_range(points[6]);
    rectifiedPoints[1].insert_range(points[0]);
    rectifiedPoints[1].insert_range(points[4]);
    rectifiedPoints[2].insert_range(points[1]);
    rectifiedPoints[2].insert_range(points[3]);
    rectifiedPoints[3].insert_range(points[5]);
    rectifiedPoints[3].insert_range(points[7]);


    set<Point> commonPoints[2]{{}, {}};

    set_intersection(rectifiedPoints[0].begin(), rectifiedPoints[0].end(), rectifiedPoints[1].begin(),
                     rectifiedPoints[1].end(),
                     inserter(commonPoints[0], commonPoints[0].begin()));

    set_intersection(rectifiedPoints[2].begin(), rectifiedPoints[2].end(), rectifiedPoints[3].begin(),
                     rectifiedPoints[3].end(),
                     inserter(commonPoints[1], commonPoints[1].begin()));

    return total;
}
