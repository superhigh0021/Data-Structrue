#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* pred;
    Node* succ;
    Node(){}
    Node(int e) {this->data=e;}
};

class List
{
public:
    int _size;
    Node* header;
    Node* trailer;

    void init();
    List() { init(); }
    Node* first() const { return header->succ; } //首节点位置
    Node* last() const { return trailer->pred; } //末节点位置
    ~List();
    int clear();
    int remove(Node* p);
    Node* insertAsFirst(int e);
};

void List::init()
{
    header = new Node;
    trailer = new Node;
    // Node* a = new Node(13);
    // Node* b= new Node(24);
    // Node* c= new Node(34);
    // header->succ = a;
    // header->pred = NULL;
    // a->pred=header;
    // a->succ=b;
    // b->pred=a;
    // b->succ=c;
    // c->pred=b;
    // c->succ=trailer;
    // trailer->pred = c;
    // trailer->succ = NULL;
    header->pred=NULL;
    header->succ=trailer;
    trailer->pred=header;
    trailer->succ=NULL;
    _size = 3;
}

Node* List::insertAsFirst(int e){
    Node* p=new Node(e);
    header->succ->pred=p;
    p->pred=header;
    p->succ=header->succ;
    header->succ=p;

    return p;
}

int List::remove(Node* p){
    int e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size--;
    return e;
}

int List::clear(){
    int oldSize = _size;
    while (0 < _size)
        remove(header->succ);
    return oldSize;
}

List::~List(){

    clear();
    delete header;
    delete trailer;
}

int main(void){
    List l;
    l.insertAsFirst(7);
    l.insertAsFirst(19);

    return 0;
}