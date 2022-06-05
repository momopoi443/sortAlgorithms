
#include "sortAlgorithms.h"

sort::SortInfo::SortInfo(std::string type) {
    this->type = std::move(type);
    timeMS = 0;
    numOfComps = 0;
    numOfSwaps = 0;
}


size_t sort::division(std::vector<int>& vec, size_t start, size_t end, SortInfo& info) {
    int v = vec[(int) (start + end) / 2];               // опорным является средний элемент
    size_t i = start;                                   // индекс i указывает на начало массива
    size_t j = end;                                     // индекс j - на конец массива
    while (i <= j) {                                    // повторяем действие пока индексы не пересекутся
        info.numOfComps++;
        while (vec[i] < v) {                            // передвигаем і вправо пока не найдём элемент больший опорного
            i++;
            info.numOfComps++;
        }
        info.numOfComps++;
        while (vec[j] > v) {                            // передвигаем j влево пока не найдём элемент меньший опорного
            j--;
            info.numOfComps++;
        }
        if (i >= j)                                     // досрочно выходим из цикла если индексы пересеклись
            break;
        std::swap(vec[i], vec[j]);               // меняем местами элементы под индексами і j
        info.numOfSwaps++;

        i++;                                            // делаем шаг і вправо, а j влево
        j--;
    }
    return j;
}

void sort::quickSort(std::vector<int>& vec, size_t start, size_t end, SortInfo& info) {
    if (start < end) {                                         // алгоритм заканчивает работу, когда входной массив состоит из одного елемента
        size_t mid = division(vec, start, end, info);          // основной шаг алгоритма: разделение входного массива на две части:
        quickSort(vec, start, mid, info);                 // большую и меньшую опорного элемента
        quickSort(vec, mid + 1, end, info);               // после разделение выполняем шаг для каждого подмассива
    }
}


void sort::heapify(std::vector<int>& vec, size_t size, size_t i, SortInfo& info) {
    size_t leftChild;                               // индексы левого потомка
    size_t rightChild;                              // правого
    size_t largestChild;                            // большего

    while (true) {
        leftChild = i * 2 + 1;                      // вычисляем индексы левого и правого потомков
        rightChild = i * 2 + 2;
        largestChild = i;                           // большому присваиваем значение входного

        info.numOfComps++;
        if (rightChild < size && vec[rightChild] > vec[largestChild]) {  // если правый больше родителя
            largestChild = rightChild;                                   // большему присваиваем значение правого
        }
        info.numOfComps++;
        if (leftChild < size && vec[leftChild] > vec[largestChild]) {     // если левый больше родителя
            largestChild = leftChild;                                    // большему присваиваем значение левого
        }
        if (largestChild == i)                                           // условие выхода из цикла
            break;

        std::swap(vec[i], vec[largestChild]);                     // меняем значения потомка больше родителя
        info.numOfSwaps++;
        i = largestChild;                                               // присваиваем поточному индексу индекс потомка
    }
}

void sort::buildHeap(std::vector<int>& vec, SortInfo& info) {
    for (size_t i = vec.size() / 2 - 1; i != ULONG_LONG_MAX; --i) { // повторяем действие для первой половины массива, так как именно нам хранятся корни
        heapify(vec, vec.size(), i, info);                 // каждый элемент перемещаем в нужное место
    }
}

void sort::heapSort(std::vector<int>& vec, SortInfo& info) {
    buildHeap(vec, info);                                       // сначала формируем бинарную кучу на основе данного массива
    for (size_t i = vec.size() - 1; i != ULONG_LONG_MAX; --i) { // повторяем действие начиная с конца массива
        std::swap(vec[0], vec[i]);                       // меняем первый и поточный элемент местами
        info.numOfSwaps++;
        heapify(vec, i, 0, info);                       // меняем положение первого элемента, чтоб не нарушать структуру кучи
    }
}


void sort::merge(std::vector<int>& vec, size_t start, size_t mid, size_t end, SortInfo& info) {
    size_t in1 = start;
    size_t in2 = mid;
    std::vector<int> buff(end - start);

    while (in1 < mid && in2 < end) {
        info.numOfComps++;
        if (vec[in1] < vec[in2]) {
            buff[in1 + in2 - start - mid] = vec[in1];
            in1++;
        } else {
            buff[in1 + in2 - start - mid] = vec[in2];
            in2++;
        }
    }

    while (in1 < mid) {
        buff[in1 + in2 - start - mid] = vec[in1];
        in1++;
    }
    while (in2 < end) {
        buff[in1 + in2 - start - mid] = vec[in2];
        in2++;
    }

    std::copy(buff.begin(), buff.end(), vec.begin() + start);
    info.numOfSwaps += buff.size();
}

void sort::mergeSort(std::vector<int>& vec, size_t start, size_t end, SortInfo& info) {
    if (start < end - 1) {
        size_t mid = (start + end) / 2;
        mergeSort(vec, start, mid, info);
        mergeSort(vec, mid, end, info);
        merge(vec, start, mid, end, info);
    }
}

