#include <cmath>

#include "Day17.h"

string Day17::Part1() {
    vector<int> Registers{0, 0, 0};
    int PC = 0;
    string output{};

    auto combo = [](const int operand, const vector<int> *registers) {
        switch (operand) {
            case 0:
            case 1:
            case 2:
            case 3:
                return operand;
            case 4:
                return (*registers)[0];
            case 5:
                return (*registers)[1];
            case 6:
                return (*registers)[2];
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

    auto execute = [combo](const Op op, const int operand, vector<int> *registers, int &pc, string &output,
                           bool debug = false) {
        int *A = &(*registers)[0];
        int *B = &(*registers)[1];
        int *C = &(*registers)[2];
        int cx = combo(operand, registers);
        int x = operand;
        switch (op) {
            case adv:
                if (debug) cout << "A = " << *A << " / pow(2," << cx << ") = ";
                *A = *A / pow(2, cx);
                if (debug) cout << *A << endl;
                pc += 2;
                break;
            case bxl:
                if (debug) cout << "B = " << *B << " ^ " << x;
                *B = *B ^ operand;
                if (debug) cout << " = " << *B << endl;
                pc += 2;
                break;
            case bst:
                *B = cx % 8;
                if (debug) cout << "B = " << cx << " % 8 = " << *B << endl;
                pc += 2;
                break;
            case jnz:
                if (*A > 0) {
                    pc = operand;
                    if (debug) cout << "Jump to = " << x << endl;
                } else {
                    if (debug) cout << "Dont Jump" << endl;
                    pc += 2;
                }
                break;
            case bxc:
                if (debug) cout << "B = " << *B << " ^ " << *C;
                *B = *B ^ *C;
                if (debug) cout << " = " << *B << endl;
                pc += 2;
                break;
            case out:
                output += "," + to_string(cx % 8);
                if (debug) cout << "Output: " << cx << " % 8 = " << cx % 8 << endl;
                pc += 2;
                break;
            case bdv:
                *B = *A / pow(2, cx);
                if (debug) cout << "B = " << *A << " / pow(2," << cx << ") = " << *B << endl;
                pc += 2;
                break;
            case cdv:
                *C = *A / pow(2, cx);
                if (debug) cout << "C = " << *A << " / pow(2," << cx << ") = " << *C << endl;
                pc += 2;
                break;
        }
    };

    const auto lines = Helpers::readFile(17, false);

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

    // cout << endl;
    while (PC < programLength) {
        Op op = static_cast<Op>(program[PC]);
        int operand = program[PC + 1];
        execute(op, operand, &Registers, PC, output);
    }
    // cout << endl;

    return output.substr(1);
}
