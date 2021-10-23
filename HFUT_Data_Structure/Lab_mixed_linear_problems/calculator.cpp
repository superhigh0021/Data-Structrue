/* 设计计算器系统，能对包含四则运算及括号的表达式计算其结果 */
#include <iostream>
#include <stack>
using namespace std; 
char Compare(char a, char b)
{
    int i, j;
    char Table[9][8] = {
        {' ', '+', '-', '*', '/', '(', ')', '='},
        {'+', '>', '>', '<', '<', '<', '>', '>'},
        {'-', '>', '>', '<', '<', '<', '>', '>'},
        {'*', '>', '>', '>', '>', '<', '>', '>'},
        {'/', '>', '>', '>', '>', '<', '>', '>'},
        {'(', '<', '<', '<', '<', '<', '=', ' '},
        {')', '>', '>', '>', '>', ' ', '>', '>'},
        {'=', '<', '<', '<', '<', '<', ' ', '='},
        {'\0', '<', '<', '<', '<', '<', ' ', '='}}; //优先级表格
    for (i = 0; i < 8; i++)
        if (Table[0][i] == a) //横坐标寻找，当前
            break;
    for (j = 0; j < 9; j++) //纵坐标寻找,栈顶
        if (Table[j][0] == b)
            break;
    return Table[j][i];
}
bool issymbol(const char &c)
{
    char ptr[8] = {'+', '-', '*', '/', '(', ')', '='};
    for (int i = 0; i < 7; ++i)
    {
        if (c == ptr[i])
            return 1;
    }
    return 0;
}
int Execute(int a, char op, int b)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    }
}

int main(void)
{
    string s;
    cin >> s;
    stack<char> sym;
    sym.push('=');
    stack<int> num;
    int i = 0, sum = 0, lvalue = 0, rvalue = 0, flag = 0, count = 0;
    char oper;
    while (i < s.size())
    {
        if (!issymbol(s[i]))
        {
            if (i > 1 && issymbol(s[i - 1]))
                sum = 0;
            sum = sum * 10 + (s[i++] - 48);
        }
        if (issymbol(s[i]))
        {
            if (!issymbol(s[i - 1]))
                if (flag == 0)
                    num.push(sum);
            switch (Compare(s[i], sym.top()))
            {
            case '<':
                sym.push(s[i++]);
                flag = 0;
                break;
            case '=':
                sym.pop();
                ++i;
                flag = 1;
                break;
            case '>':
                lvalue = num.top();
                num.pop();
                rvalue = num.top();
                num.pop();
                oper = sym.top();
                sym.pop();
                num.push(Execute(rvalue, oper, lvalue));
                flag = 1;
                break;
            }
        }
    }
    cout << num.top() << endl;
    system("pause");
    return 0;
}