#include <map>
#include <algorithm>

#include "Day1.h"

int Day1::Part2() {
    const auto lines = Helpers::readFile(1);

    vector<int> firstColumn{};
    map<int,int> secondColumn{};

    for (const auto& line: lines)
    {
        const auto i = line.find_first_of(' ');
        firstColumn.push_back(stoi(line.substr(0,i)));
        secondColumn[stoi(line.substr(i+2))]++;
    }

    ranges::sort(firstColumn);

    int total {0};

    for (int i : firstColumn)
    {
        total += i * secondColumn[i];
    }

    return total;
}