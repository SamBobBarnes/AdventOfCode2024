#include "Day17.h"

int Day17::Part2() {
    auto combo = [](const int operand, const vector<long> *registers) -> long {
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

    auto DV = [](long A, long cx)-> long {
        return A / powl(2, cx);
    };

    auto BXL = [](long B, int x)-> long {
        return B ^ x;
    };

    auto BST = [](long cx)-> long {
        return cx % 8;
    };

    auto BXC = [](long B, long C)-> long {
        return B ^ C;
    };

    auto OUT = [](long cx)-> int {
        return cx % 8;
    };

    auto execute = [combo](const Op op, const int operand, vector<long> *registers, int &pc,
                           vector<int> *output,
                           bool debug = false) {
        long *A = &(*registers)[0];
        long *B = &(*registers)[1];
        long *C = &(*registers)[2];
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

    auto run = [execute](const int A, vector<int> *program)-> vector<int> {
        vector<long> Registers{A, 0, 0};
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
    string programString = "";
    for (auto i: program) {
        programString += "," + to_string(i);
    }

    vector<int> output{};

    int programLength = program.size();
    int index = -1;


    int current = 0;

    const long A = 1526138149;
    auto result = run(A, &program);

    // int A = 5;

    long B = BST(A);
    long B2 = BXL(B, 1);
    long C = DV(A, B2);
    long A1 = DV(A, 3);
    long B3 = BXL(B2, 4);
    long B4 = BXC(B3, C);
    long O = OUT(B4);

    vector<int> possibles{};

    for (int i = programLength - 1; i >= 0; i--) {
        int top = ((current + 1) * 8) - 1;
        int bottom = current * 8;

        for (int j = bottom; j <= top; j++) {
            if (j == 0) continue;
            int A = j;

            long B = BST(A);
            long B2 = BXL(B, 1);
            long C = DV(A, B2);
            long A1 = DV(A, 3);
            long B3 = BXL(B2, 4);
            long B4 = BXC(B3, C);
            long O = OUT(B4);
            int result = O;
            cout << result << endl;
            if (result == program[i]) {
                current = A;
                break;
            }
        }
    }


    return current;
}
