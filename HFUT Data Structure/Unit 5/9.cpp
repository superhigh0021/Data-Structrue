#include <iostream>
#include <string>
using namespace std;

int Mystrcmp(string s1, string s2)
{
    for (int i = 0; i < s1.size() || i < s2.size();) {
        if (s1[i] == s2[i])
            i++;
        else if (s1[i] > s2[i])
            return 1;
        else
            return -1;
    }
    return 0; //循环结束意味着两个字符串的数值大小相同
}

int main(void)
{
    string s1("ac");
    string s2("abd");
    cout << Mystrcmp(s1, s2);

    system("pause");
    return 0;
}