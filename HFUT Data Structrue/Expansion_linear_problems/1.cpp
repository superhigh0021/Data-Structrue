/*����㷨ʵ��ϡ����������Ӧ��
    1�����ϡ������ࣻ
    2����������������ʵ��n��ϡ�������������ˡ�*/

#include "matrix.h"
using namespace std;

int main(void)
{
    vector<spmatrix> s = reset();
    //vector<vector<vector<int>>> v; //ϡ�����ĸ�������һ��Ϊϡ����󣬵ڶ�������Ϊ����Ԫ�أ�������ӡ
    //v.resize(s.size());
    // for (int i = 0; i < v.size(); ++i) {
    //     v[i].resize(s[i].mu);
    //     for (int j = 0; j < s[i].mu; ++j)
    //         v[i][j].resize(s[i].nu);
    // }
    insert(s);
    vector<vector<int>> v;
    v.resize(s[0].mu);
    for (int i = 0; i < v.size(); ++i) {
        v[i].resize(s[i].nu);
    }
    // for (int i = 0; i < v[0].size(); ++i) {
    //     int count = 0;
    //     for (auto j : v[0][i]) {
    //         cout << j << ' ';
    //         count++;
    //         if (count == v[0][i].size()) {
    //             cout << endl;
    //             count = 0;
    //         }
    //     }
    // }
    plus_spmatrix(s, v);

    system("pause");
    return 0;
}