#include "Day24.h"

int Day24::Part2() {
    const auto lines = Helpers::readFile(24, true);

    bool readWires{true};
    for (const auto &line: lines) {
        if (line.empty()) {
            readWires = false;
            continue;
        }
        if (readWires) {
            auto wireInfo = Helpers::split(line, ": ");
            cout << wireInfo[0] << endl;
        } else {
            //     auto insts = Helpers::split(inst, ' ');
            //     auto A = insts[0];
            //     auto B = insts[2];
            //     auto Out = insts[4];
            //     if (insts[1] == "AND") Op = AND;
            //     else if (insts[1] == "OR") Op = OR;
            //     else cout << "{{" << << "}}";
        }
    }
    return 0;
}
