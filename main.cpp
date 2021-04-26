#include <iostream>
#include <vector>
#include "./includes/matrix.hpp"

using namespace std;

void readFile()
{
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);
}

int main()
{
    readFile();
    matrix a = matrix(2, 2), b = matrix(3, 3);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            a[i][j] = 1;
            b[i][j] = 1;
        }
    }

    matrix res = a.naiveMultiplication(b);
    res.print();
    return 0;
}