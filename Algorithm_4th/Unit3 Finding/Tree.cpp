#include <iostream>
using namespace std;

#include "Tree.h"

int main(void)
{
    BST<int, int> s;
    s.put(1, 1);
    s.put(2, 12);
    s.put(3, 123);
    s.put(4, 1234);
    s.put(5, 12345);
    cout << s.get(2) << ' ' << s.get(5) << endl;
    s.Delete(4);
    cout<<s.get(3);

    system("pause");
    return 0;
}