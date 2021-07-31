#include <iostream>
#include <vector>
using namespace std;

void percolate_down(vector<int>& v, int i, int n)
{
    while (i * 2 <= n - 1) {
        int j = i * 2 + 1;
        if (j < n && v[j] < v[j + 1])
            ++j;
        if (v[i] < v[j])
            swap(v[i], v[j]);
        i = j;
    }
}

void heap_sort(vector<int>& v)
{
    int n = v.size();
    for (int i = n / 2 - 1; i >= 0; --i) {
        percolate_down(v, i, n);
    }
    --n;
    while (n > 0) {
        swap(v[0], v[n--]);
        percolate_down(v, 0, n);
    }
}