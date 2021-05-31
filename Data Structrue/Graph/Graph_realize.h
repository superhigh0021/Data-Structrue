#include "Graph.h"
#include "vector.h"

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

    Edge(Te const &d, int w) : data(d), weight(w), type(UNDETERMINED) {}
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
    virtual int firstNbr(int i) { return nextNbr(i, n); } //首个邻接顶点
    virtual int nextNbr(int i, int j)
    {
        while ((-1 < j) && (!exists(i, --j)))
            ;
        return j;
    }
    virtual VStatus &status(int i) { return V[i].status; }
    virtual int &dTime(int i) { return V[i].dTime; }
    virtual int &fTime(int i) { return V[i].fTime; }
    virtual int &parent(int i) { return V[i].priority; }

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
    //喊出顶点i和j之间的联边
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