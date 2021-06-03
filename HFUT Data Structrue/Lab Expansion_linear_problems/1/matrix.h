#define maxnum 10
using namespace std;

#include <iostream>
#include <vector>

struct Tuple {
    int i, j; //元素的行列下标
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
    for (int i = 0; i < num; ++i) {
        s[i].mu = mu;
        s[i].nu = nu;
    }
    for (int i = 0; i < num; ++i) {
        cout << "第" << i + 1 << "个矩阵的非零元素个数：";
        int num_of_nzero;
        cin >> num_of_nzero;
        s[i].tu = num_of_nzero;
    }
    return s;
}

void insert(vector<spmatrix>& s)
{
    int num = s.size();
    for (int m = 0; m < num; ++m) {
        int num_of_nzero = s[m].tu;
        for (int n = 0; n < num_of_nzero; ++n) {
            int i, j, value;
            cout << "你创建的第" << m + 1 << "个矩阵非零元素的行列和元素值分别为：";
            cin >> i >> j >> value;
            s[m].data[n].i = i; //第n个非零元素的行标
            s[m].data[n].j = j; //第n个非零元素的列标
            s[m].data[n].value = value;
        }
    }
}

void pirnt_matrix(vector<vector<int>> v)
{
    for (int i = 0; i < v.size(); ++i) {
        int count = 0;
        for (auto c : v[i]) {
            cout << c << ' ';
            count++;
            if (count == v[0].size()) {
                cout << endl;
                count = 0;
            }
        }
    }
}

void copy_value(const vector<spmatrix>& s, vector<vector<int>> v)
{
    for (int j = 0; j < s[0].tu; ++j) {
        //第j个非零元素 行标、列标、元素值
        int I = s[0].data[j].i, J = s[0].data[j].j, V = s[0].data[j].value;
        v[I - 1][J - 1] = V; //保存的行标、列标是习惯上的从1开始
    }
}

void plus_spmatrix(const vector<spmatrix>& s)
{
    vector<vector<int>> v;
    v.resize(s[0].mu);

    for (int i = 0; i < v.size(); ++i) {
        v[i].resize(s[0].nu);
    }

    int n = 1;
    //尚未考虑非零元素为0的情况
    for (int j = 0; j < s[0].tu; ++j) {
        //第j个非零元素 行标、列标、元素值
        int I = s[0].data[j].i, J = s[0].data[j].j, V = s[0].data[j].value;
        v[I - 1][J - 1] = V; //保存的行标、列标是习惯上的从1开始
    }

    //打印矩阵
    //pirnt_matrix(v);

    //第一个稀疏矩阵已经赋值，从第二个开始加
    while (n != s.size()) {
        for (int j = 0; j < s[n].tu; ++j) {
            int I = s[n].data[j].i, J = s[n].data[j].j, V = s[n].data[j].value;
            v[I - 1][J - 1] += V;
        }
        n++;
    }
    pirnt_matrix(v);
}

void multiply_spmatrix(const vector<spmatrix>& s)
{
    int n = 1;
    vector<vector<int>> v;
    v.resize(s[0].mu);

    for (int i = 0; i < v.size(); ++i) {
        v[i].resize(s[0].nu);
    }
    //将第一个稀疏矩阵copy到二维vector中
    for (int j = 0; j < s[0].tu; ++j) {
        //第j个非零元素 行标、列标、元素值
        int I = s[0].data[j].i, J = s[0].data[j].j, V = s[0].data[j].value;
        v[I - 1][J - 1] = V; //保存的行标、列标是习惯上的从1开始
    }
    pirnt_matrix(v);

    //再开辟一个数组存放结果
    vector<vector<int>> v2;
    v2.resize(s[n].mu);

    for (int i = 0; i < v2.size(); ++i) {
        v2[i].resize(s[n].nu);
    }

    while (n != s.size()) {
        //每次在循环内创建一个vector用来记录乘法中后一个稀疏矩阵
        vector<vector<int>> v1;
        v1.resize(s[n].mu);

        for (int i = 0; i < v1.size(); ++i) {
            v1[i].resize(s[n].nu);
        }

        for (int j = 0; j < s[n].tu; ++j) {
            //第j个非零元素 行标、列标、元素值
            int I = s[n].data[j].i, J = s[n].data[j].j, V = s[n].data[j].value;
            v1[I - 1][J - 1] = V; //保存的行标、列标是习惯上的从1开始
        }

        for (int i = 0; i < v.size(); ++i) {
            for (int j = 0; j < v1[i].size(); ++j) {
                int sum = 0;
                for (int k = 0; k < v[i].size(); ++k) {
                    sum += v[i][k] * v1[k][j];
                }
                v2[i][j] = sum;
            }
        }
        //一轮乘法完毕，再将v2存放的乘法结果赋值给v，实现n组相乘
        v.swap(v2);
        ++n;//进入下一轮乘法
    }
    pirnt_matrix(v);
}
