#include <iostream>
#include "LinkedList.h"
#include <vector>
using namespace std;

template <typename T>
void insert01(LinkedList<T> &l)
{
    l.insert(5, 100);
    l.insert(10, 100);
    l.insert(11, 100);
    l.insert(0, 100);
    l.insert(1, 100);
    l.insert(12, 100);
    l.PrintTest();
    cout << endl;
}

template <typename T>
void insert02(LinkedList<T> &l)
{
    l.insert(5, 100);
}

int main(void)
{
    vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    LinkedList<int> l1(v1, v1.size());
    insert01(l1);
    LinkedList<int> l2;
    insert02(l2);

    system("pause");
    return 0;
}
