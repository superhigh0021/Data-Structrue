#pragma once

#include "generalized_list.h"
using namespace std;

class tutor {
public:
    tutor();
    void showmenu();
    void insert();
    void search();
    void delete_member();
    void Delete_member(GLNode* head, string name);

    //均为头结点，不存放数据
    GLNode* Lhead1; //导师
    GLNode* Lhead2; //研究生
    GLNode* Lhead3; //本科生
private:
    int size1 = 0, size2 = 0, size3 = 0;

    void insert_tutor();
    void insert_graduate();
    void insert_undergraduate();
    void Search(GLNode* head, const string& name);
};

tutor::tutor()
{
    Lhead1 = new GLNode;
    Lhead2 = new GLNode;
    Lhead3 = new GLNode;
}

void tutor::showmenu()
{
    cout << "********************************************" << endl;
    cout << "***********  欢迎使用本科生导师系统 **********" << endl;
    cout << "*************  0.退出管理程序  *************" << endl;
    cout << "*************  1.增加人员信息  *************" << endl;
    cout << "*************  2.删除人员信息  *************" << endl;
    cout << "*************  3.查找人员信息  *************" << endl;
    cout << "********************************************" << endl;
    cout << endl;
}

void tutor::insert()
{
    system("cls");
    while (true) {
        cout << "********************************************" << endl;
        cout << "**************  增加人员信息  **************" << endl;
        cout << "**************  0.增加导师    *************" << endl;
        cout << "**************  1.增加研究生  *************" << endl;
        cout << "**************  2.增加本科生  ************" << endl;
        cout << "**************  3.退出增加系统  *************" << endl;
        cout << "********************************************" << endl;
        cout << endl;

        int i = 0;
        cout << "请输入你的选择：";
        cin >> i;
        switch (i) {
        case 0:
            insert_tutor();
            break;
        case 1:
            insert_graduate();
            break;
        case 2:
            insert_undergraduate();
            break;
        case 3:
            return;
        default:
            cout << "输入格式有误，请重新输入" << endl;
            continue;
        }
    }
}

void tutor::insert_tutor()
{
    cout << "请输入导师姓名：";
    string name;
    cin >> name;
    GLNode* p = Lhead1;
    size1++;
    int n = size1;
    while (n != 1) {
        p = p->next;
        --n;
    }
    p->next = new GLNode;
    p = p->next;
    p->name = name;
    cout << endl;
}

void tutor::insert_graduate()
{
    cout << "请输入研究生姓名：";
    string name;
    cin >> name;
    GLNode* p = Lhead2;
    size2++;
    int n = size2;
    while (n != 1) {
        p = p->next;
        --n;
    }
    p->next = new GLNode;
    p = p->next;
    p->name = name;
    cout << "该研究生的导师是谁？";
    string name_tutor;
    cin >> name_tutor;

    GLNode* t = Lhead1;
    while (t->next != nullptr) {
        t = t->next;
        if (t->name == name_tutor)
            break;
    }
    if (t->nextlevel)
        t->nextlevel->next = p;
    else
        t->nextlevel = p;
    ++t->num;
    p->up = t;
}

void tutor::insert_undergraduate()
{
    cout << "请输入本科生姓名：";
    string name;
    cin >> name;
    GLNode* p = Lhead3;
    size3++;
    int n = size3;
    while (n != 1) {
        p = p->next;
        --n;
    }
    p->next = new GLNode;
    p = p->next;
    p->name = name;
    cout << "他是 1.由导师负责  2.由研究生负责";
    int flag;
    cin>>flag;
    if (flag == 1) {
        //他直接由导师负责
        string name_tutor;
        cout << "他的导师的姓名是：";
        cin >> name_tutor;
        GLNode* t = Lhead1;
        while (t->next != nullptr) {
            t = t->next;
            if (t->name == name_tutor)
                break;
        }
        ++t->num;
        if (t->nextlevel)
            t->nextlevel->next = p;
        else
            t->nextlevel = p;
        ++t->num;
        p->up = t;
    } else if (flag == 2) {
        //由研究生负责
        string name_graduate;
        cout << "请输入负责他的研究生的姓名:";
        cin >> name_graduate;
        GLNode* t = Lhead2;
        while (t->next != nullptr) {
            t = t->next;
            if (t->name == name_graduate)
                break;
            if (t->nextlevel)
                t->nextlevel->next = p;
            else
                t->nextlevel = p;
            ++t->num;
            p->up = t;
        }
    }
}

//不同身份传入每一层对应的头结点
void tutor::Search(GLNode* head, const string& name)
{
    GLNode* p = head;
    while (p->next != nullptr) {
        p = p->next;
        if (p->name == name) {
            cout << "查找成功！" << endl;
            if (head == Lhead1) {
                //导师

                cout << "该人为导师,";
                if (p->nextlevel->nextlevel) {
                    //说明他带了研究生
                    p = p->nextlevel;
                    cout << "他负责的研究生是" << p->name << endl;
                }
                cout << endl;
            } else if (head == Lhead2) {
                //研究生
                cout << "该人为研究生" << endl
                     << "他的导师是：";
                cout << p->up->name << endl;
                if (p->nextlevel != nullptr) {
                    cout << "他负责的本科生:";
                    p = p->nextlevel;
                    cout << p->name << ' ';
                    while (p->next != nullptr) {
                        p = p->next;
                        cout << p->name << ' ';
                    }
                    cout << endl;
                } else
                    cout << "他的导师不带本科生" << endl;
            } else if (head == Lhead3) {
                //本科生
                if (p->up->up == nullptr)
                    //说明没有所属的导师没有研究生
                    cout << "他的导师是：" << p->up->name << endl;
                else {
                    cout << "他的导师是：" << p->up->up->name << endl
                         << "负责他的研究生是：" << p->up->name << endl;
                }
            }
            system("pause");
            return;
        }
    }
    cout << "该人不存在" << endl;
    system("pause");
    return;
}

//调用主函数Search
void tutor::search()
{
    cout << "请输入你要搜索的人的身份1.导师 2.研究生 3.本科生";
    string name;
    int id;
    cin >> id;
    cout << "请输入他的姓名：";
    cin >> name;
    switch (id) {
    case 1:
        Search(Lhead1, name);
        break;
    case 2:
        Search(Lhead2, name);
        break;
    case 3:
        Search(Lhead3, name);
        break;
    }
}

void tutor::delete_member()
{
    cout << "请输入你要删除的人的身份1.研究生 2.本科生";
    string name;
    int id;
    cin >> id;
    cout << "请输入他的姓名：";
    cin >> name;
    switch (id) {
    case 1:
        Delete_member(Lhead2, name);
        break;
    case 2:
        Delete_member(Lhead3, name);
        break;
    }
}

void tutor::Delete_member(GLNode* head, string name)
{
    GLNode* p = head;
    while (p->next != nullptr) {
        p = p->next;
        if (p->name == name) {
            //定位到那个节点了！
            if (head == Lhead2) {
                //要删除研究生
                p->up->nextlevel = p->nextlevel;
                p->nextlevel->up = p->up;
                p->up->num = p->num;
            } else if (head = Lhead3) {
                //要删除本科生
                if (p->up->up == nullptr) {
                    //没有研究生，导师直接带本科生
                    p->up->nextlevel = nullptr;
                    p->num = 0;
                } else {
                    //导师带了研究生
                    p->up->nextlevel = nullptr;
                    p->up->num = 0;
                }
            }
        }
    }
    cout << "删除成功！" << endl;
    system("pause");
}
