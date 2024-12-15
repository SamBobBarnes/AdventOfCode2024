#include "Day15.h"
#include "../Point.h"

void Print(const vector<vector<Day15::WH> > *warehouse) {
    cout << endl;
    for (int y = 0; y < warehouse->size(); ++y) {
        for (int x = 0; x < (*warehouse)[0].size(); ++x) {
            if ((*warehouse)[y][x] == Day15::WH::Box)
                cout << 'O';
            else if ((*warehouse)[y][x] == Day15::WH::Wall)
                cout << '#';
            else cout << '.';
        }
        cout << endl;
    }
}

int Day15::Part1() {
    const auto lines = Helpers::readFile(15, false);

    Point robot;
    vector<vector<WH> > warehouse{};
    vector<Dir> instructions{};

    bool readingInstrs{false};

    int x{0};
    int y{0};

    for (auto line: lines) {
        if (line == "") {
            readingInstrs = true;
            continue;
        }

        if (readingInstrs) {
            for (auto dir: line) {
                if (dir == '>') instructions.push_back(Dir::Right);
                else if (dir == '<')instructions.push_back(Dir::Left);
                else if (dir == '^')instructions.push_back(Dir::Up);
                else if (dir == 'v')instructions.push_back(Dir::Down);
            }
        } else {
            vector<WH> row{};
            for (auto cell: line) {
                if (cell == '#') row.push_back(Wall);
                else if (cell == 'O') row.push_back(Box);
                else if (cell == '.') row.push_back(Floor);
                else if (cell == '@') {
                    row.push_back(Floor);
                    robot = {x, y};
                }
                x++;
            }
            warehouse.push_back(row);
            y++;
            x = 0;
        }
    }
    // Print(&warehouse);


    auto moveBox = [](const int x, const int y, const Dir dir, vector<vector<WH> > *warehouse,
                      auto &moveBoxRef) -> bool {
        Point tempPos{x, y};
        switch (dir) {
            case Up:
                tempPos.y -= 1;
                break;
            case Right:
                tempPos.x += 1;
                break;
            case Down:
                tempPos.y += 1;
                break;
            case Left:
                tempPos.x -= 1;
        }

        if ((*warehouse)[tempPos.y][tempPos.x] == Floor) {
            (*warehouse)[y][x] = Floor;
            (*warehouse)[tempPos.y][tempPos.x] = Box;
            return true;
        }
        if ((*warehouse)[tempPos.y][tempPos.x] == Box) {
            if (moveBoxRef(tempPos.x, tempPos.y, dir, warehouse, moveBoxRef)) {
                (*warehouse)[y][x] = Floor;
                (*warehouse)[tempPos.y][tempPos.x] = Box;
                return true;
            }
        }
        return false;
    };

    for (const auto inst: instructions) {
        Point tempPos = robot;
        switch (inst) {
            case Up:
                tempPos.y -= 1;
                break;
            case Right:
                tempPos.x += 1;
                break;
            case Down:
                tempPos.y += 1;
                break;
            case Left:
                tempPos.x -= 1;
        }

        if (warehouse[tempPos.y][tempPos.x] == Floor) {
            robot = tempPos;
            continue;
        }
        if (warehouse[tempPos.y][tempPos.x] == Box) {
            if (moveBox(tempPos.x, tempPos.y, inst, &warehouse, moveBox)) {
                robot = tempPos;
            }
        }
        // Print(&warehouse);
    }

    int total{0};

    for (int y = 0; y < warehouse.size(); ++y) {
        for (int x = 0; x < warehouse[0].size(); ++x) {
            if (warehouse[y][x] == Box) total += 100 * y + x;
        }
    }

    return total;
}
