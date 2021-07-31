#pragma once
#define NULLKEY -1
class HashTable {
    int* elem;           //数据元素存储地址，动态分配数组
    int HASHSIZE=0;      //定义散列表长为数组的长度
public:
    //对哈希表进行初始化
    HashTable(int HASHSIZE) {
        this->HASHSIZE = HASHSIZE;
        int i;
        this->elem = new int[HASHSIZE];
        for (i = 0; i < HASHSIZE; i++) {
            this->elem[i] = NULLKEY;   //初始化为-1
        }
    };
    //哈希表的插入函数，可用于构造哈希表
    void Insert( int data) {
        int hashAddress = data % HASHSIZE; //求哈希地址
        //发生冲突
        while (this->elem[hashAddress] != NULLKEY) {
            //利用开放定址法解决冲突，直到找到空位置位置
            hashAddress = (++hashAddress) % HASHSIZE;
        }
       this->elem[hashAddress] = data;
    }

    //哈希表的查找算法，
    //其实换汤不换药，就相当于一个相同的元素想要插入时得判断出插入位置，只不过查找的时候不需要插入
    //依次比较即可，若比较一圈回来了，说明不含有该元素
    int search(int data) {
        int hashAddress = data % HASHSIZE; //求哈希地址
        while (this->elem[hashAddress] != data) {//发生冲突
            //利用开放定址法解决冲突
            hashAddress = (++hashAddress) % HASHSIZE;
            //如果查找到的地址中数据为NULL，或者经过一圈的遍历回到原位置，则查找失败
            if (this->elem[hashAddress] == NULLKEY || hashAddress == data % HASHSIZE) {
                return -1;
            }
        }
        return hashAddress;
    }
};
