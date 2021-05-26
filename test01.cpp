#include <iostream>
#include <vector>
using namespace std;
struct node
{
	int data;
	node *next;
	node *prior;
};
class DLinkList
{
public:
	DLinkList(vector<int> a, int n);
	int size();
	int get_element(const int &i);
	bool insert(int i, int x);
	bool delete_element(int i);
	void display();
	node *locate(DLinkList L, int i);
	bool judge();
	int count;
	node *head, prior;
};
DLinkList::DLinkList(vector<int> a, int n)
{
	head = new node;
	node *r;
	r = head;
	head->prior = r;
	head->next = r;
	for (int i = 0; i < n; i++)
	{
		node *p = new node;
		p->data = a[i];
		r->next = p;
		p->prior = r;
		p->next = head;
		head->prior = p;
		r = p;
	}
	r->next = head;
	count = count + n;
}
int DLinkList::size()
{
	node *p = head;
	int n = 0;

	while (p->next != head)
	{
		p = p->next;
		n++;
	}
	return n;
}
int DLinkList::get_element(const int &i)
{
	node *p = head;
	int j = 0;
	while (j < i && p != NULL)
	{
		p = p->next;
		j++;
	}
	return p->data;
}
bool DLinkList::insert(int i, int x)
{
	if (i < 1)
		return false;
	node *p = head;
	int j = 0;
	while (p != NULL && j < i - 1)
	{
		p = p->next;
		j++;
	}
	if (p == NULL)
		return false;
	node *s = new node;
	s->data = x;
	s->next = p->next;
	p->next = s;
	count++;
	return true;
}
bool DLinkList::delete_element(int i)
{
	if (i < 1)
		return false;
	node *p = head;
	int j = 0;
	while (p != NULL && j < i - 1)
	{
		p = p->next;
		j++;
	}
	if (p == NULL)
		return false;
	if (p->next == NULL)
		return false;
	node *u = p->next;
	p->next = u->next;
	delete u;
	count--;
}
void DLinkList::display()
{
	node *p = head;
	while (p->next != head)
	{
		p = p->next;
		cout << p->data << " ";
	}
	cout << endl;
}
node *DLinkList::locate(DLinkList L, int i)
{
	int j = 0;
	if (i > count)
		return NULL;
	node *p = head;
	while (p != NULL && j != i)
	{
		p = p->next;
		j++;
	}
	return p;
}
bool DLinkList::judge()
{
	node *p;
	node *q;
	p = head->prior;
	q = head->next;
	while (p->data != q->data)
	{
		return false;
		break;
	}
	while (p->data == q->data && p->prior != head)
	{
		if (p->data == q->data)
		{
			p = p->prior;
			q = q->next;
		}
		if (p->data != q->data)
		{
			return false;
			break;
		}
	}
	while (p->prior == head)
	{
		return true;
		break;
	}
}
void test04()
{
	vector<int> v1 = {10, 30, 40, 55, 60, 70, 80, 99, 100};
	vector<int>v2={1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	DLinkList L1(v1, v1.size());
	DLinkList L2(v2, v2.size());
	L1.display();
	cout<<endl;
	L2.display();
}
void test05()
{
	vector<int> v1 = {1, 2, 3, 4, 5, 4, 3, 2, 1};
	DLinkList L1(v1, v1.size());
	vector<int>v2={1, 2, 3, 4, 5, 5, 4, 3, 2, 1};
	DLinkList L2(v2,v2.size());
	vector<int>v3={1, 2, 3, 4, 5, 6, 3, 2, 1};
	DLinkList L3(v3,v3.size());
	vector<int>v4={1, 2, 3, 4, 5, 5, 6, 4, 3, 2, 1};
	DLinkList L4(v4,v4.size());
	
	cout << L1.judge()<<' '<<L2.judge()<<' '<<L3.judge()<<' '<<L4.judge();
}

int main()
{
	//test04();
	test05();
	system("pause");
	return 0;
}