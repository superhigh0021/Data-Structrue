#include <iostream>
using namespace std;

const int M = 10;

template<typename T>
class Queue {
public:
    bool empty();
    bool full();
    T get_front();
    void append(int x);
    void serve();

private:
    T data[M];
    int count = 0, count1 = 0;
    int turn = 0;
};

template<typename T>
bool Queue<T>::empty(){
    if (count == 0 && turn == 0)
        return true;
    return false;
}

template<typename T>
bool Queue<T>::full(){
    if (count + 1 == count1 || (count + 1 == 11 && count1 == 0))
        return true;
    return false;
}

template<typename T>
T Queue<T>::get_front(){
    return data[count1];
}

template<typename T>
void Queue<T>::append(int x){
    if (full())
        cout << "Overflow!" << endl;
    else {
        if (count == 10) {
            count = 0;
            turn++;
        }
        data[count] = x;
        count++;
    }
}

template<typename T>
void Queue<T>::serve(){
    if (empty())
        cout << "Empty!";
    else {
        data[count1] = 0;
        count1++;
    }
}