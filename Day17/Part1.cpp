#include "Day17.h"

string Day17::Part1() {
    int Registers[3]{};
    int PC = 0;
    string output{};

    auto combo = [Registers](const int operand) {
        switch (operand) {
            case 0:
            case 1:
            case 2:
            case 3:
                return operand;
            case 4:
                return Registers[0];
            case 5:
                return Registers[1];
            case 6:
                return Registers[2];
            default:
                cerr << "TILT! " << operand << " is not a valid operand!";
                return -1;
        }
    };

    enum Op {
        // x = literal, cx = combo
        adv = 0, // A = A / (pow(2,cx))
        bxl = 1, // B = B ^ x
        bst = 2, // B = cx % 8
        jnz = 3, // if A > 0 then jmp to x
        bxc = 4, // B = B ^ C
        out = 5, // OUT = cx % 8
        bdv = 6, // B = A / (pow(2,cx))
        cdv = 7 // C = A / (pow(2,cx))
    };

    auto execute = [combo](const Op op, const int operand, int *registers[3], int &pc, string &output) {
        switch (op) {
            case adv:
                (*registers)[0] = (*registers)[0] / pow(2, combo(operand));
                pc += 2;
                break;
            case bxl:
                (*registers)[1] = (*registers)[1] ^ operand;
                pc += 2;
                break;
            case bst:
                (*registers)[1] = combo(operand) % 8;
                pc += 2;
                break;
            case jnz:
                if ((*registers)[0] > 0) pc = operand;
                break;
            case bxc:
                (*registers)[1] = (*registers)[1] ^ (*registers)[2];
                pc += 2;
                break;
            case out:
                output += combo(operand) % 8;
                pc += 2;
                break;
            case bdv:
                (*registers)[1] = (*registers)[0] / pow(2, combo(operand));
                pc += 2;
                break;
            case cdv:
                (*registers)[2] = (*registers)[0] / pow(2, combo(operand));
                pc += 2;
                break;
        }
    };

    const auto lines = Helpers::readFile(17, true);

    Registers[0] = stoi(lines[0].substr(12));
    Registers[1] = stoi(lines[1].substr(12));
    Registers[2] = stoi(lines[2].substr(12));

    auto loadProgram = [lines]() {
        vector<string> strings = Helpers::split(lines[4].substr(9), ',');
        vector<int> program{};
        for (auto str: strings) {
            program.push_back(stoi(str));
        }
        return program;
    };

    auto program = loadProgram();

    int programLength = program.size();

    while (PC < programLength) {
        execute(static_cast<Op>(program[PC]), program[PC + 1], &Registers, PC, output);
    }

    return output;
}
