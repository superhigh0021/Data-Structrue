#include "Graph.h"
#include "vector.h"

template <typename Tv>
//顶点对象
struct Vertex {
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