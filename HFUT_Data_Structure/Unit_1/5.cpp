#include <iostream>
#include <vector>
using namespace std;

void rsequence(const vector<int>& v) {
    int j = 0, i = 0;
    for (i = 0; i < v.size() - 2;) {
        for (j = i + 1; j <= v.size();) {
            if (v[j] > v[j - 1]) ++j;
            if (v[j] <= v[j - 1]|| j >= v.size()) {
                if (j - i >= 2) {
                    cout << '(';
                    for (int k = i; k < j; ++k) {
                        if (k == j - 1) {
                            cout << v[k];
                            break;
                        }
                        cout << v[k] << ',';
                    }
                    cout << ") ";
                }
                break;
            }
        }
        i = j;
    }
}

void dsequence(const vector<int>& v) {
    int j = 0, i = 0;
    for (i = 0; i < v.size() - 2;) {
        for (j = i + 1; j <= v.size();) {
            if (v[j] < v[j - 1]) ++j;
            if (v[j] >= v[j - 1] || j >= v.size()) {
                if (j - i >= 2) {
                    cout << '(';
                    for (int k = i; k < j; ++k) {
                        if (k == j - 1) {
                            cout << v[k];
                            break;
                        }
                        cout << v[k] << ',';
                    }
                    cout << ") ";
                }
                break;
            }
        }
        i = j;
    }
}

void sequence(const vector<int>&v) {
    rsequence(v);
    dsequence(v);
}

int main(void) {
    vector<int> v = {1, 20, 30, 12, 3, 5, 7, 4, 6, 100, 11, 8};
    sequence(v);

    system("pause");
    return 0;
}