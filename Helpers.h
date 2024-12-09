//
// Created by Samuel Barnes on 11/30/2024.
//
#pragma once

#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include <cerrno>
#include <iostream>
#include <ranges>
#include <vector>

#ifndef HELPERS_H
#define HELPERS_H
#include <string>
#include <fstream>

class Helpers {
public:
    static std::string pwd() {
        char cCurrentPath[FILENAME_MAX];

        if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath))) {
            std::cout << errno << std::endl;
            throw std::runtime_error("Invalid path length");
        }

        cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

        return cCurrentPath;
    }

    static void colorReference() {
        std::cout << "\033[31m" << "Red" << "\033[0m" << " 31" << std::endl;
        std::cout << "\033[91m" << "Bright Red" << "\033[0m" << " 91" << std::endl;
        std::cout << "\033[35m" << "Magenta" << "\033[0m" << " 35" << std::endl;
        std::cout << "\033[95m" << "Bright Magenta" << "\033[0m" << " 95" << std::endl;
        std::cout << "\033[32m" << "Green" << "\033[0m" << " 32" << std::endl;
        std::cout << "\033[92m" << "Bright Green" << "\033[0m" << " 92" << std::endl;
        std::cout << "\033[33m" << "Yellow" << "\033[0m" << " 33" << std::endl;
        std::cout << "\033[93m" << "Bright Yellow" << "\033[0m" << " 93" << std::endl;
        std::cout << "\033[36m" << "Cyan" << "\033[0m" << " 36" << std::endl;
        std::cout << "\033[96m" << "Bright Cyan" << "\033[0m" << " 96" << std::endl;
        std::cout << "\033[34m" << "Blue" << "\033[0m" << " 34" << std::endl;
        std::cout << "\033[94m" << "Bright Blue" << "\033[0m" << " 94" << std::endl;
        std::cout << "\033[37m" << "White" << "\033[0m" << " 37" << std::endl;
        std::cout << "\033[97m" << "Bright White" << "\033[0m" << " 97" << std::endl;
    }

    static std::vector<std::string> readFile(const int day, const bool example = false) {
        const std::string path = "inputs/Day" + std::to_string(day) + (example ? "-example" : "") + ".txt";
        return readFile(path);
    }

    static std::vector<std::string> readFile(const std::string &path, bool debug = false) {
        std::vector<std::string> lines{};
#ifdef _WIN32
        std::string backtrace = "/../";
#else
        std::string backtrace = "/../";
#endif
        std::string filePath = pwd() + backtrace + path;
        if (debug) std::cout << "Reading file from " << filePath << std::endl;
        std::ifstream inputFile(filePath);
        std::string line;
        if (inputFile.is_open()) {
            while (getline(inputFile, line)) {
                lines.push_back(line);
            }
            inputFile.close();
        } else std::cout << "Unable to open file";

        return lines;
    }

    static std::vector<std::string> split(std::string input, char on = ' ') {
        std::string temp = std::move(input);
        std::vector<std::string> result{};
        bool finished{false};

        while (!finished) {
            int spaceIndex = temp.find(on);
            if (spaceIndex == -1) finished = true;
            std::string token = temp.substr(0, spaceIndex);
            if (!token.empty()) result.push_back(token);
            temp = temp.substr(spaceIndex + 1);
        }

        return result;
    }

    static std::vector<char> splitIntoChars(const std::string &input) {
        std::vector<char> result{};

        result.reserve(input.length());
        for (int i = 0; i < input.length(); ++i) {
            result.push_back(input[i]);
        }

        return result;
    }

    static std::vector<int> splitIntoInts(const std::string &input) {
        std::vector<int> result{};

        result.reserve(input.length());
        for (int i = 0; i < input.length(); ++i) {
            result.push_back(input[i] - '0');
        }

        return result;
    }

    static std::string leftPad(const int number, const int width) {
        std::string text = std::to_string(number);
        if (text.length() < width) {
            int spaces = width - text.length();
            for (int i: std::views::iota(0, spaces)) {
                text = " " + text;
            }
        }
        return text;
    }
};


#endif //HELPERS_H
