/*通过运算符重载实现两矩阵的加、减运算*/

#include <iostream>
#include <vector>
using namespace std;

void operator +(vector<vector<int> >v1,vector<vector<int> >v2){
    for(int i=0;i<v1.size();++i){
        for(int j=0;j<v1[i].size();++j){
            cout<<v1[i][j]+v2[i][j]<<' ';
        }
        cout<<endl;
    }
}

void operator -(vector<vector<int> >v1,vector<vector<int> >v2){
    for(int i=0;i<v1.size();++i){
        for(int j=0;j<v1[i].size();++j){
            cout<<v1[i][j]-v2[i][j]<<' ';
        }
        cout<<endl;
    }
}

int main(void)
{
    vector<vector<int> > v1 = { { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
        { 2, 3, 4, 5, 6, 7, 8, 9, 10 },
        { 3, 4, 5, 6, 7, 8, 9, 10, 11 } };
    vector<vector<int> > v2 = { { 9, 8, 7, 6, 5, 4, 3, 2, 1 },
        { 10, 9, 8, 7, 6, 5, 4, 3, 2 },
        { 11, 10, 9, 8, 7, 6, 5, 4, 3 } };
    
    v1+v2;
    cout<<endl<<endl;
    v1-v2;

    system("pause");
    return 0;
}