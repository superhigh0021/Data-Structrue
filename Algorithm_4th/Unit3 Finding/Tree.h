#include <iostream>
using namespace std;

template <typename K, typename V>
class node
{
public:
    node(K key, V value)
        : key(key), value(value), N(1) {}
    K key;
    V value;
    int N;
    node *left = nullptr;
    node *right = nullptr;
};

template <typename K, typename V>
class Binary_Tree
{
private:
    int size(node<K, V> *p)
    {
        if (p == nullptr)
            return 0;
        else
            return p->N;
    }
    V get(node<K, V> *p, K key);
    node<K, V> *put(node<K, V> *p, K key, V value);
    void Delete(K key)
    {
        root = Delete(root, key);
    }

public:
    node<K, V> *root = nullptr;
    int size() { return size(root); }
    V get(K key);
    node<K, V> *put(K key, V value);
    node<K, V> *Delete(node<K, V> *p, K key);
};

template <typename K, typename V>
V Binary_Tree<K, V>::get(K key)
{
    return get(root, key);
}

template <typename K, typename V>
V Binary_Tree<K, V>::get(node<K, V> *p, K key)
{
    if (p == nullptr)
    {
        cout << "²éÕÒÊ§°Ü!";
        exit(0);
    }
    if (p->key > key)
        return get(p->left, key);
    else if (p->key < key)
        return get(p->right, key);
    else
        return p->value;
}

template <typename K, typename V>
node<K, V> *Binary_Tree<K, V>::put(K key, V value)
{
    root = put(root, key, value);
}

template <typename K, typename V>
node<K, V> *Binary_Tree<K, V>::put(node<K, V> *p, K key, V value)
{
    if (p == nullptr)
        return new node<K, V>(key, value);
    if (p->key > key)
        p->left = put(p->left, key, value);
    else if (p->key < key)
    {
        p->right = put(p->right, key, value);
    }
    else
        p->value = value;
    p->N = size(p->left) + size(p->right) + 1;
    return p;
}

template <typename K, typename V>
node<K, V> *Binary_Tree<K, V>::Delete(node<K, V> *p, K key)
{
    if (p == nullptr)
        return nullptr;
    if (p->key < key)
        p->right = Delete(p->right, key);
    else if (p->key > key)
        p->left = Delete(p->left, key);
    else
    {
        if (p->right == nullptr)
            return p->left;
        if (p->left == nullptr)
            return p->right;
        node<K,V>* temp=p;
    }
}