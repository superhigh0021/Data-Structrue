#include <iostream>
using namespace std;

template <typename K, typename V>
class Binary_Tree {
public:
    node(K, V) root = nullptr;
    int size() { return size(root); }
    V get(K key);
    void put(K key, V value);

private:
    class node {
        node(K key, V value)
            : key(key)
            , value(value)
            , N(1) {}
        K key;
        V value;
        int N;
        typename node<K, V>* left;
        typename node<K, V>* right;
    };

    int size(node* p) { return p->N; }
    V get(node* p, K key);
    void put(node* p, K key, V value)
};

template <typename K, typename V>
V Binary_Tree<K, V>::get(K key)
{
    return get(root, key);
}

template <typename K, typename V>
V Binary_Tree<K, V>::get(node* p, K key)
{
    if (p == nullptr)
        return;
    if (p->key > key)
        return get(p->left, key);
    else if (p->key < key)
        return get(p->right, key);
    else
        return p->value;
}

template <typename K, typename V>
void Binary_Tree<K, V>::put(K key, V value)
{
    root = put(root, key, value);
}

template <typename K, typename V>
void Binary_Tree<K, V>::put(node* p, K key, V value)
{
    if (p == nullptr)
        return new node(key, value);
    if (p->key > key)
        return put(p->left, key);
}