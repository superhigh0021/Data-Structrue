#include <iostream>
#include <vector>
using namespace std;

// int partition(vector<int> &v, int lo, int hi)
// {
//     int pivot = v[lo]; //—°»°÷·µ„
//     while (lo < hi)
//     {
//         while (lo < hi && v[hi] >= pivot)
//             --hi;
//         v[lo] = v[hi];
//         while (lo < hi && v[lo] <= pivot)
//             ++lo;
//         v[hi] = v[lo];
//     }
//     v[lo] = pivot;
//     return lo;
// }

int partition(vector<int> &v, int lo, int hi)
{
    int i = lo, j = hi, pivot = v[lo];
    while (true)
    {
        while (i <hi && v[i] <= pivot)
        {
            i++;
            if (v[i] > pivot)
                break;
        }
        while (j>lo && v[j] >= pivot)
        {
            --j;
            if (v[j] < pivot)
                break;
        }
        if (i >= j)
            break;
        swap(v[i], v[j]);
    }
    swap(v[lo],v[j]);
    return j;
}

void _sort(vector<int> &v, int lo, int hi)
{
    if (hi <= lo)
        return;
    int flag = partition(v, lo, hi);
    _sort(v, lo, flag);
    _sort(v, flag + 1, hi);
}