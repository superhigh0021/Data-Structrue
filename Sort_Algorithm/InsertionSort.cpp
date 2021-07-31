#include<iostream>
#include<vector>
using namespace std;

template<typename T>
void InsertionSort(T &a,int size){
    for(int i=1;i<size;++i){
        for(int j=i;j>0;--j){
            if(a[j-1]>a[j])
            swap(a[j],a[j-1]);
        }
    }
}

int main(void){
    vector<int>v={1,2,19,58,35};
    InsertionSort(v,v.size());
    for(auto i:v)
    cout<<i<<' ';
    
    system("pause");
    return 0;
}
