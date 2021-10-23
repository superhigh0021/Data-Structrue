#include"KMP.h"
using namespace std;

int main(void){
    string t="BDCABA";
    string p="ABCBDAB";
    cout<<match(t,p);


    return 0;
}