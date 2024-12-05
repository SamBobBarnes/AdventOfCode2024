#include <map>

#include "Day5.h"

int Day5::Part1() {
    const auto lines = Helpers::readFile(5, false);

    map<int, vector<int> > rules{};
    vector<vector<int> > printJobs{};

    bool jobs{false};
    for (const auto &line: lines) {
        if (line.empty()) {
            jobs = true;
            continue;
        }
        if (jobs) {
            vector<int> job{};
            for (const auto &sheet: Helpers::split(line, ',')) {
                job.push_back(stoi(sheet));
            }
            printJobs.push_back(job);
        } else {
            auto rule = Helpers::split(line, '|');

            if (rules.contains(stoi(rule[0]))) {
                rules[stoi(rule[0])].push_back(stoi(rule[1]));
            } else {
                rules[stoi(rule[0])] = {stoi(rule[1])};
            }
        }
    }

    vector<vector<int> > validJobs{};

    for (const auto &job: printJobs) {
        bool valid{true};
        vector<int> printedSheets{};
        for (auto sheet: job) {
            if (rules.contains(sheet)) {
                // check rules
                for (auto after: rules[sheet]) {
                    if (ranges::find(printedSheets, after) != printedSheets.end()) {
                        valid = false;
                        break;
                    }
                }
            }
            if (!valid) break;
            printedSheets.push_back(sheet);
        }
        if (valid) validJobs.push_back(job);
    }

    int total{0};

    for (auto job: validJobs) {
        int length = job.size();
        int midPoint = length / 2;
        total += job[midPoint];
    }

    return total;
}
