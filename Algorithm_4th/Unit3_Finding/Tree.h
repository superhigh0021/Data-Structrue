#define Node node<K, V>*
#define templateKV template <typename K, typename V>

#include <iostream>
using namespace std;


templateKV class node {
public:
    node(K key, V value)
        : key(key)
        , value(value)
        , size(1)
    {
    }
    Node left = nullptr;
    Node right = nullptr;
    int size;
    K key;
    V value;
};

templateKV class BST {
public:
    V get(K key);
    void Delete(K key);
    void put(K key, V value);

private:
    Node root = nullptr;
    int size(Node p)
    {
        if (p == nullptr)
            return 0;
        return p->size;
    }
    V get_from(Node p, K key);
    Node put_from(Node p, K key, V value);
    Node Delete_from(Node p, K key);
    Node delMin(Node p);
    Node min(Node p);
};

templateKV
    V
    BST<K, V>::get(K key)
{
    return get_from(root, key);
}

templateKV
    V
    BST<K, V>::get_from(Node p, K key)
{
    if (p == nullptr)
        return -10000;
    if (key < p->key)
        return get_from(p->left, key);
    else if (key > p->key)
        return get_from(p->right, key);
    else
        return p->value;
}

templateKV void
BST<K, V>::put(K key, V value)
{
    root = put_from(root, key, value);
}

templateKV
    Node
    BST<K, V>::put_from(Node p, K key, V value)
{
    if (p == nullptr)
        return new node<K, V>(key, value);
    if (key < p->key)
        p->left = put_from(p->left, key, value);
    else if (key > p->key)
        p->right = put_from(p->right, key, value);
    else
        p->value = value;
    p->size = size(p->left) + size(p->right) + 1;
    return p;
}

templateKV Node BST<K, V>::Delete_from(Node p, K key)
{
    if (p == nullptr)
        exit(0);
    if (key < p->key)
        p->left = Delete_from(p->left, key);
    else if (key > p->key)
        p->right = Delete_from(p->right, key);
    else {
        if (p->right == nullptr)
            return p->left;
        if (p->left == nullptr)
            return p->right;
        Node temp = p;
        p = min(temp->right);
        p->left = temp->left;
        p->right = delMin(temp->right);
    }
    p->size = size(p->left) + size(p->right) + 1;
    return p;
}

templateKV void BST<K, V>::Delete(K key)
{
    root = Delete_from(root, key);
}

templateKV
    Node
    BST<K, V>::min(Node p)
{
    if (p->left == nullptr)
        return p;
    return min(p->left);
}

templateKV
    Node
    BST<K, V>::delMin(Node p)
{
    if (p->left == nullptr)
        return p->right;
    p->left = delMin(p->left);
    p->size = size(p->left) + size(p->right) + 1;
    return p;
}