#include <iostream>
using namespace std;
typedef int elementtype;
int E;
#define max 100
int inf = 99999;
bool visited[max];
typedef struct
{
	int d;	 //到达某点的最短路径距离
	int pre; //该最短路径是经过哪个点传过来的，源点或其他某个点
} path;
class graph
{
public:
	elementtype vertex[max]; //顶点表
	int edge[max][max];		 //邻接矩阵
	int n;					 //当前顶点数
	int e = 0;				 //边数
	int vis[max];			 //表示最短路径是否被找到
	path to[max];			 //记录当前某个点的最短路径及从那个点传过来
	graph()
	{
		int i, j;
		for (i = 1; i <= max; i++)
			vertex[i] = -1;
	};
	void visite(elementtype v) { cout << vertex[v] << "  "; }
	//无向图

	//有向图(网络)
	void createadj2()
	{
		int i, j, k;
		cout << "请输入顶点数" << endl;
		cin >> n;
		for (i = 1; i <= n; i++)
		{
			vis[i] = 0;
		}
		for (i = 1; i <= n; i++)
		{
			for (j = 1; j <= n; j++)
			{
				edge[i][j] = inf;
			}
			to[i].d = inf;
		}
		cout << "请输入各顶点的值" << endl;
		for (k = 1; k <= n; k++)
			cin >> vertex[k];
		cout << "请输入边和边的值：i j k，i为-1时结束" << endl;
		cin >> i >> j;
		while (i != -1)
		{
			cin >> edge[i][j];
			cin >> i >> j;
		}
	};

	//从原点到其他点的最短路径
	void fun2()
	{
		int i, min, j, k;
		for (i = 2; i <= n; i++)
		{
			to[i].d = edge[1][i]; //初始化源点到i点边权值，之后过程中会发生变化
			if (edge[1][i] != inf)
			{
				to[i].pre = 1;
			}
		}
		vis[1] = 1;
		for (i = 2; i <= n; i++)
		{ //共循环n-1次，每循环一次，确定一条最短路，再次循环时这条路就不用考虑了，去寻找下一条最短路
			min = inf;
			for (j = 2; j <= n; j++)
			{ //寻找下一条当前最短路
				if (to[j].d < min && vis[j] == 0)
				{
					min = to[j].d;
					k = j;
				}
			}
			vis[k] = 1; //找到了，到k点的路是当前最短路，标记它，根据它寻找下一条最短路
			for (j = 2; j <= n; j++)
			{
				if (to[j].d > to[k].d + edge[k][j] && vis[j] == 0)
				{ //经过此k点到达j点的路径是否小于其他到达j点的路径
					to[j].d = to[k].d + edge[k][j];
					to[j].pre = k; //改变j点是谁传来的，现在到j点的最短路径是经过k点的，由j点传来
				}
			}
		}
		int max_dis = INT_MIN;
		int max_vertex = INT_MIN;
		for (i = 2; i <= n; i++)
		{ //输出到达个点的最短路径
			cout << "原点到该点的最短路径距离为：";
			cout << to[i].d << endl;
			if (to[i].d > max_dis)
			{
				max_dis = to[i].d;
				max_vertex = i;
			}
			cout << "具体路径为：";
			cout << i;
			j = i;
			while (j != 1)
			{
				j = to[j].pre;
				cout << "<-" << j;
			}
			cout << endl;
		}
		cout << endl
			 << "关键路径为：";
		cout << max_vertex;
		j = max_vertex;
		while (j != 1)
		{
			j = to[j].pre;
			cout << "<-" << j;
		}
		cout << endl
			 << "该关键路径的长度为：" << max_dis << endl;
	}
};