#include <iostream>
#include <vector>
using namespace std;

template <typename T>
struct node {
    T data;
    node<T>* next;
    node<T>* pred;
};

template <typename T>
class LinkedList {
public:
    LinkedList();
    LinkedList(vector<T> a, int n);
    int size();
    T get_element(const int& i) const;
    node<T>* locate(const T& x) const;
    void insert(const int& i, const T& x);
    void delete_element(const int& i);
    void convert();
    void PrintTest();

private:
    int count;
    node<T>* head;
};

template <typename T>
LinkedList<T>::LinkedList(vector<T> a, int n)
{
    head = new node<T>;
    node<T>* p = head;
    for (int i = 0; i < n; i++) {
        p->next = new node<T>;
        node<T>* q = p;
        p = p->next;
        p->pred = q;
        p->data = a[i];
    }
    p->next = NULL;
    count += n;
}

template <typename T>
int LinkedList<T>::size()
{
    node<T>* p = head->next;
    int n = 0;
    while (p != NULL) {
        n++;
        p = p->next;
    }
    return n;
}

template <typename T>
T LinkedList<T>::get_element(const int& i) const
{
    node<T>* p = head->next;
    int j = 0;
    while (j != i && p != NULL) {
        p = p->next;
        j++;
    }
    if (p == NULL)
        return INT_MIN;
    return p->data;
}

template <typename T>
node<T>* LinkedList<T>::locate(const T& x) const
{
    node<T>* p = head->next;
    while (p != NULL)
        if (p->data == x)
            return p;
        else
            p = p->next;
    return NULL;
}

template <typename T>
void LinkedList<T>::insert(const int& i, const T& x)
{
    node<T>* p = head;
    int j = 0;
    while (j != i && p != NULL) {
        p = p->next;
        ++j;
    }
    if (p == NULL)
        return;
    node<T>* s = new node<T>;
    s->data = x;
    s->next = p->next;
    p->next = s;
    count++;
}

template <typename T>
void LinkedList<T>::delete_element(const int& i)
{
    node<T>* p = head;
    int j = 0;
    while (j != i && p != NULL) {
        p = p->next;
        ++j;
    }
    if (i < 0 || i > count)
        return;
    node<T>* u = p->next;
    p->next = u->next;
    delete u;
    count--;
}

template <typename T>
void LinkedList<T>::PrintTest()
{
    node<T>* p = head->next;
    for (int i = 0; i < size(); ++i) {
        cout << p->data << ' ';
        p = p->next;
    }
}

template <typename T>
void LinkedList<T>::convert()
{
    node<T>*current = head->next, *q = NULL, *pr;
    head->next = NULL;
    while (current) {
        pr = current->next;
        if (pr != NULL)
            pr->pred = current;
        current->next = q;
        if (q != NULL)
            q->pred = current;
        q = current;
        current = pr;
    }
    head->next = q;
    q->pred = head;
}

int main(void)
{
    vector<int> a = { 1, 3, 5, 7, 10 };
    LinkedList<int> l(a, a.size());
    l.convert();
    l.PrintTest();

    system("pause");
    return 0;
}