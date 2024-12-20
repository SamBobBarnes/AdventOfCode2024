#ifndef DAY17_H
#define DAY17_H

#include "../Helpers.h"

using namespace std;

class Day17 {
public:
    static string Part1();

    static int Part2();

    static string program2String(vector<int> *program) {
        string programString = "";
        for (auto i: *program) {
            programString += "," + to_string(i);
        }
        return programString;
    }

    static bool checkLast(vector<int> *program, vector<int> *against, const int startAt) {
        for (int i = startAt; i < program->size(); i++) {
            if ((*against)[i] != (*program)[i]) return false;
        }
        return true;
    }

    static bool findA(uint64_t A, vector<int> *program, const int i, auto &run) {
        for (int j = -1; j < 8; j++) {
            if (j > -1) // leave as 0
                A += powl(8, i);

            if (i == 0) {
                std::cout << std::oct << A << std::dec << ": i=" << i << " j=" << j << std::endl;
                auto result = run(A, program);
                if (result == *program) {
                    cout << "answer: " << A << endl;
                    return true;
                }
            }
            findA(A, program, i - 1, run);
        }
        return false;
    };
};

#endif //DAY17_H
