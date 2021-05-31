#include "Graph.h"
#include "vector.h"

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

    Edge(Te const &d, int w) : data(d), weight(w), type(UNDETERMINED) {}
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
    virtual int firstNbr(int i) { return nextNbr(i, n); } //�׸��ڽӶ���
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
    //��������i��j֮�������
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