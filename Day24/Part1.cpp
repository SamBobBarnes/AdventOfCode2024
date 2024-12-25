#include <queue>
#include <utility>
#include <__algorithm/ranges_sort.h>

#include "Day24.h"

enum Operation {
    AND,
    XOR,
    OR
};

struct Wire {
    explicit Wire(string name, const bool value): Name(std::move(name)), Out(value) {
    }

    string Name;
    bool Out;

    bool operator==(const string &other) const {
        return Name == other;
    }

    bool operator<(const Wire &other) const {
        return Name > other.Name;
    }
};

struct Instruction {
    explicit Instruction(string inst) {
        auto insts = Helpers::split(inst, ' ');
        A = insts[0];
        B = insts[2];
        Out = insts[4];
        if (insts[1] == "AND") Op = AND;
        else if (insts[1] == "OR") Op = OR;
        else Op = XOR;
    }

    Operation Op;
    string A;
    string B;
    string Out;
};

long Day24::Part1() {
    const auto lines = Helpers::readFile(24, false);

    vector<Wire> wires{};
    vector<Instruction> instructions{};

    bool readWires{true};
    for (const auto &line: lines) {
        if (line.empty()) {
            readWires = false;
            continue;
        }
        if (readWires) {
            auto wireInfo = Helpers::split(line, ": ");
            wires.emplace_back(wireInfo[0], wireInfo[1] == "1");
        } else {
            instructions.emplace_back(line);
        }
    }

    queue<Instruction *> q{};

    for (auto &i: instructions) q.push(&i);

    while (!q.empty()) {
        auto i = q.front();
        q.pop();
        const auto aIt = ranges::find_if(wires, [i](const Wire &w) { return w.Name == i->A; });
        const auto bIt = ranges::find_if(wires, [i](const Wire &w) { return w.Name == i->B; });
        if (aIt == wires.end() || bIt == wires.end()) {
            q.push(i);
            continue;
        }

        const auto a = &*aIt;
        const auto b = &*bIt;
        bool out;
        switch (i->Op) {
            case AND:
                out = a->Out && b->Out;
                break;
            case XOR:
                out = (a->Out || b->Out) && !(a->Out && b->Out);
                break;
            case OR:
                out = a->Out || b->Out;
        }
        wires.emplace_back(i->Out, out);
    }

    vector<Wire> outputs{};

    for (auto w: wires) {
        if (w.Name[0] == 'z') outputs.push_back(w);
    }

    sort(outputs.begin(), outputs.end());

    string output;

    for (const auto &o: outputs) {
        output += o.Out ? "1" : "0";
    }

    return strtol(output.c_str(), nullptr, 2);
}
