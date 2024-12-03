#include <regex>

#include "Day3.h"

int Day3::Part1() {
    const auto lines = Helpers::readFile(3);

    const regex find{"mul\\([0-9]+,[0-9]+\\)"};

    vector<string> matches{};

    for (const auto &line: lines) {
        string log = line;
        for (std::smatch sm; regex_search(log, sm, find);) {
            matches.push_back(sm.str());
            log = sm.suffix();
        }
    }

    int total{0};

    for (auto match: matches) {
        auto parts = Helpers::split(match, ',');
        int first = stoi(parts[0].substr(4));
        int second = stoi(parts[1].substr(0, parts[1].length() - 1));

        total += first * second;
    }

    return total;
}
