#include <iostream>
using namespace std;
#include <vector>
#include<map>

void KProblem(int S, const vector<int>& v) {
    int sum = 0;
    vector<string>v;
    for (int i = 0; i < v.size() - 1;) {
        for (int j = i + 1; j < v.size();) {
            if (sum + v[j] < S) {
                sum += v[j];
                ++j;
                v.push_back
                continue;
            }
            if (sum + v[j] > S){
                ++j;
                continue;
            }
            if (sum + v[j] == S) {
                
            }
        }
    }
}

int main(void) {
    int S = 50;
    vector<int> v = {29, 26, 18, 16, 13, 10, 8, 5, 3, 1};
}