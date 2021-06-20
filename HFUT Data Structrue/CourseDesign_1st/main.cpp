/*设计散列表实现电话号码查找系统。 
 
1) 设每个记录有下列数据项：用户名、电话号码、地址； 
2) 从键盘输入各记录，以用户名（汉语拼音形式）为关键字建立散列表；
3) 采用一定的方法解决冲突； 
4) 查找并显示给定电话号码的记录； 
5) （选作）设计不同的散列函数，比较冲突率； 
6) （选作）在散列函数确定的前提下，尝试各种不同类型处理冲突的方法,考察平均查找长度的变化。 */

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
        cout << "请输入你的选择：";
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
            cout << "输入格式有误！请重新输入。" << endl;
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
