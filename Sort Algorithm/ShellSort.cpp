//改进版的插入排序，效率高一点，但是因为是跳着比较，所以不稳定
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void ShellSort(T &v, int size) {
    for (int gap = size >> 1; gap > 0; gap = gap >> 1) {
        for (int i = gap; i < size; ++i) {
            for (int j = i; j > gap - 1; j -= gap) {
                if (v[j - gap] > v[j]) swap(v[j], v[j - gap]);
            }
        }
    }
}

int main(void) {
    vector<int> v = {9, 6, 11, 3, 5, 12, 8, 7, 10, 15, 14, 4, 1, 13, 2};
    ShellSort(v, v.size());
    for (auto i : v) cout << i << ' ';

    return 0;
}