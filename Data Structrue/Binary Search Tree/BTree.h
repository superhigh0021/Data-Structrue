#include "BTNode.h"
#include <iostream>
using namespace std;

template <typename T>
class BTree {
protected:
    int _size; //��Źؼ��������
    int _order; //B-���Ľ״Σ�����Ϊ3������������ʱָ����һ�㲻���޸�
    BTNodePosi(T) _root;
    BTNodePosi(T) _hot;

    void solveOverflow(BTNodePosi(T)); //����������֮��ķ��Ѵ���
    void solveUnderflow(BTNodePosi(T)); //��ɾ��������֮��ĺϲ�����
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
        Rank r = v->key.search(e); //�Ѿ��޸Ĺ�ԭ����������ֵΪ������e�������
        if ((0 <= r) && (e == v->key[r]))
            return v;
        _hot = v;
        v = v->child[r + 1]; //��һ��ͼ�ͺ������
    }
    return NULL;
}

template <typename T>
bool BTree<T>::insert(const T& e)
{
    BTNodePosi(T) v = search(e);
    if (v)
        return false; //ȷ��Ŀ��ڵ㲻����
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
        return; //_orderΪB���Ľ״Ρ��ݹ������ǰ�ڵ㲢δ����
    Rank s = _order >> 1; //���
    BTNodePosi(T) u = new BTNode<T>();
    //��u��Ϊ_hot���Һ���
    for (Rank j = 0; j < _order - s - 1; ++j) {
        u->child.insert(j, v->child.remove(s + 1));
        u->key.insert(j, v->key.remove(s + 1));
    }
    //�ƶ�v��ҵĺ��Ӹ�u
    u->child[_order - s - 1] = v->child.remove(s + 1);
    if (u->child[0])
        for (Rank j = 0; j < _order - s; ++j)
            u->child[j]->parent = u;
    BTNodePosi(T) p = v->parent;
    if (!p) { //��pΪ�գ���newһ���ڵ���Ϊ���ڵ�
        _root = p = new BTNode(T);
        p->child[0] = v;
        v->parent = p;
    }
    Rank r = 1 + p->key.search(v->key[0]); //p��ָ��v��ָ�����
    p->key.insert(r, v->key.remove(s)); //���Ĺؼ������������ڵ���
    p->child.insert(r + 1, u);
    u->parent = p;
    solveOverflow(p);
}