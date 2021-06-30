#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

#define max_size 100
#define max 9999

//ȫ��
vector<int> visited(100, 0);
int last;//��һ�����ʵĶ���
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
        //��������(Floyd)�������
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (A[i][k] + A[k][j] < A[i][j]) {
                        A[i][j] = A[i][k] + A[k][j];
                        path[i][j] = path[i][k];
                    }

        cout << endl
             << "��̾������Ϊ��" << endl;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++)
                cout << A[i][j] << " ";
            cout << endl;
        }

        int v1, v2, z;
        cout << "���������㣬���֮��·��" << endl;
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
    int n; //��ĸ���
    int m; //�ߵĸ���

    void DFS(int root)
    {
        visited[root] = 1;
        for (int child = 1; child <= n; child++) {
            if (child != root && A[root][child] != max) //�ڽӾ����нڵ�v���ڽӵ�
            {
                if (visited[child] == 1 && last != child) 
                //���һ����ʹ�(����Ϊ״̬1��˵�����ǻ��ݹ����Ķ���)��˵�����ڻ�(�ж�i����v�ĸ��ڵ�)
                    flag = false;
                else if (visited[child] == 0) {
                    last = root; //����last
                    DFS(child);
                }
            }
        }
        visited[root] = 2; //���������е��ڽӵ�ű�Ϊ״̬2
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
    cout << "�������ĸ����ͱߵĸ���:" << endl;
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
    //�����
    cout << "����㵽��ľ���" << endl;
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
        cout << "��ͼ�л������ܹ�������" << endl;
    else
        cout << "��ͼ�޻������Թ�����" << endl;
    
    gg.Floyd();

    system("pause");
    return 0;
}