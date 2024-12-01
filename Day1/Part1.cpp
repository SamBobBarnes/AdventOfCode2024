#include <algorithm>

#include "Day1.h"

int Day1::Part1() {
    const auto lines = Helpers::readFile(1);

    vector<int> firstColumn{};
    vector<int> secondColumn{};

    for (const auto& line: lines)
    {
        const auto i = line.find_first_of(' ');
        firstColumn.push_back(stoi(line.substr(0,i)));
        secondColumn.push_back(stoi(line.substr(i+2)));
    }

    ranges::sort(firstColumn);
    ranges::sort(secondColumn);

    int total {0};

    for (int i = 0; i < firstColumn.size(); ++i)
    {
        total += abs(firstColumn[i] - secondColumn[i]);
    }

    return total;
}