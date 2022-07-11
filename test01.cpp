#include <iostream>
using namespace std;

template <int T>
void print() {
    cout << 2 * T << endl;
}

int main(int argc, char** argv) {
    print<2>();
    return 0;
}