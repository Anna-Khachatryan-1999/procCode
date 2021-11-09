#include <iostream>
#include <memory>
#include <string>

class A
{
public:
    A(){}
private:
    int x;
};

A deleter(int *p, int x) {
    A a;
    return a;
}

int main()
{
    //int* pInt = new int(42);
    std::shared_ptr<int> pShared(new int, deleter);
 /*std::shared_ptr<int> pShared1(pInt);
    outpu("Naked pointer ", pInt);
    *pInt = 32;
    std::cout << *pShared << "\n";
    // output("Shared pointer ", pShared); // compiler error
    outpu("Shared pointer with get() ", pShared.get());
        outpu("Shared pointer with get() ", pShared1.get());

 
    delete pInt;*/
}
