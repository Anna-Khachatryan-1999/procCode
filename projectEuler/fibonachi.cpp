#include <iostream>

int fibonachi(int n) {
    int count = 0;
    int first = 1;
    int second = 2;
    while (second < n) {
        if (second % 2 == 0) {
            count += second;
        }
        int current = first + second;
        first = second;
        second = current;
    }
    return count;
}

int main()
{
    int n;
    std::cin >> n;
    std::cout << fibonachi(n) << std::endl;
    return 0;
}
