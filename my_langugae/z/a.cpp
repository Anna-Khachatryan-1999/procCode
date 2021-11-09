#include <iostream>

int main()
{
    int a = 6;
    if (a == 6) {
        int a = 7;
        std::cout << a << std::endl;
    }
    std::cout << a << std::endl;
    return 0;
}
