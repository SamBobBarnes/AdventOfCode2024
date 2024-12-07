#ifndef DAY7_H
#define DAY7_H

#include <utility>

#include "../Helpers.h"

using namespace std;

struct Equation {
    Equation(const long answer, vector<long> parts): Answer(answer), Parts(std::move(parts)) {
    }

    long Answer;
    vector<long> Parts;
    vector<char> Operators{};

    [[nodiscard]] bool Full() const {
        return Operators.size() == Parts.size() - 1;
    }

    bool CorrectOperators() {
        long total{Parts[0]};
        for (int i = 0; i < Operators.size(); ++i) {
            total = perform(total, Parts[i + 1], Operators[i]);
        }
        return total == Answer;
    }

private :
    long perform(long a, long b, char _operator) {
        switch (_operator) {
            case '+':
                return a + b;
            case '*':
                return a * b;
            case '|':
                int size = trunc(log10(b)) + 1;
                long ten = powl(10, size);
                return a * ten + b;
        }
    }
};

class Day7 {
public:
    static long Part1();

    static long Part2();

    static bool SolveEquation(Equation e, const vector<char> &operators);
};

inline bool Day7::SolveEquation(Equation e, const vector<char> &operators) {
    if (e.Full()) {
        return e.CorrectOperators();
    }

    vector<bool> results{};

    for (auto op: operators) {
        Equation e1 = e;
        e1.Operators.push_back(op);
        results.push_back(SolveEquation(e1, operators));
    }

    for (const bool result: results) {
        if (result) return true;
    }
    return false;
}

#endif //DAY7_H
