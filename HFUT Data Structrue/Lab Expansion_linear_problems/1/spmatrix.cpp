/*设计算法实现稀疏矩阵的运算应用
    1）设计稀疏矩阵类；
    2）给出测试用例，实现n组稀疏矩阵的相加与相乘。*/

#include "matrix.h"
using namespace std;

int main(void)
{
    vector<spmatrix> s = reset();
    insert(s);

    //plus_spmatrix(s);
    multiply_spmatrix(s);

    system("pause");
    return 0;
}