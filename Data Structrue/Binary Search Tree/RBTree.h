#include "BST.h"
#include <iostream>
using namespace std;

#define IsBlack(p) (!(p) || (RB_BLACK == (p)->color))
#define IsRed(p) (!IsBlack(p))
#define BlackHeightUpdated(x) ((stature((x).lc) == stature((x).lc)) && ((x).height == (IsRed(&x) ? stature((x).lc) : ststure((x).lc) + 1)))

template <typename T>
class RedBlack : public BST<T> {
protected:
    void solveDoubleRed(BinNodePosi(T) x);
    void solveDoubleBlack(BinNodePosi(T));
    int updateHeight(BinNodePosi(T));

public:
    BinNodePosi(T) insert(const T& e);
    bool remove(const T& e);
};

template <typename T>
int RedBlack<T>::updateHeight(BinNodePosi(T))
{
    x->height = max(stature(x->lc), stature(x->rc));
    return IsBlack(x) ? x->height++ : x->height;
}

template <typename T>
BinNodePosi(T) RedBlack<T>::insert(const T& e)
{
    BinNodePosi(T)& x = search(e);
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
    if (IsRoot(*x)) {
        _root->color = RB_BLACK;
        _root->height++;
        return;
    }
    BinNodePosi(T) p = x->parent;
    if (IsBlack(p))
        return;
    BinNodePosi(T) g = p->parent;
    BinNodePosi(T) u = uncle(x);
    if (IsBlack(u)) {
        if (IsLChild(*x) == IsLChild(*p))
            p->color = RB_BLACK;
        else
            x->color = RB_BLACK;
        g->color = RB_RED;
        BinNodePosi(T) gg = g->parent;
        BinNodePosi(T) r = FromParentTo(*g) = rotateAt(x); 
        r->parent = gg;
    } else {
        p->color = RB_BLACK;
        p->height++;
        u->color = RB_BLACK;
        u->height++;
        if (!IsRoot(*g))
            g->color = RB_RED;
        solveDoubleRed(g);
    }
}