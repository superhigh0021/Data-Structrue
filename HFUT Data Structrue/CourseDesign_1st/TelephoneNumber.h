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
    cout << "***********  ��ӭʹ�õ绰����ϵͳ **********" << endl;
    cout << "*************  0.�˳��������  *************" << endl;
    cout << "*************  1.����ְ����Ϣ  *************" << endl;
    cout << "*************  2.����ְ����Ϣ  *************" << endl;
    cout << "********************************************" << endl;
    cout << endl;
}

void TelephoneNumber::exitsystem()
{
    cout << "ȷ���˳�";
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
    cout << "����������绰������û���(����������밴#)��" << endl;
    do {
        cin >> number >> id;
        h.put(id, number);
    } while (getchar() != '#');
    cin.clear();
    cout << "����ɹ���" << endl;
    push_in_file(id,number);
    system("pause");
    system("cls");
}

void TelephoneNumber::find()
{
    cout << "��������Ҫ��ѯ���û�����";
    string s;
    cin >> s;
    if (h.get(s))
        cout << "����Ҫ��ѯ���û��ĵ绰����Ϊ��" << *h.get(s) << endl;
    else
        cout << "����Ҫ���ҵ��û������ڣ�" << endl;
    system("pause");
    system("cls");
}