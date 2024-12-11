#include "Day11.h"

long long Day11::Part1() {
    const auto lines = Helpers::readFile(11, false);

    // 0 -> 1
    // even number of digits becomes two stones split down the middle
    // else old * 2024

    int rounds{25};
    vector<long long> stones{};
    for (const auto &i: Helpers::split(lines[0], ' ')) stones.push_back(stoi(i));

    for (int i = 0; i < rounds; ++i) {
        vector<long long> temp{};

        for (const auto stone: stones) {
            if (stone == 0) {
                temp.push_back(1);
            } else if (auto stoneString = to_string(stone); stoneString.length() % 2 == 0) {
                temp.push_back(stoi(stoneString.substr(0, stoneString.length() / 2)));
                temp.push_back(stoi(stoneString.substr(stoneString.length() / 2)));
            } else {
                temp.push_back(stone * 2024);
            }
        }
        stones = temp;
    }

    return stones.size();
}
