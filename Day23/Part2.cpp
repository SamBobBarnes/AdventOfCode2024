#include <map>
#include <set>
#include <algorithm>

#include "Day23.h"
#include "Node.h"

string Day23::Part2() {
    const auto lines = Helpers::readFile(23, true);
    vector<Node> clients{};

    for (auto &line: lines) {
        const string a = line.substr(0, 2);
        const string b = line.substr(3, 2);
        if (ranges::find(clients, a) == clients.end()) clients.emplace_back(a);
        if (ranges::find(clients, b) == clients.end()) clients.emplace_back(b);
        cout << a << "<-->" << b << ";" << endl;
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

    for (const auto &head: clients) {
        for (auto child1: head.connections) {
            for (auto child2: child1->connections) {
                for (auto child3: child2->connections) {
                    if (child3 == &head) {
                        vector loop{child1, child2, child3};
                        ranges::sort(loop);
                        string loopString = loop[0]->name + loop[1]->name + loop[2]->name;
                        loops.insert(loopString);
                    }
                }
            }
        }
    }

    map<string, int> sets{};

    for (auto &client: clients) {
        vector<Node> lan{};
        lan.reserve(client.connections.size() + 1);
        for (auto i: client.connections) lan.push_back(*i);
        lan.push_back(client);
        sort(lan.begin(), lan.end());
        string group;
        for (const auto &c: lan) group += "," + c.name;
        sets[group.substr(1)]++;
    }

    // for (const auto &[ids,count]: sets) {
    //     cout << ids << " : " << count << endl;
    // }

    return "0";
}
