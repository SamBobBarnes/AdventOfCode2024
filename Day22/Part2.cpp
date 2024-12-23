#include <map>
#include <set>
#include <unordered_map>

#include "Day22.h"

uint32_t combineIntoUint32(int8_t a, int8_t b, int8_t c, int8_t d) {
    return (static_cast<uint32_t>(static_cast<uint8_t>(a)) << 24) |
           (static_cast<uint32_t>(static_cast<uint8_t>(b)) << 16) |
           (static_cast<uint32_t>(static_cast<uint8_t>(c)) << 8) |
           static_cast<uint32_t>(static_cast<uint8_t>(d));
}

vector<int> extractFromUint32(uint32_t combined) {
    return {
        static_cast<int8_t>((combined >> 24) & 0xFF),
        static_cast<int8_t>((combined >> 16) & 0xFF),
        static_cast<int8_t>((combined >> 8) & 0xFF),
        static_cast<int8_t>(combined & 0xFF)
    };
}


uint64_t Day22::Part2() {
    const auto lines = Helpers::readFile(22, false);

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

    map<uint32_t, uint64_t> memo{};

    constexpr uint64_t rounds{2000};
    for (auto &number: numbers) {
        set<uint32_t> recorded{};
        auto previous{number % 10};
        vector<int> changes{};
        for (int i = 0; i < rounds; ++i) {
            auto digit = transform(number);
            auto current = digit;
            changes.push_back(current - previous);
            previous = current;
            if (i < 3) continue;

            // memoize changes

            const uint32_t memoId = combineIntoUint32(changes[i - 3], changes[i - 2], changes[i - 1], changes[i]);
            // auto extracted = extractFromUint32(memoId);
            if (!recorded.contains(memoId)) {
                recorded.insert(memoId);
                memo[memoId] += digit;
            }
        }
    }

    vector<uint32_t> highest;
    uint64_t highestValue = 0;
    for (auto [id,number]: memo) {
        if (number == highestValue) {
            highest.push_back(id);
        }
        if (number > highestValue) {
            highestValue = number;
            highest = {id};
        }
    }

    // auto monkey = extractFromUint32(highest[0]);

    return highestValue;
}
