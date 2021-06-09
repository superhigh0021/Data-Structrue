//判断PQ[i]是否合法
#define InHeap(n, i) (((-1) < (i)) && ((i) < (n)))
#define Parent(i) ((i - 1) >> 1)               //PQ[i]的父节点
#define LastInternal(n) Parent(n - 1)          //最后一个内部节点，即末节点的父亲
#define LChild(i) (1 + ((i) << 1))             //PQ[i]的左孩子
#define RChild(i) ((1 + (i)) << 1)             //PQ[i]的右孩子
#define ParentValid(i) (0 < i)                 //判断PQ[i]是否有父亲
#define LChildValid(n, i) InHeap(n, LChild(i)) //判断PQ[i]是否有一个左孩子
#define RChildValid(n, i) InHeap(n, RChild(i)) //判断PQ[i]是否有两个孩子
#define Bigger(PQ, i, j) (lt(PQ[i], PQ[j]) ? j : i)//取大者
