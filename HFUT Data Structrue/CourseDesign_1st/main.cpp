/*���ɢ�б�ʵ�ֵ绰�������ϵͳ�� 
 
1) ��ÿ����¼������������û������绰���롢��ַ�� 
2) �Ӽ����������¼�����û���������ƴ����ʽ��Ϊ�ؼ��ֽ���ɢ�б�
3) ����һ���ķ��������ͻ�� 
4) ���Ҳ���ʾ�����绰����ļ�¼�� 
5) ��ѡ������Ʋ�ͬ��ɢ�к������Ƚϳ�ͻ�ʣ� 
6) ��ѡ������ɢ�к���ȷ����ǰ���£����Ը��ֲ�ͬ���ʹ����ͻ�ķ���,����ƽ�����ҳ��ȵı仯�� */

#include "TelephoneNumber.h"
#include <iostream>
#include <string>
using namespace std;

int main(void)
{
    TelephoneNumber tn;
    char choice = 0;
    while (true) {
        tn.showmenu();
        cout << "���������ѡ��";
        cin >> choice;
        switch (choice) {
        case '0':
            tn.exitsystem();
            break;
        case '1':
            cin.clear();
            tn.push();
            break;
        case '2':
            cin.clear();
            tn.find();
            break;
        default:
            cout << "�����ʽ�������������롣" << endl;
            cin.clear();
            cin.sync();
            system("pause");
            system("cls");
            continue;
        }
    }

    system("pause");
    return 0;
}
