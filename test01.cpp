#include <iostream>
using namespace std;
#include <ctime>
#include <vector>

class A {
public:
    int m;
    A(int c)
        : m(c)
    {
    }
};
class B : virtual public A {
public:
    B(int c,int d)
        : A(c),n(d)
    {
    }
    int n;
};

class C : public B {
public:
    C(int c,int d)
        : B(c,d)
        , A(c)
    {
    }
};

int main(void)
{
    A a(100);
    B b(555,312);
    C c(132,999);
    cout << c.m;

    system("pause");

    return 0;
}