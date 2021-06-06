#pragma once

#include "generalized_list.h"
using namespace std;

class tutor {
public:
    tutor();
    void showmenu();
    void insert_tutor();
    void search();
    void delete_member();
    void Delete_member(GLNode* head, string name);

    //��Ϊͷ��㣬���������
    GLNode* Lhead1; //��ʦ
    GLNode* Lhead2; //�о���
    GLNode* Lhead3; //������
private:
    int size1 = 0, size2 = 0, size3 = 0;

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
    cout << "***********  ��ӭʹ�ñ�������ʦϵͳ **********" << endl;
    cout << "*************  0.�˳��������  *************" << endl;
    cout << "*************  1.������Ա��Ϣ  *************" << endl;
    cout << "*************  2.ɾ����Ա��Ϣ  *************" << endl;
    cout << "*************  3.������Ա��Ϣ  *************" << endl;
    cout << "********************************************" << endl;
    cout << endl;
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

//��ͬ��ݴ���ÿһ���Ӧ��ͷ���
void tutor::Search(GLNode* head, const string& name)
{
    GLNode* p = head;
    while (p->next != nullptr) {
        p = p->next;
        if (p->name == name) {
            cout << "���ҳɹ���" << endl;
            if (head == Lhead1) {
                //��ʦ

                cout << "����Ϊ��ʦ,";
                if (p->num == 1) {
                    //˵���������о���
                    p = p->nextlevel;
                    cout << "��������о�����" << p->name << endl;
                }
                p = p->nextlevel;
                cout << "������ı������У�" << p->name << ' ';
                while (p->next != nullptr) {
                    p = p->next;
                    cout << p->name << ' ';
                }
            } else if (head == Lhead2) {
                //�о���
                cout << "����Ϊ�о���" << endl
                     << "���ĵ�ʦ�ǣ�";
                cout << p->up->name << endl;
                if (p->nextlevel != nullptr) {
                    cout << "�������ĵ�ʦ�ı�����:";
                    p = p->nextlevel;
                    cout << p->name << ' ';
                    while (p->next != nullptr) {
                        p = p->next;
                        cout << p->name << ' ';
                    }
                } else
                    cout << "���ĵ�ʦ����������" << endl;
            } else if (head == Lhead3) {
                //������
                if (p->up->up == nullptr)
                    //˵��û�������ĵ�ʦû���о���
                    cout << "���ĵ�ʦ�ǣ�" << p->up->name << endl;
                else {
                    cout << "���ĵ�ʦ�ǣ�" << p->up->up->name << endl
                         << "���������о����ǣ�" << p->up->name << endl;
                }
            }
            system("pause");
            return;
        }
    }
    cout << "���˲�����" << endl;
    system("pause");
    return;
}

//����������Search
void tutor::search()
{
    cout << "��������Ҫ�������˵����1.��ʦ 2.�о��� 3.������";
    string name;
    int id;
    cin >> id;
    cout << "����������������";
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
    cout << "��������Ҫɾ�����˵����1.�о��� 2.������";
    string name;
    int id;
    cin >> id;
    cout << "����������������";
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
            //��λ���Ǹ��ڵ��ˣ�
            if (head == Lhead2) {
                //Ҫɾ���о���
                p->up->nextlevel = p->nextlevel;
                p->nextlevel->up = p->up;
                p->up->num = p->num;
            } else if (head = Lhead3) {
                //Ҫɾ��������
                if (p->up->up == nullptr) {
                    //û���о�������ʦֱ�Ӵ�������
                    p->up->nextlevel = nullptr;
                    p->num = 0;
                } else {
                    //��ʦ�����о���
                    p->up->nextlevel = nullptr;
                    p->up->num = 0;
                }
            }
        }
    }
    cout<<"ɾ���ɹ���"<<endl;
    system("pause");
}
