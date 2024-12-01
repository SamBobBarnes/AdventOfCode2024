#include <iostream>

#include "Helpers.h"
#include "Day1/Day1.h"
//####include


int main() {
    std::cout << "Running on ";
#ifdef _WIN32
    std::cout << "Windows";
#else
    std::cout << "Linux";
#endif
    std::cout << std::endl << std::endl;
    std::cout << "Current dir: " << Helpers::pwd() << std::endl;

    // Helpers::colorReference();

    switch (1)
    {
    case 1:
        std::cout << "Day 1 - Part 1: " << Day1::Part1() << std::endl;
        std::cout << "Day 1 - Part 2: " << Day1::Part2() << std::endl;
        break;
        //####case
        default:
            std::cout << "TILT" << std::endl;
    }

    return 0;
}