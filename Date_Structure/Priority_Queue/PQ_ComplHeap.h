#include "PQ.h"
#include "../Vector/vector.h"

#define InHeap(n, i) (((-1) < (i)) && ((i) < (n))) //�ж�PQ[i]�Ƿ�Ϸ�
#define Parent(i) ((i - 1) >> 1) //PQ[i]�ĸ��ڵ�

//��ȫ�����һ���ڵ��Ȼ���������ӣ�n���ұߵģ�n-1����ߵģ�������n-1��parent
#define LastInternal(n) Parent(n - 1) //���һ���ڲ��ڵ㣬��ĩ�ڵ�ĸ���
#define LChild(i) (1 + ((i) << 1)) //PQ[i]������
#define RChild(i) ((1 + (i)) << 1) //PQ[i]���Һ���
#define ParentValid(i) (0 < i) //�ж�PQ[i]�Ƿ��и���
#define LChildValid(n, i) InHeap(n, LChild(i)) //�ж�PQ[i]�Ƿ���һ������
#define RChildValid(n, i) InHeap(n, RChild(i)) //�ж�PQ[i]�Ƿ�����������
#define Bigger(PQ, i, j) (lt(PQ[i], PQ[j]) ? j : i) //ȡ����

//����(����)�����еĴ���
#define ProperParent(PQ, n, i)                                          \
        (RChildValid(n,i)? Bigger(PQ,Bigger(PQ,i,LChild(i)),Rchild(i)):\
        (LchildValid(n,i)?Bigger(PQ,i,LChild(i):i\
        )\
        )   //���ʱ���ڵ����ȣ���˿ɱ��ⲻ��Ҫ�Ľ���

template <typename T>
class PQ_ComplHeap : public PQ<T>, public Vector<T> {
protected:
    Rank percolateDown(Rank n, Rank i); //����
    Rank percolateUp(Rank i); //����
    void heapify(Rank n); //Floyd�����㷨
public:
    PQ_ComplHeap() { }
    //��������
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
    Vector<T>::insert(e); //���Ƚ��´����ӵ�����ĩβ
    percolateUp(_size - 1); //�ٶԸô���ʵʩ���˵���
}

template <typename T>
Rank PQ_ComplHeap<T>::percolateUp(Rank i)
{
    while (ParentValid(i)) {
        //ֻҪi�и���(��δ����Ѷ�)
        Rank j = Parent(i);
        if (lt(_elem[i], _elem[j]))
            break; //һ����ǰiС�������������漴���
        swap(_elem[i], _elem[j]); //���򽻻����ӣ����Ҽ�����������һ��
        i = j;
    }
    return i;
}

template <typename T>
T PQ_ComplHeap<T>::delMax()
{
    //ժ���Ѷ�����֮��ĩ����
    T maxElem = _elem[0];
    _elem[0] = _elem[--this->_size];
    //���¶�ʵʩ����
    percolateDown(_size, 0);
    return maxElem;
}

template <typename T>
Rank PQ_ComplHeap<T>::percolateDown(Rank n, Rank i)
{
    Rank j;
    //ProperParent����_elem��i��������һ��,���Һ��Ӷ������ڵ�ʱ����Լ�����ʱ�򣬷����Լ�
    while (i != (j = ProperParent(_elem, n, i))) {
        swap(_elem[i], _elem[j]);
        i = j;
    }
    return i;
}

//Floyd�����㷨
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