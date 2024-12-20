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
};

#endif //DAY17_H
