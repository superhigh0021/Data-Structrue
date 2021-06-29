#include <iostream>
#include <cmath>
using namespace std;

//冒泡排序
void BubbleSort(int A[], int m)
{
    int x;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m - 1; j++)
        {
            if (A[j] > A[j + 1])
            {
                x = A[j];
                A[j] = A[j + 1];
                A[j + 1] = x;
            }
        }
    }
}

//选择排序
void ChooseSort(int A[], int m)
{
    int x = 0;
    for (int i = 0; i < m; i++)
    {
        int min = i;
        for (int j = i + 1; j < m; j++)
        {
            if (A[j] < A[min])
                min = j;
        }
        x = A[i];
        A[i] = A[min];
        A[min] = x;
    }
}

//插入排序
void InsertSort(int A[], int m)
{
    int current, pre;
    for (int i = 1; i < m; i++)
    {
        pre = i - 1;
        current = A[i];
        while (pre >= 0 && A[pre] > current)
        {
            A[pre + 1] = A[pre];
            pre--;
        }
        A[pre + 1] = current;
    }
    return;
}

//希尔排序
void ShellSort(int A[], int len) //m==length
{
    for (int gap = len >> 1; gap > 0; gap = gap >> 1)
    {
        for (int i = gap; i < len; i++)
        {
            for (int j = i; j > gap - 1; j -= gap)
            {
                if (A[j - gap] > A[j])
                    swap(A[j], A[j - gap]);
            }
        }
    }
}

//归并排序
int *B = (int *)malloc(9 * sizeof(int)); //辅助数组

void Merge(int A[], int low, int mid, int high)
{
    int i, j, k;
    for (k = low; k <= high; k++) //给辅助空间赋值
        B[k] = A[k];
    for (i = low, j = mid + 1, k = i; i <= mid && j <= high; k++) //给两个分组整体排序
    {
        if (B[i] <= B[j])
            A[k] = B[i++];
        else
            A[k] = B[j++];
    }
    //数量较多的那个数组分量赋值
    while (i <= mid)
        A[k++] = B[i++];
    while (j <= high)
        A[k++] = B[j++];
}

void MergeSort(int A[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        MergeSort(A, low, mid);
        MergeSort(A, mid + 1, high);
        Merge(A, low, mid, high);
    }
}

//快速排序
int Partrition(int A[], int low, int high) //每执行一次确定pivot的位置
{
    int pivot = A[low];
    while (low < high)
    {
        while (low < high && A[high] >= pivot) //更换大于小于号可以改变排序方向
            high--;
        A[low] = A[high];
        while (low < high && A[low] <= pivot)
            low++;
        A[high] = A[low];
    }
    A[low] = pivot;
    return low;
}

void QuickSort(int A[], int low, int high)
{
    if (low < high)
    {
        int partrition = Partrition(A, low, high);
        QuickSort(A, low, partrition);
        QuickSort(A, partrition + 1, high);
        return;
    }
}

//堆的算法
//由下至上的堆有序化（上浮）的实现
void swim(int A[], int k)
{
    while (k > 1 && A[k / 2] < A[k])
    {
        swap(A[k / 2], A[k]);
        k = k / 2;
    }
}
//由上至下的堆有序化（下沉）的实现
void sink(int A[], int k, int len)
{
    while (2 * k + 1 < len)
    {
        int j = 2 * k + 1;
        if (A[j] <= A[j + 1])
            j++;
        if (A[k] > A[j])
            break;
        swap(A[k], A[j]);
        k = j;
    }
}

//堆排序
void HeapSort(int A[], int len)
{
    int N = len - 1;
    for (int k = N / 2 - 1; k >= 0; k--)
        sink(A, k, N);
    while (N > 0)
    {
        swap(A[0], A[N--]);
        sink(A, 0, N);
    }
}

//堆排序易懂版
void Heapify(int A[], int len, int k)
{
    if (k >= len)
        return;
    int lc = 2 * k + 1;
    int rc = 2 * k + 2;
    int max = k;
    if (lc < len && A[lc] > A[max])
        max = lc;
    if (rc < len && A[rc] > A[max])
        max = rc;
    if (max != k)
    {
        swap(A[max], A[k]);
        Heapify(A, len, max);
    }
}

void BuildHeap(int A[], int len)
{
    int last_node = len - 1;
    int parent = (last_node - 1) / 2;
    for (int i = parent; i >= 0; i--)
        Heapify(A, len, i);
}

void HeapSort01(int A[], int len)
{
    BuildHeap(A, len);
    for (int i = len - 1; i >= 0; i--)
    {
        swap(A[i], A[0]);
        Heapify(A, i, 0);
    }
}

//计数排序
//桶排序
//基数排序
int maxbit(int data[], int len) //辅助数组，求数组的最大位数
{
    int maxData = data[0]; //最大数
    for (int i = 1; i < len; i++)
    {
        if (maxData < data[i])
            maxData = data[i];
    }
    int d = 1;
    int p = 10;
    while (maxData >= p)
    {
        //p*=10  Maybe OverFlow
        maxData /= 10;
        ++d;
    }
    return d;
}

void RadixSort(int A[], int len)
{
    int d = maxbit(A, len);
    int *tmp = new int[len];
    int *count = new int[10]; //计数器
    int i, j, k;
    int radix = 1;
    for (i = 0; i <= d; i++) //进行d次排序
    {
        for (j = 0; j < 10; j++)
            count[j] = 0; //每次分配前清空计数器
        for (j = 0; j < len; j++)
        {
            k = (A[j] / radix) % 10;
            count[k]++;
        }
        for (j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
        for (j = len - 1; j >= 0; j--)          //将所有桶中记录依次收集到tmp中
        {
            k = (A[j] / radix) % 10;
            tmp[count[k] - 1] = A[j];
            count[k]--;
        }
        for (j = 0; j < len; j++)
            A[j] = tmp[j];
        radix = radix * 10;
    }
    delete[] tmp;
    delete[] count;
}