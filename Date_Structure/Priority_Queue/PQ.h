template<typename T>
struct PQ{
    //���ձȽ���ȷ�������ȼ�����������
    virtual void insert(T)=0;
    virtual T getMax()=0;
    virtual T delMax()=0;
};