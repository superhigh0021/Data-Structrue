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
        Rank r = v->key.search(e); //�Ѿ��޸Ĺ�ԭ����������ֵΪ������e�������
        if ((0 <= r) && (e == v->key[r]))
            return v;
        _hot = v;
        v = v->child[r + 1]; //��һ��ͼ�ͺ������
    }
    return NULL;
}

template <typename T>
bool BTree<T>::insert(const T &e)
{
    BTNodePosi(T) v = search(e);
    if (v)
        return false; //ȷ��Ŀ��ڵ㲻����
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
        return;           //_orderΪB���Ľ״Ρ��ݹ������ǰ�ڵ㲢δ����
    Rank s = _order >> 1; //���
    BTNodePosi(T) u = new BTNode<T>();
    //��u��Ϊ_hot���Һ���
    for (Rank j = 0; j < _order - s - 1; ++j)
    {
        u->child.insert(j, v->child.remove(s + 1));
        u->key.insert(j, v->key.remove(s + 1));
    }
    //�ƶ�v��ҵĺ��Ӹ�u
    u->child[_order - s - 1] = v->child.remove(s + 1);
    if (u->child[0])
        for (Rank j = 0; j < _order - s; ++j)
            u->child[j]->parent = u;
    BTNodePosi(T) p = v->parent;
    if (!p)
    { //��pΪ�գ���newһ���ڵ���Ϊ���ڵ�
        _root = p = new BTNode(T);
        p->child[0] = v;
        v->parent = p;
    }
    Rank r = 1 + p->key.search(v->key[0]); //p��ָ��v��ָ�����
    p->key.insert(r, v->key.remove(s));    //���Ĺؼ������������ڵ���
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
    //ȷ�Ϲؼ������
    Rank r = v->key.search(e);
    if (v->child[0])
    {
        // �Ҹùؼ����Ӧ�ĺ��Ԫ��
        BTNodePosi(T) u = v->child[r + 1];
        while (u->child[0])
            u = u->child[0];
        v->key[r] = u->key[0];
        v = u;
        r = 0;
    }
    //��Ҫɾ���ĺͺ��Ԫ�ػ���һ�£�Ȼ����������Ľ�����ǻ��˸���ù����ɾ��
    v->key.remove(r);
    v->child.remove(r + 1);
    _size--;
    solveUnderflow(v);
    return true;
}

template <typename T>
void BTree<T>::solveUnderflow(BTNodePosi(T) v)
{
    //�ݹ������ǰ�ڵ㲢δ����
    if ((_order + 1) >> 1 <= v->child.size())
    {
        return;
    }
    BTNodePosi(T) p = v->parent;
    if (!p)
    { // �ݹ����  �ѵ�������
        if (!v->key.size() && v->child[0])
        {
            //��������Ϊ������v�Ѳ����йؼ��룬ȴ�зǿշ�֧����
            _root = v->child[0]; //����ڵ�ɱ�����
            _root->parent = NULL;
            v->child[0] = NULL;
            release(v);
        }
        return;
    }
    Rank r = 0;
    while (p->child[r] != v)
        r++; //ȷ��v��p�ĵ�r������

    //���1�������ֵܽ�ؼ���
    if (r > 0)
    {
        BTNodePosi(T) ls = p->child[r - 1];
        if ((_order + 1) >> 1 < ls->child.size())
        {
            //�˴������еȺţ���Ϊһ�������ˣ��Ͳ��ܽ��ˣ�һ�������
            v->key.insert(0, p->key key[r - 1]);
            p->key[r - 1] = ls->key.remove(ls->key.size() - 1);
            v->child.insert(0, ls->child.remove(ls->child.size() - 1));
            //ͬʱ��ls���Ҳ��֧���̸�v
            if (v->child[0])
                v->child[0]->parent = v;
        }
    }
    //���2�������ֵܽ�ؼ���
    if (p->child.size() - 1 > r)
    {
        //v����p�����һ����֧
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

    //���3�������ֵ�ҪôΪ�գ���������ͬʱ����Ҫô��̫�ݡ������ϲ���
    if (r > 0)
    { //�����ֵܺϲ�
        BTNodePosi(T) ls = p->child[r - 1];
        ls->key.insert(ls->key.size(), p->key.remove(r - 1));
        p->child.remove(r);
        //p�ĵ�r-1���ؼ���ת��ls��v������p�ĵ�r������
        ls->child.insert(ls->child.size(), v->child.remove(0));
        if (ls->child[ls->child.size() - 1])
            ls->child[ls->child.size() - 1]->parent = ls;
        while (!v->key.empty())
        {
            //vʣ��Ĺؼ���ͺ��ӣ�����ת��ls
            ls->key.insert(ls->key.size(), v->key.remove(0));
            ls->child.insert(ls->child.size(), v->child.remove(0));
            if (ls->child[ls->child.size() - 1])
                ls->child[ls->child.size() - 1]->parent = ls;
        }
        release(v);
    }
    else
    {
        //�����ֵܺϲ�
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