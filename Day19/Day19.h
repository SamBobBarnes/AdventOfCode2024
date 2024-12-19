#ifndef DAY19_H
#define DAY19_H

#include "../Helpers.h"
#include <map>

using namespace std;

class Day19 {
public:
    static int Part1();

    static uint64_t Part2();

    static bool isPossible(const vector<string> *towels, const string &pattern);

    static uint64_t countOptions(map<int, uint64_t> *tMap, const vector<string> *towels, const string &pattern,
                                 const int i);
};

#endif //DAY19_H
