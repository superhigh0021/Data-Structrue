#include <iostream>
#include "List.h"
using namespace std;

int main(void)
{
    int A[] = {1, 3, 7, 10, 23};
    int B[] = {2, 3, 9, 14, 23};
    List<int> l1(A, 5), l2(B, 5);
    l1.MinusSet(l2);
    l1.PrintTest();

    system("pause");
    return 0;
}