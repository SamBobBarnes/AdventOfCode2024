#include "Day22.h"

uint64_t Day22::Part1() {
    const auto lines = Helpers::readFile(22, false);

    vector<uint64_t> numbers{};

    for (auto &i: lines) {
        numbers.push_back(stoi(i));
    }

    uint64_t total{0};

    constexpr uint64_t rounds{2000};
    for (auto &number: numbers) {
        for (int i = 0; i < rounds; ++i) {
            constexpr uint64_t pruner = 16777216;
            const uint64_t a = number;
            const uint64_t b = ((a * 64) ^ a) % pruner;
            const uint64_t c = ((b / 32) ^ b) % pruner;
            const uint64_t d = ((c * 2048) ^ c) % pruner;
            number = d;
        }
        // cout << number << endl;
        total += number;
        // cout << total << endl;
    }

    return total;
}
