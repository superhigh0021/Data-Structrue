#include <iostream>
#include<fstream>
#include<string.h>
#include<malloc.h>
using namespace std;
ifstream HFtree;
//哈夫曼树的存储表示
typedef struct
{
	char data;
    int weight;                 //节点的权值
    int parent, lchild, rchild; //节点的双亲，左孩子和右孩子
} HTNode, *HuffmanTree;
typedef char** HuffmanCode;//指向哈夫曼树的code 
struct file
{
	char data;
    int weight;                 //节点的权值
};
//查处权值最小且双亲为0的2的节点
void Select(HuffmanTree HT, int len, int &s1, int &s2)
{
    int i, min1 = 0x3f3f3f3f, min2 = 0x3f3f3f3f; //先赋予最大值
    for (i = 1; i <= len; i++)
    {
        if (HT[i].weight < min1 && HT[i].parent == 0)
        {
            min1 = HT[i].weight;
            s1 = i;
        }
    }
    int temp = HT[s1].weight; //将原值存放起来，然后先赋予最大值，防止s1被重复选择
    HT[s1].weight = 0x3f3f3f3f;
    for (i = 1; i <= len; i++)
    {
        if (HT[i].weight < min2 && HT[i].parent == 0)
        {
            min2 = HT[i].weight;
            s2 = i;
        }
    }
    HT[s1].weight = temp; //恢复原来的值
}
void HuffmanCoding(HuffmanTree HT,HuffmanCode* HC,int n){
	//n为叶子结点个数 
	*HC = (HuffmanCode)malloc((n+1)*sizeof(char*));
	//动态开辟内存空间存放所有非叶子结点的编码
	char* cd=(char*)malloc(n*sizeof(char));
	 //动态开辟内存空间存放某个结点的编码
	 *(cd+n-1) ='\0';
	 int start =0;
	 for(int i=1;i<=n;i++){
	 	start=n-1;
	 	for(int c=i,f=(HT+i)->parent;f!=0;c=f,f=(HT+f)->parent){
	 		if((HT+f)->lchild == c){
	 			*(cd+ --start) ='0';
			 }else{
			 	*(cd+ --start) ='1';
			 }
		 }
	 *(*HC+i)=(char*)malloc((n-start)*sizeof(char));
	 strcpy(*(*HC+i),cd + start);
     }
}
void TraverseCoding(HuffmanCode HC,int n){
	for(int i=1;i<=n;i++){
		cout<<"哈夫曼编码"<<*(HC+i)<<"  "; 
	}
}
void CreatHuffmanTree(HuffmanTree &HT, int n,int N,file *T)
{
	//n为结点数 N为文件中的字母数 
    //构造赫夫曼树HT
    int m, s1, s2, i;
    if (n <= 1)
        return;
    m = 2 * n - 1;
    HT = new HTNode[m + 1];
	//0号单元未用，所以需要动态分配m+1个单元，HT[m]表示根结点
    for (i = 1; i <= m; ++i) 
	//将1~m号单元中的双亲、左孩子，右孩子的下标都初始化为0
    {
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
        HT[i].data='0';
    }
    
    for (i = 1; i <= n; ++i)//将file中存储的权值赋值给HT数组 
    {
    	for(int k=i-1;k<N;k++){
		if(T[k].weight!=0) {
			HT[i].data=T[k].data; 
		    HT[i].weight=T[k].weight;
		    break;
	    }	
	}
    }
/*――――――――――初始化工作结束，下面开始创建赫夫曼树――――――――――*/
    for (i = n + 1; i <= m; ++i)
    { //通过n-1次的选择、删除、合并来创建赫夫曼树
        Select(HT, i - 1, s1, s2);
        //在HT[k](1≤k≤i-1)中选择两个其双亲域为0且权值最小的结点,
        // 并返回它们在HT中的序号s1和s2
        HT[s1].parent = i;
        HT[s2].parent = i;
        //得到新结点i，从森林中删除s1，s2，将s1和s2的双亲域由0改为i
        HT[i].lchild = s1;
        HT[i].rchild = s2;                            
		//s1,s2分别作为i的左右孩子
        HT[i].weight = HT[s1].weight + HT[s2].weight; 
		//的i权值为左右孩子权值之和
    }                    
}  
void show(HuffmanTree HT,int n,int m){
	for(int i=1;i<=n;i++){
		if(HT[i].data!='0'){
			cout<<HT[i].data<<' '<<HT[i].weight<<' ';
			}
		}
}

int main()
{
	HFtree.open("HFtree.txt",ios::in);
    HuffmanTree HT;
    int n=10;
    file*T=new file[n];
	for(int i=0;i<n;i++){
		HFtree>>T[i].data;
		T[i].weight=1;
		if(T[i].data>122||T[i].data<65){//检测是不是乱码 
		n=i;
		break;	
		} 
	}//先全部读入到一个数组中
	for(int i=0;i<n;i++){
		for(int k=i+1;k<n;k++){
			if(T[i].data==T[k].data&&T[k].weight==1){
				T[i].weight++;
				T[k].weight=0;//记过数的字符没有权值 
			}
		}
	}//给字符计算权值 
	int m=0;
	for(int i=0;i<n;i++){
		if(T[i].weight) m++;//m是节点数 
	} 
    CreatHuffmanTree(HT,m,n,T);//n是文件的字母数 
    HuffmanCode HC =NULL;
    HuffmanCoding(HT,&HC,2*m-1);
    show(HT,2*m-1,m);
    cout<<endl;
    TraverseCoding(HC,m);
    HFtree.close();
}
