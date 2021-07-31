#include <iostream>
#include "List.h"
using namespace std;

int main(void)
{
    int a[] = {1, 5, 7, 16, 38, 77, 98, 132, 229};
    List<int> l(a,9);
    l.SortInsert(32);
    l.PrintTest();

    system("pause");
    return 0;
}