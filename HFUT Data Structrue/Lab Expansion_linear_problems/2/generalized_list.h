#pragma once

#include <iostream>
#include <string>
using namespace std;

struct GLNode
{
    int num=0;//��һ�������,�ڲ����ɾ��ʱ��������
    string name;       //����
    GLNode *up=nullptr;        //��һ��
    GLNode *nextlevel=nullptr; //��һ��
    GLNode *next=nullptr;      //ͬһ�����һ���ڵ�
};
