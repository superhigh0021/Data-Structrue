#include "BST.h"
#include <iostream>
using namespace std;

template <typename T>
class Splay : public BST<T> {
protected:
    BinNodePosi(T) splay(BinNodePosi(T) v);

public:
    BinNodePosi(T) & search(const T& e);
    BinNodePosi(T) insert(const T& e);
    bool remove(const T& e);
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
    while (p = v->parent&& g = p->parent) {
        BinNodePosi(T) gg = g->parent;
        //每轮之后v都以原曾祖父为父
        if (IsLChild(*v))
            if (IsLChild(*p)) {
                attachAsLChild(g, p->rc);
                attachAsLChild(p, v->rc);
                attachAsRChild(p, g);
                attachAsRChild(v, p);
            } else {
                attachAsLChild(p, v->rc);
                attachAsRChild(g, v->lc);
                attachAsLChild(v, g);
                attachAsRChild(v, p);
            }
        else if (IsRChild(*p)) {
            attachAsRChild(g, p->lc);
            attachAsRChild(p, v->lc);
            attachAsLChild(p, g);
            attachAsLChild(v, p);
        } else {
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
    if (p = v->parent) //偶数个节点的情况，最后v上面还有个p，单独旋转一下就行了
    {
        if (IsLChild(*v)) {
            attachAsLChild(p, v->rc);
            attachAsRChild(v, p);
        } else {
            attachAsRChild(p, v->lc);
            attachAsLChild(v, p);
        }
        updateHeight(p);
        updateHeight(v);
    }
    v->parent = NULL;
    return v;
}

template <typename T>
    BinNodePosi(T) & Splay<T>::search(const T& e)
{
    BinNodePosi(T) p = searchIn(this->_root, e, this->_hot = NULL);
    this->_root = splay(p ? p : this->_hot); //能找到该节点，调整p；找不到，调整最后命中的那个节点
    return this->_root;
}

template <typename T>
BinNodePosi(T) Splay<T>::insert(const T& e)
{
    if (!this->_root) {
        this->_size++;
        return this->_root = new BinNode<T>(e);
    } //处理原树为空的情况
    if (e == search(e)->data)
        return this->_root;
    this->_size++;
    BinNodePosi(T) t = this->_root;
    if (this->_root->data < e) {
        t->parent = this->_root = new BinNode<T>(e, NULL, t, t->rc);
        if (HasRChild(*t)) {
            t->rc->parent = this->_root;
            t->rc = NULL;
        } //此处解释不清楚，再看时不明白一定要画图
    } else {
        t->parent = this->_root = new Binnode<T>(e, NULL, t->lc, t);
        if (HasLChild(*t)) {
            t->lc->parent = this->_root;
            t->lc = NULL;
        }
    }
    updateHeightAbove(t);
    return this->_root;
}

template <typename T>
bool Splay<T>::remove(const T& e)
{
    if (!this->_root || (e != search(e)->data))
        return false;
    BinNodePosi(T) w = this->_root;
    if (!HasLChild(*this->_root)) {
        this->_root = this->_root->rc;
        if (this->_root)
            this->root->parent = NULL;
    } else if (!HasRChild(*this->_root)) {
        this->_root = this->_root->lc;
        if (this->_root)
            this->_root->parent = NULL;
    } else {
        BinNodePosi(T) lTree = this->_root->lc;
        lTree->parent = NULL;
        this->_root->lc = NULL;
        this->_root = this->_root->rc;
        this->_root->parent = NULL;
        search(w->data);
        this->_root->lc = lTree;
        lTree->parent = this->_root;
    }
    release(w->data);
    release(w);
    --this->_size;
    if (this->_root)
        updateHeight(this->_root);
    return true;
}