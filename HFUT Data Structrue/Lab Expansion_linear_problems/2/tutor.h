#pragma once

#include "generalized_list.h"
using namespace std;

class tutor {
public:
    tutor();
    void insert_tutor();
    void insert_graduate();
    void insert_undergraduate();

    //均为头结点，不存放数据
    GLNode* Lhead1; //导师
    GLNode* Lhead2; //研究生
    GLNode* Lhead3; //本科生
    int size1 = 0, size2 = 0, size3 = 0;
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

    cout << "该导师负责研究生吗？1.负责；2.不负责";
    int w;
    cin >> w;
    GLNode* k;
    if (w == 1) {
        GLNode* s = Lhead2;
        int flag2 = size2;
        insert_graduate();
        while (flag2 >= 0) {
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
    GLNode* t = Lhead3;
    int flag3 = size3;
    while (m != 0) {
        insert_undergraduate();
        m--;
    }
    while (flag3 >= 0) {
        t = t->next;
        --flag3;
    }

    if (w == 1 && q != 0) {
        //该导师负责研究生且负责本科生
        p->num++; //导师的下一层num++
        //研究生的下一层num也要增加
        k->num += num_of_undergraduate;

        p->nextlevel = k;
        k->up = p;
        k->nextlevel = t;
        while (q != 0) {
            t->up = k;
            t = t->next;
            --q;
        }
    } else if (w == 1 && q == 0) {
        //该导师负责研究生但是不负责本科生
        p->num++;
        p->nextlevel = k;
        k->up = p;
    } else if (w == 2 && q != 0) {
        //该导师不负责研究生，但是负责本科生
        p->num += num_of_undergraduate;
        cout<<p->num<<endl<<endl;
        p->nextlevel = t;
        while (q > 0) {
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
}