#pragma once

#include <iostream>
#include <string>
using namespace std;

struct GLNode
{
    //Ϊ0ʱ�ýڵ�û����һ�㣬Ϊ1ʱ����һ��
    bool tag;
    int num;//��һ�������
    string name;       //����
    GLNode *up;        //��һ��
    GLNode *nextlevel; //��һ��
    GLNode *next;      //ͬһ�����һ���ڵ�
};
