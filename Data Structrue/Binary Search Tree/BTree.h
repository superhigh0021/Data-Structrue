#include "BTNode.h"
#include <iostream>
using namespace std;

template <typename T>
class BTree
{
protected:
    int _size;  //��Źؼ��������
    int _order; //B-���Ľ״Σ�����Ϊ3������������ʱָ����һ�㲻���޸�
    BTNodePosi(T) _root;
    BTNodePosi(T) _hot;

    void solveOverflow(BTNodePosi(T));  //����������֮��ķ��Ѵ���
    void solveUnderflow(BTNodePosi(T)); //��ɾ��������֮��ĺϲ�����
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
        Rank r = v->key.search(e);  //�Ѿ��޸Ĺ�ԭ����������ֵΪ������e�������
        if ((0 <= r) && (e == v->key[r]))
            return v;
        _hot = v;
        v = v->child[r + 1];  //��һ��ͼ�ͺ������
    }
    return NULL;
}

template<typename T>
bool BTree<T>::insert(const T& e){
    BTNodePosi(T) v=search(e);
    if(v) return false;
}