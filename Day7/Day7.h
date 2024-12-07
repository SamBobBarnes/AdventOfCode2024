#ifndef DAY7_H
#define DAY7_H

#include <utility>

#include "../Helpers.h"

using namespace std;

class Day7 {
public:
    static int Part1();

    static int Part2();
};

struct Equation {
    Equation(const int answer, vector<int> parts): Answer(answer), Parts(std::move(parts)) {
    }

    int Answer;
    vector<int> Parts;
};

#endif //DAY7_H
