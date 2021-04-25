#include "BST.h"
#include <iostream>
using namespace std;

#define IsBlack(p) (!(p) || (RB_BLACK == (p)->color))
#define IsRed(p) (!IsBlack(p))
#define BlackHeightUpdated(x) ((stature((x).lc) == stature((x).rc)) && ((x).height == (IsRed(&x) ? stature((x).lc) : ststure((x).lc) + 1)))

template <typename T>
class RedBlack : public BST<T>
{
protected:
    void solveDoubleRed(BinNodePosi(T) x);
    void solveDoubleBlack(BinNodePosi(T));
    int updateHeight(BinNodePosi(T));

public:
    BinNodePosi(T) insert(const T &e);
    bool remove(const T &e);
};

template <typename T>
int RedBlack<T>::updateHeight(BinNodePosi(T))
{
    x->height = max(stature(x->lc), stature(x->rc));
    return IsBlack(x) ? x->height++ : x->height;
}

template <typename T>
BinNodePosi(T) RedBlack<T>::insert(const T &e)
{
    BinNodePosi(T) &x = search(e);
    if (x)
        return x;
    x = new BinNode<T>(e, _hot, NULL, NULL, -1);
    _size++;
    solveDoubleRed(x);
    return x ? x : _hot->parent;
}

template <typename T>
void RedBlack<T>::solveDoubleRed(BinNodePosi(T) x)
{
    if (IsRoot(*x))
    {
        _root->color = RB_BLACK;
        _root->height++;
        return;
    }
    BinNodePosi(T) p = x->parent;
    if (IsBlack(p))
        return;
    BinNodePosi(T) g = p->parent;
    BinNodePosi(T) u = uncle(x);
    if (IsBlack(u))
    {
        if (IsLChild(*x) == IsLChild(*p))
            p->color = RB_BLACK;
        else
            x->color = RB_BLACK;
        g->color = RB_RED;
        BinNodePosi(T) gg = g->parent;
        BinNodePosi(T) r = FromParentTo(*g) = rotateAt(x);
        r->parent = gg;
    }
    else
    {
        p->color = RB_BLACK;
        p->height++;
        u->color = RB_BLACK;
        u->height++;
        if (!IsRoot(*g))
            g->color = RB_RED;
        solveDoubleRed(g);
    }
}

template <typename T>
bool RedBlack<T>::remove(const T &e)
{
    BinNodePosi(T) &x = search(e);
    if (!x)
        return false; //����Ҳ����ýڵ㣬ɾ������ʧ��
    BinNodePosi(T) r = removeAt(x, _hot);
    if (!(--_size))
        return true; //ʵʩɾ��
    if (!_hot)       //���ոձ�ɾ���Ľڵ�Ϊ���ڵ㣬�����úڣ������ºڸ߶�
    {
        _root->color = RB_BLACK;
        updateHeight(_root);
        return true;
    }

    //�����ȵĺ������Ȼƽ�⣬���������
    if (BlackHeightUpdated(*_hot))
        return true;
    if (IsRed(r))
    {
        r->color = RB_BLACK;
        r->height++;
        return true;
    }
    solveDoubleBlack(r);
    return true;
}

template <typename T>
void RedBlack<T>::solveDoubleBlack(BinNodePosi(T) r)
{
    // r�ĸ���
    BinNodePosi(T) p = r ? r->parent : _hot;
    if (!p)
        return;

    // r���ֵ�
    BinNodePosi(T) s = (r == p->lc) ? p->rc : p->lc;

    //�ֵ���Ϊ��
    if (IsBlack(s))
    {
        BinNodePosi(T) t = NULL;
        //s�ĺ캢��(�����Һ��ӽ�Ϊ�죬�������ȣ��Ժ�ʹΪNULL)
        if (IsRed(s->rc))
            t = s->rc;
        if (IsRed(r->lc))
            t = s->lc;
        if (t)
        {
            //��s�к캢�ӣ� BB-1
            RBColor oldColor = p->color; //����ԭ�������ڵ�p��ɫ
            //ͨ����ת��ƽ�⣬���������������Һ���Ⱦ��
            BinNodePosi(T) b = FromParentTo(*p) = rotateAt(t);
            if (HasLChild(*b))
            {
                b->lc->color = RB_BLACK;
                updateHeight(b->lc); //����
            }
            if (HasRChild(*b))
            {
                b->rc->color = RB_BLACK;
                updateHeight(b->rc);
            }
            b->color = oldColor;
            updateHeight(b);
        }
        else
        {
            //��s�޺캢��
            s->color = RB_RED;
            s->height--; //sת��
            if (IsRed(p))
            {
                //BB-2-R
                p->color = RB_BLACK;
            }
            else
            {
                //BB-2-B
                p->height--;
                solveDoubleBlack(p); //�ݹ�����
            }
        }
    }
    else
    {
        //�ֵ�sΪ��  BB-3
        s->color = RB_BLACK;
        p->color = RB_RED;

        //����ת����t��s��ͬ�࣬һ������ת������֮������ת��������
        BinNodePosi(T) t = IsLChild(*s) ? s->lc : s->rc;
        _hot = p;
        FromParentTo(*p) = rotateAt(t);
        solveDoubleBlack(r);
    }
}