#include "List.h"
#include <iostream>
using namespace std;

template <typename T>
void Union(List<T>& l1, List<T>& l2)
{
    cout<<"交集：";
    cout << "{";
    for (int i = 0; i < l1.size(); ++i) {
        if (l2.locate(l1.get_element(i)) != -1)
            cout << l1.get_element(i) << ' ';
    }
    cout << "}" << endl;
}

template <typename T>
void Intersection(List<T>& l1, List<T>& l2)
{
    cout<<"并集：";
    cout << "{";
    for (int i = 0; i < l1.size(); ++i) {
        if (l2.locate(l1.get_element(i)) != -1)
            l1.Delete(i);
    }
    l1.PrintTest();l2.PrintTest();
    cout<<"}"<<endl;
}

int main(void)
{
    int a[] = { 1, 3, 5, 7 };
    int b[] = { 2, 5, 8, 6 };
    List<int> l1(a, 4), l2(b, 4);
    Union(l1, l2);
    Intersection(l1,l2);

    system("pause");
    return 0;
}