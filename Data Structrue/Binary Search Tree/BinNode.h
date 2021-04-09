#include "BinNode_macro_BASIC.h"
#include <iostream>
using namespace std;
#define BinNodePosi(T) BinNode<T>*
#define stature(p) ((p) ? (p)->height : -1)
typedef enum {
    RB_RED,
    RB_BLACK
} RBColor;

template <typename T>
struct BinNode {
    T data;
    BinNodePosi(T) parent;
    BinNodePosi(T) lc;
    BinNodePosi(T) rc;
    int height;
    int npl;
    RBColor color;
    //构造函数
    BinNode()
        : parent(NULL)
        , lc(NULL)
        , rc(NULL)
        , height(0)
        , npl(1)
        , color(RB_RED)
    {
    }
    BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED)
        : data(e)
        , parent(p)
        , lc(lc)
        , rc(rc)
        , height(h)
        , npl(l)
        , color(c)
    {
    }
    //接口操作
    int size(); //统计当前节点后代总数
    BinNodePosi(T) insertAsLc(const T&);
    BinNodePosi(T) insertAsRc(const T&);
    BinNodePosi(T) succ();
    template <typename VST>
    void travLevel(VST&); //子树层次遍历
    template <typename VST>
    void travPre(VST&); //子树先序遍历
    template <typename VST>
    void travIn(VST&); //子树中序遍历
    template <typename VST>
    void travPost(VST&); //子树后序遍历
    //比较器、判等器
    bool operator<(BinNode const& bn) { return data < bn.data; };
    bool operator==(BinNode const& bn) { return data == bn.data; };
};

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLc(const T& e)
{
    return this->lc = new BinNode(e, this);
}

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRc(const T& e)
{
    return this->rc = new BinNode(e, this);
}

template <typename T>
int BinNode<T>::size()
{
    int s = 1;
    if (lc)
        s += lc->size();
    if (rc)
        s += rc->size();

    return s;
}

template <typename T>
template <typename VST>
void BinNode<T>::travIn(VST& visit)
{
    switch (rand() % 5) {
    case 1:
        travIn_I1(this, visit);
        break; //迭代版#1
    case 2:
        travIn_I2(this, visit);
        break; //迭代版#2
    case 3:
        travIn_I3(this, visit);
        break; //迭代版#3
    case 4:
        travIn_I4(this, visit);
        break; //迭代版#4
    default:
        travIn_R(this, visit);
        break; //递归版
    }
}

template <typename T>
BinNodePosi(T) BinNode<T>::succ()
{
    BinNodePosi(T) s = this;
    if (rc) {
        s = rc;
        while (HasLChild(*s))
            s = s->lc;
    } else {
        while (IsRChild(*s))
            s = s->parent;
        s = s->parent;
    }
    return s;
}