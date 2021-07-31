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
        Rank r = v->key.search(e); //已经修改过原函数，返回值为不大于e的最大秩
        if ((0 <= r) && (e == v->key[r]))
            return v;
        _hot = v;
        v = v->child[r + 1]; //画一下图就好理解了
    }
    return NULL;
}

template <typename T>
bool BTree<T>::insert(const T &e)
{
    BTNodePosi(T) v = search(e);
    if (v)
        return false; //确认目标节点不存在
    Rank r = _hot->key.search(e);
    _hot->key.insert(r + 1, e);
    _hot->child.insert(r + 2, NULL);
    this->_size++;
    solveOverflow(_hot);
    return true;
}

template <typename T>
void BTree<T>::solveOverflow(BTNodePosi(T) v)
{
    if (_order >= v->child.size())
        return;           //_order为B树的阶次。递归基：当前节点并未上溢
    Rank s = _order >> 1; //轴点
    BTNodePosi(T) u = new BTNode<T>();
    //让u成为_hot的右孩子
    for (Rank j = 0; j < _order - s - 1; ++j)
    {
        u->child.insert(j, v->child.remove(s + 1));
        u->key.insert(j, v->key.remove(s + 1));
    }
    //移动v最靠右的孩子给u
    u->child[_order - s - 1] = v->child.remove(s + 1);
    if (u->child[0])
        for (Rank j = 0; j < _order - s; ++j)
            u->child[j]->parent = u;
    BTNodePosi(T) p = v->parent;
    if (!p)
    { //若p为空，则new一个节点作为根节点
        _root = p = new BTNode(T);
        p->child[0] = v;
        v->parent = p;
    }
    Rank r = 1 + p->key.search(v->key[0]); //p中指向v的指针的秩
    p->key.insert(r, v->key.remove(s));    //轴点的关键码上升至父节点中
    p->child.insert(r + 1, u);
    u->parent = p;
    solveOverflow(p);
}

template <typename T>
bool BTree<T>::remove(const T &e)
{
    BTNodePosi(T) v = search(e);
    if (!v)
        return false;
    //确认关键码存在
    Rank r = v->key.search(e);
    if (v->child[0])
    {
        // 找该关键码对应的后继元素
        BTNodePosi(T) u = v->child[r + 1];
        while (u->child[0])
            u = u->child[0];
        v->key[r] = u->key[0];
        v = u;
        r = 0;
    }
    //把要删除的和后继元素换了一下，然而这个操作的结果就是换了个倒霉蛋被删除
    v->key.remove(r);
    v->child.remove(r + 1);
    _size--;
    solveUnderflow(v);
    return true;
}

template <typename T>
void BTree<T>::solveUnderflow(BTNodePosi(T) v)
{
    //递归基，当前节点并未下溢
    if ((_order + 1) >> 1 <= v->child.size())
    {
        return;
    }
    BTNodePosi(T) p = v->parent;
    if (!p)
    { // 递归基：  已到达树根
        if (!v->key.size() && v->child[0])
        {
            //但倘若作为树根的v已不含有关键码，却有非空分支，则
            _root = v->child[0]; //这个节点可被跳过
            _root->parent = NULL;
            v->child[0] = NULL;
            release(v);
        }
        return;
    }
    Rank r = 0;
    while (p->child[r] != v)
        r++; //确定v是p的第r个孩子

    //情况1：向左兄弟借关键码
    if (r > 0)
    {
        BTNodePosi(T) ls = p->child[r - 1];
        if ((_order + 1) >> 1 < ls->child.size())
        {
            //此处不能有等号，因为一旦等于了，就不能借了，一借就下溢
            v->key.insert(0, p->key key[r - 1]);
            p->key[r - 1] = ls->key.remove(ls->key.size() - 1);
            v->child.insert(0, ls->child.remove(ls->child.size() - 1));
            //同时将ls最右侧分支过继给v
            if (v->child[0])
                v->child[0]->parent = v;
        }
    }
    //情况2：向右兄弟借关键码
    if (p->child.size() - 1 > r)
    {
        //v不是p的最后一个分支
        BTNodePosi(T) rs = p->child[r + 1];
        if ((_order + 1) >> 1 < rs.child.size())
        {
            v->key.insert(v->key.size(), p->key[r]);
            p->key[r] = rs->key.remove(0);
            v->child.insert(v->child.size(), rs->child.remove(0));
            if (v->child[v->child.size() - 1])
                v->child[v->child.size() - 1]->parent = v;
            return;
        }
    }

    //情况3：左右兄弟要么为空（但不可能同时），要么都太瘦———合并！
    if (r > 0)
    { //与左兄弟合并
        BTNodePosi(T) ls = p->child[r - 1];
        ls->key.insert(ls->key.size(), p->key.remove(r - 1));
        p->child.remove(r);
        //p的第r-1个关键码转入ls，v不再是p的第r个孩子
        ls->child.insert(ls->child.size(), v->child.remove(0));
        if (ls->child[ls->child.size() - 1])
            ls->child[ls->child.size() - 1]->parent = ls;
        while (!v->key.empty())
        {
            //v剩余的关键码和孩子，依次转入ls
            ls->key.insert(ls->key.size(), v->key.remove(0));
            ls->child.insert(ls->child.size(), v->child.remove(0));
            if (ls->child[ls->child.size() - 1])
                ls->child[ls->child.size() - 1]->parent = ls;
        }
        release(v);
    }
    else
    {
        //与右兄弟合并
        BTNodePosi(T) rs = p->child[r + 1];
        rs->key.insert(0, p->key.remove(r));
        p->child.remove(r);
        rs->child.insert(0, v->child.remove(v->child.size() - 1));
        if (rs->child[0])
            rs->child[0]->parent = rs;
        while (!v->key.empty())
        {
            rs->key.insert(0, v->key.remove(v->key.size() - 1));
            rs->child.insert(0, v->child.remove(v->child.size() - 1));
            if (rs->child[0])
                rs->child[0]->parent = rs;
        }
        release(v);
    }
    solveUnderflow(p);
    return;
}