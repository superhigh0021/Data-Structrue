#include <iostream>
using namespace std;

int Hcf(int M, int N)
{
    int H;
    while (N != 0) {
        H = M % N;
        M = N;
        N = H;
    }
    cout << M;
    return M;
}

int main(void)
{
    cout<<Hcf(100,350);
    cout<<Hcf(200,49);

    system("pause");
    return 0;
}
