#pragma once

#include "generalized_list.h"
using namespace std;

class tutor {
public:
    tutor();
    void insert_tutor();
    void insert_graduate();
    void insert_undergraduate();

    //��Ϊͷ��㣬���������
    GLNode* Lhead1; //��ʦ
    GLNode* Lhead2; //�о���
    GLNode* Lhead3; //������
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
    cout << "�����뵼ʦ������";
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

    cout << "�õ�ʦ�����о�����1.����2.������";
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
        } //�ò�����ָ��ָ����һ���о�����ʼ
        k = s;
    }

    cout << "�õ�ʦ���𼸸���������";
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
        //�õ�ʦ�����о����Ҹ��𱾿���
        p->num++; //��ʦ����һ��num++
        //�о�������һ��numҲҪ����
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
        //�õ�ʦ�����о������ǲ����𱾿���
        p->num++;
        p->nextlevel = k;
        k->up = p;
    } else if (w == 2 && q != 0) {
        //�õ�ʦ�������о��������Ǹ��𱾿���
        p->num += num_of_undergraduate;
        cout<<p->num<<endl<<endl;
        p->nextlevel = t;
        while (q > 0) {
            t->up = p;
            t = t->next;
            --q;
        }
    }
    //cout<<Lhead1->next->next->nextlevel->num;//��������ʱע��
}

void tutor::insert_graduate()
{
    cout << "�������о���������";
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
    cout << "�����뱾����������";
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