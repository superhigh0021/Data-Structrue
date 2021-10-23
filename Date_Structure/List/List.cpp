/* Ѱ�ȷ��ʣ�����ȷ������Ԫ�ص�������ַ�����������Ӻ�ɾ��Ԫ�غ�
�ֲ��ò��ƶ�O(n)�����Ԫ�ء��ֲ��޸Ļ������Χ���ݽṹ�ĵ��� */
#include <iostream>
using namespace std;

typedef int Rank;
#define ListNodePosi(T) ListNode<T> * //�����ڵ�λ�����ͣ����������ʹ��

template <typename T>
struct ListNode //��˫������ʵ��
{
    T data;               //����
    ListNodePosi(T) pred; //ǰ���ڵ�
    ListNodePosi(T) succ; //��̽ڵ�
                          //���캯��
    ListNode() {}
    ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL)
        : data(e), pred(p), succ(s) {}
    //�����ӿ�
    ListNodePosi(T) insertAsPred(const T &e); //��ǰ�ڵ�֮ǰ����
    ListNodePosi(T) insertAsSucc(const T &e); //��ǰ�ڵ�֮�����
};

template <typename T>
class List
{ //�б�ģ����

private:
    int _size;
    ListNodePosi(T) header;
    ListNodePosi(T) trailer; //��ģ��ͷ�ڱ���β�ڱ�

protected:
    void init();                                                                  //�б�����ʱ�ĳ�ʼ��
    int clear();                                                                  //������нڵ�
    void copyNodes(ListNodePosi(T), int);                                         //�����б�����λ��p���n��
    ListNodePosi(T) merge(ListNodePosi(T), int, List<T> &, ListNodePosi(T), int); //�鲢
    void mergeSort(ListNodePosi(T) &, int);                                       //�Դ�p��ʼ������n���ڵ�鲢����
    void selectionSort(ListNodePosi(T), int);                                     //�Դ�p��ʼ������n���ڵ�ѡ������
    void insertionSort(ListNodePosi(T), int);                                     //�Դ�p��ʼ������n���ڵ��������
    void radixSort(ListNodePosi(T), int);                                         //�Դ�p��ʼ������n���ڵ��������

public:
    // ���캯��
    List() { init(); }                                     //Ĭ��
    List(List<T> const &L);                                //���帴���б�L
    List(List<T> const &L, Rank r, int n);                 //�����б�L���Ե�r�����n��
    List(ListNodePosi(T) p, int n);                        //�����б�����λ��p���n��
                                                           // ��������
    ~List();                                               //�ͷţ�����ͷ��β�ڱ����ڵģ����нڵ�
                                                           // ֻ�����ʽӿ�
    Rank size() const { return _size; }                    //��ģ
    bool empty() const { return _size <= 0; }              //�п�
    T &operator[](Rank r) const;                           //���أ�֧��ѭ�ȷ��ʣ�Ч�ʵͣ�
    ListNodePosi(T) first() const { return header->succ; } //�׽ڵ�λ��
    ListNodePosi(T) last() const { return trailer->pred; } //ĩ�ڵ�λ��
    bool valid(ListNodePosi(T) p)                          //�ж�λ��p�Ƿ����Ϸ�
    {
        return p && (trailer != p) && (header != p);
    }                                      //��ͷ��β�ڵ��ͬ��NULL
    ListNodePosi(T) find(T const &e) const //�����б�����
    {
        return find(e, _size, trailer);
    }
    ListNodePosi(T) find(T const &e, int n, ListNodePosi(T) p) const; //�����������
    ListNodePosi(T) search(T const &e) const                          //�����б�����
    {
        return search(e, _size, trailer);
    }
    ListNodePosi(T) search(T const &e, int n, ListNodePosi(T) p) const;                //�����������
    ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);                               //��p����n-1�������ѡ�������
    ListNodePosi(T) selectMax() { return selectMax(header->succ, _size); }             //���������
                                                                                       // ��д���ʽӿ�
    ListNodePosi(T) insertAsFirst(T const &e);                                         //��e�����׽ڵ����
    ListNodePosi(T) insertAsLast(T const &e);                                          //��e����ĩ�ڵ����
    ListNodePosi(T) insertA(ListNodePosi(T) p, T const &e);                            //��e����p�ĺ�̲��루After��
    ListNodePosi(T) insertB(ListNodePosi(T) p, T const &e);                            //��e����p��ǰ�����루Before��
    T remove(ListNodePosi(T) p);                                                       //ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�
    void merge(List<T> &L) { merge(header->succ, _size, L, L.header->succ, L._size); } //ȫ�б��鲢
    void sort(ListNodePosi(T) p, int n);                                               //�б���������
    void sort() { sort(first(), _size); }                                              //�б���������
    int deduplicate();                                                                 //����ȥ��
    int uniquify();                                                                    //����ȥ��
    void reverse();                                                                    //ǰ���ã�ϰ�⣩
                                                                                       // ����
    void traverse(void (*)(T &));                                                      //����������ʵʩvisit����������ָ�룬ֻ����ֲ����޸ģ�
    template <typename VST>                                                            //������
    void traverse(VST &);                                                              //����������ʵʩvisit�������������󣬿�ȫ�����޸ģ�
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
    //��������
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
    ListNodePosi(T) pp = p->pred;            //�鲢֮��p���ܲ���ָ���׽ڵ㣬�����ȼ��䣬�Ա��ڷ���ǰ����
    while ((0 < m) && (q != p))              //q��δ���磨����mergeSort()�У�p��δ���磩֮ǰ
        if ((0 < n) && (p->data <= q->data)) //��p��δ������v(p) <= v(q)����
        {
            p = p->succ;
            n--;
        }    //pֱ�Ӻ��ƣ�����ɹ���
        else //���򣬽�qת����p֮ǰ������ɹ���
        {
            insertA(p, L.remove((q = q->succ)->pred));
            m--;
        }
    return pp->succ; //���µ��׽ڵ�
}

template <typename T>
void List<T>::mergeSort(ListNodePosi(T) & p, int n)
{
    if (n < 2)
        return;     //��������Χ���㹻С����ֱ�ӷ��أ�����...
    int m = n >> 1; //���е�Ϊ��
    ListNodePosi(T) q = p;
    for (int i = 0; i < m; i++)
        q = q->succ; //�ҵ������б����
    mergeSort(p, m);
    mergeSort(q, n - m);              //ǰ�������б����ֱ�����
    p = merge(p, m, *this, q, n - m); //�鲢
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

    return 0;
}