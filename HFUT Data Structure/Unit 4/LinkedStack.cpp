#include <iostream>
using namespace std;

template <typename T>
struct node
{
    T data;
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
    bool get_top(T &x);
    bool push(const T &x);
    void pop();

private:
    int count;
    node<T> *top;
};

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
bool Stack<T>::get_top(T &x)
{
    if (empty())
        return false;
    x = top->data;
    return true;
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

int main(void)
{
    Stack<int> s;
    int x;

    system("pause");
    return 0;
}