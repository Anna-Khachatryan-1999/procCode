#include <iostream>
//#include <wstring>
//#define __cplusplus 199711L

void foo (const int& b){
    std::cout << "lv" << std::endl ;
}

void foo (int&& b){
    std::cout << "rv" << std::endl ;
}
int main()
{

    //foo(5);
    std::cout << R"f(a\
                 b\nc()"
                 "
                 )f" << std::endl;

    std::cout << "a\\n     b\\nc()\"\n     \"\n"  << std::endl;\




    std::wstring s = L"hello";
    std::cout << s[0] << std::endl;
}
