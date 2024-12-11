#include <map>

#include "Day11.h"

long long Day11::Part2() {
    const auto lines = Helpers::readFile(11, false);

    int rounds{75};
    map<long long, long long> stones{};
    for (const auto &i: Helpers::split(lines[0], ' ')) stones[stoi(i)] = 1;

    for (int i = 0; i < rounds; ++i) {
        map<long long, long long> temp{};

        for (const auto [stone,amt]: stones) {
            if (stone == 0) {
                temp[1] += amt;
            } else if (auto stoneString = to_string(stone); stoneString.length() % 2 == 0) {
                temp[stoi(stoneString.substr(0, stoneString.length() / 2))] += amt;
                temp[stoi(stoneString.substr(stoneString.length() / 2))] += amt;
            } else {
                temp[stone * 2024] += amt;
            }
        }
        stones = temp;
    }

    long long total{0};

    for (const auto [stone,amt]: stones) total += amt;

    return total;
}
