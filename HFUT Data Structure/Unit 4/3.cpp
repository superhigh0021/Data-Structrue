#include <iostream>
#include <vector>
using namespace std;

template <typename T>
struct node
{
    T data;
    node<T> *next;
};

template <typename T>
class LinkedList
{
public:
    node<T> *front;
    LinkedList(const T &x);
    LinkedList(vector<T> a, int n);
};
template <typename T>
LinkedList<T>::LinkedList(const T &x)
{
    front = new node<T>;
    front->data = x;
    front->next = NULL;
}
template <typename T>
LinkedList<T>::LinkedList(vector<T> a, int n)
{
    front = new node<T>;
    node<T> *p = front, *q = front;
    for (int i = 0; i < n; i++)
    {
        p->next = new node<T>;
        p = p->next;
        p->data = a[i];
    }
    p->next = NULL;
    q = q->next;
}
template <typename T>
void convert(LinkedList<T> &l)
{
    node<T> *p, *q, *pr;
    p = l.front->next;
    q = NULL;
    l.front->next = NULL;
    while (p)
    {
        pr = p->next;
        p->next = q;
        q = p;
        p = pr;
    }
    l.front->next = q;
}

int main(void)
{
    vector<int> a = {1, 3, 5, 7, 10};
    LinkedList<int> l(a, a.size());
    convert(l);
    node<int> *p = l.front->next;
    for (int i = 0; i < 5; ++i)
    {
        cout << p->data<<' ';
        p = p->next;
    }

    system("pause");
    return 0;
}