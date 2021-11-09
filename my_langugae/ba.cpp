#include <iostream>

/*class A
{
public:
    virtual void foo(A* a){}
private:
    int x;
};

class B: public A
{
public:
    B(){ l = 0;}
    void foo(A* a) override{
        l = 9;
    }
private:
    int l;
};
*/
int main()
{
   // A* p = new B{};
   // A* p1 = new B{};
   // B b1;
   // p->foo(&b1);
   int x = 12;
   double y = x;
   std::cout << y;
}
