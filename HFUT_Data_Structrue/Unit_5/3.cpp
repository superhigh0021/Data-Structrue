#include<iostream>
#include"List.h"
using namespace std;

int main(void){
    int a[]={1,1,2,2,2,3,4,5,5,5,6,6,7,7,8,8,8,9};
    List<int>l(a,18);
    l.DeleteSame();
    l.PrintTest();

    system("pause");
    return 0;
}