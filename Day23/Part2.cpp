#include <map>
#include <set>
#include <algorithm>
#include <queue>

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

    vector<string> usedInCliques{};
    vector<vector<Node *> > cliques{};
    set<Node *> starters{};

    for (const auto &loop: loops) {
        auto first = &*ranges::find(clients, loop.substr(0, 2));
        auto second = &*ranges::find(clients, loop.substr(2, 2));
        auto third = &*ranges::find(clients, loop.substr(4, 2));
        starters.insert(first);
        starters.insert(second);
        starters.insert(third);
    }


    for (const auto &start: starters) {
        if (ranges::find(usedInCliques, start->name) != usedInCliques.end()) continue;
        queue<Node *> q{};
        vector<Node *> visited{};
        vector<Node *> clique{};
        clique.push_back(start);
        for (auto v: start->connections)q.push(v);

        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            if (ranges::find(visited, u) != visited.end()) continue;

            visited.push_back(u);

            bool partOfClique{true};

            for (auto v: visited) {
                if (!v->connectsTo(u->name)) partOfClique = false;
            }

            if (partOfClique) {
                clique.push_back(u);
                q.push_range(u->connections);
            }
        }

        for (auto i: clique) {
            usedInCliques.push_back(i->name);
        }

        cliques.push_back(clique);
    }

    // for (const auto &[ids,count]: sets) {
    //     cout << ids << " : " << count << endl;
    // }

    return "0";
}
