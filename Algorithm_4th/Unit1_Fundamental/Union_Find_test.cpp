#include"Union_Find.h"
using namespace std;

int main(void){
    Union_Find uu(5);
    uu._Union(1,2);
    uu._Union(2,3);
    cout<<uu.Is_Connected(1,4);
    
    return 0;
}