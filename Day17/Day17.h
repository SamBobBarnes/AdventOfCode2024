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

    static vector<int> execute(uint64_t input) {
        uint64_t A = input;
        uint64_t B = 0;
        uint64_t C = 0;
        vector<int> output{};
        do {
            B = A % 8;
            B = B ^ 1;
            C = A / static_cast<uint64_t>(pow(2, B));
            A = A / 8;
            B = B ^ 4;
            B = B ^ C;
            output.push_back(B % 8);
        } while (A != 0);

        return output;
    };

    static bool solve(uint64_t A, const vector<int> &program) {
        if (execute(A) == program) {
            cout << A << endl;
            return true;
        }
        A = A << 3;
        for (int i = 0; i < 8; i++) {
            const auto output = execute(A);
            bool same = true;
            for (int j = 0; j < output.size(); j++) {
                same = same && output[j] == program[program.size() - output.size() + j];
            }
            if (same && solve(A, program)) return true;
            A++;
        }
        return false;
    }
};

#endif //DAY17_H
