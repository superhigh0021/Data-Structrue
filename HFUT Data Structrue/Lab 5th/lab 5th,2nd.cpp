#include <fstream>
#include <iostream>
using namespace std;
ifstream forest; //定义全局的输入流文件
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
        cout << T->data << "左孩子(#结束):";
        cmdcreat(T->firstchild);
        cout << T->data << "右兄弟(#结束):";
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
    int n = 0; //n为树的个数
    cout << "这是一个森林系统 你要生成几棵树";
    cin >> n;
    bnode* B = new bnode[n]; //用来存储每棵树的根节点
    int num = 0; //记录当前是第几棵树
    while (1) {
        cout << "用命令行生成树输入1   用文件生成树输入2   让树变成森林输入3   ";
        cout << "前序遍历输入4   中序遍历输入5   后序遍历输入6   结束输入0" << endl;
        cin >> i;
        if (i == 0)
            break;
        if (i == 1) {
            bnode* T = NULL;
            cout << "输入根节点";
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
