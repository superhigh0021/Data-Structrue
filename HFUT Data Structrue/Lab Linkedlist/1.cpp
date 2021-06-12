#include "LinkedList.h"
#include <iostream>
using namespace std;

template <typename T>
void spilit(LinkedList<T> L1)
{
    vector<int> v1;
    vector<int> v2;
    for (int i = 0; i < L1.size(); ++i)
    {
        if (L1[i] % 2 != 0)
            v1.push_back(L1[i]);
        else
            v2.push_back(L1[i]);
    }
    LinkedList<int> l1(v1, v1.size());
    LinkedList<int> l2(v2, v2.size());
    l1.PrintTest();
    l2.PrintTest();
}

template <typename T>
void Public_set(LinkedList<T> L1, LinkedList<T> L2)
{
    int i = 0, j = 0;
    vector<int> v;
    while (i < L1.size() && j < L2.size())
    {
        if (L1[i] < L2[j])
            ++i;
        else if (L1[i] > L2[j])
            ++j;
        else
        {
            v.push_back(L1[i]);
            ++i;
            ++j;
        }
    }
    LinkedList<int> l(v, v.size());
    l.PrintTest();
}

void test01()
{
    vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    LinkedList<int> L1(a, 10);
    cout << L1.locate(5) << endl;
    cout << L1.locate(10) << endl;
    cout << L1.locate(11) << endl;
    cout << L1.locate(12) << endl
         << endl;
    vector<int> b;
    LinkedList<int> L2(b, 0);
    cout << L2.locate(1) << endl;
    cout << L2.locate(2) << endl;
}

void test02()
{
    vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    LinkedList<int> L2(a, 10);
    L2.insert(5, 100);
    L2.insert(10, 100);
    L2.PrintTest();
    L2.insert(11, 100);
    L2.PrintTest();
    L2.insert(0, 100);
    L2.PrintTest();
    L2.insert(1, 100);
    L2.PrintTest();
    L2.insert(12, 100);
    L2.PrintTest();
    vector<int> b = {0};
    LinkedList<int> L3(a, 0);
    L3.insert(5, 100);
}

void test03()
{
    vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    LinkedList<int> L1(a, 10);
    L1.PrintTest();
    L1.delete_element(5);
    L1.delete_element(10);
    L1.delete_element(1);
    L1.PrintTest();
    L1.delete_element(11);
    L1.delete_element(0);
    L1.PrintTest();
    vector<int> b = {0};
    LinkedList<int> L3(b, 0);
    L3.delete_element(0);
}

void test04()
{
    vector<int> a = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    LinkedList<int> L1(a, 10);
    L1.PrintTest();
    L1.insert(L1.locate_element(25), 25);
    L1.PrintTest();
    L1.insert(L1.locate_element(85), 85);
    L1.PrintTest();
    L1.insert(L1.locate_element(110), 110);
    L1.PrintTest();
    L1.insert(L1.locate_element(8), 8);
    L1.PrintTest();
}

void test05()
{
    vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 60};
    LinkedList<int> L1(a, a.size());
    spilit(L1);

    cout << endl
         << endl;
    vector<int> b = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    LinkedList<int> L2(b, b.size());
    spilit(L2);
}

void test06()
{
    vector<int> v1 = {1, 3, 6, 10, 15, 16, 17, 18, 19, 20};
    vector<int> v2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 18, 20, 30};
    LinkedList<int> l1(v1, v1.size());
    LinkedList<int> l2(v2, v2.size());
    Public_set(l1, l2);

    // vector<int> v1 = {1, 3, 6, 10, 15, 16, 17, 18, 19, 20};
    // vector<int> v2 = {2, 4, 5, 7, 8, 9, 12, 22};
    // LinkedList<int> l1(v1, v1.size());
    // LinkedList<int> l2(v2, v2.size());
    // Public_set(l1, l2);

    // vector<int> v1 ;
    // vector<int> v2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // LinkedList<int> l1(v1, v1.size());
    // LinkedList<int> l2(v2, v2.size());
    // Public_set(l1, l2);
}

int main(void)
{

    test01();
    test02();
    test03();
    test04();
    test05();
    test06();

    system("pause");
    return 0;
}
