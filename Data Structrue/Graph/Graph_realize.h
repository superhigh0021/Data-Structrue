#include "Graph.h"
#include "vector.h"

template <typename Tv>
//�������
struct Vertex {
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
    Vertex(Tv const& d = (Tv)0)
        : data(d)
        , inDegree(0)
        , outDegree(0)
        , status(UNDISCOVERED)
        , dTime(-1)
        , fTime(-1)
        , parent(-1)
        , priority(INT_MAX)
    {
    }
};