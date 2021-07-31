#pragma once
#include<iostream>
using namespace std;
class Sort {
    /*<2> 设计一个排序类，并基于此类实现以下功能：
    （1）设计实现基于顺序表的排序算法（1~2种） ；
    （2）设计实现基于树表的堆排序算法；
    （3）设计实现基于链式基数排序算法 ；
    （4）利用随机函数产生长度不少于N（N=10000）的数据，进行上述算法
               的验证，并给出时间消耗对比。
*/
    /****************************归并排序*******************************/
    void Merge(int a[], int left, int right)
        /*合并两个子序列中的元素*/
    {
        int begin1, begin2, mid, k = 0, len, * b;
        begin1 = left;
        mid = (left + right) / 2;
        begin2 = mid + 1;
        len = right - left + 1;
        b = (int*)malloc(len * sizeof(int));
        while (begin1 <= mid && begin2 <= right)
        {
            if (a[begin1] <= a[begin2])
                b[k++] = a[begin1++];
            else
                b[k++] = a[begin2++];
        }
        while (begin1 <= mid)
            b[k++] = a[begin1++];
        while (begin2 <= right)
            b[k++] = a[begin2++];
        CopyArray(b, a, len, left);
        free(b);
    }
    /*将source数组中的元素复制到dest数组中.
       其中,len是源数组长度,start是目标数组起始位置*/
    void CopyArray(int source[], int dest[], int len, int start)
    {
        int i, j = start;
        for (i = 0; i < len; i++)
        {
            dest[j] = source[i];
            j++;
        }
    }
    /****************************堆排序*******************************/
    void CreateHead(int Array[],int n) {
        //建立大顶堆
        for (int i = n / 2-1; i >= 0; i--)    //将n/2之间到n-1之间的元素调整成符合堆的要求
            AdjustHead(Array, i, n - 1);
    }
    void AdjustHead(int Array[], int s, int m) {
        //调整s到m为堆，原来已经有堆的基础，所以不用全部调整
        int t=0, j=0;
        t = Array[s];   //根节点暂时保存在t中,那么根节点就空出来了，可以插入下面子树中可能出现的大结点了
        for (j = 2 * s + 1; j <= m; j *= 2 + 1) {   //不用一个一个紧挨着遍历，只需遍历逻辑上的完全二叉树即可
            if (j < m && Array[j] < Array[j + 1]) {
                j++;        //只在沿关键字大的子树中寻找
            }
            if (t > Array[j]) {
                break;          //根节点大于其孩子结点，不进行交换
            }
            Array[s] = Array[j];//代码看着抽象，画个树状图一眼就能看懂动态变化
            s = j;
        }
        Array[s] = t;       //把根节点插入到正确的位置
    }
public:
    //归并排序的外部接口
    void MergeSort(int a[], int left, int right)
        /*归并排序*/
    {
        int i;
        if (left < right)
        {
            i = (left + right) / 2;
            MergeSort(a, left, i);
            MergeSort(a, i + 1, right);
            Merge(a, left, right);
        }
    }

    //堆排序
    void HeapSort(int Array[],int n) {
        clock_t start, finish;
        start = clock();
        CreateHead(Array,n);
        int t = 0;
        for (int i = n - 1; i > 0; i--) {
            swap(Array[0], Array[i]);//交换首尾元素,数组中i到n实际上就是已经排好的元素
            AdjustHead(Array, 0, i - 1);    //将0到i-1调整成大顶堆
        }
        finish = clock();
        cout << endl << "堆排序的时间消耗:" << double(finish - start) << "毫秒" << endl;
        cout << "排好序的前50个元素为:  " << endl;
        for (int i = 9999; i >9949; i--)
            cout << Array[i] << " ";

        cout << endl;
    }
    //只打印每个数组的前50个元素，供检查正误
    void Display(int Array[]) {
        cout << "排好序的前50个元素为:  " << endl;
        for (int i = 0; i <50;i++) {
            cout << Array[i] << " ";
            if (i== 24)
                cout << endl;
        }
        cout << endl;
    }
};
