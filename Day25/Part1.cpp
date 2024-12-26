#include "Day25.h"

int Day25::Part1() {
    const auto lines = Helpers::readFile(25, false);

    vector<vector<int> > keys{};
    vector<vector<int> > locks{};

    for (int i = 0; i < lines.size(); i += 8) {
        if (lines[i] == "#####") {
            //lock
            vector lock{0, 0, 0, 0, 0};
            for (int y = 1; y < 6; ++y) {
                for (int x = 0; x < 5; ++x) {
                    if (lines[y + i][x] == '#') lock[x]++;
                }
            }
            locks.push_back(lock);
        } else {
            //key
            vector key{0, 0, 0, 0, 0};
            for (int y = 5; y > 0; --y) {
                for (int x = 0; x < 5; ++x) {
                    if (lines[y + i][x] == '#') key[x]++;
                }
            }
            keys.push_back(key);
        }
    }

    int total{0};

    for (auto key: keys) {
        for (auto lock: locks) {
            bool fits{true};
            for (int i = 0; i < 5; ++i) {
                if (key[i] + lock[i] > 5) {
                    fits = false;
                    break;
                }
            }
            if (fits) total++;
        }
    }

    return total;
}
