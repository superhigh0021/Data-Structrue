#include "AutoSequenceStack.h"
#include <iostream>
using namespace std;

void BaseConvertion(const int &num, const int &base)
{
    SequenceStack<int>s;
    int nums=num;
    while (nums != 0)
    {
        s.push(nums % base);
        nums/=base;
    }
    s.PrintStack();
}

int main(void){
    int num=0,base=0;
    cin>>num>>base;
    BaseConvertion(num,base);

    system("pause");
    return 0;
}