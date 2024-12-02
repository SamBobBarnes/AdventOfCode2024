#include "Day2.h"

int Day2::Part1() {
    const auto lines = Helpers::readFile(2);
    vector<vector<int> > reports{};

    for (auto line: lines) {
        vector<int> row{};
        for (auto col: Helpers::split(line, ' ')) {
            row.push_back(stoi(col));
        }
        reports.push_back(row);
    }

    int total{0};

    for (auto report: reports) {
        int rising = -1;
        bool valid{true};
        for (int i = 1; i < report.size(); ++i) {
            if (rising == -1) {
                if (report[i - 1] < report[i]) rising = 1;
                else if (report[i - 1] > report[i]) rising = 0;
                else {
                    valid = false;
                    break;
                }
            }
            if (rising == 1 && report[i - 1] > report[i]) {
                valid = false;
                break;
            }
            if (rising == 0 && report[i - 1] < report[i]) {
                valid = false;
                break;
            }
            if (report[i - 1] == report[i]) {
                valid = false;
                break;
            }
            if (abs(report[i - 1] - report[i]) > 3) {
                valid = false;
                break;
            }
        }
        if (!valid) continue;

        total++;
    }

    return total;
}
