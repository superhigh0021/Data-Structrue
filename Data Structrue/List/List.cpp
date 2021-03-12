/* 寻秩访问，由秩确定向量元素的物理地址，但是在添加和删除元素后
又不得不移动O(n)个后继元素。局部修改会引起大范围数据结构的调整 */
#include <iostream>
using namespace std;

typedef int Rank;
#define ListNodePosi(T) ListNode<T> * //链表节点位置类型，方便理解和使用

template <typename T>
struct ListNode //以双向链表实现
{
    T data;               //数据
    ListNodePosi(T) pred; //前驱节点
    ListNodePosi(T) succ; //后继节点
                          //构造函数
    ListNode() {}
    ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL)
        : data(e), pred(p), succ(s) {}
    //操作接口
    ListNodePosi(T) insertAsPred(const T &e); //当前节点之前插入
    ListNodePosi(T) insertAsSucc(const T &e); //当前节点之后插入
};

template <typename T>
class List
{ //列表模板类

private:
    int _size;
    ListNodePosi(T) header;
    ListNodePosi(T) trailer; //规模、头哨兵、尾哨兵

protected:
    void init();                                                                  //列表创建时的初始化
    int clear();                                                                  //清除所有节点
    void copyNodes(ListNodePosi(T), int);                                         //复制列表中自位置p起的n项
    ListNodePosi(T) merge(ListNodePosi(T), int, List<T> &, ListNodePosi(T), int); //归并
    void mergeSort(ListNodePosi(T) &, int);                                       //对从p开始连续的n个节点归并排序
    void selectionSort(ListNodePosi(T), int);                                     //对从p开始连续的n个节点选择排序
    void insertionSort(ListNodePosi(T), int);                                     //对从p开始连续的n个节点插入排序
    void radixSort(ListNodePosi(T), int);                                         //对从p开始连续的n个节点基数排序

public:
    // 构造函数
    List() { init(); }                                     //默认
    List(List<T> const &L);                                //整体复制列表L
    List(List<T> const &L, Rank r, int n);                 //复制列表L中自第r项起的n项
    List(ListNodePosi(T) p, int n);                        //复制列表中自位置p起的n项
                                                           // 析构函数
    ~List();                                               //释放（包含头、尾哨兵在内的）所有节点
                                                           // 只读访问接口
    Rank size() const { return _size; }                    //规模
    bool empty() const { return _size <= 0; }              //判空
    T &operator[](Rank r) const;                           //重载，支持循秩访问（效率低）
    ListNodePosi(T) first() const { return header->succ; } //首节点位置
    ListNodePosi(T) last() const { return trailer->pred; } //末节点位置
    bool valid(ListNodePosi(T) p)                          //判断位置p是否对外合法
    {
        return p && (trailer != p) && (header != p);
    }                                      //将头、尾节点等同于NULL
    ListNodePosi(T) find(T const &e) const //无序列表查找
    {
        return find(e, _size, trailer);
    }
    ListNodePosi(T) find(T const &e, int n, ListNodePosi(T) p) const; //无序区间查找
    ListNodePosi(T) search(T const &e) const                          //有序列表查找
    {
        return search(e, _size, trailer);
    }
    ListNodePosi(T) search(T const &e, int n, ListNodePosi(T) p) const;                //有序区间查找
    ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);                               //在p及其n-1个后继中选出最大者
    ListNodePosi(T) selectMax() { return selectMax(header->succ, _size); }             //整体最大者
                                                                                       // 可写访问接口
    ListNodePosi(T) insertAsFirst(T const &e);                                         //将e当作首节点插入
    ListNodePosi(T) insertAsLast(T const &e);                                          //将e当作末节点插入
    ListNodePosi(T) insertA(ListNodePosi(T) p, T const &e);                            //将e当作p的后继插入（After）
    ListNodePosi(T) insertB(ListNodePosi(T) p, T const &e);                            //将e当作p的前驱插入（Before）
    T remove(ListNodePosi(T) p);                                                       //删除合法位置p处的节点,返回被删除节点
    void merge(List<T> &L) { merge(header->succ, _size, L, L.header->succ, L._size); } //全列表归并
    void sort(ListNodePosi(T) p, int n);                                               //列表区间排序
    void sort() { sort(first(), _size); }                                              //列表整体排序
    int deduplicate();                                                                 //无序去重
    int uniquify();                                                                    //有序去重
    void reverse();                                                                    //前后倒置（习题）
                                                                                       // 遍历
    void traverse(void (*)(T &));                                                      //遍历，依次实施visit操作（函数指针，只读或局部性修改）
    template <typename VST>                                                            //操作器
    void traverse(VST &);                                                              //遍历，依次实施visit操作（函数对象，可全局性修改）
};

template <typename T>
void List<T>::init()
{
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ = trailer;
    header->pred = NULL;
    trailer->pred = header;
    trailer->succ = NULL;
    _size = 0;
}

template <typename T>
T &List<T>::operator[](Rank r) const
{
    ListNodePosi(T) p = this->first();
    while (0 < r--)
        p = p->succ;
    return p->data;
}

template <typename T>
ListNodePosi(T) List<T>::find(const T &e, int n, ListNodePosi(T) p) const
{
    while (0 < n--)
        if (e == (p = p->pred)->data)
            return p;
    return NULL;
}

template <typename T>
ListNodePosi(T) List<T>::insertAsFirst(const T &e)
{
    this->_size++;
    return header->insertAsSucc(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertAsLast(const T &e)
{
    this->_size++;
    return trailer->insertAsPred(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertA(ListNodePosi(T) p, const T &e)
{
    this->_size++;
    return p->insertAsSucc(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertB(ListNodePosi(T) p, const T &e)
{
    this->_size++;
    return p->insertAsPred(e);
}

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(const T &e)
{
    ListNodePosi(T) x = new ListNode<T>(e, pred, this);
    pred->succ = x;
    this->pred = x;
    return x;
}

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(const T &e)
{
    ListNodePosi(T) x = new ListNode<T>(e, this, succ);
    this->succ = x;
    succ->pred = x;
    return x;
}

template <typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n)
{
    init();
    while (n--)
    {
        insertAsLast(p->data);
        p = p->succ;
    }
}

template <typename T>
List<T>::List(ListNodePosi(T) p, int n)
{
    copyNodes(p, n);
}

template <typename T>
List<T>::List(const List<T> &L)
{
    copyNodes(L.first(), L.size());
}

template <typename T>
List<T>::List(const List<T> &L, int r, int n)
{
    copyNodes(L[r], n);
}

template <typename T>
T List<T>::remove(ListNodePosi(T) p)
{
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size--;
    return e;
}

template <typename T>
List<T>::~List()
{
    clear();
    delete header;
    delete trailer;
}

template <typename T>
int List<T>::clear()
{
    int oldSize = _size;
    while (0 < _size)
        remove(header->succ);
    return oldSize;
}

template <typename T>
int List<T>::deduplicate()
{
    if (_size < 2)
        return 0;
    int oldSize = _size;
    ListNodePosi(T) p = header;
    Rank r = 0;
    while (trailer != (p = p->succ))
    {
        ListNodePosi(T) q = find(p->data, r, p);
        q ? remove(q) : r++;
    }
    return oldSize - _size;
}

template <typename T>
template <typename VST>
void List<T>::traverse(VST &visit)
{
    //函数对象
    for (ListNodePosi(T) p = header->succ; trailer != p; p = p->succ)
        visit(p->data);
}

template <typename T>
int List<T>::uniquify()
{
    if (_size < 2)
        return 0;
    int oldSize = _size;
    ListNodePosi(T) p = first();
    ListNodePosi(T) q;
    while (trailer != (q = p->succ))
        if (p->data != q->data)
            p = q;
        else
            remove(q);
    return oldSize - _size;
}

template <typename T>
ListNodePosi(T) List<T>::search(const T &e, int n, ListNodePosi(T) p) const
{
    while (0 <= n--)
        if (((p = p->pred)->data) <= e)
            break;
    return p;
}

template <typename T>
void List<T>::sort(ListNodePosi(T) p, int n)
{
    // switch (rand() % 3)
    // {
    // case 1:
    //     insertionSort(p, n);
    //     break;
    // case 2:
    //     selectionSort(p, n);
    //     break;
    // default:
    //     mergeSort(p, n);
    //     break;
    // }
    mergeSort(p, n);
}

template <typename T>
void List<T>::insertionSort(ListNodePosi(T) p, int n)
{
    for (int r = 0; r < n; ++r)
    {
        insertA(search(p->data, r, p), p->data);
        p = p->succ;
        remove(p->pred);
    }
}

template <typename T>
static bool lt(T *a, T *b)
{
    return lt(*a, *b);
}

template <typename T>
bool lt(T a, T b)
{
    return a < b;
}

template <typename T>
void List<T>::selectionSort(ListNodePosi(T) p, int n)
{
    ListNodePosi(T) head = p->pred;
    ListNodePosi(T) tail = p;
    for (int i = 0; i < n; ++i)
        tail = tail->succ;
    while (1 < n)
    {
        ListNodePosi(T) max = selectMax(head->succ, n);
        insertB(tail, remove(max));
        tail = tail->pred;
        --n;
    }
}

template <typename T>
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n)
{
    ListNodePosi(T) max = p;
    for (ListNodePosi(T) cur = p; 1 < n; --n)
    {
        if (!(lt((cur = cur->succ)->data, max->data)))
            max = cur;
    }
    return max;
}

template <typename T>
ListNodePosi(T) List<T>::merge(ListNodePosi(T) p, int n, List<T> &L, ListNodePosi(T) q, int m)
{
    ListNodePosi(T) pp = p->pred;            //归并之后p可能不再指向首节点，故需先记忆，以便在返回前更新
    while ((0 < m) && (q != p))              //q尚未出界（或在mergeSort()中，p尚未出界）之前
        if ((0 < n) && (p->data <= q->data)) //若p尚未出界且v(p) <= v(q)，则
        {
            p = p->succ;
            n--;
        }    //p直接后移，即完成归入
        else //否则，将q转移至p之前，以完成归入
        {
            insertA(p, L.remove((q = q->succ)->pred));
            m--;
        }
    return pp->succ; //更新的首节点
}

template <typename T>
void List<T>::mergeSort(ListNodePosi(T) & p, int n)
{
    if (n < 2)
        return;     //若待排序范围已足够小，则直接返回；否则...
    int m = n >> 1; //以中点为界
    ListNodePosi(T) q = p;
    for (int i = 0; i < m; i++)
        q = q->succ; //找到后子列表起点
    mergeSort(p, m);
    mergeSort(q, n - m);              //前、后子列表各分别排序
    p = merge(p, m, *this, q, n - m); //归并
}

struct show
{
    void operator()(const int &e)
    {
        cout << e << ' ';
    }
};

int main(void)
{
    List<int> l;
    l.insertAsFirst(4);
    l.insertAsFirst(46);
    l.insertAsFirst(18);
    l.insertAsFirst(97);
    l.insertAsFirst(32);
    show w;
    l.traverse(w);
    cout << endl;
    l.sort(l.first(), 4);
    l.traverse(w);

    system("pause");
    return 0;
}