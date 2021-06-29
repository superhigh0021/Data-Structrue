#include <iostream>
#include <vector>
using namespace std;
#define INF 9999

class MGraph
{
public:
    int n;
    vector<vector<int>> A;
    vector<vector<int>> path;
    MGraph(vector<vector<int>> v) : A(v),n(v.size()) {
        path.resize(n,vector<int>(n,-1));
    }
    void display_matrix();
    void Floyd();
    void ppath(int i, int j);
    void DisPath();
};

void MGraph::ppath(int i, int j)
{
    int k;
    k = path[i][j]; //path[i][j]是中转
    if (k == -1)
        return;
    ppath(i, k);
    printf("%d,", k);
    ppath(k, j);
}

void MGraph::DisPath()
{
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (A[i][j] != INF && i != j)
            {
                printf("  从%d到%d路径为:", i, j);
                cout<<i<<',';
                ppath(i, j);
                cout<<j;
                cout<<'\t'<<"路径长度为"<<A[i][j]<<endl;
            }
}

void MGraph::Floyd() //弗洛伊德算法从每对顶点之间的最短路径
{
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (A[i][j] > (A[i][k] + A[k][j]))
                {
                    A[i][j] = A[i][k] + A[k][j];
                    path[i][j] = k;
                }
    }
    cout << endl
         << "最短路径为：" << endl;
    DisPath(); //输出最短路径
}

void MGraph::display_matrix()
//输出邻接矩阵g
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            if (A[i][j] == INF)
                printf("%3s", "∞");
            else
                printf("%3d", A[i][j]);
        printf("\n");
    }
}
int main()
{
    int i, j;
    vector<vector<int>> v = {
        {0, 5, INF, 7, INF, INF},
        {INF, 0, 4, INF, INF, INF},
        {8, INF, 0, INF, INF, 9},
        {INF, INF, 5, 0, INF, 6},
        {INF, INF, INF, 5, 0, INF},
        {3, INF, INF, INF, 1, 0}};
    MGraph g(v);
    g.display_matrix();
    g.Floyd();
    cout << endl;

    system("pause");
    return 0;
}