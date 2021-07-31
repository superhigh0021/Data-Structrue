#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int>& v, vector<int>& aux, int lo, int mi, int hi)
{
    for (int i = lo; i <=hi; ++i)
        aux[i] = v[i];
    int i = lo, k = lo, j = mi + 1;
    while (i <= mi && j <= hi) {
        if (aux[i] <= aux[j])
            v[k++] = aux[i++];
        else if (aux[i] > aux[j])
            v[k++] = aux[j++];
    }
    while (i <= mi)
        v[k++] = aux[i++];
    while (j <= hi)
        v[k++] = aux[j++];
}

void _sort(vector<int>& v, vector<int>& aux, int lo, int hi)
{
    if (hi <= lo)
        return;
    int mi = (lo + hi) >> 1;
    _sort(v, aux, lo, mi);
    _sort(v, aux, mi + 1, hi);
    merge(v, aux, lo, mi, hi);
}

void _sort(vector<int>& v)
{
    vector<int> aux(v.size());
    _sort(v, aux, 0, v.size() - 1);
}