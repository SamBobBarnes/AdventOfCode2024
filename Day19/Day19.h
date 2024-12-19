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

    static int countOptions(map<int, map<size_t, string> > *tMap, const string &pattern, const int i);
};

#endif //DAY19_H
