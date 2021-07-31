#include<iostream>
#include<deque>
using namespace std;

void convert(int A[],int size){
    deque<int>d;
    for(int i=0;i<size;++i){
        if(A[i]%2==0)d.push_back(A[i]);
        else d.push_front(A[i]);
    }
    for(int i=0;i<size;++i)
    A[i]=d[i];
}

int main(void){
    int A[]={1,6,7,9,16,15,83,49,52,61};
    convert(A,10);
    for(auto i:A)  cout<<i<<' ';

    system("pause");
    return 0;
}