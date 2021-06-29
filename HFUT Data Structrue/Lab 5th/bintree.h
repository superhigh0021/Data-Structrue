#include <iostream>
using namespace std;

#define BinNodePosi(T) BinNode<T>*

template <typename T>
class BinNode {
public:
    T data;
    BinNodePosi(T) parent;
    BinNodePosi(T) lchild=nullptr;
    BinNodePosi(T) rchild=nullptr;
    BinNode()
        : parent(nullptr)
        , lchild(nullptr)
        , rchild(nullptr)
    {
    }
    BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL)
        : data(e)
    {
    }
    BinNodePosi(T) insertAsLc(const T& e)
    {
        return this->lchild = new BinNode(e, this);
    }
    BinNodePosi(T) insertAsRc(const T& e)
    {
        return this->rchild = new BinNode(e, this);
    }
};

template <typename T>
class BinTree {
private:
    int _size;
    BinNodePosi(T) _root;

public:
    BinTree()
        : _size(0),_root(nullptr)
    {
    }
    void travIn()
    {
        if (_root)
            travIn_R(this->_root, 0);
    }
    BinNodePosi(T) root() const { return _root; }
    BinNodePosi(T) insertAsRoot(T const& e)
    {
        _size = 1;
        return _root = new BinNode<T>(e);
    }
    BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e)
    {
        _size++;
        x->insertAsLc(e);
        return x->lchild;
    }
    BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e)
    {
        _size++;
        x->insertAsRc(e);
        return x->rchild;
    }
};

template <typename T>
void travIn_R(BinNodePosi(T) x, int n)
{
    if (!x)
        return;
    ++n;
    travIn_R(x->lchild, n);
    cout << x->data <<":"<< n << "  ";
    travIn_R(x->rchild, n);
}