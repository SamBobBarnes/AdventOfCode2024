#include "ClawMachine.h"
#include "Day13.h"

long long Day13::Part2() {
    const auto lines = Helpers::readFile(13, false);

    vector<ClawMachine> machines{};

    for (int i = 0; i < lines.size(); i += 4) {
        string info[3]{lines[i], lines[i + 1], lines[i + 2]};
        machines.emplace_back(info);
    }

    long long int total = 0;

    for (const auto machine: machines) {
        const long long int a = machine.ax;
        const long long int c = machine.ay;
        const long long int d = machine.bx;
        const long long int b = machine.by;
        const long long int prizeX = machine.prizeX2;
        const long long int prizeY = machine.prizeY2;

        const long long int denominator = (a * b - d * c);

        const long long int A = (prizeX * b - d * prizeY) / denominator;
        const long long int B = (a * prizeY - prizeX * c) / denominator;

        if (A >= 0 && B >= 0 && a * A + d * B == prizeX && c * A + b * B == prizeY)
            total += 3 * A + B;
    }

    return total;
}
