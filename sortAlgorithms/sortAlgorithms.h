
#ifndef COURSE_WORK_SORTALGORITHMS_H
#define COURSE_WORK_SORTALGORITHMS_H

#include <iostream>
#include <vector>

namespace sort {
    struct SortInfo {
        std::string type;
        unsigned int timeMS;
        unsigned int numOfComps;
        unsigned int numOfSwaps;

        SortInfo(std::string type);

        friend std::ostream& operator<< (std::ostream& out, const SortInfo& info) {
            out
                    << info.type << " sort info:" << std::endl
                    << "Execution time: " << info.timeMS << " ms" << std::endl
                    << "Number of comparisons: " << info.numOfComps << std::endl
                    << "Number of swaps: " << info.numOfSwaps << std::endl;
            return out;
        }
    };


    size_t division(std::vector<int>& vec, size_t start, size_t end, SortInfo& info);

    void quickSort(std::vector<int>& vec, size_t start, size_t end, SortInfo& info);


    void heapify(std::vector<int>& vec, size_t size, size_t i, SortInfo& info);

    void buildHeap(std::vector<int>& vec, SortInfo& info);

    void heapSort(std::vector<int>& vec, SortInfo& info);


    void merge(std::vector<int>& vec, size_t start, size_t mid, size_t end, SortInfo& info);

    void mergeSort(std::vector<int>& vec, size_t start, size_t end, SortInfo& info);
}

#endif
