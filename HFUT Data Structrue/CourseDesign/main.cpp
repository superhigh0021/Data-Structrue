/*
题 20：散列表的设计与实现 
问题描述：设计散列表实现电话号码查找系统。 
实现要求： 
1) 设每个记录有下列数据项：用户名、电话号码、地址； 
2) 从键盘输入各记录，以用户名（汉语拼音形式）为关键字建立散列表；
3) 采用一定的方法解决冲突； 
4) 查找并显示给定电话号码的记录； 
5) （选作）设计不同的散列函数，比较冲突率； 
6) （选作）在散列函数确定的前提下，尝试各种不同类型处理冲突的方法， 
考察平均查找长度的变化。 */

#include "hashtable.h"
#include <iostream>
#include<string>
using namespace std;

void test01(){
    Hashtable<string,long long>h;
    string a;
    long long b;
    do{
        cin>>b>>a;
        h.put(a,b);
    }while(getchar()!='#');
    cout<<*(h.get("wangwu"));
}

int main(void){
    test01();

    system("pause");
    return 0;
}
