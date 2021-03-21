#include <iostream>
using namespace std;
#define maxlen 10;

template <typename T>
class Queue {
public:
    Queue();
    bool empty() const;
    bool full() const;
    error_code get_front(T& x);
    error_code append(const T& x);
    error_code serve();

private:
    int front, count, rear;
    T data[maxlen];
};

template <typename T>
Queue<T>::Queue()
{
    count = 0;
    front = rear = 0;
}

template <typename T>
bool Queue<T>::empty()
{
    if (front == rear)
        return true;
    return false;
}

template <typename T>
bool Queue<T>::full()
{
    if (count = maxlen - 1)
        return true;
    return false;
}

template <typename T>
error_code Queue<T>::get_front()
{
    if (this->empty())
        return UNDERFLOW;
    return
}