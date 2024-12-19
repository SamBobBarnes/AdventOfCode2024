#include <map>

#include "Day19.h"
#include "../Point.h"

int Day19::countOptions(map<int, map<size_t, string> > *tMap, const string &pattern, const int i) {
    if (i == pattern.length()) return 1;
    int permutations = 0;
    auto current = (*tMap)[i];
    for (auto [size,_]: current) {
        permutations += countOptions(tMap, pattern, i + size);
    }
    return permutations;
}

struct memo {
    int index;
    vector<memo> options;
};


long long Day19::Part2() {
    const auto lines = Helpers::readFile(19, false);

    const auto towels = Helpers::split(lines[0], ", ");

    vector<string> patterns{};

    for (int i = 2; i < lines.size(); i++) {
        patterns.push_back(lines[i]);
    }

    long long total{0};
    vector<string> possiblePatterns{};

    for (auto pattern: patterns) {
        if (isPossible(&towels, pattern)) possiblePatterns.push_back(pattern);
    }

    // for (auto pattern: possiblePatterns) {
    auto pattern = possiblePatterns[0];
    auto findAll = [](const string &pattern, const string &t)-> vector<int> {
        vector<int> indices{};
        int i = -1;
        int location = 0;
        do {
            i = pattern.find(t, location);
            if (i >= 0)indices.push_back(i);
            location = i + 1;
        } while (i >= 0);
        return indices;
    };

    map<int, map<size_t, string> > tMap{}; //index, length, towel
    for (const auto &towel: towels) {
        auto length = towel.length();
        auto is = findAll(pattern, towel);
        for (auto &i: is) {
            tMap[i][length] = towel;
        }
    }
    // int i = pattern.length() - 1;

    // map<int, int> memo{};
    //
    // do {
    //     auto options = tMap[i];
    //     if (options.empty())
    //         memo[i] = 0;
    //     i--;
    // } while (i > 0);
    // }
    return total;
}
