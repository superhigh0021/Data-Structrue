#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Sort.h"
#include "Search.h"
using namespace std;

class Sort
{
public:
    void init(int a[]) //�����ֵ
    {
        srand(time(NULL));
        for (int N = 0; N < 20; N++)
            a[N] = rand();
    }
    friend void Heapify(int A[], int len, int k);
    friend void BuildHeap(int A[], int len);
    friend void HeapSort01(int A[], int len);
    friend void ShellSort(int A[], int len);

    int A[20]; //˳���
    int B[20]; //����
    int C[20]; //��������
};

class Search : public Sort
{
public:
    void BInit()
    {
        srand(time(NULL));
        T = newNode(time(NULL));
        for (int N = 0; N < 19; N++)
            T = insert(T, rand());
    }

    void HInit1() //��������ʼ������ͷ�������
    {
        H = new HashTable;
        H->next = H->nextlevel = NULL;
        int i = KEY - 1;
        while (i >= 0)
        {
            HashTable *p = new HashTable;
            p->key = i;
            p->value = -1;
            p->nextlevel = NULL;
            p->next = H->next;
            H->next = p;
            i--;
        }
    }

    void HInit2() //���Բ��ҷ���ʼ������ͷ��㵥ѭ������
    {
        int i = KEY - 1;
        H = new HashTable;
        H->key = 0;
        H->nextlevel = NULL;
        H->next = H;
        while (i > 0)
        {
            HashTable *p = new HashTable;
            p->key = i;
            p->value = -1;
            p->next = H->next;
            H->next = p;
            i--;
        }
    }

    void HAppend1(int i)
    {
        srand(time(NULL));
        while (i > 0)
        {
            HashTable *p = H->next;
            int value = rand();
            if (i == 5)
                a = value; //������Ԫ��
            while (value % KEY != p->key)
                p = p->next;
            if (p->value == -1)
                p->value = value;
            else
            {
                HashTable *p1 = new HashTable;
                p1->value = value;
                p1->nextlevel = p->nextlevel;
                p->nextlevel = p1;
            }
            i--;
        }
    }

    void HAppend2(int i) //i<=KEY
    {
        srand(time(NULL));
        while (i > 0)
        {
            HashTable *p = H;
            int value = rand();
            if (i == 5)
                a = value; //������Ԫ��
            while (value % KEY != p->key)
                p = p->next;
            while (p->value != -1)
                p = p->next;
            p->value = value;
            i--;
        }
    }

    friend BTNode *newNode(int key);
    friend int BinTreeSearch(BTNode *T, int value);
    friend int BinarySearch(int A[], int value, int low, int high);
    friend HashTable *HashSearch1(HashTable *H, int value);
    friend HashTable *HashSearch2(HashTable *H, int value);

    BTNode *T;
    HashTable *H;
    int a; //���汻����Ԫ��
};

void Show(int a[])
{
    for (int i = 0; i < 20; i++)
        cout << a[i] << " ";
    cout << endl;
}

int main()
{
    clock_t start, end;

    Sort S1;
    start = clock(); //ϣ������ + ���ֲ���
    S1.init(S1.A);
    for (int i = 0; i < 100000; i++)
        ShellSort(S1.A, 20);
    cout << BinarySearch(S1.A, S1.A[16], 0, 19);
    end = clock();
    cout << end - start << endl;
    Show(S1.A);

    start = clock(); //������
    S1.init(S1.B);
    for (int i = 0; i < 100000; i++)
        HeapSort01(S1.B, 20);
    end = clock();
    cout << end - start << endl;
    Show(S1.B);

    start = clock(); //��������
    S1.init(S1.C);
    for (int i = 0; i < 100000; i++)
        RadixSort(S1.C, 20);
    end = clock();
    cout << end - start << endl;
    Show(S1.C);

    Search S2;
    start = clock(); //����ƽ��������
    S2.BInit();
    cout << "���������";
    PreOrder(S2.T);
    cout << endl;
    cout << "���������";
    InOrder(S2.T);
    cout << endl;
    end = clock();

    start = clock(); //ɢ�б�������
    HashTable *p;
    S2.HInit1();
    S2.HAppend1(14);
    for (int i = 0; i < 100000000; i++)
        p = HashSearch1(S2.H, S2.a);
    cout << "\n"
         << p->value << endl;
    end = clock();
    cout << end - start << endl;

    start = clock(); //ɢ�б����Բ��ҷ�
    S2.HInit2();
    S2.HAppend2(14);
    for (int i = 0; i < 100000000; i++)
        p = HashSearch2(S2.H, S2.a);
    cout << "\n"
         << p->value << endl;
    end = clock();
    cout << end - start << endl;

    system("pause");
}