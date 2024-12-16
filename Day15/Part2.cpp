#include "Day15.h"
#include "../Point.h"

int Day15::Part2() {
    const auto lines = Helpers::readFile(15, true);

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
                if (cell == '#') {
                    row.push_back(Wall);
                    row.push_back(Wall);
                } else if (cell == 'O') {
                    row.push_back(BoxL);
                    row.push_back(BoxR);
                } else if (cell == '.') {
                    row.push_back(Floor);
                    row.push_back(Floor);
                } else if (cell == '@') {
                    row.push_back(Floor);
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
    Print(&warehouse);


    auto moveBox = [](const int x, const int y, const Dir dir, vector<vector<WH> > *warehouse,
                      auto &moveBoxRef) -> bool {
        bool left = (*warehouse)[y][x] == BoxL;
        int tempY = y;
        int tempXL = left ? x : x - 1;
        int tempXR = left ? x + 1 : x;
        switch (dir) {
            case Up:
                tempY -= 1;

                if ((*warehouse)[tempY][tempXL] == Floor && (*warehouse)[tempY][tempXR] == Floor) {
                    (*warehouse)[y][x] = Floor;
                    if (left)
                        (*warehouse)[y][x + 1] = Floor;
                    else
                        (*warehouse)[y][x - 1] = Floor;
                    (*warehouse)[tempY][tempXL] = BoxL;
                    (*warehouse)[tempY][tempXR] = BoxR;

                    return true;
                }

                if ((*warehouse)[tempY][tempXL] == BoxL || (*warehouse)[tempY][tempXL] == BoxR ||
                    (*warehouse)[tempY][tempXR] == BoxL) {
                    if ((*warehouse)[tempY][tempXL] == BoxL) {
                        return moveBoxRef(tempXL, tempY, dir, warehouse, moveBoxRef);
                    }

                    bool canMove{true};
                    if ((*warehouse)[tempY][tempXL] == BoxR) {
                        canMove = canMove && moveBoxRef(tempXL - 1, tempY, dir, warehouse, moveBoxRef);
                    }
                    if ((*warehouse)[tempY][tempXR] == BoxL) {
                        canMove = canMove && moveBoxRef(tempXR, tempY, dir, warehouse, moveBoxRef);
                    }
                    return canMove;
                }
                return false;
            case Right:
                tempXL += 1;
                tempXR += 1;

            //check for floor
            //check for blocks

                return false;
            case Down:
                tempY += 1;

            //check for floor
            //check for blocks

                return false;
            case Left:
                tempXL -= 1;
                tempXR -= 1;

            //check for floor
            //check for blocks

                return false;
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
        if (warehouse[tempPos.y][tempPos.x] == BoxL || warehouse[tempPos.y][tempPos.x] == BoxR) {
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
