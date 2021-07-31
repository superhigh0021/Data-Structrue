#include "BinTree.h"
#include <iostream>
using namespace std;

template <typename T>
class BST : public BinTree<T> {
protected:
    BinNodePosi(T) _hot;
    BinNodePosi(T)
        connect34(BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
            BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));
    BinNodePosi(T) rotateAt(BinNodePosi(T) x);

public:
    virtual BinNodePosi(T) & search(const T& e);
    virtual BinNodePosi(T) insert(const T& e);
    virtual bool remove(const T& e);
};

template <typename T>
    static BinNodePosi(T) & serchIn(BinNodePosi(T) & v, const T& e, BinNodePosi(T) & hot)
{
    if (!v || (e == v->data))
        return v;
    hot = v;
    return searchIn(((e < v->data) ? v->lc : v->rc), e, hot);
}

template <typename T>
    BinNodePosi(T) & BST<T>::search(const T& e)
{
    return searchIn(this->_root, e, _hot = NULL);
}

template <typename T>
BinNodePosi(T) BST<T>::insert(const T& e)
{
    BinNodePosi(T)& x = search(e);
    if (x)
        return x;
    x = new BinNode<T>(e, _hot); //ÒÔ_hotÎª¸¸
    this->_size++;
    updateHeightAbove(x);
    return x;
}

template <typename T>
static BinNodePosi(T) removeAt(BinNodePosi(T) & x, BinNodePosi(T) & hot)
{
    BinNodePosi(T) w = x;
    BinNodePosi(T) succ = NULL;
    if (!HasLChild(*x))
        succ = x = x->rc;
    else if (!HasRChild(*x))
        succ = x = x->lc;
    else {
        w = w->succ();
        std::swap(x->data, w->data);
        BinNodePosi(T) u = w->parent;
        ((u == x) ? u->rc : u->lc) = succ = w->rc;
    }
    if (succ)
        succ->parent = hot;
    release(w->data);
    release(w);
    return succ;
}

template <typename T>
bool BST<T>::remove(const T& e)
{
    BinNodePosi(T)& x = search(e);
    if (!x)
        return false;
    removeAt(x, _hot);
    this->_size--;
    updateHeightAbove(_hot);
    return true;
}

template <typename T>
BinNodePosi(T) BST<T>::
    connect34(BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c, BinNodePosi(T) T0,
        BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3)
{
    a->lc = T0;
    if (T0)
        T0->parent = a;
    a->rc = T1;
    if (T1)
        T1->parent = a;
    updateHeight(a);
    c->lc = T2;
    if (T2)
        T2->parent = c;
    c->rc = T3;
    if (T3)
        T3->parent = c;
    updateHeight(c);
    b->lc = a;
    a->parent = b;
    b->rc = c;
    c->parent = b;
    updateHeight(b);
    return b;
}

template <typename T>
BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) v)
{
    BinNodePosi(T) p = v->parent;
    BinNodePosi(T) g = p->parent;
    if (IsLChild(*p)) {
        if (IsLChild(*v)) {
            p->parnet = g->parent;
            return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
        } else {
            v->parent = g->parent;
            return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
        }
    } else if (IsRChild(*p)) {
        if (IsRChild(*v)) {
            p->parent = g->parent;
            return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
        } else {
            v->parent = g->parent;
            return connect34(g, v, p, g->lc, g->lc, v->lc, v->rc, p->rc);
        }
    }
}