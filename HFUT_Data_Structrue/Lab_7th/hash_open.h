#pragma once
#define NULLKEY -1
class HashTable {
    int* elem;           //����Ԫ�ش洢��ַ����̬��������
    int HASHSIZE=0;      //����ɢ�б�Ϊ����ĳ���
public:
    //�Թ�ϣ����г�ʼ��
    HashTable(int HASHSIZE) {
        this->HASHSIZE = HASHSIZE;
        int i;
        this->elem = new int[HASHSIZE];
        for (i = 0; i < HASHSIZE; i++) {
            this->elem[i] = NULLKEY;   //��ʼ��Ϊ-1
        }
    };
    //��ϣ��Ĳ��뺯���������ڹ����ϣ��
    void Insert( int data) {
        int hashAddress = data % HASHSIZE; //���ϣ��ַ
        //������ͻ
        while (this->elem[hashAddress] != NULLKEY) {
            //���ÿ��Ŷ�ַ�������ͻ��ֱ���ҵ���λ��λ��
            hashAddress = (++hashAddress) % HASHSIZE;
        }
       this->elem[hashAddress] = data;
    }

    //��ϣ��Ĳ����㷨��
    //��ʵ��������ҩ�����൱��һ����ͬ��Ԫ����Ҫ����ʱ���жϳ�����λ�ã�ֻ�������ҵ�ʱ����Ҫ����
    //���αȽϼ��ɣ����Ƚ�һȦ�����ˣ�˵�������и�Ԫ��
    int search(int data) {
        int hashAddress = data % HASHSIZE; //���ϣ��ַ
        while (this->elem[hashAddress] != data) {//������ͻ
            //���ÿ��Ŷ�ַ�������ͻ
            hashAddress = (++hashAddress) % HASHSIZE;
            //������ҵ��ĵ�ַ������ΪNULL�����߾���һȦ�ı����ص�ԭλ�ã������ʧ��
            if (this->elem[hashAddress] == NULLKEY || hashAddress == data % HASHSIZE) {
                return -1;
            }
        }
        return hashAddress;
    }
};
