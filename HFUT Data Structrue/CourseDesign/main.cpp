/*
�� 20��ɢ�б�������ʵ�� 
�������������ɢ�б�ʵ�ֵ绰�������ϵͳ�� 
ʵ��Ҫ�� 
1) ��ÿ����¼������������û������绰���롢��ַ�� 
2) �Ӽ����������¼�����û���������ƴ����ʽ��Ϊ�ؼ��ֽ���ɢ�б�
3) ����һ���ķ��������ͻ�� 
4) ���Ҳ���ʾ�����绰����ļ�¼�� 
5) ��ѡ������Ʋ�ͬ��ɢ�к������Ƚϳ�ͻ�ʣ� 
6) ��ѡ������ɢ�к���ȷ����ǰ���£����Ը��ֲ�ͬ���ʹ����ͻ�ķ����� 
����ƽ�����ҳ��ȵı仯�� */

#include "hashtable.h"
#include <iostream>
#include<string>
using namespace std;

void test01(){
    Hashtable<string,long long>h;
    string a;
    long long b;
    do{
        cin>>b>>a;
        h.put(a,b);
    }while(getchar()!='#');
    cout<<*(h.get("wangwu"));
}

int main(void){
    test01();

    system("pause");
    return 0;
}
