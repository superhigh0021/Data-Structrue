#pragma once
#include <ctime>
#include"ƽ�����������.hpp"
#include"��ϣ����-���Ŷ�ַ��.hpp"
#include"��ϣ����-����ַ��.hpp"
#include<iostream>
using namespace std;
class Search {
    /*<1> ���һ�������࣬�����ڴ���ʵ�����¹��ܣ�
    ��1�����ʵ�ֻ���˳���Ĳ����㷨��1~2�֣���
    ��2�����ʵ�ֻ�������Ĳ����㷨��1~2�֣���
    ��3�����ʵ��2�ֻ���ɢ�б�Ĳ����㷨��
    ��4��������������������Ȳ�����N��N=10000�������ݣ����������㷨
               ����֤��������ʱ�����ĶԱȡ�
*/
public:
    /********����˳���Ĳ���*****************/
    void SeqSearch(int Array[], int key, int ArrayLength) {
        clock_t start, finish;
        start = clock();
        if (Array != NULL) {
            int index = 0;
            for (int i = 0; i < ArrayLength; i++) {
                if (Array[i] == key)
                    cout << "���ҵ���" << ++index << "��" << key << "λ��:" << i + 1 << endl;
            }
        }
        finish = clock();
        cout << endl << "˳���Ĳ��ҵ�time cost is:" << double(finish - start) * 10000 << "����" << endl;
    }
    //�����Ҫ���ԣ�����൱�ڴ������ĳ���û���������������±���д���
    //���ֲ��ҵ�ǰ����������У��ܼ���,������������˸Ľ����ƽ��������ҷ�
    void BinarySearch(int Array[], int key, int low, int high) {
        int mid = (low + high) / 2;
        while (low <= high) {
            if (key > Array[mid])
                low = mid;
            else if (key < Array[mid])
                high = mid;
            else if (key == Array[mid])
                cout << "���ҵ���Ԫ��,λ��: " << mid + 1 << endl;
        }

    }
    /********************************************/
    /*********��������Ĳ���-ƽ�������**************/
    void AVLSearch(int Array[], int key, int n) {
        BSTree root = NULL, pos;
        bool taller;
        //�� nArr���ұ���ƽ������������ϲ������ݵĹ��̣�
        for (int i = 0; i < n; i++)
        {
            InsertAVL(&root, Array[i], &taller);
        }
        //����������
        //InorderTra(root);
        clock_t start, finish;
        start = clock();
        if (FindNode(root, key, &pos))
            cout << "���ҵ���Ԫ��" << endl;
        else
            cout << "δ���ҵ���Ԫ��" << endl;
        finish = clock();
        cout << endl << "ƽ����������ҷ���time cost is:" << double(finish - start) * 10000 << "����" << endl;
    }
    /***********************************************/
    /********��һ������ɢ�б�Ĳ����㷨*******************/
    void HashSearchM01(int Array[], int key, int n) {
        int i, result;
        HashTable hashTable(n);
        //���ò��뺯�������ϣ��
        for (i = 0; i < n; i++) {
            hashTable.Insert(Array[i]);
        }
        clock_t start, finish;
        start = clock();
        result = hashTable.search(key);
        if (result == -1)
            cout << "δ���ҵ���Ԫ��" << endl;
        else
            cout << "���ҵ���Ԫ�ص�λ��" << result + 1 << "λ��" << endl;
        finish = clock();
        cout << endl << "��һ����ϣ�㷨-���ŵ�ַ����time cost is:" << double(finish - start) * 10000 << "����" << endl;
    }
    /*****�ڶ�������ɢ�б�Ĳ����㷨**********int Array[],int n***/
    void HashSearchM02(int Array[], int key, int n) {
        _HashTable h;
        for (int i = 0; i < n; i++)
            h._Insert(Array[i]);
        clock_t start, finish;
        start = clock();
        int result = h.search(key);
        if (result == -1)
            cout << "δ���ҵ���Ԫ��" << endl;
        else
            cout << "���ҵ���Ԫ�ص�λ��" << result + 1 << "����" << endl;
        finish = clock();
        cout << endl << "�ڶ�����ϣ�㷨-����ַ����time cost is:" << double(finish - start) * 10000 << "����" << endl;
    }
};
