#include "Day2.h"

vector<int> removeAt(const vector<int> *arr, const int x) {
    vector<int> newArr{};

    for (int i = 0; i < arr->size(); ++i) {
        if (i == x) continue;
        newArr.push_back((*arr)[i]);
    }

    return newArr;
}

int isValidReport(const vector<int> *report) {
    int rising = -1;
    int valid{0};
    for (int i = 1; i < report->size(); ++i) {
        if (rising == -1) {
            if ((*report)[i - 1] < (*report)[i]) rising = 1;
            else if ((*report)[i - 1] > (*report)[i]) rising = 0;
            else {
                valid = i;
                break;
            }
        }
        if (rising == 1 && (*report)[i - 1] > (*report)[i]) {
            valid = i;
            break;
        }
        if (rising == 0 && (*report)[i - 1] < (*report)[i]) {
            valid = i;
            break;
        }
        if ((*report)[i - 1] == (*report)[i]) {
            valid = i;
            break;
        }
        if (abs((*report)[i - 1] - (*report)[i]) > 3) {
            valid = i;
            break;
        }
    }

    return valid;
}

int Day2::Part2() {
    const auto lines = Helpers::readFile(2);
    vector<vector<int> > reports{};

    for (const auto &line: lines) {
        vector<int> row{};
        for (const auto &col: Helpers::split(line, ' ')) {
            row.push_back(stoi(col));
        }
        reports.push_back(row);
    }

    int total{0};

    for (const auto &report: reports) {
        int invalid = isValidReport(&report);

        if (invalid > 0) {
            int valids{0};
            for (int i = 0; i < report.size(); ++i) {
                auto remove0 = removeAt(&report, i);
                int invalid0 = isValidReport(&remove0);
                if (invalid0 == 0) valids++;
            }
            if (valids == 0) {
                continue;
            }
        }

        total++;
    }

    return total;
}
