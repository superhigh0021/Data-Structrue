/*
�� 20��ɢ�б�������ʵ�� 
�������������ɢ�б�ʵ�ֵ绰�������ϵͳ�� 
ʵ��Ҫ�� 
1) ��ÿ����¼������������û������绰���롢��ַ�� 
2) �Ӽ����������¼�����û���������ƴ����ʽ��Ϊ�ؼ��ֽ���ɢ�б�
3) ����һ���ķ��������ͻ�� 
4) ���Ҳ���ʾ�����绰����ļ�¼�� 
5) ��ѡ������Ʋ�ͬ��ɢ�к������Ƚϳ�ͻ�ʣ� 
6) ��ѡ������ɢ�к���ȷ����ǰ���£����Ը��ֲ�ͬ���ʹ����ͻ�ķ���,����ƽ�����ҳ��ȵı仯�� */

#include <iostream>
#include <string>
#include "TelephoneNumber.h"
using namespace std;


int main(void)
{
    TelephoneNumber tn;
    int choice = 0;
    while (true)
    {
        tn.showmenu();
        cout << "���������ѡ��";
        cin >> choice;
        switch (choice)
        {
        case 0:
            tn.exitsystem();
            break;
        case 1:
            tn.push();
            break;
        case 2:
            tn.find();
            break;
        default:
            cout<<"�����ʽ����"<<endl;
            continue;
        }
    }

    system("pause");
    return 0;
}
