#include <iostream>
using namespace std;
  
int main()
{
    int arr[] = { 10, 20, 30, 40 };
  
    // Printing elements of an array using
    // foreach loop
    for (int x : arr)
        x = 1;
    for (int x : arr)
        cout << x << endl;
}

