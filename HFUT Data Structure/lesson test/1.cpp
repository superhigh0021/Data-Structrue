#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void convert(vector<int> const &A, vector<int> const &B)
{
    vector<int> C;
    for (int i = 0; i < A.size(); ++i)
    {
        for (int j = 0; j < B.size(); ++j)
        {
            if (A[i] == B[j])
            {
                C.push_back(A[i]);
                break;
            }
            else
                continue;
        }
    }
    for (auto c : C)
        cout << c << ' ';
}

int main(void)
{
    vector<int> A = {1, 3, 6, 10, 67};
    vector<int> B = {3, 10};
    convert(A, B);

    system("pause");
    return 0;
}