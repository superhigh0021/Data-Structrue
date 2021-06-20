#include "BinNode.h"
#include <iostream>
using namespace std;
template <typename T>
class BinTree {
protected:
    int _size;
    BinNodePosi(T) _root; //规模，根节点
    virtual int updateHeight(BinNodePosi(T) x); //更新节点x的高度
    void updateHeightAbove(BinNodePosi(T) x); //更新节点x及其祖先的高度
public:
    BinTree()
        : _size(0)
        , _root(NULL)
    {
    }
    ~BinTree()
    {
        if (_size > 0)
            remove(_root);
    }
    int size() const { return _size; }
    bool empty() const { return !_root; }
    BinNodePosi(T) root() const { return _root; } //规模
    BinNodePosi(T) insertAsRoot(T const& e);
    BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e);
    BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e);
    BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>*& S);
    BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>*& S);
    int remove(BinNodePosi(T) x);
    BinTree<T>* secede(BinNodePosi(T) x);
    template <typename VST>
    void travLevel(VST& visit)
    {
        if (_root)
            _root->travLevel(visit);
    } //层次遍历
    template <typename VST>
    void travPre(VST& visit)
    {
        if (_root)
            _root->travPre(visit);
    } //先序遍历
    template <typename VST>
    void travIn(VST& visit)
    {
        if (_root)
            _root->travIn(visit);
    } //中序遍历
    template <typename VST>
    void travPost(VST& visit)
    {
        if (_root)
            _root->travPost(visit);
    } //后序遍历

    static bool lt(T* a, T* b)
    {
        return lt(*a, *b);
    }

    bool lt(T a, T b)
    {
        return a < b;
    }

    bool operator<(BinTree<T> const& t)
    {
        return _root && t._root && this->lt(_root, t._root);
    }
    bool operator==(BinTree<T> const& t)
    {
        return _root && t._root && (_root == t._root);
    }
};

template <typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x)
{
    return x->height = 1 + max(stature(x->lc), stature(x->rc));
}

template <typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
    while (x) {
        updateHeight(x);
        x = x->parent;
    }
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e)
{
    _size = 1;
    return _root = new BinNode<T>(e);
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e)
{
    _size++;
    x->insertAsLc(e); //此处为BinNode类的同名函数，并非递归调用
    updateHeightAbove(x);
    return x->lc;
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e)
{
    _size++;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rc;
}

template <typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>*& S)
{
    if (x->lc = S->_root)
        x->lc->parent = x;
    _size += S->_size;
    updateHeightAbove(x);
    S->_root = NULL;
    S->_size = 0;
    delete S;
    S = NULL;
    return x;
}

template <typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>*& S)
{
    if (x->rc = S->_root)
        x->rc->parent = x;
    _size += S->_size;
    updateHeightAbove(x);
    S->_root = NULL;
    S->_size = 0;
    delete S;
    S = NULL;
    return x;
}

template <typename T>
int BinTree<T>::remove(BinNodePosi(T) x)
{
    FromParentTo(*x) = NULL;
    updateHeightAbove(x->parent);
    int n = removeAt(x);
    _size -= n;
    return n;
}

template <typename T>
static int removeAt(BinNodePosi(T) x)
{
    if (!x)
        return 0;
    int n = 1 + removeAt(x->lc) + removeAt(x->rc);
    delete x;
    return n;
}

template <typename T, typename VST>
void travPre_R(BinNodePosi(T) x, VST& visit)
{
    if (!x)
        return;
    visit(x->data);
    travPre_R(x->lc, visit);
    travPre_R(x->rc, visit);
}

template <typename T, typename VST>
void travPost_R(BinNodePosi(T) x, VST& visit)
{
    if (!x)
        return;
    travPost_R(x->lc, visit);
    travPost_R(x->rc, visit);
    visit(x);
}
