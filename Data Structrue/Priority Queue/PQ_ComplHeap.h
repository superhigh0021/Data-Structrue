#include "PQ.h"
#include "vector.h"

#define InHeap(n, i) (((-1) < (i)) && ((i) < (n))) //判断PQ[i]是否合法
#define Parent(i) ((i - 1) >> 1) //PQ[i]的父节点

//完全二叉堆一个节点必然有两个孩子，n是右边的，n-1是左边的，所以是n-1的parent
#define LastInternal(n) Parent(n - 1) //最后一个内部节点，即末节点的父亲
#define LChild(i) (1 + ((i) << 1)) //PQ[i]的左孩子
#define RChild(i) ((1 + (i)) << 1) //PQ[i]的右孩子
#define ParentValid(i) (0 < i) //判断PQ[i]是否有父亲
#define LChildValid(n, i) InHeap(n, LChild(i)) //判断PQ[i]是否有一个左孩子
#define RChildValid(n, i) InHeap(n, RChild(i)) //判断PQ[i]是否有两个孩子
#define Bigger(PQ, i, j) (lt(PQ[i], PQ[j]) ? j : i) //取大者

//父子(至多)三者中的大者
#define ProperParent(PQ, n, i)                                          \
        (RChildValid(n,i)? Bigger(PQ,Bigger(PQ,i,LChild(i)),Rchild(i)):\
        (LchildValid(n,i)?Bigger(PQ,i,LChild(i):i\
        )\
        )   //相等时父节点优先，如此可避免不必要的交换

template <typename T>
class PQ_ComplHeap : public PQ<T>, public Vector<T> {
protected:
    Rank percolateDown(Rank n, Rank i); //下滤
    Rank percolateUp(Rank i); //上滤
    void heapify(Rank n); //Floyd建堆算法
public:
    PQ_ComplHeap() { }
    //批量构造
    PQ_ComplHeap(T* A, Rank n)
    {
        copyFrom(A, 0, n);
        heapify(n);
    }
    void insert(T);
    T getMax();
    T delMax();
};

template <typename T>
T PQ_ComplHeap<T>::getMax() { return _elem[0]; }

template <typename T>
void PQ_ComplHeap<T>::insert(T e)
{
    Vector<T>::insert(e); //首先将新词条接到向量末尾
    percolateUp(_size - 1); //再对该词条实施上滤调整
}

template <typename T>
Rank PQ_ComplHeap<T>::percolateUp(Rank i)
{
    while (ParentValid(i)) {
        //只要i有父亲(尚未到达堆顶)
        Rank j = Parent(i);
        if (lt(_elem[i], _elem[j]))
            break; //一旦当前i小于他爹，上滤随即完成
        swap(_elem[i], _elem[j]); //否则交换父子，并且继续考察上面一层
        i = j;
    }
    return i;
}

template <typename T>
T PQ_ComplHeap<T>::delMax()
{
    //摘除堆顶，代之以末词条
    T maxElem = _elem[0];
    _elem[0] = _elem[--this->_size];
    //对新堆实施下滤
    percolateDown(_size, 0);
    return maxElem;
}

template <typename T>
Rank PQ_ComplHeap<T>::percolateDown(Rank n, Rank i)
{
    Rank j;
    //ProperParent返回_elem中i处最大的那一个,左右孩子都不存在的时候和自己最大的时候，返回自己
    while (i != (j = ProperParent(_elem, n, i))) {
        swap(_elem[i], _elem[j]);
        i = j;
    }
    return i;
}

//Floyd建堆算法
template <typename T>
void PQ_ComplHeap<T>::heapify(Rank n)
{
    for (int i  = LastInternal(n); InHeap(n, i); --i)
        percolateDown(n, i);
}

template <typename T>
void Vector<T>::heapSort(Rank lo, Rank hi)
{
    PQ_ComplHeap<T> H(_elem + lo, hi - lo);
    while(!H.empty())
        _elem[--hi]=H.delMax();
}