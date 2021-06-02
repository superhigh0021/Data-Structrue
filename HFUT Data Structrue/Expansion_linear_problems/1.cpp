/*设计算法实现稀疏矩阵的运算应用
    1）设计稀疏矩阵类；
    2）给出测试用例，实现n组稀疏矩阵的相加与相乘。*/

#include "matrix.h"
using namespace std;

int main(void)
{
    vector<spmatrix> s = reset();
    vector<vector<vector<int>>> v; //稀疏矩阵的个数；第一层为稀疏矩阵，第二、三层为具体元素，辅助打印
    v.resize(s.size());
    for (int i = 0; i < v.size(); ++i)
    {
        v[i].resize(s[i].mu);
        for (int j = 0; j < s[i].mu; ++j)
            v[i][j].resize(s[i].nu);
    }
    insert(s, v);
    for(int i=0;i<v[0].size();++i){
        int count=0;
        for(auto j:v[0][i]){
            cout<<j<<' ';
            count++;
        }
    }

    system("pause");
    return 0;
}