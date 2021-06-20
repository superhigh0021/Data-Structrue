#include <iostream>
using namespace std;

struct node {
    node* next = nullptr;
    int data;
};

void change(node* p)
{
    while (p->next != nullptr)
        p = p->next;
}

int main(void)
{
    node* head = new node;
    head->data = 1;
    head->next = new node;
    head->next->data = 2;
    head->next->next = new node;
    head->next->next = new node;
    head->next->next->data = 3;
    node* p = head;

    change(p);
    cout << p->data;

    system("pause");

    return 0;
}