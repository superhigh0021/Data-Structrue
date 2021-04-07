#include <iostream>
#include <memory>
using namespace std;

#define DEFAULT_CAPACITY 10

template <typename T>
class SequenceStack
{
private:
    int count;
    T *data;
    int capacity;
    void expand();

public:
    SequenceStack();
    SequenceStack(T a[], int _size);
    ~SequenceStack();
    int size(){
        return count;
    }
    bool empty() const;
    bool full() const;
    T get_top() const;
    void push(const T &x);
    void pop();
    void PrintStack();
};

template <typename T>
void SequenceStack<T>::expand()
{
    if (count < capacity)
        return;
    if (capacity < DEFAULT_CAPACITY)
        capacity = DEFAULT_CAPACITY;
    T *OldData = data;
    data = new T[capacity <<= 1];
    for (int index = 0; index < count; ++index)
        data[index] = OldData[index];
    delete[] OldData;
}

template <typename T>
SequenceStack<T>::SequenceStack()
{
    count = 0;
    capacity=DEFAULT_CAPACITY;
}

template <typename T>
SequenceStack<T>::SequenceStack(T a[], int _size)
{
    capacity=DEFAULT_CAPACITY;
    count = _size;
    data=new T[count];
    for (int index = 0; index < count; ++index)
    {
        data[index] = a[index];
    }
}

template <typename T>
bool SequenceStack<T>::empty() const
{
    return count == 0;
}

template <typename T>
bool SequenceStack<T>::full() const
{
    return count == DEFAULT_CAPACITY;
}

template <typename T>
T SequenceStack<T>::get_top() const
{
    if (this->empty())
    {
        cout << "The Stack is empty!";
        return -1;
    }
    return data[count - 1];
}

template <typename T>
void SequenceStack<T>::push(const T &x)
{
    if (count + 1 == capacity)
        this->expand();
    if(count==0){
        data=new T;
        ++count;
        data[0]=x;
        return;
    }
    ++count;
    data[count-1] = x;
}

template <typename T>
void SequenceStack<T>::pop()
{
    if (this->empty())
    {
        cout << "The Stack is empty!";
        return;
    }
    --count;
}

template <typename T>
SequenceStack<T>::~SequenceStack()
{
    count = 0;
}

template <typename T>
void SequenceStack<T>::PrintStack()
{
    for (int index = count-1; index >=0; --index)
        cout << data[index];
}