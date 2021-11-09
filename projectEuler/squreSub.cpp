#include <iostream>

int squrtSub(int n) {
    int sumSqrt = 0;
    int sqrtSum = 0;
    for (int i = 1; i <= n; ++i) {
        sqrtSum += (i*i);
        sumSqrt += i;
    }
    return sumSqrt*sumSqrt - sqrtSum;
}

int main()
{
    int n;
    std::cin >> n;
    std::cout << squrtSub(n) << std::endl;
    return 0;
}
