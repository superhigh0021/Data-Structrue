#include <iostream>
using namespace std;

#define DEFAULT_CAPACITY 20

template <typename T>
class SequenceStack
{
private:
    int count;
    T data[DEFAULT_CAPACITY];

public:
    SequenceStack();
    SequenceStack(T a[],int _size);
    ~SequenceStack();
    bool empty() const;
    bool full() const;
    T get_top() const;
    void push(const T &x);
    void pop();
    void PrintStack();
};

template <typename T>
SequenceStack<T>::SequenceStack()
{
    count = 0;
}

template<typename T>
SequenceStack<T>::SequenceStack(T a[],int _size){
    count=_size;
    for(int index=0;index<count;++index){
        data[index]=a[index];
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
    if(this->full()){
        cout<<"The Stack is FULL!";
        return;
    }
    ++count;
    data[count-1]=x;
}

template<typename T>
void SequenceStack<T>::pop(){
    if(this->empty()){
        cout<<"The Stack is empty!";
        return;
    }
    --count;
}

template<typename T>
SequenceStack<T>::~SequenceStack(){
    count=0;
}

template<typename T>
void SequenceStack<T>::PrintStack(){
    for(int index=0;index<count;++index)
    cout<<data[index]<<' ';
}

int main(void){
    int a[]={1,3,5,7,9};
    SequenceStack<int> s(a,end(a)-begin(a));
    s.PrintStack();

    system("pause");
    return 0;
}

