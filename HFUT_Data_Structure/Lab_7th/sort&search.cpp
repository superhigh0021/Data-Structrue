#include<iostream>
#include <cstdlib>
#include"search.h"
#include"sort.h"
#include"Listsort.h"

#define random(a,b) (rand()%(b-a)+a)
using namespace std;
//生成随机数在0到10000的数组
void CreateRandom(int* Array, int n) {
    srand((int)time(0));  // 产生随机种子  把0换成NULL也行
    //全部初始化为0
    memset(Array, 0, n);
    for (int i = 1; i < n; i++)
        Array[i] = random(0, 1000);
}
void CompareSearch() {
    Search s;
    int key = 0;
    cout << "" << endl;
    cin >> key;
    int* Array = new int[10000];
    CreateRandom(Array, 10000);
    //顺序表的查找
    s.SeqSearch(Array, key, 10000);
    cout << "****************************" << endl;
    //平衡二叉树查找法
    s.AVLSearch(Array, key, 10000);
    cout << "****************************" << endl;
    //第一个哈希算法-开放地址法
    s.HashSearchM01(Array,key,10000);
    cout << "****************************" << endl;
    //第二个哈希算法-链地址法
    s.HashSearchM02(Array,key, 10000);
}
void CompareSort() {
    Sort s;
    int* Array01 = new int[10000];
    CreateRandom(Array01, 10000);
    int* Array02 = new int[10000];
    CreateRandom(Array02, 10000);
   s.MergeSort(Array01,0, 9999);
   s.Display(Array01);
   /*
    cout << "*******************************************" << endl;
    s.HeapSort(Array02,10000);*/
  // cout << "*******************************************" << endl;
    //CardinalitySort c;   //奇数排序
   // c._CardinalitySort();
}
int main(){
    CompareSearch();
    //CompareSort();

    system("pause");
    return 0;
}
