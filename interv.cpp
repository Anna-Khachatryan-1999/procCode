#include <iostream>

class A
{
public:
    A() :i(0) {}
protected:
    int i;
};

class B
{
public:
    B() :d(0.0) {}
protected:
    double d;
};

class C : public A, public B
{
public:
    C() : c1{'a'}{}
private:
    char c1;
};

int main()
{
    C c;
    A* a = &c;
    B* b = &c;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << &c << std::endl;
    std::cout << (a == &c) << std::endl;
    std::cout << (b == &c) << std::endl;
    std::cout << (reinterpret_cast<void*>(b) == reinterpret_cast<void*>(a)) << std::endl;
}
