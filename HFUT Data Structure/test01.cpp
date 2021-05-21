#include <iostream>
#include<cstdio>
using namespace std;
struct number {
    char a[4];
    char b[8];
};
int main()
{
    struct number n1, n2;
    int i;
    char c;
    scanf("%s %s%s %s", &n1.a, &n1.b, &n2.a, &n2.b);
    printf("%s",n2.a);
    system("pause");

    return 0;
}