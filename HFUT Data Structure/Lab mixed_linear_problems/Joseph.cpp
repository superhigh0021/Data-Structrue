#include <iostream>
#include "LinkedList.h"
using namespace std;

template <typename T>
int count_update(LinkedList1<T> l)
{
    int sum = 0;
    for (int i = 0; i < l.size(); ++i)
        if (l[i] == 1)
            ++sum;
    return sum;
}

void Joseph()
{
    vector<int> v(41, 1);
    LinkedList1<int> l(v, v.size());
    node1<int> *p = l.head->next->next;
    for (; count_update(l) > 2;)
    {
        while (p->data == 0)
            p = p->next;
        p->data = 0;
        for (int i = 0; i < 3; ++i)
        {
            p = p->next;
            while (p->data == 0)
                p = p->next;
        }
    }
    for (int i = 0; i < l.size(); ++i)
        if (l[i] == 1)
            cout << i+1 << ' ';
}

int main(void)
{
    Joseph();

    system("pause");
    return 0;
}