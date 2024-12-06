#include <map>

#include "Day5.h"

bool ValidJob(const vector<int> *job, map<int, vector<int> > *rules) {
    bool valid{true};
    vector<int> printedSheets{};
    for (auto sheet: *job) {
        if (rules->contains(sheet)) {
            // check rules
            for (auto after: (*rules)[sheet]) {
                if (ranges::find(printedSheets, after) != printedSheets.end()) {
                    valid = false;
                    break;
                }
            }
        }
        if (!valid) break;
        printedSheets.push_back(sheet);
    }
    return valid;
}

tuple<int, int> InvalidIndex(const vector<int> *job, map<int, vector<int> > *rules) {
    int invalidIndex{-1};
    int invalidIndex2{-1};
    vector<int> printedSheets{};
    int index{0};
    for (auto sheet: *job) {
        if (rules->contains(sheet)) {
            // check rules
            for (auto after: (*rules)[sheet]) {
                auto it = ranges::find(printedSheets, after);
                if (it != printedSheets.end()) {
                    invalidIndex = index;
                    invalidIndex2 = std::distance(printedSheets.begin(), it);
                    break;
                }
            }
        }
        if (invalidIndex >= 0) break;
        printedSheets.push_back(sheet);
        index++;
    }
    return {invalidIndex, invalidIndex2};
}

int Day5::Part2() {
    const auto lines = Helpers::readFile(5);

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

    vector<vector<int> > invalidJobs{};

    for (const auto &job: printJobs) {
        if (!ValidJob(&job, &rules)) invalidJobs.push_back(job);
    }

    int total{0};

    for (auto &job: invalidJobs) {
        vector<int> tempJob{};
        for (auto i: job) {
            tempJob.push_back(i);
        }
        while (!ValidJob(&tempJob, &rules)) {
            auto indecies = InvalidIndex(&tempJob, &rules);
            int index = get<0>(indecies);
            int index2 = get<1>(indecies);
            vector<int> tempOrder{};
            for (int i = 0; i < tempJob.size(); ++i) {
                if (i == index2) continue;
                tempOrder.push_back(tempJob[i]);
                if (i == index) tempOrder.push_back(tempJob[index2]);
            }
            tempJob = tempOrder;
        }
        int centerIndex = tempJob.size() / 2;
        total += tempJob[centerIndex];
    }

    return total;
}
