#include <iostream>
#include<fstream>
#include<string.h>
#include<malloc.h>
using namespace std;
ifstream HFtree;
//���������Ĵ洢��ʾ
typedef struct
{
	char data;
    int weight;                 //�ڵ��Ȩֵ
    int parent, lchild, rchild; //�ڵ��˫�ף����Ӻ��Һ���
} HTNode, *HuffmanTree;
typedef char** HuffmanCode;//ָ�����������code 
struct file
{
	char data;
    int weight;                 //�ڵ��Ȩֵ
};
//�鴦Ȩֵ��С��˫��Ϊ0��2�Ľڵ�
void Select(HuffmanTree HT, int len, int &s1, int &s2)
{
    int i, min1 = 0x3f3f3f3f, min2 = 0x3f3f3f3f; //�ȸ������ֵ
    for (i = 1; i <= len; i++)
    {
        if (HT[i].weight < min1 && HT[i].parent == 0)
        {
            min1 = HT[i].weight;
            s1 = i;
        }
    }
    int temp = HT[s1].weight; //��ԭֵ���������Ȼ���ȸ������ֵ����ֹs1���ظ�ѡ��
    HT[s1].weight = 0x3f3f3f3f;
    for (i = 1; i <= len; i++)
    {
        if (HT[i].weight < min2 && HT[i].parent == 0)
        {
            min2 = HT[i].weight;
            s2 = i;
        }
    }
    HT[s1].weight = temp; //�ָ�ԭ����ֵ
}
void HuffmanCoding(HuffmanTree HT,HuffmanCode* HC,int n){
	//nΪҶ�ӽ����� 
	*HC = (HuffmanCode)malloc((n+1)*sizeof(char*));
	//��̬�����ڴ�ռ������з�Ҷ�ӽ��ı���
	char* cd=(char*)malloc(n*sizeof(char));
	 //��̬�����ڴ�ռ���ĳ�����ı���
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
		cout<<"����������"<<*(HC+i)<<"  "; 
	}
}
void CreatHuffmanTree(HuffmanTree &HT, int n,int N,file *T)
{
	//nΪ����� NΪ�ļ��е���ĸ�� 
    //����շ�����HT
    int m, s1, s2, i;
    if (n <= 1)
        return;
    m = 2 * n - 1;
    HT = new HTNode[m + 1];
	//0�ŵ�Ԫδ�ã�������Ҫ��̬����m+1����Ԫ��HT[m]��ʾ�����
    for (i = 1; i <= m; ++i) 
	//��1~m�ŵ�Ԫ�е�˫�ס����ӣ��Һ��ӵ��±궼��ʼ��Ϊ0
    {
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
        HT[i].data='0';
    }
    
    for (i = 1; i <= n; ++i)//��file�д洢��Ȩֵ��ֵ��HT���� 
    {
    	for(int k=i-1;k<N;k++){
		if(T[k].weight!=0) {
			HT[i].data=T[k].data; 
		    HT[i].weight=T[k].weight;
		    break;
	    }	
	}
    }
/*�D�D�D�D�D�D�D�D�D�D��ʼ���������������濪ʼ�����շ������D�D�D�D�D�D�D�D�D�D*/
    for (i = n + 1; i <= m; ++i)
    { //ͨ��n-1�ε�ѡ��ɾ�����ϲ��������շ�����
        Select(HT, i - 1, s1, s2);
        //��HT[k](1��k��i-1)��ѡ��������˫����Ϊ0��Ȩֵ��С�Ľ��,
        // ������������HT�е����s1��s2
        HT[s1].parent = i;
        HT[s2].parent = i;
        //�õ��½��i����ɭ����ɾ��s1��s2����s1��s2��˫������0��Ϊi
        HT[i].lchild = s1;
        HT[i].rchild = s2;                            
		//s1,s2�ֱ���Ϊi�����Һ���
        HT[i].weight = HT[s1].weight + HT[s2].weight; 
		//��iȨֵΪ���Һ���Ȩֵ֮��
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
		if(T[i].data>122||T[i].data<65){//����ǲ������� 
		n=i;
		break;	
		} 
	}//��ȫ�����뵽һ��������
	for(int i=0;i<n;i++){
		for(int k=i+1;k<n;k++){
			if(T[i].data==T[k].data&&T[k].weight==1){
				T[i].weight++;
				T[k].weight=0;//�ǹ������ַ�û��Ȩֵ 
			}
		}
	}//���ַ�����Ȩֵ 
	int m=0;
	for(int i=0;i<n;i++){
		if(T[i].weight) m++;//m�ǽڵ��� 
	} 
    CreatHuffmanTree(HT,m,n,T);//n���ļ�����ĸ�� 
    HuffmanCode HC =NULL;
    HuffmanCoding(HT,&HC,2*m-1);
    show(HT,2*m-1,m);
    cout<<endl;
    TraverseCoding(HC,m);
    HFtree.close();
}
