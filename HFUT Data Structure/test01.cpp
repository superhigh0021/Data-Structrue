#include <iostream>

#define lsp(p) p

int main(void)
{
    int *t;
    int b = 10;
    int a = lsp(*t) = b;
    std::cout << *t<<std::endl;

    system("pause");
    return 0;
}