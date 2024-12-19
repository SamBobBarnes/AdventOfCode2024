#ifndef DAY19_H
#define DAY19_H

#include "../Helpers.h"

using namespace std;

class Day19 {
public:
    static int Part1();

    static int Part2();

    static bool isPossible(const vector<string> *towels, const string &pattern);

    static int countOptions(const vector<string> *towels, const string &pattern);
};

#endif //DAY19_H
