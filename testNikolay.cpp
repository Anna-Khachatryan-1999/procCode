#include<functional>
#include<iostream>
#include <map>
/*std::function<int(int,int)> returnLambda ()
{
    return [] (int x, int y) {
        return x*y;
    };
}

/*struct B
{
char a1 : 1;
char a2 : 18;
int a3 : 1;
char a4 : 1;
}b;
int main()
{
    //auto lf = returnLambda();
    //std::cout << lf(6,7) << std::endl;
    //std::cout << returnLambda(6,7) << std::endl;
    int i = (3.5);
    std::cout << i << std::endl;
    int a1[10];
int a3[10];
std::swap(a1,a3);
    //std::cout << sizeof(char);
    //if(1 > -12)
      //  std::cout << "Yes";
    //else std::cout << "No";
   // int i = 5000000;
   // short n{i};
   // std::cout << n << std::endl;
  //  int i = 1;
 //   enum l {num = i}k;
    std::cout << sizeof(b) << std::endl;
   // int*a, t;
    //t = &i;
    int i = 12;
    if(i < 12.3) {
        std::cout << "yes";
    }

    short i1 = 5000000;
    //std::cout << i1 << std::endl;
    std::map<std::string,float> coll;
    decltype(coll)::value_type elem;
    //std::cout <<  std::is_same_v(decltype(coll)) << std::endl;
    std::cout << "\\\\n" << std::endl;
}*/


template <typename T>
void foo (T val)
{
    std::cout << val << std::endl;
    ++val;
}

int main()
{
    int x = 3;
    foo(std::ref(x));
    std::cout << x << std::endl;
}

