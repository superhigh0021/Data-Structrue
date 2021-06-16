#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int>& v, vector<int>& aux, int lo, int mid, int hi)
{
    for (int i = lo; i <= hi; ++i)
        aux[i] = v[i]; //�����鲢���ֿ�������������aux
    int i = lo, j = mid + 1;
    while (i <= mid && j <= hi) {
        if (aux[i] <= aux[j])
            v[lo++] = aux[i++];
        else
            v[lo++] = aux[j++];
    }
    while (i <= mid)
        v[lo++] = aux[i++];
    while (j <= hi)
        v[lo++] = aux[j++];
}

void _sort(vector<int>& v, vector<int>& aux, int lo, int hi)
{
    if (hi <= lo)
        return;
    int mid = (lo + hi) >> 1;
    _sort(v, aux, lo, mid);
    _sort(v, aux, mid + 1, hi);
    merge(v, aux, lo, mid, hi);
}

void _sort(vector<int>& v)
{
    //һ�θ������У�����ÿ�ι鲢ʱ����һ������Ŀ���
    vector<int> aux(v.size());
    _sort(v, aux, 0, aux.size() - 1);
}