//
// Created by sb17057 on 12/6/2024.
//

#ifndef TIMER_H
#define TIMER_H
#include <chrono>
#include <iostream>
#include <map>


class Timer {
private:
    std::map<std::string, std::vector<std::chrono::time_point<std::chrono::system_clock> > > timers{};

public:
    void Start(const std::string &label) {
        if (timers.contains(label)) {
            std::cerr << "TILT! Timer'" << label << "' already exists";
            throw;
        }
        timers[label] = {std::chrono::high_resolution_clock::now()};
    }

    void End(const std::string &label) {
        auto t2 = std::chrono::high_resolution_clock::now();
        if (!timers.contains(label)) {
            std::cerr << "TILT! Timer'" << label << "' does not exist";
            throw;
        }
        if (timers[label].size() > 1) {
            std::cerr << "TILT! Timer'" << label << "' has already been ended";
            throw;
        }
        timers[label].push_back(t2);
    }

    void Clear(const std::string &label) {
        if (!timers.contains(label)) {
            std::cerr << "TILT! Timer'" << label << "' does not exist";
            throw;
        }
        const auto it = timers.find(label);
        timers.erase(it);
    }

    double GetTime(const std::string &label) {
        const std::chrono::duration<double, std::milli> ms_double = timers[label].back() - timers[label].front();
        return ms_double.count();
    }
};


#endif //TIMER_H
