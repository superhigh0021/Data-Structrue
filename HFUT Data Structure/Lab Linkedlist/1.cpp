#include "LinkedList.h"
#include <iostream>
using namespace std;

template <typename T>
void test01(LinkedList<T> &l)
{
    cout << l[4] << ' ' << l[9] << ' ' << l[-1] << ' ' << l[10] << ' ' << l[11];
}

template <typename T>
void test02(LinkedList<T> &l)
{
    cout << l[-1] << ' ' << l[1];
}

int main(void)
{
    vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    LinkedList<int> l1(v1, v1.size());
    test01(l1);
    LinkedList<int> l2;
    test02(l2);

    system("pause");
    return 0;
}
