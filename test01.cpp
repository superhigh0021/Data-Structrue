#include <iostream>
using namespace std;
#include <stack>

int main(void)
{
    double r=0, f=1;
    int i;
    for(i = 1; i <= 100; i ++)
    {
        f*=i;//i!
        r+=f;
    }
    cout<<r;

    system("pause");
    return 0;
}