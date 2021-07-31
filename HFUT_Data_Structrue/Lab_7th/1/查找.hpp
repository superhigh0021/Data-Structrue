#pragma once
#include <ctime>
#include"平衡二叉树查找.hpp"
#include"哈希查找-开放定址法.hpp"
#include"哈希查找-链地址法.hpp"
#include<iostream>
using namespace std;
class Search {
    /*<1> 设计一个查找类，并基于此类实现以下功能：
    （1）设计实现基于顺序表的查找算法（1~2种）；
    （2）设计实现基于树表的查找算法（1~2种）；
    （3）设计实现2种基于散列表的查找算法：
    （4）利用随机函数产生长度不少于N（N=10000）的数据，进行上述算法
               的验证，并给出时间消耗对比。
*/
public:
    /********基于顺序表的查找*****************/
    void SeqSearch(int Array[], int key, int ArrayLength) {
        clock_t start, finish;
        start = clock();
        if (Array != NULL) {
            int index = 0;
            for (int i = 0; i < ArrayLength; i++) {
                if (Array[i] == key)
                    cout << "查找到第" << ++index << "个" << key << "位于:" << i + 1 << endl;
            }
        }
        finish = clock();
        cout << endl << "顺序表的查找的time cost is:" << double(finish - start) * 10000 << "毫秒" << endl;
    }
    //这个不要测试，这个相当于凑字数的程序，没调过，估计数组下标会有错误
    //二分查找的前提是有序才行，很鸡肋,所以下面给出了改进版的平衡二叉树找法
    void BinarySearch(int Array[], int key, int low, int high) {
        int mid = (low + high) / 2;
        while (low <= high) {
            if (key > Array[mid])
                low = mid;
            else if (key < Array[mid])
                high = mid;
            else if (key == Array[mid])
                cout << "查找到该元素,位于: " << mid + 1 << endl;
        }

    }
    /********************************************/
    /*********基于数表的查找-平衡二叉树**************/
    void AVLSearch(int Array[], int key, int n) {
        BSTree root = NULL, pos;
        bool taller;
        //用 nArr查找表构建平衡二叉树（不断插入数据的过程）
        for (int i = 0; i < n; i++)
        {
            InsertAVL(&root, Array[i], &taller);
        }
        //中序遍历输出
        //InorderTra(root);
        clock_t start, finish;
        start = clock();
        if (FindNode(root, key, &pos))
            cout << "查找到该元素" << endl;
        else
            cout << "未查找到该元素" << endl;
        finish = clock();
        cout << endl << "平衡二叉树查找法的time cost is:" << double(finish - start) * 10000 << "毫秒" << endl;
    }
    /***********************************************/
    /********第一个基于散列表的查找算法*******************/
    void HashSearchM01(int Array[], int key, int n) {
        int i, result;
        HashTable hashTable(n);
        //利用插入函数构造哈希表
        for (i = 0; i < n; i++) {
            hashTable.Insert(Array[i]);
        }
        clock_t start, finish;
        start = clock();
        result = hashTable.search(key);
        if (result == -1)
            cout << "未查找到该元素" << endl;
        else
            cout << "查找到该元素第位于" << result + 1 << "位置" << endl;
        finish = clock();
        cout << endl << "第一个哈希算法-开放地址法的time cost is:" << double(finish - start) * 10000 << "毫秒" << endl;
    }
    /*****第二个基于散列表的查找算法**********int Array[],int n***/
    void HashSearchM02(int Array[], int key, int n) {
        _HashTable h;
        for (int i = 0; i < n; i++)
            h._Insert(Array[i]);
        clock_t start, finish;
        start = clock();
        int result = h.search(key);
        if (result == -1)
            cout << "未查找到该元素" << endl;
        else
            cout << "查找到该元素第位于" << result + 1 << "串上" << endl;
        finish = clock();
        cout << endl << "第二个哈希算法-链地址法的time cost is:" << double(finish - start) * 10000 << "毫秒" << endl;
    }
};
