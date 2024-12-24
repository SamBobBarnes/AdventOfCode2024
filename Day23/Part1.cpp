#include <queue>
#include <set>
#include <__algorithm/ranges_sort.h>

#include "Day23.h"

struct Node {
    Node(const string name): name(name) {
    }

    string name;
    vector<Node *> connections{};

    bool operator==(const Node &other) const {
        return name == other.name;
    }

    bool operator==(const string &other) const {
        return name == other;
    }

    bool operator<(const Node &other) const {
        return name < other.name;
    }
};

int Day23::Part1() {
    const auto lines = Helpers::readFile(23, false);
    vector<Node> clients{};

    for (auto &line: lines) {
        const string a = line.substr(0, 2);
        const string b = line.substr(3, 2);
        if (ranges::find(clients, a) == clients.end()) clients.emplace_back(a);
        if (ranges::find(clients, b) == clients.end()) clients.emplace_back(b);
        // cout << a << "<-->" << b << endl;
    }

    for (auto &line: lines) {
        const string a = line.substr(0, 2);
        const string b = line.substr(3, 2);
        auto A = &*ranges::find(clients, a);
        auto B = &*ranges::find(clients, b);
        if (ranges::find(A->connections, B) == A->connections.end())
            A->connections.push_back(B);
        if (ranges::find(B->connections, A) == B->connections.end())
            B->connections.push_back(A);
    }

    set<string> loops{};

    queue<Node *> q{};

    for (const auto &head: clients) {
        for (auto child1: head.connections) {
            for (auto child2: child1->connections) {
                for (auto child3: child2->connections) {
                    if (child3 == &head) {
                        vector loop{child1, child2, child3};
                        ranges::sort(loop);
                        loops.insert(loop[0]->name + loop[1]->name + loop[2]->name);
                    }
                }
            }
        }
    }

    int total{0};
    for (auto i: loops) {
        if (i[0] == 't' || i[2] == 't' || i[4] == 't') total++;
    }

    return total;
}
