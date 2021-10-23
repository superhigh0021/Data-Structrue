#include <iostream>
using namespace std;
#include <vector>

// template <typename T>
// int partition(vector<T> &v, int lo, int hi) {
//     //swap(v[lo], v[lo + rand() % (hi - lo + 1)]);
//     T pivot = v[lo];  //�����ѡȡ
//     while (lo < hi) {
//         while ((lo < hi) && (pivot <= v[hi])) hi--;
//         v[lo] = v[hi];
//         while ((lo < hi) && (v[lo] <= pivot)) lo++;
//         v[hi] = v[lo];
//     }
//     v[lo]=pivot;
//     return lo;
// }

// template <typename T>
// void QuickSort(vector<T> &v, int lo, int hi) {
//     if (hi - lo < 2) return;
//     int mi = partition(v, lo, hi);
//     QuickSort(v,lo, mi);
//     QuickSort(v,mi + 1, hi);
// }

template <typename T>
int partition(vector<T>& v, int lo, int hi) {
    T pivot = v[lo];
    while (lo < hi) {
        while (lo < hi && v[hi] >= pivot) --hi;
        v[lo] = v[hi];
        while (lo < hi && v[lo] <= pivot) ++lo;
        v[hi] = v[lo];
    }
    v[lo] = pivot;
    return lo;
}

template <typename T>
void QuickSort(vector<T>& v, int lo, int hi) {
    if (hi - lo < 2) return;
    int mi=partition(v,lo,hi);
    QuickSort(v,lo,mi);
    QuickSort(v,mi+1,hi);
}

int main(void) {
    vector<int> v = {5, 72, 696, 51, 26, 83, 45, 2, 54};
    QuickSort(v, 0, v.size() - 1);

    for (auto i : v) cout << i << ' ';


    return 0;
}