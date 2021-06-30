#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;
#define maxSize 100

#define CSTree CSNode*

//树的结点定义（孩子-兄弟链表法)
class CSNode {
public:
    char data;
    CSNode *firstchild, *nextsibling;
    CSNode(char data)
        : data(data)
    {
    }
};

//二叉树结点的定义
class BTNode {
public:
    char data;
    BTNode* lchild;
    BTNode* rchild;
};

//森林的定义
typedef struct
{
    CSTree ct[maxSize]; //只需把普通常规树的头结点全部放到森林中的数组即可
    int num; //森林中树的棵数
} Forest;

//存储路径定义
typedef struct
{
    char path[100];
} Str;

//创建一棵树
//常规树的输入规则：每遇到一个叶子节点就加一个0，最后都输入完了再多加两个0，跟二叉树的输入规则一样
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

//树转换成二叉树其实很简单，就是借助他俩先序序列一样
//让树的兄弟和二叉树的右孩子直接交换data就行
//因为他俩存储的时候其实采用的方式也是一样的，都是孩子兄弟链表法
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
//二叉树转换成普通树
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
//森林转二叉树
BTNode* ForestToBTree(CSTree F[], int low, int high)
{
    //low为当前指向的树，high为第n棵树的下标n-1
    if (low > high)
        return NULL;
    else {
        //二叉树的根即为第一棵树的根，同时二叉树的左孩子是第一棵树根节点的子树森林转化成的二叉树
        BTNode* root = ExchangeToBTree(F[low]);
        root->rchild = ForestToBTree(F, low + 1, high); //二叉树的右子树是森林其他树转换成的二叉树
        return root;
    }
}
//二叉树转森林
Forest* BTreeToForest(BTNode* root)
{
    BTNode* p = root;

    //森林初始化
    Forest* F = (Forest*)malloc(sizeof(Forest));
    BTNode* q = NULL;
    int i = 0; //统计树的个数
    //将二叉树转化为森林，核心代码
    while (p != NULL) {
        q = p->rchild; //先用q指向下一棵树的根节点
        p->rchild = NULL; //将当前有右孩子的二叉树的右孩子链接断开
        F->ct[i++] = ExchangeToCSTree(p); //将二叉树转化为树
        p = q; //将p指向下一棵树
    }
    F->num = i;
    return F;
}
//二叉树先序遍历
void preorder(BTNode* bt)
{
    if (bt != NULL) {
        cout << bt->data << "  ";
        preorder(bt->lchild);
        preorder(bt->rchild);
    }
}

//二叉树中序遍历
void inorder(BTNode* bt)
{
    if (bt != NULL) {
        inorder(bt->lchild);
        cout << bt->data << "  ";
        inorder(bt->rchild);
    }
}

//普通常规树的先序遍历
void preorder_cstree(CSTree ct)
{
    if (ct != NULL) {
        cout << ct->data << "  ";
        preorder_cstree(ct->firstchild);
        preorder_cstree(ct->nextsibling);
    }
}

//普通树的后序遍历=二叉树的中序遍历
void inorder_cstree(CSTree ct)
{
    if (ct != NULL) {
        inorder_cstree(ct->firstchild);
        cout << ct->data << "  ";
        inorder_cstree(ct->nextsibling);
    }
}

//森林先根遍历
void preorder_forest(Forest* f)
{
    int i;
    for (i = 0; i < f->num; ++i)
        preorder_cstree(f->ct[i]);
}

//森林后根遍历
void inorder_forest(Forest* f)
{
    int i;
    for (i = 0; i < f->num; ++i)
        inorder_cstree(f->ct[i]);
}
//下面是对创建树、树转二叉树、二叉树转树的代码测试
void test_01()
{
    ifstream ifs("E:\\FileRecv\\cstree.txt");
    string str;
    while (!ifs.eof()) {
        getline(ifs, str);
    }
    int a = 0;
    //创建一棵普通的常规树
    CSTree ct = CreateCSTree(str, str.length(), a);
    cout << "树的先序遍历序列为: ";
    preorder_cstree(ct);
    cout << endl;
    //普通树转为二叉树
    BTNode* bt = ExchangeToBTree(ct);
    cout << "普通树转为的二叉树的先序遍历序列为: ";
    preorder(bt);
    cout << endl;
    cout << "普通树转为的二叉树的中序遍历序列为: ";
    inorder(bt);
    cout << endl;
    //二叉树转为普通树
    CSTree ct2 = ExchangeToCSTree(bt);
    cout << "二叉树转为普通树的先序遍历序列为：";
    preorder_cstree(ct2);
    cout << endl;
}
//用来测试森林的创建、森林转二叉树、二叉树转森林
void test_02()
{
    //创建一个森林
    CSTree F[3];
    //三个建树文件的路径
    Str ps[3] = { "E:\\FileRecv\\cstree1.txt", "E:\\FileRecv\\cstree2.txt", "E:\\FileRecv\\cstree3.txt" };
    int length = 3;
    string* arr = new string[3];
    //从文件中读取建树字符串
    for (int i = 0; i < length; i++) {
        ifstream ifs(ps[i].path);
        getline(ifs, arr[i]);
        int a = 0;
        F[i] = CreateCSTree(arr[i], arr[i].length(), a);
    }
    //森林转二叉树
    BTNode* bt = ForestToBTree(F, 0, length - 1);
    cout << "森林转为的二叉树的中序遍历序列为： ";
    inorder(bt);
    cout << endl;
    //二叉树转森林
    Forest* F2;
    F2 = BTreeToForest(bt);
    cout << "中序遍历森林的结果为:  ";
    inorder_forest(F2);
    cout << endl;
    cout << "先序遍历森林的结果为: ";
    preorder_forest(F2);
    cout << endl;
}
int main()
{
    //test_01();	//测试二叉树和普通树
    test_02(); //测试森林和二叉树

    system("pause");
    return 0;
}