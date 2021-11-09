#include <iostream>
#include <cstddef>

void foo(int x){
    std::cout << "int" << std::endl;
}

void foo(char* p) {
    std::cout << "char*" << std::endl;
}

int main()
{
    foo(std::nullptr_t);
}
