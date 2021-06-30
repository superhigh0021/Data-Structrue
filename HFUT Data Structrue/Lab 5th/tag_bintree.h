#include <iostream>
#include <string.h>
using namespace std;
#define BinNodePosi(T) BinNode<T>*

template <typename T>
class BinNode {
public:
    BinNode(const T& data)
        : _data(data)
        , lchild(nullptr)
        , rchild(nullptr)
        , parent(nullptr)
        , Ltag(0)
        , Rtag(0)
    {
    }
    char _data;
    BinNodePosi(T) lchild;
    BinNodePosi(T) rchild;
    BinNodePosi(T) parent;
    bool Ltag, Rtag;
};

template <typename T>
void travIn_R(BinNodePosi(T) x, int n)
{
    if (!x)
        return;
    ++n;
    travIn_R(x->lchild, n);
    cout << x->_data <<":"<< n << "  ";
    travIn_R(x->rchild, n);
}


template <typename T>
class Thread_BiTree {
public:
    //���� --������
    Thread_BiTree(string s)
        : _pRoot(nullptr)
        , Prev(nullptr)
    {
        size_t index = 0;
        _CreatTree(_pRoot, s, s.size(), index); //����������
    }

protected:
    void _CreatTree(BinNodePosi(T) & Root, string s, size_t size, size_t& index)
    {
        if (size == 0) {
            cout << "�������� " << endl;
            return;
        }
        if (index < size && s[index] != '#') {
            Root = new BinNode<T>(s[index]);
            _CreatTree(Root->lchild, s, size, ++index);
            _CreatTree(Root->rchild, s, size, ++index);
        }
    }

public:
    void travIn(){
        travIn_R(_pRoot,0);
    }

public:
    //����--������������
    void PreOrderThreading()
    {
        _PreOrderThreading(this->_pRoot);
    }
    //����--���� ����������
    void PreOrder()
    {
        _PreOrder(this->_pRoot);
    }

protected:
    //����--������������--C
    //˼·���ȿ��������� ����һ���ڵ��ʱ���ټ����һ���ڵ���ҽڵ�
    void _PreOrderThreading(BinNodePosi(T) & Root)
    {
        if (Root == NULL) {
            return;
        }
        if (Root->lchild == NULL) //û��������
        {
            Root->lchild = Prev; //ǰ��
            Root->Ltag = 1;
        }
        if (Prev != NULL && Prev->rchild == NULL) // ��һ���ڵ���û��������
        { //Prev��һ�ν��� Ϊ��
            Prev->rchild = Root; //���
            Prev->Rtag = 1;
        }
        Prev = Root; //ǰ��,ÿ�μ�ס�ϴεĽڵ�

        //�ж�Root�Ƿ������Һ���
        if (Root->Ltag == 0)
            _PreOrderThreading(Root->lchild);
        if (Root->Rtag == 0)
            _PreOrderThreading(Root->rchild);
    }
    //����--���� ����������--C
    void _PreOrder(BinNodePosi(T) Root)
    {
        if (Root == NULL) {
            return;
        }
        BinNodePosi(T) pCur = Root;
        while (pCur != NULL) {
            while (pCur->lchild != NULL && pCur->Ltag == 0) //�ҵ�����ߵĽڵ�,����һֱΪ1
            {
                cout << pCur->_data << ' ';
                pCur = pCur->lchild;
            }
            //����������ߵĵĽڵ㻹û�з���
            cout << pCur->_data << ' ';

            if (pCur->Ltag == 1) //�������� �Ϳ��ҽڵ�
            {
                pCur = pCur->rchild;
            }
            while (pCur != NULL) //ѭ���ҽڵ�
            {
                if (pCur->lchild != NULL && pCur->Ltag == 0) //������ڵ���� �� �����
                    break;
                cout << pCur->_data << ' ';
                pCur = pCur->rchild;
            }
        }
    }

public:
    //����--������������
    void InOrderThreading()
    {
        _InOrderThreading(_pRoot);
    }
    //����--��������������
    void InOrder()
    {
        _InOrder(this->_pRoot);
    }

protected:
    //����--������������--C
    //˼·:�� ��-��-�ҵ�˳��   ���ҵ�����ߵĽڵ�-> ����������һ�� ,��������������ִ�е���һ���ڵ��ڿ��ϴνڵ�������� -> ������
    void _InOrderThreading(BinNodePosi(T) & Root)
    {
        if (Root == NULL) {
            return;
        }
        _InOrderThreading(Root->lchild); // ��

        if (Root->lchild == NULL) //��
        {
            Root->Ltag = 1;
            Root->lchild = Prev;
        }
        if (Prev != NULL && Prev->rchild == NULL) {
            Prev->rchild = Root;
            Prev->Rtag = 1;
        }
        Prev = Root;
        _InOrderThreading(Root->rchild); //��
    }
    //����--����������--C
    //˼·���ҵ�����ʼ�Ľڵ㣨����ߵĽڵ㣩-> (��� )���ĸ��ڵ㣬��û�������ҽڵ�
    void _InOrder(BinNodePosi(T) Root)
    {
        if (Root == NULL) {
            return;
        }
        BinNodePosi(T) pCur = Root;
        while (pCur) {
            while (pCur->Ltag == 0) //������ߵĽڵ�
            {
                pCur = pCur->lchild;
            }
            cout << pCur->_data << ' ';

            while (pCur && pCur->Rtag == 1) //�������̽ڵ�
            {
                pCur = pCur->rchild;
                cout << pCur->_data << ' ';
            }
            //û�к�̣���������
            pCur = pCur->rchild;
        }
    }

public:
    //����--����������
    void PostOrderThreading()
    {
        _PostOrderThreading(_pRoot);
    }

    void PostOrder()
    {
        _PostOrder(this->_pRoot);
    }

protected:
    //����--����������--C
    //˼·����-��-��  ��ǰ���һ��
    void _PostOrderThreading(BinNodePosi(T) & Root)
    {
        if (Root == NULL) {
            return;
        }
        _PostOrderThreading(Root->lchild);
        _PostOrderThreading(Root->rchild);

        if (Root->lchild == NULL) {
            Root->lchild = Prev;
            Root->Ltag = 1;
        }
        if (Prev != NULL && Prev->rchild == NULL) {
            Prev->rchild = Root;
            Prev->Rtag = 1;
        }
        if(Prev!=NULL&&Prev->rchild!=NULL)
        Prev->parent=Root;
        Prev = Root;
    }

    void _PostOrder(BinNodePosi(T) Root)
    {
        if (Root) {
            BinNodePosi(T) pCur = Root;
            Prev = NULL;
            while (pCur != NULL) {
                //��һ������������ߵĽڵ�
                while (pCur->lchild != Prev && pCur->Ltag == 0) //������
                {
                    pCur = pCur->lchild;
                }
                //ѭ�������� pCur== Root ����Ϊ��

                //�ڶ��������ʺ��
                while (pCur && pCur->Rtag == 1) {
                    cout << pCur->_data << ' ';
                    Prev = pCur;
                    pCur = pCur->rchild;
                }
                //�жϴ�ʱpCur�ǲ���ָ���˸��ڵ�
                if (pCur == Root) {
                    cout << pCur->_data << ' ';
                    return;
                }
                while (pCur && pCur->rchild == Prev) {
                    cout << pCur->_data << ' ';
                    Prev = pCur;
                    pCur = pCur->parent; //����һ����
                }
                //���ﲻ����NULL�жϣ�������Rtag
                if (pCur && pCur->Rtag == 0) {
                    pCur = pCur->rchild;
                }
            }
            //end-while
        }
    }

public:
    void insert_as_lchild(BinNodePosi(T) p,const T& e){
        if(p->lchild==nullptr)
            p->lchild=new BinNode<T>(e);
    }
    
    void insert_as_rchild(BinNodePosi(T) p, const T& e){
        if(p->rchild==nullptr)
            p->rchild=new BinNode<T>(e);
    }

    
    BinNodePosi(T) _pRoot = nullptr;
    BinNodePosi(T) Prev = nullptr; //��¼
};