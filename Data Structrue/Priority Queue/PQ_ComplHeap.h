//�ж�PQ[i]�Ƿ�Ϸ�
#define InHeap(n, i) (((-1) < (i)) && ((i) < (n)))
#define Parent(i) ((i - 1) >> 1)               //PQ[i]�ĸ��ڵ�
#define LastInternal(n) Parent(n - 1)          //���һ���ڲ��ڵ㣬��ĩ�ڵ�ĸ���
#define LChild(i) (1 + ((i) << 1))             //PQ[i]������
#define RChild(i) ((1 + (i)) << 1)             //PQ[i]���Һ���
#define ParentValid(i) (0 < i)                 //�ж�PQ[i]�Ƿ��и���
#define LChildValid(n, i) InHeap(n, LChild(i)) //�ж�PQ[i]�Ƿ���һ������
#define RChildValid(n, i) InHeap(n, RChild(i)) //�ж�PQ[i]�Ƿ�����������
#define Bigger(PQ, i, j) (lt(PQ[i], PQ[j]) ? j : i)//ȡ����
