#include "BTNode.h"
#include <iostream>
using namespace std;

template <typename T>
class BTree {
protected:
    int _size; //存放关键码的总数
    int _order; //B-树的阶次，至少为3————创建时指定，一般不能修改
    BTNodePosi(T) _root;
    BTNodePosi(T) _hot;

    void solveOverflow(BTNodePosi(T)); //因插入而上溢之后的分裂处理
    void solveUnderflow(BTNodePosi(T)); //因删除而下溢之后的合并处理
public:
    BTree(int order = 3)
        : _order(order)
        , _size(0)
    {
        _root = new BNTNode<T>();
    }
    ~BTree()
    {
        if (_root)
            release(_root);
    }
    int const order() { return _order; }
    int const size() { return _size; }
    bool empty() const { return !_root; }
    BTNodePosi(T) search(const T& e);
    bool insert(const T& e);
    bool remove(const T& e);
};

template <typename T>
BTNodePosi(T) BTree<T>::search(const T& e)
{
    BTNodePosi(T) v = _root;
    _hot = NULL;
    while (v) {
        Rank r = v->key.search(e); //已经修改过原函数，返回值为不大于e的最大秩
        if ((0 <= r) && (e == v->key[r]))
            return v;
        _hot = v;
        v = v->child[r + 1]; //画一下图就好理解了
    }
    return NULL;
}

template <typename T>
bool BTree<T>::insert(const T& e)
{
    BTNodePosi(T) v = search(e);
    if (v)
        return false; //确认目标节点不存在
    Rank r = this->_hot->key.search(e);
    this->_hot->key.insert(r + 1, e);
    this->_hot->child.insert(r + 2, NULL);
    this->_size++;
    solveOverflow(this->_hot);
    return true;
}

template <typename T>
void BTree<T>::solveOverflow(BTNodePosi(T) v)
{
    if (_order >= v->child.size())
        return; //_order为B树的阶次。递归基：当前节点并未上溢
    Rank s = _order >> 1; //轴点
    BTNodePosi(T) u = new BTNode<T>();
    //让u成为_hot的右孩子
    for (Rank j = 0; j < _order - s - 1; ++j) {
        u->child.insert(j, v->child.remove(s + 1));
        u->key.insert(j, v->key.remove(s + 1));
    }
    //移动v最靠右的孩子给u
    u->child[_order - s - 1] = v->child.remove(s + 1);
    if (u->child[0])
        for (Rank j = 0; j < _order - s; ++j)
            u->child[j]->parent = u;
    BTNodePosi(T) p = v->parent;
    if (!p) { //若p为空，则new一个节点作为根节点
        _root = p = new BTNode(T);
        p->child[0] = v;
        v->parent = p;
    }
    Rank r = 1 + p->key.search(v->key[0]); //p中指向v的指针的秩
    p->key.insert(r, v->key.remove(s)); //轴点的关键码上升至父节点中
    p->child.insert(r + 1, u);
    u->parent = p;
    solveOverflow(p);
}