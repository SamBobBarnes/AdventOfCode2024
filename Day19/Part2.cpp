#include <map>
#include <queue>
#include <set>

#include "Day19.h"
#include "../Point.h"

template<typename T, typename C>
class Queue {
    std::set<T, C> impl;

public:
    Queue(C compare) : impl(compare) {
    }

    const T pop() {
        auto x = *impl.begin();
        impl.erase(impl.begin());
        return x;
    }

    bool empty() const { return impl.empty(); }

    std::size_t size() const { return impl.size(); }

    void push(const T &value) { impl.insert(value); }
};

vector<int> findNext(const vector<string> *towels, const string &pattern, const int start) {
    vector<int> endPoints{};
    for (const auto &towel: (*towels)) {
        int i = pattern.find(towel, start);
        if (i != start) continue;
        endPoints.push_back(i + towel.length());
    }
    return endPoints;
};

uint64_t Day19::countOptions(map<int, int> *tMap, const vector<string> *towels, const string &pattern, const int i) {
    if (i == pattern.length())
        return 1;

    if (tMap->contains(i)) {
        return (*tMap)[i];
    }

    uint64_t sum = 0;
    for (auto j: findNext(towels, pattern, i)) {
        sum += countOptions(tMap, towels, pattern, j);
    }

    (*tMap)[i] = sum;
    return sum;
}


uint64_t Day19::Part2() {
    const auto lines = Helpers::readFile(19, false);

    const auto towels = Helpers::split(lines[0], ", ");

    vector<string> patterns{};

    for (int i = 2; i < lines.size(); i++) {
        patterns.push_back(lines[i]);
    }

    uint64_t total{0};

    for (const auto &pattern: patterns) {
        if (!isPossible(&towels, pattern)) continue;
        map<int, int> tMap{};
        uint64_t subTotal = countOptions(&tMap, &towels, pattern, 0);
        total += subTotal;
    }

    return total; // > 29335
}
