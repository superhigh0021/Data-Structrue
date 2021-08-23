#include <iostream>
#include <cstring>
using namespace std;


int main(void)
{
    char s[] = "abcdefg";
    char *t = s + strlen(s);
    if ("a" > t)
        cout << "yes!" << endl;
    else
        cout << "no!" << endl;

    system("pause");
    return 0;
}