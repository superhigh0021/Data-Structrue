#include <iostream>
#include "BinNode.h"
#include "BinNode_macro_BASIC.h"
using namespace std;

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLc(const T &e)
{
    return this->lc = new BinNode(e, this);
}

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRc(const T &e)
{
    return this->rc = new BinNode(e, this);
}

template <typename T>
int BinNode<T>::size()
{
    int s = 1;
    if (lc)
        s += lc->size();
    if (rc)
        s += rc->size();

    return s;
}

template <typename T>
template <typename VST>
void BinNode<T>::travIn(VST &visit)
{
    switch (rand() % 5)
    {
    case 1:
        travIn_I1(this, visit);
        break; //µü´ú°æ#1
    case 2:
        travIn_I2(this, visit);
        break; //µü´ú°æ#2
    case 3:
        travIn_I3(this, visit);
        break; //µü´ú°æ#3
    case 4:
        travIn_I4(this, visit);
        break; //µü´ú°æ#4
    default:
        travIn_R(this, visit);
        break; //µÝ¹é°æ
    }
}

template <typename T>
BinNodePosi(T) BinNode<T>::succ()
{
    BinNodePosi(T) s = this;
    if (rc)
    {
        s = rc;
        while (HasLChild(*s))
            s = s->lc;
    }
    else
    {
        while (IsRChild(*s))
            s = s->parent;
        s = s->parent;
    }
    return s;
}