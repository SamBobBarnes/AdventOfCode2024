#include <map>

#include "Day19.h"
#include "../Point.h"

int Day19::countOptions(const vector<string> *towels, const string &pattern) {
    int permutations{0};
    for (auto towel: *towels) {
        int i = pattern.find(towel);
        if (i != 0) continue;
        string next = pattern.substr(towel.length());
        if (next.length() == 0) {
            permutations++;
            continue;
        }
        permutations += countOptions(towels, next);
    };

    return permutations;
}


int Day19::Part2() {
    const auto lines = Helpers::readFile(19, true);

    const auto towels = Helpers::split(lines[0], ", ");

    vector<string> patterns{};

    for (int i = 2; i < lines.size(); i++) {
        patterns.push_back(lines[i]);
    }

    int total{0};
    vector<string> possiblePatterns{};

    for (auto pattern: patterns) {
        if (isPossible(&towels, pattern)) possiblePatterns.push_back(pattern);
    }

    // for (auto pattern: possiblePatterns) {
    //     total += countOptions(&towels, pattern);
    // }

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
        //find all instances and write to map
        auto length = towel.length();
        auto is = findAll(pattern, towel);
        for (auto &i: is) {
            tMap[i][length] = towel;
        }
    }

    //go find all possible permutations within map

    return total;
}
