#include <iostream>
#include <string>
#include <vector>
using namespace std;

int removeDuplicates(vector<int>& v)
    {
        int cnt = v[0];
        for (int i = 1; i < v.size();) {
            vector<int>::iterator v1 = v.begin();
            for (int j = 0; j < i; ++j)
                v1++;
            v.erase(remove(v1, v.end(), cnt), v.end());
            cnt = v[i++];
        }
        return v.size();
    }

int main(void)
{
    vector<int> v = { 0,0,1,1,1,2,2,3,3,4};
    cout<<removeDuplicates(v)<<endl;
    

    system("pause");
    return 0;
}