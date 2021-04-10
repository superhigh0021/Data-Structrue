#include "LinkedList.h"
#include <iostream>
using namespace std;

template <typename T>
void test01(LinkedList<T>& l, const int& _size)
{
    cout << l[5] << endl
         << NULL << endl
         << l[0] << NULL << endl
         << NULL<< endl;
    return;
}

int main(void)
{
    vector<int> v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    LinkedList<int> l1(v1, v1.size());
    test01(l1, l1.size());

    system("pause");
    return 0;
}