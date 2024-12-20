#include <complex.h>
#include <math.h>
#include <queue>

#include "Day17.h"

struct programValue {
    programValue(const uint64_t cur, const int pc): currentValue(cur), pc(pc) {
    }

    uint64_t currentValue;
    int pc;

    bool operator<(const programValue &other) const {
        return pc < other.pc;
    }
};

int Day17::Part2() {
    // case 0:
    // case 1:
    // case 2:
    // case 3:
    //     return operand;
    // case 4:
    //     return (*registers)[0];
    // case 5:
    //     return (*registers)[1];
    // case 6:
    //     return (*registers)[2];


    // x = literal, cx = combo
    // adv = 0, // A = A / (pow(2,cx))
    // bxl = 1, // B = B ^ x
    // bst = 2, // B = cx % 8
    // jnz = 3, // if A > 0 then jmp to x
    // bxc = 4, // B = B ^ C
    // out = 5, // OUT = cx % 8
    // bdv = 6, // B = A / (pow(2,cx))
    // cdv = 7 // C = A / (pow(2,cx))


    /// 2,4 B = A % 8
    /// 1,1 B = B ^ 1
    /// 7,5 C = A / pow(2,B)
    /// 0,3 A = A / 8
    /// 1,4 B = B ^ 4
    /// 4,0 B = B ^ C
    /// 5,5 OUT B % 8
    /// 3,0 JMP 0

    auto execute = [](uint64_t input) {
        uint64_t A = input;
        uint64_t B = 0;
        uint64_t C = 0;
        vector<int> output{};
        do {
            B = A % 8;
            B = B ^ 1;
            C = A / static_cast<uint64_t>(pow(2, B));
            A = A / 8;
            B = B ^ 4;
            B = B ^ C;
            output.push_back(B % 8);
        } while (A != 0);

        // reverse(output.begin(), output.end());
        return output;
    };

    const auto lines = Helpers::readFile(17, true);

    vector<string> strings = Helpers::split(lines[4].substr(9), ',');
    vector<int> program{};
    for (auto str: strings) {
        program.push_back(stoi(str));
    }

    string programString = program2String(&program);

    auto output = execute(32916674);

    return 0;
}
