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
        }
    }
};

class Day7 {
public:
    static long Part1();

    static int Part2();

    static bool SolveEquation(Equation e, char operators[]);
};

inline bool Day7::SolveEquation(Equation e, char operators[]) {
    if (e.Full()) {
        return e.CorrectOperators();
    }

    Equation e1 = e;
    e1.Operators.push_back(operators[0]);
    bool e1a = SolveEquation(e1, operators);
    Equation e2 = e;
    e2.Operators.push_back(operators[1]);
    bool e2a = SolveEquation(e2, operators);

    return e1a || e2a;
}

#endif //DAY7_H
