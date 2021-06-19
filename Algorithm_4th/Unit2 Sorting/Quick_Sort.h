#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int>& v, int lo, int hi)
{
    int pivot = v[lo], i = lo, j = hi;
    while (i < j) {
        while (i < hi && v[i] <= pivot)
            ++i;
        while (j > lo && v[j] >= pivot)
            --j;
        if (i < j)
            swap(v[i], v[j]);
    }
    swap(v[lo], v[j]);
    return j;
}

void _sort(vector<int>& v, int lo, int hi)
{
    if (hi <= lo)
        return;
    int mi = partition(v, lo, hi);
    _sort(v, lo, mi);
    _sort(v, mi + 1, hi);
}