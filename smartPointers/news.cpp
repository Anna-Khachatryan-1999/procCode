#include <iostream>

struct B
{
    void operator()(int *)
    {
        std::cout << "qesc" ;
    }
};

class A
{
    public:
        template <class B>
        A(B ob()) {
        
        }
}
