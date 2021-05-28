#include <iostream>
#include <vector>
#include "LinkedList.h"
using namespace std;

template <typename T>
LinkedList<T> interset(LinkedList<T> &l1, LinkedList<T> &l2)
{
    vector<T> v;
    for (int i=0; i < l1.size(); ++i)
        if (l2.locate(l1.get_element(i)) != NULL)
            v.push_back(l1.get_element(i));

            for(auto i:v)cout<<i<<' ';
    LinkedList<T> l(v, v.size());
    return l;
}

int main(void)
{
    vector<int> v1 = {1, 3, 5, 7, 9};
    vector<int> v2 = {2, 5, 6, 8, 9};
    LinkedList<int> l1(v1, v1.size());
    LinkedList<int> l2(v2, v2.size());
    interset(l1,l2);

    system("pause");
    return 0;
}