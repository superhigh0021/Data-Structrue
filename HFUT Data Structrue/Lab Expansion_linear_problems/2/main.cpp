#include "tutor.h"
using namespace std;

int main(void)
{
    tutor t;
    while (true) {
        t.showmenu();
        int choice;
        cin >> choice;
        switch (choice) {
        case 0:
            exit(0);
            break;
        case 1:
            t.insert_tutor();
            system("cls");
            break;
        case 2:
            t.delete_member();
            system("cls");
            break;
        case 3:
            t.search();
            system("cls");
            break;
        default:
            break;
        }
    }

    system("pause");
    return 0;
}