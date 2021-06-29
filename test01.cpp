#include <iostream>
using namespace std;
#define MAXV 100
#define INF 9999
class MGraph {
public:
    int edges[MAXV][MAXV];
    int n, e;
};
void ppath(int path[][MAXV], int i, int j)
{
    int k;
    k = path[i][j];
    if (k == -1)
        return;
    ppath(path, i, k);
    printf("%d,", k);
    ppath(path, k, j);
}
void DisPath(int A[][MAXV], int path[][MAXV], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (A[i][j] != INF && i != j) {
                printf("  从%d到%d路径为:", i, j);
                printf("%d,", i);
                ppath(path, i, j);
                printf("%d", j);
                printf("\t路径长度为:%d\n", A[i][j]);
            }
}
void Floyd(MGraph g) //弗洛伊德算法从每对顶点之间的最短路径
{
    int A[MAXV][MAXV], path[MAXV][MAXV];
    int i, j, k, n = g.n;
    for (i = 0; i < n; i++) //给A数组置初值
        for (j = 0; j < n; j++) {
            A[i][j] = g.edges[i][j];
            path[i][j] = -1;
        }
    for (k = 0; k < n; k++) //计算Ak
    {
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (A[i][j] > (A[i][k] + A[k][j])) {
                    A[i][j] = A[i][k] + A[k][j];
                    path[i][j] = k;
                }
    }
    printf("\n输出最短路径:\n");
    DisPath(A, path, n); //输出最短路径
}
void DispMat(MGraph g)
//输出邻接矩阵g
{
    int i, j;
    for (i = 0; i < g.n; i++) {
        for (j = 0; j < g.n; j++)
            if (g.edges[i][j] == INF)
                printf("%3s", "∞");
            else
                printf("%3d", g.edges[i][j]);
        printf("\n");
    }
}
int main()
{
    int i, j;
    MGraph g;
    int B[MAXV][6] = {
        { 0, 5, INF, 7, INF, INF },
        { INF, 0, 4, INF, INF, INF },
        { 8, INF, 0, INF, INF, 9 },
        { INF, INF, 5, 0, INF, 6 },
        { INF, INF, INF, 5, 0, INF },
        { 3, INF, INF, INF, 1, 0 }
    };
    g.n = 6;
    g.e = 10;
    for (i = 0; i < g.n; i++)
        for (j = 0; j < g.n; j++)
            g.edges[i][j] = B[i][j];
    DispMat(g);
    Floyd(g);
    cout<<endl;

    system("pause");
    return 0;
}