#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<queue>
using namespace std;
#define range 10000     // ��������Ĵ�С 
class CardinalitySort {
	int* Array;		//�������������
public:
	int myrandom(int a[])    //���������� 
	{
		int max = 0;
		srand((unsigned)time(NULL));
		for (int i = 0; i < range; i++)
		{
			a[i] = rand() % range + 1;
			if (a[i] > max)
				max = a[i];
		}
		return max;
	}
	int Max_bit(int a)          //���������λ�� 
	{
		return a < 10 ? 1 : 1 + Max_bit(a / 10);
	}
	void RadixSort(int a[], int max_bit)      //�������� 
	{
		queue<int> temp[10];
		int mod = 10;
		int div = 1;
		int j = 0;
		int num = 0;
		for (int i = 0; i < max_bit; i++, mod *= 10, div *= 10)
		{

			for (j = 0; j < range; j++)
			{
				num = (a[j] % mod) / div;
				temp[num].push(a[j]);
			}
			int pos = 0;
			for (j = 0; j < 10; j++)
			{

				while (!temp[j].empty())
				{

					a[pos++] = temp[j].front();
					temp[j].pop();
				}
			}
		}
	}
	void _CardinalitySort() {
		clock_t start, end;           // ���ڲ��� ��ʱ 
		start = clock();
		int a[range];
		int max = myrandom(a);
		int bit_max = Max_bit(max);
		RadixSort(a, bit_max);
		for (int i = 0; i < range; i++)
		{
			cout << a[i] << " ";
			if ((i + 1) % 50 == 0)
				cout << endl;
		}
		end = clock();
		cout << range << "������ͨ�����������ʱ��" << (float)(end - start) * 1000.0 / CLOCKS_PER_SEC << "ms" << endl;
	}
};