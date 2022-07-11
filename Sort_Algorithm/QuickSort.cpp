#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int>& vec, int lo, int hi) {
    int pivot = vec[hi], temp = lo - 1;
    for (int i = lo; i < hi; ++i)
        if (vec[i] <= pivot)
            swap(vec[++temp], vec[i]);
    swap(vec[temp + 1], vec[hi]);
    return temp + 1;
}

void quickSort(vector<int>& vec, int lo, int hi) {
    if (lo >= hi)
        return;
    int pivot = partition(vec, lo, hi);
    quickSort(vec, lo, pivot - 1);
    quickSort(vec, pivot + 1, hi);
}

void quickSort(vector<int>& vec) {
    quickSort(vec, 0, vec.size() - 1);
}