/*����㷨ʵ��ϡ����������Ӧ��
    1�����ϡ������ࣻ
    2����������������ʵ��n��ϡ�������������ˡ�*/

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