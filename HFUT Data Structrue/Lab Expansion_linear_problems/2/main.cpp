#include "tutor.h"
using namespace std;

int main(void)
{
    tutor t;
    t.insert_tutor();
    t.search();


//研究生的写的没问题，主要是导师和本科生的代码，up和nextlevel不明确，不方便表达

    // cout<<t.Lhead1->next->next->name<<endl;
    // cout<<t.Lhead1->next->next->nextlevel->name<<endl;
    // cout<<t.Lhead1->next->next->nextlevel->nextlevel->name<<endl;
    system("pause");
    return 0;
}