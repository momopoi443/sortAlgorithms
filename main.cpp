#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include "sortAlgorithms/sortAlgorithms.h"

using namespace std::literals;

void howToFill(short& choice) {
    std::cout
            << "1. Generate random array" << std::endl
            << "2. Enter from keyboard" << std::endl
            << "3. Enter from file" << std::endl
            << "Choose:";
    std::cin >> choice;
}

void fillRand(std::vector<int>& vec, int leftB, int rightB) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<size_t> dist(leftB, rightB);
    std::generate(vec.begin(), vec.end(), [&] () {return dist(mt);});
}

void fillFromFile(std::vector<int>& vec, const std::string& path) {
    std::ifstream file;
    file.open(path);
    if(!file.is_open()) {
        std::cout << "Wrong path!";
        exit(-1);
    }

    int i;
    while(file >> i) {
        vec.push_back(i);
    }
    file.close();
}

void howToSort(short& choice) {
    while (choice < 1 || choice > 4) {
        std::cout
                << "1. Quick sort" << std::endl
                << "2. Heap sort" << std::endl
                << "3. Merge sort" << std::endl
                << "4. All" << std::endl;
        std::cout << "Choose sort (Enter 1, 2, 3 or 4):";
        std::cin >> choice;
    }
}

void printMsg(const std::vector<int>& vec, const sort::SortInfo& info) {
    std::cout
            << info
            << "Sorted array:" << std::endl;
    for(auto& i: vec) std::cout << i << " ";
    std::cout << std::endl << std::endl;
}

void writeToFile(std::vector<int>& vec, const std::string& path) {
    std::ofstream file;
    file.open(path);

    for(auto& i: vec) file << i << " ";
    file.close();
}

int main() {
    std::vector<int> vec;
    std::string path = "-1";

    short choice = -1;
    howToFill(choice);
    switch (choice) {
        case 1: {
            long long size = -1;
            while (size < 0 || size > vec.max_size()) {
                std::cout << "Enter size:";
                std::cin >> size;
            }

            int rightB, leftB;
            std::cout << "Left border:";
            std::cin >> leftB;
            std::cout << "Right border:";
            std::cin >> rightB;

            vec.resize(size);
            fillRand(vec, leftB, rightB);
            break;
        }
        case 2: {
            long long size = -1;
            while (size < 0 || size > vec.max_size()) {
                std::cout << "Enter size:";
                std::cin >> size;
            }

            vec.resize(size);
            for (auto &i: vec) std::cin >> i;
            break;
        }
        case 3: {
            std::cout << "Enter absolute path of file:";
            std::cin >> path;

            fillFromFile(vec, path);
        }
        break;
    }

    choice = -1;
    howToSort(choice);
    switch (choice) {
        case 1: {
            sort::SortInfo sortInfo("Quick");

            auto start = std::chrono::steady_clock::now();
            sort::quickSort(vec, 0, vec.size() - 1, sortInfo);
            auto end = std::chrono::steady_clock::now();
            sortInfo.timeMS = (end - start) / 1ms;

            printMsg(vec, sortInfo);
            break;
        }
        case 2: {
            sort::SortInfo sortInfo("Heap");

            auto start = std::chrono::steady_clock::now();
            sort::heapSort(vec, sortInfo);
            auto end = std::chrono::steady_clock::now();
            sortInfo.timeMS = (end - start) / 1ms;

            printMsg(vec, sortInfo);
            break;
        }
        case 3: {
            sort::SortInfo sortInfo("Merge");

            auto start = std::chrono::steady_clock::now();
            sort::mergeSort(vec, 0, vec.size(), sortInfo);
            auto end = std::chrono::steady_clock::now();
            sortInfo.timeMS = (end - start) / 1ms;

            printMsg(vec, sortInfo);
            break;
        }
        case 4: {
            sort::SortInfo info[3] {sort::SortInfo("Quick"),
                                    sort::SortInfo("Heap"),
                                    sort::SortInfo("Merge")};

            auto vec1 = vec;
            auto vec2 = vec;

            auto start = std::chrono::steady_clock::now();
            sort::quickSort(vec, 0, vec.size() - 1, info[0]);
            auto end = std::chrono::steady_clock::now();
            info[0].timeMS = (end - start) / 1ms;

            printMsg(vec, info[0]);

            start = std::chrono::steady_clock::now();
            sort::heapSort(vec1, info[1]);
            end = std::chrono::steady_clock::now();
            info[1].timeMS = (end - start) / 1ms;

            printMsg(vec1, info[1]);

            start = std::chrono::steady_clock::now();
            sort::mergeSort(vec2, 0, vec.size(), info[2]);
            end = std::chrono::steady_clock::now();
            info[2].timeMS = (end - start) / 1ms;

            printMsg(vec2, info[2]);
            break;
        }
    }

    choice = -1;
    std::cout << "Save array in file? (1 / any):";
    std::cin >> choice;
    if (choice == 1) {
            std::cout << "Enter absolute path of file:";
            std::cin >> path;
            writeToFile(vec, path);
    }

    system("Pause");
    return 0;
}
