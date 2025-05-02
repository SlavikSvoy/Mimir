#include <iostream>
#include "Bubblesort.h"

int main() {
    int arr[] = { 5, 2, 9, 1, 5, 6 };
    int size = sizeof(arr) / sizeof(arr[0]);

    Bubblesort sorter;
    sorter.Sort(arr, size);

    std::cout << "Відсортований масив: ";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
