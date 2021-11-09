#include <iostream>
#include <vector>

bool sudoku2(std::vector<std::vector<char>> grid) {
    int cur1 = 0;
    int cur2 = 0;
    int cur3 = 0;
    int cur = 0;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (grid[i][j] != '.') {
                cur = cur1;
                cur1 = cur1 ^ (1 << grid[i][j]);
                if (cur1 < cur) {
                    return false;
                }
            }
            if (grid[j][i] != '.') {
                cur = cur2;
                cur2 = cur2 ^ (1 << grid[j][i]);
                if (cur2 < cur) {
                    return false;
                }
            }
            if (grid[j/3 + (i/3 * 3)][j%3 + (i%3)*3] != '.') {
                cur = cur3;
                cur3 = cur3 ^ (1 << grid[j/3 + (i/3 * 3)][j%3 + (i%3)*3]);
                if (cur3 < cur) {
                    std::cout << i << " "  << j;
                    return false;
                }
            }
        }
        cur1 = 0; cur2 = 0; cur3 = 0;
    }
    return true;
}
int main()
{
    std::vector<std::vector<char>> v = {{'.','.','.','1','4','.','.','2','.'},
            { '.','.','6','.','.','.','.','.','.'},
            { '.','.','.','.','.','.','.','.','.'},
            { '.','.','1','.','.','.','.','.','.'},
            { '.','6','7','.','.','.','.','.','9'},
            { '.','.','.','.','.','.','8','1','.'},
            { '.','3','.','.','.','.','.','.','6'},
            { '.','.','.','.','.','7','.','.','.'},
            { '.','.','.','5','.','.','.','7','.'}};
    std::cout << sudoku2(v) << std::endl;
}
