#include<iostream>
#include<fstream> 
using namespace std;
ifstream Tree;//定义全局的输入流文件 
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
			while (pCur->ltag == 0) //找最左边的节点
			{
				if(pCur->data==a){
		    	target=pCur;
		    	return;
			    }
			    pCur = pCur->Lchild;
			}
			while ( pCur && pCur->rtag == 1)//找中序后继节点
			{
				if(pCur->data==a){
		    	target=pCur;
		    	return;
			    }
			    pCur = pCur->Rchild;
			}
			//没有后继，有右子树 
			if(pCur)
			pCur = pCur->Rchild;
		}
} 
void ThreadPreorder( bnode*T,bnode*&pre)//初始调用时，pre初值为null;
{       
    if ( T != NULL ) {
        if(T->Lchild==NULL)// *T的前驱线索化 
        T->Lchild=pre;       
        if(pre!=NULL&&pre->rtag==1)// *pre的后继线索化  
        pre->Rchild=T;        		    
        pre = T;//  pre指针跟进，以便后续结点的线索化        
        if(T->ltag==0)// 确保是左子树，而不是线索
        ThreadPreorder(T->Lchild,pre);
        if(T->rtag==0)//确保是右子树，而不是线索
        ThreadPreorder (T->Rchild,pre);
    }//由于pre是指针的引用 他不会在 ThreadPreorder(T->Lchild,pre);执行完毕时
	//被弹栈 即在走到 ThreadPreorder (T->Rchild,pre);前保持4不变
	//但T会被弹栈 在 ThreadPreorder (T->Rchild,pre);这一系列函数执行完毕后
	//T回到根节点 
}

void ThreadInorder( bnode*T,bnode*&pre)//初始调用时，pre初值为null;
{       
    if ( T != NULL ) {
    	if(T->ltag==0)// 确保是左子树，而不是线索
        ThreadInorder(T->Lchild,pre);       
		if(T->Lchild==NULL)// *T的前驱线索化 
        T->Lchild=pre;      
        if(pre!=NULL&&pre->rtag==1)// *pre的后继线索化  
        pre->Rchild=T;        		    
        pre = T;//  pre指针跟进，以便后续结点的线索化
        if(T->rtag==0)//确保是右子树，而不是线索
        ThreadInorder (T->Rchild,pre);
    }
}

void ThreadPostorder( bnode*T,bnode*&pre)//初始调用时，pre初值为null;
{       
    if ( T != NULL ) {
    	if(T->ltag==0)// 确保是左子树，而不是线索
        ThreadPostorder(T->Lchild,pre);
        if(T->rtag==0)//确保是右子树，而不是线索
        ThreadPostorder (T->Rchild,pre);
        if(T->Lchild==NULL)// *T的前驱线索化		 
        T->Lchild=pre;      
        if(pre!=NULL&&pre->rtag==1)// *pre的后继线索化  
        pre->Rchild=T;      		    
        pre = T;//  pre指针跟进，以便后续结点的线索化
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
			//找到最左边的节点,左标记一直为0
			{
				cout << pCur->data << ' '<<':'<< pCur->high<<' ';
				pCur = pCur->Lchild;
			}
			//到这来，左边的的节点还没有访问
			cout << pCur->data << ' '<<':'<< pCur->high<<' ';
			if (pCur->ltag == 1)//遇到线索 就看右节点
			{
				pCur = pCur->Rchild;
			}
			while (pCur != NULL)//循环右节点
			{

				if (pCur->Lchild != NULL && pCur->ltag == 0)
				//遇到左节点存在 ， 则访问
				{
					break;
				}
				//否则一直访问同一深度的兄弟结点 
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
			while (pCur->ltag == 0) //找最左边的节点
			{
				pCur = pCur->Lchild;
			}
			cout << pCur->data <<':'<< pCur->high<<' ';
			while ( pCur && pCur->rtag == 1)//找中序后继节点
			{
				pCur = pCur->Rchild;
				if(pCur)//走到6时会空 
				cout << pCur->data <<':'<< pCur->high<<' ';
			}
			//没有后继，有右子树 
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
		{//第一步：找树最左边的节点
			while ( pCur->Lchild != Prev && pCur->ltag == 0) //左子树
			{
				pCur = pCur->Lchild;
			}//循环结束后 pCur== Root 或者为空
			//第二步：访问后继
			while (pCur && pCur->rtag==1 )
			{
				cout << pCur->data << ' ';
				Prev = pCur;
				pCur = pCur->Rchild;
			}
			//判断此时pCur是不是指向了根节点
			if (pCur == Root)
			{
				cout << pCur->data << ' ';
				return;
			}
			while (pCur && pCur->Rchild == Prev)
			{
				cout << pCur->data << ' ';
				Prev = pCur;
				pCur = pCur->pParent;  //往上一级走
			}
			//这里不能用NULL判断，而是用Rtag
			if (pCur && pCur->Rtag == Link)
			{
				pCur = pCur->pRight;
			}
		}
}
*/
void InOrderInsert(bnode*T){
	char a;
	cout<<"要插入到那个结点的左孩子";
	cin>>a;
	find(T,a);
	target->ltag=0;
	bnode*k=target->Lchild;
	bnode*s=new bnode;
	target->Lchild=s;
	char b; 
	cout<<"输入待插入的结点的data";
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
