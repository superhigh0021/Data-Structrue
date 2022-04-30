#include <iostream>
using namespace std;

using Rank = int;          //秩
#define DEFAULT_CAPACITY 3 //默认的初始容量(实际应用中可能更大)

template <typename T>
class Vector {
public:
    //! 构造函数
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) {
        //! s < c (size < capacity)
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v)
            ;
    }

    //数组整体复制
    Vector(const T* A, Rank n) { copyFrom(A, 0, n); }

    //数组区间复制
    Vector(const T* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }

    //完整拷贝构造函数
    Vector(const Vector<T>& V) { copyFrom(V._elem, 0, V._size); }

    //区间拷贝构造函数
    Vector(const Vector<T>& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); }

    //! 析构函数
    ~Vector() { delete[] _elem; }

    //! 只读访问接口

    Rank size() const { return _size; }

    bool empty() const { return !_size; }

    //判断vector是否已排序
    int disordered() const;

    //无序向量整体查找
    Rank find(T const& e) const { return find(e, 0, _size); }

    //无须向量区间查找
    Rank find(T const& e, Rank lo, Rank hi) const;

    //有序向量整体查找
    Rank search(T const& e) const {
        return (_size <= 0) ? -1 : search(e, 0, _size);
    }

    //有序向量区间查找
    Rank search(T const& e, Rank lo, Rank hi) const;

    //! 可写访问接口

    //重载下标操作符
    T& operator[](Rank r);

    //重载赋值操作符，以便直接克隆向量
    Vector<T>& operator=(Vector<T> const&);

    //删除元素
    T remove(Rank r);

    //区间删除 [lo,hi)
    int remove(Rank lo, Rank hi);

    //插入元素
    Rank insert(Rank r, T const& e);

    //默认作为尾元素插入
    Rank insert(T const& e) { return insert(_size, e); }

    //区间排序
    void sort(Rank lo, Rank hi);

    //整体排序
    void sort() { sort(0, _size); }

    //区间置乱
    void unsort(Rank lo, Rank hi);

    //整体置乱
    void unsort() { unsort(0, _size); }

    //无序去重
    int deduplicate();

    //有序去重
    int uniquify();

    //! 遍历
    //遍历(使用函数指针，只读或局部性修改)
    void traverse(void (*)(T&));

    //遍历(使用函数对象，可全局性修改)
    template <typename VST>
    void traverse(VST&);

protected:
    // Rank _size;
    // int _capacity;
    // T* _elem;

    //复制区间A[lo,hi)
    void copyFrom(T const* A, Rank lo, Rank hi);

    //空间不足时扩容
    void expand();

    //装填因子过小时压缩
    void shrink();

    //扫描交换
    bool bubble(Rank lo, Rank hi);

    //冒泡排序算法
    void bubbleSort(Rank lo, Rank hi);

    //选取最大元素
    Rank maxItem(Rank lo, Rank hi);

    //选择排序算法
    void selectionSort(Rank lo, Rank hi);

    //归并算法
    void merge(Rank lo, Rank mi, Rank hi);

    //归并排序算法
    void mergeSort(Rank lo, Rank hi);

    //堆排序算法
    void heapSort(Rank lo, Rank hi);

    //轴点partition构造算法
    Rank partition(Rank lo, Rank hi);

    //快速排序算法
    void quickSort(Rank lo, Rank hi);

    //希尔排序算法
    void shellSort(Rank lo, Rank hi);

private:
    Rank _size;
    int _capacity;
    T* _elem;
};

template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
    _elem = new T[_capacity = 2 * (hi - lo)];
    _size = 0; //分配空间，规模清零
    while (lo < hi) {
        _elem[size++] = A[lo++];
    }
}

//* 由于vector内部有动态分配的空间，默认的=运算符不足以支持向量之间的直接赋值
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& V) {
    if (_elem)
        delete[] _elem; //释放原有内容
    copyFrom(V._elem, 0, V.size());
    return *this;
}

template <typename T>
void Vector<T>::expand() {
    if (_size < _capacity)
        return;
    if (_capacity < DEFAULT_CAPACITY)
        _capacity = DEFAULT_CAPACITY;
    T* oldElem = _elem;
    _elem = new T[_capacity <<= 1];
    for (int i = 0; i < _size; ++i)
        _elem[i] = oldElem[i];
    delete[] oldElem;
}

template <typename T>
void Vector<T>::shrink() {
    if (_capacity < DEFAULT_CAPACITY << 1)
        return;
    if (_size << 2 > _capacity)
        return;
    T* oldElem = _elem;
    _elem = new T[_capacity >>= 1];
    for (int i = 0; i < _size; ++i)
        _elem[i] = oldElem[i];
    delete[] oldElem;
}

template <typename T>
T& Vector<T>::operator[](Rank r) {
    return _elem[r];
}

template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
    T* V = _elem + lo;
    for (Rank i = hi - lo; i > 0; --i)
        swap(V[i - 1], V[rand() % i]);
}

template <typename T>
static bool lt(T* a, T* b) {
    return lt(*a, *b);
}

template <typename T>
bool lt(const T& a, const T& b) {
    return a < b;
}

template <typename T>
static bool eq(T* a, T* b) {
    return eq(*a, *b);
}

template <typename T>
static bool eq(const T& a, const T& b) {
    return a == b;
}

//返回最后一个元素e的位置
template <typename T>
Rank Vector<T>::find(const T& e, Rank lo, Rank hi) const {
    while ((lo < hi--) && (e != _elem[hi]))
        ;
    return hi;
}

//将元素e作为秩为r的元素插入
template <typename T>
Rank Vector<T>::insert(Rank r, const T& e) {
    this->expand();
    for (int i = _size; i > r; --i)
        _elem[i] = _elem[i - 1];
    _elem[r] = e;
    _size++;

    return r;
}

template <typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
    if (lo == hi)
        return 0;
    
    //[hi,_size)顺次前移hi-lo个单元
    while (hi < _size)
        _elem[lo++] = _elem[hi++];
    _size = lo;
    this->shrink();

    return hi - lo; //返回被删除元素的数目
}

template <typename T>
T Vector<T>::remove(Rank r) {
    T e = _elem[r];
    this->remove(r, r + 1);
    return e;   //返回被删除的元素
}

//删除无须向量中的重复元素
template <typename T>
int Vector<T>::deduplicate() {
    int oldSize = _size;
    Rank i = 1;
    while (i < _size)
        this->find(_elem[i], 0, i) < 0 ? i++ : this->remove(i);
    return oldSize - _size;
}

template <typename T>
template <typename VST>
void Vector<T>::traverse(VST& visit) {
    for (int i = 0; i < _size; ++i)
        visit(_elem[i]); //遍历vector
}

struct Increase {
    template <typename T>
    void operator()(T& e) {
        ++e;
    }
};

template <typename T>
void increase(Vector<T>& V) {
    Increase i;
    V.traverse(i);
}

struct Decrease {
    template <typename T>
    void operator()(T& e) {
        --e;
    }
};

template <typename T>
void decrease(Vector<T>& V) {
    Decrease d;
    V.traverse(d);
}

//返回vector中逆序相邻元素对的总数
template <typename T>
int Vector<T>::disordered() const {
    int n = 0;
    for (int i = 1; i < _size; ++i) {
        if (_elem[i - 1] > _elem[i])
            ++n;
    }
    return n;
}

template <typename T>
int Vector<T>::uniquify() {
    Rank i = 0, j = 0;
    while (++j < _size) {
        if (_elem[i] != _elem[j])
            _elem[++i] = _elem[j];
    }
    _size = ++i;
    this->shrink();

    return j - i;
}

template <typename T>
static Rank binSearch(T* A, const T& e, Rank lo, Rank hi) {
    while (lo < hi) {
        Rank mi = (lo + hi) >> 1;
        if (A[mi] > e)
            hi = mi;
        else if (A[mi] < e)
            lo = mi + 1;
        else
            return mi;
    }
    return -1;
}

class Fib { // Fibonacci������
private:
    int f, g; // f = fib(k - 1), g = fib(k)����Ϊint�ͣ��ܿ�ͻ���ֵ���
public:
    Fib(int n) //��ʼ��Ϊ��С��n����СFibonacci��
    {
        f = 1;
        g = 0;
        while (g < n)
            next();
    }                       // fib(-1), fib(0)��O(log_phi(n))ʱ��
    int get() { return g; } //��ȡ��ǰFibonacci�O(1)ʱ��
    int next() {
        g += f;
        f = g - f;
        return g;
    } //ת����һFibonacci�O(1)ʱ��
    int prev() {
        f = g - f;
        g -= f;
        return g;
    } //ת����һFibonacci�O(1)ʱ��
};

template <typename T>
static Rank fibSearch(T* A, const T& e, Rank lo, Rank hi) {
    Fib fib(hi - lo);
    while (lo < hi) {
        while (hi - lo < fib.get())
            fib.prev();
        Rank mi = lo + fib.get() - 1;
        if (e < A[mi])
            hi = mi;
        else if (A[mi] < e)
            lo = mi + 1;
        else
            return mi;
    }
}

template <typename T>
Rank Vector<T>::search(const T& e, Rank lo, Rank hi) const {
    return (rand() % 2) ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
}

template <typename T>
void Vector<T>::sort(Rank lo, Rank hi) {
    switch (rand() % 2) {
    case 1:
        bubbleSort(lo, hi);
        break;
    case 2:
        mergeSort(lo, hi);
        ;
        break;
    // case 3:
    //     selectionSort(lo, hi);
    //     break;
    // case 4:
    //     heapSort(lo, hi);
    //     break;
    default:
        // quickSort(lo, hi);
        break;
    }
}

template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
    while (!bubble(lo, hi))
        ;
}

template <typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) {
    bool sorted = true;
    while (++lo < hi) {
        if (_elem[lo - 1] > _elem[lo]) {
            sorted = false;
            swap(_elem[lo - 1], _elem[lo]);
        }
    }
    return sorted;
}

template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
    if (hi - lo < 2)
        return;
    int mi = (lo + hi) / 2;
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    merge(lo, mi, hi);
}

template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
    T* A = _elem + lo;
    int lb = mi - lo;
    T* B = new T[lb];
    for (Rank i = 0; i < lb; ++i)
        B[i] = A[i];
    int lc = hi - mi;
    T* C = _elem + mi;
    for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);) {
        if ((j < lb) && (!(k < lc) || (B[j] <= C[k])))
            A[i++] = B[j++];
        if ((k < lc) && (!(j < lb) || (C[k] < B[j])))
            A[i++] = C[k++];
    }
    delete[] B;
}