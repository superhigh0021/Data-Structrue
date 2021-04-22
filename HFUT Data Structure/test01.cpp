#include <iostream>
using namespace std;

int main(void)
{
    int a = 3;
    int* b = &a;
    *b=6;
    cout<<a;
    system("pause");

    return 0;
}