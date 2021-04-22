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
    LinkedList();
    LinkedList(vector<T> a, int n);
    int size();
    T get_element(const int &i) const;
    node<T> *locate(const T &x) const;
    void insert(const int &i, const T &x);
    void delete_element(const int &i);
    void PrintTest();
    T operator[](const int &i);

private:
    int count;
    node<T> *head;
};

template <typename T>
LinkedList<T>::LinkedList()
{
    count = 0;
    this->head = NULL;
}

template <typename T>
LinkedList<T>::LinkedList(vector<T> a, int n)
{
    head = new node<T>;
    node<T> *p = head;
    for (int i = 0; i < n; i++)
    {
        p->next = new node<T>;
        p = p->next;
        p->data = a[i];
    }
    p->next = NULL;
    count += n;
}

template <typename T>
int LinkedList<T>::size()
{
    if (count == 0)
        return 0;
    node<T> *p = head->next;
    int n = 0;
    while (p != NULL)
    {
        n++;
        p = p->next;
    }
    return n;
}

template <typename T>
T LinkedList<T>::get_element(const int &i) const
{
    node<T> *p = head->next;
    int j = 0;
    while (j != i && p != NULL)
    {
        p = p->next;
        j++;
    }
    if (p == NULL)
        return INT_MIN;
    return p->data;
}

template <typename T>
node<T> *LinkedList<T>::locate(const T &x) const
{
    node<T> *p = head->next;
    while (p != NULL)
        if (p->data == x)
            return p;
        else
            p = p->next;
    return NULL;
}

template <typename T>
void LinkedList<T>::insert(const int &i, const T &x)
{
    if(i>size()){
        cout<<"ÉÏÒç£¡²åÈëÊ§°Ü£¡"<<endl;
        return;
    }
    node<T> *p = head;
    int j = 0;
    while (j != i && p != NULL)
    {
        p = p->next;
        ++j;
    }
    if (p == NULL)
        return;
    node<T> *s = new node<T>;
    s->data = x;
    s->next = p->next;
    p->next = s;
    count++;
}

template <typename T>
void LinkedList<T>::delete_element(const int &i)
{
    if(i<0||i>=size()){
        cout<<"ÏÂÒç£¡É¾³ýÊ§°Ü£¡"<<endl;
        return;
    }
    node<T> *p = head;
    int j = 0;
    while (j != i && p != NULL)
    {
        p = p->next;
        ++j;
    }
    if (i < 0 || i > count)
        return;
    node<T> *u = p->next;
    p->next = u->next;
    delete u;
    count--;
}

template <typename T>
void LinkedList<T>::PrintTest()
{
    node<T> *p = head->next;
    for (int i = 0; i < size(); ++i)
    {
        cout << p->data << ' ';
        p = p->next;
    }
}
template <typename T>
T LinkedList<T>::operator[](const int &i)
{
    if (i < 0 || i >= size())
        return INT_MIN;
    node<T> *p = head->next;
    for (int j = 0; j < i; ++j)
        p = p->next;
    return p->data;
}
