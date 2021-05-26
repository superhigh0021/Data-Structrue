#include "LinkedList.h"
#include <iostream>
using namespace std;

void test01()
{
    vector<int> a = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    LinkedList<int> L1(a, 10);
    cout << L1.locate(5) << endl;
    cout << L1.locate(10) << endl;
    cout << L1.locate(11) << endl;
    cout << L1.locate(12) << endl;
    vector<int> b = { 0 };
    LinkedList<int> L2(b, 0);
    cout << L2.locate(0) << endl;
    cout << L2.locate(2) << endl;
}

void test02()
{
    vector<int> a = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
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
    vector<int> b = { 0 };
    LinkedList<int> L3(a, 0);
    L3.insert(5, 100);
}

void test03()
{
    vector<int> a = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    LinkedList<int> L1(a, 10);
    L1.PrintTest();
    L1.delete_element(5);
    L1.delete_element(10);
    L1.delete_element(1);
    L1.PrintTest();
    L1.delete_element(11);
    L1.delete_element(0);
    L1.PrintTest();
    vector<int> b = { 0 };
    LinkedList<int> L3(b, 0);
    L3.delete_element(0);
}

void test04()
{
    vector<int> a = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
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

int main(void)
{

    test01();
    test02();
    test03();
    test04();

    system("pause");
    return 0;
}
