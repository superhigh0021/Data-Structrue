#include <iostream>
using namespace std;
#include <stack>
#include <string>

bool judge(string const& s) {
    stack<char> S;
    bool flag=false;
    for (int i = 0; i < s.size(); ++i) {
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
                if ((S.empty()) || ('(' != S.top()))
                    flag=false;
                else if (!(S.empty()) && '(' == S.top())
                    S.pop();
                break;
            case ']':
                if ((S.empty()) || ('[' != S.top()))
                    flag=false;
                else if (!(S.empty()) && '[' == S.top())
                    S.pop();
                break;
            case '}':
                if ((S.empty()) || ('{' != S.top()))
                    {flag=false;}
                 else if (!(S.empty()) && '{' == S.top())
                    S.pop();
                break;
            default:
                break;
        }
    }
    if(S.empty()) flag=true;
    return flag;
}

int main(void) {
    string s ;
    cin>>s;
    cout << judge(s);
    system("pause");
    return 0;
}