#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

class matrix
{
private:
    int n, m;
    vector<vector<int>> mat;

public:
    matrix(int, int);
    ~matrix();

    void print();
    matrix naiveMultiplication(matrix);
    vector<int> &operator[](int i);
};

matrix::matrix(int n = 0, int m = 0)
{
    this->n = n;
    this->m = m;
    this->mat = vector<vector<int>>(n, vector<int>(m, 0));
}

matrix::~matrix()
{
}

vector<int> &matrix::operator[](int i)
{
    return this->mat[i];
}

void matrix::print()
{
    for (int i = 0; i < this->n; i++)
    {
        for (int j = 0; j < this->m; j++)
        {
            cout << this->mat[i][j] << ' ';
        }
        cout << endl;
    }
}

matrix matrix::naiveMultiplication(matrix b)
{
    if (this->m != b.n)
    {
        throw logic_error("Invalid Matrix dimensions");
    }

    matrix result = matrix(this->n, b.m);
    for (int i = 0; i < this->n; i++)
    {
        for (int j = 0; j < b.m; j++)
        {
            for (int k = 0; k < b.n; k++)
            {
                result[i][j] += this->mat[i][k] * b[k][j];
            }
        }
    }
    return result;
}