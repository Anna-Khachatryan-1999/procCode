#include <iostream>
using namespace std;

template<typename T>
string toBinary(const T& t)
{
  string s = "";
  int n = sizeof(T)*8;
  for(int i=n-1; i>=0; i--)
  {
    s += (t & (1 << i))?"1":"0";
  }
  return s;
}

int main()
{
  char a, b;

  short c;
  a = 58;
  c = -315;

  b = a >> 3;

  cout << "a = " << a << " => " << toBinary(a) << endl;
  cout << "b = " << b << " => " << toBinary(b) << endl;
  cout << "c = " << c << " => " << toBinary(c) << endl;
}
