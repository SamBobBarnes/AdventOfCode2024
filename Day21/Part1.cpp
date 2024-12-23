#include <map>

#include "Day21.h"

int Day21::Part1() {
    const auto lines = Helpers::readFile(21, true);

    auto getKeypadPos = [](const char key)-> Point {
        switch (key) {
            case 'A': return {2, 3};
            case '0': return {1, 3};
            case '1': return {1, 2};
            case '2': return {2, 2};
            case '3': return {0, 1};
            case '4': return {1, 1};
            case '5': return {2, 1};
            case '6': return {0, 2};
            case '7': return {0, 0};
            case '8': return {1, 0};
            case '9': return {2, 0};
            default: throw;
        }
    };

    auto getDirpadPos = [](const char key)-> Point {
        switch (key) {
            case '^': return {1, 0};
            case 'A': return {2, 0};
            case '<': return {0, 1};
            case 'v': return {1, 1};
            case '>': return {2, 1};
            default: throw;
        }
    };

    auto quickestPath = [getDirpadPos](const Point &a, const Point &b)-> int {
        if (a == b) return 0;

        return abs(a.x - b.x) + abs(a.y - b.y);
    };

    //Keypad Robot

    vector<Point> buttonPresses{};
    for (char i: lines[0]) {
        buttonPresses.push_back(getKeypadPos(i));
    }

    map<char, map<char, vector<string> > > paths{
        {
            '>', {
                {'A', {"^"}},
                {'^', {"^<", "<^"}},
                {'v', {"<"}},
                {'<', {"<<"}}
            }
        },
        {
            'A', {
                {'>', {"v"}},
                {'^', {"v>", ">v"}},
                {'v', {"v<", "<v"}},
                {'<', {"<v<", "v<<"}}
            }
        },
        {
            '^', {
                {'>', {"v>", ">v"}},
                {'A', {">"}},
                {'v', {"v"}},
                {'<', {"v<"}}
            }
        },
        {
            'v', {
                {'>', {">"}},
                {'^', {"^"}},
                {'A', {">^", "^>"}},
                {'<', {"<"}}
            }
        },
        {
            '<', {
                {'>', {">>"}},
                {'^', {">^"}},
                {'v', {">"}},
                {'A', {">>^", ">^>"}}
            }
        },
    };

    //Robot 1
    //Robot 2
    //Me


    return 0;
}

/*
    +---+---+
    | ^ | A |
+---+---+---+
| < | v | > |
+---+---+---+

> A
    ^
> ^
    ^<
    <^
> v
    <
> <
    <<




+---+---+---+
| 7 | 8 | 9 |
+---+---+---+
| 4 | 5 | 6 |
+---+---+---+
| 1 | 2 | 3 |
+---+---+---+
    | 0 | A |
    +---+---+

*/
