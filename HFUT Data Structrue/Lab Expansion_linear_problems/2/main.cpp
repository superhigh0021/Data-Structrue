#include "tutor.h"
using namespace std;

int main(void)
{
    tutor t;
    t.insert_tutor();
    t.search();


//�о�����д��û���⣬��Ҫ�ǵ�ʦ�ͱ������Ĵ��룬up��nextlevel����ȷ����������

    // cout<<t.Lhead1->next->next->name<<endl;
    // cout<<t.Lhead1->next->next->nextlevel->name<<endl;
    // cout<<t.Lhead1->next->next->nextlevel->nextlevel->name<<endl;
    system("pause");
    return 0;
}