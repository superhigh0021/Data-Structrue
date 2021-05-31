//顶点状�?
typedef enum { UNDISCOVERED,
    DISCOVERED,
    VISITED } VStatus;
//边在遍历树中所属的类型
typedef enum { UNDETERMINED,
    TREE,
    CROSS,
    FORWARD,
    BACKWARD } EType;

template <typename Tv, typename Te>
class Graph {
private:
    //所有定点、边的辅助信息复�?
    void reset()
    {
        //所有顶�?
        for (int i = 0; i < n; ++i) {
            //状态，时间标签
            status(i) = UNDISCOVERED;
            dTime(i) = fTime(i) = -1;

            //在遍历树中的父节点，优先级数
            parent(i) = -1;
            priority(i) = INT_MAX;
            for (int j = 0; j < n; ++j)
                if (exist(i, j))
                    type(i, j) = UNDETERMINED;//类型
        }
    }

};
