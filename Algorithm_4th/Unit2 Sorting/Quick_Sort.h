#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int>& v, int lo, int hi)
{
    int pivot = v[lo];
    while (lo < hi) {
        while (lo < hi && v[lo] <= pivot)
            ++lo;
        v[hi] = v[lo];
        while (lo < hi && v[hi] >= pivot)
            --hi;
        v[lo]=v[hi];
    }
}

void _sort(vector<int>& v, int lo, int hi)
{
    if (hi <= lo)
        return;
    int flag = partition(v, lo, hi);
    _sort(v, lo, flag);
    _sort(v, flag + 1, hi);
}