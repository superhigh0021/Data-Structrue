#include <vector>
#include <iostream>
using namespace std;

class Union_Find
{
private:
    int count = 0;  //连通分量的个数
    vector<int> id; //树根位置的数组
    vector<int> sz; //树根权重数组

public:
    Union_Find(const int &N) : count(N)
    {
        sz.resize(N);
        id.resize(N);
        for (int i = 0; i < N; ++i)
        {
            sz[i] = 1;
            id[i] = i;
        }
    }
    int size() { return count; }
    int find(int p)
    {
        while (id[p] != p)
            p = id[p];
        return p;
    }
    bool Is_Connected(int p, int q) { return find(p) == find(q); }
    void _Union(int p, int q)
    {
        int Pid = find(p), Qid = find(q);
        if (sz[Pid] <= sz[Qid])
        {
            //小根依附于大根
            sz[Qid] += sz[Pid];
            id[Pid] = Qid;
        }
        else
        {
            sz[Pid] += sz[Qid];
            id[Qid] = Pid;
        }
        --count;
    }
};