#include "Day22.h"

uint64_t Day22::Part2() {
    const auto lines = Helpers::readFile(22, true);

    auto transform = [](uint64_t &number)-> int {
        constexpr uint64_t pruner = 16777216;
        const uint64_t a = number;
        const uint64_t b = ((a * 64) ^ a) % pruner;
        const uint64_t c = ((b / 32) ^ b) % pruner;
        const uint64_t d = ((c * 2048) ^ c) % pruner;
        number = d;

        return number % 10;
    };

    vector<uint64_t> numbers{};

    for (auto &i: lines) {
        numbers.push_back(stoi(i));
    }

    uint64_t total{0};

    constexpr uint64_t rounds{2000};
    for (auto &number: numbers) {
        vector digits{number % 10};
        vector<int> changes{};
        for (int i = 0; i < rounds; ++i) {
            auto digit = transform(number);
            digits.push_back(digit);
            changes.push_back(digits[i] - digits[i + 1]);
            if (i < 4) continue;

            // memoize changes
        }
        total += number;
    }

    return total;
}
