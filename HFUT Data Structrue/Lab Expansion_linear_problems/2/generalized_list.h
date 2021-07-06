#pragma once

#include <iostream>
#include <string>
using namespace std;

struct GLNode
{
    int num=0;//下一层的数量,在插入和删除时更新数据
    string name;       //姓名
    GLNode *up=nullptr;        //上一层
    GLNode *nextlevel=nullptr; //下一层
    GLNode *next=nullptr;      //同一层的下一个节点
    GLNode *next_direct=nullptr;
    GLNode *up_direct=nullptr;
    bool direct_flag=false;
};
