#pragma once

#include "Bitmap.h"
#include "Dictionary.h"
#include <cstring>
using namespace std;

template <typename K, typename V>
struct Entry
{
    K key;
    V value;
    Entry(K k = K(), V v = V())
        : key(k), value(v){};
    Entry(Entry<K, V> const &e)
        : key(e.key), value(e.value){};
    bool operator<(Entry<K, V> const &e) { return key < e.key; }
    bool operator>(Entry<K, V> const &e) { return key > e.key; }
    bool operator==(Entry<K, V> const &e) { return key == e.key; }
    bool operator!=(Entry<K, V> const &e) { return key != e.key; }
};

template <typename K, typename V>
class Hashtable : public Dictionary<K, V>
{
private:
    Entry<K, V> **ht;    //桶数组，存放词条数组
    int M;               //桶数组容量
    int N;               //词条数量
    Bitmap *lazyRemoval; //懒惰删除标记
#define lazilyRemoved(x) (lazyRemoval->test(x))
#define markAsRemoved(x) (lazyRemoval->set(x))

protected:
    int probe4Hit(const K &k);  //沿关键码k对应的试探链，找到词条匹配的桶
    int probe4Free(const K &k); //沿关键码k对应的试探链，找到首个可用空桶
    void rehash();              //重散列算法：扩充桶数组，保证装填因子在警戒线以下

public:
    Hashtable(int c = 2); //创建一个容量不小于c的散列表
    ~Hashtable();
    int size() const { return N; }
    bool put(K, V);
    V *get(K k);
    bool remove(K k);
};

//根据file文件中的记录，在[c,n)内取最小的素数
int primeNLT(int c, int n, char *file)
{
    Eratosthenes(n, file);
    Bitmap B(file, n);
    while (c < n)
        if (B.test(c))
            c++;
        else
            return c; //返回首个发现的素数
    return c;
}

//字符
static size_t hashCode(char c)
{
    return (size_t)c;
}

//整数以及long long int
static size_t hashCode(int k)
{
    return (size_t)k;
}

static size_t hashCode(long long i)
{
    return (size_t)((i >> 32) + (int)i);
}


//字符串
static size_t hashCode(string s)
{
    int h = 0;
    for (size_t n = s.size(), i = 0; i < n; ++i)
    {
        h = (h << 5) | ((h >> 27));
        h += (int)s[i];
    }
    return (size_t)h;
}

template <typename K, typename V>
Hashtable<K, V>::Hashtable(int c)
{
    string s="E:/Data-Structrue/HFUT_Data_Structrue/CourseDesign/prime-1048576-bitmap.txt";
    const char* x=s.c_str();
    char* t=const_cast<char*>(x);
    M = primeNLT(c, 1048576,t );
    N = 0;
    //开辟桶数组
    ht = new Entry<K, V> *[M];
    memset(ht, 0, sizeof(Entry<K, V> *) * M);
    lazyRemoval = new Bitmap(M);
}

template <typename K, typename V>
Hashtable<K, V>::~Hashtable()
{
    for (int i = 0; i < M; i++)
        if (ht[i])
            delete ht[i];
    delete ht;
    delete lazyRemoval;
}

//词条的查找算法
template <typename K, typename V>
V *Hashtable<K, V>::get(K k)
{
    int r = probe4Hit(k);
    //禁止词条的key值雷同
    return ht[r] ? &(ht[r]->value) : NULL;
}

//沿关键码k对应的查找链，找到与之匹配的桶
template <typename K, typename V>
int Hashtable<K, V>::probe4Hit(const K &k)
{
    int r = hashCode(k) % M; //从起始桶触发
    while ((ht[r] && (k != ht[r]->key)) || (!ht[r] && lazilyRemoved(r)))
        r = (r + 1) % M; //沿查找链线性试探：跳过所有冲突的桶以及带懒惰删除标记的桶
    return r;
}

template <typename K, typename V>
bool Hashtable<K, V>::remove(K k)
{
    int r = probe4Hit(k);
    if (!ht[r])
        return false;
    delete ht[r];
    ht[r] = NULL;
    markAsRemoved(r);
    N--;
    return true;
}

template <typename K, typename V>
int Hashtable<K, V>::probe4Free(const K &k)
{
    int r = hashCode(k) % M;
    while (ht[r])
        r = (r + 1) % M;
    return r;
}

template <typename K, typename V>
bool Hashtable<K, V>::put(K k, V v)
{
    if (ht[probe4Hit(k)])
        return false;
    int r = probe4Free(k);
    ht[r] = new Entry<K, V>(k, v);
    ++N;
    if (N * 2 > M)
        rehash();
    return true;
}

template <typename K, typename V>
void Hashtable<K, V>::rehash()
{
    int old_capacity = M;
    Entry<K, V> **old_ht = ht;
    string s= "E:/Data-Structrue/HFUT_Data_Structrue/CourseDesign/prime-1048576-bitmap.txt";
    const char* c=s.c_str();
    char* t=const_cast<char*>(c);
    M = primeNLT(2 * M, 1048576, t);
    N = 0;
    ht = new Entry<K, V> *[M];
    memset(ht, 0, sizeof(Entry<K, V> *) * M);
    delete lazyRemoval;
    lazyRemoval = new Bitmap(M);
    for (int i = 0; i < old_capacity; ++i)
    {
        if (old_ht[i])
            put(old_ht[i]->key, old_ht[i]->value);
    }
    delete old_ht;
}
