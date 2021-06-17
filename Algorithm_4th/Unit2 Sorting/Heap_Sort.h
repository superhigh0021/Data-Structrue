#include <iostream>
#include <vector>
using namespace std;

void percolate_down(vector<int>& v, int k, int n)
{
    while (k * 2 <= n - 1) {
        int j = 2 * k + 1;
        if (j< n && v[j] < v[j + 1])
            ++j;
        if (v[j] <= v[k])
            break;
        swap(v[j], v[k]);
        k = j;
    }
}

void heap_sort(vector<int>& v)
{
    int n = v.size();
    for (int k = n / 2 - 1; k >= 0; --k) {
        percolate_down(v, k, n);
    }
    --n;
    while (n > 0) {
        swap(v[0], v[n--]);
        percolate_down(v, 0, n);
    }
}