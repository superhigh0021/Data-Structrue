#include <iostream>
#include <vector>
using namespace std;

template <typename T>
struct node1 {
    T data;
    node1<T>* next;
};

template <typename T>
class LinkedList1 {
public:
    LinkedList1(vector<T> a, int n);
    int size();
    void PrintTest();
    T operator[](const int& i);

private:
    int count;
    node1<T>* head;
};

template <typename T>
LinkedList1<T>::LinkedList1(vector<T> a, int n)
{
    head = new node1<T>;
    head->next=head;
    head->data=a[0];
    node1<T>* r = head;
    for (int i = 1; i < n; i++) {
        node1<T>* p=new node1<T>;
        p->data=a[i];
        r->next=p;
        r=p;
        r->next=head;
    }
    count += n;
}

template <typename T>
int LinkedList1<T>::size()
{
    if (count == 0)
        return 0;
    node1<T>* p = head;
    int n = 0;
    while (p->next!=head) {
        n++;
        p = p->next;
    }
    return n+1;
}


template <typename T>
void LinkedList1<T>::PrintTest()
{
    node1<T>* p = head->next;
    for (int i = 0; i < size(); ++i) {
        cout << p->data << ' ';
        p = p->next;
    }
    cout << endl;
}

template <typename T>
T LinkedList1<T>::operator[](const int& i)
{
    if (i < 0 || i >= size())
        return INT_MIN;
    node1<T>* p = head;
    for (int j = 0; j < i; ++j)
        p = p->next;
    return p->data;
}
