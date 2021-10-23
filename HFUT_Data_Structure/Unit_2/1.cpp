#include<iostream>
using namespace std;

int getPermuStack(int n, int m) {
    if (n == 0)  //递归边界
        return 1;
    if (m == 0)  //(n,0)问题的处理
        return getPermuStack(n - 1, 1);
    return getPermuStack(n, m - 1) + getPermuStack(n - 1, m + 1);
}

int main() {
    cout<<getPermuStack(5, 0)<<endl;
    system("pause");
    return 0;

}