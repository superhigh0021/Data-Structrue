#define maxnum 10
using namespace std;

#include <vector>
#include <iostream>

struct Tuple
{
    int i, j;  //元素的行列下标
    int value; //元素的值
};

typedef struct
{
    int mu, nu, tu; //元素的行数、列数、非零元素个数
    Tuple data[maxnum];
} spmatrix;

vector<spmatrix> reset()
{
    int num;
    cout << "你要创建多少个矩阵？" << endl;
    cin >> num;
    vector<spmatrix> s;
    s.resize(num);
    cout << "你要创建矩阵的行数列数分别为多少？" << endl;
    int mu, nu;
    cin >> mu >> nu;
    for (int i = 0; i < num; ++i)
    {
        s[i].mu = mu;
        s[i].nu = nu;
    }
    for (int i = 0; i < num; ++i)
    {
        cout << "第" << i + 1 << "个矩阵的非零元素个数：";
        int num_of_nzero;
        cin >> num_of_nzero;
        s[i].tu = num_of_nzero;
    }
    return s;
}

void insert(vector<spmatrix> &s, vector<vector<vector<int>>> &v)
{
    int num = s.size();
    for (int m = 0; m < num; ++m)
    {
        int num_of_nzero = s[m].tu;
        for (int n = 0; n < num_of_nzero; ++n)
        {
            int i, j, value;
            cout << "你创建的第" << m + 1 << "个矩阵非零元素的行列和元素值分别为：";
            cin >> i >> j >> value;
            s[m].data[n].i = i; //第n个非零元素的行标
            s[m].data[n].j = j; //第n个非零元素的列标
            s[m].data[n].value = value;
        }
    }
    for (int i = 0; i < v.size(); ++i)
    {
        //第i个稀疏矩阵
        for (int j = 0; j < s[i].tu; ++j)
        {
            //第j个非零元素 行标、列标、元素值
            int I = s[i].data[j].i, J = s[i].data[j].j, V = s[i].data[j].value;
            v[i][I-1][J-1] = V;//保存的行标、列标是习惯上的从1开始
        }
    }
}