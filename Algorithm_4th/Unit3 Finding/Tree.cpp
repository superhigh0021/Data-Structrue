#include <iostream>
using namespace std;

#include "Tree.h"

int main(void)
{
    Binary_Tree<int, int> s;
    s.put(1, 1);
    s.put(2, 12);
    cout <<s.get(2);

    system("pause");
    return 0;
}