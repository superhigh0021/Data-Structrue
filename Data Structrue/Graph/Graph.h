#pragma once
#include <stack>
#include "vector.h"
#include <queue>
#include <iostream>

//����״̬
typedef enum
{
    UNDISCOVERED,
    DISCOVERED,
    VISITED
} VStatus;
//���ڱ�����������������
typedef enum
{
    UNDETERMINED,
    TREE,
    CROSS,
    FORWARD,
    BACKWARD
} EType;

template <typename Tv, typename Te>
class Graph
{
private:
    //���ж��㡢�ߵĸ�����Ϣ��λ
    void reset()
    {
        //���ж����
        for (int i = 0; i < n; ++i)
        {
            //״̬��ʱ���ǩ
            status(i) = UNDISCOVERED;
            dTime(i) = fTime(i) = -1;

            //�ڱ������еĸ��ڵ㣬���ȼ���
            parent(i) = -1;
            priority(i) = INT_MAX;
            for (int j = 0; j < n; ++j)
                if (exist(i, j))
                    type(i, j) = UNDETERMINED; //����
        }
    }
    void BFS(int, int &);                //(��ͨ��)������������㷨
    void DFS(int, int &);                //(��ͨ��)������������㷨
    void BCC(int, int &, stack<int> &);  //(��ͨ��)����DFS��˫��ͨ�����ֽ��㷨
    bool TSort(int, int &, stack<Tv> *); //(��ͨ��)����DFS�����������㷨
    template <typename PU>
    void PFS(int, PU); //(��ͨ��)���ȼ��������
public:
    //����
    int n�� //��������
        virtual int
        insert(Tv const &) = 0;        //���붥�㣬���ر��
    virtual Tv remove(int) = 0;        //ɾ�����㼰������ߣ����ظö�����Ϣ
    virtual Tv &vertex(int) = 0;       //����v������
    virtual int inDegree(int) = 0;     //����v�����
    virtual int outDegree(int) = 0;    //����v�ĳ���
    virtual int firstNbr(int) = 0;     //����v���׸��ڽӶ���
    virtual int nextNbr(int, int) = 0; //����v����ڶ���j����һ���ڽӶ���
    virtual VStatus &status(int) = 0;  //����v��״̬
    virtual int &dTime(int) = 0;       //����v��ʱ���ǩdTime
    virtual int &fTime(int) = 0;       //����v��ʱ���ǩfTime
    virtual int &parent(int) = 0;      //�����ڱ������еĸ���
    virtual int &priority(int) = 0;    //����v�ڱ������е����ȼ���

    //�ߣ�����Լ��������߾�ͳһת��Ϊ�������һ������ߣ��Ӷ�������ͼ��������ͼ������

    int e;                                              //������
    virtual bool exists(int, int) = 0;                  //�жϱ�(v,u)�Ƿ����
    virtual void insert(Te const &, int, int, int) = 0; //�ڶ���v��u֮�����Ȩ��Ϊw�ı�e
    virtual Te remove(int, int) = 0;                    //ɾ������v��u֮��ı�e�����ظñ���Ϣ
    virtual EType &type(int, int) = 0;                  //��(v,u)������(�ñߵ�ȷ����)
    virtual int &weight(int, int) = 0;                  //��(v,u)��Ȩ��
    //�㷨
    void bfs(int);                          //������������㷨
    void dfs(int);                          //������������㷨
    void bcc(int);                          //����DFS��˫��ͨ�����ֽ��㷨
    stack<Tv> *tSort(int);                  //����DFS�����������㷨
    void prim(int);                         //��С֧����Prim�㷨
    void dijkstra(int);                     //���·��Dijkstra�㷨
    template<typename PU> void pfs(int, PU); //���ȼ��������
};
