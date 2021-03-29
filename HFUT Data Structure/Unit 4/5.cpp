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
    node<T> *p = front, *q = front;
    for (int i = 0; i < n; i++)
    {
        p->next = new node<T>;
        p = p->next;
        p->data = a[i];
    }
    p->next = NULL;
    q = q->next;
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

bool judge(const string &s1)
{
    vector<char> v;
    Stack<char> S;
    string s2;
    for (int i = 0; i < s1.size(); ++i)
        v.push_back(s1[i]);
    LinkedList<char> l(v, v.size());
    node<char> *p = l.front->next;
    for (int i = 0; i < l.size(); ++i)
    {
        S.push(p->data);
        p = p->next;
    }
    while (!S.empty())
    {
        s2.push_back(S.get_top());
        S.pop();
    }
    if (s1 == s2)
        return true;
    else
        return false;
}

int main(void)
{
    string s;
    cin >> s;
    cout<<judge(s);

    system("pause");
    return 0;
}