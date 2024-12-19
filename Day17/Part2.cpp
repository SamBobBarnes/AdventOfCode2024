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

bool checkLast(vector<int> *program, vector<int> *against, const int startAt) {
    for (int i = startAt; i < program->size(); i++) {
        if ((*against)[i] != (*program)[i]) return false;
    }
    return true;
}

string program2String(vector<int> *program) {
    string programString = "";
    for (auto i: *program) {
        programString += "," + to_string(i);
    }
    return programString;
}

int Day17::Part2() {
    auto combo = [](const int operand, const vector<uint64_t> *registers) -> uint64_t {
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

    auto execute = [combo](const Op op, const int operand, vector<uint64_t> *registers, int &pc,
                           vector<int> *output,
                           bool debug = false) {
        uint64_t *A = &(*registers)[0];
        uint64_t *B = &(*registers)[1];
        uint64_t *C = &(*registers)[2];
        int cx = combo(operand, registers);
        int x = operand;
        switch (op) {
            case adv:
                if (debug) cout << "A = " << *A << " / powl(2," << cx << ") = ";
                *A = *A / powl(2, cx);
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
                output->push_back(cx % 8);
                if (debug) cout << "Output: " << cx << " % 8 = " << cx % 8 << endl;
                pc += 2;
                break;
            case bdv:
                *B = *A / powl(2, cx);
                if (debug) cout << "B = " << *A << " / powl(2," << cx << ") = " << *B << endl;
                pc += 2;
                break;
            case cdv:
                *C = *A / powl(2, cx);
                if (debug) cout << "C = " << *A << " / powl(2," << cx << ") = " << *C << endl;
                pc += 2;
                break;
        }
    };

    const auto lines = Helpers::readFile(17, false);

    auto loadProgram = [lines]() {
        vector<string> strings = Helpers::split(lines[4].substr(9), ',');
        vector<int> program{};
        for (auto str: strings) {
            program.push_back(stoi(str));
        }
        return program;
    };

    auto run = [execute](const uint64_t A, vector<int> *program)-> vector<int> {
        vector<uint64_t> Registers{A, 0, 0};
        int PC = 0;
        vector<int> out{};
        while (PC < program->size()) {
            const Op op = static_cast<Op>((*program)[PC]);
            const int operand = (*program)[PC + 1];
            execute(op, operand, &Registers, PC, &out);
        }
        return out;
    };
    auto program = loadProgram();
    string programString = program2String(&program);

    vector<int> output{};

    uint64_t A = powl(8, 15);

    for (int i = 14; i >= 0; i--) {
        vector<int> result;
        do {
            A += powl(8, i);
            result = run(A, &program);
        } while (!checkLast(&program, &result, i + 1));
    }

    auto result = run(A, &program);

    cout << endl;
    for (auto i: result) {
        cout << "," << i;
    }

    cout << endl << programString << endl;

    return A;
}
