#include <iostream>
#include <algorithm>
#include "vector.h"
using namespace std;

typedef int Rank;          //��
#define DEFAULT_CAPACITY 3 //Ĭ�ϳ�ʼ����

void testIncrease()
{
    Vector<int> s;
    for (int i = 0; i != 10; ++i)
    {
        s.insert(0, i);
    }
    for (int i = 0; i != 10; ++i)
    {
        cout << s[i] << ' ';
    }
    cout << endl;
    increase(s);
    for (int i = 0; i != 10; ++i)
    {
        cout << s[i] << ' ';
    }
}
void testUniquify()
{
    Vector<int> s;
    s.insert(0, 1);
    s.insert(0, 1);
    s.insert(0, 1);
    s.insert(0, 2);
    s.insert(0, 2);
    s.insert(0, 2);
    s.insert(0, 2);
    s.insert(0, 3);
    s.insert(0, 3);
    s.insert(0, 3);
    s.insert(0, 3);

    for (int i = 0; i < s.size(); ++i)
    {
        cout << s[i] << ' ';
    }
}
void testMerge()
{
    Vector<int> s;
    for (int i = 0; i != 10; ++i)
    {
        s.insert(0, i);
    }
    increase(s);
    increase(s);
    increase(s);
    increase(s);
    increase(s);
    increase(s);
    increase(s);
    increase(s);
    increase(s);
    for (int i = 0; i != 10; ++i)
    {
        s.insert(0, i);
    }
    for (int i = 0; i != s.size(); ++i)
    {
        cout << s[i] << ' ';
    }
    cout << endl;
    s.sort(0, s.size());
    for (int i = 0; i != s.size(); ++i)
    {
        cout << s[i] << ' ';
    }
}

void test()
{
    //testIncrease();
    //testUniquify();
    testMerge();

}

int main(void)
{
    test();

    return 0;
}