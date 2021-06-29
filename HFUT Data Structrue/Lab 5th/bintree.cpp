#include"bintree.h"
using namespace std;

int main(void){
    BinTree<char> bt;
    bt.insertAsRoot('A');
    BinNodePosi(char) p=bt.root();
    bt.insertAsLC(p,'B');
    bt.insertAsRC(p,'C');
    bt.insertAsLC(p->lchild,'D');
    bt.insertAsRC(p->lchild,'E');
    bt.insertAsLC(p->rchild,'F');
    bt.insertAsRC(p->rchild,'G');

    bt.travIn();
    cout<<endl;

    system("pause");
    return 0;
}