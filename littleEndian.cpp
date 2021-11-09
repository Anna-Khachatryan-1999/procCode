#include <iostream>

int main()
{
    int x = 1;
    char* cp = (char*)&x;
    if(*cp == 1)
        std::cout << "Little endian";
    else
        std::cout << "Big endian";
}
