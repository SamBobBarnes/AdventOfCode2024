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
    }

    int ax;
    int ay;
    int bx;
    int by;
    int prizeX;
    int prizeY;
};


#endif //CLAWMACHINE_H
