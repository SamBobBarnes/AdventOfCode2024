//
// Created by Samuel Barnes on 12/23/24.
//

#ifndef NODE_H
#define NODE_H
#include "Day23.h"

struct Node {
    Node(const string name): name(name) {
    }

    string name;
    vector<Node *> connections{};

    [[nodiscard]] bool connectsTo(const string& other)const {
        for (const auto conn: connections) {
            if (*conn == other) return true;
        }
        return false;
    }

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

#endif //NODE_H
