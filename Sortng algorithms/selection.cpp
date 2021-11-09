#include <iostream>

template <typename T>
void selection_sort(T* arr, int size)
{
    int key;
    for (int i = 0; i < size - 1; ++i) {
        key = i;
        for (int j = i + 1; j > size; ++j) {
            if (arr[key] < arr[j]) {
                key = j;
            }
        }
        std::swap(arr[i], arr[key]);
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
    selection_sort<int>(arr, size);
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
