#include <iostream>
using namespace std;

template <class T>
class Queue {
private:
    int maxSize;
    int front;
    int rear;
    int* queue;
    bool tag;

public:
    Queue(int size);
    ~Queue()
    {
        delete[] queue;
    }
    bool append(const T& x);
    bool serve(T& x);
    bool get_front(T& x);
};

template <class T>
Queue<T>::Queue(int size)
{
    maxSize = size;
    flag = 0;
    queue = new T[maxSize];
    front = rear = 0;
}

template <class T>
bool Queue<T>::append(const T& x)
{
    if (rear == front && flag) {
        cout << "FULL,overflow!" << endl;
        return false;
    }
    queue[rear] = x;
    rear = (rear + 1) % maxSize;
    flag = 1;
    return true;
}

template <class T>
bool Queue<T>::serve(T& x)
{
    if (rear == front && !flag) {
        cout << "EMPTY,overflow" << endl;
        return false;
    }
    x = queue[front];
    front = (front + 1) % maxSize;
    flag = 0;
    return true;
}

template <class T>
bool Queue<T>::get_front(T& x)
{
    if (rear == front && !flag) {
        cout << "EMPTY,overflow£¡" << endl;
        return false;
    }
    x = queue[front];
    return true;
}