#include <iostream>
using namespace std;

template <typename T>
class Queue {
public:
    Queue(int size);
    bool empty();
    bool full();
    bool get_front(T& x);
    bool append(T const& x);
    bool serve(T& x);
    ~Queue()
    {
        delete[] data;
    }

private:
    T* data;
    int maxsize = 0, front = 0, count = 0;
};

template <typename T>
Queue<T>::Queue(int size)
{
    maxsize = size;
    data = new T[size];
}

template <typename T>
bool Queue<T>::empty()
{
    if (count == 0)
        return true;
    return false;
}

template <typename T>
bool Queue<T>::full()
{
    if (count + 1 == maxsize)
        return true;
    return false;
}

template <typename T>
bool Queue<T>::get_front(T& x)
{
    if (empty()) {
        cout << "EMPTY!" << endl;
        return false;
    }
    x = data[front];
    front = (front + 1) % maxsize;
    return true;
}

template <typename T>
bool Queue<T>::append(T const& x)
{
    if (full()) {
        cout << "Overflow!" << endl;
        return false;
    } else {
        data[count] = x;
        count++;
        return true;
    }
}

template <typename T>
bool Queue<T>::serve(T& x)
{
    if (empty()) {
        cout << "Empty!";
        return false;
    } else {
        x = data[front];
        front = (front + 1) % maxsize;
        return true;
    }
}