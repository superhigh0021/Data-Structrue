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
    int const order(){
        return _order;
    }
    int const size(){
         return _size;
    }
    BTNodePosi(T) search
};