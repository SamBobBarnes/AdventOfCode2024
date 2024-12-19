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


uint64_t Day19::Part2() {
    const auto lines = Helpers::readFile(19, false);

    const auto towels = Helpers::split(lines[0], ", ");

    vector<string> patterns{};

    for (int i = 2; i < lines.size(); i++) {
        patterns.push_back(lines[i]);
    }

    uint64_t total{0};

    for (const auto &pattern: patterns) {
        uint64_t subTotal{0};
        if (!isPossible(&towels, pattern)) continue;
        // auto pattern = possiblePatterns[0];
        auto findAll = [](const string &pattern, const string &t)-> vector<int> {
            vector<int> indices{};
            int i = -1;
            int location = 0;
            do {
                i = pattern.find(t, location);
                if (i >= 0)indices.push_back(i);
                location = i + 1;
            } while (i >= 0);
            return indices;
        };

        map<int, vector<int> > tMap{}; //index, length, towel
        for (const auto &towel: towels) {
            auto length = towel.length();
            auto is = findAll(pattern, towel);
            for (auto &i: is) {
                tMap[i].push_back(i + length);
            }
        }

        auto compRev = [](int first, int second) { return first < second; };
        Queue<int, decltype(compRev)> q(compRev);

        q.push(0);

        while (!q.empty()) {
            auto x = q.pop();
            // cout << x << endl;
            auto options = &tMap[x];
            int size = options->size();
            if (size > 1) subTotal += size;
            for (auto o: tMap[x]) {
                q.push(o);
            }
        }
        total += subTotal;
    }

    return total;
}
