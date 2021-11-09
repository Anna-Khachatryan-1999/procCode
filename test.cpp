#include <iostream>
#include <vector>
#include <unordered_map>

class A
{
public:
    A(){
        std::cout << "A";
    }
    A(const A&) {
        std::cout << "B";
    }
    virtual void f() {
        std::cout << "C";
    }
};

class B
{
public:
    B() {foo();}
    virtual ~B() {foo();}
    virtual void foo() {std::cout << "1";}
    void bar(){foo();}
};
class C : public B
{
public:
    void foo() {std::cout << "2";}
};

int max(int a, int b)
{
    if(a == b) return a;
    if (a > b) return max(a-b, b);
    else return max(a, b-a);
}

int dubl(int* arr, int size)
{
    std::unordered_map<int, int> m;
    for (int i = 0; i < size; ++i) {
        if(++m[arr[i]] > 1) return arr[i];
    }
    return -1;
}

int main()
{
    std::vector<int> v =  {5, 10};
    std::cout << v.size() << v.at(2) << std::endl;
    A a[2];
    for (auto x : a)
    {
        x.f();
    }
    C c;
    c.bar();
    std::cout << std::endl;
    std::cout << max(12, 8) << std::endl;
    int arr[7] = {0, 1, 2, 3, 5, 9, 111};
    std::cout << dubl(arr, 7) << std::endl;
}
