#include <iostream>

int multipiesTreeOrFive(int n) {
    int count = 0;
    int three = 3;
    int five = 5;
    while (three < n) {
        if (three % 5 != 0) {
            count += three;
        }
        if (five < n) {
            count += five;
            five += 5;
        }
        three += 3;
    }
    return count;
}

int main()
{
    int n;
    std::cin >> n;
    std::cout << multipiesTreeOrFive(n) << std::endl;
    return 0;
}
