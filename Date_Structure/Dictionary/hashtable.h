#include "Bitmap.h"
#include "dictionary.h"
#include "release.h"
#include <cstring>
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
    Entry<K, V>** ht; //Ͱ���飬��Ŵ�������
    int M; //Ͱ��������
    int N; //��������
    Bitmap* lazyRemoval; //����ɾ�����
#define lazilyRemoved(x) (lazyRemoval->test(x))
#define markAsRemoved(x) (lazyRemoval->set(x))

protected:
    int probe4Hit(const K& k); //�عؼ���k��Ӧ����̽�����ҵ�����ƥ���Ͱ
    int probe4Free(const K& k); //�عؼ���k��Ӧ����̽�����ҵ��׸����ÿ�Ͱ
    void rehash(); //��ɢ���㷨������Ͱ���飬��֤װ�������ھ���������

public:
    Hashtable(int c = 5); //����һ��������С��c��ɢ�б�
    // ~Hashtable();
    int size() const { return N; }
    bool put(K, V);
    V* get(K k);
    bool remove(K k);
};

//����file�ļ��еļ�¼����[c,n)��ȡ��С������
int primeNLT(int c, int n, char* file)
{
    Eratosthenes(n, file);
    Bitmap B(file, n);
    while (c < n)
        if (B.test(c))
            c++;
        else
            return c; //�����׸����ֵ�����
    return c;
}

//�ַ�
static size_t hashCode(char c)
{
    return (size_t)c;
}

//�����Լ�long long int
static size_t hashCode(int k)
{
    return (size_t)k;
}

static size_t hashCode(long long i)
{
    return (size_t)((i >> 32) + (int)i);
}

static size_t hashCode(char s[])
{
    int h = 0;
    for (size_t n = strlen(s), i = 0; i < n; ++i) {
        h = (h << 5) | ((h >> 27));
        h += (int)s[i];
    }
    return (size_t)h;
}

template <typename K, typename V>
Hashtable<K, V>::Hashtable(int c)
{
    M = primeNLT(c, 1048576, "E:/Data-Structrue/Data Structrue/Dictionary/prime-1048576-bitmap.txt");
    N = 0;
    //����Ͱ����
    ht = new Entry<K, V>*[M];
    memset(ht, 0, sizeof(Entry<K, V>*) * M);
    lazyRemoval = new Bitmap(M);
}

// template <typename K, typename V>
// Hashtable<K, V>::~Hashtable()
// {
//     for (int i = 0; i < M; i++)
//         if (ht[i])
//             release(ht[i]);
//     release(ht);
//     release(lazyRemoval);
// }

//�����Ĳ����㷨
template <typename K, typename V>
V* Hashtable<K, V>::get(K k)
{
    int r = probe4Hit(k);
    //��ֹ������keyֵ��ͬ
    return ht[r] ? &(ht[r]->value) : NULL;
}

//�عؼ���k��Ӧ�Ĳ��������ҵ���֮ƥ���Ͱ
template <typename K, typename V>
int Hashtable<K, V>::probe4Hit(const K& k)
{
    int r = k % M; //����ʼͰ����
    while ((ht[r] && (k != ht[r]->key)) || (!ht[r] && lazilyRemoved(r)))
        r = (r + 1) % M; //�ز�����������̽���������г�ͻ��Ͱ�Լ�������ɾ����ǵ�Ͱ
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

template <typename K, typename V>
int Hashtable<K, V>::probe4Free(const K& k)
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
    Entry<K, V>** old_ht = ht;
    M = primeNLT(2 * M, 1048576, "E:/Data-Structrue/Data Structrue/Dictionary/prime-1048576-bitmap.txt");
    N = 0;
    ht = new Entry<K, V>*[M];
    memset(ht, 0, sizeof(Entry<K, V>*) * M);
    release(lazyRemoval);
    lazyRemoval = new Bitmap(M);
    for (int i = 0; i < old_capacity; ++i) {
        if (old_ht[i])
            put(old_ht[i]->key, old_ht[i]->value);
    }
    release(old_ht);
}