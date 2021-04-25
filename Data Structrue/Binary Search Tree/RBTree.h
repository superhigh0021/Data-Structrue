#include "BST.h"
#include <iostream>
using namespace std;

#define IsBlack(p) (!(p) || (RB_BLACK == (p)->color))
#define IsRed(p) (!IsBlack(p))
#define BlackHeightUpdated(x) ((stature((x).lc) == stature((x).rc)) && ((x).height == (IsRed(&x) ? stature((x).lc) : ststure((x).lc) + 1)))

template <typename T>
class RedBlack : public BST<T>
{
protected:
    void solveDoubleRed(BinNodePosi(T) x);
    void solveDoubleBlack(BinNodePosi(T));
    int updateHeight(BinNodePosi(T));

public:
    BinNodePosi(T) insert(const T &e);
    bool remove(const T &e);
};

template <typename T>
int RedBlack<T>::updateHeight(BinNodePosi(T))
{
    x->height = max(stature(x->lc), stature(x->rc));
    return IsBlack(x) ? x->height++ : x->height;
}

template <typename T>
BinNodePosi(T) RedBlack<T>::insert(const T &e)
{
    BinNodePosi(T) &x = search(e);
    if (x)
        return x;
    x = new BinNode<T>(e, _hot, NULL, NULL, -1);
    _size++;
    solveDoubleRed(x);
    return x ? x : _hot->parent;
}

template <typename T>
void RedBlack<T>::solveDoubleRed(BinNodePosi(T) x)
{
    if (IsRoot(*x))
    {
        _root->color = RB_BLACK;
        _root->height++;
        return;
    }
    BinNodePosi(T) p = x->parent;
    if (IsBlack(p))
        return;
    BinNodePosi(T) g = p->parent;
    BinNodePosi(T) u = uncle(x);
    if (IsBlack(u))
    {
        if (IsLChild(*x) == IsLChild(*p))
            p->color = RB_BLACK;
        else
            x->color = RB_BLACK;
        g->color = RB_RED;
        BinNodePosi(T) gg = g->parent;
        BinNodePosi(T) r = FromParentTo(*g) = rotateAt(x);
        r->parent = gg;
    }
    else
    {
        p->color = RB_BLACK;
        p->height++;
        u->color = RB_BLACK;
        u->height++;
        if (!IsRoot(*g))
            g->color = RB_RED;
        solveDoubleRed(g);
    }
}

template <typename T>
bool RedBlack<T>::remove(const T &e)
{
    BinNodePosi(T) &x = search(e);
    if (!x)
        return false; //如果找不到该节点，删除宣告失败
    BinNodePosi(T) r = removeAt(x, _hot);
    if (!(--_size))
        return true; //实施删除
    if (!_hot)       //若刚刚被删除的节点为根节点，则将其置黑，并更新黑高度
    {
        _root->color = RB_BLACK;
        updateHeight(_root);
        return true;
    }

    //若祖先的黑深度依然平衡，则无需调整
    if (BlackHeightUpdated(*_hot))
        return true;
    if (IsRed(r))
    {
        r->color = RB_BLACK;
        r->height++;
        return true;
    }
    solveDoubleBlack(r);
    return true;
}

template <typename T>
void RedBlack<T>::solveDoubleBlack(BinNodePosi(T) r)
{
    // r的父亲
    BinNodePosi(T) p = r ? r->parent : _hot;
    if (!p)
        return;

    // r的兄弟
    BinNodePosi(T) s = (r == p->lc) ? p->rc : p->lc;

    //兄弟若为黑
    if (IsBlack(s))
    {
        BinNodePosi(T) t = NULL;
        //s的红孩子(若左右孩子皆为红，左者优先；皆黑使为NULL)
        if (IsRed(s->rc))
            t = s->rc;
        if (IsRed(r->lc))
            t = s->lc;
        if (t)
        {
            //黑s有红孩子： BB-1
            RBColor oldColor = p->color; //备份原子树根节点p颜色
            //通过旋转重平衡，并将新子树的左右孩子染黑
            BinNodePosi(T) b = FromParentTo(*p) = rotateAt(t);
            if (HasLChild(*b))
            {
                b->lc->color = RB_BLACK;
                updateHeight(b->lc); //左子
            }
            if (HasRChild(*b))
            {
                b->rc->color = RB_BLACK;
                updateHeight(b->rc);
            }
            b->color = oldColor;
            updateHeight(b);
        }
        else
        {
            //黑s无红孩子
            s->color = RB_RED;
            s->height--; //s转红
            if (IsRed(p))
            {
                //BB-2-R
                p->color = RB_BLACK;
            }
            else
            {
                //BB-2-B
                p->height--;
                solveDoubleBlack(p); //递归上溯
            }
        }
    }
    else
    {
        //兄弟s为红  BB-3
        s->color = RB_BLACK;
        p->color = RB_RED;

        //让旋转参数t和s在同侧，一字型旋转而不是之字形旋转！！！！
        BinNodePosi(T) t = IsLChild(*s) ? s->lc : s->rc;
        _hot = p;
        FromParentTo(*p) = rotateAt(t);
        solveDoubleBlack(r);
    }
}