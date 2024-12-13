//
// Created by Samuel Barnes on 12/12/24.
//

#ifndef CLAWMACHINE_H
#define CLAWMACHINE_H
#include <string>

#include "../Helpers.h"


class ClawMachine {
public:
    explicit ClawMachine(const std::string lines[3]) {
        const auto aInfo = Helpers::split(lines[0], ' ');
        const auto bInfo = Helpers::split(lines[1], ' ');
        const auto prizeInfo = Helpers::split(lines[2], ' ');

        ax = stoi(aInfo[2].substr(2, aInfo[2].length() - 3));
        ay = stoi(aInfo[3].substr(2, aInfo[3].length() - 2));
        bx = stoi(bInfo[2].substr(2, bInfo[2].length() - 3));
        by = stoi(bInfo[3].substr(2, bInfo[3].length() - 2));
        prizeX = stoi(prizeInfo[1].substr(2, prizeInfo[1].length() - 3));
        prizeY = stoi(prizeInfo[2].substr(2, prizeInfo[2].length() - 2));
        prizeX2 = stoi(prizeInfo[1].substr(2, prizeInfo[1].length() - 3)) + 10000000000000;
        prizeY2 = stoi(prizeInfo[2].substr(2, prizeInfo[2].length() - 2)) + 10000000000000;
    }

    int ax;
    int ay;
    int bx;
    int by;
    int prizeX;
    int prizeY;
    long long prizeX2;
    long long prizeY2;
};


#endif //CLAWMACHINE_H
