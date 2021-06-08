#include "Graph.h"

template <typename Tv>
//顶点对象
struct Vertex
{
    //数据、出入度数、状态
    Tv data;
    int inDegree, outDegree;
    VStatus status;

    //时间标签
    int dTime, fTime;

    //在遍历树中的父节点、优先级数
    int parent;
    int priority;

    //构造新顶点
    Vertex(Tv const &d = (Tv)0)
        : data(d), inDegree(0), outDegree(0), status(UNDISCOVERED), dTime(-1), fTime(-1), parent(-1), priority(INT_MAX)
    {
    }
};

//边对象
template <typename Te>
struct Edge
{
    //数据、权重、类型
    Te data;
    int weight;
    EType type;

    Edge(Te const &d, int w)
        : data(d), weight(w), type(UNDETERMINED)
    {
    }
};

//基于向量和邻接矩阵实现的图
template <typename Tv, typename Te>
class GraphMatrix : public Graph<Tv, Te>
{
private:
    Vector<Vertex<Tv>> V;         //顶点集(向量)
    Vector<Vector<Edge<Te> *>> E; //边集(邻接矩阵)
    //二维数组
public:
    GraphMatrix() { n = e = 0; }
    ~GraphMatrix()
    {
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                delete E[j][k];
    }

    //顶点的基本操作：查询第i个顶点
    virtual Tv &vertex(int i) { return V[i].data; }
    virtual int inDegree(int i) { return V[i].inDegree; }
    virtual int outDegree(int i) { return V[i].outDegree; }

    //下面两个确定邻接顶点的算法均为逆向的！即从后往前。
    virtual int firstNbr(int i) { return nextNbr(i, n); } //首个邻接顶点
    virtual int nextNbr(int i, int j)                     //相对于顶点j的下一邻接顶点，逆向！！
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

    //顶点的动态操作

    //插入顶点，返回编号
    virtual int insert(Tv const &vertex)
    {
        //各顶点预留一条潜在的关联边
        for (int j = 0; j < n; ++j)
            R[j].insert(NULL);
        ++n;
        //创建新顶点对应的边向量
        E.insert(Vector<Edge<Te> *>(n, n, (Edge<Te> *)NULL));
        return V.insert(Vertex<Tv>(vertex)); //顶点向量增加一个顶点
    }

    //删除第i个顶点及其关联边
    for (int j = 0; j < n; ++j)
        if (exists(i, j))
        {
            delete E[i][j];
            V[j].inDegree--;
        }
    E.remove(i);
    n--; //删除第i行
    Tv vBak = vertex(i);
    V.remove(i); //删除顶点i
    for (int j = 0; j < n; ++j)
        if (Edge<Te> *e = E[j].remove(i))
        {
            delete e;
            V[j].outDegeree--;
        }        //逐条删除
    return vBak; //返回被删除顶点的信息

    //边的确认操作
    virtual bool exists(int i, int j)
    {
        return (0 < i) && (i < n) && (0 <= j) && (j < n) && E[i][j] != NULL;
    }

    //边的基本操作：查询顶点i与j之间的联边
    virtual Etype &type(int i, int j) { return E[i][j]->type; }   //边(i,j)的类型
    virtual Te &edge(int i, int j) { return E[i][j]->data; }      //边(i,j)的数据
    virtual int &weight(int i, int j) { return E[i][j]->weight; } //边(i,j)的权重

    //边的动态操作

    //插入权重为w的边e=(i,j)
    virtual void insert(Te const &edge, int w, int i, int j)
    {
        //确保该边尚不存在
        if (exists(i, j))
            return;
        E[i][j] = new Edge<Te>(edge, w); //创建新边
        ++e;
        V[i].outDegree++;
        V[j].inDegree++; //更新边计数与关联顶点的度数
    }
    //删除顶点i和j之间的联边
    virtual Te remove(int i, int j)
    {
        //备份后删除边记录
        Te eBak = edge(i, j);
        delete E[i][j];
        E[i][j] = NULL;

        //更新边计数与关联顶点的度数
        e--;
        V[i].outDegree--;
        V[j].inDegree--;

        return eBak;
    }
};

template <typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s)
{
    //从s开始调用bfs算法
    reset();
    //初始化
    int clock = 0, v = s;
    do
    {
        //一旦遇到尚未发现的顶点，即从该顶点触发启动一次BFS
        if (status(v) == UNDISCOVERED)
            BFS(v, clock);
    } while (s != (v = (++v % n)))
}

//广度优先算法(单个连通域)
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
        //再次加深该算法逆向的思路！
        for (int u = firstNbr(v); - 1 < u; u = nextNbr(v, u)) //枚举v的所有邻居u
            if (status(u) == UNDISCOVERED)
            {
                //若u尚未被发现
                status(u) = DISCOVERED;
                Q.push(u);
                type(v, u) = TREE;
                parent(u) = v;
            }
            else
            {
                type(v, u) = CROSS;
            }
        status(v) = VISITED; //至此，当前顶点访问完毕
    }
}

//深度优先搜索DFS算法(全图)
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

//(单个连通域)
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
            //若u尚未被发现，意味着支撑树可在此处拓展
            type(v, u) = TREE;
            parent(u) = v;
            DFS(u, clock);
            break;
        case DISCOVERED:
            //若u已被发现但尚未访问完毕，应属于被后代指向的祖先
            type(v, u) = BACKWARD;
            break;
        default:
            //若u已访问完毕(VISITED，有向图)，则视承袭关系分为前向边和跨边
            type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
            break;
        }
    }
    status(v) = VISITED;
    fTime(v) = ++clock;
}

//基于DFS的拓扑排序算法
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
                    //任意连通域(亦即整图)非DAG
                    S->pop();
                    break;
                }
    } while (s != (v = (++v % n)));
    return S;
}

//基于DFS的拓扑排序算法(单趟)
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
            type(v, u) = BACKWARD; //一旦发现后向边
            return false;
        default:
            type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
            break;
        }
    status(v) = VISITED;
    S->push(vertex(v)); //顶点被标记为VISITED时，随即入栈
    return true;
}

//优先级搜索(全图)
template <typename Tv, typename Te>
template <typename PU>
void Graph<Tv, Te>::pfs(int s, PU prioUpdater)
{
    reset();
    int v = s; //从s开始
    do
    {
        if (status(s) == UNDISCOVERED)
            //一旦遇到尚未发现的顶点，就从该顶点启动一次PFS
            PFS(v, prioUpdater);
    } while (s != (v = (++v % n)));
}

template <typename Tv, typename Te>
template <typename PU>
//顶点、边、优先级更新
void Graph<Tv, Te>::PFS(int s, PU prioUpdater)
{
    //优先级搜索(单个连通域)
    priority(s) = 0;
    status(s) = VISITED;
    parent(s) = -1;
    while (true)
    {
        //将下一顶点和边添加到PFS树中
        for (int w = firstNbr(s); w > -1; w = nextNbr(s, w))
            prioUpdater(this, s, w); //优先级策略更新函数
        for (int shortest = INT_MAX, w = 0; w < n; w++)
            //优先级数越大，优先级越低
            if (status(w) == UNDISCOVERED)
                if (shortest > priority(w))
                {
                    //从尚未加入遍历树的顶点中选出下一个优先级最高的顶点s
                    shortest = priority(w);
                    s = w;
                }
        if (status(s) == VISITED)
            break;//直到所有顶点均已加入,break的是while
        status(s)=VISITED;
        type(parent(s),s)=TREE;
    }
}

