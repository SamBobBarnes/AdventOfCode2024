#include <utility>

#include "Day24.h"

struct OutputBuffer {
    explicit OutputBuffer(const int size) {
        Inputs.resize(size);
    }

    vector<bool> Inputs{};

    string Output() {
        string result;
        for (int i = Inputs.size() - 1; i >= 0; --i) {
            result += Inputs[i] ? "1" : "0";
        }
        return result;
    }
};

enum Operation {
    AND,
    XOR,
    OR
};

struct Gate {
    Gate(const Operation op, string name): Op(op), Name(std::move(name)), A(nullptr), B(nullptr), Out(false) {
    }

    Operation Op;
    string Name;
    bool *A;
    bool *B;
    bool Out;
    bool Executed{false};

    void Execute() {
        switch (Op) {
            case AND:
                Out = *A && *B;
                break;
            case XOR:
                Out = (*A || *B) && !(*A && *B);
                break;
            case OR:
                Out = *A || *B;
                break;
        }
        Executed = true;
    }
};

string Day24::Part1() {
    const auto lines = Helpers::readFile(24, true);


    return "0";
}
