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
    const auto lines = Helpers::readFile(23, true);
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


    int total{0};
    return 0;
}
