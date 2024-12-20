#include <algorithm>
#include <regex>
#include <set>
#include <map>

#include "Day4.h"
#include "../Point.h"

void Print(vector<Point> points, const vector<string> *grid) {
    for (int y = 0; y < grid->size(); ++y) {
        for (int x = 0; x < (*grid)[0].length(); ++x) {
            // auto it = find(points.begin(), points.end(), new Point{x, y});
            if (ranges::find_if(points, [x,y](const Point &p) { return p.x == x && p.y == y; }) != points.end()) {
                cout << "\033[31;4m" << (*grid)[y][x] << "\033[0m";
            } else {
                cout << (*grid)[y][x];
            }
        }
        cout << endl;
    }
}

int Day4::Part2() {
    const auto wordSearch = Helpers::readFile(4);

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
            pointMappings[0][{y, x}] = {x, height - y - 1};
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


    // for (int i = 0; i < 8; ++i) {
    //     cout << endl;
    //     Print(points[i], &rotations[2]);
    // }
    set<Point> rectifiedPoints[4]{{}, {}, {}, {}};

    for (auto i: points[2]) {
        rectifiedPoints[0].insert(i);
    }
    for (auto i: points[6]) {
        rectifiedPoints[0].insert(i);
    }
    for (auto i: points[0]) {
        rectifiedPoints[1].insert(i);
    }
    for (auto i: points[4]) {
        rectifiedPoints[1].insert(i);
    }
    for (auto i: points[1]) {
        rectifiedPoints[20].insert(i);
    }
    for (auto i: points[5]) {
        rectifiedPoints[2].insert(i);
    }
    for (auto i: points[3]) {
        rectifiedPoints[3].insert(i);
    }
    for (auto i: points[7]) {
        rectifiedPoints[3].insert(i);
    }


    set<Point> commonPoints[2]{{}, {}};

    set_intersection(rectifiedPoints[0].begin(), rectifiedPoints[0].end(), rectifiedPoints[1].begin(),
                     rectifiedPoints[1].end(),
                     inserter(commonPoints[0], commonPoints[0].begin()));

    set_intersection(rectifiedPoints[2].begin(), rectifiedPoints[2].end(), rectifiedPoints[3].begin(),
                     rectifiedPoints[3].end(),
                     inserter(commonPoints[1], commonPoints[1].begin()));

    total += commonPoints[1].size();
    return total;
}
