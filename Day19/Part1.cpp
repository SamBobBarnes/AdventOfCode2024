#include <queue>

#include "Day19.h"

bool Day19::isPossible(const vector<string> *towels, const string pattern) {
    bool possible = false;
    queue<string> q{};
    for (auto towel: *towels) q.push(towel);
    do {
        auto towel = q.front();
        q.pop();
        int i = pattern.find(towel);
        if (i != 0) continue;
        string next = pattern.substr(towel.length());
        if (next.length() == 0) return true;
        possible = isPossible(towels, next);
    } while (!(possible == true || q.empty()));

    return possible;
}


int Day19::Part1() {
    const auto lines = Helpers::readFile(19, false);

    const auto towels = Helpers::split(lines[0], ", ");

    vector<string> patterns{};

    for (int i = 2; i < lines.size(); i++) {
        patterns.push_back(lines[i]);
    }

    int total{0};

    for (auto pattern: patterns) {
        if (isPossible(&towels, pattern)) total++;
    }

    return total;
}
