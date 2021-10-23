//栈可以用向量vector实现，也可以用列表list实现！
#include <iostream>
using namespace std;
#include "vector.h"

template <typename T>
class Stack : public Vector<T>
{
public:
    void push(T const &e) { this->insert(this->size(), e); }
    T pop() { return remove(this->size() - 1); }
    T &top() { return (*this)[this->size() - 1]; }
};

void convert(Stack<char> &S, __int64 n, int base)
{
    static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    if (n > 0)
    {
        S.push(digit[n % base]);
        convert(S, n / base, base);
    }
}