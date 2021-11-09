#include <iostream>

template <typename T>
void selection_sort(T* arr, int size)
{
    int key;
    for (int i = 0; i < size - 1; ++i) {
        key = i;
        for (int j = i + 1; j < size; ++j) {
            if (arr[key] < arr[j]) {
                key = j;
            }
        }
        std::swap(arr[i], arr[key]);
    }

}

template <typename T>
void insertion_sort(T* arr, int size)
{
    T key;
    int j;
    for (int i = 1; i < size; ++i) {
        j = i - 1;
        key = arr[i];
        while (j >= 0 && arr[j] < key) {
            arr[j+1] = arr[j];
            --j;
        }
        arr[j+1] = key;
    }
}

template <typename T>
void bubble_sort(T* arr, int size)
{
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (arr[i] < arr[j]) {
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
    //selection_sort<int>(arr, size);
    //insertion_sort<int>(arr, size);
    bubble_sort<int>(arr, size);
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
