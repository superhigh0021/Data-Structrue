#pragma once

#include <fstream>
using namespace std;
#include "hashtable.h"

class TelephoneNumber {
public:
    TelephoneNumber();
    void showmenu();
    void exitsystem();
    void push();
    void find();

private:
    Hashtable<string, long long> h;
};

TelephoneNumber::TelephoneNumber()
{
    fstream txtfile("E:/Data-Structrue/HFUT Data Structrue/CourseDesign_1st/telephone_number.txt");
    string id;
    long long number;
    char flag;
    txtfile >> flag;
    do {
        txtfile >> number >> id;
        h.put(id, number);
        txtfile >> flag;
    } while (flag == '#');
    txtfile.clear();
    txtfile.close();
}

void TelephoneNumber::showmenu()
{
    cout << "********************************************" << endl;
    cout << "***********  欢迎使用电话号码系统 **********" << endl;
    cout << "*************  0.退出管理程序  *************" << endl;
    cout << "*************  1.增加职工信息  *************" << endl;
    cout << "*************  2.查找职工信息  *************" << endl;
    cout << "********************************************" << endl;
    cout << endl;
}

void TelephoneNumber::exitsystem()
{
    cout << "确认退出";
    system("pause");
    exit(0);
}

void push_in_file(const string& id, long long number)
{
    fstream txtfile("E:/Data-Structrue/HFUT Data Structrue/CourseDesign_1st`/telephone_number.txt",ios::app);
    char deletechar;
    txtfile >> deletechar;
    txtfile << '#' << number << ' ' << id << endl<<'%';
    txtfile.close();
}

void TelephoneNumber::push()
{
    string id;
    long long number;
    cout << "请依次输入电话号码和用户名(若输入完毕请按#)：" << endl;
    do {
        cin >> number >> id;
        h.put(id, number);
    } while (getchar() != '#');
    cin.clear();
    cout << "插入成功！" << endl;
    push_in_file(id,number);
    system("pause");
    system("cls");
}

void TelephoneNumber::find()
{
    cout << "请输入你要查询的用户名：";
    string s;
    cin >> s;
    if (h.get(s))
        cout << "您所要查询的用户的电话号码为：" << *h.get(s) << endl;
    else
        cout << "您索要查找的用户不存在！" << endl;
    system("pause");
    system("cls");
}