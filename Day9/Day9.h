#ifndef DAY9_H
#define DAY9_H

#include "../Helpers.h"

using namespace std;

struct DiskBlock {
    DiskBlock(const int id, const int size, const int index): id(id), size(size), index(index) {
    }

    int index;
    int size;
    int id;
    bool checked{false};
};

class Day9 {
public:
    static long Part1();

    static long Part2();

    static long CalculateChecksum(const vector<int> *disk) {
        long total{0};

        for (int i = 0; i < disk->size(); i++) {
            if ((*disk)[i] == -1) return total;
            total += i * (*disk)[i];
        }
        return total;
    }

    static long CalculateChecksum(const vector<DiskBlock> *files) {
        long total{0};
        for (const auto &file: *files) {
            for (int i = file.index; i < file.size + file.index; i++) total += file.id * i;
        }
        return total;
    }
};

#endif //DAY9_H
