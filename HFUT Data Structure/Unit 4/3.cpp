#include <iostream>
using namespace std;

template <typename T>
struct node {
    T data;
    node* next;
};

template <typename T>
class LinkedList {
private:
    node* front;

public:
    LinkedList(const T& x);
    LinkedList(int a[], int n);
    void convert();
    ~LinkedList();
};
template <typename T>
LinkedList<T>::LinkedList(const T& x)
{
    front = new node;
    front->data = x;
    front->next = NULL;
}
template <typename T>
LinkedList<T>::LinkedList(int a[], int n)
{
    front = new node;
    node *p = front, *q = front;
    for (int i = 0; i < n; i++) {
        p->next = new node;
        p = p->next;
        p->data = a[i];
    }
    p->next = NULL;
    q = q->next;
}
template<typename T>
void LinkedList<T>::convert(){
    node* p,q,t;
    p=front->next;
    q=NULL;
    front->next=NULL;
    while(p){
        pr=p->next;
        p->next=q;
        q=p;
        p=pr;
    }
    front->next=q;
}