#include "Merge_Sort.h"
#include"Quick_Sort.h"
#include"Heap_Sort.h"
using namespace std;

void Merge_test(){
    vector<int> v = { 5, 6, 3, 2, 12, 94, 12, 62, 45 };
    _sort(v);
    for (auto i : v)
        cout << i << ' ';
    cout << endl;
}

void Quick_test(){
    vector<int> v = { 100,5, 6, 3, 2, 12, 94, 12, 62, 45,1234 };
    _sort(v,0,v.size()-1);
    for (auto i : v)
        cout << i << ' ';
    cout << endl;
}

void heap_test(){
    vector<int> v = { 13,20 };
    heap_sort(v);
    for (auto i : v)
        cout << i << ' ';
    cout << endl;
} 

int main(void)
{
    //Merge_test();
    //Quick_test();
    heap_test();

    system("pause");
    return 0;

}