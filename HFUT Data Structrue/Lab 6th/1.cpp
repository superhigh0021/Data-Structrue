#include <iostream>
#include <List>
using namespace std;

const int Max = 10;

typedef class UnDirectedGragh
{
public:
    UnDirectedGragh() //��ά�����ʼ��
    {
        edge = 0;
        for (int i = 0; i < Max; i++)
        {
            node[i] = -1; //��ʼ���������
            for (int j = 0; j < Max; j++)
                gragh[i][j] = 99999;
        }
    }
    void Create(); //�������Զ���ͼ�ṹ
    bool Judge();  //�ж��Ƿ�����
    //һ������ͼG��һ����������Ϊ��G�������޻�·����ͨͼ��n-1���ߵ���ͨͼ
    void Floyd();                                 //�����������·���㷨
    void print();                                 //��ӡͼ�ṹ
    void search(int entrance, int mid, int exit); //�ݹ�������·��
    void next(int x);                             //����ͼ�ṹ�ж��Ƿ�Ϊ�޻�ͼ

private:
    int gragh[Max][Max]; //��ά���鴢��ͼ
    int node[Max];       //������������жϽ���Ƿ���
    int path[Max][Max];
    list<int> List; //���·��
    int edge;       //ͼ����
} UGragh;

void UGragh::Create()
{
    int x, y;
    bool judge = true;
    while (judge)
    {
        cout << "�����뽨����ͨ�����ڵ��±꣺";
        cin >> x >> y;
        node[x] = node[y] = 0;
        cout << "������·�����ȣ�";
        cin >> gragh[x][y];
        gragh[y][x] = gragh[x][y];
        cout << "�����ɹ����Ƿ�������룿 1���� 0����";
        edge++;
        cin >> judge;
        system("cls");
    }
}

void UGragh::print()
{
    for (int i = 0; i < Max; i++)
    {
        if (node[i] == 0)
        {
            cout << "G[" << i << "] -> ";
            for (int j = 0; j < Max; j++)
            {
                if (gragh[i][j] != 99999)
                    cout << "G[" << j << "] = " << gragh[i][j] << "  ";
            }
            cout << endl;
        }
    }
}

void UGragh::next(int x)
{
    for (int i = 0; i < Max; i++)
    {
        if (gragh[x][i] != 99999)
        {
            node[x] = 1;
            node[i] = 1;
            next(++i);
        }
    }
}

bool UGragh::Judge()
{
    int x = 0;
    for (int i = 0; i < Max; i++)
        if (node[i] == 0)
            x++;
    if (edge == x - 1)
    {
        for (int i = 0; i < Max; i++)
            if (node[i] == 0)
                next(i);
        for (int i = 0; i < Max; i++)
        {
            if (node[i] == 0)
                return false;
        }
        return true;
    }
    else
        return false;
}

void UGragh::Floyd()
{
    int entrance, exit;
    cout << "������ ��ںͳ��ڣ�";
    cin >> entrance >> exit;

    for (int i = 0; i < Max; i++)
        for (int j = 0; j < Max; j++)
            path[i][j] = -1;
    for (int k = 0; k < Max; k++)
        for (int i = 0; i < Max; i++)
            for (int j = 0; j < Max; j++)
            {
                if (gragh[i][j] > gragh[i][k] + gragh[k][j])
                {
                    gragh[i][j] = gragh[i][k] + gragh[k][j];
                    path[i][j] = k;
                }
            }
    cout << "���·������Ϊ��" << gragh[entrance][exit] << endl;

    List.push_back(entrance);
    List.push_back(exit);
    search(entrance, path[entrance][exit], exit);
    cout << "���·��Ϊ��";
    for (list<int>::iterator it = List.begin(); it != List.end(); it++)
        cout << "G[" << (*it) << "] -> ";
    cout << "NULL" << endl;
}

void UGragh::search(int entrance, int mid, int exit)
{
    list<int>::iterator m;
    for (list<int>::iterator it = List.begin(); it != List.end(); it++)
    {
        if (*it == entrance)
            m = ++it;
    }
    if (mid != -1)
    {
        List.insert(m, mid);
        search(entrance, path[entrance][mid], mid);
        search(mid, path[mid][exit], exit);
    }
}

int main()
{
    UGragh G;
    G.Create();
    G.print();
    cout << (G.Judge() ? "��ͼ���� " : "��ͼ������ ") << endl;
    G.Floyd();

    system("pause");
}
