#include "BTNode.h"
#include <iostream>
using namespace std;

template <typename T>
class BTree
{
protected:
    int _size;  //存放关键码的总数
    int _order; //B-树的阶次，至少为3————创建时指定，一般不能修改
    BTNodePosi(T) _root;
    BTNodePosi(T) _hot;

    void solveOverflow(BTNodePosi(T));  //因插入而上溢之后的分裂处理
    void solveUnderflow(BTNodePosi(T)); //因删除而下溢之后的合并处理
public:
    BTree(int order = 3)
        : _order(order), _size(0)
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
    BTNodePosi(T) search(const T &e);
    bool insert(const T &e);
    bool remove(const T &e);
};

template <typename T>
BTNodePosi(T) BTree<T>::search(const T &e)
{
    BTNodePosi(T) v = _root;
    _hot = NULL;
    while (v)
    {
        Rank r = v->key.search(e);  //已经修改过原函数，返回值为不大于e的最大秩
        if ((0 <= r) && (e == v->key[r]))
            return v;
        _hot = v;
        v = v->child[r + 1];  //画一下图就好理解了
    }
    return NULL;
}

template<typename T>
bool BTree<T>::insert(const T& e){
    BTNodePosi(T) v=search(e);
    if(v) return false;
}