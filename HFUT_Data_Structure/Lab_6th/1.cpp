#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

#define max_size 100
#define max 9999

//全局
vector<int> visited(100, 0);
int last;//上一个访问的顶点
bool flag = true;

class Graph {
public:
    Graph(vector<vector<int>> v, vector<vector<int>> path, int m, int n)
        : A(v)
        , path(path)
        , m(m)
        , n(n)
    {
    }
    vector<vector<int>> A;
    vector<vector<int>> path;
    void DFSTraverse();
    void Floyd()
    {
        //弗洛伊德(Floyd)核心语句
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (A[i][k] + A[k][j] < A[i][j]) {
                        A[i][j] = A[i][k] + A[k][j];
                        path[i][j] = path[i][k];
                    }

        cout << endl
             << "最短距离矩阵为：" << endl;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++)
                cout << A[i][j] << " ";
            cout << endl;
        }

        int v1, v2, z;
        cout << "输入两个点，输出之间路径" << endl;
        cin >> v1 >> v2;
        z = path[v1][v2];
        cout << v1;
        while (z != v2) {
            cout << "->" << z;
            z = path[z][v2];
        }
        cout << "->" << v2;
    }

private:
    int n; //点的个数
    int m; //边的个数

    void DFS(int root)
    {
        visited[root] = 1;
        for (int child = 1; child <= n; child++) {
            if (child != root && A[root][child] != max) //邻接矩阵中节点v的邻接点
            {
                if (visited[child] == 1 && last != child) 
                //而且还访问过(而且为状态1，说明不是回溯过来的顶点)，说明存在环(判断i不是v的父节点)
                    flag = false;
                else if (visited[child] == 0) {
                    last = root; //更新last
                    DFS(child);
                }
            }
        }
        visited[root] = 2; //遍历完所有的邻接点才变为状态2
    }
};

void Graph::DFSTraverse()
{
    for (int i = 1; i <= n; i++)
        if (!visited[i]) {
            DFS(i);
        }
}

int main(void)
{
    int m, n;
    cout << "请输入点的个数和边的个数:" << endl;
    cin >> n >> m;
    vector<vector<int>> v;
    v.resize(max_size, vector<int>(max_size));
    vector<vector<int>> path;
    path.resize(max_size, vector<int>(max_size));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (i == j)
                v[i][j] = 0;
            else
                v[i][j] = max;
    //读入边
    cout << "输入点到点的距离" << endl;
    for (int i = 1; i <= m; i++) {
        int t1, t2, t3;
        cin >> t1 >> t2 >> t3;
        v[t1][t2] = t3;
        v[t2][t1] = t3;
        path[t1][t2] = t2;
    }
    Graph gg(v, path, m, n);
    gg.DFSTraverse();
    if (flag == false)
        cout << "该图有环，不能构成树！" << endl;
    else
        cout << "该图无环，可以构成树" << endl;
    
    gg.Floyd();

    system("pause");
    return 0;
}