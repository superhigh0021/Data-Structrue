#include <iostream>
using namespace std;

template <typename T>
struct node {
    T data;
    node* next;
};

template <typename T>
class Queue {
public:
    Queue();
    ~Queue();
    bool empty();
    bool full();
    bool get_front(T& x);
    bool append(const T& x);
    bool serve();

private:
    int count;
    node *front, *rear;
};

template <typename T>
Queue<T>::Queue()
{
    front = new node;
    rear = front;
    front->next = NULL;
    count = 0;
}

template <typename T>
bool Queue<T>::empty()
{
    return count == 0;
}

template <typename T>
bool Queue<T>::full()
{
    return false;
}

template <typename T>
bool get_front(T& x)
{
    if (empty())
        return false;
    x = front->next->data;
    return true;
}
template <typename T>
bool Queue<T>::append(const T& x)
{
    node* s = new node;
    s->data = x;
    s->next = NULL;
    rear->next = s;
    rear = s;
    count++;
    return true;
}
template <typename T>
bool Queue<T>::serve()
{
    if (empty())
        return false;
    node* x = front->next;
    front->next = x->next;
    delete x;
    count--;
    if (front->next == NULL)
        rear = front;
    return true;
}

template <typename T>
Queue<T>::~Queue()
{
    while (!empty())
        this->serve();
    count = 0;
    delete front;
    delete rear;
}