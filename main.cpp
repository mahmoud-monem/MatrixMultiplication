#include <iostream>

using namespace std;

void readFile()
{
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);
}

int main()
{
    readFile();
    string x;
    cin >> x;
    cout << x << endl;
    return 0;
}