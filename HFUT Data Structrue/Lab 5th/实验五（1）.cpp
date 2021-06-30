#include<iostream>
#include<fstream> 
using namespace std;
ifstream Tree;//����ȫ�ֵ��������ļ� 
struct bnode{
	char data;
	int rtag,ltag;
	int high; 
	bnode*Lchild;
	bnode*Rchild;
};
void creat(bnode*&T,int h){
	char num;
	Tree>>num;
	if(num=='#')T=NULL;
	else{
		T=new bnode;
		T->data=num;
		T->high=h;
		creat(T->Lchild,h+1); 
		creat(T->Rchild,h+1);
	}
}
void tag(bnode*T){
	if(T->Lchild==NULL) T->ltag=1;
	else T->ltag=0;
	if(T->Rchild==NULL) T->rtag=1;
	else T->rtag=0;
	if(T->ltag==0)
	tag(T->Lchild);
	if(T->rtag==0)
	tag(T->Rchild);
}
bnode*target;
void find(bnode*&Root,char a){
	if (Root == NULL)
		{
			return;
		}
		bnode* pCur = Root;
		while (pCur)
		{ 
			while (pCur->ltag == 0) //������ߵĽڵ�
			{
				if(pCur->data==a){
		    	target=pCur;
		    	return;
			    }
			    pCur = pCur->Lchild;
			}
			while ( pCur && pCur->rtag == 1)//�������̽ڵ�
			{
				if(pCur->data==a){
		    	target=pCur;
		    	return;
			    }
			    pCur = pCur->Rchild;
			}
			//û�к�̣��������� 
			if(pCur)
			pCur = pCur->Rchild;
		}
} 
void ThreadPreorder( bnode*T,bnode*&pre)//��ʼ����ʱ��pre��ֵΪnull;
{       
    if ( T != NULL ) {
        if(T->Lchild==NULL)// *T��ǰ�������� 
        T->Lchild=pre;       
        if(pre!=NULL&&pre->rtag==1)// *pre�ĺ��������  
        pre->Rchild=T;        		    
        pre = T;//  preָ��������Ա��������������        
        if(T->ltag==0)// ȷ����������������������
        ThreadPreorder(T->Lchild,pre);
        if(T->rtag==0)//ȷ����������������������
        ThreadPreorder (T->Rchild,pre);
    }//����pre��ָ������� �������� ThreadPreorder(T->Lchild,pre);ִ�����ʱ
	//����ջ �����ߵ� ThreadPreorder (T->Rchild,pre);ǰ����4����
	//��T�ᱻ��ջ �� ThreadPreorder (T->Rchild,pre);��һϵ�к���ִ����Ϻ�
	//T�ص����ڵ� 
}

void ThreadInorder( bnode*T,bnode*&pre)//��ʼ����ʱ��pre��ֵΪnull;
{       
    if ( T != NULL ) {
    	if(T->ltag==0)// ȷ����������������������
        ThreadInorder(T->Lchild,pre);       
		if(T->Lchild==NULL)// *T��ǰ�������� 
        T->Lchild=pre;      
        if(pre!=NULL&&pre->rtag==1)// *pre�ĺ��������  
        pre->Rchild=T;        		    
        pre = T;//  preָ��������Ա��������������
        if(T->rtag==0)//ȷ����������������������
        ThreadInorder (T->Rchild,pre);
    }
}

void ThreadPostorder( bnode*T,bnode*&pre)//��ʼ����ʱ��pre��ֵΪnull;
{       
    if ( T != NULL ) {
    	if(T->ltag==0)// ȷ����������������������
        ThreadPostorder(T->Lchild,pre);
        if(T->rtag==0)//ȷ����������������������
        ThreadPostorder (T->Rchild,pre);
        if(T->Lchild==NULL)// *T��ǰ��������		 
        T->Lchild=pre;      
        if(pre!=NULL&&pre->rtag==1)// *pre�ĺ��������  
        pre->Rchild=T;      		    
        pre = T;//  preָ��������Ա��������������
    }
}
void Preorder(bnode* Root)
	{
		if (Root == NULL)
		{
			return;
		}
		bnode* pCur = Root;
		while (pCur != NULL)
		{
			while (pCur->Lchild != NULL && pCur->ltag == 0)
			//�ҵ�����ߵĽڵ�,����һֱΪ0
			{
				cout << pCur->data << ' '<<':'<< pCur->high<<' ';
				pCur = pCur->Lchild;
			}
			//����������ߵĵĽڵ㻹û�з���
			cout << pCur->data << ' '<<':'<< pCur->high<<' ';
			if (pCur->ltag == 1)//�������� �Ϳ��ҽڵ�
			{
				pCur = pCur->Rchild;
			}
			while (pCur != NULL)//ѭ���ҽڵ�
			{

				if (pCur->Lchild != NULL && pCur->ltag == 0)
				//������ڵ���� �� �����
				{
					break;
				}
				//����һֱ����ͬһ��ȵ��ֵܽ�� 
				cout << pCur->data << ' '<<':'<< pCur->high<<' ';
				pCur = pCur->Rchild;
			}
		}
	}
	
void InOrder(bnode* Root)
	{
		if (Root == NULL)
		{
			return;
		}
		bnode* pCur = Root;
		while (pCur)
		{
			while (pCur->ltag == 0) //������ߵĽڵ�
			{
				pCur = pCur->Lchild;
			}
			cout << pCur->data <<':'<< pCur->high<<' ';
			while ( pCur && pCur->rtag == 1)//�������̽ڵ�
			{
				pCur = pCur->Rchild;
				if(pCur)//�ߵ�6ʱ��� 
				cout << pCur->data <<':'<< pCur->high<<' ';
			}
			//û�к�̣��������� 
			if(pCur)
			pCur = pCur->Rchild;
		}
	}

/*void PostOrder(bnode* Root)
{
		if (Root == NULL)
		{
			return;
		}
		bnode* pCur = Root;
		Prev = NULL;
		while (pCur != NULL)
		{//��һ������������ߵĽڵ�
			while ( pCur->Lchild != Prev && pCur->ltag == 0) //������
			{
				pCur = pCur->Lchild;
			}//ѭ�������� pCur== Root ����Ϊ��
			//�ڶ��������ʺ��
			while (pCur && pCur->rtag==1 )
			{
				cout << pCur->data << ' ';
				Prev = pCur;
				pCur = pCur->Rchild;
			}
			//�жϴ�ʱpCur�ǲ���ָ���˸��ڵ�
			if (pCur == Root)
			{
				cout << pCur->data << ' ';
				return;
			}
			while (pCur && pCur->Rchild == Prev)
			{
				cout << pCur->data << ' ';
				Prev = pCur;
				pCur = pCur->pParent;  //����һ����
			}
			//���ﲻ����NULL�жϣ�������Rtag
			if (pCur && pCur->Rtag == Link)
			{
				pCur = pCur->pRight;
			}
		}
}
*/
void InOrderInsert(bnode*T){
	char a;
	cout<<"Ҫ���뵽�Ǹ���������";
	cin>>a;
	find(T,a);
	target->ltag=0;
	bnode*k=target->Lchild;
	bnode*s=new bnode;
	target->Lchild=s;
	char b; 
	cout<<"���������Ľ���data";
	cin>>b;
	s->data=b;
	s->Lchild=k;
	s->ltag=1;
	s->Rchild=target;
	s->rtag=1;
	s->high=4;
}
int main(){
	Tree.open("tree.txt",ios::in);
    bnode*T=NULL;
    bnode*pre=NULL;
    creat(T,1);
    tag(T);
    ThreadPreorder(T,pre);
	Preorder(T);
	//ThreadInorder(T,pre);
	//InOrderInsert(T);
	//InOrder(T);
	Tree.close();
} 
