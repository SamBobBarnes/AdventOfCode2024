#include "ClawMachine.h"
#include "Day13.h"

int Day13::Part1() {
    const auto lines = Helpers::readFile(13, false);

    vector<ClawMachine> machines{};

    for (int i = 0; i < lines.size(); i += 4) {
        string info[3]{lines[i], lines[i + 1], lines[i + 2]};
        machines.emplace_back(info);
    }

    int total{0};

    for (auto machine: machines) {
        int min{Helpers::Max};
        for (int a = 0; a < 100; ++a) {
            for (int b = 0; b < 100; ++b) {
                if (a * machine.ax + b * machine.bx == machine.prizeX &&
                    a * machine.ay + b * machine.by == machine.prizeY) {
                    if (min > a * 3 + b * 1) min = a * 3 + b * 1;
                }
            }
        }
        if (min < Helpers::Max) total += min;
    }

    return total;
}
