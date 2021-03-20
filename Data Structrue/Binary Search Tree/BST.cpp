#include "BST.h"

#include <iostream>
using namespace std;

template <typename T>
    static BinNodePosi(T) & serchIn(BinNodePosi(T) & v, const T& e, BinNodePosi(T) & hot)
{
    if (!v || (e == v->data))
        return v;
    hot = v;
    return searchIn(((e < v->data) ? v->lc : v->rc), e, hot);
}

template <typename T>
    BinNodePosi(T) & BST<T>::search(const T& e)
{
    return searchIn(_root, e, _hot = NULL);
}