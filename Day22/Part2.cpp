#include <map>
#include <set>
#include <unordered_map>

#include "Day22.h"

size_t combineHashes(size_t hash1, size_t hash2) {
    // A simple hash combination technique, you can use more sophisticated ones if needed
    return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
}

size_t hashInts(const std::array<int, 4> &ints) {
    std::hash<int> hasher;
    size_t combinedHash = 0;

    for (int value: ints) {
        combinedHash = combineHashes(combinedHash, hasher(value));
    }

    return combinedHash;
}

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
    map<size_t, uint64_t> memo{};
    set<size_t> memoIds{};

    constexpr uint64_t rounds{2000};
    for (auto &number: numbers) {
        auto previous{number % 10};
        vector<int> changes{};
        for (int i = 0; i < rounds; ++i) {
            auto digit = transform(number);
            auto current = digit;
            changes.push_back(current - previous);
            previous = current;
            if (i < 4) continue;

            // memoize changes

            uint32_t memoId = hashInts({changes[i - 4], changes[i - 3], changes[i - 2], changes[i - 1]});
            memoIds.insert(memoId);
            memo[memoId] += digit;
        }
        total += number;
    }

    vector<size_t> highest;
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

    auto monkey = memo[hashInts({-2, 1, -1, 3})];

    return total;
}
