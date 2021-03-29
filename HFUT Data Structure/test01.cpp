#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int search(vector<int>& nums, int target)
{
    // int i = 0;
    // for (; i < nums.size(); ++i)
    //     if (nums[i] < nums[0])
    //         break;
    // if (nums[0] > target)
    //     binsearch(nums, i, nums.size() - 1, target);
    // else if (nums[0] < target)
    //     binsearch(nums, 0, i, target);
    // else
    //     return 0;
    int i;
    for (i = 0; i < nums.size(); ++i) {
        if (nums[i] == target)
            return i;
    }
    if (i == nums.size())
            return -1;
}
int main(void)
{
    vector<int> v1 = { 4, 5, 6, 7, 0, 1, 2 };
    cout << search(v1, 3)<<endl;

    system("pause");
    return 0;
}
