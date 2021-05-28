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
    cout << "*********  ��ӭʹ�õ绰����ϵͳ **********" << endl;
    cout << "*************  0.�˳��������  *************" << endl;
    cout << "*************  1.����ְ����Ϣ  *************" << endl;
    cout << "*************  2.����ְ����Ϣ  *************" << endl;
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
    cout << "����������绰������û���(����������밴#)��" << endl;
    do
    {
        cin >> number >> id;
        h.put(id, number);
    } while (getchar() != '#');
    cin.clear();
    cout << "����ɹ���" << endl;
    system("pause");
    system("cls");
}

void TelephoneNumber::find(){
    cout<<"��������Ҫ��ѯ���û�����";
    string s;
    cin>>s;
    if(h.get(s))
    cout<<"����Ҫ��ѯ���û��ĵ绰����Ϊ��"<<*h.get(s)<<endl;
    else cout<<"����Ҫ���ҵ��û������ڣ�"<<endl;
    system("pause");
    system("cls");
}