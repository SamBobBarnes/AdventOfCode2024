#include <iostream>

#include "Helpers.h"
#include "Day1/Day1.h"
#include "Day2/Day2.h"
#include "Day3/Day3.h"
#include "Day4/Day4.h"
#include "Day5/Day5.h"
#include "Day6/Day6.h"
#include "Day7/Day7.h"
#include "Day8/Day8.h"
#include "Day9/Day9.h"
#include "Day10/Day10.h"
#include "Day11/Day11.h"
#include "Day12/Day12.h"
#include "Day13/Day13.h"
#include "Day14/Day14.h"
#include "Day15/Day15.h"
#include "Day16/Day16.h"
#include "Day17/Day17.h"
#include "Day18/Day18.h"
#include "Day19/Day19.h"
#include "Day20/Day20.h"
#include "Day21/Day21.h"
#include "Day22/Day22.h"
#include "Day23/Day23.h"
#include "Day24/Day24.h"
#include "Day25/Day25.h"
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

    switch (25) {
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
        case 4:
            std::cout << "Day 4 - Part 1: " << Day4::Part1() << std::endl;
            std::cout << "Day 4 - Part 2: " << Day4::Part2() << std::endl;
            break;
        case 5:
            std::cout << "Day 5 - Part 1: " << Day5::Part1() << std::endl;
            std::cout << "Day 5 - Part 2: " << Day5::Part2() << std::endl;
            break;
        case 6:
            std::cout << "Day 6 - Part 1: " << Day6::Part1() << std::endl;
            std::cout << "Day 6 - Part 2: " << Day6::Part2() << std::endl;
            break;
        case 7:
            std::cout << "Day 7 - Part 1: " << Day7::Part1() << std::endl;
            std::cout << "Day 7 - Part 2: " << Day7::Part2() << std::endl;
            break;
        case 8:
            std::cout << "Day 8 - Part 1: " << Day8::Part1() << std::endl;
            std::cout << "Day 8 - Part 2: " << Day8::Part2() << std::endl;
            break;
        case 9:
            std::cout << "Day 9 - Part 1: " << Day9::Part1() << std::endl;
            std::cout << "Day 9 - Part 2: " << Day9::Part2() << std::endl;
            break;
        case 10:
            std::cout << "Day 10 - Part 1: " << Day10::Part1() << std::endl;
            std::cout << "Day 10 - Part 2: " << Day10::Part2() << std::endl;
            break;
        case 11:
            std::cout << "Day 11 - Part 1: " << Day11::Part1() << std::endl;
            std::cout << "Day 11 - Part 2: " << Day11::Part2() << std::endl;
            break;
        case 12:
            std::cout << "Day 12 - Part 1: " << Day12::Part1() << std::endl;
            std::cout << "Day 12 - Part 2: " << Day12::Part2() << std::endl;
            break;
        case 13:
            std::cout << "Day 13 - Part 1: " << Day13::Part1() << std::endl;
            std::cout << "Day 13 - Part 2: " << Day13::Part2() << std::endl;
            break;
        case 14:
            std::cout << "Day 14 - Part 1: " << Day14::Part1() << std::endl;
            std::cout << "Day 14 - Part 2: " << Day14::Part2() << std::endl;
            break;
        case 15:
            std::cout << "Day 15 - Part 1: " << Day15::Part1() << std::endl;
            std::cout << "Day 15 - Part 2: " << Day15::Part2() << std::endl;
            break;
        case 16:
            std::cout << "Day 16 - Part 1: " << Day16::Part1() << std::endl;
            std::cout << "Day 16 - Part 2: " << Day16::Part2() << std::endl;
            break;
        case 17:
            std::cout << "Day 17 - Part 1: " << Day17::Part1() << std::endl;
            std::cout << "Day 17 - Part 2: " << Day17::Part2() << std::endl;
            break;
        case 18:
            std::cout << "Day 18 - Part 1: " << Day18::Part1() << std::endl;
            std::cout << "Day 18 - Part 2: " << Day18::Part2() << std::endl;
            break;
        case 19:
            std::cout << "Day 19 - Part 1: " << Day19::Part1() << std::endl;
            std::cout << "Day 19 - Part 2: " << Day19::Part2() << std::endl;
            break;
        case 20:
            std::cout << "Day 20 - Part 1: " << Day20::Part1() << std::endl;
            std::cout << "Day 20 - Part 2: " << Day20::Part2() << std::endl;
            break;
        case 21:
            std::cout << "Day 21 - Part 1: " << Day21::Part1() << std::endl;
            std::cout << "Day 21 - Part 2: " << Day21::Part2() << std::endl;
            break;
        case 22:
            std::cout << "Day 22 - Part 1: " << Day22::Part1() << std::endl;
            std::cout << "Day 22 - Part 2: " << Day22::Part2() << std::endl;
            break;
        case 23:
            std::cout << "Day 23 - Part 1: " << Day23::Part1() << std::endl;
            std::cout << "Day 23 - Part 2: " << Day23::Part2() << std::endl;
            break;
        case 24:
            std::cout << "Day 24 - Part 1: " << Day24::Part1() << std::endl;
            std::cout << "Day 24 - Part 2: " << Day24::Part2() << std::endl;
            break;
        case 25:
            std::cout << "Day 25 - Part 1: " << Day25::Part1() << std::endl;
            std::cout << "Day 25 - Part 2: " << Day25::Part2() << std::endl;
            break;
        //####case
        default:
            std::cout << "TILT" << std::endl;
    }

    return 0;
}
