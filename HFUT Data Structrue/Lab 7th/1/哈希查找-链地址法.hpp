#pragma once
struct Node {
	Node* next=nullptr;
	int Data=-1;
	Node(){}
	Node(int Data) :Data(Data) {}
};
class _HashTable {
	Node *Array[10];	//�洢ͷָ���һά����
	int Length=10;	//�洢ͷָ��ĳ�������Ϊ10
public:
	_HashTable() {
		for (int i = 0; i < this->Length; i++)
			Array[i] = new Node;
	}
	void _Insert(int Data) {
		int hashAddress = Data % this->Length;
		//������ͻ
		Node*temp=Array[hashAddress];
		Node*p = new Node(Data);
		while (temp->next!= nullptr)	//�ƶ�����֧��������
			temp = temp->next;
		temp->next = p;					//����洢Data���½��
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