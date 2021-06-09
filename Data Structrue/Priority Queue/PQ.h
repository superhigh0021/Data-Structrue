template<typename T>
struct PQ{
    //按照比较器确定的优先级次序插入词条
    virtual void insert(T)=0;
    virtual T getMax()=0;
    virtual T delMax()=0;
};