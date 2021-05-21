#include "Bitmap.h"
#include "dictionary.h"
#include <iostream>
using namespace std;

template <typename K, typename V>
struct Entry {
    K key;
    V value;
    Entry(K k = K(), V v = V())
        : key(k)
        , value(v) {};
    Entry(Entry<K, V> const& e)
        : key(e.key)
        , value(e.value) {};
    bool operator<(Entry<K, V> const& e) { return key < e.key; }
    bool operator>(Entry<K, V> const& e) { return key > e.key; }
    bool operator==(Entry<K, V> const& e) { return key == e.key; }
    bool operator!=(Entry<K, V> const& e) { return key != e.key; }
};

template <typename K, typename V>
class Hashtable : public Dictionary<K, V> {
private:
    Entry<K, V>** ht; //桶数组，存放词条数组
    int M; //桶数组容量
    int N; //词条数量
    Bitmap* lazyRemoval; //懒惰删除标记
#define lazilyRemoved(x) (lazyRemoval->test(x))
#define markAsRemoved(x) (lazyRemoval->set(x))

protected:
    int probe4Hit(const K& k); //沿关键码k对应的试探链，找到词条匹配的桶
    int probe4Free(const K& k); //沿关键码k对应的试探链，找到首个可用空桶
    void rehash(); //重散列算法：扩充桶数组，保证装填因子在警戒线以下

public:
    Hashtable(int c = 5); //创建一个容量不小于c的散列表
    ~Hashtable();
    int size() const { return N; }
    bool put(K, V);
    V* get(K k);
    bool remove(K k);
};

//根据file文件中的记录，在[c,n)内取最小的素数
int primeNLT(int c, int n, char* file)
{
    Bitmap B(file, n);
    while (c < n)
        if (B.test(c))
            c++;
        else
            return c; //返回首个发现的素数
    return c;
}

template <typename K, typename V>
Hashtable<K, V>::Hashtable(int c)
{
    M = primeNLT(c, 1048576, "E:/Data-Structrue/Data Structrue/Dictionary/prime-1048576-bitmap.txt");
    N = 0;
    //开辟桶数组
    ht = new Entry<K, V>*[M];
    memset(ht, 0, sizeof(Entry<K, V>*) * M);
    lazyRemoval = new Bitmap(M);
}

template <typename K, typename V>
Hashtable<K, V>::~Hashtable()
{
    for (int i = 0; i < M; i++)
        if (ht[i])
            release(ht[i]);
    release(ht);
    release(lazyRemoval);
}

//词条的查找算法
template <typename K, typename V>
V* Hashtable<K, V>::get(K k)
{
    int r = probe4Hit(k);
    //禁止词条的key值雷同
    return ht[r] ? &(ht[r]->value) : NULL;
}

//沿关键码k对应的查找链，找到与之匹配的桶
template <typename K, typename V>
int Hashtable<K, V>::probe4Hit(const K& k)
{
    int r = k % M; //从起始桶触发
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
    release(ht[r]);
    ht[r] = NULL;
    markAsRemoved(r);
    N--;
    return true;
}