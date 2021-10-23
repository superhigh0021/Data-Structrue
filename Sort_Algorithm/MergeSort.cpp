#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void Merge(vector<T> &v, int lRank, int rRank) {
    int mid = (rRank + lRank) >> 1;
    vector<T> temp(rRank - lRank + 1);
    int i = lRank, j = mid + 1, k = 0;
    while (i <= mid && j <= rRank) {
        if (v[i] < v[j]) {
            temp[k++] = v[i++];
        } else {
            temp[k++] = v[j++];
        }
    }
    while (i <= mid) temp[k++] = v[i++];
    while (j <= rRank) temp[k++] = v[j++];
    for (int m = 0; m < temp.size(); ++m) v[lRank + m] = temp[m];
}

template <typename T>
void MergeSort(vector<T> &v, int lo, int hi) {
    if (lo == hi) return;
    int mid = (hi + lo) >> 1;
    MergeSort(v, lo, mid);
    MergeSort(v, mid + 1, hi);
    Merge(v, lo, hi);
}

int main(void) {
    vector<int> v = {1657, 4, 7, 83, 16, 3, 6, 9};
    MergeSort(v, 0, v.size() - 1);
    for (auto i : v) cout << i << ' ';
    
    return 0;
}