#include <iostream>
#include "LinkedList.h"
#include <vector>
using namespace std;

template <typename T>
void delete01(LinkedList<T> &l)
{
    l.delete_element(4);
    l.PrintTest();
    cout << endl;
    l.delete_element(9);
    l.PrintTest();
    cout << endl;
    l.delete_element(1);
    l.PrintTest();
    cout << endl;
    l.delete_element(10);
    l.PrintTest();
    cout << endl;
    l.delete_element(-1);
    l.PrintTest();
    cout << endl;
}

template<typename T>
void delete02(LinkedList<T>&l){
    l.delete_element(5);
}

int main(void)
{
    vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    LinkedList<int> l1(v1, v1.size());
    delete01(l1);
    cout<<endl;
    
    LinkedList<int>l2;
    delete02(l2);

    system("pause");
    return 0;
}