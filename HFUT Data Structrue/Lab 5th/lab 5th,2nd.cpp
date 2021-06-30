#include <fstream>
#include <iostream>
using namespace std;
ifstream forest; //����ȫ�ֵ��������ļ�
struct bnode {
    char data;
    bnode* firstchild;
    bnode* nextbrother;
};
void filecreat(bnode*& T)
{
    char num;
    forest >> num;
    if (num == '#')
        T = NULL;
    else {
        T = new bnode;
        T->data = num;
        filecreat(T->firstchild);
        filecreat(T->nextbrother);
    }
}
void cmdcreat(bnode*& T)
{
    char num;
    cin >> num;
    if (num == '#')
        T = NULL;
    else {
        T = new bnode;
        T->data = num;
        cout << T->data << "����(#����):";
        cmdcreat(T->firstchild);
        cout << T->data << "���ֵ�(#����):";
        cmdcreat(T->nextbrother);
    }
}
void creattree(bnode T[], int n)
{
    for (int i = 0; i < n; i++) {
        if (i + 1 < n)
            T[i].nextbrother = &T[i + 1];
    }
}
void Preorder(bnode*& T)
{
    if (T != NULL) {
        Preorder(T->firstchild);
        cout << T->data;
        Preorder(T->nextbrother);
    }
}
void Inorder(bnode*& T)
{
    if (T != NULL) {
        Inorder(T->firstchild);
        cout << T->data;
        Inorder(T->nextbrother);
    }
}
void Postorder(bnode*& T)
{
    if (T != NULL) {
        Postorder(T->firstchild);
        cout << T->data;
        Postorder(T->nextbrother);
    }
}

int main()
{
    int i = 0;
    int n = 0; //nΪ���ĸ���
    cout << "����һ��ɭ��ϵͳ ��Ҫ���ɼ�����";
    cin >> n;
    bnode* B = new bnode[n]; //�����洢ÿ�����ĸ��ڵ�
    int num = 0; //��¼��ǰ�ǵڼ�����
    while (1) {
        cout << "������������������1   ���ļ�����������2   �������ɭ������3   ";
        cout << "ǰ���������4   �����������5   �����������6   ��������0" << endl;
        cin >> i;
        if (i == 0)
            break;
        if (i == 1) {
            bnode* T = NULL;
            cout << "������ڵ�";
            cmdcreat(T);
            *(B + num) = *T;
            num++;
        }
        if (i == 2) {
            forest.open("E:\\Data-Structrue\\HFUT Data Structrue\\Lab 5th\\forest1.txt", ios::in);
            bnode* T1 = NULL;
            filecreat(T1);
            *(B + num) = *T1;
            num++;
            forest.close();
            forest.open("E:\\Data-Structrue\\HFUT Data Structrue\\Lab 5th\\forest2.txt", ios::in);
            bnode* T2 = NULL;
            filecreat(T2);
            *(B + num) = *T2;
            num++;
            forest.close();
            forest.open("E:\\Data-Structrue\\HFUT Data Structrue\\Lab 5th\\forest3.txt", ios::in);
            bnode* T3 = NULL;
            filecreat(T3);
            *(B + num) = *T3;
            num++;
            forest.close();
            if (i == 3)
                creattree(B, n);
            if (i == 4)
                Preorder(B);
            if (i == 5)
                Inorder(B);
            if (i == 6)
                Postorder(B);
        }
    }
    system("pause");
    return 0;
}
