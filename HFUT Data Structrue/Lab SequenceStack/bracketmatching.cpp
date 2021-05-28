#include"AutoSequenceStack.h"
#include<iostream>
using namespace std;

bool isValid(string s)
{
    bool flag = false;
    SequenceStack<char> S;
    for (int i = 0; i < s.size(); ++i) {
        flag = false;
        switch (s[i]) {
        case '(':
            S.push(s[i]);
            break;
        case '[':
            S.push(s[i]);
            break;
        case '{':
            S.push(s[i]);
            break;
        case ')':
            if (S.empty())
                return flag;
            if (S.get_top() == '(') {
                flag = true;
                S.pop();
            } else
                return flag;
            break;
        case ']':
            if (S.empty())
                return flag;
            if (S.get_top() == '[') {
                flag = true;
                S.pop();
            } else
                return flag;
            break;
        case '}':
            if (S.empty())
                return flag;
            if (S.get_top() == '{') {
                flag = true;
                S.pop();
            } else
                return flag;
            break;
        default:
            break;
        }
    }
    if (!S.empty())
        return false;
    return flag;
}

int main(void){
    string s;
    cin>>s;
    cout<<isValid(s);

    system("pause");
    return 0;
}