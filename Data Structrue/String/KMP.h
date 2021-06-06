#include <iostream>
#include <string>
using namespace std;

//针对模式串P的子串问题
int* buildNext(const string& P)
{
    int m = P.size(), j = 0;
    int* N = new int[m];
    int t = N[0] = -1;
    while (j < m - 1)
        if (t < 0 || P[j] == P[t]) {
            j++;
            t++;
            N[j] = t;
        } else
            t = N[t];
    return N;
}

int match(const string& T, const string& P)
{
    int* next = buildNext(P);
    int n = T.size(), i = 0;
    int m = P.size(), j = 0;
    while (i < n && j < m)
        if (j < 0 || T[i] == P[j]) {
            ++i;
            ++j;
        } else
            j = next[j];
    delete[] next;
    return i - j;
}