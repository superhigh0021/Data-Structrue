#include <iostream>
using namespace std;
#include <vector>

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

void heap_sort(vector<int>& v, int k)
{
    int n = v.size();
    for (int i = n / 2 - 1; i >= 0; --i) {
        percolate_down(v, i, n);
    }
    --n;
    int m = k;
    while (n > 0 && k > 0) {
        swap(v[0], v[n--]);
        percolate_down(v, 0, n);
        --k;
    }
    cout << v[v.size() - m];
}

void adjustHeap(int* A, int idx, int n)
{
    int ldx = 2 * idx + 1;
    int rdx = 2 * idx + 2;
    int maxdx = idx;

    if (idx <= n / 2) {
        if (ldx < n && A[ldx] > A[maxdx]) {
            maxdx = ldx;
        }

        if (rdx < n && A[rdx] > A[maxdx]) {
            maxdx = rdx;
        }

        if (maxdx != idx) {
            swap(A[idx], A[maxdx]);
            adjustHeap(A, maxdx, n);
        }
    }
}

int main(void)
{
    vector<int> v = { 7, 3, 2, 0, 1, 8, 5, 6, 4 };
    heap_sort(v, 3);

    system("pause");

    return 0;
}