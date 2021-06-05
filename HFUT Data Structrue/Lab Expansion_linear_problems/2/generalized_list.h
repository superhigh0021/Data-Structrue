#pragma once

#include <iostream>
#include <string>
using namespace std;

struct GLNode
{
    //为0时该节点没有下一层，为1时有下一层
    bool tag;
    int num;//下一层的数量,在插入和删除时更新数据
    string name;       //姓名
    GLNode *up;        //上一层
    GLNode *nextlevel; //下一层
    GLNode *next;      //同一层的下一个节点
};
