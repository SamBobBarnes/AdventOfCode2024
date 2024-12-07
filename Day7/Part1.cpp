#include "Day7.h"

long Day7::Part1() {
    const auto lines = Helpers::readFile(7, false);

    vector<Equation> equations{};
    vector<char> operators{'+', '*'};

    for (const auto &line: lines) {
        vector<long> parts{};
        auto partsStrings = Helpers::split(Helpers::split(line, ':')[1].substr(1), ' ');
        parts.reserve(partsStrings.size());
        for (const auto &i: partsStrings) parts.push_back(stol(i));
        equations.emplace_back(stol(Helpers::split(line, ':')[0]), parts);
    }

    long total{0};

    for (const auto &e: equations) {
        if (SolveEquation(e, operators)) total += e.Answer;
    }

    return total;
}
