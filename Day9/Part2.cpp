#include <numeric>

#include "Day9.h"

DiskBlock *GetLastUncheckedFile(vector<DiskBlock> *files) {
    int largestId{-1};
    DiskBlock *lastUnchecked = nullptr;

    for (auto &file: *files) {
        if (!file.checked && file.id > largestId) {
            largestId = file.id;
            lastUnchecked = &file;
        }
    }

    return lastUnchecked;
}

void PrintBlocks(const vector<DiskBlock> *files, const int diskSize) {
    string output(diskSize, '.');

    for (auto &file: *files) {
        for (int i = file.index; i < file.size + file.index; i++) output[i] = to_string(file.id)[0];
    }

    cout << endl << output;
}

long Day9::Part2() {
    const auto lines = Helpers::readFile(9, false);
    const auto input = Helpers::splitIntoInts(lines[0]);
    const auto diskSize = reduce(input.begin(), input.end());

    vector<DiskBlock> files{};
    vector<DiskBlock> emptyBlocks{};


    int i{0};
    int blockIndex{0};
    int diskIndex{0};
    for (auto &num: input) {
        if (i % 2 == 0) {
            files.emplace_back(blockIndex, num, diskIndex);
            blockIndex++;
        } else {
            emptyBlocks.emplace_back(-1, num, diskIndex);
        }
        diskIndex += num;
        i++;
    }

    auto current = GetLastUncheckedFile(&files);

    // PrintBlocks(&files, diskSize);
    while (current != nullptr) {
        for (auto &block: emptyBlocks) {
            if (!block.size) continue;
            if (block.size >= current->size && block.index < current->index) {
                current->index = block.index;
                block.size -= current->size;
                block.index += current->size;
                break;
            }
        }

        // PrintBlocks(&files, diskSize);
        current->checked = true;
        current = GetLastUncheckedFile(&files);
    }
    // cout << endl;

    return CalculateChecksum(&files);
    // < 8456900406063
}
