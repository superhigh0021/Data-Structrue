#include "LinkedList.h"
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
LinkedList<T> Union(LinkedList<T>& l1, LinkedList<T>& l2)
{
    vector<T> v;
    for (int i = 0; i < l1.size(); ++i)
        v.push_back(l1.get_element(i));
    for (int i = 0; i < l2.size(); ++i) {
        if (l1.locate(l2.get_element(i)) != NULL)
            continue;
        v.push_back(l2.get_element(i));
    }

    LinkedList<T> l(v, v.size());
    l.PrintTest();
    return l;
}

int main(void)
{
    vector<int> v1 = { 1, 2, 3, 5 };
    vector<int> v2 = { 3, 5, 6, 4 };
    LinkedList<int> l1(v1, v1.size());
    LinkedList<int> l2(v2, v2.size());
    Union(l1, l2);

    system(("pause"));
    return 0;
}