#pragma once
struct Node {
	Node* next=nullptr;
	int Data=-1;
	Node(){}
	Node(int Data) :Data(Data) {}
};
class _HashTable {
	Node *Array[10];	//存储头指针的一维数组
	int Length=10;	//存储头指针的长度设置为10
public:
	_HashTable() {
		for (int i = 0; i < this->Length; i++)
			Array[i] = new Node;
	}
	void _Insert(int Data) {
		int hashAddress = Data % this->Length;
		//发生冲突
		Node*temp=Array[hashAddress];
		Node*p = new Node(Data);
		while (temp->next!= nullptr)	//移动到分支链表的最后
			temp = temp->next;
		temp->next = p;					//插入存储Data的新结点
	}
	int search(int data) {
		int hashAddress = data % this->Length;
		for (int i = 0; i < Length; i++) {
			Node* temp = Array[i];
			while (temp != nullptr) {
				if (temp->Data == data) {
					return i;
				}
				temp = temp->next;
			}
		}
		return -1;
	}
};