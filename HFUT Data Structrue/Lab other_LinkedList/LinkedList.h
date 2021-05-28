#include <iostream>
#include <vector>
using namespace std;

template <typename T>
struct node2 {
    T data;
    node2<T>* next;
};

template <typename T>
class LinkedList2 {
public:
    LinkedList2();
    LinkedList2(vector<T> a, int n);
    node2<T>* locate(const T& x) const;
    int size();
    void PrintTest();
    T operator[](const int& i);

private:
    int count;
    node2<T>* head;
};

template <typename T>
LinkedList2<T>::LinkedList2()
{
    count = 0;
    this->head = NULL;
}

template <typename T>
LinkedList2<T>::LinkedList2(vector<T> a, int n)
{
    head = new node2<T>;
    head->next=head;
    node2<T>* r = head;
    for (int i = 0; i < n; i++) {
        node2<T>* p=new node2<T>;
        p->data=a[i];
        r->next=p;
        r=p;
        r->next=head;
    }
    count += n;
}

template <typename T>
int LinkedList2<T>::size()
{
    if (count == 0)
        return 0;
    node2<T>* p = head;
    int n = 0;
    while (p->next!=head) {
        n++;
        p = p->next;
    }
    return n;
}

template <typename T>
node2<T>* LinkedList2<T>::locate(const T& x) const
{
    node2<T>* p = head->next;
    while (p != head)
        if (p->data == x)
            return p;
        else
            p = p->next;
    return NULL;
}

template <typename T>
void LinkedList2<T>::PrintTest()
{
    node2<T>* p = head->next;
    for (int i = 0; i < size(); ++i) {
        cout << p->data << ' ';
        p = p->next;
    }
    cout << endl;
}

template <typename T>
T LinkedList2<T>::operator[](const int& i)
{
    if (i < 0 || i >= size())
        return INT_MIN;
    node2<T>* p = head->next;
    for (int j = 0; j < i; ++j)
        p = p->next;
    return p->data;
}
