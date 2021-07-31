#include "LinkedList.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int Mystrcmp(LinkedList<char> l1, LinkedList<char> l2)
{
    for (int i = 0; i < l1.size() || i < l2.size();) {
        if (l1[i] == l2[i])
            i++;
        else if (l1[i] > l2[i])
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
    vector<char> v1;
    vector<char> v2;
    for (int i = 0; i < s1.size(); ++i)
        v1.push_back(s1[i]);
    for (int i = 0; i < s2.size(); ++i)
        v2.push_back(s2[i]);
    LinkedList<char> l1(v1, v1.size());
    LinkedList<char> l2(v2, v2.size());
    cout<<Mystrcmp(l1,l2);
    system("pause");
    return 0;
}