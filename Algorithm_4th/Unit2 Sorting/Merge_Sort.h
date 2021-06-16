#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int>& v, vector<int>& aux, int lo, int mid, int hi)
{
    for (int i = lo; i <= hi; ++i)
        aux[i] = v[i]; //将待归并部分拷贝给辅助数组aux
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
    //一次辅助序列，减少每次归并时声明一个数组的开销
    vector<int> aux(v.size());
    _sort(v, aux, 0, aux.size() - 1);
}