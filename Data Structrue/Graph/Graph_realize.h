#include "Graph.h"

template <typename Tv>
//�������
struct Vertex
{
    //���ݡ����������״̬
    Tv data;
    int inDegree, outDegree;
    VStatus status;

    //ʱ���ǩ
    int dTime, fTime;

    //�ڱ������еĸ��ڵ㡢���ȼ���
    int parent;
    int priority;

    //�����¶���
    Vertex(Tv const &d = (Tv)0)
        : data(d), inDegree(0), outDegree(0), status(UNDISCOVERED), dTime(-1), fTime(-1), parent(-1), priority(INT_MAX)
    {
    }
};

//�߶���
template <typename Te>
struct Edge
{
    //���ݡ�Ȩ�ء�����
    Te data;
    int weight;
    EType type;

    Edge(Te const &d, int w)
        : data(d), weight(w), type(UNDETERMINED)
    {
    }
};

//�����������ڽӾ���ʵ�ֵ�ͼ
template <typename Tv, typename Te>
class GraphMatrix : public Graph<Tv, Te>
{
private:
    Vector<Vertex<Tv>> V;         //���㼯(����)
    Vector<Vector<Edge<Te> *>> E; //�߼�(�ڽӾ���)
    //��ά����
public:
    GraphMatrix() { n = e = 0; }
    ~GraphMatrix()
    {
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                delete E[j][k];
    }

    //����Ļ�����������ѯ��i������
    virtual Tv &vertex(int i) { return V[i].data; }
    virtual int inDegree(int i) { return V[i].inDegree; }
    virtual int outDegree(int i) { return V[i].outDegree; }

    //��������ȷ���ڽӶ�����㷨��Ϊ����ģ����Ӻ���ǰ��
    virtual int firstNbr(int i) { return nextNbr(i, n); } //�׸��ڽӶ���
    virtual int nextNbr(int i, int j)                     //����ڶ���j����һ�ڽӶ��㣬���򣡣�
    {
        while ((-1 < j) && (!exists(i, --j)))
            ;
        return j;
    }
    virtual VStatus &status(int i) { return V[i].status; }
    virtual int &dTime(int i) { return V[i].dTime; }
    virtual int &fTime(int i) { return V[i].fTime; }
    virtual int &parent(int i) { return V[i].parent; }
    virtual int &priority(int i) { return V[i].priority; }

    //����Ķ�̬����

    //���붥�㣬���ر��
    virtual int insert(Tv const &vertex)
    {
        //������Ԥ��һ��Ǳ�ڵĹ�����
        for (int j = 0; j < n; ++j)
            R[j].insert(NULL);
        ++n;
        //�����¶����Ӧ�ı�����
        E.insert(Vector<Edge<Te> *>(n, n, (Edge<Te> *)NULL));
        return V.insert(Vertex<Tv>(vertex)); //������������һ������
    }

    //ɾ����i�����㼰�������
    for (int j = 0; j < n; ++j)
        if (exists(i, j))
        {
            delete E[i][j];
            V[j].inDegree--;
        }
    E.remove(i);
    n--; //ɾ����i��
    Tv vBak = vertex(i);
    V.remove(i); //ɾ������i
    for (int j = 0; j < n; ++j)
        if (Edge<Te> *e = E[j].remove(i))
        {
            delete e;
            V[j].outDegeree--;
        }        //����ɾ��
    return vBak; //���ر�ɾ���������Ϣ

    //�ߵ�ȷ�ϲ���
    virtual bool exists(int i, int j)
    {
        return (0 < i) && (i < n) && (0 <= j) && (j < n) && E[i][j] != NULL;
    }

    //�ߵĻ�����������ѯ����i��j֮�������
    virtual Etype &type(int i, int j) { return E[i][j]->type; }   //��(i,j)������
    virtual Te &edge(int i, int j) { return E[i][j]->data; }      //��(i,j)������
    virtual int &weight(int i, int j) { return E[i][j]->weight; } //��(i,j)��Ȩ��

    //�ߵĶ�̬����

    //����Ȩ��Ϊw�ı�e=(i,j)
    virtual void insert(Te const &edge, int w, int i, int j)
    {
        //ȷ���ñ��в�����
        if (exists(i, j))
            return;
        E[i][j] = new Edge<Te>(edge, w); //�����±�
        ++e;
        V[i].outDegree++;
        V[j].inDegree++; //���±߼������������Ķ���
    }
    //ɾ������i��j֮�������
    virtual Te remove(int i, int j)
    {
        //���ݺ�ɾ���߼�¼
        Te eBak = edge(i, j);
        delete E[i][j];
        E[i][j] = NULL;

        //���±߼������������Ķ���
        e--;
        V[i].outDegree--;
        V[j].inDegree--;

        return eBak;
    }
};

template <typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s)
{
    //��s��ʼ����bfs�㷨
    reset();
    //��ʼ��
    int clock = 0, v = s;
    do
    {
        //һ��������δ���ֵĶ��㣬���Ӹö��㴥������һ��BFS
        if (status(v) == UNDISCOVERED)
            BFS(v, clock);
    } while (s != (v = (++v % n)))
}

//��������㷨(������ͨ��)
template <typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int &clock)
{
    queue<int> Q;
    status(v) = DISCOVERED;
    Q.push(v);
    while (!Q.empty())
    {
        int v = Q.front();
        Q.pop();
        dTime(v) = ++clock;
        //�ٴμ�����㷨�����˼·��
        for (int u = firstNbr(v); - 1 < u; u = nextNbr(v, u)) //ö��v�������ھ�u
            if (status(u) == UNDISCOVERED)
            {
                //��u��δ������
                status(u) = DISCOVERED;
                Q.push(u);
                type(v, u) = TREE;
                parent(u) = v;
            }
            else
            {
                type(v, u) = CROSS;
            }
        status(v) = VISITED; //���ˣ���ǰ����������
    }
}

//�����������DFS�㷨(ȫͼ)
template <typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int s)
{
    reset();
    int clock = 0;
    int v = s;
    do
    {
        if (UNDISCOVERED == status(v))
            DFS(v, clock);
    } while (s != (v = (++v % n)));
}

//(������ͨ��)
template <typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int &clock)
{
    dTime(v) = ++clock;
    status(v) = DISCOVERED;
    for (int u = firstNbr(v); - 1 < u; u = nextNbr(v, u))
    {
        switch (status(u))
        {
        case UNDISCOVERED:
            //��u��δ�����֣���ζ��֧�������ڴ˴���չ
            type(v, u) = TREE;
            parent(u) = v;
            DFS(u, clock);
            break;
        case DISCOVERED:
            //��u�ѱ����ֵ���δ������ϣ�Ӧ���ڱ����ָ�������
            type(v, u) = BACKWARD;
            break;
        default:
            //��u�ѷ������(VISITED������ͼ)�����ӳ�Ϯ��ϵ��Ϊǰ��ߺͿ��
            type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
            break;
        }
    }
    status(v) = VISITED;
    fTime(v) = ++clock;
}

//����DFS�����������㷨
template <typename Tv, typename Te>
stack<Tv> *Graph<Tv, Te>::tSort(int s)
{
    reset();
    int clock = 0;
    int v = s;
    stack<Tv> *S = new stack<Tv>;
    do
    {
        if (status(v) == UNDISCOVERED)
            if (!TSort(v, clock, S))
                while (!S->empty)
                {
                    //������ͨ��(�༴��ͼ)��DAG
                    S->pop();
                    break;
                }
    } while (s != (v = (++v % n)));
    return S;
}

//����DFS�����������㷨(����)
template <typename Tv, typename Te>
bool Graph<Tv, Te>::TSort(int v, int &clock, stack<Tv> *S)
{
    dTime(v) = ++clock;
    status(v) = DISCOVERED;
    for (int u = fisrstNbr(v); - 1 < u; u = nextNbr(v, u))
        switch (status(u))
        {
        case UNDISCOVERED:
            parent(u) = v;
            type(v, u) = TREE;
            if (TSort(u, clock, S))
                return false;
        case DISCOVERED:
            type(v, u) = BACKWARD; //һ�����ֺ����
            return false;
        default:
            type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
            break;
        }
    status(v) = VISITED;
    S->push(vertex(v)); //���㱻���ΪVISITEDʱ���漴��ջ
    return true;
}

//���ȼ�����(ȫͼ)
template <typename Tv, typename Te>
template <typename PU>
void Graph<Tv, Te>::pfs(int s, PU prioUpdater)
{
    reset();
    int v = s; //��s��ʼ
    do
    {
        if (status(s) == UNDISCOVERED)
            //һ��������δ���ֵĶ��㣬�ʹӸö�������һ��PFS
            PFS(v, prioUpdater);
    } while (s != (v = (++v % n)));
}

template <typename Tv, typename Te>
template <typename PU>
//���㡢�ߡ����ȼ�����
void Graph<Tv, Te>::PFS(int s, PU prioUpdater)
{
    //���ȼ�����(������ͨ��)
    priority(s) = 0;
    status(s) = VISITED;
    parent(s) = -1;
    while (true)
    {
        //����һ����ͱ���ӵ�PFS����
        for (int w = firstNbr(s); w > -1; w = nextNbr(s, w))
            prioUpdater(this, s, w); //���ȼ����Ը��º���
        for (int shortest = INT_MAX, w = 0; w < n; w++)
            //���ȼ���Խ�����ȼ�Խ��
            if (status(w) == UNDISCOVERED)
                if (shortest > priority(w))
                {
                    //����δ����������Ķ�����ѡ����һ�����ȼ���ߵĶ���s
                    shortest = priority(w);
                    s = w;
                }
        if (status(s) == VISITED)
            break;//ֱ�����ж�����Ѽ���,break����while
        status(s)=VISITED;
        type(parent(s),s)=TREE;
    }
}

