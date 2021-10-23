#include <iostream>
#include <vector>
using namespace std;

int main(void) {
    vector<int> v;
    int i;
    do {
        cin >> i;
        v.push_back(i);
    } while (getchar() != '\n');
    int x, sum = 0;
    cin >> x;
    for (int j = 0; j < v.size(); ++j) sum = sum * x + v[j];

    cout << sum << endl;
    return 0;
}