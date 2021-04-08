#include "BST.h"
#include <iostream>
using namespace std;

template <typename T>
class Splay : public BST<T>
{
protected:
    BinNodePosi(T) splay(BinNodePosi(T) v);

public:
    BinNodePosi(T) & search(const T &e);
    BinNodePosi(T) insert(const T &e);
    bool remove(const T &e);
};

template <typename NodePosi>
inline void attachAsLChild(NodePosi p, NodePosi lc)
{
    p->lc = lc;
    if (lc)
        lc->parent = p;
}

template <typename NodePosi>
inline void attachAsRChild(NodePosi p, NodePosi rc)
{
    p->rc = rc;
    if (rc)
        rc->parent = p;
}

template <typename T>
BinNodePosi(T) Splay<T>::splay(BinNodePosi(T) v)
{
    if (!v)
        return NULL;
    BinNodePosi(T) p, g;
    while (p = v->parent &&g = p->parent)
    {
        BinNodePosi(T) gg = g->parent;
        //每轮之后v都以原曾祖父为父
        if (IsLChild(*v))
            if (IsLChild(*p))
            {
                attachAsLChild(g, p->rc);
                attachAsLChild(p, v->rc);
                attachAsRChild(p, g);
                attachAsRChild(v, p);
            }
            else
            {
                attachAsLChild(p, v->rc);
                attachAsRChild(g, v->lc);
                attachAsLChild(v, g);
                attachAsRChild(v, p);
            }
        else if (IsRChild(*p))
        {
            attachAsRChild(g, p->lc);
            attachAsRChild(p, v->lc);
            attachAsLChild(p, g);
            attachAsLChild(v, p);
        }
        else
        {
            attachAsRChild(p, v->lc);
            attachAsLChild(g, v->rc);
            attachAsRChild(v, g);
            attachAsLChild(v, p);
        }
        if (!gg)
            v->parent = NULL;
        else
            (g == gg->lc) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
        updateHeight(g);
        updateHeight(p);
        updateHeight(v);
    }
    if (p = v->parent)   //偶数个节点的情况，最后v上面还有个p，单独旋转一下就行了
    {
        if (IsLChild(*v))
        {
            attachAsLChild(p, v->rc);
            attachAsRChild(v, p);
        }
        else
        {
            attachAsRChild(p, v->lc);
            attachAsLChild(v, p);
        }
        updateHeight(p);
        updateHeight(v);
    }
    v->parent = NULL;
    return v;
}


