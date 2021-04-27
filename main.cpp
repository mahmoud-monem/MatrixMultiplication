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
    // readFile();
    matrix matA = matrix(2, 2), matB = matrix(2, 2);
    matA[0][0] = 1;
    matA[0][1] = 2;
    matA[0][2] = 3;
    matA[1][0] = 4;
    matA[1][1] = 5;
    matA[1][2] = 6;

    matB[0][0] = 7;
    matB[0][1] = 8;
    matB[1][0] = 9;
    matB[1][1] = 10;
    matB[2][0] = 11;
    matB[2][1] = 12;

    matrix res = matA.strassenMultiplication(matB);
    res.print();
    return 0;
}