#include "LinkedList.h"
#include "LinkedList_without_head.h"
#include <cmath>
#include <iostream>
using namespace std;

void test1()
{
    vector<int> v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 60 };
    LinkedList1<int> l1(v1, v1.size());
    for (int i = 0; i < v1.size(); ++i)
        cout << l1[i] << ' ';
    cout << endl;

    vector<int> v2 = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
    LinkedList1<int> l2(v2, v2.size());
    for (int i = 0; i < v2.size(); ++i)
        cout << l2[i] << ' ';
}

bool test21()
{
    bool flag;
    vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 15, 16, 18 };
    LinkedList2<int> l(v, v.size());
    for (int i = 0; i < v.size(); ++i) {
        if (abs(l[i] - (i + 1)) <= 3)
            flag = true;
        else {
            flag = false;
            break;
        }
    }
    return flag;
}
bool test22()
{
    bool flag;
    vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 20, 18 };
    LinkedList2<int> l(v, v.size());
    for (int i = 0; i < v.size(); ++i) {
        if (abs(l[i] - (i + 1)) <= 3)
            flag = true;
        else {
            flag = false;
            break;
        }
    }
    return flag;
}

void test31()
{
    vector<int> v1 = { 1, 3, 6, 10, 15, 16, 17, 18, 19, 20 };
    vector<int> v2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 18, 20, 30 };
    vector<int> v3, v4;
    LinkedList2<int> l1(v1, v1.size());
    LinkedList2<int> l2(v2, v2.size());
    for (int i = 0; i < v1.size(); ++i) {
        if (l2.locate(l1[i]) != NULL)
            v3.push_back(l1[i]);
    }
    for (int i = 0; i < v2.size(); ++i)
        v4.push_back(l2[i]);
    for (int i = 0; i < v1.size(); ++i) {
        if (l2.locate(l1[i]) != NULL)
            continue;
        v4.push_back(l1[i]);
    }
    for (auto i : v3)
        cout << i << ' ';
    cout << endl;
    for (auto i : v4)
        cout << i << ' ';
    cout << endl;
    LinkedList2<int> l3(v3, v3.size());
    LinkedList2<int> l4(v4, v4.size());
}

void test32()
{
    vector<int> v1 = { 1, 3, 6, 10, 15, 16, 17, 18, 19, 20 };
    vector<int> v2 = { 2, 4, 5, 7, 8, 9, 12, 22 };
    vector<int> v3, v4;
    LinkedList2<int> l1(v1, v1.size());
    LinkedList2<int> l2(v2, v2.size());
    for (int i = 0; i < v1.size(); ++i) {
        if (l2.locate(l1[i]) != NULL)
            v3.push_back(l1[i]);
    }
    for (int i = 0; i < v2.size(); ++i)
        v4.push_back(l2[i]);
    for (int i = 0; i < v1.size(); ++i) {
        if (l2.locate(l1[i]) != NULL)
            continue;
        v4.push_back(l1[i]);
    }
    for (auto i : v3)
        cout << i << ' ';
    cout << endl;
    for (auto i : v4)
        cout << i << ' ';
    cout << endl;
    LinkedList2<int> l3(v3, v3.size());
    LinkedList2<int> l4(v4, v4.size());
}

void test33()
{
    vector<int> v1;
    vector<int> v2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> v3, v4;
    LinkedList2<int> l1(v1, v1.size());
    LinkedList2<int> l2(v2, v2.size());
    for (int i = 0; i < v1.size(); ++i) {
        if (l2.locate(l1[i]) != NULL)
            v3.push_back(l1[i]);
    }
    for (int i = 0; i < v2.size(); ++i)
        v4.push_back(l2[i]);
    for (int i = 0; i < v1.size(); ++i) {
        if (l2.locate(l1[i]) != NULL)
            continue;
        v4.push_back(l1[i]);
    }
    for (auto i : v3)
        cout << i << ' ';
    cout << endl;
    for (auto i : v4)
        cout << i << ' ';
    cout << endl;
    LinkedList2<int> l3(v3, v3.size());
    LinkedList2<int> l4(v4, v4.size());
}

void test4(){
    vector<int>v1={1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int>v2={10, 30, 40, 55, 60, 70, 88, 99, 100};
    
}

int main(void)
{
    test1();
    cout<<endl<<endl;
    cout << test21() << ' ' << test22()<<endl<<endl;
    test31();
    test32();
    test33();

    system("pause");
    return 0;
}