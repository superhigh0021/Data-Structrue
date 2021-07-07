#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

struct node {
	int data;
	node* next;
};
class LinkList {
public:
	LinkList(vector<int>a, int n);
	int size();
	int get_element(const int& i);
	bool insert(int i, int x);
	bool delete_element(int i);
	void display();
	node* locate(LinkList L, int i);
	bool judge(LinkList& L);
	int count;
	node* head;
};
LinkList::LinkList(vector<int>a, int n) {
	head = new node;
	head->next = head;
	node* r;
	r = head;
	for (int i = 0; i < n; i++) {
		node* p = new node;
		p->data = a[i];
		p->next = NULL;
		r->next = p;
		r = p;
		r->next = head;
	}
	count = count + n;
}
int LinkList::size() {
	node* p = head;
	int n = 0;

	while (p->next != head) {
		p = p->next;
		n++;
	}
	return n;
}
int LinkList::get_element(const int& i) {
	node* p = head;
	int j = 0;
	while (j < i && p != NULL) {
		p = p->next;
		j++;
	}
	return p->data;
}
bool LinkList::insert(int i, int x) {
	if (i < 1)return false;
	node* p = head;
	int j = 0;
	while (p != NULL && j < i - 1) {
		p = p->next;
		j++;
	}
	if (p == NULL)return false;
	node* s = new node;
	s->data = x;
	s->next = p->next;
	p->next = s;
	count++;
	return true;
}
bool LinkList::delete_element(int i) {
	if (i < 1)return false;
	node* p = head;
	int j = 0;
	while (p != NULL && j < i - 1) {
		p = p->next;
		j++;
	}
	if (p == NULL) return false;
	if (p->next == NULL)return false;
	node* u = p->next;
	p->next = u->next;
	delete u;
	count--;
}
void LinkList::display() {
	node* p = head;
	for (int i = 0; i < size(); i++) {
		p = p->next;
		//if (p->next!=head)
		cout << p->data << "  ";

	}
	cout << endl;
}
node* LinkList::locate(LinkList L, int i) {
	int j = 0;
	if (i > count) return NULL;
	node* p = head;
	while (p != NULL && j != i) {
		p = p->next;
		j++;
	}
	return p;
}
bool LinkList::judge(LinkList& L) {
	node* p = head->next;
	if (p == NULL) cout << "链表为空" << endl;
	int j = 1;
	while (p != head) {
		if (fabs(p->data - j) <= 3) {
			p = p->next;
			j++;
			if (p == head)
				return true;
		}
		else
			return false;
	}
}
void public_(LinkList L1, LinkList L2, LinkList& L3) {
	node* p1 = L1.head->next; node* p2 = L2.head->next;
	while (p1 != L1.head && p2 != L2.head) {
		if (p1->data < p2->data)p1 = p1->next;
		else if (p1->data > p2->data)p2 = p2->next;
		else
		{
			L3.insert(L3.count + 1, p1->data);
			p1 = p1->next;
			p2 = p2->next;
		}
	}
    cout<<"交集：";
	L3.display();
}
void bingji(LinkList L1, LinkList L2, LinkList& L3) {
	node* p1 = L1.head->next; node* p2 = L2.head->next;
	while (p1 != L1.head && p2 != L2.head) {
		if (p1->data > p2->data) {
			L3.insert(L3.count + 1, p2->data);
			p2 = p2->next;
		}
		else if (p1->data < p2->data) {
			L3.insert(L3.count + 1, p1->data);
			p1 = p1->next;
		}
		else if (p1->data == p2->data) {
			L3.insert(L3.count + 1, p1->data);
			p1 = p1->next;
			p2 = p2->next;
		}
	}
	if (p1 == L1.head) {
		while (p2 != L2.head) {
			L3.insert(L3.count + 1, p2->data);
			p2 = p2->next;
		}
	}
	else if (p2 == L2.head) {
		while (p1 != L1.head) {
			L3.insert(L3.count + 1, p1->data);
			p1 = p1->next;
		}
	}
    cout<<"并集：";
	L3.display();
}


void test01()
{
	vector<int>v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 60 };
	LinkList L(v, 15);
}

void test02() {
	//vector<int>v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 15, 16, 18 };
	//LinkList L(v, 15);
	vector<int>v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 20, 18};
	LinkList L(v, 16);
}



void test03() {
	vector<int>a = { 1,3,6,10,15,16,17,18,19,20 };
	vector<int>b = { 1,2,3,4,5,6,7,8,9,10,18,20 };
	vector<int>c = { 0 };
	LinkList L1(a, 10);
	LinkList L2(b, 12);
	LinkList L3(c, 0);
	cout << "原链表为："; L1.display();
	cout << "          "; L2.display();
	public_(L1, L2, L3);
	bingji(L1, L2, L3);
}




// #include<iostream>
// #include<vector>
// using namespace std;
// struct node {
// 	int data;
// 	node* next;
// 	node* prior;
// };
// class DLinkList {
// public:
// 	DLinkList(vector<int>a, int n);
// 	int size();
// 	int get_element(const int& i);
// 	bool insert(int i, int x);
// 	bool delete_element(int i);
// 	void display();
// 	node* locate(DLinkList L, int i);
// 	bool judge(DLinkList& L);
// 	int count;
// 	node* head, prior;
// };
// DLinkList::DLinkList(vector<int>a, int n) {
// 	head = new node; node* r;
// 	r = head;
// 	head->prior = r;
// 	head->next = r;
// 	for (int i = 0; i < n; i++) {
// 		node* p = new node;
// 		p->data = a[i];
// 		r->next = p;
// 		p->prior = r;
// 		p->next = head;
// 		head->prior = p;
// 		r = p;
// 	}
// 	r->next = head;
// 	count = count + n;
// }
// int DLinkList::size() {
// 	node* p = head;
// 	int n = 0;

// 	while (p->next != head) {
// 		p = p->next;
// 		n++;
// 	}
// 	return n;
// }
// int DLinkList::get_element(const int& i) {
// 	node* p = head;
// 	int j = 0;
// 	while (j < i && p != NULL) {
// 		p = p->next;
// 		j++;
// 	}
// 	return p->data;
// }
// bool DLinkList::insert(int i, int x) {
// 	if (i < 1)return false;
// 	node* p = head;
// 	int j = 0;
// 	while (p != NULL && j < i - 1) {
// 		p = p->next;
// 		j++;
// 	}
// 	if (p == NULL)return false;
// 	node* s = new node;
// 	s->data = x;
// 	s->next = p->next;
// 	p->next = s;
// 	count++;
// 	return true;
// }
// bool DLinkList::delete_element(int i) {
// 	if (i < 1)return false;
// 	node* p = head;
// 	int j = 0;
// 	while (p != NULL && j < i - 1) {
// 		p = p->next;
// 		j++;
// 	}
// 	if (p == NULL) return false;
// 	if (p->next == NULL)return false;
// 	node* u = p->next;
// 	p->next = u->next;
// 	delete u;
// 	count--;
// }
// void DLinkList::display() {
// 	node* p = head;
// 	while (p->next != head) {
// 		p = p->next;
// 		cout << p->data << " ";
// 	}
// 	cout << endl;
// }
// node* DLinkList::locate(DLinkList L, int i) {
// 	int j = 0;
// 	if (i > count) return NULL;
// 	node* p = head;
// 	while (p != NULL && j != i) {
// 		p = p->next;
// 		j++;
// 	}
// 	return p;
// }
// bool DLinkList::judge(DLinkList& L) {
// 	node* p; node* q;
// 	p = head->prior;
// 	q = head->next;
// 	while (p->data != q->data) {
// 		return false; break;
// 	}
// 	while (p->data == q->data && p->prior != head) {
// 		if (p->data == q->data) {
// 			p = p->prior;
// 			q = q->next;
// 		}
// 		if (p->data != q->data) {
// 			return false; break;
// 		}
// 	}
// 	while (p->prior == head) {
// 		return true; break;
// 	}
// }
// void test04() {
// 	vector<int>v = { 10,30,40,55,60,70,80,99,100 };
// 	DLinkList L(v, 9);
// 	L.display();
// }
// void test05() {
// 	//vector<int>v = { 1, 2, 3, 4, 5, 4, 3, 2, 1 };
// 	//DLinkList L(v, 9);
// 	vector<int>v = { 1,2 };
// 	DLinkList L(v, 2);
// 	cout << L.judge(L);
// }


int main() {
	test01();
	test02();
	test03();
	//test04();
	//test05();
    system("pause");
}