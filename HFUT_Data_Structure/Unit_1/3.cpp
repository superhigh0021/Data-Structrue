#include <iostream>
#include <vector>
using namespace std;

void Set(vector<int>& v, int i, int n)
{
    if (i > n)
        return;
    v.push_back(i);
    for (auto c : v)
        cout << c << ' ';
    cout << endl;
    for (int j = 1; j < n; ++j) {
        vector<int> vec = v;
        Set(vec, i + j, n);
    }
}
int main(void)
{
    int n;
    cin >> n;
    if (n > 0)
        for (int i = 1; i <= n; ++i) {
            vector<int> v;
            Set(v, i, n);
        }
    else
        return 0;
    system("pause");
    return 0;
}