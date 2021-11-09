#include <iostream>

void merge(int* arr, int first, int mid, int end)
{
    int n1 = mid - first + 1;
    int n2 = end - mid;
    int* arr1 = new int[n1];
    int* arr2 = new int[n2];
    for (int i = 0; i < n1; ++i) {
        arr1[i] = arr[first + i];
    }
    for (int i = 0; i < n2; ++i)
    {
        arr2[i] = arr[mid + i + 1];
    }
    int i1 = 0;
    int i2 = 0;
    for (int i = first; i <= end; ++i) {
        if (i1 < n1 && (i2 == n2 || arr1[i1] < arr2[i2])) {
            arr[i] = arr1[i1];
            ++i1;
        } else {
            arr[i] = arr2[i2];
            ++i2;
        }
    }
}

void merge_sort(int* arr, int first, int end)
{
    if (first < end) {
    int mid = (end + first) / 2;
    merge_sort (arr, first, mid);
    merge_sort (arr, mid + 1, end);
    merge(arr, first, mid, end);
    }
}


int main()
{
    int size;
    std::cout << "input size - ";
    std::cin >> size;
    int* arr = new int[size];
    for (int i = 0; i < size; ++i) {
        std::cin >> arr[i];
    }
    merge_sort(arr, 0, size-1);
    for (int i = 0; i < size; ++i)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
    return 0;
}
