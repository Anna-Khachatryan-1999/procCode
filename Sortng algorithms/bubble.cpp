#include <iostream>

template <typename T>
void bubble_sort(T* arr, int size)
{
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (arr[i] > arr[j]) {
                std::swap(arr[i], arr[j]);
            }
        }
    }
}

int main()
{
    int size;
    std::cin >> size;
    int* arr = new int[size];
    for (int i = 0; i < size; ++i) {
        std::cin >> arr[i];
    }
    bubble_sort<int>(arr, size);
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
