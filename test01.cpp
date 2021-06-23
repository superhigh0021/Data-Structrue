#include <iostream>
using namespace std;
#include <vector>
#include <ctime>

int main(void)
{
    clock_t start, end;
    start = clock();
    for (int i = 0; i < 1000000; ++i)
        int *t = new int;

    end=clock();

    cout<<end-start;

    system("pause");

    return 0;
}