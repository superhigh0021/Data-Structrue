#include "BinNode.h"
template <typename T>
class BinTree
{
protected:
    int _size;
    BinNodePosi(T) _root;                       //规模，根节点
    virtual int updateHeight(BinNodePosi(T) x); //更新节点x的高度
    void updateHeightAbove(BinNodePosi(T) x);   //更新节点x及其祖先的高度
public:
    BinTree() : _size(0), _root(NULL) {}
    ~BinTree()
    {
        if (_size > 0)
            remove(_root);
    }
    int size() const { return _size; }
    bool empty() const { return !_root; }
    BinNodePosi(T) root() const { return _root; } //规模
    BinNodePosi(T) insertAsRoot(T const &e);
    BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const &e);
    BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const &e);
    BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T> *T);
    BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T> *T);
    int remove(BinNodePosi(T) x);
    BinTree<T> *secede(BinNodePosi(T) x);
    template <typename VST>
    void travLevel(VST &visit)
    {
        if (_root)
            _root->travLevel(visit);
    } //层次遍历
    template <typename VST>
    void travPre(VST &visit)
    {
        if (_root)
            _root->travPre(visit);
    } //先序遍历
    template <typename VST>
    void travIn(VST &visit)
    {
        if (_root)
            _root->travIn(visit);
    } //中序遍历
    template <typename VST>
    void travPost(VST &visit)
    {
        if (_root)
            _root->travPost(visit);
    } //后序遍历

    template <typename T>
    static bool lt(T *a, T *b)
    {
        return lt(*a, *b);
    }

    template <typename T>
    bool lt(T a, T b)
    {
        return a < b;
    }

    bool operator<(BinTree<T> const &t)
    {
        return _root && t._root && this->lt(_root, t._root);
    }
    bool operator==(BinTree<T> const &t)
    {
        return _root && t._root && (_root == t._root);
    }
};