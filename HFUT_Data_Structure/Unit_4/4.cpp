#include <iostream>
#include <vector>
using namespace std;

template <typename T>
struct node
{
    int data;
    node<T> *next;
};

template <typename T>
class Stack
{
public:
    Stack();
    ~Stack();
    bool empty();
    bool full();
    int size()
    {
        return count;
    }
    T get_top();
    bool push(const T &x);
    void pop();

private:
    int count;
    node<T> *top;
};

template <typename T>
class LinkedList
{
public:
    node<T> *front;
    LinkedList(const T &x);
    LinkedList(vector<T> a, int n);
    int count = 0;
    int size()
    {
        return count;
    }
};

template <typename T>
LinkedList<T>::LinkedList(const T &x)
{
    front = new node<T>;
    front->data = x;
    front->next = NULL;
    count++;
}

template <typename T>
LinkedList<T>::LinkedList(vector<T> a, int n)
{
    front = new node<T>;
    node<T> *p = front;
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
Stack<T>::Stack()
{
    count = 0;
    top = NULL;
}

template <typename T>
bool Stack<T>::empty()
{
    return count == 0;
}

template <typename T>
bool Stack<T>::full()
{
    return false;
}

template <typename T>
T Stack<T>::get_top()
{
    if (empty())
        exit(0);
    return top->data;
}

template <typename T>
bool Stack<T>::push(const T &x)
{
    node<T> *s = new node<T>;
    s->data = x;
    s->next = top;
    top = s;
    count++;
    return true;
}

template <typename T>
void Stack<T>::pop()
{
    node<T> *x = top;
    top = top->next;
    delete x;
    count--;
}

template <typename T>
Stack<T>::~Stack()
{
    while (!empty())
        this->pop();
}

template <typename T>
LinkedList<T> merge(LinkedList<T> l1, LinkedList<T> l2)
{
    Stack<T> s1, s2;
    node<T> *p = l1.front->next, *q = l2.front->next;
    for (int i = 0; i < l1.size(); ++i)
    {
        s1.push(p->data);
        p = p->next;
    }
    for (int i = 0; i < l2.size(); ++i)
    {
        s2.push(q->data);
        q = q->next;
    }
    vector<T> v;
    while (s1.size() > 0 || s2.size() > 0)
    {
        if (s1.get_top() < s2.get_top())
        {
            v.push_back(s2.get_top());
            s2.pop();
        }
        else
        {
            v.push_back(s1.get_top());
            s1.pop();
        }
        while (s1.size() == 0 && s2.size() > 0)
        {
            for (int i = 0; i < s2.size(); ++i)
            {
                v.push_back(s2.get_top());
                s2.pop();
            }
        }
        while (s2.size() == 0 && s1.size() > 0)
        {
            for (int i = 0; i < s1.size(); ++i)
            {
                v.push_back(s1.get_top());
                s1.pop();
            }
        }
    }
    LinkedList<T> l(v, v.size());
    node<T> *s = l.front->next;
    for (int i = 0; i < l.size(); ++i)
    {
        cout << s->data << ' ';
        s = s->next;
    }
    return l;
}

int main(void)
{
    vector<int> v1 = {1, 3, 5, 7};
    vector<int> v2 = {2, 4, 6, 8, 10};
    LinkedList<int> l1(v1, v1.size());
    LinkedList<int> l2(v2, v2.size());
    merge(l1, l2);

    system("pause");
    return 0;
}