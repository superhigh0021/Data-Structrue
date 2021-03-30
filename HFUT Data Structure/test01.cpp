#include <iostream>
using namespace std;
#include <string>
#include <vector>
struct Node {
    char data;
    Node* next;
};
class Stack {
public:
    Stack();
    bool empty();
    bool full();
    int size()
    {
        return count;
    }
    int get_top();
    void pop();
    bool push(char& x);

private:
    int count;
    Node* top;
};
class LinkList {
public:
    Node* front;
    LinkList(vector<char> a, int n);
    int count = 0;
    int size()
    {
        return count;
    }
};
LinkList::LinkList(vector<char> a, int n)
{
    front = new Node;
    Node *p = front, *q = front;
    for (int i = 0; i < n; i++) {
        p->next = new Node;
        p = p->next;
        p->data = a[i];
    }
    p->next = NULL;
    q = q->next;
    count = count + n;
}
Stack::Stack()
{
    count = 0;
    top = NULL;
}
bool Stack::empty()
{
    return count == 0;
}
bool Stack::full()
{
    return false;
}
int Stack::get_top()
{
    if (empty())
        return false;
    return top->data;
}
bool Stack::push(char& x)
{
    Node* s = new Node;
    s->data = x;
    s->next = top;
    top = s;
    count++;
    return true;
}
void Stack::pop()
{
    Node* x = top;
    top = top->next;
    delete x;
    count--;
}
bool judge(string& s1)
{
    vector<char> v;
    Stack s;
    string s2;
    for (int i = 0; i < s1.size(); i++) {
        v.push_back(s1[i]);
    }
    LinkList L(v, v.size());
    Node* p = L.front->next;
    for (int i = 0; i < L.size(); i++) {
        s.push(p->data);
        p=p->next;
    }
    while (!s.empty()) {
        s2.push_back(s.get_top());
        s.pop();
    }
    if (s1 == s2)
        return true;
    else
        return false;
}
int main()
{
    string s;
    cin >> s;
    cout << judge(s);
    system("pause");
    return 0;
}