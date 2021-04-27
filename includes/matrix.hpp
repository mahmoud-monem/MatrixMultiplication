#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

class matrix
{
private:
    int n, m;
    vector<vector<int>> mat;
    matrix _strassenMultiplication(matrix, int, int, int);

public:
    matrix(int, int);
    ~matrix();

    void print();
    matrix naiveMultiplication(matrix);
    matrix strassenMultiplication(matrix);
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

matrix matrix::strassenMultiplication(matrix b)
{
    return this->_strassenMultiplication(b, this->n, this->m, b.m);
}

matrix matrix::_strassenMultiplication(matrix b, int n, int l, int m)
{
    if (n == 1 || l == 1 || m == 1)
    {
        return this->naiveMultiplication(b);
    }
    else
    {
        int adjN = (n >> 1) + (n & 1);
        int adjL = (l >> 1) + (l & 1);
        int adjM = (m >> 1) + (m & 1);

        matrix separatedA[2][2];
        for (int x = 0; x < 2; x++)
        {
            for (int y = 0; y < 2; y++)
            {
                separatedA[x][y] = matrix(adjN, adjL);
                for (int i = 0; i < adjN; i++)
                {
                    for (int j = 0; j < adjL; j++)
                    {
                        int I = i + (x & 1) * adjN;
                        int J = j + (y & 1) * adjL;
                        separatedA[x][y][i][j] = (I < n && J < l) ? this->mat[I][J] : 0;
                    }
                }
            }
        }

        matrix separatedB[2][2];
        for (int x = 0; x < 2; x++)
        {
            for (int y = 0; y < 2; y++)
            {
                separatedB[x][y] = matrix(adjL, adjM);
                for (int i = 0; i < adjL; i++)
                {
                    for (int j = 0; j < adjM; j++)
                    {
                        int I = i + (x & 1) * adjL;
                        int J = j + (y & 1) * adjM;
                        separatedB[x][y][i][j] = (I < l && J < m) ? b[I][J] : 0;
                    }
                }
            }
        }

        matrix s[10];
        for (int i = 0; i < 10; i++)
        {
            switch (i)
            {
            case 0:
                s[i] = matrix(adjL, adjM);
                for (int j = 0; j < adjL; j++)
                {
                    for (int k = 0; k < adjM; k++)
                    {
                        s[i][j][k] = separatedB[0][1][j][k] - separatedB[1][1][j][k];
                    }
                }
                break;
            case 1:
                s[i] = matrix(adjN, adjL);
                for (int j = 0; j < adjN; j++)
                {
                    for (int k = 0; k < adjL; k++)
                    {
                        s[i][j][k] = separatedA[0][0][j][k] + separatedA[0][1][j][k];
                    }
                }
                break;
            case 2:
                s[i] = matrix(adjN, adjL);
                for (int j = 0; j < adjN; j++)
                {
                    for (int k = 0; k < adjL; k++)
                    {
                        s[i][j][k] = separatedA[1][0][j][k] + separatedA[1][1][j][k];
                    }
                }
                break;
            case 3:
                s[i] = matrix(adjL, adjM);
                for (int j = 0; j < adjL; j++)
                {
                    for (int k = 0; k < adjM; k++)
                    {
                        s[i][j][k] = separatedB[1][0][j][k] - separatedB[0][0][j][k];
                    }
                }
                break;
            case 4:
                s[i] = matrix(adjN, adjL);
                for (int j = 0; j < adjN; j++)
                {
                    for (int k = 0; k < adjL; k++)
                    {
                        s[i][j][k] = separatedA[0][0][j][k] + separatedA[1][1][j][k];
                    }
                }
                break;
            case 5:
                s[i] = matrix(adjL, adjM);
                for (int j = 0; j < adjL; j++)
                {
                    for (int k = 0; k < adjM; k++)
                    {
                        s[i][j][k] = separatedB[0][0][j][k] + separatedB[1][1][j][k];
                    }
                }
                break;
            case 6:
                s[i] = matrix(adjN, adjL);
                for (int j = 0; j < adjN; j++)
                {
                    for (int k = 0; k < adjL; k++)
                    {
                        s[i][j][k] = separatedA[0][1][j][k] - separatedA[1][1][j][k];
                    }
                }
                break;
            case 7:
                s[i] = matrix(adjL, adjM);
                for (int j = 0; j < adjL; j++)
                {
                    for (int k = 0; k < adjM; k++)
                    {
                        s[i][j][k] = separatedB[1][0][j][k] + separatedB[1][1][j][k];
                    }
                }
                break;
            case 8:
                s[i] = matrix(adjN, adjL);
                for (int j = 0; j < adjN; j++)
                {
                    for (int k = 0; k < adjL; k++)
                    {
                        s[i][j][k] = separatedA[0][0][j][k] - separatedA[1][0][j][k];
                    }
                }
                break;
            case 9:
                s[i] = matrix(adjL, adjM);
                for (int j = 0; j < adjL; j++)
                {
                    for (int k = 0; k < adjM; k++)
                    {
                        s[i][j][k] = separatedB[0][0][j][k] + separatedB[0][1][j][k];
                    }
                }
                break;
            }
        }

        matrix p[7];

        p[0] = separatedA[0][0]._strassenMultiplication(s[0], adjN, adjL, adjM);
        p[1] = s[1]._strassenMultiplication(separatedB[1][1], adjN, adjL, adjM);
        p[2] = s[2]._strassenMultiplication(separatedB[0][0], adjN, adjL, adjM);
        p[3] = separatedA[1][1]._strassenMultiplication(s[3], adjN, adjL, adjM);
        p[4] = s[4]._strassenMultiplication(s[5], adjN, adjL, adjM);
        p[5] = s[6]._strassenMultiplication(s[7], adjN, adjL, adjM);
        p[6] = s[8]._strassenMultiplication(s[9], adjN, adjL, adjM);

        matrix c(n, m);
        for (int i = 0; i < adjN; i++)
        {
            for (int j = 0; j < adjM; j++)
            {
                c[i][j] = p[4][i][j] + p[3][i][j] - p[1][i][j] + p[5][i][j];
                if (j + adjM < m)
                    c[i][j + adjM] = p[0][i][j] + p[1][i][j];
                if (i + adjN < n)
                    c[i + adjN][j] = p[2][i][j] + p[3][i][j];
                if (i + adjN < n && j + adjM < m)
                    c[i + adjN][j + adjM] = p[4][i][j] + p[0][i][j] - p[2][i][j] - p[6][i][j];
            }
        }

        return c;
    }
}
