#include <iostream>
using namespace std;
typedef int elementtype;
int E;
#define max 100
int inf = 99999;
bool visited[max];
typedef struct
{
	int d;	 //����ĳ������·������
	int pre; //�����·���Ǿ����ĸ��㴫�����ģ�Դ�������ĳ����
} path;
class graph
{
public:
	elementtype vertex[max]; //�����
	int edge[max][max];		 //�ڽӾ���
	int n;					 //��ǰ������
	int e = 0;				 //����
	int vis[max];			 //��ʾ���·���Ƿ��ҵ�
	path to[max];			 //��¼��ǰĳ��������·�������Ǹ��㴫����
	graph()
	{
		int i, j;
		for (i = 1; i <= max; i++)
			vertex[i] = -1;
	};
	void visite(elementtype v) { cout << vertex[v] << "  "; }
	//����ͼ

	//����ͼ(����)
	void createadj2()
	{
		int i, j, k;
		cout << "�����붥����" << endl;
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
		cout << "������������ֵ" << endl;
		for (k = 1; k <= n; k++)
			cin >> vertex[k];
		cout << "������ߺͱߵ�ֵ��i j k��iΪ-1ʱ����" << endl;
		cin >> i >> j;
		while (i != -1)
		{
			cin >> edge[i][j];
			cin >> i >> j;
		}
	};

	//��ԭ�㵽����������·��
	void fun2()
	{
		int i, min, j, k;
		for (i = 2; i <= n; i++)
		{
			to[i].d = edge[1][i]; //��ʼ��Դ�㵽i���Ȩֵ��֮������лᷢ���仯
			if (edge[1][i] != inf)
			{
				to[i].pre = 1;
			}
		}
		vis[1] = 1;
		for (i = 2; i <= n; i++)
		{ //��ѭ��n-1�Σ�ÿѭ��һ�Σ�ȷ��һ�����·���ٴ�ѭ��ʱ����·�Ͳ��ÿ����ˣ�ȥѰ����һ�����·
			min = inf;
			for (j = 2; j <= n; j++)
			{ //Ѱ����һ����ǰ���·
				if (to[j].d < min && vis[j] == 0)
				{
					min = to[j].d;
					k = j;
				}
			}
			vis[k] = 1; //�ҵ��ˣ���k���·�ǵ�ǰ���·���������������Ѱ����һ�����·
			for (j = 2; j <= n; j++)
			{
				if (to[j].d > to[k].d + edge[k][j] && vis[j] == 0)
				{ //������k�㵽��j���·���Ƿ�С����������j���·��
					to[j].d = to[k].d + edge[k][j];
					to[j].pre = k; //�ı�j����˭�����ģ����ڵ�j������·���Ǿ���k��ģ���j�㴫��
				}
			}
		}
		int max_dis = INT_MIN;
		int max_vertex = INT_MIN;
		for (i = 2; i <= n; i++)
		{ //��������������·��
			cout << "ԭ�㵽�õ�����·������Ϊ��";
			cout << to[i].d << endl;
			if (to[i].d > max_dis)
			{
				max_dis = to[i].d;
				max_vertex = i;
			}
			cout << "����·��Ϊ��";
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
			 << "�ؼ�·��Ϊ��";
		cout << max_vertex;
		j = max_vertex;
		while (j != 1)
		{
			j = to[j].pre;
			cout << "<-" << j;
		}
		cout << endl
			 << "�ùؼ�·���ĳ���Ϊ��" << max_dis << endl;
	}
};