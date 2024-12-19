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

    map<int, tuple<int,string>> tMap{}; //index, length, towel
    for (auto towel: towels) {
        //find all instances and write to map
    }

    //go find all possible permutations within map

    return total;
}
