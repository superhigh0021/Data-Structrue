#include "Heap_Sort.h"
#include "Merge_Sort.h"
#include "Quick_Sort.h"
using namespace std;

void Merge_test()
{
    vector<int> v = { 5, 6, 3, 2, 12, 94, 12, 62, 45 };
    _sort(v);
    for (auto i : v)
        cout << i << ' ';
    cout << endl;
}

void Quick_test()
{
    vector<int> v = { 100, 5, 6, 3, 0, 2, 12, 94, 12, 62, 45, 1234 };
    _sort(v, 0, v.size() - 1);
    for (auto i : v)
        cout << i << ' ';
    cout << endl;
}

void heap_test()
{
    vector<int> v = { 7, 3, 2, 0, 1, 8, 5, 6, 4 };
    heap_sort(v);
    for (auto i : v)
        cout << i << ' ';
    cout << endl;
}

int main(void)
{
    Merge_test();
    //Quick_test();
    //heap_test();

    return 0;
}