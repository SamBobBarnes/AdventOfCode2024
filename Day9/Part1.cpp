#include <numeric>

#include "Day9.h"

void Print(const vector<int> *disk) {
    cout << endl;
    for (auto &num: *disk) {
        if (num == -1)cout << '.';
        else cout << num;
    }
    cout << endl;
}

int FirstEmpty(const vector<int> *disk, const int lastI) {
    for (int i = lastI + 1; i < disk->size(); i++) {
        if ((*disk)[i] < 0) return i;
    }
    return -1;
}

int LastBlockElement(const vector<int> *disk, const int lastI) {
    for (int i = lastI - 1; i >= 0; i--) {
        if ((*disk)[i] >= 0) return i;
    }
    return -1;
}

long Day9::Part1() {
    const auto lines = Helpers::readFile(9, false);
    const auto input = Helpers::splitIntoInts(lines[0]);
    const auto diskSize = reduce(input.begin(), input.end());

    vector<int> disk{};
    disk.resize(diskSize);


    int i{0};
    int blockIndex{0};
    int diskIndex{0};
    for (auto &num: input) {
        if (i % 2 == 0) {
            for (int j = 0; j < num; j++) disk[diskIndex + j] = blockIndex;
            blockIndex++;
        } else {
            for (int j = 0; j < num; j++) disk[diskIndex + j] = -1;
        }
        diskIndex += num;
        i++;
    }

    int current = diskSize - 1;
    int firstEmpty = FirstEmpty(&disk, -1);

    // Print(&disk);
    while (firstEmpty < current) {
        disk[firstEmpty] = disk[current];
        disk[current] = -1;
        current = LastBlockElement(&disk, current);
        firstEmpty = FirstEmpty(&disk, firstEmpty);
        // Print(&disk);
    }


    return CalculateChecksum(&disk);
}
