#include <map>
#include <unordered_map>

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

    auto hash = [](const int a, const int b, const int c, const int d) {
        return ((int8_t) a << 24) ^ ((int8_t) b << 16) ^ ((int8_t) c << 8) ^ ((int8_t) d);
    };

    auto unhash = [](const int32_t hashNum)-> vector<int> {
        vector<int> nums{0, 0, 0, 0};

        nums[3] = hashNum & 0x000000FF;
        nums[2] = hashNum & 0x0000FF00;
        nums[1] = hashNum & 0x00FF0000;
        nums[0] = hashNum & 0xFF000000;

        return nums;
    };

    vector<uint64_t> numbers{};

    for (auto &i: lines) {
        numbers.push_back(stoi(i));
    }

    uint64_t total{0};
    map<int32_t, uint64_t> memo{};

    constexpr uint64_t rounds{2000};
    for (auto &number: numbers) {
        auto previous{number % 10};
        vector<int> changes{};
        for (int i = 0; i < rounds; ++i) {
            auto digit = transform(number);
            auto current = digit;
            changes.push_back(previous - current);
            previous = current;
            if (i < 4) continue;

            // memoize changes

            int32_t memoId = hash(changes[i - 4], changes[i - 3], changes[i - 2], changes[i - 1]);
            memo[memoId] += digit;
        }
        total += number;
    }

    vector<int32_t> highest;
    uint64_t highestValue = 0;
    for (auto [id,number]: memo) {
        if (number > highestValue) {
            highestValue = number;
            highest = {id};
        }
        if (number == highestValue) {
            highest.push_back(id);
        }
    }

    auto monkey = memo[hash(-2, 1, -1, 3)];

    return total;
}
