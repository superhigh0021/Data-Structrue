#pragma once

#include "generalized_list.h"
using namespace std;

class tutor
{
public:
    tutor();
    void insert_tutor();
    void search();

    //均为头结点，不存放数据
    GLNode *Lhead1; //导师
    GLNode *Lhead2; //研究生
    GLNode *Lhead3; //本科生
    int size1 = 0, size2 = 0, size3 = 0;

    void insert_graduate();
    void insert_undergraduate();
    void Search(GLNode *head, const string &name);
};

tutor::tutor()
{
    Lhead1 = new GLNode;
    Lhead2 = new GLNode;
    Lhead3 = new GLNode;
}

void tutor::insert_tutor()
{
    cout << "请输入导师姓名：";
    string name;
    cin >> name;
    GLNode *p = Lhead1;
    size1++;
    int n = size1;
    while (n != 1)
    {
        p = p->next;
        --n;
    }
    p->next = new GLNode;
    p = p->next;
    p->name = name;
    cout << endl;

    cout << "该导师负责研究生吗？1.负责；2.不负责";
    int w;
    cin >> w;
    GLNode *k;
    if (w == 1)
    {
        GLNode *s = Lhead2;
        int flag2 = size2;
        insert_graduate();
        while (flag2 >= 0)
        {
            s = s->next;
            --flag2;
        } //该操作将指针指向下一个研究生开始
        k = s;
    }

    cout << "该导师负责几个本科生？";
    int num_of_undergraduate;
    cin >> num_of_undergraduate;
    int m = num_of_undergraduate;
    int q = m;
    GLNode *t = Lhead3;
    int flag3 = size3;
    while (m != 0)
    {
        insert_undergraduate();
        m--;
    }
    while (flag3 >= 0)
    {
        t = t->next;
        --flag3;
    }

    if (w == 1 && q != 0)
    {
        //该导师负责研究生且负责本科生
        p->num++; //导师的下一层num++
        //研究生的下一层num也要增加
        k->num += num_of_undergraduate;

        p->nextlevel = k;
        k->up = p;
        k->nextlevel = t;
        while (q != 0)
        {
            t->up = k;
            t = t->next;
            --q;
        }
    }
    else if (w == 1 && q == 0)
    {
        //该导师负责研究生但是不负责本科生
        p->num++;
        p->nextlevel = k;
        k->up = p;
    }
    else if (w == 2 && q != 0)
    {
        //该导师不负责研究生，但是负责本科生
        p->num += num_of_undergraduate;
        p->nextlevel = t;
        while (q > 0)
        {
            t->up = p;
            t = t->next;
            --q;
        }
    }
    //cout<<Lhead1->next->next->nextlevel->num;//测试用随时注释
}

void tutor::insert_graduate()
{
    cout << "请输入研究生姓名：";
    string name;
    cin >> name;
    GLNode *p = Lhead2;
    size2++;
    int n = size2;
    while (n != 1)
    {
        p = p->next;
        --n;
    }
    p->next = new GLNode;
    p = p->next;
    p->name = name;
}

void tutor::insert_undergraduate()
{
    cout << "请输入本科生姓名：";
    string name;
    cin >> name;
    GLNode *p = Lhead3;
    size3++;
    int n = size3;
    while (n != 1)
    {
        p = p->next;
        --n;
    }
    p->next = new GLNode;
    p = p->next;
    p->name = name;
}

//不同身份传入每一层对应的头结点
void tutor::Search(GLNode *head, const string &name)
{
    GLNode *p = head;
    while (p->next != nullptr)
    {
        p = p->next;
        if (p->name == name)
        {
            cout << "查找成功！";
            if (head == Lhead1)
            {
                //导师

                cout<<"该人为导师";
                if(p->nextlevel->nextlevel==nullptr)
            }
            else if (head == Lhead2)
            {
                //研究生
                cout << "该人为研究生" << endl
                     << "他的导师是：";
                cout << p->up->name << endl;
                if (p->nextlevel != nullptr)
                {
                    cout << "他负责他的导师的本科生:";
                    p = p->nextlevel;
                    cout << p->name << ' ';
                    while (p->next != nullptr)
                    {
                        p = p->next;
                        cout << p->name << ' ';
                    }
                }
                else
                    cout << "他的导师不带本科生" << endl;
            }
            else if (head == Lhead3)
            {
                //本科生
                if (p->up->up == nullptr)
                    //说明没有所属的导师没有研究生
                    cout << "他的导师是：" << p->up->name << endl;
                else
                {
                    cout << "他的导师是：" << p->up->up->name << endl
                         << "负责他的研究生是：" << p->up->name << endl;
                }
            }
            return;
        }
    }
    cout << "该人不存在" << endl;
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
    switch (id)
    {
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
