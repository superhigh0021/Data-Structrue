#include <iostream>
using namespace std;
#include "hashtable.h"

class TelephoneNumber
{
public:
    void showmenu();
    void exitsystem();
    void push();
    void find();
private:
    Hashtable<string, long long> h;
};

void TelephoneNumber::showmenu()
{
    cout << "********************************************" << endl;
    cout << "*********  欢迎使用电话号码系统 **********" << endl;
    cout << "*************  0.退出管理程序  *************" << endl;
    cout << "*************  1.增加职工信息  *************" << endl;
    cout << "*************  2.查找职工信息  *************" << endl;
    cout << "********************************************" << endl;
    cout << endl;
}

void TelephoneNumber::exitsystem()
{
    system("pause");
    exit(0);
}

void TelephoneNumber::push()
{
    string id;
    long long number;
    cout << "请依次输入电话号码和用户名(若输入完毕请按#)：" << endl;
    do
    {
        cin >> number >> id;
        h.put(id, number);
    } while (getchar() != '#');
    cin.clear();
    cout << "插入成功！" << endl;
    system("pause");
    system("cls");
}

void TelephoneNumber::find(){
    cout<<"请输入你要查询的用户名：";
    string s;
    cin>>s;
    if(h.get(s))
    cout<<"您所要查询的用户的电话号码为："<<*h.get(s)<<endl;
    else cout<<"您索要查找的用户不存在！"<<endl;
    system("pause");
    system("cls");
}