#include <iostream>
#include <string>
#include "BinTree.h"
using namespace std;

const int KEY = 15;

struct HashTable
{
    int key; //����ʮ����
    int value;
    HashTable *next;
    HashTable *nextlevel; //������
};

//���ֲ���
int BinarySearch(int A[], int value, int low, int high)
{
    int mid = (low + high) / 2;
    if (A[mid] == value)
        return mid;
    else if (A[mid] > value)
        return BinarySearch(A, value, low, mid - 1);
    else
        return BinarySearch(A, value, mid + 1, high);
}

// //����������
// int BinTreeSearch(BTNode *T, int value)
// {
//     BTNode *p = T;
//     if (p->key != value)
//         ;
// }

//ɢ�в��ң���������
HashTable *HashSearch1(HashTable *H, int value)
{
    HashTable *p = H;
    while (value % KEY != p->key)
        p = p->next;
    while (p->value != value)
        p = p->nextlevel;
    return p;
}

//ɢ�в��ң����Բ��ҷ���
HashTable *HashSearch2(HashTable *H, int value)
{
    HashTable *p = H;
    while (value % KEY != p->key)
        p = p->next;
    while (p->value != value)
        p = p->next;
    return p;
}

//KMP�㷨
int *buildNext(string P)
{
    size_t m = P.size(), j = 0;
    int *N = new int[m];
    int t = N[0] = -1;
    while (j < m - 1)
        if (0 > t || P[j] == P[t])
        {
            j++;
            t++;
            N[j] = t;
        }
        else
            t = N[t];
    return N;
}

int match(string T, string P) //TΪĸ����PΪ�Ӵ�
{
    int *next = buildNext(P);
    int n = T.size(), i = 0;
    int m = P.size(), j = 0;
    while (j < m && i < n)
        if (0 > j || T[i] == P[j])
        {
            i++;
            j++;
        }
        else
            j = next[j];
    delete[] next;
    return i - j;
}