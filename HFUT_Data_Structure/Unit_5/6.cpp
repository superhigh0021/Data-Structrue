#include <iostream>
#include "LinkedList.h"
#include <vector>
using namespace std;

template <typename T>
bool JudgeSubset(LinkedList<T> &l1, LinkedList<T> &l2)
{
    int cnt = 0;
    for (int i = 0; i < l1.size(); ++i)
    {
        if (l2.locate(l1.get_element(i)) != NULL)
            ++cnt;
    }
    if (cnt == l1.size())
        return 1;
    return 0;
}

int main(void)
{
    vector<int> v1 = {1, 3, 5, 7};
    vector<int> v2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    LinkedList<int> l1(v1, v1.size());
    LinkedList<int> l2(v2, v2.size());
    cout<<JudgeSubset(l1,l2);

    system("pause");
    return 0;
}