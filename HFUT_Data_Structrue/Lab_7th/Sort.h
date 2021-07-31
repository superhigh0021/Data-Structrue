#pragma once
#include<iostream>
using namespace std;
class Sort {
    /*<2> ���һ�������࣬�����ڴ���ʵ�����¹��ܣ�
    ��1�����ʵ�ֻ���˳���������㷨��1~2�֣� ��
    ��2�����ʵ�ֻ�������Ķ������㷨��
    ��3�����ʵ�ֻ�����ʽ���������㷨 ��
    ��4��������������������Ȳ�����N��N=10000�������ݣ����������㷨
               ����֤��������ʱ�����ĶԱȡ�
*/
    /****************************�鲢����*******************************/
    void Merge(int a[], int left, int right)
        /*�ϲ������������е�Ԫ��*/
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
    /*��source�����е�Ԫ�ظ��Ƶ�dest������.
       ����,len��Դ���鳤��,start��Ŀ��������ʼλ��*/
    void CopyArray(int source[], int dest[], int len, int start)
    {
        int i, j = start;
        for (i = 0; i < len; i++)
        {
            dest[j] = source[i];
            j++;
        }
    }
    /****************************������*******************************/
    void CreateHead(int Array[],int n) {
        //�����󶥶�
        for (int i = n / 2-1; i >= 0; i--)    //��n/2֮�䵽n-1֮���Ԫ�ص����ɷ��϶ѵ�Ҫ��
            AdjustHead(Array, i, n - 1);
    }
    void AdjustHead(int Array[], int s, int m) {
        //����s��mΪ�ѣ�ԭ���Ѿ��жѵĻ��������Բ���ȫ������
        int t=0, j=0;
        t = Array[s];   //���ڵ���ʱ������t��,��ô���ڵ�Ϳճ����ˣ����Բ������������п��ܳ��ֵĴ�����
        for (j = 2 * s + 1; j <= m; j *= 2 + 1) {   //����һ��һ�������ű�����ֻ������߼��ϵ���ȫ����������
            if (j < m && Array[j] < Array[j + 1]) {
                j++;        //ֻ���عؼ��ִ��������Ѱ��
            }
            if (t > Array[j]) {
                break;          //���ڵ�����亢�ӽ�㣬�����н���
            }
            Array[s] = Array[j];//���뿴�ų��󣬻�����״ͼһ�۾��ܿ�����̬�仯
            s = j;
        }
        Array[s] = t;       //�Ѹ��ڵ���뵽��ȷ��λ��
    }
public:
    //�鲢������ⲿ�ӿ�
    void MergeSort(int a[], int left, int right)
        /*�鲢����*/
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

    //������
    void HeapSort(int Array[],int n) {
        clock_t start, finish;
        start = clock();
        CreateHead(Array,n);
        int t = 0;
        for (int i = n - 1; i > 0; i--) {
            swap(Array[0], Array[i]);//������βԪ��,������i��nʵ���Ͼ����Ѿ��źõ�Ԫ��
            AdjustHead(Array, 0, i - 1);    //��0��i-1�����ɴ󶥶�
        }
        finish = clock();
        cout << endl << "�������ʱ������:" << double(finish - start) << "����" << endl;
        cout << "�ź����ǰ50��Ԫ��Ϊ:  " << endl;
        for (int i = 9999; i >9949; i--)
            cout << Array[i] << " ";

        cout << endl;
    }
    //ֻ��ӡÿ�������ǰ50��Ԫ�أ����������
    void Display(int Array[]) {
        cout << "�ź����ǰ50��Ԫ��Ϊ:  " << endl;
        for (int i = 0; i <50;i++) {
            cout << Array[i] << " ";
            if (i== 24)
                cout << endl;
        }
        cout << endl;
    }
};
