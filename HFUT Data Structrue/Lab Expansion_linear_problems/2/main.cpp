#include "tutor.h"
using namespace std;

int main(void)
{
    tutor t;
    t.insert_tutor();
    t.insert_tutor();

    cout<<t.Lhead1->next->next->nextlevel->num;//²âÊÔÓÃËæÊ±×¢ÊÍ



    // cout<<t.Lhead1->next->next->name<<endl;
    // cout<<t.Lhead1->next->next->nextlevel->name<<endl;
    // cout<<t.Lhead1->next->next->nextlevel->nextlevel->name<<endl;
    system("pause");
    return 0;
}