#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;
#define maxSize 100

#define CSTree CSNode*

//���Ľ�㶨�壨����-�ֵ�����)
class CSNode {
public:
    char data;
    CSNode *firstchild, *nextsibling;
    CSNode(char data)
        : data(data)
    {
    }
};

//���������Ķ���
class BTNode {
public:
    char data;
    BTNode* lchild;
    BTNode* rchild;
};

//ɭ�ֵĶ���
typedef struct
{
    CSTree ct[maxSize]; //ֻ�����ͨ��������ͷ���ȫ���ŵ�ɭ���е����鼴��
    int num; //ɭ�������Ŀ���
} Forest;

//�洢·������
typedef struct
{
    char path[100];
} Str;

//����һ����
//���������������ÿ����һ��Ҷ�ӽڵ�ͼ�һ��0��������������ٶ������0�������������������һ��
CSTree CreateCSTree(string& str, int length, int& index)
{
    if (index < length) {
        char ch = str[index];
        CSTree CT = NULL;
        if (ch != '#') {
            CT = new CSNode(ch);
            CT->firstchild = CreateCSTree(str, length, ++index);
            CT->nextsibling = CreateCSTree(str, length, ++index);
        }
        return CT;
    }
}

//��ת���ɶ�������ʵ�ܼ򵥣����ǽ���������������һ��
//�������ֵܺͶ��������Һ���ֱ�ӽ���data����
//��Ϊ�����洢��ʱ����ʵ���õķ�ʽҲ��һ���ģ����Ǻ����ֵ�����
BTNode* ExchangeToBTree(CSTree ct)
{
    if (ct == NULL)
        return NULL;
    else {
        BTNode* bt = new BTNode;
        bt->data = ct->data;
        bt->lchild = ExchangeToBTree(ct->firstchild);
        bt->rchild = ExchangeToBTree(ct->nextsibling);
        return bt;
    }
}
//������ת������ͨ��
CSTree ExchangeToCSTree(BTNode* bt)
{
    if (bt == NULL)
        return NULL;
    else {
        CSTree ct = (CSNode*)malloc(sizeof(CSNode));
        ct->data = bt->data;
        ct->firstchild = ExchangeToCSTree(bt->lchild);
        ct->nextsibling = ExchangeToCSTree(bt->rchild);
        return ct;
    }
}
//ɭ��ת������
BTNode* ForestToBTree(CSTree F[], int low, int high)
{
    //lowΪ��ǰָ�������highΪ��n�������±�n-1
    if (low > high)
        return NULL;
    else {
        //�������ĸ���Ϊ��һ�����ĸ���ͬʱ�������������ǵ�һ�������ڵ������ɭ��ת���ɵĶ�����
        BTNode* root = ExchangeToBTree(F[low]);
        root->rchild = ForestToBTree(F, low + 1, high); //����������������ɭ��������ת���ɵĶ�����
        return root;
    }
}
//������תɭ��
Forest* BTreeToForest(BTNode* root)
{
    BTNode* p = root;

    //ɭ�ֳ�ʼ��
    Forest* F = (Forest*)malloc(sizeof(Forest));
    BTNode* q = NULL;
    int i = 0; //ͳ�����ĸ���
    //��������ת��Ϊɭ�֣����Ĵ���
    while (p != NULL) {
        q = p->rchild; //����qָ����һ�����ĸ��ڵ�
        p->rchild = NULL; //����ǰ���Һ��ӵĶ��������Һ������ӶϿ�
        F->ct[i++] = ExchangeToCSTree(p); //��������ת��Ϊ��
        p = q; //��pָ����һ����
    }
    F->num = i;
    return F;
}
//�������������
void preorder(BTNode* bt)
{
    if (bt != NULL) {
        cout << bt->data << "  ";
        preorder(bt->lchild);
        preorder(bt->rchild);
    }
}

//�������������
void inorder(BTNode* bt)
{
    if (bt != NULL) {
        inorder(bt->lchild);
        cout << bt->data << "  ";
        inorder(bt->rchild);
    }
}

//��ͨ���������������
void preorder_cstree(CSTree ct)
{
    if (ct != NULL) {
        cout << ct->data << "  ";
        preorder_cstree(ct->firstchild);
        preorder_cstree(ct->nextsibling);
    }
}

//��ͨ���ĺ������=���������������
void inorder_cstree(CSTree ct)
{
    if (ct != NULL) {
        inorder_cstree(ct->firstchild);
        cout << ct->data << "  ";
        inorder_cstree(ct->nextsibling);
    }
}

//ɭ���ȸ�����
void preorder_forest(Forest* f)
{
    int i;
    for (i = 0; i < f->num; ++i)
        preorder_cstree(f->ct[i]);
}

//ɭ�ֺ������
void inorder_forest(Forest* f)
{
    int i;
    for (i = 0; i < f->num; ++i)
        inorder_cstree(f->ct[i]);
}
//�����ǶԴ���������ת��������������ת���Ĵ������
void test_01()
{
    ifstream ifs("E:\\FileRecv\\cstree.txt");
    string str;
    while (!ifs.eof()) {
        getline(ifs, str);
    }
    int a = 0;
    //����һ����ͨ�ĳ�����
    CSTree ct = CreateCSTree(str, str.length(), a);
    cout << "���������������Ϊ: ";
    preorder_cstree(ct);
    cout << endl;
    //��ͨ��תΪ������
    BTNode* bt = ExchangeToBTree(ct);
    cout << "��ͨ��תΪ�Ķ������������������Ϊ: ";
    preorder(bt);
    cout << endl;
    cout << "��ͨ��תΪ�Ķ������������������Ϊ: ";
    inorder(bt);
    cout << endl;
    //������תΪ��ͨ��
    CSTree ct2 = ExchangeToCSTree(bt);
    cout << "������תΪ��ͨ���������������Ϊ��";
    preorder_cstree(ct2);
    cout << endl;
}
//��������ɭ�ֵĴ�����ɭ��ת��������������תɭ��
void test_02()
{
    //����һ��ɭ��
    CSTree F[3];
    //���������ļ���·��
    Str ps[3] = { "E:\\FileRecv\\cstree1.txt", "E:\\FileRecv\\cstree2.txt", "E:\\FileRecv\\cstree3.txt" };
    int length = 3;
    string* arr = new string[3];
    //���ļ��ж�ȡ�����ַ���
    for (int i = 0; i < length; i++) {
        ifstream ifs(ps[i].path);
        getline(ifs, arr[i]);
        int a = 0;
        F[i] = CreateCSTree(arr[i], arr[i].length(), a);
    }
    //ɭ��ת������
    BTNode* bt = ForestToBTree(F, 0, length - 1);
    cout << "ɭ��תΪ�Ķ������������������Ϊ�� ";
    inorder(bt);
    cout << endl;
    //������תɭ��
    Forest* F2;
    F2 = BTreeToForest(bt);
    cout << "�������ɭ�ֵĽ��Ϊ:  ";
    inorder_forest(F2);
    cout << endl;
    cout << "�������ɭ�ֵĽ��Ϊ: ";
    preorder_forest(F2);
    cout << endl;
}
int main()
{
    //test_01();	//���Զ���������ͨ��
    test_02(); //����ɭ�ֺͶ�����

    system("pause");
    return 0;
}