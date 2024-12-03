#include <iostream>

#include "Helpers.h"
#include "Day1/Day1.h"
#include "Day2/Day2.h"
#include "Day3/Day3.h"
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

    switch (3) {
        case 1:
            std::cout << "Day 1 - Part 1: " << Day1::Part1() << std::endl;
            std::cout << "Day 1 - Part 2: " << Day1::Part2() << std::endl;
            break;
        case 2:
            std::cout << "Day 2 - Part 1: " << Day2::Part1() << std::endl;
            std::cout << "Day 2 - Part 2: " << Day2::Part2() << std::endl;
            break;
        case 3:
            std::cout << "Day 3 - Part 1: " << Day3::Part1() << std::endl;
            std::cout << "Day 3 - Part 2: " << Day3::Part2() << std::endl;
            break;
        //####case
        default:
            std::cout << "TILT" << std::endl;
    }

    return 0;
}
